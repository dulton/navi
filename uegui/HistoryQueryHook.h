/*
*	����
*	��ҳ�ؼ�
*	��ǩ����ʷ��¼����ʷ�켣����ʷ·�ߣ�
*	ҳ����Ϣ ��n/s��
*	ҳ�����ݣ�5����ť�б�
*/

#ifndef _UEGUI_HISTORYQUERYHOOK_H
#define _UEGUI_HISTORYQUERYHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif
#ifndef _UEGUI_BACKGROUNDHOOK_H
#include "backgroundHook.h"
#endif
#ifndef _UEGUI_PAGETURNING_H
#include "uipageturningctrl.h"
#endif
#ifndef _UEGUI_BITBUTTON_H
#include "uibutton.h"
#endif
#ifndef _UEGUI_DIALOGEHOOK_H
#include "messagedialoghook.h"
#endif
#ifndef _UEROUTE_ROUTEBASIC_H
#include "ueroute\routebasic.h"
#endif

namespace UeGui
{
	class UEGUI_CLASS CHistoryQueryHook : public CBackgroundHook//CAggHook
	{
	private:
		enum PageTag
		{
			kPageNone = 0,
			kPageHisRecord,     //��ʷ��¼  
			kPageHisTrajectory, //��ʷ�켣
			kPageHisRoute,      //��ʷ·��
			kPageEnd
		};
		enum TabStatus
		{
			kTabNormal, //����״̬
			kTabFocus   //���ڽ���״̬
		};
		enum RowTag
		{
			kRow0=0,
			kROW1,
			kROW2,
			kROW3,
			kROW4,
			kROWEnd
		};

	public:
		CHistoryQueryHook();
		virtual ~CHistoryQueryHook();
		virtual short MouseDown(CGeoPoint<short> &scrPoint);
		virtual short MouseMove(CGeoPoint<short> &scrPoint);
		virtual short MouseUp(CGeoPoint<short> &scrPoint);
		virtual bool operator ()();

		static bool gotoHistoryQueryHook(unsigned uPreHookType=-1,
			void *pDoCallBackObj=0,Query_CallBack *pCallBackEvent=0);

		static unsigned GetHookType(void){
			return CViewHook::DHT_HistoryQueryHook;
		}

	protected:
		//	virtual tstring GetBinaryFileName();
		void initCtrlNames();
		void initHookCtrl();

	private:
		//��ҳ������
		CPageTurning m_pageTurning;
		//��¼�������Ŀ���ļ��ж�Ӧ������
		int m_Itemidx;	

		//��ǰ�ҳ
		PageTag m_avtivePageIndex;
		//��¼��ǰѡ����к�
		RowTag m_selectRow;

		//����ҳ��
		void ActivatePage(PageTag page);
		//����Tab״̬
		void SetTabStatus(PageTag page, TabStatus status);
		//��������ʾ��ĳ����
		void DoShowRowData(RowTag row, const char* value);
		//����ҳ����ʾ����
		void ShowHistoryData(PageTag page);
		//���ĳһ�У�row=[0.4]
		void ClearARow(RowTag row);
		//���������
		void ClearAllRows();
		//���ݷ�ҳ������÷�ҳ��ť״̬
		void SetNavigatorStatus();
		//ѡ����ĳ��
		void selectARow();

		static void OnSelectHistoryRoute( CAggHook* sender, ModalResultType modalResult );
		void SelectHistoryRoute();
		//����·���滮
		void PlanHistoryRoute();

		void setRoutePageInfo(void);		//���� ��ʷ·�� ҳ��Ϣ
		void setRecortPageInfo(void);		//���� ��ʷ��¼ ҳ��Ϣ
		void setTrajectoryPageInfo(void);	//���� ��ʷ�켣 ҳ��Ϣ
		void showHistoryRecordData(void);		//��ȡ����ʾ ��ʷ��¼ ����
		void showHistoryTrajectoryData(void);	//��ȡ����ʾ ��ʷ�켣 ����
		void ShowHistoryRouteData(void);		//��ȡ����ʾ ��ʷ·�� ����
		// 
		// 		int m_iCurResultIndex;
		// 		int m_iTotalPageCount;

		//Tab�ؼ�
		CUiButton m_historyRecordCtrl;	//��ʷ��¼
		CUiButton m_historyRouteCtrl;	//��ʷ·��
		CUiButton m_historyTrajectoryCtrl;	//��ʷ�켣
		//�б�ؼ�����ʾ��¼/·��/�켣��Ϣ������
		const static int nQuantityOfOnePage=5;
		CUiButton m_listBtnCtrl[nQuantityOfOnePage];	
		//��ҳ
		CUiBitButton m_nextPageCtrl;
		CUiBitButton m_prevPageCtrl;
		//ҳ����Ϣ 0/0
		CUiButton m_pageInfoCtrl;

	public:
		enum ChkHistoryHookCtrlType
		{
			ChkHistoryHook_Begin =BT_BackCtrlEnd,	//=4
			ChkHistoryHook_PageInfo,
			ChkHistoryHook_HistoryRecord,
			ChkHistoryHook_HistoryTrajectory,
			ChkHistoryHook_HistoryRoute,
			ChkHistoryHook_List1LeftBtn,
			ChkHistoryHook_List1CenterBtn,
			ChkHistoryHook_List1RightBtn,
			ChkHistoryHook_List2LeftBtn,
			ChkHistoryHook_List2CenterBtn,
			ChkHistoryHook_List2RightBtn,
			ChkHistoryHook_List3LeftBtn,
			ChkHistoryHook_List3CenterBtn,
			ChkHistoryHook_List3RightBtn,
			ChkHistoryHook_List4LeftBtn,
			ChkHistoryHook_List4CenterBtn,
			ChkHistoryHook_List4RightBtn,
			ChkHistoryHook_List5LeftBtn,
			ChkHistoryHook_List5CenterBtn,
			ChkHistoryHook_List5RightBtn,
			ChkHistoryHook_PageUpBtn,
			ChkHistoryHook_PageUpIcon,
			ChkHistoryHook_PageDownBtn,
			ChkHistoryHook_PageDownIcon,
			ChkHistoryHook_End
		};

	};
}
#endif



