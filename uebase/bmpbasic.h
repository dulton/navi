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
#ifndef _UEBASE_BMPBASIC_H
#define _UEBASE_BMPBASIC_H

// Refer to EXPORT & IMPORT definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to stdio.h etc stand C headers
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to OS-depedent headers
#ifndef _MAKE_OPTIONS_H
#include "makeopts.h"
#endif

// Refer to picture basic definitions
#ifndef _UEBASE_PICTUREBASIC_H
#include "picturebasic.h"
#endif

// Refer to CGeoRect
#ifndef _UEBASE_GEOMBASIC_H
#include "geombasic.h"
#endif

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4996 )  // Deprecated function calling

// UeBase namespace
namespace UeBase
{
  //
  enum org_e
  {
    org_mono8   = 8,
    org_color16 = 16,
    org_color24 = 24,
    org_color32 = 32,
    org_color48 = 48,
    org_color64 = 64
  };

  /**
  * \brief This class is mainly responsible for BMP structure creation, data analyzation etc.
  */
  class UEBASE_CLASS CBmpBasic
  {
    // Disallow implicitly creation etc
    CBmpBasic(const CBmpBasic&);
    const CBmpBasic& operator = (const CBmpBasic&);

  public:
    //
    // Constructors & deconstructor
    //
    /**
    * \brief ���캯��
    */
    CBmpBasic();

    /**
    * \brief ��������
    */
    ~CBmpBasic();

  public:
    //
    // Methods for BMP/DIB creation & deletion
    //
    /**
    * \brief �ͷ�bmp������ڴ���Դ
    */
    void Destroy();

    /**
    * \brief ����λͼ
    *
    * \param width λͼ���(������Ϊ��λ)
    * \param height λͼ�߶�(������Ϊ��λ)
    * \param org ����ö��ֵ�μ�org_e����
    * \param clear_val ���λͼ���ݣ�ÿ��λ�ĳ�ʼֵ
    */
    void Create(unsigned width, unsigned height, org_e org, unsigned clear_val = 256);

    /**
    * \brief �����豸�޹ص�λͼ
    *
    * \param h_dc ͼ���豸�������
    * \param width λͼ���
    * \param height λͼ�߶�
    * \param org ����ö��ֵ�μ�org_e����
    * \param clear_val ��ʼ����������ֵ
    */
    void *CreateDIBSection(void *h_dc, unsigned width, unsigned height, org_e org, unsigned clear_val=256);

    /**
    * \brief ���λͼ��ɫֵ������Ϊָ����ʼֵ
    *
    * \param clear_val ��ʼֵ
    */
    void Clear(unsigned clear_val=256);

    /**
    * \brief �趨λͼ������Ϣ��
    *
    * \param bmp ָ��λͼ��������ָ��
    */
    void AttachToBmp(void *bmp);

    /**
    * \brief ��ȡλͼ������Ϣ��
    *
    * \return ָ��λͼ��������ָ��
    */
    void* GetBitmapInfo() 
    { 
      return m_bmp; 
    }

    /**
    * \brief ���ļ��м���BMPͼ������
    * 
    * \param fd �򿪵�BMP�ļ���ʶ
    */
    bool LoadFromBmp(FILE *fd);

    /**
    * \brief ����ΪBMP�ļ�
    * 
    * \param fd �����BMP�ļ���ʶ
    */
    bool SaveAsBmp(FILE *fd) const;

    /**
    * \brief ���ļ��м���BMPͼ������
    *
    * \param fileName Ҫ�򿪵�bmp�ļ���
    */
    bool LoadFromBmp(const tstring &fileName);

    /**
    * \brief ����ΪBMP�ļ�
    * 
    * \param fileName �����bmp�ļ���
    */
    bool SaveAsBmp(const tstring &fileName) const;

    //
    //
    //
    /**
    * \brief BMPͼ����Ⱦ
    *
    * \param h_dc �豸�������
    * \param device_rect ��Ļ���η�Χ
    * \param bmp_rect λͼ�ľ��η�Χ
    */
    void Draw(void *h_dc, const CGeoRect<int> &device_rect, const CGeoRect<int> &bmp_rect) const;

    /**
    * \brief BMPͼ����Ⱦ
    * 
    * \param h_dc �豸�������
    * \param x ���Ͻ�x����
    * \param y ���Ͻ�y����
    * \param scale ���ű�
    */
    void Draw(void *h_dc, int x, int y, double scale=1.0) const;

    /**
    * \brief TODO:δʹ�õĽӿ�
    *
    * \param dest Ŀ�껺������ַ
    * \param width ���
    * \param height �߶�
    * \param device_rect ��Ļ���η�Χ
    * \param bmp_rect λͼ�ľ��η�Χ
    */
    void GetPart(unsigned char *dest, unsigned width, unsigned height, const CGeoRect<int> &device_rect, const CGeoRect<int> &bmp_rect) const;

