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
* AUTHOR WOULD \ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
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
#ifndef _UEMODEL_DIRECTGATEWAY_H
#define _UEMODEL_DIRECTGATEWAY_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to tstring etc portable definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to its parent
#ifndef _UEMODEL_GATEWAY_H
#include "netgateway.h"
#endif

// Refer to basic memory operations
#ifndef _UEBASE_MEMBASIC_H
#include "uebase\membasic.h"
#endif

// Refer to basic file operations
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

// Refer to basic directory operations
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning(disable : 4996)  // Deprecated function
#pragma warning(disable : 4251)  // Deprecated function

//
namespace UeModel
{
  // Forward classes
  class CUeParcel;

  /**
  * \brief ·�����ݷ��ʽӿ�INetGateWayʵ�֣�ֱ�Ӵ��ļ��м��ز������������ݡ�
  * Directly load parcel data into memory and those parcel would be cached.
  */
  class UEMODEL_CLASS CDirectGateWay : public INetGateWay
  {
  private:
    // Not allow directly assigned and implicitly data conversion
    CDirectGateWay(const CDirectGateWay &other);
    const CDirectGateWay &operator = (const CDirectGateWay &other);

  public:
    //
    //
    //
    /**
    * \brief ��ʼ��
    *
    * \param parcelType �μ�ParcelType����
    * \param gateName �����ļ���
    */
    CDirectGateWay(short parcelType, const tstring &gateName, CGeoIndexImpl *indexWay);

    /**
    * \brief �ͷ���Դ���ر��ļ�
    */
    virtual ~CDirectGateWay();

  public:
    //
    // I/O operations
    //
    /**
    * \brief ��ȡ�������ݲ��򿪵�ͼ�����ļ���
    *
    * \return �ɹ�����1�����򷵻�0.
    */
    virtual short Open();

    /**
    * \brief �ͷ���Դ���ر��ļ���
    *
    * \return �ɹ�����1�����򷵻�0.
    */
    virtual short Close();

    //
    // Access to parcel content
    //
    /**
    * \brief ��ȡ�ܵ�������
    *
    * \return ������Ŀ
    */
    virtual long GetParcelCount();

    /**
    * \brief ��ȡָ�������ŵ���������
    * Based on special index algorithm, e.g., grid, to get one parecel contained by this data gate
    *
    * \param parcelID ��������
    * \param mode ����ģʽ���˴�������
    * \return ��������
    */
    virtual INetParcel *GetParcel(long parcelID, short mode);

    /**
    * \brief δʵ��
    * Update or add new parcels during running time
    */
    virtual bool UpdateParcel(INetParcel *oneParcel);

    /**
    * \brief ���ָ���������ڵ����������
    * Deprecated function: which should be moved to CNetIndexWay
    * 
    * \param pos ָ������
    * \return ����������
    */
    virtual long GetParcelID(CGeoPoint<long> &pos);

    /**
    * \brief ���ָ��������������������������������ż���
    * Deprecated function: which should be moved to CNetIndexWay
    *
    * \param mbr ָ���ľ�������
    * \param ids ���ص����������ż���
    */
    virtual void GetParcelID(CGeoRect<long> &mbr, CMemVector &ids);

    //
    // Memory management
    //
    /**
    * \brief ��Դ����
    */
    virtual bool ForCollegues();

  private:
    /**
    *
    */
    short PrepareIndex(const tstring &gateName);

    /**
    *
    */
    short PrepareData(const tstring &gateName);

    /**
    *
    */
    short CheckVersion();

    /**
    *
    */
    CUeParcel *LoadSimpleParcel(long parcelID) const;

    /**
    *
    */
    CUeParcel *LoadCompositedParcel(long parcelID) const;

    /**
    *
    */
    short GateRead(void *fp, long offset, void **data, int size, int count, CUeParcel *oneParcel = 0) const;

    /**
    *
    */
    bool MapMbrFile();

    /**
    *
    */
    bool IsExistMbrFile();

  private:
    // Basic description of this file
    short m_parcelType;
    tstring m_gateName;

    // File pointers to index and data
    void *m_indexFile;
    void *m_dataFile;

    /// Header data
    void *m_header;

    // RTree index
    bool m_isUseRTree;
    void *m_rtreeHandle;

    // TODO:
    // Refer to one kind of index mechansim
    // ...
    // Mapping mbrs
    // Note: For mainland case
    void *m_mbrHandle;
    void *m_mbrMapping;
    bool m_isUseGridIdx;
    static CGeoRect<long> *m_mbrs;	// Since all network layer follow the same mbr definition

    //
    CMemBasic m_memBasic;
    const CFileBasic &m_fileBasic;
    const CPathBasic &m_pathBasic;

    //
    CGeoIndexImpl *m_indexImpl;
  };
}

#endif
