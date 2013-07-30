#ifndef _UEGUI_HISTORYQUERYHOOK_H
#include "HistoryQueryHook.h"
#endif

#ifndef _UEBASE_TIMEBASIC_H
#include "uebase\timebasic.h"
#endif
#ifndef _UEGUI_MAPHOOK_H
#include "maphook.h"
#endif
#ifndef _UEQUERY_UERECORD_H
#include "uequery/uerecord.h"
#endif
#ifndef _UEGUI_DISTANDTYPEHOOK_H
#include "DistAndTypeHook.h"
#endif
#ifndef _UEGUI_DIALOGEHOOK_H
#include "messagedialoghook.h"
#endif
#ifndef _UEGUI_OPERATIONRIGHT_H
#include "guioperationright.h"
#endif
#include "uebase/stringbasic.h"

#include "userdatawrapper.h"
using namespace UeMap;
using namespace UeModel;
using namespace UeBase;

namespace UeGui
{
	CHistoryQueryHook::CHistoryQueryHook() :m_selectRow(kRow0), 
		m_avtivePageIndex(kPageNone),m_Itemidx(-1)
	{
		m_strBGMenuText = "����ʷ";
		m_vecHookFile.push_back(_T("HistoryQueryHook.bin"));
	}

	CHistoryQueryHook::~CHistoryQueryHook()
	{
		m_elements.clear();
		m_ctrlNames.clear();
		m_imageNames.clear();
	}

	bool CHistoryQueryHook::gotoHistoryQueryHook(unsigned uPreHookType, 
		void *pDoCallBackObj,Query_CallBack *pCallBackEvent)
	{
		CHistoryQueryHook *pChkHistoryHook((CHistoryQueryHook *)IView::GetView()->GetHook(GetHookType()));
		if (pChkHistoryHook==0)
			return false;

		CViewHook::m_curHookType = GetHookType();
		pChkHistoryHook->m_uPrevHookType = uPreHookType;
		pChkHistoryHook->m_pDoCallBackObj = pDoCallBackObj;
		pChkHistoryHook->m_pCallBackEvent = pCallBackEvent;

		if (pDoCallBackObj != NULL)
		{
			pChkHistoryHook->m_historyRouteCtrl.SetEnable(false);	//��ʷ·��
			pChkHistoryHook->m_historyTrajectoryCtrl.SetEnable(false);	//��ʷ�켣
		}
		else
		{
			pChkHistoryHook->m_historyRouteCtrl.SetEnable(true);	//��ʷ·��
			pChkHistoryHook->m_historyTrajectoryCtrl.SetEnable(true);	//��ʷ�켣
		}
		//Ȩ�޹���
		pChkHistoryHook->m_historyRecordCtrl.SetEnable(CGuiOperationRight::HaveRight(OR_HISRECORD));
		if (pChkHistoryHook->m_historyRouteCtrl.IsEnable())
		{
			pChkHistoryHook->m_historyRouteCtrl.SetEnable(CGuiOperationRight::HaveRight(OR_HISROUTE));	//��ʷ·��
			pChkHistoryHook->m_historyTrajectoryCtrl.SetEnable(CGuiOperationRight::HaveRight(OR_HISTRACK));	//��ʷ�켣
		}

		//���� ��ʷ��¼ ҳ
		pChkHistoryHook->ActivatePage(kPageHisRecord);

		return true;
	}

	void CHistoryQueryHook::ClearARow(RowTag row)
	{
		m_listBtnCtrl[row].ClearCaption();
		m_listBtnCtrl[row].SetEnable(false);
	}

	void CHistoryQueryHook::ClearAllRows()
	{
		for(int i=0;i<nQuantityOfOnePage;i++){
			//ClearARow(i);
			m_listBtnCtrl[i].ClearCaption();
			m_listBtnCtrl[i].SetEnable(false);
		}

	}

	//����Tab״̬
	void CHistoryQueryHook::SetTabStatus(PageTag page, TabStatus status)
	{
		CViewHook::GuiElement* tabElement = NULL;
		switch (page)
		{
		case kPageHisRecord :
			{
				tabElement = GetGuiElement(ChkHistoryHook_HistoryRecord);
				break;
			}
		case kPageHisTrajectory : 
			{
				tabElement = GetGuiElement(ChkHistoryHook_HistoryTrajectory);
				break;
			}
		case kPageHisRoute :
			{
				tabElement = GetGuiElement(ChkHistoryHook_HistoryRoute);
				break;
			}
		}
		if (NULL != tabElement)
		{
			if (status == kTabFocus)
			{
				tabElement->m_backStyle = tabElement->m_bkDisabled;
			}
			else
			{
				tabElement->m_backStyle = tabElement->m_bkNormal;
			}
		}
	}
	void CHistoryQueryHook::SetNavigatorStatus()
	{
		m_prevPageCtrl.SetEnable(true);
		m_nextPageCtrl.SetEnable(true);
		if (m_pageTurning.IsFirstPage())
		{
			m_prevPageCtrl.SetEnable(false);
		}
		if (m_pageTurning.IsLastPage())
		{
			m_nextPageCtrl.SetEnable(false);
		}
	}

