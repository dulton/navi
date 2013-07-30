#ifndef _UEGUI_VIEWSPOTMGR_H_
#define _UEGUI_VIEWSPOTMGR_H_

#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

#include "uebase\geombasic.h"
#include "simplefilereader.h"
#include <vector>

using namespace UeBase;

namespace UeGui
{
  class CViewspotMgr
  {

#pragma pack(push)
#pragma pack(4)
    struct ViewSpotFileBlock
    {
      ViewSpotFileBlock() {}
      ViewSpotFileBlock(int id, long offset,unsigned int dist, double x, double y)
        : m_id(id), m_offSet(offset), m_distCode(dist), m_x(x), m_y(y) {}
      int m_id;
      long m_offSet;
      unsigned int m_distCode;
      double m_x;
      double m_y;
    };
#pragma pack(pop)

    struct ViewSpotList
    {
      const static int MAXNAMELENGTH = 256;
      char m_name[MAXNAMELENGTH];
      char m_distName[45];
      CGeoPoint<long> m_point;
      ViewSpotList()
      {
        ::memset(this, 0x00, sizeof(struct ViewSpotList));
      }
    };
  public:
    CViewspotMgr(void);
    ~CViewspotMgr(void);

    //�򿪾����ѯ
    void OpenViewSpotHook();


  private:
    //��ȡ�ļ����������������й���
    static void ReadFile(const unsigned int distCode);
    //�������
    static void ReleaseData();
    //��ȡ�������ļ���������dostCode���й���
    static void ReadMainFile(const tstring& fileName, const unsigned int distCode);
    //������ݣ�nameFileName�����������ļ����ļ���
    static void PackData(const tstring& fileName);

    //���ξ���hook�����¼�
    static void OnViewSpotListQuery(const char* keyValue1, const char* keyValue2, const CGeoPoint<long>& point);
    //������ı�ʱ�����²�ѯ����
    static void OnAreaChange();
  private:
    static vector<ViewSpotFileBlock*> m_mainVec;
    static vector<ViewSpotList*> m_list;

  };

}
#endif
