#ifndef _UEXML_XMLNODE_H_
#define _UEXML_XMLNODE_H_

#include <assert.h>
#include <string>
#include <list>
#include <istream>
#include "irrXML.h"
#include "irrString.h"
#include "irrArray.h"

using irr::io::EXML_NODE;
using irr::core::array;

namespace UeXml
{
  //XML���࣬����չʹ��
  template<class char_type>
  class CXmlBase
  {
  public:
    CXmlBase() {}
    ~CXmlBase() {}
  protected:
    irr::core::string<char_type> m_node_name;
    irr::core::string<char_type> m_node_value;
  };

  template<class char_type>
  class CXmlNode : public CXmlBase<char_type>
  {
  public:
    CXmlNode(irr::io::EXML_NODE node_type, CXmlNode<char_type>* node_parent) : m_node_type(node_type), m_parent(node_parent) {}
    ~CXmlNode() 
    {
      ClearChild();
      ClearAttribute();
      // ע�⸸�ڵ����ⲿ�����ָ�룬���ﲻ���ͷţ��������ⲿ�����ͷ�
      m_parent = NULL;
    }
  public:
    struct SAttribute
    {
      irr::core::string<char_type> m_name;
      irr::core::string<char_type> m_value;
    };

    // ���õ�ǰ�ڵ������
    void SetName(irr::core::string<char_type>& node_name)
    {
      m_node_name = node_name;
    }

    void SetName(const char_type* node_name)
    {
      m_node_name = node_name;
    }

    // ���õ�ǰ�ڵ��ֵ
    void SetValue(irr::core::string<char_type>& node_value)
    {
      m_node_value = node_value;
    }

    void SetValue(const char_type* node_value)
    {
      m_node_value = node_value;
    }

    // ��ӵ�ǰ�ڵ���ӽڵ�
    CXmlNode<char_type>* AddChild(const char_type* node_name = NULL, EXML_NODE node_type = EXN_ELEMENT)
    {
      if (node_type != EXN_COMMENT && node_type != EXN_ELEMENT)
      {
        return NULL;
      }
      CXmlNode<char_type>* child = new CXmlNode<char_type>(node_type, this);
      if (node_name != NULL)
      {
        child->SetName(node_name);
      }
      m_children.push_back(child);
      return child;
    }

    // ��ӵ�ǰ�ڵ���ӽڵ�
    CXmlNode<char_type>* AddChild(irr::core::string<char_type>& node_name = NULL, EXML_NODE node_type = EXN_ELEMENT)
    {
      if (node_type != EXN_COMMENT && node_type != EXN_ELEMENT)
      {
        return NULL;
      }
      CXmlNode<char_type>* child = new CXmlNode<char_type>(node_type, this);
      if (node_name != NULL)
      {
        child->SetName(node_name);
      }
      m_children.push_back(child);
      return child;
    }

    // ��ӵ�ǰ�ڵ������ֵ
    void AddAttribute(const char_type* name, const char_type* value)
    {
      SAttribute attribute;
      attribute.m_name = name;
      attribute.m_value = value;
      m_attribute_list.push_back(attribute);
    }

    // ��ӵ�ǰ�ڵ������ֵ
    void AddAttribute(irr::core::string<char_type> name, irr::core::string<char_type> value)
    {
      SAttribute attribute;
      attribute.m_name = name;
      attribute.m_value = value;
      m_attribute_list.push_back(attribute);
    }

    // ɾ����ǰ�ڵ�������ӽڵ�
    void ClearChild()
    {
      for (std::list<CXmlNode<char_type>*>::iterator iter = m_children.begin();
           iter != m_children.end();
           ++iter)
      {
        CXmlNode<char_type>* child = *iter;
        assert(child != NULL);
        delete child;
      }
      m_children.clear();
    }

    // �����ǰ�ڵ�������б�
    inline void ClearAttribute()
    {
      m_attribute_list.clear();
    }

    inline bool HasParent()
    {
      return NULL != m_parent;
    }

