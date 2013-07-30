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
#ifndef _UEBASE_UEMAPSIO_H
#define _UEBASE_UEMAPSIO_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Portable definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to File basic definitions
#ifndef _UEBASE_FILEBASIC_H
#include "filebasic.h"
#endif

// Refer to Path basic definitions
#ifndef _UEBASE_PATHBASIC_H
#include "pathbasic.h"
#endif

// Refer to uemaps.ztt description
#ifndef _UEBASE_UEMAPS_H
#include "uemaps.h"
#endif

// Declare namespace UeBase
namespace UeBase
{
  /**
  * \class CUeMapsIO
  *
  * \brief This class is mainly responsible for creation & updation of file uemaps.ztt
  */
  class UEBASE_CLASS CUeMapsIO
  {
  public:
    /**
    * \enum PropertyType
    */
    enum PropertyType
    {
      PT_Font,
      PT_Point,
      PT_Line,
      PT_Poly,
      PT_Text,
      PT_Layer
    };


    //
    // ����&����
    //
    /**
    * \brief ���캯��
    */
    CUeMapsIO();

    /**
    * \brief ��������
    */
    ~CUeMapsIO();

  public:
    //
    // Methods for data update
    //
    /**
    * \brief ��õ�ͼ�����ļ����ļ�ͷ
    *
    * \param mapsHeader �ļ�ͷ��Ϣ
    */
    void GetHeader(MapsHeader &mapsHeader);

    /**
    * \brief ���µ�ͼ�����ļ����ļ�ͷ
    *
    * \param mapsHeader �ļ�ͷ��Ϣ
    */
    void UpdateHeader(MapsHeader &mapsHeader);

    /**
    * \brief ���ָ�������ò���
    *
    * \param type �������ͣ�����ö��ֵ�ο�PropertyType����
    * \param properties ���ص����ò�����Ϣ
    * \param count ���ö������Ŀ
    * \param isDay ָ����Ҫ��ȡ�����ò�������������ģʽ��������Ǻ�ҹ
    */
    void GetProperties(short type, void **properties, int count, bool isDay = true);

    /**
    * \brief ����ָ�������ò���
    *
    * \param type �������ͣ�����ö��ֵ�ο�PropertyType����
    * \param properties Ҫ���µ����ö���
    * \param count ���ö������Ŀ
    * \param isDay ָ����Ҫ��ȡ�����ò�������������ģʽ��������Ǻ�ҹ
    */
    void UpdateProperties(short type, void *properties, int count, bool isDay = true);

    /**
    * \brief �������ò�����ָ�����ļ�λ��
    *
    * \param propertes Ҫ���µ����ö���
    * \param offset �������������ļ��е�ƫ����
    * \param size �����ö���Ĵ�С
    */
    void UpdateProperties(void *properties, int offset, int size);

    /**
    * \brief �����������ͻ�����������ļ��е�ƫ�����������С
    *
    * \param type �������ͣ�����ö��ֵ�ο�PropertyType����
    * \param offset �������������ļ��е�ƫ����
    * \param size �����ö���Ĵ�С
    * \param isDay ָ����Ҫ��ȡ�����ò�������������ģʽ��������Ǻ�ҹ
    */
    void GetOffsetSize(short type, int &offset, int &size, bool isDay);
  
  private:
    /// File name
    tstring m_fileName;

    /// File utilities
    const CFileBasic &m_fileBasic;

    /// Path utilities
    const CPathBasic &m_pathBasic;
  };
}

#endif