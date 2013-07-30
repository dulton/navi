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
#ifndef _UEXML_XMLREADER_H
#define _UEXML_XMLREADER_H

// Refer to EXPORT & IMPORT macro defintions
#ifndef _UEXML_BASE_H
#include "uexml.h"
#endif

// Refer to std::string
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to IrrXmlReader
#ifndef __IRR_XML_H_INCLUDED__
#include "irrxml.h"
#endif
using namespace irr;
using namespace io;

/// UeXml namespace
/// �ṩ���XML�ĵ���һϵ�в����ӿ�
namespace UeXml
{
  /*! \class CXmlReader
  *
  * \brief XML�����������ڴ�xml�ļ��л�ȡ�ڵ�����
  *
  * Directly read one XML node to get its attributes and its value and this class directly benefit from 
  * opensource IRRXML project
  */
  class UEXML_CLASS CXmlReader
  {
    ///
    CXmlReader(const CXmlReader &other);
    const CXmlReader &operator=(const CXmlReader &other);

  public:
    //
    // ����&����
    //
    /*!
    * \brief Ĭ�Ϲ��캯��
    */
    CXmlReader() : m_xml(0)
    {
    }

    /*!
    * \brief ���캯��
    *
    * \param xmlFile xml�ļ���
    */
    CXmlReader(const char *xmlFile);

    /*!
    * \brief ��������
    */
    ~CXmlReader();

  public:
    //
    //
    //
    /*!
    * \brief ��Ҫ��ȡ��xml�ļ�
    *
    * \param xmlFile xml�ļ���
    *
    * \return �򿪳ɹ��򷵻�true�����򷵻�false��
    */
    bool Open(const char *xmlFile);

    /*!
    * \brief �ж�xml�ļ��Ƿ��
    *
    * \return ���xml�Ѿ����򷵻�true�����򷵻�false��
    */
    bool IsOpened()
    {
      return m_xml != 0;
    }

    /*!
    * \brief �ж��Ƿ����ָ���Ľڵ�
    *
    * \param nodeName �ڵ�����
    *
    * \return ��������򷵻�true�����򷵻�false��
    */
    bool IsExist(const std::string &nodeName);

    /*!
    * \brief �رմ򿪵��ļ����ͷ���Դ��
    */
    void Release()
    {
      if(m_xml)
      {
        delete m_xml;
      }
      m_xml = 0;
    }

    //
    // ��ȡ�ڵ���Ϣ
    //
    /*!
    * \brief ��ȡ�ڵ�����
    *
    * \param nodeName �ڵ�����
    * \param content ���ڷ��ؽڵ����ݵ��ַ���
    */
    void GetContent(const std::string &nodeName, std::string &content);

    /*!
    * \brief ��ȡ�ڵ�����
    *
    * \param nodeName �ڵ�����
    * \param nodeField �����ֶ�
    * \param value ���ص�����ֵ
    */
    void GetAttribute(const std::string &nodeName, const std::string &nodeField, std::string &value);

  private:
    // Delegate to XML reader
    IrrXMLReader *m_xml;
  };
}
#endif