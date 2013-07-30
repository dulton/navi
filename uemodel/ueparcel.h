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
#ifndef _UEMODEL_UEPARCEL_H
#define _UEMODEL_UEPARCEL_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to its parent
#ifndef _UEMODEL_NETPARCEL_H
#include "netparcel.h"
#endif

// Refer to basic structures for UE data model
#ifndef _UEMODEL_UENETBASIC_H
#include "uenetbasic.h"
#endif

// Refer to self-defined array
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

// Refer to different memory mechansims
#ifndef _UEBASE_MEMBASIC_H
#include "uebase\membasic.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling

// Declare namespace
namespace UeModel
{
  /// Forward classes
  class CUeAllocator;
  class CUeLink;
  class CUeSimpleLink;
  class CUeCompositedLink;
  class CUeNode;
  class CUeSimpleNode;
  class CUeCompositedNode;

  /**
  * \brief �������ݽӿ�INetParcel��ʵ��
  */
  class UEMODEL_CLASS CUeParcel : public INetParcel
  {
    /// Relatives
    friend class CUeGateWay;
    friend class CDirectGateWay;

    friend class CUeLink;
    friend class CUeSimpleLink;
    friend class CUeCompositedLink;

    friend class CUeNode;
    friend class CUeSimpleNode;
    friend class CUeCompositedNode;

    friend class CUeAllocator;

  public:
    ///
    /// Constructors and deconstructor
    ///
    /**
    * \brief ��ʼ�� Must indicate which type of one parcel
    *
    * \param parcelType �μ�ParcelType����
    * \param memType �μ�MemType����
    */
    CUeParcel(short parcelType, short memType);

    /**
    * \brief �ͷ���Դ
    */
    virtual ~CUeParcel();

  public:
    ///
    /// Methods as common usage
    ///
    /**
    * \brief Never forget to delete this interface when never used similar to dereference
    */
    virtual void Delete();

    /**
    * \brief ��õ�ǰ��������·����Ŀ
    */
    virtual short GetLinkCount(short type = -1) = 0;

    /**
    * \brief ��õ�ǰ��������·����Ŀ
    */
    virtual short GetNodeCount(short type = -1) = 0;

    /**
    * \brief ��������ڵĹ�����
    */
    virtual short GetMrtCount() = 0;

    /**
    * \brief ��������ڵ�ʱ��������
    */
    virtual short GetTimeCount() = 0;

    ///
    /// New specifications only used to inner package and not exposed
    ///
    /**
    * \brief ͨ�����ID��ȡ������
    *
    * \param nodeID ���unique id
    * \return ������ָ��
    */
    virtual CUeNode *GetNode(UeNetID &nodeID) = 0;

    /**
    * \brief ͨ��·��ID��ȡ·�ζ���
    *
    * \param linkID ·��unique id
    * \return ·�ζ���ָ��
    */
    virtual CUeLink *GetLink(UeNetID &linkID) = 0;

    ///
    /// Common specifications for outside, here don't outside directly call them in order to 
    /// support the uniform cache mechansim etc
    //
    /**
    * \brief ����·��ID��ȡ·�ζ���
    *
    * \param linkID ·��ID
    * \return ·�ζ���ָ��
    */
    virtual INetLink *GetLink(long linkID);

    /**
    * \brief ��ȡָ��λ�õ�·��
    *
    * \param point ָ��λ�õ�����
    * \param tolerance �ݲ�
    * \return INetLink ���ص�·�μ���
    */
    virtual INetLink *GetLink(CGeoPoint<double> &point, double tolerance);

    /**
    * \brief ��ȡ�����ڵ�����·��
    *
    * \param indice ��ȡ��������·��ID�ļ���
    */
    virtual void GetLink(CMemVector& indice);

    /**
    * \brief ��ȡ��ָ��λ�������·��
    *
    * \param pos ָ��λ�õ�����
    * \param tolerance �ݲ�
    * \param isForPoi 
    * \return ·�ζ���ָ��
    */
    virtual INetLink *GetNearest(NetPosition &pos, double tolerance, bool isForPoi = false);

    /**
    * \brief ��ȡָ����Χ�ڵ�·��
    *
    * \param mbr ָ���ķ�Χ
    * \param tolerance �ݲ�
    * \param indice ȡ�õ�·��ID�ļ���
    */
    virtual bool GetLink(CGeoRect<double> &mbr, double tolerance, CMemVector& indice);

    /**
    * \brief ͨ�����ID��ȡ���
    *
    * \param nodeID ָ������ID
    * \return ������ָ��
    */
    virtual INetNode *GetNode(long nodeID);

    /**
    * \brief ��ȡָ��λ�õĽ��
    *
    * \param point ָ��λ�õ�����
    * \param tolerance �ݲ�
    * \return ������ָ��
    */
    virtual INetNode *GetNode(CGeoPoint<double> &point, double tolerance);

