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
#ifndef _UEBASE_PICTUREBASIC_H
#define _UEBASE_PICTUREBASIC_H

// Refer to EXPORT & IMPORT definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to CGeoRect<> definition
#ifndef _UEBASE_GEOMBASIC_H
#include "geombasic.h"
#endif

// UeBase namespace
namespace UeBase
{
  /**
  * \brief Encapsulate those general and useful functions for the general purpose of picture operation. This class is taken as 
  * a singleton since it is mainly be composited by those useful functions.
  *
  */
  class UEBASE_CLASS CPictureBasic
  {
    // Disallow automatically and implicitly creation etc...
    CPictureBasic(const CPictureBasic &other);
    void operator=(const CPictureBasic &other);

  public:
    /**
    * \brief Picture types
    */
    enum PictureType
    {
      PT_Unknown = -1,
      PT_BMP,
      PT_PNG,
      PT_Max
    };

    /**
    * \brief Color schema, namely how many bytes or bits to represent different color channels
    *
    * Note:
    * Refer to AGG opensource to get more color expressions
    **/
    enum ColorType
    {
      CT_Unknown = 0,
      CT_RGB,
      CT_RGBA,
      CT_GRAY8,
      CT_GRAYA8,
      CT_RGB555,
      CT_RGBA555,
      CT_RGB565,
      CT_RGBA565,
      CT_RGBPAL,
      CT_BGR
    };

    /**
    * \brief Different rendering way or styles.
    */
    enum RenderingStyle
    {
      /// ��͸����
      RS_Opaque = 0,
      /// ͸����
      RS_Transparent,
      /// ��͸����
      RS_Semitrans,
      RS_Gray
    };

    /**
    * \brief How to render one picture
    */
    struct RenderingSpec
    {
      int m_resIdx;

      int m_cx;
      int m_cy;

      unsigned char m_style;
      /// ������ɫ
      unsigned int m_maskClr;

      /**
      * \brief ��ʼ��
      */
      RenderingSpec() : m_resIdx(0), m_cx(0), m_cy(0), m_style(0), m_maskClr(0)
      {
      }

      /**
      * \brief ��ֵ������
      */
      const RenderingSpec &operator = (const RenderingSpec &other)
      {
        if(this == &other)
        {
          return *this;
        }

        m_resIdx = other.m_resIdx;
        m_cx = other.m_cx;
        m_cy = other.m_cy;
        m_style = other.m_style;
        m_maskClr = other.m_maskClr;

        return *this;
      }
    };

    /**
    * \brief Picture description to describle as more picture formats as possible.
    */
    struct PictureBasic
    {
      // Picture size
      int m_width;
      int m_height;

      // Picture basic attributes
      /// Bit per pixel
      int m_bpp;	
      /// ��ɫģʽ���μ�ColorType
      unsigned char m_clrType;
      /// �μ�PictureType
      unsigned char m_formatType;

      // BMP structure
      /// Here should be HBITMAP
      void *m_bmp;	
      /// Here should be BITMAPINFO
      void *m_bmpInfo;	
      /// BMP content memory
      unsigned char *m_bmpBase;	

      // For PNG structure or new storing mechansim, for example, RGB555 etc
      // Namely, even if we directly load one bitmap, we can re-layout memory in m_rows for new
      // store mechansim
      unsigned char **m_rows;

      /**
      * \brief ��ʼ��
      *
      * Note:
      * Since it refer to memmediator.h, it carry the re-definition of CT_Unknown.
      */
      PictureBasic() : m_width(0), m_height(0), m_bpp(0), m_formatType(PT_Unknown), m_clrType(CT_Unknown), 
        m_bmp(0), m_bmpInfo(0), m_bmpBase(0), m_rows(0)
      {
      }

      /**
      * \brief �ж��Ƿ�Ϊ��Ч��ͼ��
      *
      * \return ��Ч�򷵻�true�����򷵻�false��
      */
      bool IsValid()
      {
        return m_width > 0 && m_height > 0;
      }

      /**
      * \brief ��ֵ������
      */
      const PictureBasic &operator =(const PictureBasic &other)
      {
        if(this == &other)
        {
          return *this;
        }

        m_width = other.m_width;
        m_height = other.m_height;
        m_bpp = other.m_bpp;
        m_clrType = other.m_clrType;
        m_formatType = other.m_formatType;
        m_bmp = other.m_bmp;
        m_bmpInfo = other.m_bmpInfo;
        m_bmpBase = other.m_bmpBase;
        m_rows = other.m_rows;

        return *this;
      }

      /**
      * \brief Consider there maybe many objects sharing the same meory for one picture description, so it no need 
      * to release that memory unitl the loader know when and where is suitable to free those memories
      */
      void Reset()
      {
        m_bmpBase = 0;
        m_bmpInfo = 0;
        m_bmp = 0;
        m_rows = 0;

        m_width = 0;
        m_height = 0;
        m_bpp = 0;
        m_clrType = -1;
        m_formatType = PT_Unknown;
      }
    };

  protected:
    // 
    // Constructors & deconstructor
    //
    /**
    * \brief ���캯��
    */
    CPictureBasic()
    {
    }

    /**
    * \brief ��������
    */
    ~CPictureBasic()
    {
    }

  public:
    /**
    * \brief Singelton
    */
    static const CPictureBasic &Get();

    //
    //
    //
    //
    // Common utility functions for memory conversion in order to suppoet different storing mechansim
    // for one picture
    //
    /**
    * \brief ת��������ɫ��ʽ(��rgb24��rgb555)
    *
    * \param r rgb24��ɫ����
    * \param g rgb24��ɫ����
    * \param b rgb24��ɫ����
    * \return rgb555��ʽ(ÿ����ɫ������ռ5λ)����ɫֵ
    */
    unsigned short rgb24_2_rgb555(int r, int g, int b) const;