	//��������ʾ��ĳ����
	void CHistoryQueryHook::DoShowRowData(RowTag row, const char* value)
	{
		m_listBtnCtrl[row].SetEnable(true);
		m_listBtnCtrl[row].SetCaption(value);
	}

	//����ҳ����ʾ����
	void CHistoryQueryHook::ShowHistoryData(PageTag page)
	{
		switch (page)
		{
		case kPageHisRecord :
			{
				showHistoryRecordData();
				break;
			}
		case kPageHisTrajectory : 
			{
				showHistoryTrajectoryData();
				break;
			}
		case kPageHisRoute :
			{
				ShowHistoryRouteData();
				break;
			}
		} 
	}

	void CHistoryQueryHook::setRecortPageInfo(void){
		m_pageTurning.Clear();

    UeQuery::SQLSetting setting;
    m_query->ConnectTo(UeQuery::DT_HistoryRecords,setting);
		m_pageTurning.SetTotal(m_query->GetHistoryRecordCount());
		m_query->Disconnect(UeQuery::DT_HistoryRecords);

		m_pageTurning.SetQuantityOfOnePage(nQuantityOfOnePage);
		SetNavigatorStatus();
	}
	void CHistoryQueryHook::setTrajectoryPageInfo(void){
		m_pageTurning.Clear();
    m_pageTurning.SetTotal(0);
    m_pageTurning.SetQuantityOfOnePage(nQuantityOfOnePage);
		SetNavigatorStatus();

	}
	void CHistoryQueryHook::setRoutePageInfo(void)
	{
		m_pageTurning.Clear();

    UeQuery::SQLSetting setting;
    m_query->ConnectTo(UeQuery::DT_Recents,setting);
		m_pageTurning.SetTotal(m_query->GetRecentCount());
    m_query->Disconnect(UeQuery::DT_Recents);

		m_pageTurning.SetQuantityOfOnePage(nQuantityOfOnePage);
		SetNavigatorStatus();
	}

	//��ȡ����ʾ ��ʷ��¼ ����
	void CHistoryQueryHook::showHistoryRecordData(void){
		ClearAllRows();
		// ����ҳ����Ϣ
		m_pageInfoCtrl.SetCaption(m_pageTurning.GetPageInfo());

		//��ʾ����
		int startPos = m_pageTurning.GetPageStartPosition() - 1;
		int endPos = m_pageTurning.GetPageEndPosition() - 1;
		if (startPos >= 0)
		{
			int row = kRow0;
			UeQuery::SQLSetting setting;
			unsigned int isConnectOK=m_query->ConnectTo(UeQuery::DT_HistoryRecords,setting);
			if (isConnectOK != UeQuery::SQL_Success)
				return;
			for(int i = startPos; i <= endPos; i++)
			{
				const HistoryRecordEntry *curEntry = m_query->GetHistoryRecord(i);
				if (curEntry)
				{
          const CStringBasic& stringBasic = CStringBasic::Get();
          //DoShowRowData((RowTag)row, stringBasic.TrimSpace((char*)curEntry->m_addrName));
          char* addrname = new char[HistoryRecordEntry::MAXADDRNAMELENGTH];
          ::strcpy(addrname,(char*)curEntry->m_addrName);
          //DoShowRowData((RowTag)row, (char*)curEntry->m_addrName);
          DoShowRowData((RowTag)row, stringBasic.TrimSpace(addrname));
          delete addrname;
					++row;
				}
			}
			m_query->Disconnect(UeQuery::DT_HistoryRecords);
		}
	}	
	//��ȡ����ʾ ��ʷ�켣 ����
	void CHistoryQueryHook::showHistoryTrajectoryData(void){
		ClearAllRows();	
		m_pageInfoCtrl.SetCaption("0/0");
	}
	//��ȡ����ʾ ��ʷ·�� ����
	void CHistoryQueryHook::ShowHistoryRouteData()
	{
		ClearAllRows();
		// ����ҳ����Ϣ
		m_pageInfoCtrl.SetCaption(m_pageTurning.GetPageInfo());

		int startPos = m_pageTurning.GetPageStartPosition() - 1;
		int endPos = m_pageTurning.GetPageEndPosition() - 1;
		if (startPos < 0)
			return;

		//��ʾ����
		int row = kRow0;
		UeQuery::SQLSetting setting;
		if( (m_query->ConnectTo(UeQuery::DT_Recents, setting)) != UeQuery::SQL_Success )
			return;
		for(int i = startPos; i <= endPos; i++)
		{
			const RecentEntry *curEntry = m_query->GetRecent(i);

			CTimeBasic::TimeReport timeReport = {};
			CTimeBasic::Double2TimeReport(curEntry->m_timeStamp, timeReport);

			char timeStr[20] = "";
			::sprintf(timeStr, "%4d/%02d/%02d/%02d:%02d", 
				timeReport.m_year, timeReport.m_month, timeReport.m_day, timeReport.m_hour, timeReport.m_minute);
			char routeName[30] = "��ʷ��¼--";
			::strcat(routeName, timeStr);
			DoShowRowData((RowTag)row, (char*)routeName);
			++row;
		}
		m_query->Disconnect(UeQuery::DT_Recents);
	}

