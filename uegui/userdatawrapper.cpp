#include "userdatawrapper.h"

#include "uebase\timebasic.h"
using namespace UeBase;

#include "uemap\viewhook.h"
using namespace UeMap;

#include "uemodel\network.h"
#include "uemodel\netnametable.h"
using namespace UeModel;

//#include "myjourneyhook.h"
#include "myjourneywrapper.h"
#include "settingwrapper.h"
#include "messagedialoghook.h"
#include "maphook.h"
#include "uebase\pathconfig.h"

using namespace UeGui;
using namespace UeBase;

const CUserDataWrapper& CUserDataWrapper::Get()
{
  static CUserDataWrapper m_userDataWrapper;
  return m_userDataWrapper;
}

CUserDataWrapper::CUserDataWrapper() : m_view(IView::GetView()), m_route(IRoute::GetRoute()),
m_query(IQuery::GetQuery()),m_net(IRoadNetwork::GetNetwork()),m_pathBasic(CPathBasic::Get()),
m_fileBasic(CFileBasic::Get())
{
  m_usuallyFile = new CUsuallyFile();
}

CUserDataWrapper::~CUserDataWrapper()
{
  if (m_usuallyFile)
  {
    delete m_usuallyFile;
    m_usuallyFile = NULL;
  }
}

int CUserDataWrapper::GetHistoryRecordCount() const
{
  int count = 0;
  if (m_query && ConnectToHistoryRecord() == UeQuery::SQL_Success)
  {
    count = m_query->GetHistoryRecordCount();
    DisconnectHistoryRecord();
  }
  return count;
}

int CUserDataWrapper::GetFavoriteCount() const
{
  int count = 0;
  if (m_query && ConnectToFavorite() == UeQuery::SQL_Success)
  {
    count = m_query->GetFavoriteCount();
    DisconnectFavorite();
  }
  return count;
}

int CUserDataWrapper::GetRecentCount() const
{
  int count = 0;
  if (m_query && ConnectToRecent() == UeQuery::SQL_Success)
  {
    count = m_query->GetRecentCount();
    DisconnectRecent();
  }
  return count;
}

int CUserDataWrapper::GetJourneyCount() const
{
  int count = 0;
  if (m_view)
  {
    CMyJourneyWrapper jurneyWrapper;
    count = jurneyWrapper.GetJourneyCount();
  }
  return count;
}

void CUserDataWrapper::AddHistoryPoint(UeRoute::PlanPosition& pos) const
{

  if (!pos.IsValid())
  { 
    return;
  }
  ConnectToHistoryRecord();
  int count = m_query->GetHistoryRecordCount();
  CSettingWrapper &settingWrapper = CSettingWrapper::Get();
  int maxCount = settingWrapper.GetHistoryRecordCapacity();
  if (count >= maxCount)
  {
    m_query->RemoveHistoryRocord(--count);
  }
  DisconnectHistoryRecord();

  HistoryRecordEntry entry;
  entry.m_X = pos.m_pos.m_x;
  entry.m_Y = pos.m_pos.m_y;
  if (pos.m_name[0])
  {
    //TODO:����һ�㲻�ᳬ��32����
    const CStringBasic& stringBasic = CStringBasic::Get();
    ::strcpy(reinterpret_cast<char *>(entry.m_addrName),stringBasic.TrimSpace(reinterpret_cast<char *>(pos.m_name)));
  }
  else 
  {
    ::strcpy((char*)entry.m_addrName, "δ����");
  }

  ConnectToHistoryRecord();
  for (int i=0; i < count ; i++)
  {
    const HistoryRecordEntry* curEntry = m_query->GetHistoryRecord(i);
    if (entry.m_X==curEntry->m_X
      && entry.m_Y==curEntry->m_Y
      && ::strcmp(reinterpret_cast<const char *>(entry.m_addrName),
      reinterpret_cast<const char *>(curEntry->m_addrName))==0)
    {
      DisconnectHistoryRecord();
      return;
    }
  }
  m_query->AddHistoryRecord(entry);  
  DisconnectHistoryRecord();
}

