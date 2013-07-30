#ifndef _UEGUI_QUERYBASEHOOK_H
#include "QueryHookBase.h"
#endif
#ifndef _UEGUI_QUERYWRAPPER_H
#include "querywrapper.h"
#endif
#ifndef _UEGUI_DIALOGEHOOK_H
#include "messagedialoghook.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeGui
{
	bool CQueryHookBase::g_bIsRefreshing(false);
	bool CQueryHookBase::g_bHasRefreshRequst(false);
	std::vector<CQueryHookBase *> CQueryHookBase::g_vecQueryObj;
	//
	void CQueryHookBase::doGotoNagiv(void)
	{
		CViewHook *pViewHook(IView::GetView()->GetHook(m_uPrevHookType));
		if (CQueryHookBase *pQueryHook = dynamic_cast<CQueryHookBase *>(pViewHook))
		{
			pQueryHook->doGotoNagiv();
		}
	}
  CUeRecord *CQueryHookBase::DoQueryGetRecord(bool bShowDialog)
  {
    if (bShowDialog)
    {
      CMessageDialogEvent dialogEvent(0,CViewHook::m_curHookType,NULL);
      CMessageDialogHook::ShowMessageDialog(MB_NONE, "���ݼ����У����Ժ�...", dialogEvent);
    }
    CUeRecord *pRecordVec(CQueryWrapper::Get().DoQueryGetRecord());
    if (bShowDialog)
    {
      CMessageDialogHook::CloseMessageDialog();
      //
      if (!CQueryWrapper::Get().IsDoQueryEventAlways()
        && pRecordVec==0)
      {
        //��ʾû�н��
        CMessageDialogEvent dialogEvent(0,CViewHook::m_curHookType,NULL);
        CMessageDialogHook::ShowMessageDialog(MB_INFORMATION, "û���ҵ����",dialogEvent);
      }
    }
    return pRecordVec;
  }
}