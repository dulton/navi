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
#ifndef _UEMODEL_UENODE_H
#define _UEMODEL_UENODE_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to its parent
#ifndef _UEMODEL_NETNODE_H
#include "netnode.h"
#endif

// Refer to basic structures for UE data model
#ifndef _UEMODEL_UENETBASIC_H
#include "uenetbasic.h"
#endif

// Refer to unique id strategy
#ifndef _UEMODEL_UEALLOCATOR_H
#include "ueallocator.h"
#endif

// Refer to its container
#ifndef _UEMODEL_UEPARCEL_H
#include "ueparcel.h"
#endif

// Declare namespace
namespace UeModel
{
  /// Forward classes
  class CUeNode;
  class CUeSimpleNode;
  class CUeCompositedNode;

  /**
  * \brief �Ե�·������ӿڵ�ʵ����
  */
  class UEMODEL_CLASS CUeNode : public INetNode
  {
    /// Relatives
    friend class CUeLink;
    friend class CUeParcel;
    friend class CUeSimpleParcel;
    friend class CUeCompositedParcel;

  public:
    //
    //
    //
    /**
    * \brief ���캯������ʼ����
    *
    * \param type �μ�ParcelType����
    * \param nodeData ���������
    */
    CUeNode(short type, void *nodeData);

    /**
    * \brief ��������
    */
    virtual ~CUeNode();

  public:
    //
    //
    //
    /**
    * \brief TODO:��Ч�ӿ�
    */
    virtual void Delete();

    /**
    * \brief ��ȡ������ӵ�·����
    */
    virtual short GetCLinkCount(long nodeID = -1, INetParcel *oneParcel = 0) = 0;


    /**
    * \brief ��ȡ������ӵ�·��
    *
    * \param order ·�����
    * \param linkID ·��ID
    * \return ·�ζ����ָ��
    */
    virtual INetLink *GetCLink(short order, long &linkID, long nodeID = 0, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �жϵ�ǰ����Ƿ�Ϊ����߽���
    *
    * Note:
    * If this function is only limited to CitusModel packge, the first parameter should be UeNetID
    * The type LONG means this function should be only called by other packges' calling
    *
    */
    virtual bool IsAdjacentNode(long nodeID = -1, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(m_nodeIdx == oneIdx && oneIdx.m_type >= 0 && oneIdx.m_type < UNT_Total);
#endif
      return m_adjFlag[m_nodeIdx.m_type];
    }

    /**
    * \brief �жϵ�ǰ����Ƿ�����ϲ���
    */
    virtual bool IsUpNode(long nodeID = -1, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx.m_type >= 0 && oneIdx.m_type < UNT_Total && m_nodeIdx == oneIdx);
#endif
      return m_upFlag[m_nodeIdx.m_type];
    }

    /**
    * \brief �жϵ�ǰ����Ƿ�Ϊ�����
    */
    virtual bool IsMainNode(long nodeID = -1, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx.m_type >= 0 && oneIdx.m_type < UNT_Total && m_nodeIdx == oneIdx);
#endif
      return m_mainFlag[m_nodeIdx.m_type];
    }

    /**
    * \brief �жϵ�ǰ�ڵ��Ƿ�����²���
    */
    virtual bool IsDownNode(long nodeID = -1, INetParcel *oneParcel = 0)
    {
      assert(nodeID >= 0);
      return (nodeID >= 0) ? (m_parcelType != PT_Real) : false;
    }        

    //
    // Useful overloaded operators
    //
    /**
    * \brief ���ص��߼���Ȳ�����
    */
    bool operator == (const INetNode &otherNode)
    {
      return m_nodeData == ((dynamic_cast<CUeNode *>(const_cast<INetNode *>(&otherNode)))->m_nodeData);
    }

    /**
    * \brief ���ص��߼����Ȳ�����
    */
    bool operator != (const INetNode &otherNode)
    {
      return m_nodeData != ((dynamic_cast<CUeNode *>(const_cast<INetNode *>(&otherNode)))->m_nodeData);
    }

