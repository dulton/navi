#include "foursshopmgr.h"
#include "uemap\view.h"
#include "ddtservice4shook.h"
#include "ddtservicequerylisthook.h"
#include "gui.h"
#include <algorithm>
#include "maphook.h"
#include "assistant.h"
#include "uebase\pathconfig.h"


using namespace UeGui;
using namespace UeBase;

CFourSShopMgr::CFourSShopMgr(void)
{

}

CFourSShopMgr::~CFourSShopMgr(void)
{
  ReleaseData();

}



vector<CFourSShopMgr::FourSFileBlock*> CFourSShopMgr::m_mainVec;

vector<CFourSShopMgr::FourSList*> CFourSShopMgr::m_list;


void CFourSShopMgr::ReadFile(const unsigned int distCode,FourSCarType type)
{
  
  
  const CPathBasic& pathBasic = CPathBasic::Get();
  /*
  TCHAR path[CPathBasic::MAXPATHLENGTH] = {0,};
  pathBasic.GetModulePath(path,CPathBasic::MAXPATHLENGTH);
  tstring mainFile = path;
  pathBasic.GetPathSeperator(mainFile);
  mainFile += _T("attrs");*/

  tstring mainFile = CPathConfig::GetCommonPath(CPathConfig::CPK_AttrsPath);
  //pathBasic.GetPathSeperator(mainFile);
  mainFile += _T("foursshop");
  pathBasic.GetPathSeperator(mainFile);

  tstring nameFile = CPathConfig::GetCommonPath(CPathConfig::CPK_AttrsPath);
  /*pathBasic.GetPathSeperator(nameFile);
  nameFile += _T("attrs");*/
  //pathBasic.GetPathSeperator(nameFile);
  nameFile += _T("foursshop");
  pathBasic.GetPathSeperator(nameFile);
  switch (type)
  {
  case FourSCarType_Benze:
    mainFile += _T("benze.dk");
    nameFile += _T("benzenames.dk");
    break;
  case FourSCarType_Honda:
    mainFile += _T("honda.dk");
    nameFile += _T("hondanames.dk");
    break;
  case FourSCarType_Toyota:
    mainFile += _T("toyota.dk");
    nameFile += _T("toyotanames.dk");
    break;
  case FourSCarType_ChangCheng:
    mainFile += _T("changcheng.dk");
    nameFile += _T("changchengnames.dk");
    break;
  default:
    assert(false && !"�����ڴ���������");
    break;
  }
  //�����֮ǰ������
  ReleaseData();
  ReadMainFile(mainFile,distCode);
  PackData(nameFile);
}



void CFourSShopMgr::ReleaseData()
{
  int size = m_mainVec.size();
  for (int i = 0; i < size; i++)
  {
    delete m_mainVec[i];
  }
  m_mainVec.clear();
  size = m_list.size();
  for (int i = 0; i < size; i++)
  {
    delete m_list[i];
  }
  m_list.clear();
}

void CFourSShopMgr::ReadMainFile(const tstring& mainFileName, const unsigned int distCode)
{

  CSimpleFileReader fileReader(mainFileName,sizeof(FourSFileBlock));
  fileReader.ConnectFile();
  unsigned int size = fileReader.GetDataCount();
  for(int i=0; i < size; i++)
  {
    FourSFileBlock* fss = new FourSFileBlock();
    unsigned int readSize = 0;
    ::memcpy(fss,fileReader.GetBlockData(i,readSize), sizeof(FourSFileBlock));
    //long x = fss->m_x * 100000;
    //long y = fss->m_y * 100000;
    //unsigned int code = CDistAndTypeHook::GetDistCode(x, y);
    //if ((code/100) == (distCode/100))
    if (CAssistant::IsBelongTo(fss->m_distCode,distCode))
    {
      m_mainVec.push_back(fss);
    }
  }
  fileReader.DisconnectFile();

}

void CFourSShopMgr::PackData(const tstring& nameFileName)
{
  const CFileBasic& fileBasic = CFileBasic::Get();
  void *nameHandle = fileBasic.OpenFile(nameFileName, CFileBasic::UE_FILE_READ);
  assert(nameHandle && fileBasic.IsValidHandle(nameHandle));
  if(!fileBasic.IsValidHandle(nameHandle))
  {
    return;
  }

  int size = m_mainVec.size();
  unsigned char length = 0;
  for (int i = 0; i < size; i++)
  {
    long x = m_mainVec[i]->m_x * 100000;
    long y = m_mainVec[i]->m_y * 100000;
    FourSList* fsl = new FourSList();
    int count = 1;
    void *ptr = &length;
    fileBasic.SeekFile(nameHandle, m_mainVec[i]->m_offSet, CFileBasic::UE_SEEK_BEGIN);
    fileBasic.ReadFile(nameHandle, &ptr, sizeof(unsigned char), count);
    count = length;
    ptr = fsl->m_name;
    fileBasic.ReadFile(nameHandle, &ptr, sizeof(unsigned char), count);
    fsl->m_point.m_x = x;
    fsl->m_point.m_y = y;

    IGui* gui = IGui::GetGui();
    gui->GetDistrictName(fsl->m_point, fsl->m_distName);

    m_list.push_back(fsl);
  }

  fileBasic.CloseFile(nameHandle);
}



