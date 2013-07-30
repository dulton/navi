/**
* Copyright (c) 2012-2013 Guangdong Ritu Information System Co.,Ltd.
*/ 
#ifndef _UEGUI_UICODEBUTTON_H
#define _UEGUI_UICODEBUTTON_H

#include "uibutton.h"

#include "uequery/codeindexctrl.h"

namespace UeGui
{
  class CUiCodeButton : public CUiButton
  {
  public:
    CUiCodeButton() {}

    ~CUiCodeButton() {}
    /**
    * \brief ����CodeEntry
    **/
    void SetCodeEntry(const TCodeEntry& entry) { m_codeEntry = entry;}

    const TCodeEntry& GetCodeEntry() { return m_codeEntry; }
    /**
    * \brief ��ȡ�������
    **/
    unsigned int GetCode() { return m_codeEntry.m_uCode; }
  private:
    UeQuery::TCodeEntry m_codeEntry;
  };
}
#endif //_UEGUI_UICODEBUTTON_H