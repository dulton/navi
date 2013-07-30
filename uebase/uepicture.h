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
#ifndef _UEBASE_UEPICTURE_H
#define _UEBASE_UEPICTURE_H

// Refer to EXPORT & IMPORT defintions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to picture basic definitions
#ifndef _UEBASE_PICTUREBASIC_H
#include "picturebasic.h"
#endif

// Refer to CPictureBasic::PictureBasic etc basic definitions
#ifndef _UEBASE_PICTURELOADER_H
#include "pictureloader.h"
#endif

// Refer to how to load one dynamic DLL
#ifndef _UEBASE_DYNLIB_H
#include "dynlib.h"
#endif

/// UeBase namespace
namespace UeBase
{
  // Forward classes
  class CFileBasic;
  class CPathBasic;

  /**
  * \brief This class is against different format pictures and responsible for rendering them. There are mainly four 
  * ways to get picture data: RES DLL for __UE_WINDOWS__, corresponding picture file(*.bmp/*.png), direct memory description 
  * and CPictureLoader for self-format definition.
  *
  * \detail Currently, this class would support BMP/PNG two kinds of picture formats.The general
  * usage of this class as below:
  * 1) Specify one data source: resource DLL or UIB file or directly one BMP/PNG file or directly one memory block
  * 2) Specify the picture ID needed to be fetched from above data source
  * 3) Specify rendering specification, for example, pos informtion, mask color etc
  * 4) Render the fetched or specified picture against one device context, for example HDC or AGG memory etc
  */
  class UEBASE_CLASS CUePicture
  {
    // Disallow automatically and implicitly usage
    CUePicture(const CUePicture &other);
    void operator=(CUePicture &other);

  public:
    /**
    * \brief Different ways for loading one picture
    */
    enum DataSource
    {
      DS_Unknown = 0,
      DS_ResDLL,
      DS_MyLoader,
      DS_DirectFile,
      DS_DirectMemory,
      DS_Max
    };

    //
    // Constructor & deconstructor
    //
    /**
    * \brief ���캯��
    */
    CUePicture();

    /**
    * \brief ��������
    */
    virtual ~CUePicture();

    //
    // Different ways to specify image data source, for example, resource DLL, UIB loader, one 
    // plain file or a block of memory etc
    //
    /**
    * \brief TODO:δʹ�õĽӿ�
    */
    bool LoadResModule(const tstring &resFile);

    /**
    * \brief TODO:δʹ�õĽӿ�
    */
    void *GetResHandle();

    /**
    * \brief TODO:δʹ�õĽӿ�
    */
    void UnloadResModule();

    /**
    * \brief ����ͼ�������
    *\param path pic��·��
    * \param type ���������ͣ��μ�LoaderType���塣
    * \param isCached �Ƿ�ʹ�û������
    */
    bool SetLoader(TCHAR* path, short type, bool isCached = true);

    /**
    * \brief ����ͼ�����������
    *
    * \param type ���������ͣ��μ�LoaderType���塣
    */
    void SetLoadType(unsigned int type)
    {
      m_isLoaded = type;
    }

    /**
    * \brief ��ȡͼ�����������
    *
    * \return ָ��ͼ���������ָ��
    */
    CPictureLoader *GetLoader();

    /**
    * \brief �ͷ�ͼ�������
    */
    void ReleaseLoader();

    /**
    * \brief This file can be PNG or BMP
    *
    * \param oneFile ͼ���ļ���
    */
    void SetPictureFile(const tstring &oneFile);

    /**
    * \brief
    *
    * \param buf ͼ�����ݻ�����ָ��
    * \param format �μ�PictureType����
    */
    void SetPictureBuf(char *buf, short format);

    //
    // Methods for getting one picture against different loaded mechansim
    //
    /**
    * \brief ��ȡָ����ͼ����Դ,������ͷ�֮ǰ��ȡ��ͼƬ,��Ҫ�Լ�ȥ�ͷ�ͼƬ��
    *
    * \param resID ͼ����Դ��ʶ��
    * \param isReleasePrevPic �Ƿ��ͷŵ�֮ǰ��ͬ��ͼ����Դ��
    * \return ָ����ͼ������
    */
    const CPictureBasic::PictureBasic &GetPicture(unsigned int resID, bool isReleasePrevPic = true);

    /**
    * \brief �ͷ�ͼƬ��Դ
    * ��Loaderʹ���˻��棬�򲻻��ͷ��ڴ棬����ʼ���ڴ�����
    * ��δʹ�û��棬���ͷŸ�ͼƬռ�õ��ڴ档
    * \param resID Ҫ�ͷŵ�ͼƬ��ID
    */
    void ReleasePicture(unsigned int resID);