void CUserDataWrapper::AddHistoryPoint(UeRoute::PositionType type) const
{
  PlanPosition pos;
  pos.m_type = type;
  if (type == UeRoute::PT_Start || type == UeRoute::PT_End || type == UeRoute::PT_Middle)
  {
    if (UeRoute::PEC_Success == m_route->GetPosition(pos) )
    {
      AddHistoryPoint(pos);
    }
  }
}

//�����ʷ·������
void CUserDataWrapper::AddRecent() const
{
  assert(m_route && m_query);
  unsigned int posCount = m_route->GetPosCount();

  RecentEntry entry;
  entry.m_routePosCnt = posCount;

  PlanPosition startPos;
  startPos.m_type = UeRoute::PT_Start;
  m_route->GetPosition(startPos);
  if(!startPos.IsValid())
  {
    return;
  }

  entry.m_routePos[0].m_X = startPos.m_pos.m_x;
  entry.m_routePos[0].m_Y = startPos.m_pos.m_y;
  SetAddrName(startPos, (char *)entry.m_routePos[0].m_addrName);

  int count = GetRecentCount();
  
  CSettingWrapper &settingWrapper = CSettingWrapper::Get();
  int maxCount = settingWrapper.GetHistoryRouteCapacity();
  if (count >= maxCount)   
  {
    m_query->RemoveRecent(--count);
  }

  //���ھ��ɵ�
  if (posCount > 2)
  {
    for (int i = 1; i < posCount - 1; ++i)
    {
      PlanPosition middlePos;
      middlePos.m_type = UeRoute::PT_Middle;

      m_route->GetPosition(middlePos, i);
      if (!middlePos.IsValid())
      {
        return;
      }
      entry.m_routePos[i].m_X = middlePos.m_pos.m_x;
      entry.m_routePos[i].m_Y = middlePos.m_pos.m_y;
      SetAddrName(middlePos, (char *)entry.m_routePos[i].m_addrName);
    }

  }

  // If it is already capture GPS signal or set start position, it no need start set cmd
  PlanPosition endPos;
  endPos.m_type = UeRoute::PT_End;
  m_route->GetPosition(endPos);
  if(!endPos.IsValid())
  {
    return;
  }
  entry.m_routePos[entry.m_routePosCnt-1].m_X = endPos.m_pos.m_x;
  entry.m_routePos[entry.m_routePosCnt-1].m_Y = endPos.m_pos.m_y;

  SetAddrName(endPos, (char *)entry.m_routePos[entry.m_routePosCnt-1].m_addrName);
  CTimeBasic::TimeReport timeReport = {};
  CTimeBasic timeBasic;
  entry.m_timeStamp = timeBasic.GetNow(timeReport);
  ::strcpy((char *)entry.m_recentName, "��ʷ·��");
  entry.m_routeMode = m_route->GetMethod();
  //  //��鵱ǰ·���Ƿ��Ѿ����ڣ���������򲻱���
  if (!CheckHistoryRouteExists(entry))
  {
    m_query->AddRecent(entry);
  }  
}


bool CUserDataWrapper::AddJourneyData(const char *journeyName, unsigned int routeType, const POIDataList &poiList) const
{
  CMyJourneyWrapper journeyWrapper;
  return journeyWrapper.AddJourneyData(journeyName, routeType, poiList);
}


void CUserDataWrapper::RemoveUsually(UsuallyRecordType n) const
{
  m_usuallyFile->RemoveRecord(n);
}

int CUserDataWrapper::GetUsuallyRecord(UsuallyRecordType n , UsuallyRecord* record) const
{
  return m_usuallyFile->GetRecord(n, record);
}

int CUserDataWrapper::UpdateUsuallyRecord(UsuallyRecordType n , UsuallyRecord* record) const
{
  return m_usuallyFile->UpdateRecord(n, record);
}