	//����ָ��ҳ
	void CHistoryQueryHook::ActivatePage( PageTag page )
	{
		//��¼��ǰ�ҳID
		m_avtivePageIndex = page;

		//3.1 ���ñ�ǩ�ؼ���״̬
		//3.2 ����ҳ����Ϣ
		//3.3 ��ʾ����
		switch (page)
		{
		case kPageHisRecord :
			{
				SetTabStatus(kPageHisRecord, kTabFocus);
				SetTabStatus(kPageHisTrajectory, kTabNormal);
				SetTabStatus(kPageHisRoute, kTabNormal);

				setRecortPageInfo();
				showHistoryRecordData();
				break;
			}
		case kPageHisTrajectory : 
			{
				SetTabStatus(kPageHisRecord, kTabNormal);
				SetTabStatus(kPageHisTrajectory, kTabFocus);
				SetTabStatus(kPageHisRoute, kTabNormal);

				setTrajectoryPageInfo();
				showHistoryTrajectoryData();
				break;
			}
		case kPageHisRoute :
			{
				SetTabStatus(kPageHisRecord, kTabNormal);
				SetTabStatus(kPageHisTrajectory, kTabNormal);
				SetTabStatus(kPageHisRoute, kTabFocus);	

				setRoutePageInfo();
				ShowHistoryRouteData();
				break;
			}
		}	
	}

	///////////////////////////////////////////////////////////////////////////
	void CHistoryQueryHook::selectARow()
	{
		//��ʷ��¼
		if (m_avtivePageIndex == kPageHisRecord)
		{
			//�����ͼ
			CMapHook *pMapHook((CMapHook *)(m_view->GetHook(CViewHook::DHT_MapHook)));
			SQLRecord tmp;
			UeQuery::SQLSetting setting;
			m_query->ConnectTo(UeQuery::DT_HistoryRecords,setting);
			const HistoryRecordEntry *curEntry = m_query->GetHistoryRecord(m_Itemidx);
			tmp.m_x=curEntry->m_X;
			tmp.m_y=curEntry->m_Y;
			tmp.m_uniName=new char[128];
			strcpy(tmp.m_uniName,(char*)curEntry->m_addrName);
			m_query->Disconnect(UeQuery::DT_HistoryRecords);

			if (m_pCallBackEvent!=0)
			{
				m_pCallBackEvent(m_pDoCallBackObj,&tmp);
				delete[] tmp.m_uniName;
			}
			else
			{
				pMapHook->PeripheralInformationSwitch(&tmp);
				delete[] tmp.m_uniName;
			}
		}
		//��ʷ��·
		else if (m_avtivePageIndex == kPageHisRoute)
		{
			if (m_route)
			{
				short planState = m_route->GetPlanState();
				if ((UeRoute::PS_DemoGuidance == planState) || (UeRoute::PS_RealGuidance == planState))
				{     
					CMessageDialogEvent dialogEvent(this, CViewHook::DHT_HistoryQueryHook, &UeGui::CHistoryQueryHook::OnSelectHistoryRoute);
					CMessageDialogHook::ShowMessageDialog(MB_INFORMATION, "�Ƿ��������?", dialogEvent);
					return;
				}
				else
				{
					PlanHistoryRoute();
				}
			}
		}
		//��ʷ�켣
		else //m_avtivePageIndex == kPageHisTrajectory
		{
			//SetRouteStart(...) //���
			//SetRouteWay(...)	 //������
			//SetRouteEnd(...)	 //�յ�
			CMapHook *pMapHook((CMapHook *)(m_view->GetHook(CViewHook::DHT_MapHook)));
		}
	}

