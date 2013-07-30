#ifndef _UEGUI_BACKGROUNDHOOK_H
#include "backgroundHook.h"
#endif
//////////////////////////////////////////////////////////////////////////
#include "maphook.h"
#include "mapsettinghook.h"
namespace UeGui
{
	void CBackgroundHook::initCtrlNames(void)
	{
		m_ctrlNames.clear();
		//���಻���ڽ������
		m_ctrlNames.insert(GuiName::value_type(BT_GotoMap,"GotoMapBtn"));
		m_ctrlNames.insert(GuiName::value_type(BT_LogicBack,"LogicBackBtn"));
		m_ctrlNames.insert(GuiName::value_type(BT_BGMenuText,"BGMenuText"));
	}
	void CBackgroundHook::FetchWithBinary(void)
	{
		for (; m_uCurHookFileIdx<m_vecHookFile.size(); ++m_uCurHookFileIdx)
		{
			CAggHook::FetchWithBinary();
		}
	}
	void CBackgroundHook::initHookCtrl(void)
	{
		//��ťЧ����ʾ�ؼ�
		m_gotoMapBtn.SetLabelElement(GetGuiElement(BT_GotoMap));
		m_logicBackBtn.SetLabelElement(GetGuiElement(BT_LogicBack));
		::strcpy(GetGuiElement(BT_BGMenuText)->m_label,m_strBGMenuText.c_str());
	}
	short CBackgroundHook::doMouseUp(short ctrlType)
	{
		switch (m_downElementType)
		{
		case BT_GotoMap:
			m_gotoMapBtn.MouseUp();
			if (ctrlType==m_downElementType)
			{
				doGotoNagiv();
				//����������ͼʱ��û�з������Բ������÷���
        CAggHook::GoToMapHook();
				//����������maphook�е�ѡ�㰴ť���ɼ�
        ((CAggHook *)m_view->GetHook(CViewHook::DHT_MapHook))->ComeBack();

        //�����ѡ�񵼺����򣨸��ӵ�ͼ���������ϣ�ͼ�泵ת�����ͼģʽ��ˢ�µ�ͼ
        CMapSettingHook *settingHook = (CMapSettingHook *)(m_view->GetHook(CViewHook::DHT_MapSettingHook));
        if(settingHook->IschangeSetting())
        {
          //����Ѿ��滮��·����ˢ��
          //UeRoute::PlanResultDesc desc;
          //if (m_route->GetPlanState() != UeRoute::PS_None && m_route->GetPlanResultDesc(desc))
          {
            m_view->Refresh();
            m_isNeedRefesh = false;
          }
        }
			}
			break;
		case BT_LogicBack:
			m_logicBackBtn.MouseUp();
			if (ctrlType==m_downElementType)
			{
				doLogicBack();
        //m_view->Refresh()���ˢ�±��������ǵ�ǰhookΪmaphook��
        //�����ѡ�񵼺����򣨸��ӵ�ͼ���������ϣ�ͼ�泵ת�����ͼģʽ��ˢ�µ�ͼ
         CMapSettingHook *settingHook = (CMapSettingHook *)(m_view->GetHook(CViewHook::DHT_MapSettingHook));
         if(settingHook->IschangeSetting()&&(CViewHook::m_curHookType == CViewHook::DHT_MapHook))
         {
           //����Ѿ��滮��·����ˢ��
           //UeRoute::PlanResultDesc desc;
           //if (m_route->GetPlanState() != UeRoute::PS_None && m_route->GetPlanResultDesc(desc))
           {
             m_view->Refresh();
             m_isNeedRefesh = false;
           }
         }
       ((CMapHook *)m_view->GetHook(CViewHook::DHT_MapHook))->m_isOpenMenu=false;
       ((CMapHook *)m_view->GetHook(CViewHook::DHT_MapHook))->DoRouteCancel();
			}
			break;
		default:
			return ctrlType;
		}
		//
		Destroy();
		if (m_uPrevHookType<DHT_QueryMenuHook
			|| m_uPrevHookType>DHT_CrossQueryListHook)
		{
			if (m_query!=0)
			{
				m_query->Release();
			}
		}
		//
    if (m_isNeedRefesh)
    {
      Refresh();
    }
    m_isNeedRefesh = true;
		return ctrlType;
	}
	short CBackgroundHook::doMouseDown(short ctrlType)
	{
		switch (ctrlType)
		{
		case BT_GotoMap:
			m_gotoMapBtn.MouseDown();
			break;
		case BT_LogicBack:
			m_logicBackBtn.MouseDown();
			break;
		default:
			return ctrlType;
		}
		Refresh();
		return ctrlType;
	}
}