bool CUserDataWrapper::IsUsuallyExist(UsuallyRecordType type) const
{
  return m_usuallyFile->IsUsuallyExist(type);
}

void CUserDataWrapper::SetAddrName(const PlanPosition& planPos, char *addrName) const
{
  if (addrName)
  {
    if(planPos.m_name && ::strlen(planPos.m_name))
    {
      ::strcpy(addrName, (char *)planPos.m_name);
    }
    else
    {
      if(planPos.m_nameOffset)
      {
        short tCount = 0;
        char *name = 0;
        m_net->GetNameTable(UeModel::UNT_Network)->GetContent(planPos.m_nameOffset, &name, tCount);
        ::strcpy(addrName, name);
      }
      else
      {
        ::strcpy(addrName, "һ���·");
      }
    }
  }
}

bool CUserDataWrapper::CheckHistoryRouteExists( const RecentEntry& newEntry ) const
{
  //���·���Ƿ��ظ��������ǱȽϾ�γ�Ⱥ�����
  bool isExists = false;
  if (m_query)
  {
    ConnectToRecent();
    int dataCount = m_query->GetRecentCount();
    for(int i = 0; i < dataCount; i++)
    {
      const RecentEntry *curEntry = m_query->GetRecent(i);
      if (curEntry && curEntry->IsSameWith(newEntry))
      {
        isExists = true;
        break;
      }      
    }
    DisconnectRecent();
  }
  return isExists;
}

void CUserDataWrapper::HistoryRoutePlan(int dataIndex) const
{
  ConnectToRecent();
  const RecentEntry *tempEntry = m_query->GetRecent(dataIndex);
  //��ΪDisconnect����ͷŵ�tempEntry����������Ҫ����һ������
  RecentEntry curEntry;
  ::memcpy(&curEntry, tempEntry, sizeof(RecentEntry));
  DisconnectRecent();

  //��·����ɾ��·��
  if (m_route->GetPlanState() != UeRoute::PS_None)
  {
    m_route->SetBlock(true);
    m_route->Prepare();
  }

  //////////////////////////////////////////////////////////////////////////
  unsigned int rt = PEC_Success;
  CGeoPoint<short> scrPoint;
  CGeoPoint<long> point;

  //�����
  PlanPosition startPos;
  startPos.m_type = PT_Start;
  startPos.m_pos.m_x = curEntry.m_routePos[0].m_X;
  startPos.m_pos.m_y = curEntry.m_routePos[0].m_Y;
  startPos.m_isGPS = false;
  ::strcpy(startPos.m_name, (char*)curEntry.m_routePos[0].m_addrName);
  if (rt = m_route->SetPosition(startPos) != PEC_Success)
  {
    return;
  }

  //��Ŀ�ĵ�
  PlanPosition endPos;
  endPos.m_type = PT_End;
  endPos.m_pos.m_x = curEntry.m_routePos[curEntry.m_routePosCnt-1].m_X;
  endPos.m_pos.m_y = curEntry.m_routePos[curEntry.m_routePosCnt-1].m_Y;
  endPos.m_isGPS = false;
  ::strcpy(endPos.m_name, (char*)curEntry.m_routePos[curEntry.m_routePosCnt-1].m_addrName);
  if (rt = m_route->SetPosition(endPos) != PEC_Success)
  {
    return;
  }

  //���þ��ɵ�
  for (int i = 1; i < curEntry.m_routePosCnt - 1; ++i)
  {
    PlanPosition middlePos;
    middlePos.m_type = PT_Middle;
    middlePos.m_pos.m_x = curEntry.m_routePos[i].m_X;
    middlePos.m_pos.m_y = curEntry.m_routePos[i].m_Y;
    middlePos.m_isGPS = false;
    ::strcpy(middlePos.m_name, (char*)curEntry.m_routePos[i].m_addrName);
    if (rt = m_route->SetPosition(middlePos) != PEC_Success)
    {
      return;
    }
  }

  //���ù滮��ʽ
  unsigned int status = 0;
  unsigned int planMethod = curEntry.m_routeMode;
  status = m_route->SetMethod(curEntry.m_routeMode);
  status = m_route->IsReadyForPlanning();
  if ((status | PEC_Success) != PEC_Success)
  {
    m_route->RemovePosition();
    return;
  }

  CMessageDialogEvent dialogEvent(NULL, CViewHook::DHT_MapHook, NULL);
  CMessageDialogHook::ShowMessageDialog(MB_NONE, "�滮�У����Ժ�...", dialogEvent); 
  CMessageDialogHook::CloseMessageDialog();

  rt = m_route->RoutePlan(false);
  if (UeRoute::PEC_TooShortest == rt)
  {
    CMessageDialogHook::ShowMessageDialog(MB_NONE, "����Ŀ�ĵؾ���̫��", dialogEvent, 2);
  }
  else
  {
    if (rt == UeRoute::PEC_Success)
    {
      //�л���·�߹滮�ɹ�����ʱ����
      CMapHook* mapHook = (CMapHook*)m_view->GetHook(CViewHook::DHT_MapHook);
      if (mapHook)
      {
        //        CAggHook::TurnToHook(CViewHook::DHT_MapHook);
        mapHook->OverviewRoute();
        m_view->Refresh();
      }
    }
    else
    {
      CMessageDialogHook::ShowMessageDialog(MB_NONE, "·���滮ʧ��", dialogEvent, 2);
      m_route->RemovePosition();
    }
  }
}

