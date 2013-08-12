#ifndef _UEGUI_MAPGUIDEINFOVIEWHOOK_H
#define _UEGUI_MAPGUIDEINFOVIEWHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"
#include "routewrapper.h"
#include "viewwrapper.h"

namespace UeGui
{
  class UEGUI_CLASS CMapGuideInfoViewHook : public CAggHook
  {
  public:
    enum MapGuideInfoViewHookCtrlType
    {
      MapGuideInfoViewHook_Begin = 0,
      MapGuideInfoViewHook_RouteInfoBtn,
      MapGuideInfoViewHook_RouteInfoIcon,
      MapGuideInfoViewHook_RouteInfoLabel,
      MapGuideInfoViewHook_CurDirectionBoard,
      MapGuideInfoViewHook_CurDirectionBoardIcon,
      MapGuideInfoViewHook_DistInfoLabel,
      MapGuideInfoViewHook_NextDirectionBoard,
      MapGuideInfoViewHook_NextDirectionBoardIcon,
      MapGuideInfoViewHook_HighSpeedBoardBack1,
      MapGuideInfoViewHook_HighSpeedBoardNameLabel1,
      MapGuideInfoViewHook_HighSpeedBoardTypeLabel1,
      MapGuideInfoViewHook_HighSpeedBoardDistLabel1,
      MapGuideInfoViewHook_HighSpeedBoardBack2,
      MapGuideInfoViewHook_HighSpeedBoardNameLabel2,
      MapGuideInfoViewHook_HighSpeedBoardTypeLabel2,
      MapGuideInfoViewHook_HighSpeedBoardDistLabel2,
      MapGuideInfoViewHook_HighSpeedBoardBack3,
      MapGuideInfoViewHook_HighSpeedBoardNameLabel3,
      MapGuideInfoViewHook_HighSpeedBoardTypeLabel3,
      MapGuideInfoViewHook_HighSpeedBoardDistLabel3,
      MapGuideInfoViewHook_ShowGuideViewBack,
      MapGuideInfoViewHook_ShowGuideViewLabel,
      MapGuideInfoViewHook_RouteGuideBack,
      MapGuideInfoViewHook_RouteGuideCurName,
      MapGuideInfoViewHook_RouteGuideIcon1,
      MapGuideInfoViewHook_RouteGuideIcon2,
      MapGuideInfoViewHook_RouteGuideIcon3,
      MapGuideInfoViewHook_RouteGuideIcon4,
      MapGuideInfoViewHook_RouteGuideName1,
      MapGuideInfoViewHook_RouteGuideName2,
      MapGuideInfoViewHook_RouteGuideName3,
      MapGuideInfoViewHook_RouteGuideName4,
      MapGuideInfoViewHook_RouteGuideDist1,
      MapGuideInfoViewHook_RouteGuideDist2,
      MapGuideInfoViewHook_RouteGuideDist3,
      MapGuideInfoViewHook_RouteGuideDist4,
      MapGuideInfoViewHook_IconType1_1,
      MapGuideInfoViewHook_IconType1_2,
      MapGuideInfoViewHook_IconType1_3,
      MapGuideInfoViewHook_IconType1_4,
      MapGuideInfoViewHook_IconType1_5,
      MapGuideInfoViewHook_IconType2_1,
      MapGuideInfoViewHook_IconType2_2,
      MapGuideInfoViewHook_IconType2_3,
      MapGuideInfoViewHook_IconType2_4,
      MapGuideInfoViewHook_IconType2_5,
      MapGuideInfoViewHook_IconType2_6,
      MapGuideInfoViewHook_IconType2_7,
      MapGuideInfoViewHook_IconType2_8,
      MapGuideInfoViewHook_IconType2_9,
      MapGuideInfoViewHook_IconType2_10,
      MapGuideInfoViewHook_IconType2_11,
      MapGuideInfoViewHook_IconType2_12,
      MapGuideInfoViewHook_IconType2_13,
      MapGuideInfoViewHook_IconType2_14,
      MapGuideInfoViewHook_IconType2_15,
      MapGuideInfoViewHook_IconType2_16,
      MapGuideInfoViewHook_IconType2_17,
      MapGuideInfoViewHook_IconType2_18,
      MapGuideInfoViewHook_IconType2_19,
      MapGuideInfoViewHook_IconType2_20,
      MapGuideInfoViewHook_IconType2_21,
      MapGuideInfoViewHook_IconType2_22,
      MapGuideInfoViewHook_IconType2_23,
      MapGuideInfoViewHook_IconType2_24,
      MapGuideInfoViewHook_IconType2_25,
      MapGuideInfoViewHook_IconType2_26,
      MapGuideInfoViewHook_IconType2_27,
      MapGuideInfoViewHook_IconType2_28,
      MapGuideInfoViewHook_IconType3_1,
      MapGuideInfoViewHook_IconType3_2,
      MapGuideInfoViewHook_IconType3_3,
      MapGuideInfoViewHook_IconType3_4,
      MapGuideInfoViewHook_IconType3_5,
      MapGuideInfoViewHook_IconType4_1,
      MapGuideInfoViewHook_IconType4_2,
      MapGuideInfoViewHook_IconType4_3,
      MapGuideInfoViewHook_IconType4_4,
      MapGuideInfoViewHook_IconType4_5,
      MapGuideInfoViewHook_IconType4_6,
      MapGuideInfoViewHook_IconType4_7,
      MapGuideInfoViewHook_IconType4_8,
      MapGuideInfoViewHook_IconType4_9,
      MapGuideInfoViewHook_IconType4_10,
      MapGuideInfoViewHook_IconType4_11,
      MapGuideInfoViewHook_IconType4_12,
      MapGuideInfoViewHook_IconType4_13,
      MapGuideInfoViewHook_IconType4_14,
      MapGuideInfoViewHook_IconType4_15,
      MapGuideInfoViewHook_IconType4_16,
      MapGuideInfoViewHook_IconType4_17,
      MapGuideInfoViewHook_IconType4_18,
      MapGuideInfoViewHook_IconType4_19,
      MapGuideInfoViewHook_IconType4_20,
      MapGuideInfoViewHook_IconType4_21,
      MapGuideInfoViewHook_IconType4_22,
      MapGuideInfoViewHook_IconType4_23,
      MapGuideInfoViewHook_IconType4_24,
      MapGuideInfoViewHook_IconType4_25,
      MapGuideInfoViewHook_IconType4_26,
      MapGuideInfoViewHook_IconType4_27,
      MapGuideInfoViewHook_IconType4_28,
      MapGuideInfoViewHook_End
    };

