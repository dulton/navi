#ifndef _UEGUI_MYJOURNEYWRAPPER_H
#define _UEGUI_MYJOURNEYWRAPPER_H
#include "gui.h"
#include "uebase\customerfilereader.h"
#include "ueroute\routebasic.h"
using namespace UeBase;

namespace UeGui
{

  class CMyJourneyData
  {
  public:
    //�г����Ƶ���󳤶�
    const static int kMAXNAME = 128;
    //�г��о��ɵ���󳤶�
    const static unsigned int kMAXPOICOUNT = 6;

    CMyJourneyData() : m_routeType(UeRoute::RW_Optimal), m_POICount(0)
    {
      ::memset(m_JourneyName, 0, sizeof(m_JourneyName));
      m_POIList.clear();
    }
    virtual ~CMyJourneyData() {}
  public:
    //�������
    void Clear();
    //�����г�����
    void SetJourneyName(const char *journeyName);
    //��ȡ�г�����
    const char* GetJourneyName();
    //����·������
    void SetRouteType(unsigned int routeType);
    //��ȡ·������
    unsigned int GetRouteType();
    //����г�����
    bool AddJourneyData(const char *journeyName, unsigned int routeType, const POIDataList &poiList);
    //��ȡ�г�����
    bool GetJourneyData(POIDataList &poiList);
    //���������ݣ��������ƣ�·�����ͣ����ɵ���Ŀת�����ַ�������ȥ
    bool DataToString(std::string& data);
    //���ַ�����ת�ɽṹ����
    bool DataFromString(const char* data);
    //��ȡÿ���г����ݵĴ�С:�����г��о��ɵ���ٲ�ͬ������Ϊ�˴洢�Ͷ�ȡ�ļ����㣬����̶���С
    unsigned int DataSize();
  private:
    //�г�����
    char m_JourneyName[kMAXNAME];
    //·������
    unsigned int m_routeType;
    //���ɵ����
    unsigned short m_POICount;
    //�г�·��POI�б�
    POIDataList m_POIList;
  };

  //�����ҵ��г̴󲿷�ʱ�䶼��ʹ�ñ������ܣ���ǰ�˲�����ɾ��������ʹ��deque
  typedef std::vector<CMyJourneyData> JourneyDataList;

  class CMyJourneyWrapper 
  {

  public:
    CMyJourneyWrapper();

    ~CMyJourneyWrapper();
    //���ⲿ���õ�ɾ�����ݽӿ�
    bool DeleteJourneyData(int dataIndex);
    //���ⲿ���õ�������ݽӿ�
    void RemoveAllJourney();
    //����г�����
    bool AddJourneyData(const char *journeyName, unsigned int routeType, const POIDataList &poiList);
    //�༭�г�����
    /**
    * \brief �༭�г�����
    * \dataIndex �г���������
    **/
    bool EditJourneyData(unsigned int dataIndex, const char *journeyName, unsigned int routeType, const POIDataList &poiList);
    /**
    * \brief ��ȡָ�����������г�
    * \dataIndex ����
    **/
    bool GetJourneyData(CMyJourneyData &myJourneyData, unsigned int dataIndex);
    /**
    * \brief ��ȡָ����Χ[startPos, endPos]���г�
    * \journeyDataList Ҫ�����г��б�
    * \startPos ��ʼ����
    * \endPos ��������
    **/
    bool GetJourneyDatas(JourneyDataList &journeyDataList, unsigned int startPos, unsigned int endPos);
    //��ȡ�ļ���������
    unsigned int GetJourneyCount();

  private:
    tstring GetJourneyFilename();

  private:
    //�ҵ��г����������,�������ö�ȡ
    unsigned int m_maxSize;
    //////////////////////////////////////////////////////////////////////////
    //�ļ���д����
    CCustomerFileReader* m_journeyFileReader;
  };
}
#endif