//ɾ������Ϊorder�ļ�¼
unsigned int CUserDataWrapper::RemoveFavorite(int order) const
{
  return m_query->RemoveFavorite(order);
}
//��ȡ����Ϊorder�ĵ�ַ��Ϣ
const FavoriteEntry* CUserDataWrapper::GetFavorite(int order) const
{
  return m_query->GetFavorite(order);
}
//����µĵ�ַ��Ϣ
unsigned int CUserDataWrapper::AddFavorite(const FavoriteEntry &curFavor) const
{
  return m_query->AddFavorite(curFavor);
}
//��������Ϊorder�ĵ�ַ��Ϣ
unsigned int CUserDataWrapper::UpdateFavorite(const FavoriteEntry &curFavor,int order) const
{
  return m_query->UpdateFavorite(curFavor, order);
}

//��ȡ����Ϊorder����ʷ��·��Ϣ
const RecentEntry* CUserDataWrapper::GetRecent(int order) const
{
  return m_query->GetRecent(order);
}
//ɾ������Ϊorder����ʷ��·��Ϣ
unsigned int CUserDataWrapper::RemoveRecent(int order) const
{
  return m_query->RemoveRecent(order);
}
//��������Ϊorder����ʷ��·��Ϣ
unsigned int CUserDataWrapper::UpdateRecent(const RecentEntry &curRecent,int order) const
{
  return m_query->UpdateRecent(curRecent, order);
}

//��ȡ����Ϊorder����ʷ��¼
const HistoryRecordEntry* CUserDataWrapper::GetHistoryRecord (int order) const
{
  return m_query->GetHistoryRecord(order);
}
//���һ����ʷ��¼
unsigned int CUserDataWrapper::AddHistoryRecord (const HistoryRecordEntry &curHisRecord) const
{
  return m_query->AddHistoryRecord(curHisRecord);
}
//ɾ������Ϊorder����ʷ��¼
unsigned int CUserDataWrapper::RemoveHistoryRocord(int order) const
{
  return m_query->RemoveHistoryRocord(order);
}
//ɾ��������ʷ��¼
unsigned int CUserDataWrapper::RemoveAllHistoryRecord() const
{
  return m_query->RemoveAllHistoryRecord();
}
//��������Ϊorder����ʷ��¼
unsigned int CUserDataWrapper::UpdateHistoryRecord(const HistoryRecordEntry &curHisRecord,int order) const
{
  return m_query->UpdateHistoryRecord(curHisRecord, order);
}