    // ��ȡ��ǰ�ڵ�ĸ��ڵ�
    inline CXmlNode<char_type>* GetParent()
    {
      return m_parent;
    }

    //��ȡ��ǰ�ڵ���ӽڵ�(ע�����ﷵ�ص�����Ϊ����ָ�룬���Ҹú����Ǹ�������Ա����)
    inline std::list<CXmlNode<char_type>*>* GetChildren()
    {
       return &m_children;
    }

    //���ݽڵ����ƴ�ָ���ڵ㼰�ӽڵ��в���
    CXmlNode<char_type>* GetNode(const std::string& nodename)
    {
      std::list<CXmlNode<char_type>*>::iterator iter = m_children.begin();
      for (; iter != m_children.end(); ++iter)
      {
        CXmlNode<char_type>* child_node = *iter;
        const char* child_name_ = reinterpret_cast<const char_type*>(child_node->GetNodeName());
        if (strcmp(child_name_, nodename.c_str()) == 0)
        {
          //������ӽڵ����ҵ��򷵻��ҵ��ڵ�
          return child_node;
        }
        else
        {
          if (child_node->HasChild())
          {
            //�����ǰ�ڵ��Ҳ���,�������ӽڵ��м����ݹ����
            CXmlNode<char_type>* find_node = FindNode(child_node, nodename);
            if (find_node != NULL)
            {
              //������ӽڵ���ӽڵ��ҵ��򷵻��ҵ��ڵ�
              return find_node;
            }
          }
        }
      }
      return NULL;
    }

    //��ȡ�ڵ������
    inline const char_type* GetNodeName() const
    {
      return m_node_name.c_str();
    }

    inline const char_type* GetNodeValue() const
    {
      return m_node_value.c_str();
    }

    // ��ȡ�ڵ�����
    inline EXML_NODE GetNodeType() const
    {
      return m_node_type;
    }

    // ��ȡ�ӽڵ�ĸ���
    inline size_t GetChildCount() const
    {
      return m_children.size();
    }

    // ��ǰ�ڵ��Ƿ����ӽڵ�
    inline bool HasChild() const
    {
      return !m_children.empty();
    }

    // ��ȡ����ֵ���ֶ���
    inline int GetAttributeCount() const
    {
      return m_attribute_list.size();
    }

    // �����������ƶ�ȡ����ֵ
    const char_type* GetAttributeByName(const std::string& name) const
    {
      if (name.empty()) 
      {
        return NULL;
      }

      irr::core::string<char_type> name_ = name.c_str();

      for (int i=0; i<(int)m_attribute_list.size(); ++i)
      {
        if (m_attribute_list[i].m_name == name_)
        {
          return m_attribute_list[i].m_value.c_str();
        }
      }
      return NULL;
    }

    // �����������ƶ�ȡ����ֵ
    const char_type* GetAttributeByName(const char_type* name) const
    {
      if (!name) 
      {
        return NULL;
      }

      irr::core::string<char_type> name_ = name;

      for (int i=0; i<(int)m_attribute_list.size(); ++i)
      {
        if (m_attribute_list[i].m_name == name_)
        {
          return m_attribute_list[i].m_value.c_str();
        }
      }
      return NULL;
    }
  private:
    //��ָ���ڵ㼰�ӽڵ���ӽڵ����ָ�����ƵĽڵ�
    CXmlNode<char_type>* FindNode(CXmlNode<char_type>* xmlnode, const std::string& nodename)
    {
      if (!xmlnode->HasChild())
      {
        return NULL;
      }
      return xmlnode->GetNode(nodename);
    }
  private:
    // ��ǰ�ڵ�����
    EXML_NODE m_node_type;
    // ���ڽڵ�ĸ��ڵ㣬�ڹ��캯��ʱ�����ڵ㸳ֵ
    CXmlNode<char_type>* m_parent;
    // ��ǰ�ڵ���ӽڵ�
    std::list<CXmlNode<char_type>*> m_children;
    // ��ǰ�ڵ������б�
    array<SAttribute> m_attribute_list;
  };
}
#endif