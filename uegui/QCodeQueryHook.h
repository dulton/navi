/*
*�������ڡ���Q�롱�� 
*�û������Q��洢�� private char m_qcode[9]�У�
*�ⲿͨ������public char* getQCode()���m_qcode[9]
*/

#ifndef _UEGUI_QCODEQUERYHOOK_H
#define _UEGUI_QCODEQUERYHOOK_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEGUI_BACKGROUNDHOOK_H
#include "backgroundHook.h"
#endif
#ifndef _UEGUI_LABEL_H
#include "uilabel.h"
#endif
#ifndef _UEGUI_BITBUTTON_H
#include "uibutton.h"
#endif
// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z

//////////////////////////////////////////////////////////////////////////
//


namespace UeGui
{
	class  UEGUI_CLASS CQCodeQueryHook:public CBackgroundHook
	{
	public:
		//�ⲿͨ�����ô˾�̬������ø�ҳ���Ӧ��HookType
		static unsigned GetHookType(void)
		{
			return CViewHook::DHT_QCodeQueryHook;
		}
		//����������ʱͨ�����øþ�̬������ת����ҳ��
		static bool gotoQCodeQueryHook(unsigned uPreHookType,
			void *pDoCallBackObj=0,Query_CallBack *pCallBackEvent=0);
		//�û�����Q����ⲿͨ���ú�����ȡ
		unsigned short* getQCode(){ return m_qcode; }
    //����Q����жϺ������磺ne5-6fe-db9����ЧQ�롣
    //bool Qcmp(unsigned short Cqcod[9]);
		/////////////////////////////////////////////////////////////
		//
		CQCodeQueryHook(void):LengthQCode(0)
		{
			m_strBGMenuText = "��Q��";	//����ҳ�����
			m_vecHookFile.push_back(_T("QCodeQueryHook.bin"));	//������ͽ����ļ�
		}
		~CQCodeQueryHook(void){
			m_elements.clear();
			m_ctrlNames.clear();
			m_imageNames.clear();
		};
		//��ʼ���ؼ�����
		void initCtrlNames(void);
		//���ؼ�����Ӧ�Ŀ��ƶ����������
		void initHookCtrl(void);
		//�¼���Ӧ����
		virtual short doMouseUp(short ctrlType);
		virtual short doMouseDown(short ctrlType);
	private:
		//Q�볤��
		int LengthQCode;
		//Q��
		unsigned short m_qcode[9];
		//char m_chQCode[9];
		//Q���Ӧ�ľ�γ��
		CGeoPoint<long> m_curPos;
		//��γ�ȶ�Ӧ�ĵ�ͼ������Ļ����
		CGeoPoint<short> m_MapPoint;

		short hisPosX[5];
		////////////////////////////////////////////////////
		//
		//�ؼ�����
		//
		//ȷ����ȡ����ť
		CUiBitButton m_BtnOK;
		CUiBitButton m_BtnDelete;
		//�ӡ�0����9 a����z����36�����̰���
		static const int KeyNum=36;			//������
		CUiLabel m_pBtnsKeyBoard[KeyNum];	//�洢����������ע�⣺[0]��Ӧ��ctrlType-PT_BtnKey0
		//������ʾQ���3���ı�����
		GuiElement *m_pTextQCodeBox[3];
		//��ʾ��ǩ
		CUiButton m_textLine;
		//���
		CUiButton m_cursor1Ctrl;
		CUiButton m_cursor2Ctrl;

		//���һ���ַ����ı���
		void DoAddOneWord(const char *pChForAdd);
		//���ı���ɾ��һ���ַ�
		void DoDelOneWord(void);
		short XJmpOfCursor(GuiElement *pDstTextbox);
		//
		void resetCursorPos(short xPos)
		{
			m_cursor1Ctrl.GetCenterElement()->m_startX = xPos;
			m_cursor2Ctrl.GetCenterElement()->m_startX = xPos;
		}
	protected:
		//���Q��
		void clearQCode();
		//���ܣ���ָ���ؼ����һ���ַ�
		//������pDstTextboxΪ�ı���ؼ��� oneWordΪҪ��ӵ��ַ��� sCusPosXΪԭ���λ��
		//���أ���ӳɹ�����true,���򷵻�false
		bool AddOneWord(GuiElement *pDstTextbox,TCHAR oneWord);
		//���ܣ���ָ���ؼ�ɾ��һ���ַ�
		//������pDstTextboxΪ�ı���ؼ� sCusPosXΪԭ���λ��
		//���أ�ɾ���ɹ�����true,���򷵻�false
		bool DelOneWord(GuiElement *pDstTextBox,short sCurPosX);
		void ConvertQCodeToMap(void);



		enum ListKeyBoradType
		{
			PT_ListKeyBoradBegin=BT_BackCtrlEnd,	//=4
			PT_BtnKey0,	//=5
			PT_BtnKey1,
			PT_BtnKey2,
			PT_BtnKey3,
			PT_BtnKey4,
			PT_BtnKey5,
			PT_BtnKey6,
			PT_BtnKey7,
			PT_BtnKey8,
			PT_BtnKey9,

			PT_BtnKeyA,
			PT_BtnKeyB,
			PT_BtnKeyC,
			PT_BtnKeyD,
			PT_BtnKeyE,
			PT_BtnKeyF,
			PT_BtnKeyG,
			PT_BtnKeyH,
			PT_BtnKeyI,
			PT_BtnKeyJ,
			PT_BtnKeyK,
			PT_BtnKeyL,
			PT_BtnKeyM,
			PT_BtnKeyN,
			PT_BtnKeyO,
			PT_BtnKeyP,
			PT_BtnKeyQ,
			PT_BtnKeyR,
			PT_BtnKeyS,
			PT_BtnKeyT,
			PT_BtnKeyU,
			PT_BtnKeyV,
			PT_BtnKeyW,
			PT_BtnKeyX,
			PT_BtnKeyY,
			PT_BtnKeyZ,

			PT_TextQCode1,
			PT_TextQCode2,
			PT_TextQCode3,

			PT_BtnOkLeft,
			PT_BtnOkCenter,
			PT_BtnOkRight,
			PT_BtnDelLeft,
			PT_BtnDelCenter,
			PT_BtnDelRight,

			PT_TEXTLINE,

			PT_cursor1,
			PT_cursor2,

			PT_ListKeyBoradEnd
		};
	};
};
#endif