void CUserDataWrapper::RemoveAllRecent() const
{
  if (m_query && ConnectToRecent() == UeQuery::SQL_Success)
  {
    int count = m_query->GetRecentCount();
    for(int i = count - 1; i >= 0; i--)
    {
      RemoveRecent(i);
    }
    DisconnectRecent();
  }
}

void CUserDataWrapper::RemoveAllFavorite() const
{
  if (m_query && ConnectToFavorite() == UeQuery::SQL_Success)
  {
    int count = m_query->GetFavoriteCount();
    for (int i = count - 1; i >= 0; i--)
    {
      RemoveFavorite(i);
    }
    DisconnectFavorite();
  }
}

void CUserDataWrapper::RemoveAllJourney() const
{
  CMyJourneyWrapper jurneyWrapper;
  jurneyWrapper.RemoveAllJourney();
}

bool CUserDataWrapper::GetRecentName(unsigned int index, char *recentName) const
{
  if (recentName)
  {
    if(SQL_Success == ConnectToRecent())
    {
      const RecentEntry *curEntry = GetRecent(index);
      if (curEntry)
      {
        ::strcpy(recentName, curEntry->m_recentName);
        DisconnectRecent();
        return true;
      }
      DisconnectRecent();
    } 
  }
  return false;
}

void CUserDataWrapper::EditHistoryRouteData(unsigned int index, const char* routeName) const
{
  ConnectToRecent();
  const RecentEntry *curEntry = GetRecent(index);
  RecentEntry newRecent;
  ::memcpy(&newRecent, curEntry, sizeof(RecentEntry));
  size_t srclen = ::strlen(routeName);
  size_t destlen = sizeof(newRecent.m_recentName) - 1;
  size_t copyLen = destlen > srclen ? srclen : destlen;
  ::strcpy(newRecent.m_recentName, routeName);  
  DisconnectRecent();

  UpdateRecent(newRecent, index);
}

bool CUserDataWrapper::FavoriteEntry2EditData(const FavoriteEntry* fEntry , EditData* edata) const
{
  if (fEntry == NULL || edata == NULL)
  {
    return false;
  }
  edata->m_x = fEntry->m_x;
  edata->m_y = fEntry->m_y;
  ::strcpy((char *)edata->m_name, (char *)fEntry->m_name);

  if (fEntry->m_telphone != NULL)
  {
    char *tmp = new char[128];
    ::strcpy((char *)edata->m_telephone, (char*)fEntry->m_telphone);
    delete []tmp;
  }
  else
  {
    ::strcpy((char *)edata->m_telephone, "");
  }

  if (fEntry->m_addr != NULL)
  {
    char *tmp = new char[128];
    ::strcpy((char *)edata->m_addrCode, (char*)fEntry->m_addr);
    delete []tmp;
  }
  else
  {
    ::strcpy((char *)edata->m_addrCode, "");
  }

  if(fEntry->m_kind & 0x1)
  {
    edata->m_isStartpos = true;
  }
  else
  {
    edata->m_isStartpos = false;
  }

  unsigned short entryKind = fEntry->m_kind >> 1;
  if (entryKind & 0x1)
  {
    edata->m_isVoice = true;
  }
  else
  {
    edata->m_isVoice = false;
  }
  entryKind = entryKind >> 1;

  if (entryKind & 0x1)
  {
    edata->m_isMapshow = true;
  }
  else
  {
    edata->m_isMapshow = false;
  }
  entryKind = entryKind >> 1;

  edata->m_kind = fEntry->m_kind;
  return true;
}

