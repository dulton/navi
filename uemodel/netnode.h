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
#ifndef _UEMODEL_NETNODE_H
#define _UEMODEL_NETNODE_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to basic geometry definition
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif
using namespace UeBase;

// Declare namespace
namespace UeModel
{
  // Forward classes
  class INetParcel;
  class INetLink;

  /**
  * \brief ��·���Ҫ�س���ӿ�
  */
  class UEMODEL_CLASS INetNode
  {
  protected:
    ///
    /// Only called by its descendants
    ///
    /**
    * \brief ��������
    */
    virtual ~INetNode()
    {
    }

  public:
    ///
    /// Common methods as one interface
    ///
    /**
    * \brief ��Դ�ͷ�
    */
    virtual void Delete() = 0;

    ///
    /// Basic functions as one node
    ///
    /**
    * \brief ȡ�ý��λ������
    *
    * \return �������
    */
    virtual CGeoPoint<long> GetPosition() = 0;

    /**
    * \brief ��ȡ������ӵ�·����
    */
    virtual short GetCLinkCount(long nodeID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ������ӵ�·��
    *
    * \param order ·�����
    * \param linkID ·��ID
    *
    * \return ·�ζ����ָ��
    */
    virtual INetLink *GetCLink(short order, long &linkID, long nodeID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �жϵ�ǰ����Ƿ�Ϊ����߽���
    */
    virtual bool IsAdjacentNode(long nodeID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �жϵ�ǰ����Ƿ�����ϲ���
    */
    virtual bool IsUpNode(long nodeID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �жϵ�ǰ����Ƿ�Ϊ�����
    */
    virtual bool IsMainNode(long nodeID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �жϵ�ǰ�ڵ��Ƿ�����²���
    */
    virtual bool IsDownNode(long nodeID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ����߽紦�����ӽ����Ϣ 
    * Note: Based on the network is composited by parcels
    *
    * \param parcelID ���ӵı߽������������
    * \param nodeID ���ӵ������������ID
    */
    virtual void GetAdjacentInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ�ϲ�����Ϣ
    * Note: Based on the network is composited by parcels
    * 
    * \param parcelID �ϲ������������
    * \param nodeID �ϲ���ID
    */
    virtual void GetUpInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ�������Ϣ
    * Note: Based on the network is composited by parcels
    *
    * \param parcelID ��������������
    * \param nodeID �����ID
    */
    virtual void GetMainInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ�²�����Ϣ
    * Note: Based on the network is composited by parcels
    *
    * \param parcelID �²������������
    * \param nodeID �²���ID
    */
    virtual void GetDownInfo(long &parcelID, long &nodeID, INetParcel *oneParcel = 0) = 0;

    ///
    /// Useful overloaded operators
    ///
    /**
    * \brief ���ص��߼���Ȳ�����
    */
    virtual bool operator == (const INetNode &otherNode) = 0;

    /**
    * \brief ���ص��߼����Ȳ�����
    */
    virtual bool operator != (const INetNode &otherNode) = 0;
  };
}

#endif