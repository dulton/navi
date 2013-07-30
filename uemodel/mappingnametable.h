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
#ifndef _UEMODEL_MAPPINGNAMETABLE_H
#define _UEMODEL_MAPPINGNAMETABLE_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Refer to tstring etc definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to its parent
#ifndef _UEMODEL_NAMETABLE_H
#include "netnametable.h"
#endif

// Refer to basic file operations
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

// Refer to basic path operations
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling
#pragma warning( disable: 4275 )  // Deprecated function calling
#pragma warning( disable: 4996 )  // Deprecated function calling

// Declare namespace
namespace UeModel
{
  /**
  * \brief ���Ʊ���ʽӿ�INameTable��ʵ�֣�ͨ��ʹ���ڴ�ӳ��ķ�ʽ��ȡ���ݡ�
  */
  class UEMODEL_CLASS CMappingNameTable : public INameTable
  {
  private:
    /// Disallow copy constructor & assignment function
    CMappingNameTable(const CMappingNameTable &other);
    const CMappingNameTable &operator=(const CMappingNameTable &other);

  public:
    //
    const static short MAXNAMELENGTH = 256;

    /**
    * \brief ���Ƽ�¼ʵ��Ķ���
    */
    struct NameRecord
    {
      //
      int m_offset;
      unsigned char m_size;
      char m_str[MAXNAMELENGTH];

      //
      NameRecord() : m_size(0)
      {
        m_str[0] = '\n';
      }

      //
      const NameRecord &operator = (const NameRecord &other)
      {
        //
        if(this == &other)
        {
          return *this;
        }

        //
        m_offset = other.m_offset;
        m_size = other.m_size;
        ::strcpy(m_str, other.m_str);

        //
        return *this;
      }
    };

    /// �������Ƽ�¼�ļ򵥻���
    typedef std::vector<NameRecord> SimpleCache;

    //
    //
    //
    /**
    * \brief ��ʼ��
    */
    CMappingNameTable(const tstring &indexFile, const tstring& nameFile) : m_indexFile(indexFile), m_nameFile(nameFile), 
      m_nameHandle(0), m_nameMap(0), m_nameData(0), m_indexHandle(0), m_indexMap(0), m_indexData(0),
      m_maxIndexOffset(0), m_maxNameOffset(0), m_fileBasic(CFileBasic::Get()), m_pathBasic(CPathBasic::Get())
    {
    }

    /**
    * \brief �ͷ���Դ
    */
    virtual ~CMappingNameTable()
    {
      Close();
    }

  public:
    //
    // Common methods
    //
    /**
    * \brief �����������
    */
    virtual void Delete();

    /**
    * \brief ���������ļ��ڴ�ӳ��
    */
    virtual bool Open();

    /**
    * \brief �ͷ�ӳ���ڴ�
    */
    virtual bool Close();

    /**
    * \brief ��ȡ����
    * 
    * \param offset ����ƫ����
    * \param str ���ƻ�����
    * \param length ���Ƴ���
    * \param isCached �Ƿ񻺴�����
    * \return ��ȡ�ɹ�����true�����򷵻�false��
    */
    virtual bool GetContent(int offset, char **str, short &length, bool isCached = true);

    //
    //
    //
    /**
    * \brief ��Դ����
    */
    virtual bool ForCollegues();

  private:
    //
    //
    //
    /**
    *
    */
    bool Find(int offset, char **str, short &length);

    /**
    *
    */
    bool Insert(const NameRecord &oneRecord);

    /**
    *
    **/
    void MoveFirst(int order);

    /**
    *
    */
    bool GetFromCache(int offset, char **str, short &length);

    /**
    *
    */
    bool GetFromMapping(int offset, char **str, short &length);

    /**
    *
    */
    bool OpenIndex(const tstring &fileName);

    /**
    *
    */
    bool OpenName(const tstring &fileName);

    /**
    *
    */
    static bool CompareOffset(const NameRecord &first, const NameRecord &second);

  private:
    // File name or connection string
    // Based on file mapping mechansim
    tstring m_nameFile;
    void *m_nameHandle;	// When it is applied to mainland case, it would be as index file to get concrete offset value of which language
    void *m_nameMap;
    char *m_nameData;

    // For mainland case
    tstring m_indexFile;
    void *m_indexHandle;
    void *m_indexMap;
    char *m_indexData;

    // For exception
    int m_maxIndexOffset;
    int m_maxNameOffset;

    //
    SimpleCache m_nameCache;
    int m_cacheSize;

    ///
    const CFileBasic &m_fileBasic;
    const CPathBasic &m_pathBasic;
  };
}
#endif