  protected:
    /// Node belong to which layer
    short m_parcelType;
    /// Node inner storage types
    UeNetID m_nodeIdx;
    /// Node data content
    void *m_nodeData;

    // Common variables for different inner types of link
    const static short m_clinkCount[UNT_Total];
    const static bool m_adjFlag[UNT_Total];
    const static bool m_upFlag[UNT_Total];
    const static bool m_mainFlag[UNT_Total];
  };

  /**
  * \brief ��ʵ·������
  */
  class UEMODEL_CLASS CUeSimpleNode : public CUeNode
  {
    // Relatives
    friend class CUeNode;
    friend class CUeParcel;
    friend class CUeSimpleParcel;
    friend class CUeCompositedParcel;

  private:
    /// Disallow copy constructor & assignment function
    CUeSimpleNode(const CUeSimpleNode &other);
    const CUeSimpleNode &operator = (const CUeSimpleNode &other);

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    */
    CUeSimpleNode(UeSimpleNode *nodeData = 0) : CUeNode(0, nodeData)
    {
    }

    /**
    * \brief ��������
    */
    virtual ~CUeSimpleNode()
    {
    }

  public:
    //
    //
    //
    /**
    * \brief ��ȡ�ý�����ӵ�·����
    *
    * Note:
    * If this function is only limited to CitusModel packge, the first parameter should be UeNetID
    * The type LONG means this function should be only called by other packges' calling
    *
    */
    virtual short GetCLinkCount(long nodeID = -1, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(nodeID >= 0);
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx);
#endif

      if(!m_clinkCount[m_nodeIdx.m_type])
      {
        return (reinterpret_cast<UeSimpleNodeFive *>(m_nodeData))->m_clinkCount;
      }

      return m_clinkCount[m_nodeIdx.m_type];
    }

    /**
    * \brief ��ȡ������ӵ�·��
    *
    * \param order ·�����
    * \param linkID ·��ID
    *
    * \return ·�ζ����ָ��
    */
    INetLink *GetCLink(short order, long &linkID, long nodeID = -1, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(nodeID >= 0 && oneParcel);
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx);
#endif

      UeShortInteger *linkIDs = (reinterpret_cast<UeSimpleNode *>(m_nodeData))->m_linkID;
      if(!m_clinkCount[m_nodeIdx.m_type])
      {
        linkIDs = (reinterpret_cast<CUeParcel *>(oneParcel))->m_clinkData + (reinterpret_cast<UeSimpleNodeFive *>(m_nodeData))->m_clinkOffset;
      }

      linkID = CUeAllocator::DirectToLong(linkIDs[order], oneParcel);
      return oneParcel->GetLink(linkID);
    }

    /**
    * \brief ȡ�ý������
    *
    * \return �������
    */
    virtual CGeoPoint<long> GetPosition()
    {
      CGeoPoint<long> rt;
      rt.m_x = (reinterpret_cast<UeSimpleNode *>(m_nodeData))->m_pos.m_x;
      rt.m_y = (reinterpret_cast<UeSimpleNode *>(m_nodeData))->m_pos.m_y;
      return rt;
    }

    /**
    * \brief ��ȡ������ӵ���������Ľ����Ϣ
    *
    * \param parcelID ���ӵı߽������������
    * \param nodeID ���ӵ������������ID
    */
    virtual void GetAdjacentInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx.m_type >= 0 && oneIdx.m_type < 5 && m_nodeIdx == oneIdx);
#endif
      UeAdjacentNode *adjNode = reinterpret_cast<UeAdjacentNode *>(reinterpret_cast<char *>(m_nodeData) + m_nodeBasicSize[m_nodeIdx.m_type]);    
      assert(adjNode);
      parcelID = adjNode->m_adjParcelID;
      nodeID = CUeAllocator::DirectToLong(adjNode->m_adjNodeID, oneParcel);
    }

    /**
    * \brief ��ȡ�ϲ�����Ϣ
    * 
    * \param parcelID �ϲ������������
    * \param nodeID �ϲ���ID
    */
    virtual void GetUpInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx && oneIdx.m_type > 4 && oneIdx.m_type < 10);
