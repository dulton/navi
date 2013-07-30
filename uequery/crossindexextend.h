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
#ifndef _UEQUERY_CROSSINDEXEXTEND_H
#define _UEQUERY_CROSSINDEXEXTEND_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEQUERY_DISTINDEX_H
#include "distindex.h"
#endif
//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	/**
	* \brief ��ĳ����·�Ľ���·��ʵʩ��
	**/
	class UEQUERY_CLASS CCrossIndexExtend:public CDistIndex
	{
		friend class CRoadEntryCtrl;
		friend class CUeNetworkOutput;
		friend class CQueryDataVerify;
	public:
		CCrossIndexExtend(void):m_curDistCode(0),
			m_bodyEntries(0) {};
		virtual ~CCrossIndexExtend(void) {m_bodyEntries=0;};
		virtual unsigned Next(CMemVector &idxes, unsigned maxNumber = 10000);
	protected:
		#pragma pack(1)
		struct CrossAddrEntry
		{
			long m_code;
			long m_startAcro;
			long m_acroNum;
			long m_startBody;
		};
		/**
		* \brief �������Ϣ
		**/
		struct CrossBodyEntry
		{
#ifndef USE_NEW_DATA
			CrossBodyEntry(void):m_x(0),m_y(0),
				m_firstOffset(0),m_secondOffset(0) {};
#else
			CrossBodyEntry(void):m_x(0),m_y(0) {};
#endif
			//Ҫ��Ϊ����ڵ����꣬ע���ǽ���ڶ������ཻ��
			long m_x;
			long m_y;
#ifndef USE_NEW_DATA
			//�������в�Ҫ�����أ���Ϊ��CrossAcronymEntry��������
			//����ͨ���ַ�ת���ֶ��õ���ת�����ݲ�֪����ô�������
			//�ٶȿ��Խ��ܵĻ����ҽ���ȥ���������ֶ�
			long m_firstOffset;
			long m_secondOffset;
#endif
		};
#pragma pack()
		virtual void InitIndexData(void)
		{
			m_pDistEntries = reinterpret_cast<TDistEntry *>(m_indices);
			m_pchAcroEntries = reinterpret_cast<char *>(m_filters);
			m_bodyEntries = reinterpret_cast<CrossBodyEntry *>(m_bodies);
		}
		//�õ������ļ���
		virtual tstring getIndexFileName(void) const
		{
			return _T("crossidx.dsx");
		}
		virtual unsigned GetFilterEntrySize(void) const
		{
			return MAXACROENTRY;
		}
		virtual unsigned GetBodyEntrySize(void) const
		{
			return sizeof(*m_bodyEntries);
		}
		virtual unsigned InitQuerySQL(const SQLSentence &sqlSentence)
		{
			unsigned rt(CUeIndex::InitQuerySQL(sqlSentence));
			if (rt==SQL_Success)
			{
				m_sql.m_kind = ::strlen(m_sql.m_acronyms);
			}
			return rt;
		}
		//����oneRecord��������idx����ʼ��oneRecord���ಿ��
		unsigned int GetRecord(SQLRecord *oneRecord);
	private:
		//��·����ƴ����д�������Ŀ
		const static int MAXACROENTRY = 10*2;

		//��ǰ������������
		long m_curDistCode;
		// Part pointed by m_bodies declared in CUeIndex
		CrossBodyEntry *m_bodyEntries;

		friend class CUeQueryImpl;
	};
}
#endif
