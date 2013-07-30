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
#ifndef _UEBASE_DBFREADER_H
#define _UEBASE_DBFREADER_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to portable type definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to DBF basic definitions
#ifndef _UEBASE_DBFBASIC_H
#include "dbfbasic.h"
#endif

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  //  needs to have dll-interface
#pragma warning( disable: 4996 )  //  needs to have dll-interface

// Declare namespace
namespace UeBase
{
  // Forward classes
  class CPathBasic;
  class CFileBasic;

  /**
  * \brief Dbf�ļ�����ӿ�
  */
  class UEBASE_CLASS CDbfReader
  {
  public:
    //
    // ����&����
    //
    /**
    * \brief ���캯�� 
    * 
    * \param file dbf�ļ���
    * \param isCached �Ƿ�ʹ�û���
    */
    CDbfReader(const tstring &file, bool isCached = true);

    /**
    * \brief ��������
    */
    ~CDbfReader();

  public:
    //
    // �ļ���ؽӿ�
    //
    /*!
    * \brief ��dbf�ļ�������ȡԪ���ݡ�
    *
    * \return �ɹ�����true�����򷵻�false��
    */
    bool Open();

    /*!
    * \brief �ر��ļ�
    */
    void Close();

    //
    // ������ؽӿ�
    //
    /*!
    * \brief �����ܵļ�¼��
    *
    * \return int ��¼����
    */
    int GetRecordCount();

    /*!
    * \brief �����ֶ���
    *
    * \return int �ֶ�����
    */
    int GetFieldCount();

    /*!
    * \brief ��ȡָ���ֶε�������Ϣ
    *
    * \param fldIdx �ֶ�����
    * \param fldName �ֶ���
    * \param width ���ص��ַ��ֶεĿ��
    * \param decimals ���ص�ʮ�����ֶε�λ��
    * \return �ֶ�����
    */
    short GetFieldInfo(int fldIdx, char *fldName, int &width, int &decimals);

    /*!
    * \brief ��ȡ�ֶ�ֵ
    *
    * \param recIdx ��¼����
    * \param fldIdx �ֶ�����
    * \param fldType �ֶ�����
    * \return �ֶ�ֵ
    */
    void *GetField(int recIdx, int fldIdx, short fldType);

    /*!
    * \brief �ж�ָ����¼��ָ���ֶ��Ƿ�Ϊ��
    *
    * \param recIdx ��¼����
    * \param fldIdx �ֶ�����
    * \return ���Ϊ�շ���true�����򷵻�false��
    */
    bool IsNullField(int recIdx, int fldIdx);

  private:
    /// File name
    tstring m_fileName;

    /// File handle
    void *m_fileHandle;

    /// File description
    DbfDesc m_description;

    /// Whether geometries are cached
    bool m_isCache;

    /// Path basic functions
    const CPathBasic &m_pathBasic;

    /// File basic functions
    const CFileBasic &m_fileBasic;

    /// Memory buf for getting data value
    int m_dataSize;
    unsigned char *m_dataBuf;

    /// For numerica data conversion
    double m_numericValue;
  };
}
#endif
