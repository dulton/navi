#ifndef _UEGUI_GOODSSOURCEHOOK_H
#define _UEGUI_GOODSSOURCEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

#ifndef _UEGUI_PAGETURNING_H
#include "uipageturningctrl.h"
#endif

// #ifndef _UEGUI_GOODSSOURCEMGR_H
// #include "GoodsSourceMgr.h"
// #endif
#ifndef _UEGUI_FILECONTROLLER_H
#include "FileController.h"
#endif

namespace UeGui
{
	class UEGUI_CLASS CGoodsSourceHook : public CAggHook
	{
	public:
		enum GoodsSourceHookCtrlType
		{
			GoodsSourceHook_Begin = 0,
			GoodsSourceHook_Background,
			GoodsSourceHook_ViewMap,
			GoodsSourceHook_ViewPrevious,
			GoodsSourceHook_NavigationTitle,
			GoodsSourceHook_AreaLeft,
			GoodsSourceHook_AreaCenter,
			GoodsSourceHook_AreaRight,
			GoodsSourceHook_Row1Left,
			GoodsSourceHook_Row1Center,
			GoodsSourceHook_Row1Right,
			GoodsSourceHook_POI1Left,
			GoodsSourceHook_POI1Separater,
			GoodsSourceHook_POI1Right,
			GoodsSourceHook_Row2Left,
			GoodsSourceHook_Row2Center,
			GoodsSourceHook_Row2Right,
			GoodsSourceHook_POI2Left,
			GoodsSourceHook_POI2Separater,
			GoodsSourceHook_POI2Right,
			GoodsSourceHook_Row3Left,
			GoodsSourceHook_Row3Center,
			GoodsSourceHook_Row3Right,
			GoodsSourceHook_POI3Left,
			GoodsSourceHook_POI3Separater,
			GoodsSourceHook_POI3Right,
			GoodsSourceHook_Row4Left,
			GoodsSourceHook_Row4Center,
			GoodsSourceHook_Row4Right,
			GoodsSourceHook_POI4Left,
			GoodsSourceHook_POI4Separater,
			GoodsSourceHook_POI4Right,
			GoodsSourceHook_Row5Left,
			GoodsSourceHook_Row5Center,
			GoodsSourceHook_Row5Right,
			GoodsSourceHook_POI5Left,
			GoodsSourceHook_POI5Separater,
			GoodsSourceHook_POI5Right,
			GoodsSourceHook_NextPage,
			GoodsSourceHook_NextPageIcon,
			GoodsSourceHook_PreviousPage,
			GoodsSourceHook_PreviousPageIcon,
			GoodsSourceHook_PageInfo,
			GoodsSourceHook_End
		};

		static bool gotoGoodsSourceHook();
		CGoodsSourceHook();
		virtual ~CGoodsSourceHook()
		{
			m_elements.clear();
			m_ctrlNames.clear();
			m_imageNames.clear();
		}
		virtual void MakeGUI()
		{
			FetchWithBinary();
			MakeNames();
			MakeControls();
		}
		virtual short MouseDown(CGeoPoint<short> &scrPoint);
		virtual short MouseMove(CGeoPoint<short> &scrPoint){ return -1; }
		virtual short MouseUp(CGeoPoint<short> &scrPoint);
		virtual bool operator ()()
		{
			return false;
		}

		//��ʼ��
		void InitMe();

	protected:
		virtual tstring GetBinaryFileName()
		{
			return _T("goodssourcehook.bin");
		}

		virtual void MakeNames();

		void MakeControls();

	private:
		enum RowTag
		{
			kRow0=0,
			kROW1,
			kROW2,
			kROW3,
			kROW4,
			kRow5,
			kROWEnd
		};

		static void DoDistSwitchCallBack(
			void *pDoCallBackObj,const SQLRecord *pResult);
		//��������ʾ��ĳ����
		void DoShowRowData(RowTag row, const char* value);
		//���ĳһ�У�row=[0.4]
		void ClearARow(RowTag row);
		//���������
		void ClearAllRows();
		//���ݷ�ҳ������÷�ҳ��ť״̬
		void SetNavigatorStatus();

		void setPageInfo(void);
		void showGoodsSourceData();

		//��ҳ������
		CPageTurning m_pageTurning;
		//��¼�������Ŀ���ļ��ж�Ӧ������
		int m_Itemidx;	
		//��¼��ǰѡ����к�
		RowTag m_selectRow;

		//��ַ�������
		unsigned int m_addrCode;
		//CGoodsSourceMgr &m_goodSourceMgr;
		CFileController<GoodsSource> &m_goodSourceMgr;

		//�ؼ�
		const static int NUM_PERPAGE=5;			//�б���Ŀ��
		CUiButton m_listBtnCtrl[NUM_PERPAGE];	//�б�	
		GuiElement *m_poiLeftList[NUM_PERPAGE];	//poi����	
		GuiElement *m_SeparaterList[NUM_PERPAGE];//poi�����������ķָ���	
		GuiElement *m_poiRightList[NUM_PERPAGE];//poi������Ϣ

		CUiButton m_navigationTitleCtrl;
		CUiButton m_viewMapCtrl;
		CUiButton m_viewPreviousCtrl;
		CUiButton m_pageInfoCtrl;

		CUiBitButton m_previousPageCtrl;
		CUiBitButton m_nextPageCtrl;

		CUiBitButton m_areaBtnCtrl;
	};
}
#endif
