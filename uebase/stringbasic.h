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
#ifndef _UEBASE_STRINGBASIC_H
#define _UEBASE_STRINGBASIC_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to tstring etc
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to DBG logger
#ifndef _UEBASE_DBGTRACER_H
#include "dbglogger.h"
#endif

// Erase compile warning
#pragma warning( push )
#pragma warning( disable: 4996 )  // Deprecated function calling
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

// Here two methods for spelling conversion and as far it keeps both
// but in future it should remove one of both kinds since codes seems clumsy caused by compiling MACROES
namespace UeGui
{
  class CInputSpellingHook;
}
// Declare namespace
namespace UeBase
{
  // Forward class
  class CMemVector;

  /**
  * \brief As a singletion to encapsulate different usful string operations, for examples, ASCII/UNICODE conversion, different
  * character set conversion etc.
  */
  class UEBASE_CLASS CStringBasic
  {
		friend class UeGui::CInputSpellingHook;
    /// When translating chinese string into its spelling, the maximum is
    static const int MAXSPELLINGLENGTH = 256;

    // Only be got as a singletion and disallow the automatically and implicitly creation
    CStringBasic(const CStringBasic &other);
    void operator=(const CStringBasic &other);

    /**
    * \brief ƴ��
    */
    struct SpellingItem
    {
      int m_asciiCode;
      char m_spelling[7];
    };

    /**
    * \brief ���캯��
    */
    CStringBasic();

    /**
    * \brief ��������
    */
    ~CStringBasic();

  public:
	  typedef bool (*ascStringPtrCmp)(const char *,const char *);
    //
    // Methods about CHINESE string
    //
    /**
    * \brief ��ȡ����ƴ��
    * 
    * \param cnStr �����ַ���
    * \param spelling ����ƴ��
    */
    void GetSpelling(const tstring &cnStr, char *spelling) const;

    /**
    * \brief ��ȡ����ƴ��������ĸ
    *
    * \param cnStr �����ַ���
    * \param spelling ��ƴ
    */
    void GetAcronym(const tstring &cnStr, char *spelling) const;

    /**
    * \brief �������ĸ
    *
    * \param bytes C����ַ���
    * \param length �ַ�������
    * \param spelling ����ĸ
    */
    void GetAcronym(const char *bytes, int length, char *spelling) const;

    /**
    * \brief ת�����ı��룬��BIG5��GB2312(�ϸ���˵��code page 936)��
    *
    * \param bigStr big5������ַ���
    * \param gbStr gb������ַ���
    */
    void Big2Gb(const tstring &bigStr, tstring &gbStr) const;

    /**
    * \brief ת�����ı���ӣ�GB2312��BIG5��
    *
    * \param gbStr gb������ַ���
    * \param bigStr big5������ַ���
    */
    void Gb2Big(const tstring &gbStr, tstring &bigStr) const;

    //
    // Methods about conversion between different character representions
    //
    /**
    * \brief �����ַ������ַ���ת��Ϊ���ֽڱ�ʾ���ַ���(������֧�ֲ���)
    * 
    * \param wStr ���ַ��ַ���
    * \param aStr ���ֽ��ַ���
    * \param num �ַ���
    */
    int Wcs2Ascii(wchar_t* wStr, char *aStr, int num) const;

    /**
    * \brief �����ֽڱ����ַ���ת��Ϊ���ַ������ַ���(������֧�ֲ���)
    *
    * \param aStr ���ֽ��ַ���
    * \param wStr ���ַ��ַ���
    * \param num �ַ���
    */
    int Ascii2Wcs(char* aStr, wchar_t *wStr, int num) const;

    /**
    * \brief �����ַ����������ַ���ת��Ϊ���ֽڱ�ʾ���ַ���
    * 
    * \param wStr ���ַ��ַ���
    * \param aStr ���ֽ��ַ���
    * \param num �ַ���
    */
    int Chs2Ascii(wchar_t* wStr, char *aStr, int num = -1) const;

    /**
    * \brief �����ֽڱ��������ַ���ת��Ϊ���ַ������ַ���
    *
    * \param aStr ���ֽ��ַ���
    * \param wStr ���ַ��ַ���
    * \param num �ַ���
    */
    int Ascii2Chs(const char* aStr, wchar_t *wStr, int num = -1) const;

    /**
    * \brief ȥ���ַ����еĿո�
    *
    * \param str ������ַ���
    */
    char *TrimSpace(char *str) const;

    //
    //
    //
    /**
    * \brief �����ַ����Ĺ�ϣ��
    *
    * \param str �ַ���
    * \param code ��ϣ��
    */
    void HashCode(unsigned char *str, unsigned int &code) const;

    /**
    * \brief ���������ַ���Ӧ��ascii���ȡ��ƴ�����ݲ����ã������ַ����Ӧascii��ֵ��ת����ϵδ֪��
    *
    * \param acsiiCode �����ַ���Ӧ��ascii
    * \return ƴ���ַ���
    */
    char *GetSpelling(int acsiiCode) const;

    /**
    * \brief ֱ�Ӵ�����ƴ��������л�ȡƴ��
    * \detail ��������ֵ���������л�ȡ��Ӧ������е���������������ȡ�ö�Ӧƴ��
    *
    * \param ������
    * \param ������
    * \return ƴ���ַ���
    */
    char *GetSpelling(int row, int col) const;

    //
    // Singleton
    //
    /**
    * \brief ���CStringBasic��Ψһʵ��
    */
    static const CStringBasic &Get();
private:

    /**
    * \brief ��������ascii����ƴ���Ķ�Ӧ��
    */
    void MakeSpellingTable();
    // Chinese spelling table
    static CMemVector m_spellingTable;
    static unsigned short m_chnCodeIndex[][191];
    static char m_chnSpellingTable[][8];
	//
#if __FOR_PC__
		static CDbgLogger m_log;
#endif
	/// Singletion
	static CStringBasic m_stringBasic;
	};
}

#endif