bool CUserDataWrapper::EditData2FavoriteEntry(EditData* edata, FavoriteEntry* fEntry) const
{
  if (edata == NULL || fEntry == NULL)
  {
    return false;
  }
  fEntry->m_x = edata->m_x;
  fEntry->m_y = edata->m_y;
  ::strcpy((char *)fEntry->m_name, (char *)edata->m_name);
  fEntry->m_teleNumber = ::atoi((char *)edata->m_telephone);
  ::strcpy((char*)fEntry->m_addr, (char *)edata->m_addrCode);
  ::strcpy((char*)fEntry->m_telphone, (char *)edata->m_telephone);

  //������־λ������
  edata->m_kind = edata->m_kind<<3;
  if (edata->m_isMapshow)
  {
    edata->m_kind |= 0x4;
  }
  if(edata->m_isVoice)
  {
    edata->m_kind |= 0x2;
  }
  if(edata->m_isStartpos)
  {
    edata->m_kind |= 0x1;
  }
  fEntry->m_kind = edata->m_kind;
  return true;
}

unsigned int CUserDataWrapper::ConnectToRecent(void) const
{
  return m_query->ConnectTo(UeQuery::DT_Recents, setting);
}
unsigned int CUserDataWrapper::DisconnectRecent(void) const
{
  return m_query->Disconnect(UeQuery::DT_Recents);
}
//��ַ��
unsigned int CUserDataWrapper::ConnectToFavorite(void) const
{
  return m_query->ConnectTo(UeQuery::DT_Favorite,setting);
}
unsigned int CUserDataWrapper::DisconnectFavorite(void) const
{
  return m_query->Disconnect(UeQuery::DT_Favorite);
}
//
unsigned int CUserDataWrapper::ConnectToHistoryRecord(void) const
{
  return m_query->ConnectTo(UeQuery::DT_HistoryRecords, setting);
}
unsigned int CUserDataWrapper::DisconnectHistoryRecord(void) const
{
  return m_query->Disconnect(UeQuery::DT_HistoryRecords);
}

tstring UeGui::CUserDataWrapper::GetLastRouteBackFilename() const
{
  tstring fileName;
  fileName = CPathConfig::GetCommonPath(CPathConfig::CPK_UserPath);
  fileName += _T("lastroute.db");
  return fileName;
}

bool UeGui::CUserDataWrapper::SaveLastRoute() const
{
  if (NULL == m_route)
  {
    return false;
  }
  short planStatue = m_route->GetPlanState();
  if ((UeRoute::PS_Ready == planStatue) || (UeRoute::PS_RealGuidance == planStatue))
  {
    //·������:�Ƽ�·��,��������,���·��,����·��
    unsigned int routeType = m_route->GetMethod();
    //·�ߵľ��ɵ��±�0Ϊ��㣬Ŀǰ���������յ��ܹ�������6�����ɵ㡣
    POIDataList poiList;
    poiList.clear();
    //��ȡ���
    POIItem poiItem;
    poiItem.m_type = UeRoute::PT_Start;
    m_route->GetPosition(poiItem);
    if(poiItem.m_type != UeRoute::PT_Invalid)
    {
      poiList.push_back(poiItem);
    }
    //��ȡ�м侭�ɵ�
    unsigned int posCount = m_route->GetPosCount();
    if(posCount > 2)
    {
      ::memset(&poiItem, 0, sizeof(POIItem));
      poiItem.m_type = UeRoute::PT_Middle;
      for(int i = 1; i < posCount - 1; i++)
      {
        m_route->GetPosition(poiItem, i);
        if(poiItem.m_type != UeRoute::PT_Invalid)
        {
          poiList.push_back(poiItem);
        }
      }
    }
    //��ȡ�յ�
    ::memset(&poiItem, 0, sizeof(POIItem));
    poiItem.m_type = UeRoute::PT_End;
    m_route->GetPosition(poiItem);
    if(poiItem.m_type != UeRoute::PT_Invalid)
    {
      poiList.push_back(poiItem);
    }

    tstring fileName = GetLastRouteBackFilename();
    void *fileHandle = m_fileBasic.OpenFile(fileName, CFileBasic::UE_FILE_WRITE);
    if(!m_fileBasic.IsValidHandle(fileHandle))
    {
      m_fileBasic.CloseFile(fileHandle);
      return false;
    }

    m_fileBasic.SeekFile(fileHandle, 0, CFileBasic::UE_SEEK_BEGIN);
    //��дһ���Ƿ���δ�������·�ߵı�ʶ
    int count = 1;
    short tag = 1;
    m_fileBasic.WriteFile(fileHandle, &tag, sizeof(tag), count);
    //д·�߹滮����
    m_fileBasic.WriteFile(fileHandle, &routeType, sizeof(routeType), count);
    //��д��ǰ�ж��ٸ�������
    unsigned int dataCount = poiList.size();
    m_fileBasic.WriteFile(fileHandle, &dataCount, sizeof(dataCount), count);
    //д��·�߸����ɵ�
    for (int i = 0; i < poiList.size(); ++i)
    {
      m_fileBasic.WriteFile(fileHandle, &poiList[i], sizeof(POIItem), count);
    }
    m_fileBasic.CloseFile(fileHandle);
  }
  return false;
}

