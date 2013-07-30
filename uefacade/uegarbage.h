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
#ifndef _UEFACADE_UEGARBAGE_H
#define _UEFACADE_UEGARBAGE_H

// Refer to EXPORT & IMPORT macroes definition
#ifndef _UEFACADE_BASE_H
#include "uefacade.h"
#endif

// Refer to STL definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to its parent
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling

//
namespace UeFacade
{
  /*! \class CUeGarbage
  * \brief ��Դ������
  * \detail UE����Դ���ղ��ԣ���Ҫʹ���ڴ���ղ��ԣ�����CMemoryConsumerΪ���࣬�̳���ӿ�ForCollegues��
  * ��ForCollegues��ʵ�����ͷſ�����Դ����ע�ᵽCUeGarbage��
  */
  class UEFACADE_CLASS CUeGarbage : public CMemoryGarbage
  {
    /// Memory consumers set, one type maybe have multiple instances
    typedef std::vector<CMemoryConsumer *> ConsumerVector;
    typedef std::map<int, ConsumerVector> ConsumerMap;
    typedef ConsumerMap::iterator consumer_itr;
    typedef ConsumerMap::const_iterator consumer_citr;

  public:
    //
    // ����&����
    //
    /*!
    * \brief ���캯��
    */
    CUeGarbage();

    /*!
    * \brief ��������
    */
    virtual ~CUeGarbage();

  public:
    //
    //
    //
    /*!
    * \brief ֪ͨ������(����ǰ������)�ͷſ�����Դ
	* It would be triggered by one collegue indicatored by type if it face the little memory, generally it will
    * meet with this occasion by catching one exception
	*
	* \param type ���������� ��ϸ���͵�ö�ٲ鿴ConsumerType����
	* \param curConsumer ��ǰ������
    */
    virtual bool NotifyCollegues(short type, CMemoryConsumer *curConsumer);

    /*!
    * \brief ע����Դ��������
	* 
	* \param type ���������� ��ϸ���͵�ö�ٲ鿴ConsumerType����
	* \param oneCollegue �����������
    */
    virtual bool RegisterConsumer(short type, CMemoryConsumer *oneCollegue);

  private:
    //
    ConsumerMap m_consumers;
  };
}
#endif