    //����·���ж���
    enum RowItem
    {
      ROW1,
      ROW2,
      ROW3,
      ROW4,
      ROW_END,
    };
    CMapGuideInfoViewHook();

    virtual ~CMapGuideInfoViewHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
    /**
    * \���õ�ǰhook�Ƿ���ʾ
    */
    virtual void Show( bool show = true );
    /**
    * \brief ����Hook
    */
    virtual void Update(short type);
    /*
    * ���ø���hook
    */
    void SetParentHook(CAggHook* parentHook);
    /*
    * �����Ƿ���ʾ����·��
    */
    void SetIsShowRouteGuideList(bool show);
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    /**
    * \brief ������������ͼ��
    */
    void HideAllCtrl();
    /**
    * \brief ���µײ�״̬��������Ϣ
    */
    void UpdateGuideInfo(const GuidanceStatus& dirInfo);
    /**
    * \brief ���µ���ʱ��һ��·��Ϣ
    */
    void UpdateNextRouteInfo(const GuidanceStatus& dirInfo);
    /**
    * \brief ���·��򿴰�ͼ��
    */
    void UpdateDirectionBoardInfo(const GuidanceStatus& dirInfo);
    /**
    * \brief ���º���·����Ϣ
    */
    void UpdateRouteGuideInfo(const GuidanceStatus& dirInfo);
    /**
    * \brief �ı�����Ԫ�ص�ͼƬ
    */
    bool ChangeElementIcon(GuiElement* destElement, GuiElement* srcElement);
    /**
    * \brief ��ʾָ��·��ת��ͼ�ؼ�
    */
    void ShowGuidanceIconCtrl(CUiBitButton &iconCtrl, bool isShown = true);
    /**
    * \brief ���ݵ�ǰ������Ϣ��ʾ�ض���ͼ����ʾ(���䴦ͼƬ)
    * \param isShow ��ʾ��������
    */
    void ShowCurGuidanceIcon(bool isShow, int sndCode = 0, unsigned char infoCode = 0, int curPair = -1);
    /**
    * \brief ������һ������Ϣ��ʾ�ض���ͼ����ʾ(���䴦ͼƬ)
    * \param isShow ��ʾ��������
    */
    void ShowNextGuidanceIcon(bool isShow, int sndCode = 0);
    /**
    * \brief ��ʾ·�ڷŴ�ͼ
    */
    void ShowGuideView();
    /**
    * \brief ��ʾ��·�����б�����·�ڣ�
    */
    void ShowRouteGuideList(bool isShow = true);
    /**
    * \brief ��ʾ��·�����б�����·�ڣ�ĳ������
    */
    void ShowRouteGuideData(RowItem row, int sndCode, const char* roadName, double dist);
    /**
    * \brief ��պ���·��ĳ������
    */
    void ClearRouteGuideRow(RowItem row);
    /**
    * \brief ���Ԫ�ص�ͼƬ
    */
    void ClearElementIcon(GuiElement* element);
    /**
    * \brief ���Ԫ�ص�ͼƬ
    */
    bool ChangeCrossingIcon(CUiButton &IconButton, const int sndCode);