#endif
      UeUpNode *upNode = reinterpret_cast<UeUpNode *>(reinterpret_cast<char *>(m_nodeData) + m_nodeBasicSize[m_nodeIdx.m_type]);    
      assert(upNode);
      nodeID = CUeAllocator::DirectToLong(upNode->m_upNodeID, oneParcel);
    }

    /**
    * \brief ��ȡ�������Ϣ
    *
    * \param parcelID ��������������
    * \param nodeID �����ID
    */
    virtual void GetMainInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx && oneIdx.m_type >= 15 && oneIdx.m_type <= 19);
#endif
      UeMainNode *mainNode = reinterpret_cast<UeMainNode *>(reinterpret_cast<char *>(m_nodeData) + m_nodeBasicSize[m_nodeIdx.m_type]);    
      assert(mainNode);
      parcelID = CUeAllocator::DirectToLong(mainNode->m_mainParcelID, oneParcel);
      nodeID = CUeAllocator::DirectToLong(mainNode->m_mainNodeID, oneParcel);
    }

    /**
    * \brief ��ȡ�²�����Ϣ���򵥽�㲻�����²��㡣
    */
    virtual void GetDownInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
      parcelID = -1;
      nodeID = -1;
    }

    /**
    * \brief ��ȡ����С
    */
    static short GetNodeBasicSize(short type)
    {
      assert(type >= 0 && type < UNT_Total);
      return m_nodeBasicSize[type];
    }

    /**
    * \brief ��ȡ����ܴ�С(�������ӵ�������Ϣ���ϲ�����Ϣ��)
    */
    static short GetNodeTotalSize(short type)
    {
      assert(type >= 0 && type < UNT_Total);
      return m_nodeTotalSize[type];
    }

  protected:
    //
    const static short m_nodeBasicSize[UNT_Total];
    const static short m_nodeTotalSize[UNT_Total];
  };

  /**
  * \brief ����·������
  */
  class UEMODEL_CLASS CUeCompositedNode : public CUeNode
  {
    // Relatives
    friend class CUeNode;
    friend class CUeParcel;
    friend class CUeSimpleParcel;
    friend class CUeCompositedParcel;

  private:
    /// Disallow copy constructor & assignment function
    CUeCompositedNode(const CUeCompositedNode &other);
    const CUeCompositedNode &operator = (const CUeCompositedNode &other);

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    */
    CUeCompositedNode(UeCompositedNode *nodeData = 0) : CUeNode(1, nodeData)
    {
    }

    /**
    * \brief ��������
    */
    virtual ~CUeCompositedNode()
    {
    }

  public:
    /**
    * \brief ��ȡ������ӵ�·����
    */
    virtual short GetCLinkCount(long nodeID = -1, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(nodeID >= 0);
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx);
#endif

      if(!m_clinkCount[m_nodeIdx.m_type])
      {
        return (reinterpret_cast<UeCompositedNodeFive *>(m_nodeData))->m_clinkCount;
      }
      return m_clinkCount[m_nodeIdx.m_type];
    }


    /**
    * \brief ��ȡ������ӵ�·��
    *
    * \param order ·�����
    * \param linkID ·��ID
    *
    * \return ·�ζ����ָ��
    */
    INetLink *GetCLink(short order, long &linkID, long nodeID = -1, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(nodeID >= 0 && oneParcel);
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx);
#endif
      UeShortInteger *linkIDs = (reinterpret_cast<UeCompositedNode *>(m_nodeData))->m_linkID;
      if(!m_clinkCount[m_nodeIdx.m_type])
      {
        linkIDs = (reinterpret_cast<CUeParcel *>(oneParcel))->m_clinkData + (reinterpret_cast<UeCompositedNodeFive *>(m_nodeData))->m_clinkOffset;
      }

      linkID = CUeAllocator::DirectToLong(linkIDs[order], oneParcel);
      return oneParcel->GetLink(linkID);
    }

    /**
    * \brief ȡ�ý��λ������
    *
    * \return �������
    */
    virtual CGeoPoint<long> GetPosition()
    {
      CGeoPoint<long> rt;
      rt.m_x = (reinterpret_cast<UeCompositedNode *>(m_nodeData))->m_pos.m_x;
      rt.m_y = (reinterpret_cast<UeCompositedNode *>(m_nodeData))->m_pos.m_y;
      return rt;
    }

    /**
    * \brief ��ȡ����߽紦�����ӽ����Ϣ 
    *
    * \param parcelID ���ӵı߽������������
    * \param nodeID ���ӵ������������ID
    */
    virtual void GetAdjacentInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx && oneIdx.m_type >= 0 && oneIdx.m_type < 5);
