#ifndef _UEQUERY_ROADENTRYCTRL_H
#define _UEQUERY_ROADENTRYCTRL_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEMODEL_UENETBASIC_H
#include "uemodel/uenetbasic.h"
#endif
#ifndef _UEQUERY_QUERYDEF_H
#include "querybasic.h"
#endif
#ifndef _UEQUERY_DATAENTRYCTRL_H
#include "dataentryctrl.h"
#endif
#ifndef _UEQUERY_DISTCODEINDEXCTRL_H
#include "distcodeindexctrl.h"
#endif
namespace UeModel
{
	class IRoadNetwork;
}
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	class CUeRecord;
	typedef unsigned short defLinkCntType;
	#pragma pack(1)
	struct TLinkEntry
	{
		TLinkEntry(void):m_parcelIdx(0),m_linkIdx(0) {};

		//���ڵĵ�·��������
		UeModel::UeLongInteger m_parcelIdx;
		//�������еĵ�·����
		UeModel::UeLongInteger m_linkIdx;
	};
	struct TCrossEntry
	{
		TCrossEntry(void):m_x(0),m_y(0),m_nameOffset(0) {};
		//Ҫ��Ϊ����ڵ����꣬ע���ǽ���ڶ������ཻ��
		UeModel::UeLongInteger m_x;
		UeModel::UeLongInteger m_y;
		unsigned long m_nameOffset;
	};
	struct TRoadEntry
	{
		TRoadEntry(void):m_nameOffset(0),
			m_distCode(0),m_linkOffset(0),
			m_crossOffset(0) {};
		//
		unsigned long m_nameOffset;
		unsigned short m_distCode;
		unsigned long m_linkOffset;
		unsigned long m_crossOffset;
	};
	#pragma pack()
	class UEQUERY_CLASS CRoadEntryCtrl:public CDataEntryCtrl
	{
	public:
		CRoadEntryCtrl(bool bReadMode):m_bReadMode(bReadMode),
			m_pRoadFileHandle(0),m_pDistCodeCtrl(0),m_pRoadNetwork(0) {};
		virtual ~CRoadEntryCtrl(void) {Close();};
		//
		virtual unsigned Open(void);
		virtual unsigned Close(void);
		//
		//�ӱ�������pois�����ж�ȡ���ݣ����л���
		bool Prepare(void);
		bool OutputRoadIndex(void);
		//
		static void GetDistCode(const UeBase::CGeoPoint<long> *vertice,
			long vertexCount,std::set<long> &vecDistCode);
		static void GetPosOfOneLink(double dist,const UeBase::CGeoPoint<long> *vertice,
			long vertexCount,std::vector<UeBase::CGeoPoint<long>> &vecPos);
		//
		bool GetRoadEntryNameByOffset(long nameOffset,char *pchNameBuffer,unsigned char &uStrLen) const;
		//
		bool GetRoadCross(long crossOffset,CUeRecord *pvecRecord);
		bool GetPoiAroundRoad(long linkOffset,const SQLSentence &querySql,
			CUeRecord &vecPoiRecord);
		static void GetPoiNearByLink(CGeoPoint<long> *vertice,short vertexCount,
			const SQLSentence &querySql,CUeRecord &vecPoiRecord);
		//
		virtual unsigned GetDistCount(void) const
		{
			if (m_pDistCodeCtrl!=0)
				return m_pDistCodeCtrl->GetDistCount();
			return 0;
		}
		//��ȡ������Ŀ
		virtual unsigned GetDataCount(void) const
		{
			return m_indexHead.m_roadCount;
		}
		//��������Ҫ�Ľ������/��ţ���ȡ����
		virtual unsigned GetKind(long docIdx)
		{
			return 0;
		}
		//��������Ҫ�Ľ������/��ţ���ȡ�������
		virtual unsigned GetCode(long distIdx) const
		{
			if (m_pDistCodeCtrl!=0)
				return m_pDistCodeCtrl->GetDistCode(distIdx);
			return -1;
		}
		virtual bool GetSubDistIndex(unsigned fDistCode,
			defDistCodeType &sStartIdx,defDistCodeType &sEndIdx) const
		{
			if (m_pDistCodeCtrl!=0)
				return m_pDistCodeCtrl->GetSubDistIndex(fDistCode,
				sStartIdx,sEndIdx);
			return false;
		}
		//��������Ҫ�Ľ������/��ţ���ȡ���Ƴ���
		virtual unsigned GetNameLen(long docIdx);
		//��������Ҫ�Ľ������/��ţ�����ѯ���
		virtual SQLRecord *FixRecord(long docIdx);
		//��������Ҫ�Ľ������/��ţ��������
		virtual bool GetEntryName(long docIdx,long nameLen,char *pchNameBuffer);
	private:
		#pragma pack(1)
		struct TIndexHead
		{
			TIndexHead(void):m_roadVer(0),
				m_roadCount(0),m_linkCount(0),m_crossCount(0)
			{
				::memcpy(head,DATA_HEAD,sizeof(head));
			}
			//
			char head[16];
			unsigned short m_roadVer;
			long m_roadCount;
			long m_linkCount;
			long m_crossCount;
		};
		#pragma pack()
		//ĳһ�����ڵ�����road,firstΪnameoffset,second��Ϊ��Ӧ��link
		typedef std::map<long,std::vector<TLinkEntry> *> defCityRoadList;
		//ȫ����Ӧ��road,firstΪ������룬second��Ϊ�������µ�road
		typedef std::map<long,defCityRoadList *> defRCityList;
		//ĳһ�����ڵ�����cross,firstΪnameoffset,second��Ϊ��Ӧ��cross
		typedef std::map<long,std::vector<TCrossEntry> *> defCityCrossList;
		//ȫ����Ӧ��road,firstΪ������룬second��Ϊ�������µ�cross
		typedef std::map<long,defCityCrossList *> defCCityList;
		//
		bool InitRCityList(defRCityList &roadCityList);
		bool InitCCityList(defCCityList &crossCityList);
		bool GetRoadEntry(long idx,TRoadEntry &roadEntry);
		//
		const static long g_bufDocCnt = 50000;
		//��ǰ�Ķ�дģʽ
		bool m_bReadMode;
		//
		TIndexHead m_indexHead;
		void *m_pRoadFileHandle;
		//
		defRCityList m_roadCityList;
		defCCityList m_crossCityList;
		//
		CDistCodeIndexCtrl *m_pDistCodeCtrl;
		UeModel::IRoadNetwork *m_pRoadNetwork;

		long m_bufDocBeg;
		unsigned char m_pNameLen[g_bufDocCnt];
	};
}
#endif