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
// Refer to UeQuery package
#ifndef _UEQUERY_CROSSINDEXEXTEND_H
#include "crossindexextend.h"
#endif
#ifndef _UEMODEL_ROADNETWORK_H
#include "uemodel\network.h"
#endif
#ifndef _UEMODEL_NETPARCEL_H
#include "uemodel\netparcel.h"
#endif
#ifndef _UEMODEL_ROADLINK_H
#include "uemodel\netlink.h"
#endif
#ifndef _UEMODEL_NAMETABLE_H
#include "uemodel\netnametable.h"
#endif
using namespace UeModel;
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	unsigned CCrossIndexExtend::Next(CMemVector &idxes,unsigned maxNumber)
	{
		if(m_curIdx==-1 || m_curIdx>m_endIdx)
		{
			return SQL_MeetTail;
		}
		for (TDistEntry *oneAddr(m_pDistEntries+m_curIdx); ; ++oneAddr)
		{
			if (oneAddr->m_startAcro<m_bodyCount)
			{
				//获取拼音简写数据的大小
#ifndef USE_NEW_DATA
				int length(oneAddr->m_acroNum*MAXACROENTRY);
#else
				int length(0);
				if (m_curIdx<(m_idxCount-1))
				{
					length = (oneAddr+1)->m_startAcro-oneAddr->m_startAcro;
				}
				else
				{
					length = m_bodyCount-oneAddr->m_startAcro;
				}
				length *= MAXACROENTRY;
#endif
				//获取当前区域所有道路名称拼音简写数据
				char *content(m_pchAcroEntries+oneAddr->m_startAcro*MAXACROENTRY);
				//获取与查询条件匹配的道路索引
				int num = 0;
				CMemVector matches(sizeof(int));
				if(!m_sql.m_misses)
				{
					num = m_strMatch.StrictMatch(content,m_sql.m_acronyms,
						length,MAXACROENTRY,matches,maxNumber);
				}
				else
				{
					num = m_strMatch.LikeMatch(m_sql.m_misses,content,m_sql.m_acronyms,
						length,MAXACROENTRY,matches,maxNumber);
				}
				if (num>0)
				{
					int shift(0);
					for (int *head(reinterpret_cast<int *>(matches.GetHead())),
						i(0); i<matches.GetCount(); ++i,++head)
					{
						shift = oneAddr->m_startAcro+*head;
						idxes.Add(&shift);
					}
				}
			}
			else
			{
				m_curIdx = m_endIdx+1;
				return SQL_MeetTail;
			}
			++ m_curIdx;
			if (idxes.GetCount())
			{
				m_curDistCode = oneAddr->m_distCode;
				return SQL_Success;
			}
			//
			if (m_curIdx>m_endIdx)
			{
				return SQL_MeetTail;
			}
		}
		return SQL_MeetTail;
	}
	unsigned int CCrossIndexExtend::GetRecord(SQLRecord *oneRecord)
	{
		long shift = oneRecord->m_idx;
		oneRecord->m_x = m_bodyEntries[shift].m_x;
		oneRecord->m_y = m_bodyEntries[shift].m_y;
#if 1
		// Get road name
		short length = 0;
		const char *pchCrossStr(m_pchAcroEntries+shift*MAXACROENTRY+m_sql.m_kind);
		IRoadNetwork::GetNetwork()->GetNameTable(UeModel::UNT_Network)->GetContent(::atoi(pchCrossStr),
			&oneRecord->m_asciiName, length, false);
		{
			//TODO 到时记得清除这中做法
			length = oneRecord->m_asciiName[0];
			::strncpy(oneRecord->m_asciiName,oneRecord->m_asciiName+1,length);
			oneRecord->m_asciiName[length] = 0;
		}
		oneRecord->m_asciiLen = length;
#endif
		return SQL_Success;
	}
}