    /**
    * \brief �ͷŵ�ǰ��ͼƬ��Դ
    * ��Loaderʹ���˻��棬�򲻻��ͷ��ڴ棬����ʼ���ڴ�����
    * ��δʹ�û��棬���ͷŸ�ͼƬռ�õ��ڴ档
    */
    void ReleasePicture();
    //
    // Methods for rendering one picture or image
    //
    /**
    * \brief ����ͼ�����Ⱦ������
    *
    * \param spec ��Ⱦ������
    */
    void SetRenderingSpec(CPictureBasic::RenderingSpec &spec);

    /**
    * \brief ��ȡͼ�����Ⱦ������
    *
    * \return ��Ⱦ������
    */
    const CPictureBasic::RenderingSpec &GetRenderingSpec();

    /**
    * \brief ��ȾͼƬ��ͼ���豸����
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dcWidth Ŀ��������
    * \param dcHeight Ŀ������߶�
    * \param sx Ŀ����������Ͻ�λ��
    * \param sy Ŀ����������Ͻ�λ��
    * \param xOrder ͼ���ڲ����еĺ���order
    * \param yOrder ͼ���ڲ����е�����order
    * \param spec ��Ⱦ������
    */
    bool DirectDraw(unsigned char *bits, unsigned char **rows, int dcWidth, int dcHeight, int sx, int sy, int xOrder, int yOrder, const CPictureBasic::RenderingSpec &spec);

    /**
    * \brief ��ȾͼƬ��ͼ���豸����
    * 
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dcWidth Ŀ��������
    * \param dcHeight Ŀ������߶�
    * \param sx Ŀ����������Ͻ�λ��
    * \param sy Ŀ����������Ͻ�λ��
    * \param srcExtent Դͼ��ľ�������(����ֻ��Դͼ���ĳһ����)
    * \param style ��Ⱦ��ʽ
    */
    bool DirectDraw(unsigned char *bits, unsigned char **rows, int dcWidth, int dcHeight, int sx, int sy, const CGeoRect<int> &srcExtent, short style);

    //
    //
    // Static functions supplied by PNG opensouce
    //
    /**
    * \brief ���ļ��м���ͼ������(Against one picture file)
    *
    * \param oneFile ͼ���ļ�
    * \param onePicture ͼ������
    */
    static bool LoadPicture(const tstring &oneFile, CPictureBasic::PictureBasic *onePicture);

    /**
    * \brief ���ڴ��м���ͼ������(Against one picture memory)
    *
    * \param buffer ͼ�񻺳���
    * \param size ��������С
    * \param onePicture ͼ������
    */
    static bool LoadPicture(char *buffer, int size, CPictureBasic::PictureBasic *onePicture);


    /**
    * \brief ��ͬ��С��ͼ�� Alphaͼ����
    * \param srcPic Ҫ��ϵ�ͼƬ
    * \param spec ��Ⱦ������
    */
    bool BlendSameSizeRGBAImage(const CPictureBasic::PictureBasic & destPic, const CPictureBasic::PictureBasic &srcPic, const CPictureBasic::RenderingSpec &spec);
  private:
    // Relatives
    friend class CPictureLoader;

    //
    //
    //
    /**
    *
    */
    void Reset();

    /**
    *
    */
    bool Src2Dest(unsigned char *bits, unsigned char **rows, int dcWidth, int dcHeight, CGeoRect<int> &src, CGeoRect<int> &dest, short style);

    /**
    *
    */
    void RenderPicture(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const CGeoRect<int> &src, short style);

  protected:
    // Unique
    int m_idx;

    // Picture description
    CPictureBasic::PictureBasic m_data;

    // Loader way for getting different images
    CPictureLoader *m_loader;

    // Picture resources: encapsulated DLL or directly BMP file
    CDynamicLibrary m_resDLL;

    // One plain file to get PNG/BMP format image
    tstring m_picFile;

    // A memory block storing PNG/BMP image
    // Note: The life time of below memory should be decided by outside since it is directly assigned by outside
    char *m_picBuf;

    // Rendering parameters
    CPictureBasic::RenderingSpec m_renderingSpec;

    // Different loaded ways
    unsigned int m_isLoaded;

    // Refer to basic picture functions
    const CPictureBasic &m_picBasic;
    const CFileBasic &m_fileBasic;
    const CPathBasic &m_pathBasic;
  };
}
#endif