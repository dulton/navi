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
#ifndef _UEQUERY_QUERYIMPL_H
#define _UEQUERY_QUERYIMPL_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif
#ifndef _UEQUERY_INDEXCTRL_H
#include "indexctrl.h"
#endif
namespace UeBase
{
	class CCustomerFileReader;
}
//
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

// Declare namespace
namespace UeQuery
{
	class CUeRecord;
	struct TPoiEntry2th;
	class CPoiEntryCtrl;
	class CRoadEntryCtrl;
	class CCodeIndexCtrl;
	class CDataEntryCtrl;
	class CDistCodeIndexCtrl;
	//
	class UEQUERY_CLASS CUeQueryImpl:public CMemoryConsumer
	{
		// Relatives
		friend class CIndexCtrl;
		friend class CLegendIndex;
		friend class CKindIndex;
		friend class CGridIndex;
		friend class CAddrIndex;
		friend class CQueryDataVerify;
	public:
		CUeQueryImpl(void):m_records(0),m_pRoadEntryCtrl(0),
			m_pRoadDistCodeCtrl(0),m_pRecentCtrl(0),m_pFavoriteCtrl(0),
			m_pHistoryrecordCtrl(0) {};
		~CUeQueryImpl(void)
		{
			Release();
		}
		//�ͷŲ�ѯ���õ���������Դ
		unsigned Release(void);
		unsigned ConnectTo(short type);
		unsigned Disconnect(short type);
		//
		//������sqlȻ�����,���Բ��õ���ConnectTo����
		unsigned DoQuery(const SQLSentence &sql);
		//�õ���ǰ�Ľ����
		CUeRecord *GetRecordSet(void) const {return m_records;};
		//�õ���һ�εĲ�ѯ����
		const SQLSentence &GetCurQuerySql(void) const {return m_sql;};
		//
		//
		//��ȡ��ַ����������Ŀ
		int GetFavoriteCount(void);
		//ɾ������Ϊorder�ļ�¼
		unsigned RemoveFavorite(int order);
		//��ȡ����Ϊorder�ĵ�ַ��Ϣ
		const FavoriteEntry *GetFavorite(int order);
		//����µĵ�ַ��Ϣ
		unsigned AddFavorite(const FavoriteEntry &curFavor);
		//��������Ϊorder�ĵ�ַ��Ϣ
		unsigned UpdateFavorite(const FavoriteEntry &curFavor,int order);

		//��ȡ��ʷ��·����Ŀ
		int GetRecentCount(void);
		//��ȡ����Ϊorder����ʷ��·��Ϣ
		const RecentEntry *GetRecent(int order);
		//����µ���ʷ��·
		unsigned AddRecent(const RecentEntry &curFavor);
		//ɾ������Ϊorder����ʷ��·��Ϣ
		unsigned RemoveRecent(int order);
		//��������Ϊorder����ʷ��·��Ϣ
		unsigned UpdateRecent(const RecentEntry &curRecent,int order);

		//��ȡ��ʷ��¼����Ŀ
		int GetHistoryRecordCount(void);
		//��ȡ����Ϊorder����ʷ��¼
		const HistoryRecordEntry *GetHistoryRecord (int order);
		//���һ����ʷ��¼
		unsigned int AddHistoryRecord (const HistoryRecordEntry &curHisRecord);
		//ɾ������Ϊorder����ʷ��¼
		unsigned int RemoveHistoryRocord(int order);
		//ɾ��������ʷ��¼
		unsigned int RemoveAllHistoryRecord();
		//��������Ϊorder����ʷ��¼
		unsigned UpdateHistoryRecord(const HistoryRecordEntry &curHisRecord,int order);
		//
		virtual bool ForCollegues(void)
		{
			Release();
			return true;
		}
	private:
		struct TRoundPoiInfo
		{
			static bool Compare(const TRoundPoiInfo &first,const TRoundPoiInfo &second)
			{
				if (first.m_dist2th<second.m_dist2th)
					return true;
				if (first.m_dist2th>second.m_dist2th)
					return false;
				return first.m_idx<second.m_idx;
			}
			TRoundPoiInfo(void):m_dist2th(0.),m_idx(-1) {};
			//
			double m_dist2th;
			long m_idx;
		};
		unsigned ExecuteSQL(CIndexCtrl *&pQueryIndex)
		{
			unsigned rt(GetIndex(m_sql.m_indexType,pQueryIndex));
			if (rt==SQL_Success && pQueryIndex!=0)
			{
				rt = pQueryIndex->Predicate(m_sql);
			}
			return rt;
		}
		unsigned DoFetchRoads(CIndexCtrl *pQueryIndex);
		unsigned DoFetchCitys(CIndexCtrl *pQueryIndex);
		unsigned DoFetchCrosses(CIndexCtrl *pQueryIndex);
		unsigned DoFetchRoundPOIs(CIndexCtrl *pQueryIndex);
		unsigned GetIndex(UeQuery::IndexType indexType,CIndexCtrl *&pUeIndex);
		unsigned DoFetchTermRecord(CIndexCtrl *pQueryIndex,CDataEntryCtrl *pDataEntry);
		//
		bool InitQuery(const SQLSentence &sql);
		unsigned GetCrossOfRoad(void);
		unsigned GetPoiNearByRoad(void);
		unsigned GetPoiNearByRoute(void);
		//��ʼ����ʷ��·����
		bool InitRecentCtrl(void);
		bool InitFavoriteCtrl(void);
		bool InitHistoryrecordCtrl(void);
		//
		unsigned ConnectToRecent(void);
		unsigned DisconnectRecent(void);
		//
		unsigned ConnectToFavorite(void);
		unsigned DisconnectFavorite(void);
		//
		unsigned ConnectToHistoryRecord(void);
		unsigned DisconnectHistoryRecord(void);
		//�ͷ���һ�εĲ�ѯ��ʽ
		void DisconnectIndexes(void);
		//��m_bodyBegin��\\attrs\\pois.db���ݽ���ӳ�䣬����ʼ��pois����
		unsigned ConnectToPoiDB(void);
		unsigned DisconnectPoiDB(void);
		unsigned ConnectToRoadDB(void);
		unsigned DisconnectRoadDB(void);
		// Traits
		//��ѯ��ʽ����Ӧ�Ĳ�ѯ����
		typedef std::map<short,CIndexCtrl *> IndexWay;
		typedef IndexWay::iterator index_itr;
		typedef IndexWay::const_iterator index_citr;
		//
		char m_name[256];
		SQLSentence m_sql;
		// Different index mechansimes
		IndexWay m_indexWays;
		// Record set
		CUeRecord *m_records;
		//
		//CCodeIndexCtrl *m_pDistCodeCtrl;
		//CCodeIndexCtrl *m_pKindCodeCtrl;
		//
		//CPoiEntryCtrl *m_pPoiEntryCtrl;
		CRoadEntryCtrl *m_pRoadEntryCtrl;
		//
		//CDistCodeIndexCtrl *m_pPoiDistCodeCtrl;
		CDistCodeIndexCtrl *m_pRoadDistCodeCtrl;
		//
		CCustomerFileReader *m_pRecentCtrl;
		CCustomerFileReader *m_pFavoriteCtrl;
		CCustomerFileReader *m_pHistoryrecordCtrl;
	};
}
#endif