  private:
    //��һ��·����
    CUiBitButton m_routeInfoBtn;
    //��ǰ·�ڷ��򿴰�
    CUiBitButton m_curDirectionBoard;
    //��һ·�ڷ��򿴰�
    CUiBitButton m_nextDirectionBoard;
    //���ٿ���
    CUiBitButton m_highSpeedBoard1;
    CUiLabel m_highSpeedBoardTypeLabel1;
    CUiLabel m_highSpeedBoardDistLabel1;
    CUiBitButton m_highSpeedBoard2;
    CUiLabel m_highSpeedBoardTypeLabel2;
    CUiLabel m_highSpeedBoardDistLabel2;
    CUiBitButton m_highSpeedBoard3;
    CUiLabel m_highSpeedBoardTypeLabel3;
    CUiLabel m_highSpeedBoardDistLabel3;
    //����·��
    CUiButton m_routeGuideBack;
    CUiLabel m_routeGuideCurName;
    CUiLabel m_routeGuideName1;
    CUiLabel m_routeGuideName2;
    CUiLabel m_routeGuideName3;
    CUiLabel m_routeGuideName4;
    CUiLabel m_routeGuideDist1;
    CUiLabel m_routeGuideDist2;
    CUiLabel m_routeGuideDist3;
    CUiLabel m_routeGuideDist4;
    CUiButton m_routeGuideIcon1;
    CUiButton m_routeGuideIcon2;
    CUiButton m_routeGuideIcon3;
    CUiButton m_routeGuideIcon4;    
  private:
    // ��hook
    CAggHook* m_parentHook;
    //����·�ڷŴ�ͼ
    CUiBitButton m_shwoGuideViewBtn;
    //·���滮���ʽӿ�
    CRouteWrapper& m_routeWrapper;
    //��ͼ���ʽӿ�
    CViewWrapper& m_viewWrapper;
    //�Ƿ���ʾ����·��
    bool m_isShowRouteGuideList;
  };
}
#endif