void CFourSShopMgr::Open4SShopeHook()
{
  IView* view = IView::GetView();
  CDdtService4SHook* serviceQueryHook = dynamic_cast<CDdtService4SHook*>(view->GetHook(CViewHook::DHT_DdtService4SHook));
  serviceQueryHook->Clear();
  serviceQueryHook->SetTitle("4S��");
  serviceQueryHook->SetQueryArea("������");
  serviceQueryHook->SetQueryAreaCode(2883840);
  serviceQueryHook->SetTypeContent("��4S��");
  serviceQueryHook->SetCarListQueryEvent(&UeGui::CFourSShopMgr::On4SShopListQuery);

  serviceQueryHook->AddServiceData("����", FourSCarType_Benze);
  serviceQueryHook->AddServiceData("���ݱ���", FourSCarType_Honda);
  serviceQueryHook->AddServiceData("����", FourSCarType_ChangCheng);

  serviceQueryHook->ShowData();
  view->RefreshUI();
}

//4S����괥���¼�
void UeGui::CFourSShopMgr::On4SShopListQuery( const unsigned int distCode, FourSCarType type)
{
  //ע�⣺���ڸ÷���Ϊ��̬��Ա���������޷����ʱ���ĳ�Ա������:m_view �� ����ͨ���������ʽ����
  IView *view = IView::GetView();
  CDdtServiceQueryListHook* serviceQueryListHook = dynamic_cast<CDdtServiceQueryListHook*>(view->GetHook(CViewHook::DHT_DdtServiceQueryListHook));
  serviceQueryListHook->Clear();
  serviceQueryListHook->SetReturnEvent(&UeGui::CFourSShopMgr::On4SShopListHookReturn);
  serviceQueryListHook->SetPOIQueryEvent(&UeGui::CFourSShopMgr::On4SShopListHookPOISelect);
  serviceQueryListHook->SetTitle("4S��");
  ReadFile(distCode,type);
  int count = m_list.size();
  for (int i = 0; i < count; i++)
  {
    serviceQueryListHook->AddData(m_list[i]->m_name, m_list[i]->m_distName,m_list[i]->m_point);
  }
  //serviceQueryListHook->AddData("�㶫�±�����ó�����޹�˾", "�����");
  //serviceQueryListHook->AddData("���ݹڻ��������۷������޹�˾", "��خ",CGeoPoint<long> point(2938,3094));
  //serviceQueryListHook->AddData("���ݺϸ������������۷������޹�˾", "�����",CGeoPoint<long> point(2938,3094));
  //serviceQueryListHook->AddData("�����ʻ��������۷������޹�˾", "������",CGeoPoint<long> point(2938,3094));
  //serviceQueryListHook->AddData("���ݴ�����ó�����޹�˾", "�����");
  //serviceQueryListHook->AddData("�㶫÷������ó�����޹�˾", "������");
  //serviceQueryListHook->AddData("�㶫�齭��Լ����ó�����޹�˾", "�����");
  //serviceQueryListHook->AddData("�㶫��Ӫ����ó�����޹�˾", "Խ����");
  //serviceQueryListHook->AddData("�㶫��������ó�����޹�˾", "�����");
  serviceQueryListHook->ShowData();
  /*CViewHook::m_prevHookType = CViewHook::m_curHookType;
  CViewHook::m_curHookType = CViewHook::DHT_DdtServiceQueryListHook;*/
//  CAggHook::TurnToHook(CViewHook::DHT_DdtServiceQueryListHook);

  view->RefreshUI();
}


//4S���ѯ����б�hook�ķ����¼�
void UeGui::CFourSShopMgr::On4SShopListHookReturn()
{
  /*CViewHook::m_prevHookType = CViewHook::DHT_DdtserviceHook;
  CViewHook::m_curHookType = CViewHook::DHT_DdtService4SHook;*/
//  CAggHook::TurnToHook(CViewHook::DHT_DdtService4SHook);
}

//4S���ѯ����б�hook��POIѡ���¼�
void UeGui::CFourSShopMgr::On4SShopListHookPOISelect( const char* keyValue1, const char* keyValue2,const CGeoPoint<long>& point)
{
  
  IView* view = IView::GetView();
  CMapHook* mapHook = (CMapHook*)(view->GetHook(CViewHook::DHT_MapHook));
  mapHook->GoToPosFromList(point, keyValue1);
  
}


