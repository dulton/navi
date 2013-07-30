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
#ifndef _UEMODEL_UELINK_H
#define _UEMODEL_UELINK_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to higher level
#ifndef _UEMODEL_ROADNETWORK_H
#include "network.h"
#endif

// Refer to nametable
#ifndef _UEMODEL_NAMETABLE_H
#include "netnametable.h"
#endif

// Refer to its parent
#ifndef _UEMODEL_ROADLINK_H
#include "netlink.h"
#endif

// Refer to UE data model
#ifndef _UEMODEL_UENETBASIC_H
#include "uenetbasic.h"
#endif

// Refer to unique ID mechansim
#ifndef _UEMODEL_UEALLOCATOR_H
#include "ueallocator.h"
#endif

// Refer to self-defined array
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif
using namespace UeBase;

/// UeModel namespace
namespace UeModel
{
  /**
  * \brief ��·��Ҫ�صĳ���ӿ�INetLink��ʵ����
  */
  class UEMODEL_CLASS CUeLink : public INetLink
  {
    /// Relatives
    friend class CUeParcel;
    friend class CUeSimpleParcel;
    friend class CUeCompositedParcel;

  public:
    //
    //
    //
    /**
    * \brief ��ʼ��
    *
    * \param �μ�ParcelType����
    * \param linkData ·��������
    */
    CUeLink(short type, void *linkData);

    /**
    * \brief ��������
    */
    virtual ~CUeLink();

  public:
    //
    //
    //
    /**
    * \brief �ͷ���Դ��ʵ��Ϊ�յĽӿ�
    */
    virtual void Delete();

    /**
    * \brief ��ȡ��ǰ·�����������Ʊ��е�ƫ����
    *
    * \return ����ƫ����
    */
    virtual long GetNameOffset() = 0;

    /**
    * \brief ��ȡ·�ε�����
    *
    * \param str ·�����Ƶ��ַ���������
    * \param length ·�����Ƴ���
    */
    virtual bool GetName(char **str, short &length) = 0;

