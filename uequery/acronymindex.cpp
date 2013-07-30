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
#ifndef _UEQUERY_ACRONYMINDEX_H
#include "acronymindex.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	unsigned CAcronymIndex::Next(CMemVector &idxes,unsigned maxNumber)
	{
		if(m_curIdx==-1 || m_curIdx>m_endIdx)
		{
			return SQL_MeetTail;
		}
		for (TDistEntry *oneAddr(m_pDistEntries+m_curIdx); ; ++oneAddr)
		{
			if (oneAddr->m_startAcro<m_bodyCount)
			{
				//��ȡƴ����д���ݵĴ�С
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
				//��ȡ��ǰ�������е�·����ƴ����д����
				char *content(m_pchAcroEntries+oneAddr->m_startAcro*MAXACROENTRY);
				//��ȡ���ѯ����ƥ��ĵ�·����
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
					for (int *head(reinterpret_cast<int *>(matches.GetHead())),
						i(0); i<matches.GetCount(); ++i,++head)
					{
						idxes.Add(m_bodyEntries+*head+oneAddr->m_startAcro);
					}
				}
			}
			else
			{
				m_curIdx = m_endIdx+1;
				return SQL_MeetTail;
			}
			++ m_curIdx;
			//
			if (m_curIdx>m_endIdx)
			{
				if (idxes.GetCount())
				{
					return SQL_Success;
				}
				return SQL_MeetTail;
			}
			if (idxes.GetCount()>=maxNumber)
			{
				return SQL_Success;
			}
		}
		return SQL_MeetTail;
	}
}