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
#ifndef _UEXML_XMLDOCUMENT_H
#define _UEXML_XMLDOCUMENT_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEXML_BASE_H
#include "uexml.h"
#endif

// Refer to std::string etc definition
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

//
#pragma warning(push)
#pragma warning(disable: 4251)  // X needs to have dll-interface to be used by clients of class Z

/// UeXml namespace
namespace UeXml
{
  // Forward declaration
  class CXmlElement;

  /*! \class CXmlDocument
  *
  * \brief XML�ĵ����壬�Ƕ�xml�ļ��ĳ���һ��CXmlDocument�����Ӧһ��xml�ļ�
  *
  * A CXmlDocument represents a XML file. It holds a pointer on the root XmlElement of the document. 
  * It also holds the encoding and style sheet used.   
  */
  class UEXML_CLASS CXmlDocument
  {
  public:
    //
    // Constructors and deconstructor
    //
    /*!
    * \brief Constructs a CXmlDocument object.
    *
    * \param Encoding used in the XML file (default is Latin-1, ISO-8859-1 ).
    * \param Name of the XSL style sheet file used. If empty then no style sheet will be specified in the output.
    */
    CXmlDocument(const tstring &fileName, const std::string &encoding = "", const std::string &styleSheet = "");

  private:
    // Doesn't permit outside declare this class as stack variable except for CXmlOutputter
    friend class CXmlWriter;

    virtual ~CXmlDocument();

  private:
    /**
    * Prevents the use of xml document
    */
    CXmlDocument(const CXmlDocument &copy);

    /**
    * Prevents the use of xml document
    */
    void operator =(const CXmlDocument &copy);

  public:
    /*!
    * \brief ��ȡxml����
    */
    std::string Encoding() const;

    /*!
    * \brief ����xml����
    *
    * \param encoding XML�ĵ��ı���
    */
    void SetEncoding(const std::string &encoding = "");

    /*!
    * \brief ��ȡStyleSheet
    */
    std::string StyleSheet() const;

    /*!
    * \brief ����StyleSheet
    *
    * \param styleSheet
    */
    void SetStyleSheet(const std::string &styleSheet = "");

    /*!
    * \brief �����ļ���
    *
    * \param fileName xml�ļ���
    */
    void SetStream(const tstring &fileName);

    //
    //
    //
    /*!
    * \brief ���ø��ڵ�
    *
    * \param rootElement ָ����ڵ�����ָ��
    */
    void SetRootElement(const CXmlElement *rootElement);

    /*!
    * \brief ��ȡ���ڵ�
    */
    CXmlElement &RootElement() const;

    /*!
    * \brief ��ӽڵ�
    *
    * \param oneElement ָ����ӽڵ��ָ��
    */
    void AddElement(CXmlElement *oneElement);

    /*!
    * \brief ɾ��ָ���ڵ�
    *
    * \param idx Ҫɾ���ڵ������
    */
    void RemoveElement(int idx);

    /*!
    * \brief ��ȡָ���ڵ�
    *
    * \param idx �ڵ�����
    */
    CXmlElement *GetElement(int idx);

    //
    //
    //
    /*!
    * \brief ִ��д�����
    */
    void Write();

    /*!
    * \brief ���xml�ĵ����ַ�����ʾ
    */
    std::string ToString() const;

  protected:
    // Concrete outputer, maybe disk file, memory,etc
    tstring m_fileName;
    std::ofstream m_stream;

    // The contents of one xml document
    std::string m_encoding;
    std::string m_styleSheet;
    CXmlElement *m_rootElement;
  };
}

#pragma warning( pop )
#endif
