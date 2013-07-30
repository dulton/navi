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
#ifndef _UEBASE_PICTURELOADER_H
#define _UEBASE_PICTURELOADER_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to tstring etc definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to its parent
#ifndef _UEBASE_MEMGARBAGE_H
#include "garbage.h"
#endif

// Refer to general picture definitions
#ifndef _UEBASE_PICTUREBASIC_H
#include "picturebasic.h"
#endif

// Erase compile warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling

// UeBase namespace
namespace UeBase
{
  // Forward classes
  class CFileBasic;
  class CPathBasic;
  class CUePicture;

  /**
  * \brief Using one structure as more compatible as possible to describe as more picture formats as possible, 
  * for example, PNG/BMP etc. And With efficiently and directly storing these structures and as basic I/O analyzing 
  * different picture formats.
  *
  * \detail File corresponding to this loader is mainly divided into two parts: STRING and PICTURE. STRING part would be
  * ordered in order to support binary predicate when finding one picture except for directly using one idx. 
  * For PICTURE part, different memory units can be taken as some pictures following the same picture specification 
  * or format. For example, one picture memory unit can be composited by hundreds of PNG data and we can use its 
  * CX and CY to get one of those PNG pictures, CUePicture is responsible for analyze that memory unit and render 
  * it on specified frame buffer.
  *
  */
  class UEBASE_CLASS CPictureLoader : public CMemoryConsumer
  {
  public:
    /**
    * \brief Different loader type corresponding to those pictures by specified categories.
    * Namely, those string or picture for POI rendering, for GUIDANCE rendering etc.
    */
    enum LoaderType
    {
      LT_Unknown	= -1,
      LT_GUI,
      LT_POI,
      LT_Guidance,
      LT_Max
    };

  protected:
    /// Relatives
    friend class CUePicture;

    /// Alow how many CUePicture objects are referencing to the same memory address
    const static int MAXREFCOUNT = 10;

    /**
    * \brief Loader or storing specification.
    *
    * Different picture part would be stored as below specification.
    */
    struct LoaderDef
    {
      // File positions for string and picture parts
      long m_strOffset;
      long m_picOffset;

      // Picture or image description
      short m_imgType;
      long m_picSize;
      CPictureBasic::PictureBasic m_data;

      // Simple memory cache mechansim
      short m_refCount;
      CUePicture *m_refObjects[MAXREFCOUNT];

      /**
      * \brief ��ʼ��
      */
      LoaderDef() : m_strOffset(0), m_picOffset(0), m_imgType(0), m_picSize(0), m_refCount(0)
      {
        int i = 0;
        for(; i < MAXREFCOUNT; i++)
        {
          m_refObjects[i] = 0;
        }
      }
    };

    // Disallow the complex usage of this class
    CPictureLoader(const CPictureLoader &other);
    void operator=(const CPictureLoader &other);

    //
    // Constructors & deconstructor
    //
    // As far, this class mainly be used as singletions: POI/Guidance/GUI/Default etc loaders
    /**
    * \brief ���캯��
    */
    CPictureLoader();

    /**
    * \brief ��������
    */
    virtual ~CPictureLoader();

  protected:
    //
    // Methods for open and close one kind of picture loader
    //
    /**
    * \brief ��ͼ�����ݰ��ļ�
    *
    * \param oneFile ͼ�����ݰ��ļ���
    * \param isLazy �Ƿ�ʹ���ӳټ��ز���
    */
    bool Open(const tstring &oneFile, bool isLazy = true);

    /**
    * \brief �ͷ���Դ���ر��ļ����
    */
    void Close();

    /**
    * \brief �ж��ļ��Ƿ��Ѿ���
    *
    * \return �ļ��Ѿ��򿪷���true�����򷵻�false��
    */
    bool IsReady();

  public:
    //
    // Methods for string part
    //
    /**
    * \brief TODO:δʹ�õĽӿ�
    *
    * \param idx �ַ�������
    */
    char *GetString(int idx);

