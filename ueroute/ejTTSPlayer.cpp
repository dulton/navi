/* ejTTSPlayer.cpp
*
* Copyright (C) 2001-2008, SinoVoice Ltd.
*
*/

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>

//#include "eJTTS.h"
#include "ejTTSPlayer.h"


#define JTTS_PLAY_BUF_NUM	2				//�������ĸ���
#define JTTS_PLAY_BUF_SIZE	1024 * 4		//�������Ĵ�С

// ������ʹ��״̬
typedef enum
{
	JTTS_BUFF_FREE,			// ����������
	JTTS_BUFF_PLAYING,		// ���������ڲ���
	JTTS_BUFF_PLAYED		// �������������
};

// ���������̵߳�����
typedef enum
{
	jtTTS_CONTROL_NONE,
	jtTTS_CONTROL_PLAY,
	jtTTS_CONTROL_END
}jtControlCmd;

// �����̵߳�״̬
typedef enum
{
	jtTTS_COMMAND_IDLE,		// �ɽ�������
	jtTTS_COMMAND_HANDLING,	// �������
	jtTTS_COMMAND_EXIT		// ��������
}jtCommandStatus;

// JTTSPlayData���ڴ�Ų����߳��ڵ�����
typedef struct tagJTTSPlayData
{
	unsigned long		hJTTS;				// JTTS���
	char*				pHeap;				// Ϊ���濪�ٵĻ�����
//	CRITICAL_SECTION	CriticalSection;	// ���ݲ����ٽ���
	
	HWAVEOUT			hWaveOut;			// �����豸���
	char 				PlayBuf  [JTTS_PLAY_BUF_SIZE * JTTS_PLAY_BUF_NUM];	// ���ٻ�����
	UINT 				BuffState[JTTS_PLAY_BUF_NUM];						// ��ʾ�û������Ĳ���״̬�����У��ڲ��ţ��������
	WAVEHDR				wavHeader[JTTS_PLAY_BUF_NUM];						// ���Ż�����ͷ
}JTTSPlayData;

// JTTSCommandData�����������ݣ����ڵ����̣߳����̣߳��ͷ����߳�֮���ͬ��
typedef struct tagJTTSCommandData
{
	jtCommandStatus	uStatus;	// �����״̬
	jtControlCmd	uType;		// ��������

	struct Play
	{
		JTTSCALLBACKPROCEX	lpfnCallback;
		DWORD		dwUserData;
	}Play;
}JTTSCommandData;

// �Զ�������
typedef struct tagMyUserData
{
	char szTextIn[TTS_PLAYER_MAX_TEXTLEN];	// �����ı��ַ���
	int iStrLen;
	FILE* fpOutputFile;						// ��������ļ�·��
}MyUserData, *PMyUserData;

MyUserData		myUserData;

// JTTSSyncData�����߳�֮���ͬ��������ͬ�����ݺ�Ҫִ�е�����
typedef struct tagJTTSSyncData
{
	HANDLE				hEventChild;		// �����̣߳����̣߳�ʹ�õ�ͬ���¼�
	CRITICAL_SECTION	CriticalSection;	// ���ݲ����ٽ���

	BOOL				bStatStable;		// ״̬���ȶ�ת�������ڱ�ʶ�м�״̬
	BOOL				bStopCommand;		// ֹͣ����
	jtTTSPlayerStatus	eStatus;			// ���Ų�״̬
	JTTSCommandData		Command;			// ��������ṹ
}JTTSSyncData;

static HANDLE			g_hPlayHandle = NULL;		// �����߳̾��
static JTTSSyncData		g_SyncData;					// �߳�ͬ������
static JTTSPlayData		g_PlayData;					// �����߳�����


#ifndef _T
#define _T(x)	x
#endif	// _T

//////////////////////////////////////////////////////////////////////////

//��ò�������ǰ��Ƶ��ʽ
ERRCODE GetAudioFormat(DWORD dwHandle, unsigned int* pnSamplesPerSec, unsigned int* pnBitsPerSample)
{
	ERRCODE err = TTS_PLAYER_ERR_NONE;
	long	nFormat = 0;
	
	err = jtTTS_GetParam(dwHandle, jtTTS_PARAM_WAV_FORMAT, &nFormat);
	if(err != TTS_PLAYER_ERR_NONE)
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	
	switch(nFormat)
	{
	case jtTTS_FORMAT_PCM_NORMAL:
	case jtTTS_FORMAT_PCM_16K16B:
		*pnSamplesPerSec = 16000;
		*pnBitsPerSample = 16;
		break;
	case jtTTS_FORMAT_VOX_6K:
		*pnSamplesPerSec = 6000;
		*pnBitsPerSample = 4;
		break;
	case jtTTS_FORMAT_VOX_8K:
		*pnSamplesPerSec = 8000;
		*pnBitsPerSample = 4;
		break;
	case jtTTS_FORMAT_ALAW_8K:
	case jtTTS_FORMAT_uLAW_8K:
	case jtTTS_FORMAT_PCM_8K8B:	
		*pnSamplesPerSec = 8000;
		*pnBitsPerSample = 8;
		break;
	case jtTTS_FORMAT_PCM_8K16B:
		*pnSamplesPerSec = 8000;
		*pnBitsPerSample = 16;
		break;
	case jtTTS_FORMAT_PCM_16K8B:
		*pnSamplesPerSec = 16000;
		*pnBitsPerSample = 8;
		break;
	case jtTTS_FORMAT_PCM_11K8B:
		*pnSamplesPerSec = 11025;
		*pnBitsPerSample = 8;
		break;
	case jtTTS_FORMAT_PCM_11K16B:
		*pnSamplesPerSec = 11025;
		*pnBitsPerSample = 16;
		break;
	case jtTTS_FORMAT_PCM_22K8B:
		*pnSamplesPerSec = 22050;
		*pnBitsPerSample = 8;
		break;
	case jtTTS_FORMAT_PCM_22K16B:
		*pnSamplesPerSec = 22050;
		*pnBitsPerSample = 16;
		break;
	case jtTTS_FORMAT_PCM_44K8B:
		*pnSamplesPerSec = 44100;
		*pnBitsPerSample = 8;
		break;
	case jtTTS_FORMAT_PCM_44K16B:
		*pnSamplesPerSec = 44100;
		*pnBitsPerSample = 16;
		break;
	default:
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;		
	}
	
	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}