    /**
    * \brief ��ȡָ����Χ�ڵĽ��
    *
    * \param mbr ָ����Χ
    * \param tolerance �ݲ�
    * \param indice ȡ�õ����н��ID����
    */
    virtual void GetNode(CGeoRect<double> &mbr, double tolerance, CMemVector& indice);

    /**
    * \brief ��ȡָ��·�ε�ʸ������
    *
    * \param linkID ��·ID
    * \param count �õ�����״����Ŀ
    * \return �õ�����״�㼯��
    */
    virtual CGeoPoint<short> *GetVertex(long linkID, short &count);

    //
    // Template methods' "DO" functions' different implementations under different circumstances
    //
    /**
    * \brief �ж�ָ��link�Ƿ�ѡ��
    *
    * \param linkID ָ��link��ID
    * \param position ѡ��λ��
    * \param tolerance �ݲ�
    */
    virtual bool IsSelectedLink(UeNetID &linkID, NetPosition &position, double tolerance);

    /**
    * \brief �ж��Ƿ�Ϊ��Ч��link��������GetNearest���������ݵ�ƥ���·ʱ��
    */
    virtual bool IsValidLink(UeNetID &linkID);

    /**
    * \brief ��ȡ���ƥ��link
    *
    * \param ���п�ѡ�ļ���
    * \param rtPositon ƥ���λ�ü���·
    *
    * \return ����ѡ�е����link
    */
    virtual INetLink *IsOptimalLink(CMemVector &sels, NetPosition &rtPosition, int miniOrder = -1);

    /**
    * \brief ƥ�������Ƶ�·��
    *
    * \param sels ��ѡ��
    * \param rtPosition ƥ���λ�ü���·
    * \return �����Ƶ�·��
    */
    virtual INetLink *IsNamedLink(CMemVector &sels, NetPosition &rtPosition, int miniOrder = -1);

  protected:
    /// Index info and its type: simple or composited
    short m_parcelType;
    short m_memType;
    void *m_index;

    // RTree
    void *m_rtree;

    /// Basic data content
    char *m_nodeData[UNT_Total];
    UeUniqueID *m_clinkData;
    char *m_linkData[USLT_Total]; /// Note: For composited parcel, it only needs part not all pointers declared here

    /// Dynamic information
    UeMrtNot *m_mrtData;
    UeTimeValidity *m_tvData;
    UeTimeTable *m_timeData;

    /// The content only belongs to simple parcel
    CGeoPoint<short> *m_vertexData;
    /// The contents only belong to composited parcel
    UeShortInteger *m_children;

    /// One kind of memory allocation mechansim
    CMemBasic m_memBasic;

    /// The minimum distance for select special kind of links 
    static double m_distForMinor;

    ///
    static CUeSimpleLink m_simpleLink;
    static CUeCompositedLink m_compositedLink;
    static CUeSimpleNode m_simpleNode;
    static CUeCompositedNode m_compositedNode;
  };

  /**
  * \brief ��ʵ·�����������
  */
  class CUeSimpleParcel : public CUeParcel
  {
    // Relatives
    friend class CUeGateWay;
    friend class CDirectGateWay;
    friend class CMappingGateWay;
    friend class CUeLink;
    friend class CUeNode;

  private:
    /// Disallow copy constructor & assignment function
    CUeSimpleParcel(const CUeSimpleParcel &other);
    const CUeSimpleParcel &operator = (const CUeSimpleParcel &other);

  public:
    //
    //
    //
    /**
    * \brief ��ʼ��
    */
    CUeSimpleParcel(short memType) : CUeParcel(PT_Real, memType)
    {
    }

    /**
    * \brief ��������
    */
    virtual ~CUeSimpleParcel()
    {
    }

  public:
    ///
    /// Specifations mainly used to inner package
    ///
    /**
    * \brief ��ȡ����߽����
    */
    virtual void GetMBR(CGeoRect<double> &mbr) const
    {
      assert(m_index);

      // Consider CITUS have its data definition
      CGeoRect<UeLongInteger> &parcelMbr = reinterpret_cast<UeSimpleIndex *>(m_index)->m_mbr;
      mbr.m_minX = static_cast<double>(parcelMbr.m_minX);
      mbr.m_maxX = static_cast<double>(parcelMbr.m_maxX);
      mbr.m_minY = static_cast<double>(parcelMbr.m_minY);
      mbr.m_maxY = static_cast<double>(parcelMbr.m_maxY);
    }

    /**
    * \brief ��ȡ·�����͵�����
    */
    virtual short GetLinkTypeCount()
    {
      return USLT_Total;
    }

