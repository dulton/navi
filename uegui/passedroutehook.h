/**
* Copyright (c) 2012-2013 Guangdong Ritu Information System Co.,Ltd.
*/ 
#ifndef _UEGUI_PASSEDROUTEHOOK_H
#define _UEGUI_PASSEDROUTEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "menubackgroundhook.h"

//#include "uilabel.h"
#include "uibutton.h"
#include "uipageturningctrl.h"
#include "ueroute/routebasic.h"
#include "uebase/geombasic.h"
#include "routewrapper.h"

namespace UeGui
{
  class UEGUI_CLASS CPassedRouteHook : public CMenuBackgroundHook
  {
    enum RowTag
    {
      kROWBegin = 0,
      kROW1,
      kROW2,
      kROW3,
      kROW4,
      kROW5,
      kROWEnd
    };
    /**
    * \brief ��������ʾ���㷨��
    * �����յ㲻�ܻرܡ�ֻ������к��յ���Ҫ��ʾ �����յ��ͼ�ꡣ
    * ������ǵ�һҳ�ĵ�һ�У��յ��������һҳ�����һ��
    **/
    class CRouteRow
    {
    public:
      explicit CRouteRow(CUiButton *rowFlag, CUiButton *rowName, 
                        CUiButton *rowDist, CUiButton *rowAvoid, 
                        CPageController *pageTurning, int rowNum)
        : m_rowFlagBtn(rowFlag), m_rowNameBtn(rowName), 
          m_rowDistBtn(rowDist), m_rowAvoidBtn(rowAvoid),
          m_pageController(pageTurning), m_rowNum(rowNum),
          m_startFlag(0), m_endFlag(0)
      {
      }
      
      bool IsValid();
      //�������ͼ��
      void SetStartFlag(int startFlag) { m_startFlag = startFlag; }
      //����Ŀ�ĵ�ͼ��
      void SetEndFlag(int endFlag) { m_endFlag = endFlag; }
      /**
      * \brief ��ʾ��·���� 
      * \routeName ��·����
      * \mileage  ��·�ĳ���
      **/
      void Show(const char* routeName, const char* mileages);
      //�����Ϣ
      void Clear();
    private:
       CUiButton *m_rowFlagBtn;
       CUiButton *m_rowNameBtn;
       CUiButton *m_rowDistBtn;
       CUiButton *m_rowAvoidBtn;
       CPageController *m_pageController;
       int m_startFlag;
       int m_endFlag;
       //��1��ʼ
       int m_rowNum;
    };
    typedef std::vector<CRouteRow> RowList;

  public:

    enum passedroutehookCtrlType
    {
      passedroutehook_Begin = MenuBackgroundHook_End,
      passedroutehook_Lable1,
      passedroutehook_TotalDistLable,
      passedroutehook_Lable2,
      passedroutehook_TotalTimeLable,
      passedroutehook_Lable3,
      passedroutehook_HighWayDistLable,
      passedroutehook_Lable4,
      passedroutehook_NormalRouteLable,
      passedroutehook_RowOneBtn,
      passedroutehook_RowTwoBtn,
      passedroutehook_RowThreeBtn,
      passedroutehook_RowFourBtn,
      passedroutehook_RowFiveBtn,
      passedroutehook_RowOneNameLable,
      passedroutehook_RowTwoNameLable,
      passedroutehook_RowThreeNameLable,
      passedroutehook_RowFourNameLable,
      passedroutehook_RowFiveNameLable,
      passedroutehook_RouteTypeBtn,
      passedroutehook_RouteDownBtn,
      passedroutehook_RowOneDistLable,
      passedroutehook_RowOneSplitLable,
      passedroutehook_RowOneAvoidBtn,
      passedroutehook_RowTwoDistLable,
      passedroutehook_RowTwoSplitLable,
      passedroutehook_RowTwoAvoidBtn,
      passedroutehook_RowThreeDistLable,
      passedroutehook_RowThreeSplitLable,
      passedroutehook_RowThreeAvoidBtn,
      passedroutehook_RowFourDistLable,
      passedroutehook_RowFourSplitLable,
      passedroutehook_RowFourAvoidBtn,
      passedroutehook_RowFiveDistLable,
      passedroutehook_RowFiveSplitLable,
      passedroutehook_RowFiveAvoidBtn,
      passedroutehook_ColSplit,
      passedroutehook_RowUpBtn,
      passedroutehook_RowDownBtn,
      passedroutehook_RowDownArrowBtn,
      passedroutehook_RowUpArrowBtn,
      passedroutehook_CurrentPageLable,
      passedroutehook_SplitBtn,
      passedroutehook_TotalPageLable,
      passedroutehook_FlagOnePic,
      passedroutehook_FlagTwoPic,
      passedroutehook_FlagThreePic,
      passedroutehook_FlagFourPic,
      passedroutehook_FlagFivePic,
      passedroutehook_FlagPic,
      passedroutehook_End
    };