#endif
      UeAdjacentNode *adjNode = reinterpret_cast<UeAdjacentNode *>(reinterpret_cast<char *>(m_nodeData) + m_nodeBasicSize[m_nodeIdx.m_type]);    
      assert(adjNode);
      parcelID = static_cast<long>(adjNode->m_adjParcelID);
      nodeID = CUeAllocator::DirectToLong(adjNode->m_adjNodeID, oneParcel);
      assert(parcelID >= 0 && nodeID >= 0);
    }

    /**
    * \brief ��ȡ�ϲ�����Ϣ
    * 
    * \param parcelID �ϲ������������
    * \param nodeID �ϲ���ID
    */
    virtual void GetUpInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx && oneIdx.m_type > 4 && oneIdx.m_type < 10);
#endif
      UeUpNode *upNode = reinterpret_cast<UeUpNode *>(reinterpret_cast<char *>(m_nodeData) + m_nodeBasicSize[m_nodeIdx.m_type]);    
      assert(upNode);
      nodeID = CUeAllocator::DirectToLong(upNode->m_upNodeID, oneParcel);
    }

    /**
    * \brief ��ȡ�������Ϣ
    *
    * \param parcelID ��������������
    * \param nodeID �����ID
    */
    virtual void GetMainInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx && oneIdx.m_type >= 15 && oneIdx.m_type <= 19);
#endif
      UeMainNode *mainNode = reinterpret_cast<UeMainNode *>(reinterpret_cast<char *>(m_nodeData) + m_nodeBasicSize[m_nodeIdx.m_type]);    
      assert(mainNode);
      parcelID = CUeAllocator::DirectToLong(mainNode->m_mainParcelID, oneParcel);
      nodeID = CUeAllocator::DirectToLong(mainNode->m_mainNodeID, oneParcel);
    }

    /**
    * \brief ��ȡ�²�����Ϣ
    *
    * \param parcelID �²������������
    * \param nodeID �²���ID
    */
    virtual void GetDownInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToNodeID(nodeID, oneParcel);
      assert(oneIdx == m_nodeIdx && oneIdx.m_type >= 0 && oneIdx.m_type < UNT_Total);
#endif
      UeCompositedNode *downNode = reinterpret_cast<UeCompositedNode *>(m_nodeData);
      assert(downNode);
      nodeID = CUeAllocator::DirectToLong(downNode->m_downNodeID, oneParcel);
    }

    /**
    * \brief ��ȡ����С
    */
    static short GetNodeBasicSize(short type)
    {
      assert(type >= 0 && type < UNT_Total);
      return m_nodeBasicSize[type];
    }

    /**
    * \brief ��ȡ����ܴ�С(�������ӵ�������Ϣ���ϲ�����Ϣ��)
    */
    static short GetNodeTotalSize(short type)
    {
      assert(type >= 0 && type < UNT_Total);
      return m_nodeTotalSize[type];
    }

  protected:
    //
    const static short m_nodeBasicSize[UNT_Total];
    const static short m_nodeTotalSize[UNT_Total];
  };
}


#endif