    /**
    * \brief ת��������ɫ��ʽ(��rgb24��rgb565)
    *
    * \param r rgb24��ɫ����
    * \param g rgb24��ɫ����
    * \param b rgb24��ɫ����
    * \return rgb565��ʽ(ÿ����ɫ������ռ5λ)����ɫֵ
    */
    unsigned short rgb24_2_rgb565(int r, int g, int b) const;

    /**
    * \brief ת��������ɫ��ʽ(��rgb555��rgb24)
    *
    * \param rgb555 rgb555��ʽ����ɫֵ
    * \return rgb24��ʽ����ɫֵ
    */
    unsigned int rgb555_2_rgb24(int rgb555) const;

    /**
    * \brief ת��������ɫ��ʽ(��rgb555��bgr24)
    *
    * \param p bgr24��ʽ����ɫֵ
    * \param rgb555 rgb555��ʽ����ɫֵ
    */
    void rgb555_2_bgr24(unsigned char *p, int rgb555) const;

    /**
    * \brief ��rgb555��ʽ����ɫ����alpha���
    * 
    * \param p ��Ͻ��
    * \param cr ��ɫ����
    * \param cg ��ɫ����
    * \param cb ��ɫ����
    * \param alpha alphaֵ
    */
    void blend_pix_555(unsigned short *p, unsigned cr, unsigned cg, unsigned cb, unsigned alpha) const;

    /**
    * \brief ��rgb565��ʽ����ɫ����alpha���
    * 
    * \param p ��Ͻ��
    * \param cr ��ɫ����
    * \param cg ��ɫ����
    * \param cb ��ɫ����
    * \param alpha alphaֵ
    */
    void blend_pix_565(unsigned short *p, unsigned cr, unsigned cg, unsigned cb, unsigned alpha) const;

    /**
    * \brief ��bgr24��ʽ����ɫ����alpha���
    * 
    * \param p ��Ͻ��
    * \param cr ��ɫ����
    * \param cg ��ɫ����
    * \param cb ��ɫ����
    * \param alpha alphaֵ
    */
    void blend_pix_bgr24(unsigned char *p, unsigned cr, unsigned cg, unsigned cb, unsigned alpha) const;

    /**
    * \brief ��rgb��ɫģʽ��ͼ���еõ�rgb555��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgb��ɫģʽ��ͼ���еõ�rgb565��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb_2_565(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgb��ɫģʽ��ͼ���еõ�bgr24��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��bgr��ɫģʽ��ͼ���еõ�rgb555��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_bgr_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��bgr��ɫģʽ��ͼ���еõ�rgb565��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_bgr_2_565(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��bgr��ɫģʽ��ͼ���еõ�bgr24��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_bgr_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgba��ɫģʽ��ͼ���еõ�rgb555��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgba_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgba��ɫģʽ��ͼ���еõ�rgb565��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgba_2_565(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgba��ɫģʽ��ͼ���еõ�bgr24��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgba_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned int maskClr) const;

    /**
    * \brief ��rgb pal��ɫģʽ��ͼ���еõ�rgb555��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb_pal_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgb pal��ɫģʽ��ͼ���еõ�bgr24��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb_pal_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, void *maskClr = 0) const;

    /**
    * \brief ��rgb pal��ɫģʽ��ͼ���еõ�rgb555��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    * \param maskClr ������ɫ
    */
    void copy_image_info_rgb_pal_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;

    /**
    * \brief ��rgb pal��ɫģʽ��ͼ���еõ�bgr24��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    * \param maskClr ������ɫ
    */
    void copy_image_info_rgb_pal_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;

    /**
    * \brief ��rgb555��ɫģʽ��ͼ���еõ�rgb555��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb555_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgb555��ɫģʽ��ͼ���еõ�rgb565��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb555_2_565(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgb555��ɫģʽ��ͼ���еõ�bgr24��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    */
    void copy_image_info_rgb555_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;

    /**
    * \brief ��rgb555��ɫģʽ��ͼ���еõ�rgb555��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    * \param maskClr ������ɫ
    */
    void copy_image_info_rgb555_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;

    /**
    * \brief ��rgb555��ɫģʽ��ͼ���еõ�rgb565��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    * \param maskClr ������ɫ
    */
    void copy_image_info_rgb555_2_565(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;

    /**
    * \brief ��rgb555��ɫģʽ��ͼ���еõ�bgr24��ͼ�����ݲ�д��Ŀ���ַ(DC)
    *
    * \param bits Ŀ�껺����
    * \param rows Ŀ�껺����
    * \param dest Ŀ���������
    * \param onePic Դͼ��
    * \param src Դͼ��ľ�������
    * \param maskClr ������ɫ
    */
    void copy_image_info_rgb555_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;



    /**
    * \brief ����rgba������
    *
    * \param p ��Ͻ��
    * \param cr ��ɫ����
    * \param cg ��ɫ����
    * \param cb ��ɫ����
    * \param alpha alphaֵ
    */
    void copy_pix_rgba(unsigned char *p, unsigned cr, unsigned cg, unsigned cb, unsigned alpha) const;
    
    /**
    * \brief ��������ͬ��С��rgbaͼ��ͨ��������˵ķ�ʽ��ϡ�
    *
    * \param dest_rows Ŀ��ͼ�񻺳���
    * \param src_rows Դͼ�񻺳���
    * \param rect ͼ������
    * \param maskClr ������ɫ
    */
    void blend_samesize_rgbaimage(unsigned char **dest_rows, unsigned char **src_rows, const CGeoRect<int> &rect, unsigned int maskClr) const;
  private:
    // Singleton
    static CPictureBasic m_pictureBasic;
  };
}
#endif