	void CHistoryQueryHook::OnSelectHistoryRoute( CAggHook* sender, ModalResultType modalResult )
	{
		if (MR_OK == modalResult)
		{
			CHistoryQueryHook* pHistoryQueryHook = dynamic_cast<CHistoryQueryHook*>(sender);
			pHistoryQueryHook->SelectHistoryRoute();
		}
	}
	void CHistoryQueryHook::SelectHistoryRoute()
	{
		short planState = m_route->GetPlanState();
		if (UeRoute::PS_DemoGuidance == planState)        
		{
			m_route->StopDemo();
		}
		else if (UeRoute::PS_RealGuidance == planState)
		{
			m_route->StopGuidance();
		}
		PlanHistoryRoute();
	}

	void CHistoryQueryHook::PlanHistoryRoute()
	{
    if (m_view)
    {
      CUserDataWrapper::Get().HistoryRoutePlan(m_Itemidx);
    }
	}


	// �¼���Ӧ����
	short CHistoryQueryHook::MouseUp(CGeoPoint<short> &scrPoint)
	{
		short ctrlType = CAggHook::MouseUp(scrPoint);
		switch(m_downElementType)
		{
			//��ʷ��¼ ��ǩ
		case ChkHistoryHook_HistoryRecord:
			{
				if (m_historyRecordCtrl.IsEnable())
				{
					m_historyRecordCtrl.MouseUp();
					ActivatePage(kPageHisRecord);
				}
			}
			break;
			//��ʷ�켣 ��ǩ
		case ChkHistoryHook_HistoryRoute:
			{
				if (m_historyRouteCtrl.IsEnable())
				{
					m_historyRouteCtrl.MouseUp();
					ActivatePage(kPageHisRoute);
				}
			}
			break;
			//��ʷ��· ��ǩ
		case ChkHistoryHook_HistoryTrajectory:
			{
				if (m_historyTrajectoryCtrl.IsEnable())
				{
					m_historyTrajectoryCtrl.MouseUp();
					ActivatePage(kPageHisTrajectory);
				}
			}
			break;
			//���·�ҳ
		case ChkHistoryHook_PageDownBtn:
		case ChkHistoryHook_PageDownIcon:
			{
				if (m_nextPageCtrl.IsEnable())
				{
					m_nextPageCtrl.MouseUp();

					m_pageTurning.NextPage();
					SetNavigatorStatus();
					ShowHistoryData(m_avtivePageIndex);
				}	
			}
			break;
			//���Ϸ�ҳ
		case ChkHistoryHook_PageUpBtn:
		case ChkHistoryHook_PageUpIcon:
			{
				if (m_prevPageCtrl.IsEnable())
				{
					m_prevPageCtrl.MouseUp();

					m_pageTurning.PreviousPage();
					SetNavigatorStatus();
					ShowHistoryData(m_avtivePageIndex);
				}
			}
			break;
			//�б�ť
		default:
			if (ctrlType>=ChkHistoryHook_List1LeftBtn && ctrlType<=ChkHistoryHook_List5RightBtn)
			{
				//ѡ���˵ڼ���
				int idxOfSelectedRow = (ctrlType-ChkHistoryHook_List1LeftBtn)/3;
				//ѡ�е�Ԫ�����ļ��ж�Ӧ�������Ƕ���
				m_Itemidx = (m_pageTurning.GetCurrentPage()-1) * nQuantityOfOnePage + idxOfSelectedRow;

				if( m_listBtnCtrl[idxOfSelectedRow].IsEnable() )
				{
					m_listBtnCtrl[idxOfSelectedRow].MouseUp();

					selectARow();
					break;
				}
			}
			else
				return CBackgroundHook::doMouseUp(ctrlType);
		}

		this->Refresh();
		return ctrlType;
	}