//׼�����Ż���
void PrepareDevice(HWAVEOUT hwo, WAVEHDR* pwh, char* pVoiceData, unsigned long nLen, DWORD dwUser)
{
	MMRESULT mmr = 0;
	pwh->lpData = pVoiceData;
	pwh->dwBufferLength = nLen;
	pwh->dwUser = dwUser;
	pwh->dwBytesRecorded = 0;
	pwh->dwFlags = 0;
	pwh->dwLoops = 0;
	
	mmr = waveOutPrepareHeader(hwo, pwh, sizeof(WAVEHDR));
}

//�ͷŲ��Ż���
void UnprepareDevice(HWAVEOUT hwo, WAVEHDR* pwh)
{
	MMRESULT mmr = 0;
	mmr = waveOutUnprepareHeader(hwo, pwh, sizeof(WAVEHDR));
}


//�����������벥���豸
void PlayToDevice(HWAVEOUT hwo, WAVEHDR* pwh)
{
	MMRESULT mmr = 0;
	mmr = waveOutWrite(hwo, pwh, sizeof(WAVEHDR));
}


//����һ��������
ERRCODE PlayOneBuffer(void* pPlayDevice, unsigned long nIndex, unsigned long nLen)
{
	if(nIndex < 0 || nIndex >= JTTS_PLAY_BUF_NUM)
	{
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	}
	
	if(g_PlayData.BuffState[nIndex] != JTTS_BUFF_PLAYING)
	{
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	}
	
	HWAVEOUT hwo = (HWAVEOUT)pPlayDevice;
	WAVEHDR* pwh = (WAVEHDR*)&g_PlayData.wavHeader[nIndex];
	

	PrepareDevice(hwo, pwh, &g_PlayData.PlayBuf[nIndex * JTTS_PLAY_BUF_SIZE], nLen, (DWORD)nIndex);
	PlayToDevice(hwo, pwh);

	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}

//�ص���������������Ϻ���TTS����ȡ����
void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{	
	unsigned long iBuffIndex;
	
	switch (uMsg)
	{
	case WOM_DONE:		
		iBuffIndex = (unsigned long)((LPWAVEHDR)dwParam1)->dwUser;	

		if(iBuffIndex < 0 || iBuffIndex >= JTTS_PLAY_BUF_NUM)
		{
			// Error
			iBuffIndex = iBuffIndex;
		}

		if(g_PlayData.BuffState[iBuffIndex] == JTTS_BUFF_PLAYING)
		{
			g_PlayData.BuffState[iBuffIndex] = JTTS_BUFF_PLAYED;
		}
		break;
	}

}

//�����豸��ʼ��
HWAVEOUT InitAudioDevice()
{
	HWAVEOUT hwo = NULL;
	UINT uDeviceID = 0;
	WAVEFORMATEX wfx;
	MMRESULT mmr = 0;
	
	// ��Ƶ�����豸������Ϣ
	UINT nSamplesPerSec = 16000;
	UINT nBitsPerSample = 16;
	GetAudioFormat(g_PlayData.hJTTS, &nSamplesPerSec, &nBitsPerSample);
	
	wfx.cbSize = sizeof(WAVEFORMATEX);
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = nSamplesPerSec;
	wfx.nAvgBytesPerSec = nSamplesPerSec * nBitsPerSample / 8;
	wfx.nBlockAlign = (WORD)(nBitsPerSample/8);
	wfx.wBitsPerSample = (WORD)nBitsPerSample;
	mmr = waveOutOpen(&hwo, uDeviceID, &wfx, (DWORD)waveOutProc, 0, CALLBACK_FUNCTION);
	
	return hwo;
}

//�ͷ���Ƶ�����豸
void ResetAudioDevice(HWAVEOUT hwo)
{
	MMRESULT mmr = waveOutReset(hwo);
	if (mmr != MMSYSERR_NOERROR)
	{
		return;
	}
}

//�ͷ���Ƶ�����豸
void EndAudioDevice(HWAVEOUT hwo)
{
	MMRESULT mmr;

 	mmr = waveOutReset(hwo);
	if (mmr != MMSYSERR_NOERROR)
	{
		return;
	}

	mmr = waveOutClose(hwo);
	if (mmr != MMSYSERR_NOERROR)
	{
		return;
	}
}

