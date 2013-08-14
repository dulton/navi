/**
* Copyright (C) 2012-2013 Guangdong Ritu Information Systems Co.,Ltd.
*/

#ifndef _UEMAP_INDEXFORPOI_H
#define _UEMAP_INDEXFORPOI_H

//Refer to geombasic
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif
using namespace UeBase;

namespace UeMap
{

  /// Forward classes
  class CGroundGrid;

  //���Poi��mapRect�Ĺ�ϵ
  enum PoiDirection
  {
    PD_Default = 0,
    PD_Left,
    PD_Right,
    PD_Up,
    PD_Down,
    PD_InMap
  };

  /**
  * \brief ���ڴ���poi������,
  * ͨ�����ַ���ȡpoi��ƫ������
  */
  class CIndexForPoi
  {

    //��¼poi����,��Ӧ��poi��14���ֽڣ�
    //m_offset��ʾpoi�ڵ�ǰgrid�е�ƫ����
    struct RealGridPoi 
    {
      char m_count;
      char m_colorIndex;

      long m_x;
      long m_y;
      long m_notUse;
      long m_offSet;

    };

  public:

    /**
    * \brief ����poi��ƫ����
    * \param[in] oneGrid ���뵱ǰgridָ��
    * \param[in] gate ָ��ǰgate
    * \param[out] poiIndexs ����map��Χ�ڵ�poiƫ����
    */
    void GetPoiIndex(CGroundGrid *oneGrid, std::vector<unsigned long>& poiIndexs, CGeoRect<long> mapRect);

    CIndexForPoi();

    ~CIndexForPoi();

  protected:

    /**
    * \brief �ж�poi��mapRect���ĸ�����
    * \param[in] mapRect map����
    * \param[in] poi ָ�����poi
    */
    int IsPoiInMapRect(CGeoRect<long> mapRect, RealGridPoi &poi);

    /**
    * \brief ����mapRect���ֲ���poi��ƫ����
    * \param[in] oneGrid ���뵱ǰgridָ��
    * \param[in] mapRect map����
    * \param[out] poiIndexs ����map��Χ�ڵ�poiƫ����
    */
    void BinaryFindPoiInMapRect(CGroundGrid *oneGrid, CGeoRect<long> mapRect, std::vector<unsigned long>& poiIndexs);
    
    /**
    * \brief ����gridƫ��������poi
    * \param[out] poi ָ��poi
    * \param[in] bufOffset ��ǰgrid��ƫ���� 
    */
    bool ConstructPoi(RealGridPoi& poi,  unsigned char* poiBuf, unsigned long bufOffset);

  private:

  };

}

#endif