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

#ifndef _UEBASE_UESETTINGSIO_H
#define _UEBASE_UESETTINGSIO_H

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
#ifndef _UEBASE_UESETTINGS_H
#include "uesettings.h"
#endif

//
#pragma warning( push )
#pragma warning( disable: 4251 )  
// Deprecated function calling

// Declare namespace UeBase
namespace UeBase
{
  /**
  * \class CUeSettingsIO
  *
  * \brief This class is mainly responsible for creation & updation of file uemaps.ztt
  */
  class UEBASE_CLASS CUeSettingsIO
  {
  public:
    
    /**
    * \enum SettingType
    * 
    * \brief Property Type
    */
    enum SettingType
    {
      ST_View,     //��ͼ����
      ST_Route,    //��������
      ST_Query,    //��ѯ����
      ST_Voice,    //��������
      ST_System,   //ϵͳ����
      ST_Capacity  //������Ϣ
    };
    //
    // ����&����
    //
    /**
    * \brief ���캯��
    */
    CUeSettingsIO();

    /**
    * \brief ��������
    */
   ~CUeSettingsIO();
  public:
    /**
    * \brief ��ȡ�����ļ����ļ�ͷ
    *
    * \param settingsHeader �ļ�ͷ��Ϣ
    */
    void GetHeader(SettingsHeader &settingsHeader);

    /**
    * \brief ���������ļ����ļ�ͷ
    *
    * \param settingsHeader �ļ�ͷ��Ϣ
    */
    void UpdateHeader(SettingsHeader &settingsHeader);

    /**
    * \brief ���ָ�������ò���
    *
    * \param type ����ö��ֵ�鿴SettingType����
    * \param settings ��������ö��󣬲ο�uesettings.h�еĶ���
    * \param count ���ö������Ŀ
    */
    void GetSettings(short type, void **settings, int count);

    /**
    * \brief ����ָ�������ò���
    *
    * \param type �������ͣ�����ö��ֵ�鿴SettingType����
    * \param settings ��������ö��󣬲ο�uesettings.h�еĶ���
    * \param count ���ö������Ŀ
    */
    void UpdateSettings(short type, void *settings, int count);

    /**
    * \brief ����������Ϣ
    *
    * \param settings �������������
    * \param offset �������������ļ���ƫ����
    * \param size �����õĴ�С
    */
    void UpdateSettings(void *settings, int offset, int size);

    /**
    * \brief �����������ͻ�����������ļ��е�ƫ�����������С
    * 
    * \param type �������ͣ�����ö��ֵ�鿴SettingType����
    * \param offset �������������ļ��е�ƫ����
    * \param size �����ö���Ĵ�С
    */
    void GetOffsetSize(short type, int &offset, int &size);   
    /**
    * \brief ��ȡ�ļ��İ汾
    */
    const char* GetFileVer();
  private:
    //���������ļ�
    void ReWriteFile();
  protected:
    /// File name
    tstring m_fileName;

    /// File utilities
    const CFileBasic &m_fileBasic;

    /// Path utilities
    const CPathBasic &m_pathBasic;
  };
}

#endif