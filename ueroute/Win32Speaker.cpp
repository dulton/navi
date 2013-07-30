/******************************************************************************
* File Name		       : Win32Speaker.c
* Description          : ������Դ�ļ�
* Author               : pingbu
* Date Of Creation     : 2005-09-11
* Platform             : Win32
* Modification History : 
*------------------------------------------------------------------------------
* Date        Author     Modifications
*------------------------------------------------------------------------------
* 2005-09-11  pingbu     Created
******************************************************************************/

#include <windows.h>
#include <mmsystem.h>
#include "Win32Speaker.h"


#ifdef _WIN32_WCE
	#define _ASSERT(exp) (void)0
	#define _THROW(e) (void)0
	#pragma comment(lib, "coredll.lib")
#else
	#include <crtdbg.h>
	#define _THROW(e) throw e
	#pragma comment(lib, "winmm.lib")
#endif


//////////////////////////////////////////////////////////////////////////
// �ص�����
void CALLBACK CWin32Speaker::waveOutProc( HWAVEOUT hwo, UINT uMsg,
			CWin32Speaker* pThis, LPWAVEHDR lpwvhdr, DWORD dwParam2 )
{
	_ASSERT(pThis);

	if ( WOM_DONE == uMsg )
	{
		_ASSERT(lpwvhdr);

		::EnterCriticalSection(&pThis->m_tWork);

		if ( lpwvhdr->dwUser )
			::ReleaseSemaphore(pThis->m_hEmpty, 1, NULL);

		if ( pThis->m_bPlaying )
		{
			MMRESULT mr = ::waveOutUnprepareHeader(hwo, lpwvhdr, sizeof(WAVEHDR));
			_ASSERT(MMSYSERR_NOERROR == mr);

			if ( WAIT_OBJECT_0 == ::WaitForSingleObject(pThis->m_hFull, 0) )
			{
				lpwvhdr->lpData = pThis->m_pBuffer[pThis->m_iRead];
				lpwvhdr->dwBufferLength = pThis->m_nSize[pThis->m_iRead];
				lpwvhdr->dwUser = 1;

				++ pThis->m_iRead;
				pThis->m_iRead %= WAVE_COUNT + WAVE_EXT;
			}
			else
			{
				lpwvhdr->lpData = pThis->m_pBuffer[WAVE_COUNT + WAVE_EXT];
				lpwvhdr->dwBufferLength = pThis->m_nMaxSize;
				lpwvhdr->dwUser = 0;
			}

			lpwvhdr->dwFlags = 0;
			mr = ::waveOutPrepareHeader(hwo, lpwvhdr, sizeof(WAVEHDR));
			_ASSERT(MMSYSERR_NOERROR == mr);

			mr = ::waveOutWrite(hwo, lpwvhdr, sizeof(WAVEHDR));
			_ASSERT(MMSYSERR_NOERROR == mr);
		}

		::LeaveCriticalSection(&pThis->m_tWork);
	}
}

//////////////////////////////////////////////////////////////////////////
// ��ʼ����
void CWin32Speaker::__Start()
{
	::EnterCriticalSection(&m_tWork);

	for ( int i = 0; i < 2; ++ i )
	{
		m_tWaveHeader[i].lpData = (LPSTR)m_pBuffer[WAVE_COUNT + WAVE_EXT];
		m_tWaveHeader[i].dwBufferLength = m_nMaxSize;
		m_tWaveHeader[i].dwFlags = 0;
		m_tWaveHeader[i].dwUser = 0;

		MMRESULT mr = ::waveOutPrepareHeader(m_hWaveOut,
					m_tWaveHeader + i, sizeof(WAVEHDR));
		_ASSERT(MMSYSERR_NOERROR == mr);

		mr = ::waveOutWrite(m_hWaveOut, m_tWaveHeader + i, sizeof(WAVEHDR));
		_ASSERT(MMSYSERR_NOERROR == mr);
	}

	m_bPlaying = m_bCaching = TRUE;
	m_bPausing = FALSE;
	m_iRead = m_iWrite = 2 % (WAVE_COUNT + WAVE_EXT);
	m_nWrite = 0;

	::LeaveCriticalSection(&m_tWork);
}

