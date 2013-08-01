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
#ifndef _UEQUERY_KINDINDEX_H
#define _UEQUERY_KINDINDEX_H
//////////////////////////////////////////////////////////////////////////
// Refer to its parent
#ifndef _UEQUERY_UEINDEX_H
#include "ueindex.h"
#endif
//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling
#pragma warning( disable: 4275 )  // Deprecated function calling
#pragma warning( disable: 4996 )  // Deprecated function calling
//////////////////////////////////////////////////////////////////////////
// Declare namespace
namespace UeQuery
{
  class CDataEntryCtrl;
	/**
	* /brief ���ͼ���ʵʩ��
	**/
	class UEQUERY_CLASS CKindIndex : public CUeIndex
	{
		friend class CUePoiOutput;
		friend class CQueryDataVerify;
		friend class CUePOIPressureCheck;
	public:
		CKindIndex(void):m_bodyEntries(0),
			m_kindEntries(0) {};
		virtual ~CKindIndex(void) {};
    static bool CreateKindIndex(CDataEntryCtrl *pDataEntryCtrl);
		/**
		* \brief �õ��뵱ǰ�ṩ�����͡���������ƴ����д��ƥ���poi��pois.db�е�������Ϣ
		* \param idxes:������Ϣװ������
		* \param maxNumber:���ɷ��ص���
		**/
		virtual unsigned Next(CMemVector &idxes, unsigned maxNumber = 10000);
	protected:
		// Index item
		//��ʾ���¸�pragma����������ݽṹ1���ֽڶ���
		#pragma pack(1)
		/**
		* \brief ��������
		**/
		struct KindIndex
		{
			KindIndex(void):m_kind(0),m_addrCode(0),
				m_bodyIdx(0) { };
			//����(����|С��)
			unsigned short m_kind;
      //��������
			long m_addrCode;
			//������ĸ����͵�����poi��KindInfo������king.mj�е�ƫ����			
			long m_bodyIdx;// The offset of kind index items pointing to the start position of one kind
		};
		#pragma pack()
		virtual unsigned GetIdxes(void);
		virtual tstring getIndexFileName(void) const
		{
			return _T("kind.mj");
		}
		void InitIndexData(void)
		{
			m_bodyEntries = reinterpret_cast<int *>(m_bodies);
			m_kindEntries = reinterpret_cast<KindIndex *>(m_indices);
		}
		//TODO: ע�������Ĭ�Ϸ���,�����л����Լ������Լ���
		virtual unsigned GetIdxEntrySize(void) const
		{
			return sizeof(*m_kindEntries);
		};
		virtual unsigned GetFilterEntrySize(void) const
		{
      return 0;
		}
		virtual unsigned GetBodyEntrySize(void) const
		{
			return sizeof(*m_bodyEntries);
		}
		//
		virtual unsigned InitQuerySQL(const SQLSentence &sqlSentence)
		{
			if (!sqlSentence.m_kind==-1)
				return SQL_InvalidSentence;
			if (sqlSentence.m_addrOne==-1)
				return SQL_InvalidSentence;
			m_sql = sqlSentence;
			return SQL_Success;
		}
	private:
    static bool CmpKindIndexEntry(const KindIndex &,const KindIndex &);
		int GetIdxes(unsigned codeMask,int startIdx,int endIdx,bool isGetStart);

		//poi������poi�е�����
		int *m_bodyEntries;
		//���ͼ�������������
		KindIndex *m_kindEntries;
	};
}
#endif