/*������:	MyJTTSInit
* ˵��:		�����ڴ桢TTS����ĳ�ʼ��
* ����:		szCNLib		[in] ���Ŀ�·��
*			szENLib		[in] Ӣ�Ŀ�·��
*			szDMLib		[in] ���ƿ�·��
* ����ֵ:	ERRCODE
*/
static ERRCODE MyJTTSInit(const char* szCNLib, const char* szENLib, const char* szDMLib)
{
	jtErrCode dwError;
	long lSize;
	unsigned char		byMajor;
	unsigned char		byMinor;
	unsigned long		iRevision;
	unsigned long hTTS;		//handle to TTS engine
	void* pGlobalData = NULL;

	//��ȡTTS�汾��Ϣ
	dwError = jtTTS_GetVersion(&byMajor, &byMinor, &iRevision);
	if(dwError != jtTTS_ERR_NONE)
	{
		return dwError;
	}

	//���HEAP��С
	dwError = jtTTS_GetExtBufSize((const signed char*)szCNLib, (const signed char*)szENLib, (const signed char*)szDMLib, &lSize);

	if(jtTTS_ERR_NONE != dwError)
	{
		return (ERRCODE)TTS_PLAYER_ERR_MEMORY;
	}
	pGlobalData = (char*)malloc(lSize);
	if(pGlobalData == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_MEMORY;
	}
	
	//��ʼ��TTS engine
	
	//ִ�г�ʼ��
	dwError = jtTTS_Init((const signed char*)szCNLib, (const signed char*)szENLib, (const signed char*)szDMLib, &hTTS, pGlobalData);	


	if(dwError != TTS_PLAYER_ERR_NONE)
	{
		free(pGlobalData);
		return dwError;
	}

	if (NULL == hTTS)
	{
		//Error
	}

	g_PlayData.hJTTS = hTTS;
	g_PlayData.pHeap = (char *)pGlobalData;
	g_PlayData.hWaveOut = NULL;

	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_INPUTTXT_MODE, jtTTS_INPUT_TEXT_DIRECT);
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_CALLBACK_USERDATA, (long)&myUserData);
	
	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}

// output voice callback type
// pParameter			[in] user callback parameter
// iOutputFormat		[in] output data format
// pData				[in] output data buffer
// iSize				[in] output data size
jtErrCode OutputVoiceToFileProc(void* pParameter, long iOutputFormat, void* pData, long iSize)
{
	MyUserData *	pUserData;
	
	if(pParameter != NULL)
	{
		pUserData = (MyUserData *)pParameter;
	}
	else
	{
		return jtTTS_ERR_NONE;
	}
	
	if(pUserData->fpOutputFile == NULL)
		return jtTTS_ERR_NONE;

	fwrite(pData, 1, iSize, pUserData->fpOutputFile);
		
	return jtTTS_ERR_NONE;
}

// output voice callback type
// pParameter			[in] user callback parameter
// iOutputFormat		[in] output data format
// pData				[in] output data buffer
// iSize				[in] output data size
jtErrCode OutputVoiceToPlayProc(void* pParameter, long iOutputFormat, void* pData, long iSize)
{
	long			nLen;
	unsigned long 	nBuffIndex;	
	ERRCODE			dwError;
	
	nLen = JTTS_PLAY_BUF_SIZE;

	do //iSize>nLenʱ�ּ��β���
	{
		EnterCriticalSection(&g_SyncData.CriticalSection);
		if (g_SyncData.eStatus == TTS_PLAYER_SYNTHESIZING)
		{
			g_SyncData.eStatus = TTS_PLAYER_PLAYING;
		}
		LeaveCriticalSection(&g_SyncData.CriticalSection);

		//PAUSE����
		while (g_SyncData.eStatus == TTS_PLAYER_PAUSE)
		{
			Sleep(0);
			if (g_SyncData.bStopCommand)
			{
				EnterCriticalSection(&g_SyncData.CriticalSection);
				g_SyncData.eStatus = TTS_PLAYER_PLAYING;
				LeaveCriticalSection(&g_SyncData.CriticalSection);
				return jtTTS_ERR_NONE;
			}
		}
		
		for (nBuffIndex = 0; nBuffIndex < JTTS_PLAY_BUF_NUM; nBuffIndex++)
		{
			// ��Buffer�����Ѳ����꣬�����ͷ�
			if (g_PlayData.BuffState[nBuffIndex] == JTTS_BUFF_PLAYED)
			{
				UnprepareDevice(g_PlayData.hWaveOut, &g_PlayData.wavHeader[nBuffIndex]);	
				g_PlayData.BuffState[nBuffIndex] = JTTS_BUFF_FREE;		
			}
		}
		
		for (nBuffIndex = 0; nBuffIndex < JTTS_PLAY_BUF_NUM; nBuffIndex++)
		{
			// ��Buffer�������ڲ����У�����ʹ��
			if (g_PlayData.BuffState[nBuffIndex] == JTTS_BUFF_FREE)
			{
				g_PlayData.BuffState[nBuffIndex] = JTTS_BUFF_PLAYING;
				break;
			}
		}

		// ��ǰû�п���Buffer���ȴ�
		if (nBuffIndex == JTTS_PLAY_BUF_NUM)
		{
			Sleep(0);	// ������ϵͳ�������̣߳��ó�CPU 
			continue;
		}
		
		// ��ȡһ��session����
		if (nLen > iSize)
			nLen = iSize;
		
		memcpy(g_PlayData.PlayBuf + nBuffIndex * JTTS_PLAY_BUF_SIZE, pData, nLen);

		// ���ò��Žӿڽ��в���	
		dwError = PlayOneBuffer(g_PlayData.hWaveOut, nBuffIndex, nLen);
		if (dwError != TTS_PLAYER_ERR_NONE)
		{
			g_PlayData.BuffState[nBuffIndex] = JTTS_BUFF_FREE;
		}
		nLen = iSize - nLen;
	}
	while(nLen > 0);
	
	if(iSize == 0)	//�������ţ���ϵͳ֪ͨ�����������õ������ʹ��
	{
		WAVEHDR* pwh = (WAVEHDR*)&g_PlayData.wavHeader[nBuffIndex];
		unsigned int nSampleRate = 16000, nBitsPerSample;
		GetAudioFormat(g_PlayData.hJTTS, &nSampleRate, &nBitsPerSample);
		Sleep(jtTTS_OUTPUT_DATA_SIZE * 1000 / nSampleRate);
		waveOutProc(g_PlayData.hWaveOut, WOM_DONE, 0, (DWORD)pwh, 0);
	}
	return jtTTS_ERR_NONE;
}

