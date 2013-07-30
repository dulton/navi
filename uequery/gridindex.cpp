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
// Refer to UeQuery
#ifndef _UEQUERY_GRIDINDEX_H
#include "gridindex.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	const double CGridIndex::g_gridGapY((5.0*100000.)/60);
	//
	unsigned CGridIndex::Open(void)
	{
		unsigned int rt(CUeIndex::Open());
		if(rt == SQL_Success)
		{
			int cursor(16+2);
			// Get basic information
			//��ȡ���񻮷�X�Ŀ�ʼ����
			::memcpy(&m_gridBaseX,m_begin+cursor,sizeof(m_gridBaseX));
			cursor += sizeof(m_gridBaseX);
			//��ȡ���񻮷�Y�Ŀ�ʼ����
			::memcpy(&m_gridBaseY,m_begin+cursor,sizeof(m_gridBaseY));
			cursor += sizeof(m_gridBaseY);
			//��ȡX������һ������Ĵ�С
			::memcpy(&m_gridGapX,m_begin+cursor,sizeof(m_gridGapX));
			cursor += sizeof(m_gridGapX);
			//��ȡY������һ������Ĵ�С
			::memcpy(&m_gridGapY,m_begin+cursor,sizeof(m_gridGapY));
			cursor += sizeof(m_gridGapY);
			//��ȡ���񻮷���X�����ϵ�������Ŀ
			::memcpy(&m_gridNumX,m_begin+cursor,sizeof(m_gridNumX));
			cursor += sizeof(m_gridNumX);
			//��ȡ���񻮷���Y�����ϵ�������Ŀ
			::memcpy(&m_gridNumY,m_begin+cursor,sizeof(m_gridNumY));
			cursor += sizeof(m_gridNumY);
		}
		return rt;
	}
	unsigned CGridIndex::Next(CMemVector &idxes,unsigned maxNumber)
	{
		// Check exception
		if (m_curGrid==-1 || m_curGrid>(m_gridNum-1))
		{
			return SQL_MeetTail;
		}
		//
		do
		{
			m_curIdx = m_gridIdxs[m_curGrid];
			GridIndex *oneItem(m_gridEntries+m_curIdx);
			//
			BinaryPredicate(oneItem->m_bodyIdx,
				m_curIdx!=(m_idxCount-1)?(oneItem+1)->m_bodyIdx:m_bodyCount,idxes);
			//
			++ m_curGrid;
		} while (m_curGrid<m_gridNum && idxes.GetCount()<maxNumber);
		//
		return idxes.GetCount()?SQL_Success:SQL_MeetTail;
	}
	unsigned CGridIndex::GetIdxes(void)
	{
		if (m_idxCount==0)
			return SQL_ZeroRecord;
		//����X����������Ŀ�ʼ����
		int startX((m_sql.m_srchExtent.m_minX-m_gridBaseX)/m_gridGapX);
		if (startX<0)
		{
			startX = 0;
		}
		else if (startX>=m_gridNumX)
		{
			//��ʼ�����񶼲��ڷ�Χʱ���򷵻�
			return SQL_ZeroRecord;
		}
		//����X����������Ľ�������
		int endX((m_sql.m_srchExtent.m_maxX-m_gridBaseX)/m_gridGapX);
		if (endX<0)
		{
			//���ڷ�Χ�ڣ�ֱ�ӷŻ�
			return SQL_ZeroRecord;
		}
		else if (endX>=m_gridNumX)
		{
			endX = m_gridNumX-1;
		}
		//����Y����������Ŀ�ʼ����
		int startY((m_sql.m_srchExtent.m_minY-m_gridBaseY)/m_gridGapY);
		if (startY<0)
		{
			startY = 0;
		}
		else if (startY>=m_gridNumY)
		{
			//���ڷ�Χ�ڣ�ֱ�ӷ���
			return SQL_ZeroRecord;
		}
		//����Y����������Ľ�������
		int endY((m_sql.m_srchExtent.m_maxY-m_gridBaseY)/m_gridGapY);
		if (endY<0)
		{
			//���ڷ�Χ��,ֱ�ӷ���
			return SQL_ZeroRecord;
		}
		else if (endY>=m_gridNumY)
		{
			endY = m_gridNumY-1;
		}
		//
#if 0
		if (m_gridNum=(endX-startX+1)*(endY-startY+1))
		{
			if(m_gridIdxs)
			{
				::free(m_gridIdxs);
			}
			if (m_gridIdxs=reinterpret_cast<int *>(::malloc(m_gridNum*sizeof(int))))
			{
				// In advance get those grid idxes
				for(int count(0),i(startY); i <= endY; ++i)
				{
					for(int j(startX); j <= endX; ++j,++count)
					{
						m_gridIdxs[count] = i * m_gridNumX + j;
					}
				}
				return First();
			}
		}
#else
		if (m_gridNum=(endX-startX+1)*(endY-startY+1))
		{
			if (m_gridIdxs!=0)
			{
				::free(m_gridIdxs);
				m_gridIdxs = 0;
			}
			//��취���������ĵ�������������ǰ��
			typedef std::multimap<long,long> GridIndexMulMap;
			GridIndexMulMap gridIndexMap;
			//
			long posIndexX((m_sql.m_pos.m_x-m_gridBaseX)/m_gridGapX);
			long posIndexY((m_sql.m_pos.m_y-m_gridBaseY)/m_gridGapY);
			//��Ź�������뾶
			long gridRadius(m_sql.m_radius/((m_gridGapY+m_gridGapX)/2));
			gridRadius *= gridRadius;
			++ gridRadius;
			//
			for(int i(startY); i<=endY; ++i)
			{
				for(int j(startX); j<=endX; ++j)
				{
					long gridIndex(i*m_gridNumX+j);
					//
					if (BinaryPredicate(gridIndex))
					{
						long tempX(j-posIndexX);
						long tempY(i-posIndexY);
						long dist(tempX*tempX+tempY*tempY);
						//
						if (dist<=gridRadius)
						{
							gridIndexMap.insert(GridIndexMulMap::value_type(dist,m_curIdx));
						}
					}
				}
			}
			if (m_gridNum=gridIndexMap.size())
			{
				if (m_gridIdxs=reinterpret_cast<int *>(::malloc(m_gridNum*sizeof(int))))
				{
					GridIndexMulMap::iterator iterInfo(gridIndexMap.begin());
					for (int count(0); iterInfo!=gridIndexMap.end(); ++iterInfo,++count)
					{
						m_gridIdxs[count] = iterInfo->second;
					}
					return First();
				}
			}
		}
#endif
		return SQL_ZeroRecord;
	}
	bool CGridIndex::BinaryPredicate(long gridIdx)
	{
		//
		int start = 0;
		int end = m_idxCount - 1;
		int mid = 0;
		while(start <= end)
		{
			mid = (start + end) >> 1;
			int cmp = (m_gridEntries+mid)->m_gridIdx - gridIdx;
			if(!cmp)
			{
				m_curIdx = mid;
				return true;
			}
			else if(cmp > 0)
			{
				end = mid - 1;
			}
			else
			{
				start = mid + 1;
			}
		}
		return false;
	}
	void CGridIndex::BinaryPredicate(int startIdx, int endIdx, CMemVector &idxes)
	{
#ifdef USE_NEW_DATA
		if (m_sql.m_kind!=0)
		{
			unsigned codeMask(0xf000);
			if (m_sql.m_kind&0x00ff)
			{
				codeMask = 0xffff;
			}
			else if (m_sql.m_kind&0x0f00)
			{
				codeMask = 0xff00;
			}
			bool bHasFound(false);
			register int start(startIdx),end(endIdx-1),mid(0),cmp(0);
			//
			while(start <= end)
			{
				mid = (start + end) >> 1;
				if (!(cmp=((m_filterEntries+mid)->m_kind&codeMask)-m_sql.m_kind))
				{
					if ((startIdx=GetKindIdx(codeMask,start,mid,true))>=0
						&& (endIdx=GetKindIdx(codeMask,mid,end,false))>=0)
					{
						++ endIdx;
						bHasFound = (startIdx<=endIdx);
					}
					break;
				}
				else if(cmp > 0)
				{
					end = mid - 1;
				}
				else
				{
					start = mid + 1;
				}
			}
			if (!bHasFound)
				return;
		}
#endif
		//��ȡ��ǰ���������
		CGeoRect<double> extent;
		extent.m_minX = (m_gridEntries[m_curIdx].m_gridIdx%m_gridNumX)*m_gridGapX+m_gridBaseX;
		extent.m_minY = (m_gridEntries[m_curIdx].m_gridIdx/m_gridNumX)*g_gridGapY+m_gridBaseY;
		//
		const static double offsetX(m_gridGapX/8);
		const static double offsetY(g_gridGapY/8);
		//����������һ������X�����ϵĿ�ʼ����
		int startX((m_sql.m_srchExtent.m_minX-extent.m_minX)/offsetX);
		if (startX<0)
		{
			startX = 0;
		}
		//����������һ������X�����ϵĽ�������
		int endX((m_sql.m_srchExtent.m_maxX-extent.m_minX)/offsetX);
		if (endX>=8)
		{
			endX = 7;
		}
		//����������һ������Y�����ϵĿ�ʼ����
		int startY((m_sql.m_srchExtent.m_minY-extent.m_minY)/offsetY);
		if (startY<0)
		{
			startY = 0;
		}
		//����������һ������Y�����ϵĽ�������
		int endY((m_sql.m_srchExtent.m_maxY-extent.m_minY)/offsetY);
		if (endY>=8)
		{
			endY = 7;
		}
		//TODO:���ǵĶ�������8*8�ȷֵģ��������90Ӧ��û�в���Խ��
		bool arrSubIdx[90] = {};
		for (int i(startY); i<=endY; ++i)
		{
			for (int j(startX); j<=endX; ++j)
			{
				arrSubIdx[(i + 1) * 10 + (j + 1)] = 1;
			}
		}
		for(int start(startIdx); start<endIdx; ++start)
		{
#ifndef USE_NEW_DATA
			short oneSubGridIdx(*(m_filterEntries+start));
			if (arrSubIdx[oneSubGridIdx&0xff])
			{
				idxes.Add(m_bodyEntries+start);
			}
#else
			TFilterEntry oneSubGridIdx(*(m_filterEntries+start));
			if (arrSubIdx[oneSubGridIdx.m_subGird])
			{
				idxes.Add(&start);
			}
#endif
		}
	}
#ifdef USE_NEW_DATA
	int CGridIndex::GetKindIdx(unsigned short codeMask,int startIdx,int endIdx,bool isGetStart)
	{
		register int mid(0),rt(-1),cmp(0);
		register int increase(isGetStart?-1:1);
		register int *pPtr(isGetStart?&endIdx:&startIdx);
		//
		while (startIdx<=endIdx)
		{
			mid = (startIdx+endIdx)>>1;
			if (!(cmp=((m_filterEntries+mid)->m_kind&codeMask)-m_sql.m_kind))
			{
				rt = mid;
				*pPtr = mid+increase;
			}
			else if (cmp>0)
			{
				endIdx = mid-1;
			}
			else
			{
				startIdx = mid+1;
			}
		}
		return rt;
	}
#endif
}