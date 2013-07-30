/**
* Copyright (C) 2012-2013 Guangdong Ritu Information Systems Co.,Ltd.
*/

#ifndef _UEMODEL_GRIDINDEX_H
#define _UEMODEL_GRIDINDEX_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to tstring etc portable definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Import basic geometric definitions
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif

// Import self-array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

// Refer to basic memory operations
#ifndef _UEBASE_MEMBASIC_H
#include "uebase\membasic.h"
#endif

using namespace UeBase;

namespace UeModel
{
  /**
  * \brief ����������ά��������ŵ�����ID��ӳ��
  *
  * \detail ������ŵĹ���: gridOrder = orderY * gridNumX + orderX;
  * ���У�orderY��ʾ��ǰ�������ڵ�������orderX��ʾ��ǰ�������ڵ�������gridNumX��ʾһ���е��������
  * ���½ǵ�һ�������(orderX,orderY)ֵΪ(0,0),��gridOrderҲΪ0��
  */
  class CUeGridIndex
  {
  public:
#pragma pack(1)
    /**
    * \brief ���������ļ�ͷ
    */
    struct GridIndexHeader
    {
      /// ������
      int m_gridGapX;
      /// ����߶�
      int m_gridGapY;
      /// ����ģ�һ�У��������
      short m_gridNumX;
      /// ����ģ�һ�У��������
      short m_gridNumY;
      /// �ܵ�������
      int m_gridNum;
      /// ��Χ����������������
      CGeoRect<long> m_mbr;

      GridIndexHeader() : m_gridGapX(0), m_gridGapY(0), 
        m_gridNumX(0), m_gridNumY(0), m_gridNum(0), m_mbr(0, 0, 0, 0)
      {
      }
    };

#pragma pack()

    CUeGridIndex();

    ~CUeGridIndex();

  public:
    /**
    * \brief ���ָ��������������������
    * 
    * \param pos ָ������
    * \return ����ID
    */
    long GetParcelID(const CGeoPoint<long> &pos);

    /**
    * \brief ���ָ����ͼ��Χ���������������������ID
    *
    * \param mbr ָ���ľ�������
    * \param ids ���ص�����ID����
    */
    bool GetParcelID(const CGeoRect<long> &mbr, CMemVector &ids);

    /**
    * \brief ���������ļ�
    */
    bool CreateGridIndexFile(const CGeoRect<long> *mbrs, int count);
  private:
    int GetGridOrder(const GridIndexHeader &gridHeader, const CGeoPoint<long> &pos);
    void GetGridOrder(const GridIndexHeader &gridHeader, const CGeoRect<long> &mbr, CMemVector &ids);
  };
}
#endif //_UEMODEL_GRIDINDEX_H