//�̣߳�����
static ERRCODE MyJTTSPlay(JTTSCALLBACKPROCEX lpfnCallback, unsigned long dwUserData)
{
	unsigned long 	nBuffIndex;
	ERRCODE	nErr = TTS_PLAYER_ERR_NONE;

	if (g_PlayData.hWaveOut == NULL)
	{
		HWAVEOUT hwo;

		hwo = InitAudioDevice();
		if (hwo == NULL)
		{
			if (lpfnCallback != NULL)
			{
				lpfnCallback(TTS_PLAYER_NOTIFY_ERROR, TTS_PLAYER_ERR_AUDIO_DEVICE, dwUserData);
			}
			g_SyncData.bStatStable = TRUE;
			return (ERRCODE)TTS_PLAYER_ERR_AUDIO_DEVICE;
		}
		g_PlayData.hWaveOut = hwo;
	}

	/* ������Ƶ����ص� */
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_OUTPUT_CALLBACK, (long)OutputVoiceToPlayProc);

	EnterCriticalSection(&g_SyncData.CriticalSection);
	if (g_SyncData.bStopCommand)
	{
		g_SyncData.eStatus = TTS_PLAYER_IDLE;
		g_SyncData.bStatStable = TRUE;
		g_SyncData.bStopCommand = FALSE;
		LeaveCriticalSection(&g_SyncData.CriticalSection);

		EndAudioDevice(g_PlayData.hWaveOut);
		g_PlayData.hWaveOut = NULL;

		if(lpfnCallback != NULL)
		{
			lpfnCallback(TTS_PLAYER_NOTIFY_END, 0L, dwUserData);
		}
		return jtTTS_ERR_NONE;
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	EnterCriticalSection(&g_SyncData.CriticalSection);
	g_SyncData.eStatus = TTS_PLAYER_SYNTHESIZING;
	g_SyncData.bStatStable = TRUE;
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	nErr = jtTTS_SynthesizeText(g_PlayData.hJTTS, myUserData.szTextIn, myUserData.iStrLen);

	if (jtTTS_ERR_NONE != nErr)
	{
		EnterCriticalSection(&g_SyncData.CriticalSection);
		g_SyncData.eStatus = TTS_PLAYER_IDLE;
		g_SyncData.bStatStable = TRUE;
		g_SyncData.bStopCommand = FALSE;
		LeaveCriticalSection(&g_SyncData.CriticalSection);

		if (lpfnCallback != NULL)
		{
			lpfnCallback(TTS_PLAYER_NOTIFY_ERROR, (long)nErr, dwUserData);
		}
		return nErr;
	}

	EnterCriticalSection(&g_SyncData.CriticalSection);
	g_SyncData.bStatStable = FALSE;
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	// �ȴ�������ϣ����˳�
	while (TRUE)
	{
		for (nBuffIndex = 0; nBuffIndex < JTTS_PLAY_BUF_NUM; nBuffIndex++)
		{
			// ��Buffer�����Ѳ����꣬�����ͷ�
			if (g_PlayData.BuffState[nBuffIndex] == JTTS_BUFF_PLAYED)
			{
				UnprepareDevice(g_PlayData.hWaveOut, &g_PlayData.wavHeader[nBuffIndex]);
				g_PlayData.BuffState[nBuffIndex] = JTTS_BUFF_FREE;					
			}
		}
		
		for (nBuffIndex = 0; nBuffIndex < JTTS_PLAY_BUF_NUM; nBuffIndex++)
		{
			if (g_PlayData.BuffState[nBuffIndex] != JTTS_BUFF_FREE)
			{
				break;
			}
		}

		if (nBuffIndex == JTTS_PLAY_BUF_NUM)
		{
			break;
		}
		else
		{
			Sleep(0);	// ��ϵͳ�������ó�CPU
		}
	}

	if (g_PlayData.hWaveOut != NULL)
	{
		EndAudioDevice(g_PlayData.hWaveOut);
		g_PlayData.hWaveOut = NULL;
	}

	EnterCriticalSection(&g_SyncData.CriticalSection);
	g_SyncData.eStatus = TTS_PLAYER_IDLE;
	g_SyncData.bStatStable = TRUE;
	g_SyncData.bStopCommand = FALSE;
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	// ֪ͨ�ϲ�Ӧ�ò��Ź��̽���		
	if(lpfnCallback != NULL)
	{
		lpfnCallback(TTS_PLAYER_NOTIFY_END, 0L, dwUserData);
	}

	return TTS_PLAYER_ERR_NONE;
}