    /**
    * \brief ��BMP����alpha���
    *
    * \param h_dc �豸�������
    * \param device_rect ��Ļ���η�Χ
    * \param bmp_rect λͼ�ľ��η�Χ
    */
    void Blend(void *h_dc, const CGeoRect<int> &device_rect, const CGeoRect<int> &bmp_rect) const;

    /**
    * \brief ��BMP����alpha���
    * 
    * \param h_dc �豸�������
    * \param x ���Ͻ�x����
    * \param y ���Ͻ�y����
    * \param scale ���ű�
    */
    void Blend(void *h_dc, int x, int y, double scale=1.0) const;

    //
    // Access methods
    //
    /**
    * \brief ���λͼ������ָ��
    */
    unsigned char* GetBuf();

    /**
    * \brief ���λͼ���
    */
    unsigned GetWidth() const;

    /**
    * \brief ���λͼ�߶�
    */
    unsigned GetHeight() const;

    /**
    * \brief ��ȡͼ��ÿ�е�λ��
    *
    * \return ÿ�е�λ��
    */
    int GetStride() const;

    /**
    * \brief ��ȡ��ǰBMP��ÿ���ص�λ��
    *
    * \return ÿ���ص�λ��
    */
    unsigned GetBpp() const { return m_bpp; }

    /**
    * \brief  ��ȡͼ���С
    *
    * \return int ͼ���С
    */
    int GetImgSize()
    {
      return m_img_size;
    }

    //
    // Auxiliary static functions
    //
    /**
    * \brief �ӻ������л�ȡBMP����
    *
    * \param _io_buffer ͼ�����ݵĻ�����
    * \param _io_max ���������ɷ��ʴ�С
    * \param _info UePicture�����ָ��
    * \return �ɹ�����true�����򷵻�false
    */
    static bool ToUePicture(char *_io_buffer, int _io_max, CPictureBasic::PictureBasic *_info);

    /**
    * \brief ֱ�Ӵ��ļ��л�ȡBMP����
    *
    * \param fileName BMP�ļ���
    * \param _info UePicture�����ָ��
    * \return �ɹ�����true�����򷵻�false
    */
    static bool ToUePicture(const tstring &filename, CPictureBasic::PictureBasic *_info);

    /**
    * \brief ��ȡBMP���������ݴ�С(������BMPͷ��������Ϣ��ͼ�����ݵĴ�С)
    *
    * \param bmp BMP���ݻ�����ָ��
    */
    static unsigned GetFullSize(void *bmp);

    /**
    * \brief ��ȡBMPͷ�Ĵ�С
    *
    * \param bmp BMP���ݻ�����ָ��
    */
    static unsigned CalcHeaderSize(void *bmp);

    /**
    * \brief ��ȡBMP��ɫ��(��ɫ��)��С
    * 
    * \param clr_used λͼ��ʹ�õ���ɫ��
    * \param bits_per_pixel ÿ���ص�λ��
    */
    static unsigned GetPaletteSize(unsigned clr_used, unsigned bits_per_pixel);

    /**
    * \brief ��ȡBMP��ɫ��(��ɫ��)��С
    *
    * \param bmp BMP���ݻ�����ָ��
    */
    static unsigned CalcPaletteSize(void *bmp);

    /**
    * \brief ���ͼ�����ݻ�����ָ��
    *
    * \param bmp BMP���ݻ�����ָ��
    */
    static unsigned char *CalcImgPtr(void *bmp);

    /**
    * \brief ����λͼ��������Ϣ
    *
    * \param width λͼ���
    * \param height λͼ�߶�
    * \param bits_per_pixel ���ظ�ʽ��ÿ���ص�λ��
    */
    static void *CreateBitmapInfo(unsigned width, unsigned height, unsigned bits_per_pixel);

    /**
    * \brief ������ɫ��
    *
    * \param bmp BMP���ݻ�����ָ��
    */
    static void CreateGrayPalette(void *bmp);

    /**
    * \brief ��ȡͼ��ÿ�е�λ��
    *
    * \param width ͼ����
    * \param bits_per_pixel ÿ���ص�λ��
    */
    static unsigned GetStride(unsigned width, unsigned bits_per_pixel);        

  private:
    //
    //
    //
    /**
    *
    */
    void CreateFromBmp(void *bmp);

    /**
    *
    */
    void *CreateDIBFromArgs(void *h_dc, unsigned width, unsigned height, unsigned bits_per_pixel);

  private:
    void *m_bmp;	//BITMAPINFO
    unsigned char *m_buf;
    unsigned m_bpp;
    bool m_is_internal;
    unsigned m_full_size;
    unsigned m_img_size;
  };
}


#endif
