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
#ifndef _UEBASE_TOKENSTRING_H
#define _UEBASE_TOKENSTRING_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Erase compile warning messages
#pragma warning( push )
#pragma warning( disable: 4996 )  // Deprecated function calling

// UeBase namespace
namespace UeBase
{
  /**
  * \brief �����趨�Ĵʷ���������ַ��������ַ����ָ�Ϊһ�����ַ���
  *        With specified token rules to analyze the different part of one text.
  *
  * \detail There are three kinds of pragma specification:
  * 1) Token Characters like comma which are used to seperate different text part also include \t and space character
  * 2) Builder Characters like "" and () which express referenced part and no need to remove middle \t and '' characters
  * 3) Divider Characters which mention just comment sentence and play no any sense except for taking it as one sentence
  *
  * There are also three analyzing rule using above three kinds of tokens:
  * 1) DEFAULT: Firstly get builder part, secondly get token part, lastly get divider part while considering space and '\t' by default as tokens
  * 2) NORMAL: Firstly get token part, secondly get divider part and lastly get builder part
  * 3) FIXED: Directly with specified column information, namely its width
  */
  class UEBASE_CLASS CTokenString
  {
    // Disallow automatically create this object
    CTokenString(const CTokenString &other);
    void operator=(const CTokenString &other);

  public:
    //
    // Constructors & deconstructor
    //
    /*!
    * \brief Default construcor means using default token setting.
    */
    CTokenString();

    /*!
    * \brief Constructor with parameters using specified token setting.
    *
    * \param token Token Characters like comma which are used to seperate different text part also include \t and space character
    * \param builder Characters like "" and () which express referenced part and no need to remove middle \t and '' characters
    * \param divider Characters which mention just comment sentence and play no any sense except for taking it as one sentence
    */
    CTokenString(const char* token, const char* builder, const char* divider);

    /*!
    * \brief destructor
    */
    ~CTokenString();

  public:
    //
    // Token rules
    //
    /*!
    * \brief ����Ĭ�ϵ��ַ�����������
    */
    void SetDefault();

    /*!
    * \brief �����ַ�����������
    *
    * \param token �ָ��� Token Characters like comma which are used to seperate different text part also include \t and space character
    * \param builder �ַ�����Ƿ������������õ��ַ�������ָ������
    *                Characters like "" and () which express referenced part and no need to remove middle \t and '' characters
    * \param divider ע�� Characters which mention just comment sentence and play no any sense except for taking it as one sentence
    */
    void SetToken(const char *token, const char *builder = 0, const char *divider = 0);

    /*!
    * \brief ����ָ���ĳ��Ƚ��зָ�
    *
    * \param no �Ӵ���
    * \param widths ÿ���Ӵ�����
    */
    void SetFixedWidth(int no, int *widths);

    //
    // Analyze and results operations
    //
    /*! 
    * \brief ��������ı��ָ�Ϊ�Ӵ�(TODO:�ӿ�����������)
    *
    * \param str ������ı�����
    * \param max Ҫ�������󳤶�
    */
    int Trim(const char *str, int max);

    /*!
    * \brief �Ƚ��������ַ������Ӷ��ɵ��ַ�����keyָ�����ַ����Ƿ���ͬ
    *
    * \param str Ҫ�Ƚϵ��ַ���
    * \param isCase �Ƿ��Сд����
    * \return �����ͬ����true�����򷵻�false��
    */
    bool IsSame(const char *str, bool isCase);

    /*!
    * \brief �Ƚ�ָ������λ�õ����ַ���(���Ǵ�ָ��λ����ļ������ַ������Ӷ��ɵ��ַ���)��oneKeyָ�����ַ����Ƿ���ͬ
    *
    * \param idx ����
    * \param oneKey Ҫ�Ƚϵ��ַ���
    * \param isCase�Ƿ��Сд����
    * \param num ����ʼ������ʼ���ӵ����ַ�������
    * \return �����ͬ����true�����򷵻�false��
    */
    bool IsSame(int idx, const char *oneKey, bool isCase, int num = 1);

    /*!
    * \brief ��ý���������ַ�������Ŀ
    */
    int Count();

    /*!
    * \brief ��ý���������ַ�������Ŀ
    */
    int GetCount();

    /*!
    * \brief ��ָ��λ�ÿ�ʼ����ָ�������ַ���
    *
    * \param start ���ҵ���ʼλ��
    * \param str Ҫ���ҵ��ַ���
    * \param isCase �Ƿ��Сд����
    * \return �ҵ��򷵻����������򷵻�-1
    */
    int Find(int start, const char *str, bool isCase) const;

    /*!
    * \brief ͨ��������ȡָ��λ�õķָ������ַ���
    *
    * \param idx ���ַ���������
    * \return ���ַ���
    */
    char *GetAt(int idx) const;

    /*!
    * \brief ���ص�[]��������ͨ��������ȡָ��λ�õķָ������ַ���
    *
    * \param idx ���ַ���������
    * \return ���ַ���
    */
    char *operator[](int idx) const;

    /*!
    * \brief ��մ�ָ������λ�ÿ�ʼ֮����������ַ���
    *
    * \param idx ��ʼ����
    */
    void RemoveAfter(int idx);

    /*!
    * \brief ��ս���������ͷ���Դ
    */
    void RemoveResult();

  private:
    //
    //
    //
    /**
    *
    */
    bool AddResult(const char *res, int max);

    /**
    *
    */
    bool FindToken(char token);

    /**
    *
    */
    bool FindDivider(char divider);

    /**
    *
    */
    char FindBuilder(char builder, bool &mode);

    /**
    *
    */
    int TrimByDefault(const char *str, int max);

    /**
    *
    */
    int TrimByNormal(const char *str, int max);

    /**
    *
    */
    int TrimByFixed(const char *str);

    /**
    *
    */
    void RemoveEndSpace(char *str);

  private:
    /// Maximum length of  
    const static short m_maxTokenSize = 64;

    /// Default setting
    bool m_isDefault;

    /// Pragma rules
    char m_strToken[m_maxTokenSize+1];
    char m_strBuilder[m_maxTokenSize+1];
    char m_strDivider[m_maxTokenSize+1];

    /// String results be analyzed
    char** m_strResults;
    int m_strNum;

    /// Analyze in fixed width
    int* m_columnWidth;
    int m_columnNum;
  };
}

#endif 
