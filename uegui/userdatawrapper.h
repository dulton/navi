#ifndef _UEGUI_USERDATAWRAPPER_H
#define _UEGUI_USERDATAWRAPPER_H
#include "gui.h"

#include "ueroute/route.h"
#include "ueroute/routebasic.h"
using namespace UeRoute;

#include "uequery/query.h"
#include "uequery/querybasic.h"
using namespace UeQuery;

#include "uemap/view.h"
#include "uemap/viewhook.h"
using namespace UeMap;

#include "uemodel/network.h"

using namespace UeModel;



#define  USERDATA_LIB (CUserDataWrapper::Get())

namespace UeGui 
{
  //�༭��Ϣ����������
  struct EditData
  {
    unsigned int m_x;
    unsigned int m_y;
    unsigned short m_kind;           //����
    unsigned char m_name[128];       //����
    unsigned char m_addrCode[128];    //��ַ����,poi��Ϊunsigned int
    unsigned char m_telephone[128];  //�绰,ע��˴��ĵ绰�洢��ʽΪ�ַ�����poi��Ϊunsigned int

    //��Ϊpoi������û��������Ϣ,������ʱ�������m_kind�ĺ���λ
    bool m_isMapshow;                //ͼ����ʾ
    bool m_isVoice;                  //�������� 
    bool m_isStartpos;               //����λ��

    EditData():m_x(0) ,m_y(0) ,m_kind(0) ,m_isMapshow(false) ,m_isVoice(false) ,m_isStartpos(false) 
    {
      ::memset(m_name,0x00,128);
      ::memset(m_addrCode,0x00,128);
      ::memset(m_telephone,0x00,128);
    }
    EditData &operator=(const EditData& other)
    {
      if(this==&other)
      {
        return *this;
      }
      ::strcpy((char *)m_name,(char *)other.m_name);
      ::strcpy((char *)m_addrCode,(char *)other.m_addrCode);
      ::strcpy((char *)m_telephone,(char *)other.m_telephone);
      m_kind=other.m_kind;
      m_isMapshow=other.m_isMapshow;
      m_isVoice=other.m_isVoice;
      m_isStartpos=other.m_isStartpos;
      m_x=other.m_x;
      m_y=other.m_y;
      return *this;
    }
    bool IsSameWith(const EditData &other) 
    {
      return !(m_x != other.m_x || m_y != other.m_y ||
        ::strcmp((char *)m_name, (char *)other.m_name));
    }
  };

  class CUserDataWrapper 
  {

    CUserDataWrapper();

  public:

    ~CUserDataWrapper() {}

    static const CUserDataWrapper& Get();
    /*
    * \brief ��ȡ��ʷ��¼����
    */
    int GetHistoryRecordCount() const;
    /*
    * \brief ��ȡ��ʷ·�߸���
    */
    int GetRecentCount() const;
    /*
    * \brief ��ȡ��ַ����¼����
    */
    int GetFavoriteCount() const;
    /*
    * \brief ��ȡ�ҵ��г̵ļ�¼����
    */
    int GetJourneyCount() const;
    //�����ʷ��¼
    /*
    * UeRoute::PT_Start ��� UeRoute::PT_End �յ� PT_Middle���ɵ�
    */
    void AddHistoryPoint(UeRoute::PositionType) const;
    void AddHistoryPoint(UeRoute::PlanPosition& pos) const;
    //�����ʷ·������
    void AddRecent() const;

    //����г�����
    bool AddJourneyData(const char *journeyName, unsigned int routeType, const POIDataList &poiList) const;

    //�ж�·���Ƿ��Ѿ�����
    bool CheckHistoryRouteExists(const RecentEntry& newEntry) const;

    //������ʷ��¼�滮·��
    void HistoryRoutePlan(int dataIndex) const;

    //ɾ������Ϊorder�ļ�¼
    unsigned int RemoveFavorite(int order) const;

    //��ȡ����Ϊorder�ĵ�ַ��Ϣ
    const FavoriteEntry *GetFavorite(int order) const;

    //����µĵ�ַ��Ϣ
    unsigned int AddFavorite(const FavoriteEntry &curFavor) const;

    //��������Ϊorder�ĵ�ַ��Ϣ
    unsigned int UpdateFavorite(const FavoriteEntry &curFavor,int order) const;

    //��ȡ����Ϊorder����ʷ��·��Ϣ
    const RecentEntry *GetRecent(int order) const;

    //ɾ������Ϊorder����ʷ��·��Ϣ
    unsigned int RemoveRecent(int order) const;

    //��������Ϊorder����ʷ��·��Ϣ
    unsigned int UpdateRecent(const RecentEntry &curRecent,int order) const;

    //��ȡ����Ϊorder����ʷ��¼
    const HistoryRecordEntry *GetHistoryRecord (int order) const;

    //���һ����ʷ��¼
    unsigned int AddHistoryRecord (const HistoryRecordEntry &curHisRecord) const;

    //ɾ������Ϊorder����ʷ��¼
    unsigned int RemoveHistoryRocord(int order) const;

    //ɾ��������ʷ��¼
    unsigned int RemoveAllHistoryRecord() const;

    //��������Ϊorder����ʷ��¼
    unsigned int UpdateHistoryRecord(const HistoryRecordEntry &curHisRecord,int order) const;

    //�����ʷ·��
    void RemoveAllRecent() const;

    //��յ�ַ��
    void RemoveAllFavorite() const;

    //����ҵ�nd�г�
    void RemoveAllJourney() const;

    //��ȡ��ʷ·�ߵ�����
    bool GetRecentName(unsigned int index, char *recentName) const;
  
    /*
    * \brief �޸���ʷ·�ߵ����ơ�
    */
    void EditHistoryRouteData(unsigned int index, const char* routeName) const;
    /*
    * \brief ��ַ����༭���ݵ�ת��
    */
    bool FavoriteEntry2EditData(const FavoriteEntry* fEntry , EditData* edata) const;
    /*
    * \brief �༭�������ַ����ת��
    */
    bool EditData2FavoriteEntry(EditData* edata, FavoriteEntry* fEntry) const;

    //���Ӻ���
    unsigned int ConnectToRecent(void) const;
    unsigned int DisconnectRecent(void) const;
    //
    unsigned int ConnectToFavorite(void) const;
    unsigned int DisconnectFavorite(void) const;
    //
    unsigned int ConnectToHistoryRecord(void) const;
    unsigned int DisconnectHistoryRecord(void) const;

    

  private:
    //���õ�ַ����
    void SetAddrName(const PlanPosition& planPos, char *addrName) const;
  private:
    UeMap::IView *m_view;
    UeRoute::IRoute *m_route;
    UeQuery::IQuery *m_query;
    UeModel::IRoadNetwork *m_net;
    static CUserDataWrapper m_userDataWrapper;

    UeQuery::SQLSetting setting;
  };
}

#endif //_UEGUI_USERDATAWRAPPER_H