#ifndef _UEXML_XMLREADEREX_H
#define _UEXML_XMLREADEREX_H

#include "xmlnode.h"
#include "CXMLReaderImpl.h"

using namespace irr::io;

/// �ṩ���XML�ĵ���һϵ�в����ӿ�
namespace UeXml
{
	/*! \class CXmlReaderEx
	*
	* \brief XML�����������ڴ�xml�ļ��л�ȡ�ڵ�����
	*/
  template<class char_type>
  class CXmlReaderEx
	{
	public:
		/*!
		* \brief Ĭ�Ϲ��캯��
		*/
    CXmlReaderEx() : m_xml_reader(NULL), m_xmlroot(NULL)
		{
      
		}
		/*!
		* \brief ���캯��
		*
		* \param xmlFile xml�ļ���
		*/
		CXmlReaderEx(const char *xmlFile) : m_xml_reader(NULL), m_xmlroot(NULL)
    {
      OpenXML(xmlFile);
      ParseXML();
    }

		/*!
		* \brief ��������
		*/
    ~CXmlReaderEx() 
    {
      Release();
    }
	public:
    /*
		* \brief ��Ҫ��ȡ��xml�ļ�
		*
		* \param xmlFile xml�ļ���
		*
		* \return �򿪳ɹ��򷵻�true�����򷵻�false��
		*/
		bool OpenXML(const char *xmlFile)
    {
      Release();
      m_xmlroot = new CXmlNode<char_type>(EXN_NONE, NULL);
      std::string node_name = "XMLDOC";
      m_xmlroot->SetName(node_name.c_str());
      assert(m_xmlroot);
      m_xml_reader = new irr::io::CXMLReaderImpl<char_type, IXMLBase>(new CFileReadCallBack(xmlFile));       
      assert(m_xml_reader);
      return m_xml_reader != NULL;
    }

		/*!
		* \brief �ж�xml�ļ��Ƿ��
		*
		* \return ���xml�Ѿ����򷵻�true�����򷵻�false��
		*/
		bool IsOpened()
		{
			return m_xml_reader != NULL;
		}

		/*!
		* \brief �ж��Ƿ����ָ���Ľڵ�
		*
		* \param nodeName �ڵ�����
		*
		* \return ��������򷵻�true�����򷵻�false��
		*/
		bool IsNodeExist(const std::string &nodeName)
    {
      return false;
    }

		/*!
		* \brief �رմ򿪵��ļ����ͷ���Դ��
		*/
		void Release()
		{
			if(m_xml_reader)
			{
				delete m_xml_reader;
			}
      m_xml_reader = NULL;
      if (m_xmlroot)
      {
        delete m_xmlroot;
      }			
      m_xmlroot = NULL;
		}
    /*
    *����XML�ļ�
    */
    void ParseXML() 
    {
      CXmlNode<char_type>* current_node = m_xmlroot;
      // parse the file until end reached
      m_xml_reader->reset();
      while(m_xml_reader && m_xml_reader->read())
      {
        EXML_NODE nodetype = m_xml_reader->getNodeType();
        const char_type *nodename = m_xml_reader->getNodeName();
        switch(nodetype)
        {
        case EXN_ELEMENT:
          {            
            const char_type* node_name_ = reinterpret_cast<const char_type*>(m_xml_reader->getNodeName());
            CXmlNode<char_type>* new_node = current_node->AddChild(node_name_, EXN_ELEMENT);

            int attribute_count = m_xml_reader->getAttributeCount();
             for (int i = 0; i < attribute_count; ++i)
             {  
                const char_type* attribute_name = m_xml_reader->getAttributeName(i);
                const char_type* attribute_value = m_xml_reader->getAttributeValue(i);
                new_node->AddAttribute(attribute_name, attribute_value);
             }
            //����ǰ�ڵ��������
            //����ǽڵ�
            m_xml_reader->read();
            new_node->SetValue(m_xml_reader->getNodeData());
            //��ǰ�ڵ�ָ��ָ������ӵ��ӽڵ�
            current_node = new_node;
            break;
          }
        case EXN_COMMENT:
          {
            //�����ע��
            current_node->AddChild(m_xml_reader->getNodeName(), EXN_COMMENT);
            break;
          }
        case EXN_ELEMENT_END:
          {
            //����ǽڵ�������򽫵�ǰ�ڵ�ָ��ָ�򸸽ڵ�
            current_node = current_node->GetParent();
            break;
          }
        }
      }
    }

    // ���ݽڵ�����ƶ�ȡ�ڵ�
    CXmlNode<char_type>* GetNode(const std::string &nodeName)
    {
       return m_xmlroot->GetNode(nodeName);
    }

    // ���ݽڵ����ƶ�ȡ��ǰ�ڵ�������ӽڵ�
    std::list<CXmlNode<char_type>*>* GetNodes(const std::string &nodeName)
    {
      CXmlNode<char_type>* xmlnode = GetNode(nodeName);
      if (xmlnode && xmlnode->HasChild())
      {
        return xmlnode->GetChildren();  
      }
      return NULL;
    }

		/*!
		* \brief ��ȡ�ڵ�����
		*
		* \param nodeName �ڵ�����
		* \param content ���ڷ��ؽڵ����ݵ��ַ���
		*/
		const char_type* GetContent(const std::string &nodeName, std::string &content) const
    {
      CXmlNode<char_type>* find_node = m_xmlroot->GetNode(nodeName);
      if (find_node)
      {
        return find_node->GetNodeValue();
      }
    }

		/*!
		* \brief ��ȡ�ڵ�����
		*
		* \param nodeName �ڵ�����
		* \param nodeField �����ֶ�
		* \param value ���ص�����ֵ
		*/
		const char_type* GetAttribute(const std::string &nodeName, const std::string &nodeField) const
    {
      CXmlNode<char_type>* xmlNode = m_xmlroot->GetNode(nodeName);
      if (xmlNode)
      {
        return xmlNode->GetAttributeByName(nodeField);
      }
      return NULL;
    }
	private:
		// Delegate to XML reader
		IIrrXMLReader<char_type, IXMLBase>* m_xml_reader;
    // XML�ļ����ڵ�
    CXmlNode<char_type>* m_xmlroot;
	};
}

#endif