    /**
    * \brief ��ȡ�����ڵ�ָ�����͵ĵ�·��Ŀ
    */
    virtual short GetLinkCount(short type = -1)
    {
      if(type == -1)
      {
        return (reinterpret_cast<UeSimpleIndex *>(m_index))->m_links;
      }

      assert(type >= 0 && type < USLT_Total);
      return (reinterpret_cast<UeSimpleIndex *>(m_index))->m_linkNum[type];
    }

    /**
    * \brief ��ȡ������͵�����
    */
    virtual short GetNodeTypeCount()
    {
      return UNT_Total;
    }

    /**
    * \brief ��ȡָ��������͵Ľ����Ŀ
    */
    virtual short GetNodeCount(short type = -1)
    {
      if(type == -1)
      {
        return (reinterpret_cast<UeSimpleIndex *>(m_index))->m_nodes;
      }

      assert(type >= 0 && type < UNT_Total);
      return (reinterpret_cast<UeSimpleIndex *>(m_index))->m_nodeNum[type];
    }

    /**
    * \brief ��������ڵĹ�����
    */
    virtual short GetMrtCount()
    {
      return (reinterpret_cast<UeSimpleIndex *>(m_index))->m_mrts;
    }

    /**
    * \brief ��������ڵ�ʱ��������
    */
    virtual short GetTimeCount()
    {
      return (reinterpret_cast<UeSimpleIndex *>(m_index))->m_times;
    }

  protected:
    ///
    /// Inner specifications
    ///
    /**
    *
    */
    virtual CUeNode *GetNode(UeNetID &nodeID);

    /**
    *
    */
    virtual CUeLink *GetLink(UeNetID &linkID);
  };

  /**
  * \brief ����·�����������
  */
  class CUeCompositedParcel : public CUeParcel
  {
    // Relatives
    friend class CUeGateWay;
    friend class CDirectGateWay;
    friend class CMappingGateWay;
    friend class CUeLink;
    friend class CUeNode;

  private:
    /// Disallow copy constructor & assignment function
    CUeCompositedParcel(const CUeCompositedParcel &other);
    const CUeCompositedParcel &operator =(const CUeCompositedParcel &other);

  public:
    //
    // 
    //
    /**
    * \brief ��ʼ��
    */
    CUeCompositedParcel(short memType) : CUeParcel(PT_Global, memType)
    {
    }

    /**
    * \brief ��������
    */
    ~CUeCompositedParcel()
    {
    }

  public:
    ///
    ///
    ///
    /**
    * \brief ��ȡ����߽����
    */
    virtual void GetMBR(CGeoRect<double> &mbr) const
    {
      assert(m_index);

      CGeoRect<UeLongInteger> &parcelMbr = static_cast<UeCompositedIndex *>(m_index)->m_mbr;
      mbr.m_minX = static_cast<double>(parcelMbr.m_minX);
      mbr.m_maxX = static_cast<double>(parcelMbr.m_maxX);
      mbr.m_minY = static_cast<double>(parcelMbr.m_minY);
      mbr.m_maxY = static_cast<double>(parcelMbr.m_maxY);
    }

    /**
    * \brief ��ȡ·�����͵�����
    */
    virtual short GetLinkTypeCount()
    {
      // In fact, it is maller than this number
      return UCLT_Total;
    }

    /**
    * \brief ��ȡ��ǰ�����ڵ�ָ�����͵ĵ�·��Ŀ
    */
    virtual short GetLinkCount(short type = -1)
    {
      if(type == -1)
      {
        return (static_cast<UeCompositedIndex *>(m_index))->m_links;
      }

      assert(type >=0 && type < UCLT_Total);
      return (static_cast<UeCompositedIndex *>(m_index))->m_linkNum[type];
    }

    /**
    * \brief ��ȡ������͵�����
    */
    virtual short GetNodeTypeCount()
    {
      return UNT_Total;
    }

    /**
    * \brief ��ȡָ��������͵Ľ����Ŀ
    */
    virtual short GetNodeCount(short type = -1)
    {
      if(type == -1)
      {
        return (static_cast<UeCompositedIndex *>(m_index))->m_nodes;
      }

      assert(type >= 0 && type < UNT_Total);
      return (static_cast<UeCompositedIndex *>(m_index))->m_nodeNum[type];
    }

    /**
    * \brief ��������ڵĹ�����
    */
    virtual short GetMrtCount()
    {
      return (static_cast<UeCompositedIndex *>(m_index))->m_mrts;
    }

    /**
    * \brief ��������ڵ�ʱ��������
    */
    virtual short GetTimeCount()
    {
      return (static_cast<UeCompositedIndex *>(m_index))->m_times;
    }

  protected:
    /**
    *
    */
    virtual CUeNode *GetNode(UeNetID &nodeID);

    /**
    *
    */
    virtual CUeLink *GetLink(UeNetID &linkID);
  };
}

#endif