    /**
    * \brief ��ȡ��ǰ·�ε���ʼ���
    *
    * \param oneParcel parcel����ָ��
    * \return ��ʼ����ʶ��
    */
    virtual long GetStartNode(INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ��ǰ·�ε���ֹ���
    *
    * \param oneParcel parcel����ָ��
    * \return ��ֹ���ID
    */
    virtual long GetEndNode(INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �����ǰ·�����ڸ߲�·���е�Ҫ�أ���ȡ��ӳ�����·�μ���
    *
    * \param children ��·�μ���
    * \param linkID ·��ID
    * \param oneParcel parcel����ָ��
    */
    virtual short GetChildren(CMemVector &children, long linkID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ��ǰ·�ε�������� 
    * TODO: ��ǰ��ʵ�ֹ��ڼ��Ҳ����������������
    *
    * \param mbr ���ص��������
    * \param oneParcel parcel����ָ��
    */
    virtual void GetMBR(CGeoRect<double> &mbr, INetParcel *oneParcel = 0);

    /**
    * \brief �ж�ĳ��������뵱ǰ·�εĹ�ϵ
    *
    * \param point ָ��������λ��
    * \param tolerance �ݲ�
    * \param oneParcel parcel�����ָ��
    * \return ����õ���·�ε���С������η�Χ���򷵻�true�����򷵻�false
    */
    virtual bool IsContain(CGeoPoint<double> &point, double tolerance, INetParcel *oneParcel = 0);

    /**
    * \brief ��ȡ��ǰ·������ָ��·�����������
    * This function should have overriding functions: one is for outside calling & one is for inner calling
    *
    * \param position ���ص�����λ��
    * \param linkID ָ��·�ε�ID
    * \param oneparcel parcel����ָ��
    * \return ����õ����������
    */
    virtual double GetNearest(NetPosition &position, long linkID = -1, INetParcel *oneParcel = 0);

    //
    //
    //
    /**
    * \brief ��ȡ�м���
    */
    virtual short GetMidLevel();

    /**
    * \brief �Ƿ���ں��̵�
    */
    virtual short GetRedGreenLightFlag();

    /**
    * \brief ��ȡ��·�ȼ�
    */
    virtual short GetClass();

    /**
    * \brief ��ȡ��·����
    */
    virtual short GetType();

    /**
    * \brief ��ȡ��·��̬
    */
    virtual short GetForm();

    /**
    * \brief ��ȡͨ�еȼ�
    */
    virtual short GetSpeed();

    /**
    * \brief �Ƿ�Ϊ�������߽��·
    */
    virtual bool IsCrossAdmin(); 

    /**
    * \brief �ж��Ƿ�Ϊ�շ�·��
    */
    virtual short IsPaid();

    /**
    * \brief �жϽ�ͨ�������Ƿ�Ϊ�����ͨ��
    */
    virtual short IsSE(short vehicle = VT_Car);

    /**
    * \brief �жϽ�ͨ�������Ƿ�Ϊ�����ͨ��
    */
    virtual short IsES(short vehicle = VT_Car);

    /**
    * \brief �ж��Ƿ��й���
    */
    virtual short IsMrtFlag();

    /**
    *
    */
    virtual short GetCS();

    /**
    * \brief ��ȡ��·����
    */
    virtual int GetLength();

    /**
    * \brief �ж��Ƿ���ڹ��Ʋ�����ͨ��
    * TODO: Balance whether this function can be moved to link
    *
    * \param curID ��ǰ·��ID
    */
    virtual bool IsMrtNot(unsigned int method, long curID, long *ids, short num, bool isSE, INetParcel *oneParcel = 0);

    /**
    * \brief ��ȡ��ϸ�Ĺ�����Ϣ
    * 
    * \param curID ����·��
    * \param oneParcel �������ݶ����ָ��
    * \param outLinks ��ǰ�����漰���˳�·�εļ���
    * \param num ��ǰ�����漰���˳�·�εĸ���
    * \return ��������ڹ��ƣ�����false�����򷵻�true��
    */
    virtual bool GetMrtLinkIDs(long curID, INetParcel *oneParcel, long *outLinks, short num);

    /**
    * \brief �ж��Ƿ����ʱ������
    * TODO: Balance whether this function can be moved to link
    */
    virtual bool IsTimeLimited(unsigned int method, long linkID, short vehicle, short direction, INetParcel *oneParcel = 0);

    /**
    * \brief �ж�·���յ��Ƿ������ӵ�·��
    *
    * \param oneParcel �������ݶ���
    * \return ·���յ��пɼ���ͨ�з���true�����򷵻�false��
    */
    virtual bool HasSENext(INetParcel *oneParcel = 0);

    /**
    * \brief �ж�·������Ƿ������ӵ�·��
    *
    * \param oneParcel �������ݶ���
    * \return ����linkͨ����·������򷵻�true�����򷵻�false��
    */
    virtual bool HasESNext(INetParcel *oneParcel = 0);

    //
    // Useful overloaded operators
    //
    /**
    * \brief ���ص��߼���Ȳ�����
    */
    virtual bool operator == (const INetLink &otherLink)
    {
      return m_linkData == ((dynamic_cast<CUeLink *>(const_cast<INetLink *>(&otherLink)))->m_linkData);
    }

    /**
    * \brief ���ص��߼����Ȳ�����
    */
    virtual bool operator != (const INetLink &otherLink)
    {
      return m_linkData != ((dynamic_cast<CUeLink *>(const_cast<INetLink *>(&otherLink)))->m_linkData);
    }

  protected:
    /**
    *
    */
    virtual CGeoPoint<short> *GetVertice(short &vertexCount, CGeoPoint<short> *vertexData) = 0;

    /**
    * TODO: If it needed to be exposed, it had better use "virtual" mechansim 
    */
    CGeoPoint<long> GetStartPos(INetParcel *oneParcel);

    /**
    * TODO: If it needed to be exposed, it had better use "virtual" mechansim 
    */
    CGeoPoint<long> GetEndPos(INetParcel *oneParcel);

    /**
    * TODO: If it needed to be exposed, it had better use "virtual" mechansim 
    */
    UePassInfo &GetPassInfo();

    /**
    * TODO: If it needed to be exposed, it had better use "virtual" mechansim 
    */
    UeLinkInfo &GetLinkInfo();

    /**
    * \brief �жϹ����еĳ��������뵱ǰ���������Ƿ�һ��
    */
    bool IsValidMrtVehicleType(unsigned int method, int mrtVehicleType);

    /**
    *
    */
    bool GetMrtNot(int order, int mrtCount, long curLink, long oneLink, long *ids, short num, bool isSE, CUeParcel *oneParcel);

    /**
    *
    */
    bool GetTimeValidity(int order, short vehicle, short direction, long linkID, CUeParcel *innerParcel);

  protected:
    // Differenciate this link belong to which layer
    short m_parcelType;
    // Inner storage types of differen links
    UeNetID m_linkIdx;
    // Data memory
    /// TODO:
    /// Below memory can be represented by ZIP format, before really be used, uncompress it
    void *m_linkData;

    //
    const static short m_maxVertexCount;
  };

  /**
  * \brief ��ʵ·����·��
  */
  class UEMODEL_CLASS CUeSimpleLink : public CUeLink
  {
    // Relatives
    friend class CUeParcel;
    friend class CUeSimpleParcel;

  private:
    /// Disallow copy constructor & assignment function
    CUeSimpleLink(const CUeSimpleLink &other);
    const CUeSimpleLink &operator = (const CUeSimpleLink &other);

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    */
    CUeSimpleLink(UeSimpleLink *linkData = 0) : CUeLink(PT_Real, linkData)
    {
    }

    /**
    * \brief ��������
    */
    virtual ~CUeSimpleLink()
    {
    }

  public:
    //
    //
    //
    /**
    * \brief ��ȡ��ǰ·�����������Ʊ��е�ƫ����
    *
    * \return ����ƫ����
    */
    virtual long GetNameOffset()
    {
      long nameOffset = 0;
      if(m_isHasName[m_linkIdx.m_type])
      {
        switch(m_linkIdx.m_type)
        {
        case USLT_TwoName:
          {
            nameOffset = (reinterpret_cast<UeSimpleLinkTwoN *>(m_linkData))->m_nameOffset;
          }
          break;
        case USLT_ThreeName:
          {
            nameOffset = (reinterpret_cast<UeSimpleLinkThreeN *>(m_linkData))->m_nameOffset;
          }
          break;
        case USLT_FourName:
          {
            nameOffset = (reinterpret_cast<UeSimpleLinkFourN *>(m_linkData))->m_nameOffset;
          }
          break;
        case USLT_FiveName:
          {
            nameOffset = (reinterpret_cast<UeSimpleLinkFiveN *>(m_linkData))->m_nameOffset;
          }
          break;
        default:
          {
            assert(false);
          }
          break;
        }
      }

      return nameOffset;
    }

    /**
    * \brief ��ȡ·�ε�����
    *
    * \param str ·�����Ƶ��ַ���������
    * \param length ·�����Ƴ���
    */
    virtual bool GetName(char **str, short &length) 
    {
      return IRoadNetwork::GetNetwork()->GetNameTable()->GetContent(GetNameOffset(), str, length);
    }

    /**
    * \brief ��ȡ��ǰ·�ε���ʼ���
    * \detail The type of return value is long means this function only serving for other packages
    *
    * \param oneParcel parcel����ָ��
    * \return ��ʼ����ʶ��
    */
    virtual long GetStartNode(INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(oneParcel);
      UeNetID oneIdx = CUeAllocator::ToNodeID((reinterpret_cast<UeSimpleLink *>(m_linkData))->m_startNodeID, oneParcel);
      assert(oneIdx.m_id >= 0 && oneIdx.m_type < UNT_Total);
#endif
      return CUeAllocator::DirectToLong((reinterpret_cast<UeSimpleLink *>(m_linkData))->m_startNodeID, oneParcel);
    }

    /**
    * Note:
    * The type of return value is long means this function only serving for other packages
    */
    /**
    * \brief ��ȡ��ǰ·�ε���ֹ���
    * \detail The type of return value is long means this function only serving for other packages
    *
    * \param oneParcel parcel����ָ��
    * \return ��ֹ���ID
    */
    virtual long GetEndNode(INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(oneParcel);
      UeNetID oneIdx = CUeAllocator::ToNodeID((reinterpret_cast<UeSimpleLink *>(m_linkData))->m_endNodeID, oneParcel);
      assert(oneIdx.m_id >= 0 && oneIdx.m_type < UNT_Total);
#endif
      return CUeAllocator::DirectToLong((reinterpret_cast<UeSimpleLink *>(m_linkData))->m_endNodeID, oneParcel);
    }

    /**
    * \brief �����ǰ·�����ڸ߲�·���е�Ҫ�أ���ȡ��ӳ�����·�μ���
    */
    virtual short GetChildren(CMemVector &children, long linkID = -1, INetParcel *oneParcel = 0)
    {
      return 0;
    }

    /**
    * \brief ��ȡ��ǰ·�ε���㴦�Ƕȼ��յ㴦�ĽǶ�
    *
    * \param startAngle ��㴦�Ƕ�
    * \param endAngle �յ㴦�Ƕ�
    * \param linkID ·��ID
    * \param oneParcel �������ݶ���
    */
    virtual void GetAngle(short &startAngle, short &endAngle, long linkID = -1, INetParcel *oneParcel = 0);

    /**
    * \brief ��ȡ��ǰ·�ε���״�����꼯��
    *
    * \param vertice ���ڴ洢��״������Ļ�����
    * \param vertexCount ��״�����
    * \param linkID ·��ID
    * \param oneParcel parcel����ָ��
    */
    virtual void BuildVertex(CGeoPoint<long> *vertice, short &vertexCount, long linkID = -1, INetParcel *oneParcel = 0);

    /**
    * \brief ��ȡ·�������ֽڴ�С
    */
    static short GetLinkSize(short type)
    {
      assert(type >= 0 && type < USLT_Total);
      return (type >= 0 && type < USLT_Total) ? m_linkSize[type] : -1;
    }

    /**
    * \brief ��ȡ·����״����
    */
    static short GetVertexNum(short type)
    {
      assert(type >= 0 && type < USLT_Total);
      return (type >= 0 && type < USLT_Total) ? m_vertexNum[type] : -1;
    }

  protected:
    /**
    *
    */
    virtual CGeoPoint<short> *GetVertice(short &vertexCount, CGeoPoint<short> *vertexData)
    {
      assert(vertexData);

      if(vertexCount == 2)
      {
        vertexCount = 0;
        return 0;
      }
      else if(vertexCount == 3)
      {
        vertexCount = 1;
        return (reinterpret_cast<UeSimpleLinkThree *>(m_linkData))->m_vertice;
      }
      else if(vertexCount == 4)
      {
        vertexCount = 2;
        return (reinterpret_cast<UeSimpleLinkFour *>(m_linkData))->m_vertice;
      }
      else
      {
        vertexCount = (reinterpret_cast<UeSimpleLinkFive *>(m_linkData))->m_vertexCount;
        return (vertexData + (reinterpret_cast<UeSimpleLinkFive *>(m_linkData))->m_vertexOffset);
      }
    }

    /**
    *
    */
    void GetAngle(CGeoPoint<double> &start, CGeoPoint<double> &end, short &northAngle);

  protected:
    // Link size
    const static short m_linkSize[USLT_Total];
    // Vertex count
    const static short m_vertexNum[USLT_Total];
    // Whether have name
    const static short m_isHasName[USLT_Total];
  };

  /**
  * \brief ����·����·��
  */
  class UEMODEL_CLASS CUeCompositedLink : public CUeLink
  {
    /// Relatives 
    friend class CUeParcel;
    friend class CUeCompositedParcel;

  private:
    /// Disallow constructor & assignment function
    CUeCompositedLink(const CUeCompositedLink &other);
    const CUeCompositedLink &operator = (const CUeCompositedLink &other);

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    * \detail 
    * Note:
    * Below simply use PT_Global to represent all above index layer, it had better differenciate them respectively
    */
    CUeCompositedLink(UeCompositedLink *linkData = 0) : CUeLink(PT_Global, linkData)
    {
    }

    /**
    * \brief ��������
    */
    virtual ~CUeCompositedLink()
    {
    }

  public:
    //
    //
    //
    /**
    * \brief ��ȡ��ǰ·�����������Ʊ��е�ƫ����
    *
    * \return ����ƫ����
    */
    virtual long GetNameOffset()
    {
      long nameOffset = 0;
      if(m_isHasName[m_linkIdx.m_type])
      {
        switch(m_linkIdx.m_type)
        {
        case UCLT_OneName:
          {
            nameOffset = (reinterpret_cast<UeCompositedLinkOneN *>(m_linkData))->m_nameOffset;
          }
          break;
        case UCLT_TwoName:
          {
            nameOffset = (reinterpret_cast<UeCompositedLinkTwoN *>(m_linkData))->m_nameOffset;
          }
          break;
        case UCLT_ThreeName:
          {
            nameOffset = (reinterpret_cast<UeCompositedLinkThreeN *>(m_linkData))->m_nameOffset;
          }
          break;
        default:
          {
            assert(false);
          }
          break;
        }
      }

      return nameOffset;
    }

    /**
    * \brief ��ȡ·�ε�����
    *
    * \param str ·�����Ƶ��ַ���������
    * \param length ·�����Ƴ���
    */
    virtual bool GetName(char **str, short &length)
    {
      return IRoadNetwork::GetNetwork()->GetNameTable()->GetContent(GetNameOffset(), str, length);
    }

    /**
    * \brief ��ȡ��ǰ·�ε���ʼ���
    * \detail The type of return value is long means this function only serving for other packages
    *
    * \param oneParcel parcel����ָ��
    * \return ��ʼ����ʶ��
    */
    virtual long GetStartNode(INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(oneParcel);
      UeNetID oneIdx = CUeAllocator::ToNodeID((static_cast<UeCompositedLink *>(m_linkData))->m_startNodeID, oneParcel);
      assert(oneIdx.m_id >= 0 && oneIdx.m_type < UNT_Total);
#endif
      return CUeAllocator::DirectToLong((static_cast<UeCompositedLink *>(m_linkData))->m_startNodeID, oneParcel);
    }

    /**
    * \brief ��ȡ��ǰ·�ε���ֹ���
    * \detail The type of return value is long means this function only serving for other packages
    *
    * \param oneParcel parcel����ָ��
    * \return ��ֹ���ID
    */
    virtual long GetEndNode(INetParcel *oneParcel = 0)
    {
#ifdef _DEBUG
      assert(oneParcel);
      UeNetID oneIdx = CUeAllocator::ToNodeID((static_cast<UeCompositedLink *>(m_linkData))->m_endNodeID, oneParcel);
      assert(oneIdx.m_id >= 0 && oneIdx.m_type < UNT_Total);
#endif
      return CUeAllocator::DirectToLong((static_cast<UeCompositedLink *>(m_linkData))->m_endNodeID, oneParcel);
    }

    /**
    * \brief �����ǰ·�����ڸ߲�·���е�Ҫ�أ���ȡ��ӳ�����·�μ���
    * \detail This function should be only used by outside calling
    *
    * \param children ��·�μ���
    * \param linkID ·��ID
    * \param oneParcel parcel����ָ��
    */
    virtual short GetChildren(CMemVector &children, long linkID = -1, INetParcel *oneParcel = 0)
    {
      // Prepare
      children.RemoveAll(false);

#ifdef _DEBUG
      UeNetID oneIdx = CUeAllocator::ToLinkID(linkID, oneParcel);
      assert(m_linkIdx == oneIdx);
#endif
      //
      if(m_linkIdx.m_type == UCLT_One || m_linkIdx.m_type == UCLT_OneName)
      {
        long child = CUeAllocator::DirectToLong((reinterpret_cast<UeCompositedLinkOne *>(m_linkData))->m_childID[0], oneParcel);
        children.Add(&child);

        return 1;
      }
      else if(m_linkIdx.m_type == UCLT_Two || m_linkIdx.m_type == UCLT_TwoName)
      {
        int i = 0;
        for(; i < 2; i++)
        {
          long child = CUeAllocator::DirectToLong((reinterpret_cast<UeCompositedLinkTwo *>(m_linkData))->m_childID[i], oneParcel);
          children.Add(&child);
        }

        return 2;
      }
      else if(m_linkIdx.m_type == UCLT_Three || m_linkIdx.m_type == UCLT_ThreeName)
      {
        int count = (reinterpret_cast<UeCompositedLinkThree *>(m_linkData))->m_childCount;
        UeShortInteger *ids = (dynamic_cast<CUeParcel *>(oneParcel))->m_children + 
          (reinterpret_cast<UeCompositedLinkThree *>(m_linkData))->m_childOffset;

        int i = 0;
        for(; i < count; i++)
        {
#ifdef _DEBUG
          UeNetID oneIdx = CUeAllocator::ToLinkID(ids[i], oneParcel);
          int num = (m_parcelType == (PT_Real + 1)) ? USLT_Total : UCLT_Total;
          assert(oneIdx.m_type >= 0 && oneIdx.m_type < num);
#endif
          long child = CUeAllocator::DirectToLong(ids[i], oneParcel);
          children.Add(&child);
        }

        return count;
      }

      assert(false);
      return 0;
    }

    /**
    * \brief ��ȡ��ǰ·�ε���㴦�Ƕȼ��յ㴦�ĽǶ�
    *
    * \param startAngle ��㴦�Ƕ�
    * \param endAngle �յ㴦�Ƕ�
    * \param linkID ·��ID
    * \param oneParcel �������ݶ���
    */
    virtual void GetAngle(short &startAngle, short &endAngle, long linkID = -1, INetParcel *oneParcel = 0)
    {
      // Note:
      // Current road network model doesn't store angle information, TBD
      // in the meaning time, supper layers don't consider turn as one factor of route plan
      // ...
      assert(false);

      //
      //startAngle = (reinterpret_cast<UeCompositedLink *>(m_linkData))->m_angle.m_startAngle;
      //endAngle = (reinterpret_cast<UeCompositedLink *>(m_linkData))->m_angle.m_endAngle;

      //startAngle <<= 1;
      //endAngle <<= 1;
    }

    /**
    * \brief ��ȡ��ǰ·�ε���״�����꼯�ϣ��˽ӿڶԸ߲�·��������Ч
    */
    virtual void BuildVertex(CGeoPoint<long> *vertice, short &vertexCount, long linkID = -1, INetParcel *oneParcel = 0)
    {
      vertice = 0;
      vertexCount = 0;
    }

    /**
    * \brief ��ȡ·�ζ�����ֽڴ�С
    */
    static short GetLinkSize(short type)
    {
      assert(type >= 0 && type < UCLT_Total);
      return (type >= 0 && type < UCLT_Total) ? m_linkSize[type] : -1;
    }

  protected:
    /**
    *
    */
    virtual CGeoPoint<short> *GetVertice(short &vertexCount, CGeoPoint<short> *vertexData)
    {
      return 0;
    }

  private:
    /// Children number
    const static short m_childrenNum[UCLT_Total];
    /// Link size
    const static short m_linkSize[UCLT_Total];
    /// Whether have name
    const static short m_isHasName[UCLT_Total];
  };
}

#endif
