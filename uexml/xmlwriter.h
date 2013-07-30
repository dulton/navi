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
#ifndef _UEXML_XMLWRITER_H
#define _UEXML_XMLWRITER_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEXML_BASE_H
#include "uexml.h"
#endif

// Refer to tstring etc 
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

/// UeXml namespace
namespace UeXml
{
  // Forward classes
  class CXmlElement;
  class CXmlDocument;

  /*! \class CXmlWriter
  *
  * \brief XML�༭�ӿڣ�����д��ڵ����ݵ�XML�ļ�
  *
  * This class mainly benefits from XML part of CPPUNIT test framework
  */
  class UEXML_CLASS CXmlWriter
  {
    /// Disallow implicitly creation

  public:
    //
    //
    //
    /*!
    * \brief ���캯��
    *
    * \param fileName xml�ļ���
    * \param encoding xml����
    */
    CXmlWriter(const tstring &fileName, std::string &encoding = std::string("ISO-8859-1"));

    /*!
    * \brief ��������
    */
    ~CXmlWriter();

  public:
    //
    // ����
    //
    /*!
    * \brief ���������
    *
    * \param filename д���xml�ļ���
    */
    void SetStream(const tstring &fileName);


    /*!
    * \brief ���ñ���
    *
    * \param encoding xml����
    */
    void SetEndcoding(std::string &encoding);

    /*!
    * \brief Sets the XSL style sheet used.
    *
    * \param styleSheet
    * Name of the style sheet used. If empty, then no style sheet is used (default).
    */
    void SetStyleSheet(const std::string &styleSheet);

    //
    // Element����
    //
    /*!
    * \brief ���ø��ڵ�
    *
    * \param rootElement ָ����ڵ��ָ��
    */
    void SetRootElement(CXmlElement *rootElement);

    /*!
    * \brief ��ӽڵ�
    *
    * \param oneElement ָ����ӽڵ��ָ��
    */
    void AddElement(CXmlElement *oneElement);

    /*!
    * \brief ɾ���ڵ�
    *
    * \param idx Ҫɾ���ڵ�ı�ʶ
    */
    void RemoveElement(int idx);

    /*!
    * \brief ��ȡָ���Ľڵ�
    *
    * \param idx �ڵ��ʶ
    */
    CXmlElement *GetElement(int idx);

    //
    //
    //
    /*!
    * \brief ִ��д�����
    */
    void Write();

  private:
    /// Delgate XML format to below object
    CXmlDocument *m_xml;
  };
}
#endif