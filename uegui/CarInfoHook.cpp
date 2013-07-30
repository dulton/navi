#include "CarInfoHook.h"
//using namespace UeGui;
#include "InputHook.h"
#include "uebase\pathconfig.h"

namespace UeGui
{

CCarInfoHook::CCarInfoHook():m_pathBasic(CPathBasic::Get())
{
	/*TCHAR path[301]={0, };
	m_pathBasic.GetModulePath(path,300);
	tstring dataPath = path;
	m_filename = dataPath + _T("\\attrs\\carinfo.db");*/
  m_filename = CPathConfig::GetCommonPath(CPathConfig::CPK_AttrsPath);
  //m_pathBasic.GetPathSeperator(m_filename);
  m_filename += _T("carinfo.db");
	getCarInfoFromFile();
}

CCarInfoHook::~CCarInfoHook()
{
	m_elements.clear();
	m_ctrlNames.clear();
	m_imageNames.clear();
}
bool CCarInfoHook::getCarInfoFromFile(void)
{
	HANDLE handleRead;
	// �ļ�������򿪣��������򴴽�
	handleRead=::CreateFile(m_filename.c_str(),GENERIC_READ,0,
		NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (INVALID_HANDLE_VALUE==handleRead)
	{
		return false;
	}
	//��ȡ����
	if (GetFileSize(handleRead,NULL)==sizeof(CarInfoData))
	{
		int irealRWSize=0;
		SetFilePointer(handleRead,0,0,FILE_BEGIN);
		if ( !(ReadFile(handleRead,&m_carInfoData,sizeof(m_carInfoData),(LPDWORD)&irealRWSize,NULL)) )
		{
			return false;
		}
	}
	//�ر��ļ�
	CloseHandle(handleRead);

	return true;
}
bool CCarInfoHook::saveCarInfoToFile(void)
{
	HANDLE handleWrite;
	// �����½�
	handleWrite=::CreateFile(m_filename.c_str(),GENERIC_WRITE,0,
		NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (INVALID_HANDLE_VALUE==handleWrite)
	{
		return false;
	}
	//�����ļ�
	int irealRWSize=0;
	SetFilePointer(handleWrite,0,0,FILE_BEGIN);
	if ( !(WriteFile(handleWrite,&m_carInfoData,sizeof(m_carInfoData),(LPDWORD)&irealRWSize,NULL)) )
	{
		return false;
	}
	//�ر��ļ�
	CloseHandle(handleWrite);
	return true;
}

void CCarInfoHook::MakeGUI()
{
	FetchWithBinary();
	MakeNames();
	MakeControls();
}

void CCarInfoHook::ShowCarInfo()
{
	//���ļ���ȡ��Ϣ
	getCarInfoFromFile();
	//��ʾ
	::sprintf((char *)m_editMid1Ctrl.GetCenterElement()->m_label,
		(char *)m_carInfoData.carLicence);
	::sprintf(m_editMid2Ctrl.GetCenterElement()->m_label,"%.2f ��",m_carInfoData.width);
	::sprintf(m_editMid3Ctrl.GetCenterElement()->m_label,"%.2f ��",m_carInfoData.height);
	::sprintf(m_editMid4Ctrl.GetCenterElement()->m_label,"%.2f ��",m_carInfoData.weight);
}
//item�� �����������������ַ���
void CCarInfoHook::GetInputs(const char* item)
{
	switch(m_Rowtag)
	{
	case CarInfoHook_EditBgk1:
		{
			::sprintf( (char *)m_carInfoData.carLicence, item );
		}
		break;
	case CarInfoHook_EditBgk2:
		{
			m_carInfoData.width = atof(item);
		}
		break;
	case CarInfoHook_EditBgk3:
		{
			m_carInfoData.height = atof(item);
		}
		break;
	case CarInfoHook_EditBgk4:
		{
			m_carInfoData.weight = atof(item);
		}
		break;
	}
	//��itemд�뵽�ļ��б�������
	saveCarInfoToFile();
	ShowCarInfo();
}
void CCarInfoHook::callInputPanel(void* sender, const UeQuery::SQLRecord * data)
{
	if (NULL == sender)
	{
		return;
	}

 	CViewHook::m_curHookType = CViewHook::DHT_VehicleInformationHook;
 	CCarInfoHook* carinfohook = static_cast<CCarInfoHook*>(sender);
 	carinfohook->GetInputs(data->m_asciiName);  

	IView *view = IView::GetView();
	view->RefreshUI();
}

short CCarInfoHook::MouseUp(CGeoPoint<short> &scrPoint)
{
	short ctrlType = CAggHook::MouseUp(scrPoint);
	switch(m_downElementType)
	{
	case CarInfoHook_EditBgk1:	//���ƺ�
	case CarInfoHook_EditBgk2:	//��
	case CarInfoHook_EditBgk3:	//��
	case CarInfoHook_EditBgk4:	//��
		{
			m_editBtnCtrl[m_downElementType-CarInfoHook_EditBgk1].MouseUp();

			const static char* title[4]={"�༭���ƺ�","�༭����","�༭����","�༭������"};
			m_Rowtag = m_downElementType;
			CInputHook::gotoCurInputMethod(
				CInputHook::IM_Edit,
				CViewHook::DHT_VehicleInformationHook,
				this, 
				callInputPanel,	
				title[m_downElementType-CarInfoHook_EditBgk1]	//����
				//m_editMid4Ctrl.GetCaption() //�����������ʱ��Ĭ��ֵ
			); 
		}
		break;
	case CarInfoHook_GotoMapBtn:
		{
			m_gotoMapBtnCtrl.MouseUp();
			if(ctrlType == m_downElementType)
			{
				/*CViewHook::m_prevHookType=CViewHook::m_curHookType;
				CViewHook::m_curHookType=CViewHook::DHT_MapHook;*/
        CViewHook::GoToMapHook();
        ((CAggHook *)m_view->GetHook(CViewHook::DHT_MapHook))->ComeBack();
			}
		}
		break;
	case CarInfoHook_LogicBackBtn:
		{
			m_logicBackBtnCtrl.MouseUp();
			if(ctrlType == m_downElementType)
			{
				/*CViewHook::m_prevHookType = CViewHook::DHT_VehicleInformationHook;
				CViewHook::m_curHookType = CViewHook::DHT_TruckMainMenuHook;*/
        CViewHook::ReturnPrevHook();
			}
		}
		break;
	default:
    {
      m_isNeedRefesh = false;
      assert(false);
    }
    break;
  }
  if (m_isNeedRefesh)
  {
    this->Refresh();
  }
  m_isNeedRefesh = true;
	return ctrlType;
}

short CCarInfoHook::MouseDown(CGeoPoint<short> &scrPoint)
{
	short ctrlType = CAggHook::MouseDown(scrPoint);
	switch(ctrlType)
	{
	case CarInfoHook_EditBgk1:	//���ƺ�
	case CarInfoHook_EditBgk2:	//��
	case CarInfoHook_EditBgk3:	//��
	case CarInfoHook_EditBgk4:	//��
		{
			m_editBtnCtrl[ctrlType-CarInfoHook_EditBgk1].MouseDown();
		}
		break;
	case CarInfoHook_GotoMapBtn:
		{
			m_gotoMapBtnCtrl.MouseDown();
		}
		break;
	case CarInfoHook_LogicBackBtn:
		{
			m_logicBackBtnCtrl.MouseDown();
		}
		break;
	default:
    {
      m_isNeedRefesh = false;
      assert(false);
    }
    break;
  }
  if (m_isNeedRefesh)
  {
    this->Refresh();
  }
  m_isNeedRefesh = true;
	return ctrlType;
}

bool CCarInfoHook::operator ()()
{
	return false;
}

void CCarInfoHook::MakeNames()
{
	m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_BackGround,	"BackGround"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_BGMenuText,	"BGMenuText"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_GotoMapBtn,	"GotoMapBtn"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_LogicBackBtn,	"LogicBackBtn"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_labelTip1,	"labelTip1"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_labelTip2,	"labelTip2"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_LabelCarLicense,	"LabelCarLicense"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_LabelCarWidth,	"LabelCarWidth"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_LabelCarHeight,	"LabelCarHeight"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_LabelCarWeight,	"LabelCarWeight"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditLeft1,	"EditLeft1"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditMid1,	"EditMid1"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditLeft2,	"EditLeft2"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditMid2,	"EditMid2"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditLeft3,	"EditLeft3"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditMid3,	"EditMid3"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditLeft4,	"EditLeft4"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditMid4,	"EditMid4"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditBgk1,	"EditBgk1"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditBgk2,	"EditBgk2"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditBgk3,	"EditBgk3"));
	m_ctrlNames.insert(GuiName::value_type(CarInfoHook_EditBgk4,	"EditBgk4"));
}

void CCarInfoHook::MakeControls()
{
	m_bGMenuTextCtrl.SetCenterElement(GetGuiElement(CarInfoHook_BGMenuText));
	m_backGroundCtrl.SetCenterElement(GetGuiElement(CarInfoHook_BackGround));
	m_editLeft1Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditLeft1));
	m_editLeft2Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditLeft2));
	m_editLeft3Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditLeft3));
	m_editLeft4Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditLeft4));
	m_editMid1Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditMid1));
	m_editMid2Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditMid2));
	m_editMid3Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditMid3));
	m_editMid4Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_EditMid4));
	m_gotoMapBtnCtrl.SetCenterElement(GetGuiElement(CarInfoHook_GotoMapBtn));
	m_logicBackBtnCtrl.SetCenterElement(GetGuiElement(CarInfoHook_LogicBackBtn));
	//	m_labelTip1Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_labelTip1));
	//	m_labelTip2Ctrl.SetCenterElement(GetGuiElement(CarInfoHook_labelTip2));
	for (int i=0;i<4;i++)
	{
		m_editBtnCtrl[i].SetCenterElement(GetGuiElement(CarInfoHook_EditBgk1+i));
	}
	m_bGMenuTextCtrl.SetCaption("������Ϣ");
	ShowCarInfo();
}

}