//�����̺߳���
DWORD WINAPI MyJTTSServiceThread(LPVOID lpParameter)
{
	DWORD			dwIndex;
	ERRCODE			dwErrCode;

	while (g_SyncData.Command.uStatus != jtTTS_COMMAND_EXIT)
	{
		dwIndex = WaitForSingleObject(g_SyncData.hEventChild, INFINITE);

		if(dwIndex != WAIT_OBJECT_0)
		{
			// Error
			break;
		}

		EnterCriticalSection(&g_SyncData.CriticalSection);
		if(g_SyncData.Command.uStatus == jtTTS_COMMAND_EXIT)
		{
			LeaveCriticalSection(&g_SyncData.CriticalSection);
			break;
		}
		LeaveCriticalSection(&g_SyncData.CriticalSection);

		switch(g_SyncData.Command.uType)
		{
		case jtTTS_CONTROL_NONE:
			break;
		case jtTTS_CONTROL_PLAY:
			dwErrCode = MyJTTSPlay(g_SyncData.Command.Play.lpfnCallback, g_SyncData.Command.Play.dwUserData);
			break;
		case jtTTS_CONTROL_END:
			return 0;
			break;
		default:
			break;
		}

		EnterCriticalSection(&g_SyncData.CriticalSection);
		if(g_SyncData.Command.uStatus == jtTTS_COMMAND_EXIT)
		{
			LeaveCriticalSection(&g_SyncData.CriticalSection);
			break;
		}
		else
		{
			g_SyncData.Command.uType = jtTTS_CONTROL_NONE;
			g_SyncData.Command.uStatus = jtTTS_COMMAND_IDLE;
		}
		LeaveCriticalSection(&g_SyncData.CriticalSection);
	}

	return 0;
}

