#ifndef _UEQUERY_GRIDINDEXCTRL_H
#define _UEQUERY_GRIDINDEXCTRL_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEQUERY_INDEXCTRL_H
#include "indexctrl.h"
#endif
#ifndef _UEQUERY_POIENTRYCTRL_H
#include "poientryctrl.h"
#endif
#ifndef _UEQUERY_DATAENTRYCTRL_H
#include "dataentryctrl.h"
#endif
#ifndef _UEQUERY_DISTCODEINDEXCTRL_H
#include "distcodeindexctrl.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	class UEQUERY_CLASS CGridIndexCtrl:public CIndexCtrl,public CDataEntryCtrl
	{
	public:
		static const long g_gridGap = 5000;
		//
		CGridIndexCtrl(bool bReadMode):CIndexCtrl(bReadMode),
			m_pGridIndex(0),m_bufDocBeg(0),m_bufKindCnt(1000),
			m_pPoiKind(0),m_hitCount(0),m_curHitIdx(-1),
			m_pHitGridInfo(0),m_kindMask(0),m_pPoiEntryCtrl(0),
			m_pDistCodeCtrl(0),m_recordBufSize(0),
			m_pDocMathRecord(0) {};
		virtual ~CGridIndexCtrl(void) {Close();};
		//
		virtual unsigned Open(void);
		virtual unsigned Close(void);
		//
		//�ӱ�������pois�����ж�ȡ���ݣ����л���
		bool Prepare(void);
		bool OutputPoiIndex(void);
		//��ģʽ
		virtual unsigned First(void)
		{
			if (m_pHitGridInfo!=0 && m_hitCount!=0)
			{
				m_curHitIdx = 0;
				return SQL_Success;
			}
			return SQL_ZeroRecord;
		}
		unsigned Predicate(const SQLSentence &sql);
		unsigned Next(CMemVector &idxes,unsigned maxNumber=10000);
		//��ȡ������Ŀ
		virtual unsigned GetDistCount(void) const
		{
			if (m_pDistCodeCtrl!=0)
				return m_pDistCodeCtrl->GetDistCount();
			return 0;
		}
		//��ȡ������Ŀ
		virtual unsigned GetDataCount(void) const
		{
			if (m_pPoiEntryCtrl!=0)
				return m_pPoiEntryCtrl->GetPoiCount();
			return 0;
		}
		//��������Ҫ�Ľ������/��ţ���ȡ����
		virtual unsigned GetKind(long docIdx);
		//��������Ҫ�Ľ������/��ţ���ȡ�������
		virtual unsigned GetCode(long distIdx) const
		{
			if (m_pDistCodeCtrl!=0)
			{
				return m_pDistCodeCtrl->GetDistCode(distIdx);
			}
			return -1;
		}
		virtual bool GetSubDistIndex(unsigned fDistCode,
			defDistCodeType &sStartIdx,defDistCodeType &sEndIdx) const
		{
			if (m_pDistCodeCtrl!=0)
			{
				return m_pDistCodeCtrl->GetSubDistIndex(fDistCode,sStartIdx,sEndIdx);
			}
			return false;
		}
		//��������Ҫ�Ľ������/��ţ���ȡ���Ƴ���
		virtual unsigned GetNameLen(long docIdx)
		{
			if (m_pPoiEntryCtrl!=0)
			{
				return m_pPoiEntryCtrl->GetNameLen(docIdx);
			}
			return 10000;
		}
		//��������Ҫ�Ľ������/��ţ�����ѯ���
		virtual SQLRecord *FixRecord(long docIdx)
		{
			if (m_pPoiEntryCtrl!=0)
			{
				SQLRecord *oneRecord(m_pPoiEntryCtrl->FixRecord(docIdx));
				if (oneRecord!=0 && m_pDistCodeCtrl!=0)
				{
					oneRecord->m_addrCode = m_pDistCodeCtrl->GetDistCode(oneRecord->m_addrCode);
				}
				return oneRecord;
			}
			return 0;
		}
		//��������Ҫ�Ľ������/��ţ��������
		virtual bool GetEntryName(long docIdx,long nameLen,char *pchNameBuffer)
		{
			if (m_pPoiEntryCtrl!=0)
				return m_pPoiEntryCtrl->GetPoiEntryNameByIdx(docIdx,nameLen,pchNameBuffer);
			return false;
		}
	private:
		typedef unsigned long defGridIndexType;
		typedef unsigned long defGridPoiIdxType;
		typedef std::vector<TPoiEntry *> defPoiList;
		typedef std::map<defGridIndexType,defPoiList> defGridList;
		typedef bool (*PoiEntryCmp)(const TPoiEntry *,const TPoiEntry *);
		//
		#pragma pack(1)
		struct TGridIndex
		{
			TGridIndex(void):m_gridIdx(0),
				m_startBody(0) {};
			//
			defGridIndexType m_gridIdx;
			defGridPoiIdxType m_startBody;
		};
		struct TIndexHead
		{
			TIndexHead(void):m_gridVer(0),m_minX(0),
				m_minY(0),m_gridNumX(0),m_gridNumY(0),
				m_gridCount(0),m_poiCount(0)
			{
				::memcpy(head,DATA_HEAD,sizeof(head));
			}
			//
			char head[16];
			unsigned short m_gridVer;
			long m_minX;
			long m_minY;
			long m_gridNumX;
			long m_gridNumY;
			long m_gridCount;
			long m_poiCount;
		};
		#pragma pack()
		//
		void InitGridParam(void);
		bool AddPoiEntry2th(TPoiEntry *pPoiEntry);
		//
		bool BinaryPredicate(long gridIdx);
		bool BinaryPredicate(long &startIdx,long &endIdx);
		unsigned InitHitGridInfo(long &startX,long &startY,long &endX,long &endY);
		unsigned GetRectGrid(long &startX,long &startY,long &endX,long &endY) const;
		int GetKindIdx(int startIdx,int endIdx,bool isGetStart) const;
		//
		TGridIndex *m_pGridIndex;
		//
		long m_kindOffset;
		//m_pGridPoiKind�е�һ��kind��Ӧ��doc
		defGridPoiIdxType m_bufDocBeg;
		//m_pGridPoiKind�л����Ŷ���doc��kind
		long m_bufKindCnt;
		defPoiKindType *m_pPoiKind;
		//
		TIndexHead m_indexHead;
		//���ϵ�ǰ������������Ŀ
		long m_hitCount;
		long m_curHitIdx;
		//
		long *m_pHitGridInfo;
		//
		SQLSentence m_sql;
		//
		defPoiKindType m_kindMask;
		//���²�������дģʽ
		defGridList m_gridDataList;
		std::map<defPoiKindType,long> m_kindCnt;
		//
		CPoiEntryCtrl *m_pPoiEntryCtrl;
		CDistCodeIndexCtrl *m_pDistCodeCtrl;

		long m_recordBufSize;
		TDocMathInfo *m_pDocMathRecord;
	};
}
#endif