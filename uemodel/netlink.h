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
#ifndef _UEMODEL_ROADLINK_H
#define _UEMODEL_ROADLINK_H

// Refer to EXPORT & IMPORT definition
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to NetPosition etc 
#ifndef _UEMODEL_UEBASIC_H
#include "netbasic.h"
#endif

// Refer to basic geometry definition
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif

// Refer to self-array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif
using namespace UeBase;

namespace UeModel
{
  // Forward classes
  class INetParcel;
  class INetNode;

  /**
  * \brief ��·Ҫ�صĳ���ӿ�
  */
  class UEMODEL_CLASS INetLink
  {
  protected:
    ///
    ///
    ///
    /**
    * \brief ��������
    */
    virtual ~INetLink()
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

    ///
    ///
    ///
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
    *
    * \param mbr ���ص��������
    * \param oneParcel parcel����ָ��
    */
    virtual void GetMBR(CGeoRect<double> &mbr, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �ж�ĳ��������뵱ǰ·�εĹ�ϵ
    *
    * \param point ָ��������λ��
    * \param tolerance �ݲ�
    * \param oneParcel parcel�����ָ��
    * \return ����õ���·�ε���С������η�Χ���򷵻�true�����򷵻�false
    */
    virtual bool IsContain(CGeoPoint<double> &point,double tolerance, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ��ǰ·�ε���״�����꼯��
    *
    * \param vertice ���ڴ洢��״������Ļ�����
    * \param vertexCount ��״�����
    * \param linkID ·��ID
    * \param oneParcel parcel����ָ��
    */
    virtual void BuildVertex(CGeoPoint<long> *vertice, short &vertexCount, long linkID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ��ǰ·������ָ��λ�����������
    *
    * \param position ����λ��
    * \param linkID ָ��·�ε�ID
    * \param oneparcel parcel����ָ��
    * \return ����õ����������
    */
    virtual double GetNearest(NetPosition &position, long linkID = -1, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ��ǰ·�ε���㴦�Ƕȼ��յ㴦�ĽǶ�
    *
    * \param startAngle ��㴦�Ƕ�
    * \param endAngle �յ㴦�Ƕ�
    * \param linkID ·��ID
    * \param oneParcel �������ݶ���
    */
    virtual void GetAngle(short &startAngle, short &endAngle, long linkID = -1, INetParcel *oneParcel = 0) = 0;

    ///
    /// Note: Below responsibilites should be moved to one new class which be specially responsible for checking some policies
    ///
    /**
    * \brief ��ȡ�м���
    */
    virtual short GetMidLevel() = 0;

    /**
    * \brief �Ƿ���ں��̵�
    */
    virtual short GetRedGreenLightFlag() = 0;

    /**
    * \brief ��ȡ��·�ȼ�
    */
    virtual short GetClass() = 0;

    /**
    * \brief ��ȡ��·����
    */
    virtual short GetType() = 0;

    /**
    * \brief ��ȡ��·��̬
    */
    virtual short GetForm() = 0;

    /**
    * \brief ��ȡͨ�еȼ�
    */
    virtual short GetSpeed() = 0;

    /**
    * \brief �Ƿ�Ϊ�������߽��·
    */
    virtual bool IsCrossAdmin() = 0; 

    /**
    * \brief �ж��Ƿ�Ϊ�շ�·��
    */
    virtual short IsPaid() = 0;

    /**
    * \brief �жϽ�ͨ�������Ƿ�Ϊ����
    *
    * \param vehicle ����
    */
    virtual short IsSE(short vehicle = VT_Car) = 0;

    /**
    * \brief �жϽ�ͨ�������Ƿ�Ϊ����
    *
    * \param vehicle ����
    */
    virtual short IsES(short vehicle = VT_Car) = 0;

    /**
    * \brief �ж��Ƿ��й�����Ϣ
    */
    virtual short IsMrtFlag() = 0;

    /**
    * \brief TODO:��Ч�Ľӿ�
    */
    virtual short GetCS() = 0;

    /**
    * \brief ��ȡ��·����
    */
    virtual int GetLength() = 0;

    /**
    * \brief �ж��Ƿ���ڹ��Ʋ�����ͨ��
    * TODO: Balance whether this function can be moved to link
    *
    * \param curID ��ǰ·��ID
    */
    virtual bool IsMrtNot(unsigned int method, long curID, long *ids, short num, bool isSE, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief ��ȡ��ϸ�Ĺ�����Ϣ
    * 
    * \param curID ����·��
    * \param oneParcel �������ݶ����ָ��
    * \param outLinks ��ǰ�����漰���˳�·�εļ���
    * \param num ��ǰ�����漰���˳�·�εĸ���
    * \return ��������ڹ��ƣ�����false�����򷵻�true��
    */
    virtual bool GetMrtLinkIDs(long curID, INetParcel *oneParcel, long *outLinks, short num) = 0;

    /**
    * \brief �ж��Ƿ����ʱ������
    * TODO: Balance whether this function can be moved to link
    */
    virtual bool IsTimeLimited(unsigned int method, long linkID, short vehicle, short direction, INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �ж�·���յ��Ƿ������ӵ�·��
    *
    * \param oneParcel �������ݶ���
    * \return ·���յ��пɼ���ͨ�з���true�����򷵻�false��
    */
    virtual bool HasSENext(INetParcel *oneParcel = 0) = 0;

    /**
    * \brief �ж�·������Ƿ������ӵ�·��
    *
    * \param oneParcel �������ݶ���
    * \return ����linkͨ����·������򷵻�true�����򷵻�false��
    */
    virtual bool HasESNext(INetParcel *oneParcel = 0) = 0;

    ///
    /// Useful overloaded operators
    ///
    /**
    * \brief ���ص��߼���Ȳ�����
    */
    virtual bool operator == (const INetLink &otherLink) = 0;

    /**
    * \brief ���ص��߼����Ȳ�����
    */
    virtual bool operator != (const INetLink &otherLink) = 0;
  };
}

#endif
