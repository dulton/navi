/*
* The UrbanEye PND solution is a collection of packages based on native C++ classes
* that implement the fundamental algorithms & operations required to satisfy one kind
* of mobile or portable devices with competitive qualities being a leading one.
*
* Copyright (C) 2008 Xiujie Sheng
*
* This library isn't a free software, so you cann't take the sourcecode without author's permit.
* Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
* if you illegally got it. 
*
* NOTE: 
* AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
* LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
*
* For more information, contact:
*
* China University of Geoseciences(Wuhan)
* Graduate School
*
* Xiujie Sheng
* smartpoint@sohu.com
*/
#ifndef _UEMODEL_GATEWAY_H
#define _UEMODEL_GATEWAY_H

// Refer to EXPORT & IMPORT definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to GT_Mapping etc gate type definition
#ifndef _UEMODEL_UEBASIC_H
#include "netbasic.h"
#endif

// Import basic geometric definitions
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif

// Import self-array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

// Refer to memory garbage mechansim
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif
using namespace UeBase;

// Refer to index interface
#ifndef _UEINDEX_INDEX_H
#include "ueindex\geoindex.h"
#endif

// Refer to one kind of index mechansim
#ifndef _UEINDEX_INDEXIMPL_H
#include "ueindex\geoindeximpl.h"
#endif
using namespace UeIndex;

//
namespace UeModel
{
  // Forward classes
  class INetParcel;


  /**
  * \brief ·�����ݷ��ʽӿڶ��塣
  */
  class UEMODEL_CLASS INetGateWay : public CMemoryConsumer
  {
    // Relatives
    friend class IRoadNetwork;

  public:
    //
    // Constructors & deconstructor
    //
    /**
    * \brief ��������
    */
    virtual ~INetGateWay()
    {
    }

  public:
    //
    //
    //
    /**
    * \brief ��ȡ�ܵ�������
    *
    * \return ������Ŀ
    */
    virtual long GetParcelCount() = 0;

    // Note: For future, it still need proteced access to below functions
    // protected:
  public:
    //
    //
    //
    /**
    * \brief ��ȡָ�������ŵ���������
    * Based on special index algorithm, e.g., grid, to get one parecel contained by this data gate
    *
    * \param parcelID ��������
    * \param mode ����ģʽ���˴�������
    * \return ��������
    */
    virtual INetParcel *GetParcel(long parcelID, short mode) = 0;

    /**
    * \brief Update or add new parcels during running time
    */
    virtual bool UpdateParcel(INetParcel *oneParcel) = 0;

    /**
    * \brief �������ݷ���ͨ��
    */
    virtual short Open() = 0;

    /**
    * \brief �ر����ݷ���ͨ��
    */
    virtual short Close() = 0;

    /**
    * \brief ���ָ���������ڵ����������
    * Deprecated function: which should be moved to CNetIndexWay
    * 
    * \param pos ָ������
    * \return ����������
    */
    virtual long GetParcelID(CGeoPoint<long> &pos) = 0;

    /**
    * \brief ���ָ��������������������������������ż���
    * Deprecated function: which should be moved to CNetIndexWay
    *
    * \param mbr ָ���ľ�������
    * \param ids ���ص����������ż���
    */
    virtual void GetParcelID(CGeoRect<long> &mbr, CMemVector &ids) = 0;

    //
    //
    //
    /**
    * \brief ��Դ����
    */
    virtual bool ForCollegues()
    {
      return false;
    }
  };
}

#endif