/*������:	ejTTSPlayer_Play
* ˵��:		TTSPlayer�����ı�
* ����:		ePlayMode		[in] ����ģʽ
*			pcszText		[in] �����ŵ��ı�
*			lpfnCallback	[in] �ص�����ָ��
*			dwUserData		[in] �ص������û�����
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_Play(jtTTSPlayMode ePlayMode, char *pcszText, JTTSCALLBACKPROCEX lpfnCallback, DWORD dwUserData)
{
	long lCodePage = -1;

	if (g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	// �����߳�û�д�����
	EnterCriticalSection(&g_SyncData.CriticalSection);	
	if(g_SyncData.Command.uStatus == jtTTS_COMMAND_HANDLING)
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_PLAYING;
	}
	else if (g_SyncData.Command.uStatus == jtTTS_COMMAND_EXIT)
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_NONE;
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	EnterCriticalSection(&g_SyncData.CriticalSection);	
	if(g_SyncData.eStatus != TTS_PLAYER_IDLE)
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_PLAYING;
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	EnterCriticalSection(&g_SyncData.CriticalSection);	
	if(!g_SyncData.bStatStable)
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_PLAYING;
	}
	else
	{
		g_SyncData.bStatStable = FALSE; //״̬ת����
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	// ��Ӧ���������
	if (g_PlayData.hJTTS == NULL)
	{
		g_SyncData.bStatStable = TRUE;
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	if(pcszText == NULL)
	{
		g_SyncData.bStatStable = TRUE;
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	}

	// �ж��ϲ�Ӧ���ṩ�Ļص������Ƿ���ȷ
	if (lpfnCallback != NULL && IsBadCodePtr((FARPROC)lpfnCallback))
	{
		g_SyncData.bStatStable = TRUE;
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	}
	
	// ��������ı����Ƶ��Լ����ı�������
	memset(&myUserData, 0, sizeof(MyUserData));
	jtTTS_GetParam(g_PlayData.hJTTS, jtTTS_PARAM_CODEPAGE, &lCodePage);	
	if (jtTTS_CODEPAGE_UNICODE == lCodePage || jtTTS_CODEPAGE_UNICODE_BE == lCodePage)
	{
		myUserData.iStrLen = wcslen((const wchar_t *)pcszText) * sizeof(wchar_t);
	}
	else
	{
		myUserData.iStrLen = strlen(pcszText) * sizeof(char);
	}

	if (TTS_PLAYER_MAX_TEXTLEN - 2 < myUserData.iStrLen)
	{
		g_SyncData.bStatStable = TRUE;
		return TTS_PLAYER_ERR_TOO_MORE_TEXT;
	}

	if (0 == myUserData.iStrLen)
	{
		g_SyncData.bStatStable = TRUE;
		return TTS_PLAYER_ERR_PARAM;
	}
	memcpy(myUserData.szTextIn, pcszText, myUserData.iStrLen);

	switch (ePlayMode)
	{
	case TTS_PLAYER_PLAY_SYNC:
		return MyJTTSPlay(lpfnCallback, dwUserData);
	case TTS_PLAYER_PLAY_ASYNC:
		EnterCriticalSection(&g_SyncData.CriticalSection);	
		g_SyncData.Command.uStatus = jtTTS_COMMAND_HANDLING;
		g_SyncData.Command.uType = jtTTS_CONTROL_PLAY;
		g_SyncData.Command.Play.lpfnCallback	= lpfnCallback;
		g_SyncData.Command.Play.dwUserData	= dwUserData;
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		
		SetEvent(g_SyncData.hEventChild);
		Sleep(0);
		return (ERRCODE)TTS_PLAYER_ERR_NONE;
	default:
		g_SyncData.bStatStable = TRUE;
	    return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	}
}

static ERRCODE MyJTTSInit(const char* szCNLib, const char* szENLib, const char* szDMLib);

/*������:	ejTTSPlayer_Init
* ˵��:		TTSPlayer�ĳ�ʼ��
* ����:		szCNLib [in] ��������·��
*			szENLib [in] Ӣ������·��
*			szDMLib [in] ��������·��
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_Init(const char* szCNLib, const char* szENLib, const char* szDMLib)
{
	ERRCODE errCode;

	// ��������̴߳��ڣ�˵���Ѿ���ʼ������
	if (g_hPlayHandle != NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_ALREADYINIT;
	}
	// ��ʱ����������жϿ��ܻ��������
	if (g_SyncData.eStatus != TTS_PLAYER_NOT_INIT)
	{
		return (ERRCODE)TTS_PLAYER_ERR_ALREADYINIT;
	}

	InitializeCriticalSection(&g_SyncData.CriticalSection);

	g_SyncData.hEventChild = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(g_SyncData.hEventChild == NULL)
	{
		DeleteCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_DONOTHING;
	}

	ResetEvent(g_SyncData.hEventChild);

	errCode = MyJTTSInit(szCNLib, szENLib, szDMLib);
	
	if (TTS_PLAYER_ERR_NONE != errCode)
	{
		CloseHandle(g_SyncData.hEventChild);
		g_SyncData.hEventChild = NULL;
		DeleteCriticalSection(&g_SyncData.CriticalSection);
		return errCode;
	}

	// ���������߳�
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyJTTSServiceThread, (LPVOID)NULL, 0, 0);
	if(hThread == NULL)
	{
		jtTTS_End(g_PlayData.hJTTS);
		free((void*)g_PlayData.pHeap);
		g_PlayData.pHeap = NULL;
		g_PlayData.hJTTS = NULL;

		CloseHandle(g_SyncData.hEventChild);
		g_SyncData.hEventChild = NULL;
		DeleteCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_DONOTHING;
	}
	
	g_hPlayHandle = hThread;

	EnterCriticalSection(&g_SyncData.CriticalSection);
	for(int i = 0; i < JTTS_PLAY_BUF_NUM; i++)
	{
		g_PlayData.BuffState[i] = JTTS_BUFF_FREE;
	}

	g_SyncData.eStatus = TTS_PLAYER_IDLE;
	g_SyncData.bStatStable = TRUE;
	g_SyncData.bStopCommand = FALSE;
	g_SyncData.Command.uType	= jtTTS_CONTROL_NONE;
	g_SyncData.Command.uStatus	= jtTTS_COMMAND_IDLE;
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	Sleep(0);

	return (ERRCODE)TTS_PLAYER_ERR_NONE;
	
}


/*������:	ejTTSPlayer_End
* ˵��:		TTSPlayer�����٣��ͷ���Դ
* ����:		��
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_End()
{
	ERRCODE errCode;

	if (g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	//��ֹͣTTS����
	ejTTSPlayer_Stop(TTS_PLAYER_STOP_BLOCK);
	// ������̷߳����˳�����
	EnterCriticalSection(&g_SyncData.CriticalSection);	
	g_SyncData.Command.uStatus = jtTTS_COMMAND_EXIT;
	g_SyncData.Command.uType = jtTTS_CONTROL_END;
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	SetEvent(g_SyncData.hEventChild);
	Sleep(0);

	// ��ʹ��INFINITE�ȴ�����ֹ�߳���������
	DWORD dwIndex = WAIT_ABANDONED;
	while (WAIT_ABANDONED == dwIndex)
	{
		Sleep(0);
		dwIndex = WaitForSingleObject(g_hPlayHandle, 1000);
	}


	if(g_PlayData.hJTTS != NULL)
	{
		errCode = jtTTS_End(g_PlayData.hJTTS);

		if (TTS_PLAYER_ERR_NONE != errCode)
		{
			return errCode;
		}

		free((void*)g_PlayData.pHeap);
		g_PlayData.pHeap = NULL;
		g_PlayData.hJTTS = NULL;
	}
	
	if(g_SyncData.hEventChild != NULL)
	{
		CloseHandle(g_SyncData.hEventChild);
		g_SyncData.hEventChild = NULL;
	}

	DeleteCriticalSection(&g_SyncData.CriticalSection);

	CloseHandle(g_hPlayHandle);
	g_hPlayHandle = NULL;
	g_SyncData.eStatus = TTS_PLAYER_NOT_INIT;

	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}


/*������:	ejTTSPlayer_Stop
* ˵��:		��ֹTTSPlayer�ĺϳ�/����
* ����:		eStopMode [in] ֹͣ��ģʽ
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_Stop(jtTTSStopMode eStopMode)
{
	ERRCODE nErr = TTS_PLAYER_ERR_NONE;

	if (g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	EnterCriticalSection(&g_SyncData.CriticalSection);
	if (g_SyncData.eStatus == TTS_PLAYER_IDLE && g_SyncData.bStatStable)
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_NONE;
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	if (TTS_PLAYER_STOP_ASYNC != eStopMode &&
		TTS_PLAYER_STOP_BLOCK != eStopMode)
	{
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	}

	EnterCriticalSection(&g_SyncData.CriticalSection);
	g_SyncData.bStopCommand = TRUE;
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	nErr = jtTTS_SynthStop(g_PlayData.hJTTS);

	Sleep(0);
	
	if (TTS_PLAYER_STOP_BLOCK == eStopMode)
	{
		while (g_SyncData.eStatus != TTS_PLAYER_IDLE ||
				g_SyncData.Command.uStatus == jtTTS_COMMAND_HANDLING ||
				!g_SyncData.bStatStable)
		{
			Sleep(0);
		}
	}

	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}


/*������:	ejTTSPlayer_Pause
* ˵��:		��ͣTTSPlayer�Ĳ���
* ����:		��
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_Pause()
{
	if (g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	// �Ѿ�����ֹͣ�����������ͣ��
	EnterCriticalSection(&g_SyncData.CriticalSection);
	if(g_SyncData.bStopCommand)
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_DONOTHING;
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	// ֻ���ڲ����е��ȶ�״̬������ͣ
	EnterCriticalSection(&g_SyncData.CriticalSection);
	if(g_SyncData.eStatus == TTS_PLAYER_PLAYING && g_SyncData.bStatStable)
	{
		g_SyncData.eStatus = TTS_PLAYER_PAUSE;
	}
	else
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_DONOTHING;
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	Sleep(0);
	
	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}


/*������:	ejTTSPlayer_Resume
* ˵��:		�ָ�TTSPlayer����ͣ
* ����:		��
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_Resume()
{
	if(g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	EnterCriticalSection(&g_SyncData.CriticalSection);
	if (g_SyncData.eStatus == TTS_PLAYER_PAUSE && g_SyncData.bStatStable)
	{
		g_SyncData.eStatus = TTS_PLAYER_PLAYING;
	}
	else
	{
		LeaveCriticalSection(&g_SyncData.CriticalSection);
		return (ERRCODE)TTS_PLAYER_ERR_DONOTHING;
	}
	LeaveCriticalSection(&g_SyncData.CriticalSection);

	Sleep(0);
	
	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}

/*������:	ejTTSPlayer_SetParam
* ˵��:		����TTS����Ĳ���
* ����:		nParam [in] ��������
*			dwValue [in] ����ֵ
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_SetParam(JTTSPARAM nParam, long lValue)
{
	ERRCODE dwerrCode;

	if (g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}	
	
	if(g_PlayData.hJTTS == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}


	
	if (jtTTS_PARAM_OUTPUT_SIZE == nParam || 
		jtTTS_PARAM_INPUTTXT_MODE == nParam ||
		jtTTS_PARAM_OUTPUT_CALLBACK == nParam ||
		jtTTS_PARAM_INPUT_CALLBACK == nParam ||
		jtTTS_PARAM_INPUTTXT_MODE == nParam ||
		jtTTS_PARAM_OUTPUT_CALLBACK == nParam ||
		jtTTS_PARAM_SLEEP_CALLBACK == nParam ||
		jtTTS_PARAM_PARAM_CALLBACK == nParam)
	{
		return jtTTS_ERR_INPUT_PARAM;
	}

	dwerrCode = jtTTS_SetParam(g_PlayData.hJTTS, nParam, lValue);

	return dwerrCode;
}

/*������:	ejTTSPlayer_GetParam
* ˵��:		��ȡTTS����Ĳ���
* ����:		nParam [in] ��������
*			pdwValue [out] ����ֵ
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_GetParam(JTTSPARAM nParam, long *plValue)
{
	if (g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	if(g_PlayData.hJTTS == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	return jtTTS_GetParam(g_PlayData.hJTTS, nParam, plValue);
}

/*������:	ejTTSPlayer_GetStatus
* ˵��:		��ȡTTS����Ĳ���
* ����:		piStatus [out] ״̬
* ����ֵ:	ERRCODE
*/
ERRCODE	TTSAPI ejTTSPlayer_GetStatus(int *piStatus)
{
	if (g_hPlayHandle == NULL)
	{
		*piStatus = TTS_PLAYER_NOT_INIT; 
		return (ERRCODE)TTS_PLAYER_ERR_NONE;
	}

	Sleep(0);

	if (TTS_PLAYER_IDLE == g_SyncData.eStatus && !g_SyncData.bStatStable)
	{
		*piStatus = TTS_PLAYER_SYNTHESIZING;
		return (ERRCODE)TTS_PLAYER_ERR_NONE;
	}

	*piStatus = g_SyncData.eStatus;

	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}


