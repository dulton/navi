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
#ifndef _UEBASE_DBFWRITER_H
#define _UEBASE_DBFWRITER_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to portable string definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to SHP basic definition
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
  class CPlatInfo;

  /**
  * \brief Dbf�ļ�����ӿ�
  */
  class UEBASE_CLASS CDbfWriter
  {
  public:
    //
    // ����&����
    //
    /**
    * \brief ���캯��
    *
    * \param file dbf�ļ���
    */
    CDbfWriter(const tstring &file);

    /**
    * \brief ��������
    */
    ~CDbfWriter();

    //
    // �ļ���ؽӿ�
    //
    /**
    * \brief ����dbf�ļ������
    *
    * \return �ɹ�����true�����򷵻�false��
    */
    bool Open();

    /**
    * \brief д�뻺�����ݼ��ļ�ͷ���ر��ļ���
    */
    void Close();

    //
    // ������ؽӿ�
    //
    /**
    * \brief ��������ֶ�
    *
    * \param fldName �ֶ�����
    * \param fldType �ֶ�����
    * \param width �ַ��ֶεĿ��
    * \param decimals ʮ�����ֶε�λ��
    * \return �����ֶ��������ʧ���򷵻�-1��
    */
    int CDbfWriter::AddFieldInfo(const char *fldName, short fldType, int width, int decimals);

    /**
    * \brief ����ָ����¼��ָ���ֶε�ֵ
    *
    * \param recIdx ��¼����
    * \param fldIdx �ֶ�����
    * \param fldType �ֶ�����
    * \param data �ֶ�ֵ
    * \return д��ɹ�����true�����򷵻�false��
    */
    bool WriteField(int recIdx, int fldIdx, int fldType, void *data);

  private:
    //
    //
    //
    /**
    *
    **/
    void WriteHeader();

    /**
    *
    **/
    bool FlushRecord();

  private:
    /// File name
    tstring m_fileName;

    /// File handle
    void *m_dataHandle;

    /// DBF file information
    DbfDesc m_description;

    /// Path basic functions
    const CPathBasic &m_pathBasic;

    /// File basic functions
    const CFileBasic &m_fileBasic;
  };
}
#endif