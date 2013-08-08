#ifndef _UEGUI_SELECTPOINTCALLBACKCTRL_H
#define _UEGUI_SELECTPOINTCALLBACKCTRL_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEQUERY_CODEINDEXCTRL_H
#include "uequery/uerecord.h"
#endif
#ifndef _UEQUERY_QUERYDEF_H
#include "uequery/querybasic.h"
#endif
#ifndef _UEGUI_GUIBASIC_H
#include "guibasic.h"
#endif
namespace UeGui
{
  class CSelectPointCallBackCtrl
  {
  public:
    static CSelectPointCallBackCtrl &Get();
    //����ͼ��ѡ��Ļص���
    void SetCallBackFun(void *pDoCallBackObj, SelectPointEvent pCallBackEvent);
    //����ѡ�㲢�ص�
    void SetSelectedPoint(const UeQuery::SQLRecord *record);
    //�����Ƿ��лص�����
    void SetIsCallBackFunExist(bool isExist);
    //�ж��Ƿ��лص�����
    bool IsCallBackFunExist();
    void *GetCallBackObj();
    SelectPointEvent GetEvent();
  private:
    CSelectPointCallBackCtrl();
    SelectPointEvent m_queryCallBack;
    void *m_callBackObject;
    bool m_isCallBackFunExist;
  };
}
#endif