bool UeGui::CUserDataWrapper::GetLastRoute( unsigned int& routeType, POIDataList &poiList ) const
{
  poiList.clear();
  tstring fileName = GetLastRouteBackFilename();
  void *fileHandle = NULL;
  if(m_pathBasic.IsFileExist(fileName))
  {
    fileHandle = m_fileBasic.OpenFile(fileName, CFileBasic::UE_FILE_READ);
  }
  else
  {
    return false;
  }

  if(!m_fileBasic.IsValidHandle(fileHandle))
  {
    m_fileBasic.CloseFile(fileHandle);
    return false;
  }
  m_fileBasic.SeekFile(fileHandle, 0, CFileBasic::UE_SEEK_BEGIN);
  //�ȶ�ȡ�Ƿ���δ�������·�ߵı�ʶ
  int count = 1;
  short tag = 0;
  void *buffer = &tag;
  m_fileBasic.ReadFile(fileHandle, &buffer, sizeof(short), count);
  bool bHaveLastRoute = 1 == tag;
  if (bHaveLastRoute)
  {
    unsigned int routeType = 0;
    unsigned int dataCount = 0;
    buffer = &routeType;
    m_fileBasic.ReadFile(fileHandle, &buffer, sizeof(unsigned int), count);
    buffer = &dataCount;
    m_fileBasic.ReadFile(fileHandle, &buffer, sizeof(unsigned int), count);
    POIItem poiItem;
    for (int i = 0; i < dataCount; ++i)
    {
      ::memset(&poiItem, 0, sizeof(POIItem));
      buffer = &poiItem;
      m_fileBasic.ReadFile(fileHandle, &buffer, sizeof(POIItem), count);
      poiList.push_back(poiItem);
    }
  }
  m_fileBasic.CloseFile(fileHandle);
  return bHaveLastRoute;
}

bool UeGui::CUserDataWrapper::ClearLastRoute() const
{
  tstring fileName = GetLastRouteBackFilename();
  void *fileHandle = NULL;
  if(m_pathBasic.IsFileExist(fileName))
  {
    fileHandle = m_fileBasic.OpenFile(fileName, CFileBasic::UE_FILE_WRITE);
  }
  else
  {
    return true;
  }

  if(!m_fileBasic.IsValidHandle(fileHandle))
  {
    m_fileBasic.CloseFile(fileHandle);
    return false;
  }
  m_fileBasic.SeekFile(fileHandle, 0, CFileBasic::UE_SEEK_BEGIN);
  //��дһ���Ƿ���δ�������·�ߵı�ʶ
  int count = 1;
  short tag = 0;
  m_fileBasic.WriteFile(fileHandle, &tag, sizeof(tag), count);
  m_fileBasic.CloseFile(fileHandle);
  return true;
}