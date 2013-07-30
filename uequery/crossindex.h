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
#ifndef _UEQUERY_CROSSINDEX_H
#define _UEQUERY_CROSSINDEX_H
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
	* \brief ��·����ʵʩ��
	**/
	class UEQUERY_CLASS CCrossIndex:public CDistIndex
	{
		friend class CRoadEntryCtrl;
		friend class CUeNetworkOutput;
		friend class CQueryDataVerify;
		//��·����ƴ����д�������Ŀ
		const static int MAXACROENTRY = 10;
		const static int MAXHOUSENUMLEN = 42;
	public:
		CCrossIndex(void):m_curDistCode(0),
			m_bodyEntries(0) {};
		virtual ~CCrossIndex(void) {m_bodyEntries=0;};
		virtual unsigned Next(CMemVector &idxes,unsigned maxNumber=10000);
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
		* \breif ����ڼ����еĵ�·��Ϣ
		**/
		struct CrossBodyEntry
		{
			/**
			*
			**/
			CrossBodyEntry(void):m_parcelIdx(0),m_linkIdx(0)
			{
#ifndef USE_NEW_DATA
				::memset(m_housenum, 0x00, MAXHOUSENUMLEN);
#endif
			}
			//���ڵĵ�·��������
			long m_parcelIdx;
			//�������еĵ�·����
			long m_linkIdx;

//			//��ʱû��ʲô���ã�ʵ�ʿ���ȥ��
//			// 0-9    ����ʼ��ַ
//			// 10 -19 ���������ַ
//			// 20     ������ַ����
//			// 21-30  ����ʼ��ַ
//			// 31-40  ���������ַ
//			// 41     ������ַ����
//#ifndef USE_NEW_DATA
//			char m_housenum[MAXHOUSENUMLEN];
//#endif
		};
		#pragma pack()
		//
		virtual void InitIndexData(void)
		{
			m_pDistEntries = reinterpret_cast<TDistEntry *>(m_indices);
			m_pchAcroEntries = reinterpret_cast<char *>(m_filters);
			m_bodyEntries = reinterpret_cast<CrossBodyEntry *>(m_bodies);
		}
		//�õ������ļ���
		virtual tstring getIndexFileName(void) const
		{
			return _T("cross.mj");
		}
		virtual unsigned GetFilterEntrySize(void) const
		{
			return MAXACROENTRY;
		}
		virtual unsigned GetBodyEntrySize(void) const
		{
			return sizeof(*m_bodyEntries);
		}
		//����oneRecord��������idx����ʼ��oneRecord���ಿ��
		unsigned int GetRecord(SQLRecord *oneRecord);
	private:
		//��ǰ������������
		long m_curDistCode;
		// Part pointed by m_bodies declared in CUeIndex
		CrossBodyEntry *m_bodyEntries;

		friend class CUeQueryImpl;
	};
}
#endif
