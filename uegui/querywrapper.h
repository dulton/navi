#ifndef _UEGUI_QUERYWRAPPER_H
#define _UEGUI_QUERYWRAPPER_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEQUERY_CODEINDEXCTRL_H
#include "uequery/uerecord.h"
#endif
#ifndef _UEQUERY_QUERYDEF_H
#include "uequery/querybasic.h"
#endif
#ifndef _UEQUERY_CODEINDEXCTRL_H
#include "uequery/codeindexctrl.h"
#endif
// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z
//////////////////////////////////////////////////////////////////////////
// �뾶��Χ
#define RADIUS00 5000000
#define RADIUS01 3000000
#define RADIUS02 2000000
#define RADIUS03 1000000
#define RADIUS04 500000
#define RADIUS05 100000
#define RADIUS06 50000
#define RADIUS07 10000
#define RADIUS08 5000
#define RADIUS09 2000
#define RADIUS10 1000
#define RADIUSCOUNT 11// �뾶��Χ����
//////////////////////////////////////////////////////////////////////////
namespace UeGui
{
  class CQueryWrapper
  {
  public:
    static CQueryWrapper &Get(void);
    //�����¼�ģʽ
    void SetDoQueryEventAlways(bool bAlways)
    {
      m_bisDoAlways = bAlways;
    }
    //���ü���ģʽ
    void SetQueryMode(UeQuery::IndexType queryMode)
    {
      m_querySql.m_indexType = queryMode;
    }
    //���ü�����Χ
    void SetRoundQueryRadius(long radius)
    {
      m_querySql.m_radius = radius;
    }
    //���ü����ؼ���
    void SetQueryKeyword(const char *pchKeyword);
    //���ü������ĵ�
    void SetCenterPosOfRound(const CGeoPoint<long> &centerPos)
    {
      m_querySql.m_pos = centerPos;
    }
    void SetMaxQueryRecordNum(long maxNum)
    {
      m_querySql.m_numOfWantTo = maxNum;
    }
    //���ü���������������Ϣ
    void SetQueryAdmInfo(const UeQuery::TCodeEntry &admCodeEntry)
    {
      m_curAdmInfo = admCodeEntry;
      m_querySql.m_addrOne = admCodeEntry.m_uCode;
    }
    void SetDefaultQueryKind(void);
    //���ü�����������Ϣ
    void SetQueryKindInfo(const UeQuery::TCodeEntry &kindCodeEntry)
    {
      m_curKindInfo = kindCodeEntry;
      m_querySql.m_kind = kindCodeEntry.m_uCode;
    }
    void GetKindNameByCode(unsigned uCode,char *pchNameBuf) const;
    void GetDistrictNameByCode(unsigned uCode,char *pchNameBuf) const;
    void SetAssociateNextWord(std::vector<string> *pvecNextWord)
    {
      m_querySql.m_pvecNextWord = pvecNextWord;
    }
    //��ʼ����
    bool CheckKeyWordExist(void);
    UeQuery::CUeRecord *DoQueryGetRecord(void);
    UeQuery::CUeRecord *DoQueryGetCross(UeQuery::SQLRecord *pRoadInfo);
    UeQuery::CUeRecord *DoQueryGetPoiNearbyRoad(UeQuery::SQLRecord *pRoadInfo);
    bool IsDoQueryEventAlways(void) const
    {
      return m_bisDoAlways;
    }
    //��ȡ�ϴμ������������
    const char *GetQueryAdmName(void) const;
    void GetQueryAdmName(char *pchAdmNameBuf) const;
    //��ȡ�ϴμ������͵�����
    const char *GetQueryKindName(void) const;
    void GetQueryKindName(char *pchKindNameBuf) const;
    //��ȡ�ϴμ�������
    const UeQuery::SQLSentence &GetSQLSentence(void) const;
    //��ȡ��������������
    bool GetComAdmNameByCode(unsigned uCode,char *pchNameBuf) const;
    //���ݾ�γ�Ȼ�ö�Ӧ�ĵ���
    void GetPlaceName(CGeoPoint<long> &curPos,char *outPointName,long radius=10);
    //��ȡ�����һ����
    const UeQuery::SQLRecord *GetNearestPoi(CGeoPoint<long> &curPos,long radius=10);
    //��ȡĳ��������ǰ���������λ��,eg:pOneRecord->m_addrCode=440101ʱ��ȡ������Խ���������ĵ�
    const UeQuery::SQLRecord *GetAdmCenterPoi(const UeQuery::SQLRecord *pOneRecord);
    //���浱ǰ��������Ĺؼ���
    void SaveCurKeyWord(const char *pchKeyWord,bool bIsAcro);
    //��ȡ֮ǰ�����������ʷ�ؼ���
    void GetHistoryKeyword(std::vector<string> &vecHistoryKey,bool bIsAcro);
  private:
    CQueryWrapper(void);
    //�Ƿ����κ����������¼�
    bool m_bisDoAlways;
    UeQuery::SQLSentence m_querySql;
    UeQuery::TCodeEntry m_curAdmInfo;
    UeQuery::TCodeEntry m_curKindInfo;
  };
}
#endif