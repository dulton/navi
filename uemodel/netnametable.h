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
#ifndef _UEMODEL_NAMETABLE_H
#define _UEMODEL_NAMETABLE_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to memory garbage
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif
using namespace UeBase;

//
namespace UeModel
{
  /**
  * \brief ���Ʊ����ݷ��ʽӿڶ���
  */
  class UEMODEL_CLASS INameTable : public CMemoryConsumer
  {
  public:
    //
    //
    //
    /**
    * \brief ��������
    */
    virtual ~INameTable()
    {
    }

  public:
    //
    //
    //
    /**
    * \brief ��Դ����
    */
    virtual void Delete() = 0;

    /**
    * \brief �����Ʊ�
    */
    virtual bool Open() = 0;

    /**
    * \brief �ر����Ʊ�
    */
    virtual bool Close() = 0;

    /**
    * \brief ��ȡ����
    *
    * \param offset �����������Ʊ��е�ƫ����
    * \param str ���ڴ洢���ƵĻ�����
    * \param length ���Ƴ���
    * \param isCached �Ƿ񻺴�����
    * \return ��ȡ�ɹ�����true�����򷵻�false��
    */
    virtual bool GetContent(int offset, char **str, short &length, bool isCached = true) = 0;

    //
    //
    //
    /**
    * \brief �ͷſ�����Դ
    */
    virtual bool ForCollegues() = 0;
  };
}

#endif
