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
#ifndef _UEQUERY_QUERY_H
#define _UEQUERY_QUERY_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEQUERY_BASE_H
#include "ueinfo.h"
#endif

// Refer to query basic definition
#ifndef _UEQUERY_QUERYDEF_H
#include "querybasic.h"
#endif

// Refer to memory garbage definition
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif

// Refer to mediator definition
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif
using namespace UeBase;

// Declare namespace
namespace UeQuery
{
	// Forward class
	class CUeQueryImpl;
	class CUeRecord;

	/**
	* \brief ��Ϣ��������ӿ��࣬ͨ������static����GetQuery�ɻ�ȡ��Ӧ�Ķ���
	**/
	class UEQUERY_CLASS IQuery
	{
	public:
		IQuery(CUeQueryImpl *queryImpl);
		~IQuery(void);
		//
		//�ͷŲ�ѯ���õ���������Դ
		unsigned Release(void);
		unsigned Disconnect(short type);
		unsigned ConnectTo(short type, const SQLSetting &setting);
		//
		//������sqlȻ�����,���Բ��õ���ConnectTo����
		unsigned DoQuery(const SQLSentence &sql);
		//�Ӳ�ѯ����л�ȡ��һ����¼
		unsigned FetchFirst(SQLRecord **oneRecord) {return -1;};
		//�Ӳ�ѯ����л�ȡ��һ����¼
		unsigned FetchNext(SQLRecord **oneRecord) {return -1;};
		/**
		*
		**/
		void SetRecords(SQLRecord **records, int size) {};
		/**
		*
		**/
		void AddRecords(SQLRecord **records, int size) {};

		/**
		*
		*/
		void *GetRecords(int &size);

		/**
		*
		*/
		CUeRecord *GetRecordSet(void);
		const SQLSentence &GetCurQuerySql(void) const;

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
		
		//��ȡ����Ϊorder����ʷ��¼
		const HistoryRecordEntry *GetHistoryRecord (int order);
		//��ȡ��ʷ��¼����Ŀ
		int GetHistoryRecordCount();
		//���һ����ʷ��¼
		unsigned int AddHistoryRecord (const HistoryRecordEntry &curHisRecord);
		//ɾ������Ϊorder����ʷ��¼
		unsigned int RemoveHistoryRocord(int order);
		//ɾ��������ʷ��¼
		unsigned int RemoveAllHistoryRecord();
		//��������Ϊorder����ʷ��¼
		unsigned UpdateHistoryRecord(const HistoryRecordEntry &curHisRecord,int order);
		
		//
		//
		//
		/**
		*
		**/
		static IQuery *GetQuery();

		/**
		*
		**/
		static IQuery *GetQuery(CUeQueryImpl *queryImpl);

		/**
		*
		**/
		void Delete();

		//
		//
		//
		/**
		*
		**/
		void RegisterGarbage(CMemoryGarbage *garbage);

		/**
		*
		**/
		CMemoryGarbage *GetGarbage();

		/**
		*
		**/
		void RegisterMediator(CMediator *mediator);

		/**
		*
		**/
		CMediator *GetMediator(void);
		unsigned ExecuteSQL(SQLSentence *oneSentence)
		{
			return -1;
		};
		unsigned FetchFirst(SQLRecord **oneRecord, unsigned short maxMatches,unsigned maxNumber)
		{
			return -1;
		}
	private:
		//
		CUeQueryImpl *m_queryImpl;

		// Memory collector
		CMemoryGarbage *m_garbage;

		// Mediator decouple relationships
		CMediator *m_mediator;

		//
		static IQuery *m_query;
	};
}
#endif