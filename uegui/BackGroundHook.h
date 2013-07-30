#ifndef _UEGUI_BACKGROUNDHOOK_H
#define _UEGUI_BACKGROUNDHOOK_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEGUI_QUERYBASEHOOK_H
#include "QueryHookBase.h"
#endif
#ifndef _UEGUI_LABEL_H
#include "uilabel.h"
#endif
// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z
//////////////////////////////////////////////////////////////////////////
namespace UeGui
{
	//ӵ�б����Ľ���Ļ��࣬�̳���֮�����е�
	//���඼��ӵ����ͬ�ı�����������Ӧ���ü̳�
	//��ϵ����Ӧ����Ϲ�ϵ�������ڵļܹ���ʱ����
	class CBackgroundHook:public CQueryHookBase
	{
	public:
		CBackgroundHook(void):m_uCurHookFileIdx(0)
		{
			m_vecHookFile.push_back(_T("backgroundhook.bin"));
		};
		virtual ~CBackgroundHook(void) {};

		void setBGMenuText(const char *pchBGMenuText)
		{
			m_strBGMenuText = pchBGMenuText;
			//
			::strcpy(GetGuiElement(BT_BGMenuText)->m_label,m_strBGMenuText.c_str());
		}
		const string &getBGMenuText(void) const {return m_strBGMenuText;};
	protected:
		enum BackCtrlType
		{
			BT_GotoMap=1,
			BT_LogicBack,
			BT_BGMenuText,

			BT_BackCtrlEnd
		};
		//��ʼ���ؼ�����
		virtual void initCtrlNames(void);
		//xml�ж�ȡ����������Ϣ
		virtual void FetchWithBinary(void);
		//���ؼ�����Ӧ�Ŀ��ƶ����������
		virtual void initHookCtrl(void);
		//
		virtual short doMouseUp(short ctrlType);
		virtual short doMouseDown(short ctrlType);

		string m_strBGMenuText;
		std::vector<tstring> m_vecHookFile;
	private:
		/*
		* ��ȡ�������ļ����ƣ�������·������:licensehook.bin
		* �÷��������ฺ��ʵ�֣��������, �ұ���ʵ�֣���Ҫ��Ϊ��ͳһ��ȡ�������ļ�����
		*/
		virtual tstring GetBinaryFileName(void)
		{
			return m_vecHookFile[m_uCurHookFileIdx];
		};
		//��ťЧ����ʾ�ؼ�
		CUiLabel m_gotoMapBtn;
		CUiLabel m_logicBackBtn;
		//
		unsigned m_uCurHookFileIdx;
		
	};
}
#endif