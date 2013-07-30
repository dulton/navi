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
#ifndef _UEROUTE_SIDEPROPS_H
#define _UEROUTE_SIDEPROPS_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to eEys kinds
#ifndef _UEROUTE_ROUTEBASIC_H
#include "routebasic.h"
#endif

// Refer to file & path basic operations
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif

#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

// Refer to geom basic functions
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif

// Refer to own array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

// Refer to other modules
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif
using namespace UeBase;

/**
*
**/
namespace UeRoute
{
  /**
  * \brief ��·������Ϣ
  */
  class UEROUTE_CLASS CUeSideProps
  {
    // Relatives
    friend class CUeGuider;
    friend class CUeVoice;

  public:
    //
    //
    //
    /**
    * \brief ���캯�����򿪵�·������Ϣ�ļ�
    */
    CUeSideProps();

    /**
    * \brief ��������
    */
    ~CUeSideProps();

  protected:
    //
    //
    //
    /**
    * \brief ����ʹ�ÿ������캯��
    */
    CUeSideProps(const CUeSideProps &other);

    /**
    * \brief ����ʹ�ø�ֵ������
    */
    const CUeSideProps &operator=(const CUeSideProps &other);

  protected:
    //
    //
    //
    /**
    * \brief �򿪵�·������Ϣ�ļ�
    */
    virtual bool Open();

    /**
    * \brief �ر��ļ�
    */
    virtual bool Close();

    //
    //
    //
    /**
    * \brief ȡ��ָ����·�Ĺ�����Ϣ
    *
    * \param type ������Ϣ����
    * \param code ·�����������
    * \param xCoord ��ǰ·��ID
    * \param yCoord ����·��ID
    * \param prop ���صĹ�����Ϣ
    */
    virtual unsigned char GetProp(unsigned char type, int code, int xCoord, int yCoord, char *prop);
    
    /**
    * \brief ��ȡ���������ݻ�ͨ��ʾ����
    *
    * \param type �������ͣ���ЧֵΪSVT_TrafficSign��SVT_EEye
    * \param parcleID �����
    * \param linkID ��ǰ·��ID
    * \param direction ��ǰ·�εĽ�ͨ������
    * \param signs ���ڷ��ػ�ȡ�����ݣ��ò������ϸ�ĵ�Ԫ�������ƣ�ʹ��ʱ��ע�⡣
    *
    * \return �������ͣ��������жϵ�ǰ·���Ƿ������Ӧ���͵�����
    */
    unsigned char GetTrafficSign(unsigned char type, int parcelID, int linkID, int direction, CMemVector &signs);

    /**
    * \brief ȡ�÷��򿴰��еĸ��ٳ�����Ϣ
    * 
    * \param parcleID �����
    * \param linkID ��ǰ·��ID���豣֤��ǰ·��Ϊ����·��
    * \param nextLinkID ��һ·��ID
    * \param prop ���صĳ�����Ϣ
    */
    bool GetHighwayOutlet(int parcelID, int linkID, int nextLinkID, char *prop);

  private:
    //
    //
    //
    /**
    *
    **/
    bool GetOffets(int code, int &start, int &end, bool isIndexPart = true);

    /**
    *
    **/
    int GetStartOffset(int code, int start, int end, bool isIndexPart = true);

    /**
    *
    **/
    int GetEndOffset(int code, int start, int end, bool isIndexPart = true);

    /**
    *
    **/
    int GetDistrictIdx(const CGeoPoint<long> &pos);

    /**
    *
    **/
    //short GetType(unsigned char type);

  private:
    // Definitions for file mapping
    int m_recNum;
    int m_indexNum;
    void *m_fileHandle;
    void *m_mapHandle;
    unsigned char *m_data;

    // Pointers to different parts
    eSideIndex *m_indices;
    eSideEntry *m_entries;
    eSideEntry *m_curEntries;

    // Mediator
    CMediator *m_mediator;

    // Utility classes
    const CFileBasic &m_fileBasic;
    const CPathBasic &m_pathBasic;
  };
}
#endif