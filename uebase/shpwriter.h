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
#ifndef _UEBASE_SHPWRITER_H
#define _UEBASE_SHPWRITER_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to portable type definition like tstring
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to SHP basic definitions
#ifndef _UEBASE_SHPBASIC_H
#include "shpbasic.h"
#endif

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  //  needs to have dll-interface

// Declare namespace
namespace UeBase
{
  // Forward classes
  class CPathBasic;
  class CFileBasic;
  class CPlatInfo;

  /**
  * \brief shp�ļ�д��ӿ�
  */
  class UEBASE_CLASS CShpWriter
  {
  public:
    //
    //
    //
    /**
    * \brief ���캯��
    * 
    * \param type shp�ļ��е�ͼԪ���ͣ��й�ö��ֵ�μ�ShpType���塣
    * \param filie shp�ļ���
    */
    CShpWriter(short type, const tstring &file);

    /**
    * \brief ��������
    */
    ~CShpWriter();

  public:
    //
    // I/O functions
    //
    /**
    * \brief ����shp�ļ�����������������ļ��������ļ��Ĵ�����
    *
    * \return �ɹ�����true�����򷵻�false��
    */
    bool Open();

    /**
    * \brief �ͷ���Դ
    */
    void Close();

    //
    //
    //
    /**
    * \brief ����ͼԪ Encoding one SHP geometry
    *
    * \param type ͼԪ����
    * \param idx ͼԪ����
    * \param vertices ͼԪ��״����Ŀ
    * \param xCoords ͼԪ��״���x���꼯��
    * \param yCoords ͼԪ��״���y���꼯��
    * \param zCoords ͼԪ��״���z���꼯��
    * \return ���ش�����ͼԪ����ָ��
    */
    ShpGeometry *CreateGeometry(int type, int idx, int vertices, double *xCoords, double *yCoords, 
      double *zCoords = 0, double *mCoords = 0, int parts = 1, int *partOffsets = 0, int *partTypes = 0);

    /**
    * \brief д��ͼԪ��Ϣ
    *
    * \param geometry ShpGeometry����ָ��
    * \param isNew �Ƿ�Ϊ��ӵ���ͼԪ
    * \return �ɹ�����true�����򷵻�false��
    */
    bool WriteGeometry(ShpGeometry *geometry, bool isNew = true);

  private:
    //
    //
    //
    /**
    *
    */
    void ComputeExtents(ShpGeometry *geometry);

    /**
    * 
    */
    void SetBounds(char *buf, const ShpGeometry *geometry);

    /**
    *
    */
    void WritePolys(const ShpGeometry *geometry, char *buf, int &recordSize);

    /**
    *
    */
    void WritePoints(const ShpGeometry *geometry, char *buf, int &recordSize);

    /**
    *
    */
    void WritePoint(const ShpGeometry *geometry, char *buf, int &recordSize);

    /**
    *
    */
    void WriteHeader();

  private:
    /// File name
    tstring m_fileName;

    /// SHP description for header information
    ShpDesc m_description;

    /// Little or Big endian
    bool m_isLittle;

    /// Data handle
    void *m_dataHandle;

    /// Index handle
    void *m_indexHandle;

    /// Path basic functions
    const CPathBasic &m_pathBasic;

    /// File basic functions
    const CFileBasic &m_fileBasic;

    /// Platform-depedent utilities
    const CPlatInfo &m_platInfo;
  };
}

#endif