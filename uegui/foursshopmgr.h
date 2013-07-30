/*
* ���ְ��
*	  4S������ݴ���
* ʹ�÷�����
*
*
*
*/

#ifndef _UEGUI_FOURSSHOPMGR_H
#define _UEGUI_FOURSSHOPMGR_H

#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

#include <vector>
#include "uebase\geombasic.h"
#include "simplefilereader.h"

using namespace UeBase;

namespace UeGui
{

enum FourSCarType
{
    FourSCarType_Benze,
    FourSCarType_Toyota,
    FourSCarType_Honda,
    FourSCarType_ChangCheng,
    FourSCarType_None
};

class CFourSShopMgr
{

#pragma pack(push)
#pragma pack(4)
    struct FourSFileBlock
    {
        FourSFileBlock() {}
        FourSFileBlock(int id, long offset,unsigned int dist, double x, double y)
            : m_id(id), m_offSet(offset), m_distCode(dist), m_x(x), m_y(y) {}
        int m_id;
        long m_offSet;
        unsigned int m_distCode;
        double m_x;
        double m_y;
    };
#pragma pack(pop)

    struct FourSList
    {
        const static int MAXNAMELENGTH = 256;
        char m_name[MAXNAMELENGTH];
        char m_distName[45];
        CGeoPoint<long> m_point;
        FourSList()
        {
            ::memset(this, 0x00, sizeof(struct FourSList));
        }
    };

public:
    CFourSShopMgr(void);
    ~CFourSShopMgr(void);

    void Open4SShopeHook();

private:
    //���ļ����������������������ͽ��й���
    static void ReadFile(const unsigned int distCode,FourSCarType type);
    //�������
    static void ReleaseData();
    //������ݣ�nameFileName�����������ļ����ļ���
    static void PackData(const tstring& nameFileName);
    //��ȡ�������ļ���������dostCode���й���
    static void ReadMainFile(const tstring& mainFileName,const unsigned int distCode);
    //4S��hook��괥���¼�
    static void On4SShopListQuery(const unsigned int distCode, FourSCarType type);
    //4S���ѯ����б�hook�ķ����¼�
    static void On4SShopListHookReturn();
    //4S���ѯ����б�hook��POIѡ���¼�
    static void On4SShopListHookPOISelect(const char* keyValue1, const char* keyValue2,const CGeoPoint<long>& point);
private:

  static vector<FourSFileBlock*> m_mainVec;

  static vector<FourSList*> m_list;
};
}
#endif
