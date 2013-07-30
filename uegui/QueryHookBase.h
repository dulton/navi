#ifndef _UEGUI_QUERYBASEHOOK_H
#define _UEGUI_QUERYBASEHOOK_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif
#ifndef _UEQUERY_QUERYDEF_H
#include "uequery/querybasic.h"
#endif
#ifndef _UEBASE_TRACER_H
#include "uebase/dbgmacro.h"
#endif
// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z
//////////////////////////////////////////////////////////////////////////
namespace UeGui
{
	typedef void Query_CallBack(void *pDoCallBackObj,const SQLRecord *pResult);
	//
	class CQueryHookBase:public CAggHook
	{
		friend class CRoundQueryListHook;
	public:
		//�ͷ���һ�εļ�����Ϣ
		static void DestroyQueryModule(void)
		{
			if (g_vecQueryObj.size())
			{
				for (int i(0); i<g_vecQueryObj.size(); ++i)
				{
					g_vecQueryObj[i]->Destroy();
				}
			}
		}
		CQueryHookBase(void):m_pDoCallBackObj(0),m_pCallBackEvent(0),
			m_uPrevHookType(CViewHook::DHT_MapHook)
		{
			g_vecQueryObj.push_back(this);
		};
		virtual ~CQueryHookBase(void) {};

		//��ʼ�����桢��ť����갴�µ���ʱ��Ч��
		virtual void MakeGUI(void)
		{
			initCtrlNames();
			FetchWithBinary();
			initHookCtrl();
		}
		virtual bool operator ()(void) {return false;};
		//
		virtual short MouseUp(CGeoPoint<short> &scrPoint)
		{
			return doMouseUp(CAggHook::MouseUp(scrPoint));
		}
		virtual short MouseDown(CGeoPoint<short> &scrPoint)
		{
			return doMouseDown(CAggHook::MouseDown(scrPoint));
		}
		virtual void DynamicShow(void)
		{
			if (CViewHook::DHT_MapHook!=CViewHook::m_prevHookType)
			{
				m_uPrevHookType = CViewHook::m_prevHookType;
			}
			//if (CViewHook::DHT_MapHook!=CAggHook::GetPrevHookType())
			//{
			//	m_uPrevHookType = CAggHook::GetPrevHookType();
			//}
			CAggHook::DynamicShow();
			//Refresh();
		}
		unsigned getPerHookType(void) const {return m_uPrevHookType;};
    static UeQuery::CUeRecord *DoQueryGetRecord(bool bShowDialog);
	protected:
		//��ʼ���ؼ�����
		virtual void initCtrlNames(void) = 0;
		//���ؼ�����Ӧ�Ŀ��ƶ����������
		virtual void initHookCtrl(void) = 0;
		//
		virtual short doMouseUp(short ctrlType) = 0;
		virtual short doMouseDown(short ctrlType) = 0;
		//
		//virtual void Refresh(void);
		virtual void Destroy(void) {};
		virtual void doGotoNagiv(void);
		virtual void doLogicBack(void)
		{
			CViewHook::m_curHookType = m_uPrevHookType;
			((CAggHook*)m_view->GetHook(CViewHook::m_curHookType))->Load();
		}
		//
		void *m_pDoCallBackObj;
		Query_CallBack *m_pCallBackEvent;
		//
		unsigned m_uPrevHookType;
		//static SQLSentence g_querySql;
		static std::vector<CQueryHookBase *> g_vecQueryObj;
	private:
		//Ӧ��Ӧ���߳�ʱ��ˢ��
		static bool g_bIsRefreshing;
		static bool g_bHasRefreshRequst;
	};
}
#endif