//////////////////////////////////////////////////////////////////////////
// ֹͣ����
void CWin32Speaker::__Stop()
{
	Flush();

	::EnterCriticalSection(&m_tWork);
	m_bPlaying = FALSE;
	::LeaveCriticalSection(&m_tWork);

	MMRESULT mr = ::waveOutReset(m_hWaveOut);
	_ASSERT(MMSYSERR_NOERROR == mr);

	while ( WAIT_OBJECT_0 == ::WaitForSingleObject(m_hFull, 0) )
		::ReleaseSemaphore(m_hEmpty, 1, NULL);

	for ( int i = 0; i < 2; ++ i )
	{
		mr = ::waveOutUnprepareHeader(m_hWaveOut, m_tWaveHeader + i, sizeof(WAVEHDR));
		_ASSERT(MMSYSERR_NOERROR == mr);
	}
}

//////////////////////////////////////////////////////////////////////////
// �򿪲����豸
void CWin32Speaker::__Open( PWAVEFORMATEX wfx )
{
	if ( NULL == wfx )
	{
		m_pWaveFormat = NULL;
		m_nWrite = 0;
		for ( int i = 0; i <= WAVE_COUNT + WAVE_EXT; ++ i )
		{
			m_pBuffer[i] = NULL;
		}
	}
	else
	{
		// ����Wave��ʽ
		DWORD dwSize = sizeof(WAVEFORMATEX);
		if ( wfx->wFormatTag != WAVE_FORMAT_PCM )
			dwSize += wfx->cbSize;

		// Given current memory is limitied
		if(m_formatSize < dwSize)
		{
			m_formatSize = dwSize;
			if(m_pWaveFormat)
			{
				delete []m_pWaveFormat;
				m_pWaveFormat = NULL;
			}
			m_pWaveFormat = (LPWAVEFORMATEX)new char[dwSize];
		}
		::ZeroMemory(m_pWaveFormat, m_formatSize);
		::CopyMemory(m_pWaveFormat, wfx, dwSize);

		// ���仺����
		m_nMaxSize = (wfx->nAvgBytesPerSec / 2) / wfx->nBlockAlign * wfx->nBlockAlign;
		if(m_dataSize < m_nMaxSize)
		{
			m_dataSize = m_nMaxSize;
			if(m_pBuffer[0])
			{
				for ( int i = 0; i <= WAVE_COUNT + WAVE_EXT; ++ i )
				{
					delete []m_pBuffer[i];
					m_pBuffer[i] = NULL;
				}
			}

			for ( int i = 0; i <= WAVE_COUNT + WAVE_EXT; ++ i )
				m_pBuffer[i] = new CHAR[m_nMaxSize];
		}
		::ZeroMemory(m_pBuffer[WAVE_COUNT + WAVE_EXT], m_nMaxSize);

		// �򿪲����豸
		MMRESULT mr = ::waveOutOpen(&m_hWaveOut, WAVE_MAPPER, m_pWaveFormat,
						(DWORD)waveOutProc, (DWORD)this, CALLBACK_FUNCTION);
		_ASSERT(MMSYSERR_NOERROR == mr);

		// ��������
		//mr = ::waveOutSetVolume(m_hWaveOut, 0xFFFFFFFF);
		//_ASSERT(MMSYSERR_NOERROR == mr);

		// ��ʼ����
		__Start();
	}
}