    /**
    * \brief TODO:δʹ�õĽӿ�
    *
    * \param str �ַ���
    */
    int FindIdx(char *str);

    //
    // Methods for picture part
    //
    /**
    * \brief ��ȡָ��ͼ��Ĵ�С
    *
    * \param idx ͼ������
    * \return ͼ���С
    */
    int GetPictureSize(int idx);

    /**
    * \brief ��ȡͼ������
    *
    * \param idx ͼ������
    * \return ͼ�����ͣ����Ͷ���μ�PictureType
    */
    int GetPictureType(int idx);

    /**
    * \brief ����ָ����ͼ��
    *
    * \param idx ͼ������
    * \param onePicture ָ��CUePicture�����ָ��
    * \return ���سɹ�����true�����򷵻�false��
    */
    bool LoadPicture(int idx, CUePicture *onePicture);

    /**
    * \brief �ͷ�ָ����ͼ��
    *
    * \param idx ͼ������
    * \param onePicture ָ��CUePicture�����ָ��
    * \param isForce TODO:��ǰ��Ч�Ĳ���
    */
    void FreePicture(int idx, CUePicture *onePicture, bool isForce = false);

    //
    // Methods for simple cache operations
    //
    /**
    * \brief �����Ƿ�ʹ�û������
    *
    * \param isCached �Ƿ񻺴�
    */
    void IsCached(bool isCached);

    /**
    * \brief �ж��Ƿ�ʹ���˻������
    *
    * \return ���ʹ���˻��淵��true�����򷵻�false
    */
    bool IsCached();

    /**
    * \brief �ͷ���Դ����������ͼ������
    *
    * \param maxCount ����ͼ����Ŀ
    */
    void RemoveCache(int maxCount);

    //
    // Different kinds of UIB loader which has its own picture description or specification and as a singleton 
    // shared by different CNavPicture representing one access mechansim 
    //
    /**
    * \brief ���ݲ�ͬ��ͼ������ͻ�ȡ������ʵ��
    *
    *\param picPath uepic��·��
    * \param type ͼ������ͣ��μ�LoaderType����
    * \param isCached �Ƿ�ʹ�û������
    * \return ָ��ͼ�������ʵ����ָ��
    */
    static CPictureLoader *GetPictureLoader(TCHAR *picPath, short type, bool isCached = true);

    /**
    * \brief ����ͼ�������
    * 
    * \param type ͼ������ͣ��μ�LoaderType����
    */
    static void ReleaseLoaders(short type);

    //
    // Overrided function as one kind of memory consumer
    //
    /**
    * \brief �ͷ���Դ
    */
    virtual bool ForCollegues()
    {
      // Note:
      // Currently it seems no sense to release memory for other collegues since it should take few
      // in the meaning time it also need to be reopened as there maybe some pictures being rendered
      return false;
    }

  private:
    //
    //
    //
    /**
    *
    */
    void ReleasePicture(LoaderDef &onePic);

    /**
    * For lazy access
    */
    bool Open();

  private:
    // Load identifications
    long m_saveDate;	// 20060313 means 2006/03/13
    long m_saveTime;	// 112244 means 11: 33 : 44

    // Image part
    int m_picNum;
    LoaderDef *m_pictures;

    // String part
    long m_strOffset;
    long m_strSize;
    char *m_strings;

    // Loader itself
    tstring m_loaderFile;
    void *m_loaderHandle;

    const CFileBasic &m_fileBasic;
    const CPathBasic &m_pathBasic;

    // Simple memory cache mechansim since one picture maybe frequently used
    int m_loadedCount;
    bool m_isCached;

    /// Access pictures for POI rendering
    static CPictureLoader *m_poiLoader;
    /// Access pictures for guidance rendering
    static CPictureLoader *m_dirLoader;
    /// Access pictures for GUI rendering
    static CPictureLoader *m_guiLoader;
  };
}

#endif