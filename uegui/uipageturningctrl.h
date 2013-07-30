/*
* ��ҳ���ƶ���
* ʹ�÷����� 
* �û����÷��� SetTotal() ������������ 
* ���� SetQuantityOfOnePage()������ÿҳ��ʾ����
* ͨ���ӿ� NextPage() ������һҳ
* ͨ���ӿ� PreviousPage() ������һҳ
* GetPageStartPosition() ��ȡ��ǰҳ����ʼλ��
* GetPageEndPosition() ��ȡ��ǰҳ�Ľ���λ��
*/

#ifndef _UEGUI_PAGECONTROLLER_H
#define _UEGUI_PAGECONTROLLER_H

#include <stdio.h>
#include <iostream>

namespace UeGui
{
  class CUiControl;
  class CPageController
  {
  public:
    CPageController() : m_startPosition(-1), m_quantityOfOnePage(0), m_total(0)
    {
      memset(m_pageInfo, 0, sizeof(m_pageInfo));
    }
    virtual ~CPageController() {}
  public:
    /// �������
    void Clear();
    /// ���÷�ҳ��Ϣ������ʼҳ��λ����һҳ
    void Reset();
    /// ����������
    void SetTotal(int value);    
    /// ���õ�ҳ��ʾ��������
    void SetQuantityOfOnePage(int value);
    /// ɾ������ʱ�������м�ȥ��������
    void DeleteRecord(int numbers);
    /// ��һҳ
    void NextPage();
    /// ǰһ��ҳ
    void PreviousPage();
    /// ��ȡ��һҳ����ʼλ��
    int GetPageStartPosition();
    /// ��ȡǰһҳ����ʼλ��
    int GetPageEndPosition();
    /// ��ȡ��ҳ��
    int GetTotalPage();
    /// ��ȡ��ǰ�ǵڼ�ҳ
    int GetCurrentPage();
    /// ��ȡ��ǰҳ����ʾ��Ϣ
    char* GetPageInfo();
    /// ��ǰҳ�Ƿ��ǵ�һҳ
    bool IsFirstPage();
    /// ��ǰҳ�Ƿ������һҳ
    bool IsLastPage(); 
    /// ��ȡ���һҳ�����һ�е�����
    int GetLastPageEndRow();
    /// ��ʾҳ����Ϣ
    void ShowPageInfo(CUiControl *currentLable, CUiControl *totalLable);
  private:
    void InitPageInfo();
  private:
    /// ����������
    int m_total;
    /// ��ҳ��ʾ����
    int m_quantityOfOnePage;
    //��ǰҳ����� ��1��ʼ
    int m_startPosition;
    /// ҳ����ʾ��Ϣ
    char m_pageInfo[10];
  };
}

#endif //_UEGUI_PAGECONTROLLER_H