	short CHistoryQueryHook::MouseDown(CGeoPoint<short> &scrPoint)
	{
		short ctrlType = CAggHook::MouseDown(scrPoint);
		switch(ctrlType)
		{
		case ChkHistoryHook_HistoryRecord:
			{
				if(m_avtivePageIndex != kPageHisRecord)
					m_historyRecordCtrl.MouseDown();
			}
			break;
		case ChkHistoryHook_HistoryRoute:
			{
				if(m_avtivePageIndex != kPageHisRoute)
					m_historyRouteCtrl.MouseDown();
			}
			break;
		case ChkHistoryHook_HistoryTrajectory:
			{
				if(m_avtivePageIndex != kPageHisTrajectory)
					m_historyTrajectoryCtrl.MouseDown();
			}
			break;
		case ChkHistoryHook_PageDownBtn:
		case ChkHistoryHook_PageDownIcon:
			{
				if(m_nextPageCtrl.IsEnable())
					m_nextPageCtrl.MouseDown();
			}
			break;
		case ChkHistoryHook_PageUpBtn:
		case ChkHistoryHook_PageUpIcon:
			{
				if(m_prevPageCtrl.IsEnable())
					m_prevPageCtrl.MouseDown();
			}
			break;

		default:
			if (ctrlType>=ChkHistoryHook_List1LeftBtn && ctrlType<=ChkHistoryHook_List5RightBtn)
			{
				int indexOfBtn=(ctrlType-ChkHistoryHook_List1LeftBtn)/3;
				if(m_listBtnCtrl[indexOfBtn].IsEnable())
					m_listBtnCtrl[indexOfBtn].MouseDown();
			}else
				CBackgroundHook::doMouseDown(ctrlType);
			assert(false);
			break;
		}

		this->Refresh();
		return ctrlType;
	}

	short CHistoryQueryHook::MouseMove(CGeoPoint<short> &scrPoint)
	{
		return -1;
	}

	bool CHistoryQueryHook::operator ()()
	{
		return false;
	}

	void CHistoryQueryHook::initCtrlNames()
	{
		m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());

		CBackgroundHook::initCtrlNames();
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_PageInfo,	"PageInfo"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_HistoryRecord,	"HistoryRecord"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_HistoryTrajectory,	"HistoryTrajectory"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_HistoryRoute,	"HistoryRoute"));

		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List1LeftBtn,	"List1LeftBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List1CenterBtn,	"List1CenterBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List1RightBtn,	"List1RightBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List2LeftBtn,	"List2LeftBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List2CenterBtn,	"List2CenterBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List2RightBtn,	"List2RightBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List3LeftBtn,	"List3LeftBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List3CenterBtn,	"List3CenterBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List3RightBtn,	"List3RightBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List4LeftBtn,	"List4LeftBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List4CenterBtn,	"List4CenterBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List4RightBtn,	"List4RightBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List5LeftBtn,	"List5LeftBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List5CenterBtn,	"List5CenterBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_List5RightBtn,	"List5RightBtn"));

		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_PageUpBtn,	"PageUpBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_PageUpIcon,	"PageUpIcon"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_PageDownBtn,	"PageDownBtn"));
		m_ctrlNames.insert(GuiName::value_type(ChkHistoryHook_PageDownIcon,	"PageDownIcon"));
	}

	void CHistoryQueryHook::initHookCtrl()
	{
		CBackgroundHook::initHookCtrl();

		m_historyRecordCtrl.SetCenterElement(GetGuiElement(ChkHistoryHook_HistoryRecord));
		m_historyRouteCtrl.SetCenterElement(GetGuiElement(ChkHistoryHook_HistoryRoute));
		m_historyTrajectoryCtrl.SetCenterElement(GetGuiElement(ChkHistoryHook_HistoryTrajectory));
		m_pageInfoCtrl.SetCenterElement(GetGuiElement(ChkHistoryHook_PageInfo));

		m_nextPageCtrl.SetCenterElement(GetGuiElement(ChkHistoryHook_PageDownBtn));
		m_nextPageCtrl.SetIconElement(GetGuiElement(ChkHistoryHook_PageDownIcon));
		m_prevPageCtrl.SetCenterElement(GetGuiElement(ChkHistoryHook_PageUpBtn));
		m_prevPageCtrl.SetIconElement(GetGuiElement(ChkHistoryHook_PageUpIcon));

		for (int i=0;i<nQuantityOfOnePage;i++)
		{
			m_listBtnCtrl[i].SetLeftElement(GetGuiElement(ChkHistoryHook_List1LeftBtn+3*i));
			m_listBtnCtrl[i].SetCenterElement(GetGuiElement(ChkHistoryHook_List1CenterBtn+3*i));
			m_listBtnCtrl[i].SetRightElement(GetGuiElement(ChkHistoryHook_List1RightBtn+3*i));
		}
	}
}