/*������:	ejTTSPlayer_PlayToFile
* ˵��:		�ϳ��������ݵ�WAV�ļ�
* ����:		pszText [in] ���ϳɵ��ı�
*			pszFileName [in] WAV�ļ�·��
* ����ֵ:	ERRCODE
*/
ERRCODE TTSAPI ejTTSPlayer_PlayToFile(char *pszText, const char* pszFileName)
{
	ERRCODE		dwErrCode;
	DWORD		dwTotalLen;
	long		lCodePage = -1;
	long		lTempParamCallBack = 0;
	long		lTempSylCallBack = 0;
	long		lTempProCallBack = 0;

	if (g_hPlayHandle == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}

	if (g_PlayData.hJTTS == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_NOTINIT;
	}	

	if (pszText == NULL)
	{
		return (ERRCODE)TTS_PLAYER_ERR_PARAM;
	}

	if (!g_SyncData.bStatStable)
	{
		// Error
		return (ERRCODE)TTS_PLAYER_ERR_PLAYING;
	}

	if (g_SyncData.eStatus != TTS_PLAYER_IDLE)
	{
		// Error
		return (ERRCODE)TTS_PLAYER_ERR_PLAYING;
	}

	memset(&myUserData, 0, sizeof(MyUserData));
	jtTTS_GetParam(g_PlayData.hJTTS, jtTTS_PARAM_CODEPAGE, &lCodePage);	
	if (jtTTS_CODEPAGE_UNICODE == lCodePage)
	{
		myUserData.iStrLen = wcslen((const wchar_t *)pszText) * sizeof(wchar_t);
	}
	else
	{
		myUserData.iStrLen = strlen(pszText) * sizeof(char);
	}
	
	if (TTS_PLAYER_MAX_TEXTLEN - 2 < myUserData.iStrLen)
	{
		return jtTTS_ERR_TOO_MORE_TEXT;
	}

	if (0 == myUserData.iStrLen)
	{
		return TTS_PLAYER_ERR_PARAM;
	}

	memcpy(myUserData.szTextIn, pszText, myUserData.iStrLen);

	static unsigned char lpData[JTTS_PLAY_BUF_SIZE];

	// WAV�ļ�ͷ��ʽ
	struct WAVEFILEHEADER
	{
		char chRIFF[4];
		DWORD dwRIFFLen;
		char chWAVE[4];
		char chFMT[4];
		DWORD dwFMTLen;
		PCMWAVEFORMAT pwf;
		char chDATA[4];
		DWORD dwDATALen;
	};

	// ��Ƶ�����豸������Ϣ
	UINT nSamplesPerSec = 16000;
	UINT nBitsPerSample = 16;
	GetAudioFormat(g_PlayData.hJTTS, &nSamplesPerSec, &nBitsPerSample);
	
	// ���ļ�
	FILE *fp = fopen(pszFileName, "wb");
	if (fp == NULL)
	{		
		return (ERRCODE)TTS_PLAYER_ERR_OPENFILE;
	}

	myUserData.fpOutputFile = fp;
	
	BOOL bWriteErr = FALSE;
	
	// WAV �ļ�д�ļ�ͷ, �ü򵥵ķ���д, ����mmioϵ�к���
	WAVEFILEHEADER wfh;
	
	memcpy(wfh.chRIFF,"RIFF", 4);
	memcpy(wfh.chWAVE,"WAVE", 4);
	memcpy(wfh.chFMT, "fmt ", 4);
	memcpy(wfh.chDATA,"data", 4);
	wfh.dwFMTLen = 0x10;	// sizeof(WAVEFORMAT) + sizeof(WORD)
	wfh.pwf.wf.wFormatTag = 1;	// WAVE_FORMAT_PCM
	wfh.pwf.wf.nChannels  = 1;	// mono
	wfh.pwf.wf.nSamplesPerSec = nSamplesPerSec;
	wfh.pwf.wf.nAvgBytesPerSec = nBitsPerSample * nSamplesPerSec / 8;
	wfh.pwf.wf.nBlockAlign = (WORD)(nBitsPerSample / 8);
	wfh.pwf.wBitsPerSample = (WORD)nBitsPerSample;
	if (fwrite(&wfh, 1, sizeof(WAVEFILEHEADER), fp) != sizeof(WAVEFILEHEADER))
	{
		bWriteErr = TRUE; 
	}

	// ����ʱȡ�����Իص�
	jtTTS_GetParam(g_PlayData.hJTTS, jtTTS_PARAM_SYLLABLE_CALLBACK, &lTempSylCallBack);
	jtTTS_GetParam(g_PlayData.hJTTS, jtTTS_PARAM_PROGRESS_CALLBACK, &lTempProCallBack);
	jtTTS_GetParam(g_PlayData.hJTTS, jtTTS_PARAM_PARAM_CALLBACK, &lTempParamCallBack);

	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_SYLLABLE_CALLBACK, NULL);
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_PROGRESS_CALLBACK, NULL);
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_PROGRESS_CALLBACK, NULL);

	/* ������Ƶ����ص� */
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_OUTPUT_CALLBACK, (long)OutputVoiceToFileProc);
	
	dwErrCode = jtTTS_SynthesizeText(g_PlayData.hJTTS, pszText, myUserData.iStrLen);

	// ���¼�����Իص�
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_SYLLABLE_CALLBACK, lTempSylCallBack);
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_PROGRESS_CALLBACK, lTempProCallBack);
	jtTTS_SetParam(g_PlayData.hJTTS, jtTTS_PARAM_PARAM_CALLBACK, lTempParamCallBack);

	fseek(fp, 0L, SEEK_END);	
	dwTotalLen = ftell(fp) - sizeof(WAVEFILEHEADER);
	if (bWriteErr == FALSE)
	{
		wfh.dwDATALen = dwTotalLen;
		wfh.dwRIFFLen = dwTotalLen + 36;
		fseek(fp, 0L, SEEK_SET);
		if (fwrite(&wfh, 1, sizeof(WAVEFILEHEADER), fp) != sizeof(WAVEFILEHEADER))
			bWriteErr = TRUE;
	}
	
	fclose(fp);
	if (bWriteErr == TRUE)
	{
		return (ERRCODE)TTS_PLAYER_ERR_OPENFILE;
	}
	
	return (ERRCODE)TTS_PLAYER_ERR_NONE;
}