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
#ifndef _UEBASE_PNGBASIC_H
#define _UEBASE_PNGBASIC_H

// Refer to EXPORT & IMPORT definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to PNG headers
#ifndef PNG_H
#include "png\png.h"
#endif

// Refer to CHAR header files
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
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
  // Forward classes
  class CFileBasic;
  class CPathBasic;

  /**
  * \brief Utility functions encapsulated for PNG file.
  */
  class UEBASE_CLASS CPngBasic
  {
    // Disallow implicitly usage ...
    CPngBasic(const CPngBasic &other);
    const CPngBasic &operator=(const CPngBasic &other);

  public:
    //
    // Constructors & deconstructor
    //
    /**
    * \brief ���캯��
    */
    CPngBasic();

    /**
    * \brief ��������
    */
    ~CPngBasic();

    //
    // Get PNG data serving for CUePicture
    //
    /**
    * \brief Get PNG data directly from one file.
    *
    * \param file PNG�ļ���
    * \param data ͼ������
    */
    static bool ToUePicture(const tstring &file, CPictureBasic::PictureBasic *data);

    /**
    * \brief Get PNG data directly from one memory.
    *
    * \param buf ����ͼ�����ݵĻ�����
    * \param size ��������С
    * \param data ���ص�ͼ������
    */
    static bool ToUePicture(char *buf, int size, CPictureBasic::PictureBasic *data);

    //
    // Methods as a PNG file reader
    //
    /**
    * \brief ��ȡPNG�ļ�
    *
    * \param fileName PNG�ļ���
    * \param isFlip
    */
    bool Load(const tstring &fileName, bool isFlip = false);

    /**
    * \brief ����ΪPNG�ļ�
    *
    * \param PNG�ļ���
    */
    bool Save(const tstring &fileName); 

    //
    //
    //
    /**
    * \brief TODO:�˽ӿڶ�����bmp�Ľӿڲ���˳�򲢲�һ��
    * 
    * \param dest Ŀ�껺������ַ
    * \param dev_rect ͼ���豸�ľ��η�Χ
    * \param width ���
    * \param height �߶�
    * \param png_rect PNGͼ��ľ��η�Χ
    */
    bool GetPart(unsigned char *dest, const CGeoRect<int> &dev_rect, int width, int height, const CGeoRect<int> &png_rect);

    //
    //
    //
    /**
    * \brief �ж�ָ���ļ��Ƿ�ΪPNG
    *
    * \param file �ļ���
    * \return ���ָ���ļ���PNG�ļ��򷵻�true�����򷵻�false��
    */
    bool IsPNG(const tstring &file) const;

    /**
    * \brief �жϻ��������Ƿ�ΪPNGͼ������
    * 
    * \param buf ������ָ��
    * \return ���PNG�򷵻�true�����򷵻�false��
    */
    bool IsPNG(char *buf) const;

    /**
    * \brief �ж�ͼ���Ƿ��Ѿ�����
    *
    * \return ��Ч��ͼ���򷵻�true�����򷵻�false
    */
    bool IsGood() const;

    /**
    * \brief ���ͼ����
    *
    * \return ͼ����(���ص�λ)
    */
    int GetWidth() const;

    /**
    * \brief ���ͼ��߶�
    *
    * \return ͼ��߶�(���ص�λ)
    */
    int GetHeight() const;

    /**
    * \brief ���ͼ�����ݵ�BGRA��ɫģʽ��ʾ
    *
    * \return BGRAģʽ��ͼ�����ݻ�����
    */
    unsigned char *GetBGRA() const;

  protected:
    //
    // returns true if the specified file is a png file
    //
    /**
    * converts the png bytes to BGRA
    */
    bool ExtractData(png_structp& PngPtr, png_infop& InfoPtr);

    /**
    * gets the data from an 8-bit rgb image
    */
    unsigned char* ToRGB8(png_structp& PngPtr, png_infop& InfoPtr) const;

    /**
    * gets the data from an 8-bit rgb image with alpha values
    */
    unsigned char* ToRGBA8(png_structp& PngPtr, png_infop& InfoPtr) const;

    /**
    * gets the data from an 8-bit monochrome image
    */
    unsigned char* ToGrey8(png_structp& PngPtr, png_infop& InfoPtr) const;

    /**
    * gets the data from an 8-bit monochrome image with alpha values
    */
    unsigned char* ToGreyA8(png_structp& PngPtr, png_infop& InfoPtr) const;

    /**
    *
    */
    bool DoFlip();

  private:
    //
    bool m_good;
    int m_width;
    int m_height;
    unsigned char *m_bgra;

    //
    const CFileBasic &m_fileBasic;
    const CPathBasic &m_pathBasic;
  };
}
#endif