    CPassedRouteHook();

    virtual ~CPassedRouteHook();

    virtual void Init();

    virtual void Load();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);


  protected:

    virtual void MakeNames();

    void MakeControls();

  private:
    //�����Ϣ
    void ClearAll();

    //���������
    void ClearRows();

    //��ȡ����λ�õ���ǰIndicatorʣ�µľ���
    float GetCurIndicatorLeftDist(const GuidanceStatus& dirInfo) const;

    //��ù滮�Ľ����
    bool GetResultDesc(const unsigned char curPlan, PlanResultDesc &desc) const;

    //��ȡ·������
    unsigned char GetPlanType() const;

    //��ʾ�滮��Ϣ
    void SetPlanInfo( UeRoute::PlanResultDesc& planResult);

    //��ʼ����·��Ϣ
    void LaodRouteList();

    //��ʼ��ҳ��Ϣ
    void LoadPageTuring();

    //��ʾ·������(ֻ��ʾ��ǰҳ)
    void ShowRouteData();

    //����ҳ�水ť״̬
    void SetPageCtrlStatus();

    /**
    * \brief ��ʾ��·���� 
    * \row  ��ʾ�ڵڼ���
    * \routeName ��·����
    * \mileage  ��·�ĳ���
    **/
    void ShowRowData( RowTag row, const char* routeName, const char* mileages);

    /**
    * \brief �����еĿ�����
    **/
    void SetRowEnbale(RowTag row, bool isShow);

    /**
    * \brief ��ʾҳ��
    **/
    void ShowPageInfo();

    /**
    * \brief ��ʼ����
    **/
    void InitRowList();
    /**
    * \brief ѡ���·
    **/
    void SelectRow(unsigned int row);
    /**
    * \brief ���ѡ���е���������
    **/
    int GetDataIndex(unsigned int row);

    PointList GetCurrentPagePointList();
    /**
    * \brief ���ݿؼ��Ƿ�������ж��Ƿ�ˢ��
    * \param button ��ť
    **/
    bool IsNeedRefresh(CUiButton &button);

    void ClickRowByMouseUp(CUiButton &button, unsigned int row);

    void DoButtonMouseDown(CUiButton &button);

    void AvoidRoute(unsigned int row);
  private:
    //��ҳ������
    CPageController m_pageController;
    //·���б�
    RouteList m_routeList;
    //���б�
    RowList  m_rowList;
  private:
    CUiButton m_currentPageLableCtrl;
    CUiButton m_flagFivePicCtrl;
    CUiButton m_flagFourPicCtrl;
    CUiButton m_flagThreePicCtrl;
    CUiButton m_flagTwoPicCtrl;
    CUiButton m_highWayDistLableCtrl;
    CUiButton m_normalRouteLableCtrl;
    CUiButton m_routeDownBtnCtrl;
    CUiButton m_routeTypeBtnCtrl;
    CUiButton m_rowDownArrowBtnCtrl;
    CUiButton m_rowDownBtnCtrl;
    CUiButton m_rowFiveAvoidBtnCtrl;
    CUiButton m_rowFiveBtnCtrl;
    CUiButton m_rowFiveDistLableCtrl;
    CUiButton m_rowFiveNameLableCtrl;
    CUiButton m_rowFourAvoidBtnCtrl;
    CUiButton m_rowFourBtnCtrl;
    CUiButton m_rowFourDistLableCtrl;
    CUiButton m_rowFourNameLableCtrl;
    CUiButton m_rowOneAvoidBtnCtrl;
    CUiButton m_rowOneBtnCtrl;
    CUiButton m_rowOneDistLableCtrl;
    CUiButton m_rowOneNameLableCtrl;
    CUiButton m_rowThreeAvoidBtnCtrl;
    CUiButton m_rowThreeBtnCtrl;
    CUiButton m_rowThreeDistLableCtrl;
    CUiButton m_rowThreeNameLableCtrl;
    CUiButton m_rowTwoAvoidBtnCtrl;
    CUiButton m_rowTwoBtnCtrl;
    CUiButton m_rowTwoDistLableCtrl;
    CUiButton m_rowTwoNameLableCtrl;
    CUiButton m_rowUpArrowBtnCtrl;
    CUiButton m_rowUpBtnCtrl;
    CUiButton m_flagOnePicCtrl;
    CUiButton m_totalDistLableCtrl;
    CUiButton m_totalPageLableCtrl;
    CUiButton m_totalTimeLableCtrl;
  };
}
#endif