//////////////////////////////////////////////////////////////////////////
// �رղ����豸
void CWin32Speaker::__Close(bool isRelease)
{
	if ( m_pWaveFormat )
	{
		// ֹͣ����
		__Stop();

		// �رղ����豸
		MMRESULT mr = ::waveOutClose(m_hWaveOut);
		_ASSERT(MMSYSERR_NOERROR == mr);

		if(isRelease)
		{
			// �ͷŻ�����
			for ( int i = 0; i <= WAVE_COUNT + WAVE_EXT; ++ i )
			{
				delete[] m_pBuffer[i];
				m_pBuffer[i] = NULL;
			}

			// �ͷ�Wave��ʽ
			delete[] (LPBYTE)m_pWaveFormat;
			m_pWaveFormat = NULL;
		}
		m_pWaveFormat = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
// ����
CWin32Speaker::CWin32Speaker() : m_formatSize(0), m_dataSize(0)
{
	::InitializeCriticalSection(&m_tWork);

	m_hFull = ::CreateSemaphore(NULL, 0, WAVE_COUNT + WAVE_EXT, NULL);
	m_hEmpty = ::CreateSemaphore(NULL, WAVE_COUNT, WAVE_COUNT + WAVE_EXT, NULL);

	m_hCacheFull = ::CreateSemaphore(NULL, 0, WAVE_EXT, NULL);
	m_hCacheEmpty = ::CreateSemaphore(NULL, WAVE_EXT, WAVE_EXT, NULL);

	__Open(NULL);
}

//////////////////////////////////////////////////////////////////////////
// �ͷ�
CWin32Speaker::~CWin32Speaker()
{
	__Close(true);

	::CloseHandle(m_hCacheEmpty);
	::CloseHandle(m_hCacheFull);

	::CloseHandle(m_hEmpty);
	::CloseHandle(m_hFull);

	::DeleteCriticalSection(&m_tWork);
}

//////////////////////////////////////////////////////////////////////////
// ���ø�ʽ
void CWin32Speaker::SetWaveFormat( LPWAVEFORMATEX wfx )
{
	Wait();
	__Close();
	__Open(wfx);
}

//////////////////////////////////////////////////////////////////////////
// ׷������
void CWin32Speaker::Append( LPCVOID lpData, DWORD dwSize )
{
	_ASSERT(m_pWaveFormat);
	if ( NULL == m_pWaveFormat )
		return;

	_ASSERT(0 == (dwSize % m_pWaveFormat->nBlockAlign));
	if ( dwSize % m_pWaveFormat->nBlockAlign )
		return;

	while ( dwSize )
	{
		if ( 0 == m_nWrite )
		{
			if ( m_bCaching && WAIT_TIMEOUT == ::WaitForSingleObject(m_hCacheEmpty, 0) )
			{
				//////////////////////////////////////////////////////////////////////////
				// �Ӵ�...
				m_bCaching = FALSE;
			}

			if ( !m_bCaching )
				::WaitForSingleObject(m_hEmpty, INFINITE);
		}

		int n = min(dwSize, (DWORD)m_nMaxSize - m_nWrite);
		::CopyMemory(m_pBuffer[m_iWrite] + m_nWrite, lpData, n);
		m_nWrite += n;
		lpData = (char*)lpData + n;
		dwSize -= n;

		if ( m_nMaxSize == m_nWrite )
			Flush();
	}
}

//////////////////////////////////////////////////////////////////////////
// ��������
void CWin32Speaker::Flush()
{
	if ( m_nWrite )
	{
		m_nSize[m_iWrite] = m_nWrite;
		m_nWrite = 0;

		++ m_iWrite;
		m_iWrite %= WAVE_COUNT + WAVE_EXT;

		::ReleaseSemaphore(m_bCaching ? m_hCacheFull : m_hFull, 1, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// ��ͣ
void CWin32Speaker::Pause()
{
	if ( NULL == m_pWaveFormat )
		return;

	MMRESULT mr = ::waveOutPause(m_hWaveOut);
	_ASSERT(MMSYSERR_NOERROR == mr);

	m_bPausing = TRUE;
}

//////////////////////////////////////////////////////////////////////////
// �ָ�
void CWin32Speaker::Resume()
{
	if ( NULL == m_pWaveFormat )
		return;

	if ( m_bPausing )
	{
		MMRESULT mr = ::waveOutRestart(m_hWaveOut);
		_ASSERT(MMSYSERR_NOERROR == mr);

		m_bPausing = FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
// �ȴ�
BOOL CWin32Speaker::Wait( DWORD dwMsTimeout )
{
	if ( NULL == m_pWaveFormat )
		return TRUE;

	_ASSERT(!m_bPausing);

	// ��δ����������ӵ����Ŷ���
	Flush();

	// ��������Cache
	m_bCaching = TRUE;

	// ��Cache��ӵ����Ŷ���
	while ( WAIT_OBJECT_0 == ::WaitForSingleObject(m_hCacheEmpty, 0) )
		::ReleaseSemaphore(m_hEmpty, 1, NULL);

	while ( WAIT_OBJECT_0 == ::WaitForSingleObject(m_hCacheFull, 0) )
		::ReleaseSemaphore(m_hFull, 1, NULL);

	// �Ѽ����л�����
	if ( INFINITE == dwMsTimeout )
	{
		for ( int i = 0; i < WAVE_COUNT + WAVE_EXT; ++ i )
			::WaitForSingleObject(m_hEmpty, INFINITE);
	}
	else
	{
		dwMsTimeout += ::GetTickCount();

		for ( int i = 0; i < WAVE_COUNT + WAVE_EXT; ++ i )
		{
			DWORD t = ::GetTickCount();

			if ( t > dwMsTimeout )
				t = 0;
			else
				t = dwMsTimeout - t;

			if ( WAIT_OBJECT_0 != ::WaitForSingleObject(m_hEmpty, t) )
			{
				// �ͷ����Ѽ��Ŀ��л�����
				if ( i )
				{
					if ( i > WAVE_EXT )
					{
						::ReleaseSemaphore(m_hCacheEmpty, WAVE_EXT, NULL);
						::ReleaseSemaphore(m_hEmpty, i - WAVE_EXT, NULL);
					}
					else
					{
						::ReleaseSemaphore(m_hCacheEmpty, i, NULL);
					}
				}

				return FALSE;
			}
		}
	}

	// �ͷſ��л�����
	::ReleaseSemaphore(m_hCacheEmpty, WAVE_EXT, NULL);
	::ReleaseSemaphore(m_hEmpty, WAVE_COUNT, NULL);

	// ���¿�ʼ
	__Stop();
	__Start();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// ��λ
void CWin32Speaker::Reset()
{
	_ASSERT(m_pWaveFormat);
	if ( NULL == m_pWaveFormat )
		return;

	if ( !m_bPausing )
	{
		// ��δ����������ӵ����Ŷ���
		Flush();

		// ��������Cache
		m_bCaching = TRUE;

		::EnterCriticalSection(&m_tWork);

		// ��Cache��ӵ����Ŷ���
		while ( WAIT_OBJECT_0 == ::WaitForSingleObject(m_hCacheEmpty, 0) )
			::ReleaseSemaphore(m_hEmpty, 1, NULL);

		// ��ղ��Ŷ���
		m_iWrite += WAVE_COUNT + WAVE_EXT;

		while ( WAIT_OBJECT_0 == ::WaitForSingleObject(m_hFull, 0) )
		{
			-- m_iWrite;
			::ReleaseSemaphore(m_hEmpty, 1, NULL);
		}

		m_iWrite %= WAVE_COUNT + WAVE_EXT;

		// ͳ��Cache�Ļ�����������������
		int nBufferCount = 0, nTotalSize = 0;

		while ( WAIT_OBJECT_0 == ::WaitForSingleObject(m_hCacheFull, 0) )
		{
			m_iWrite += WAVE_COUNT + WAVE_EXT;
			-- m_iWrite;
			m_iWrite %= WAVE_COUNT + WAVE_EXT;

			nTotalSize += m_nSize[m_iWrite];
			++ nBufferCount;
		}

		// �����Ǵ�
		if ( WAVE_FORMAT_PCM == m_pWaveFormat->wFormatTag )
		{
			if ( 8 == m_pWaveFormat->wBitsPerSample )
			{
				int k = nTotalSize ++;

				for ( int i = 0; i < nBufferCount; ++ i )
				{
					LPBYTE p = (LPBYTE)m_pBuffer[m_iWrite];
					int n = m_nSize[m_iWrite];

					for ( int j = 0; j < n; ++ j )
					{
						DWORD t = p[j];
						t *= k;
						t /= nTotalSize;
						p[j] = (BYTE)t;
						-- k;
					}

					++ m_iWrite;
					m_iWrite %= WAVE_COUNT + WAVE_EXT;
				}
			}
			else if ( 16 == m_pWaveFormat->wBitsPerSample )
			{
				nTotalSize /= sizeof(SHORT);

				int k = nTotalSize ++;

				for ( int i = 0; i < nBufferCount; ++ i )
				{
					PSHORT p = (PSHORT)m_pBuffer[m_iWrite];
					int n = m_nSize[m_iWrite] / sizeof(SHORT);

					for ( int j = 0; j < n; ++ j )
					{
						LONG t = p[j];
						t *= k;
						t /= nTotalSize;
						p[j] = (SHORT)t;
						-- k;
					}

					++ m_iWrite;
					m_iWrite %= WAVE_COUNT + WAVE_EXT;
				}
			}
		}

		::LeaveCriticalSection(&m_tWork);

		// ��Cache������׷�ӵ����Ŷ���
		::ReleaseSemaphore(m_hFull, nBufferCount, NULL);

		// �Ѽ����л�����
		for ( int i = 0; i < WAVE_COUNT + WAVE_EXT; ++ i )
			::WaitForSingleObject(m_hEmpty, INFINITE);

		// �ͷſ��л�����
		::ReleaseSemaphore(m_hCacheEmpty, WAVE_EXT, NULL);
		::ReleaseSemaphore(m_hEmpty, WAVE_COUNT, NULL);
	}

	// ���¿�ʼ
	__Stop();
	__Start();
}
