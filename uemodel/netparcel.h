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
#ifndef _UEMODEL_NETPARCEL_H
#define _UEMODEL_NETPARCEL_H

// Refer to EXPORT & IMPORT definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to basic geometry definition
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif

// Refer to NetPosition etc
#ifndef _UEMODEL_UEBASIC_H
#include "netbasic.h"
#endif

// Import mem vector definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif
using namespace UeBase;

namespace UeModel
{
  // Forward classes
  class INetLink;
  class INetNode;
  class INetAllocator;

  /**
  * \brief �������ݵĽӿڶ���
  */
  class UEMODEL_CLASS INetParcel
  {
  public:
    /**
    * \brief Ways of access data
    */
    enum MemType
    {
      MT_Mapped = 0,		/// Only refer to different addresses
      MT_Loaded,			/// Allocated by itself
      MT_Zipped			/// Allocated by itself but zipped
    };

    /**
    * \brief ��������
    */
    virtual ~INetParcel()
    {
    }

  public:
    ///
    ///
    ///
    /**
    * \brief �ͷ���Դ
    */
    virtual void Delete() = 0;

    /**
    * \brief ��ȡ·�����͵�����
    * Deprecated function: here link types only make sense whenn storaged not in outside
    */
    virtual short GetLinkTypeCount() = 0;

    /**
    * \brief ��ȡ��ǰ�����ڵ�ָ�����͵ĵ�·��Ŀ
    * -1 or default value means getting total count
    */
    virtual short GetLinkCount(short type = -1) = 0;

    /**
    * \brief ��ȡ������͵�����
    * Deprecated function: here link types only make sense whenn storaged not in outside
    */
    virtual short GetNodeTypeCount() = 0;

    /**
    * \brief ��ȡָ��������͵Ľ����Ŀ
    * -1 or default value means getting total count
    */
    virtual short GetNodeCount(short type = -1) = 0;

    /**
    * \brief ��������ڵĹ�����
    * TODO: This responsibility should be moved to new class for checking or validating some policies
    */
    virtual short GetMrtCount() = 0;

    /**
    * \brief ��������ڵ�ʱ��������
    * TODO: This responsibility should be moved to new class for checking or validating some policies
    */
    virtual short GetTimeCount() = 0;

    /**
    * \brief ��ȡ����߽����
    * Note: this fucntion should be only supported by index way and get lazy usage effection
    */
    virtual void GetMBR(CGeoRect<double> &mbr) const = 0;

    /**
    * \brief ����·��ID��ȡָ����·��
    *
    * \param linkID ·��ID
    * \return INetLink����ָ��
    */
    virtual INetLink *GetLink(long linkID) = 0;

    /**
    * \brief ��ȡ��ǰparcel�µ����е�link
    *
    * \param indice �洢����link�����ļ���
    */
    virtual void GetLink(CMemVector& indice) = 0;

    /**
    * \brief ��ȡָ��λ�õ�link
    *
    * \param ָ������������
    * \param �ݲ�
    * \return ��ָ����Χ�ཻ��·��
    */
    virtual INetLink *GetLink(CGeoPoint<double> &point, double tolerance) = 0;

    /**
    * \brief ��ȡָ��λ�õ�link
    *
    * \param pos ָ���������
    * \param tolerance �ݲ�
    * \param isForPOI 
    * \return ���ص�INetLink����
    */
    virtual INetLink *GetNearest(NetPosition &pos, double tolerance, bool isForPoi = false) = 0;

    /**
    * \brief ��ȡָ���������������link
    *
    * \param mbr ��������
    * \param tolerance �ݲ�
    * \param indice ���ص�·�ε���������
    */
    virtual bool GetLink(CGeoRect<double> &mbr, double tolerance, CMemVector& indice) = 0;

    /**
    * \brief ��ȡָ���ĵ�·���
    *
    * \param nodeID ��Ҫ��ȡ�Ľ��ı�ʶ
    * \return ���ص�INetNode����ָ��
    */
    virtual INetNode *GetNode(long nodeID) = 0;

    /**
    * \brief ��ȡָ��λ�õĵ�·���
    *
    * \param point ָ������
    * \param tolerance �ݲ�
    * \return ���ص�INetNode����ָ��
    */
    virtual INetNode *GetNode(CGeoPoint<double> &point, double tolerance) = 0;

    /**
    * \brief ��ȡָ����Χ�ڵĽ��
    *
    * \param mbr ָ����Χ
    * \param tolerance �ݲ�
    * \param indice ���صĽ�������ļ���
    */
    virtual void GetNode(CGeoRect<double> &mbr, double tolerance, CMemVector& indice) = 0;

    /**
    * \brief ��ȡָ��link��ʸ������
    *
    * \param linkID ·��ID
    * \param count �õ�����״�����
    * \return ��״�㼯��
    */
    virtual CGeoPoint<short> *GetVertex(long linkID, short &count) = 0;
  };
}

#endif