#ifndef _UEQUERY_QUERYDATAVERIFY_H
#include "QueryDataVerify.h"
#endif
#ifndef _UEQUERY_QUERYDEF_H
#include "uequery/querybasic.h"
#endif
#ifndef _UEMODEL_ROADNETWORK_H
#include "../uemodel/network.h"
#endif
#ifndef _UEMODEL_ROADLINK_H
#include "../uemodel/netlink.h"
#endif
#ifndef _UEBASE_DBGTRACER_H
#include "../uebase/dbglogger.h"
#endif
#ifndef _UEMODEL_NETPARCEL_H
#include "../uemodel\netparcel.h"
#endif
#ifndef _UEQUERY_DISTINDEX_H
#include "../uequery/distindex.h"
#endif
#ifndef _UEQUERY_GRIDINDEX_H
#include "../uequery/gridindex.h"
#endif
#ifndef _UEQUERY_KINDINDEX_H
#include "../uequery/kindindex.h"
#endif
#ifndef _UEQUERY_CROSSINDEX_H
#include "../uequery/crossindex.h"
#endif
#ifndef _UEQUERY_QUERYIMPL_H
#include "../uequery/uequeryimpl.h"
#endif
#ifndef _UEQUERY_ACRONYMINDEX_H
#include "../uequery/acronymindex.h"
#endif
#ifndef _UEGUI_DISTANDTYPEHOOK_H
#include "../uegui/DistAndTypeHook.h"
#endif
#ifndef _UEQUERY_QUICKWORDINDEX_H
#include "../uequery/quickwordindex.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	unsigned CQueryDataVerify::VerifyGridData(CUeQueryImpl *pQueryImpl)
	{
		UeBase::CDbgLogger logCtrl(_T("VerifyGridData"));
		//
		CUeIndex *pVerifyIndex(0),*pUeIndex(0);
		unsigned rt(InitPoiVerify(IT_Grid,pQueryImpl,pVerifyIndex,pUeIndex,&logCtrl));
		if (rt!=DT_Success)
			return rt;
		//
		int iPreGridIndex(-1),iPoiCount(0);
		GridVerifyMap::iterator iterInfo;
		GridVerifyMap poiInfo(TableEntryPtrCmp);

		CGridIndex *pGridIndex(reinterpret_cast<CGridIndex *>(pUeIndex));
		CGridIndex::GridIndex *pIdxEntry(pGridIndex->m_gridEntries);
		//
		for (int i(0); i<pGridIndex->m_idxCount; ++i,++pIdxEntry)
		{
			int idxGridX(0),idxGridY(0);
			{
				if (iPreGridIndex>=pIdxEntry->m_gridIdx)
				{
					//�����ǰ���С����˳������
					logCtrl.Log(_T("���������������δ���մ�С�������,preGridIdx=%d,curGridIdx=%d"),
						iPreGridIndex,pIdxEntry->m_gridIdx);
				}
				iPreGridIndex = pIdxEntry->m_gridIdx;
				if (iPreGridIndex<0 || iPreGridIndex>=(pGridIndex->m_gridNumX*pGridIndex->m_gridNumY))
				{
					logCtrl.Log(_T("��������������Χ��curGridIdx=%d,gridNumX=%d,gridNumY=%d"),
						iPreGridIndex,pGridIndex->m_gridNumX,pGridIndex->m_gridNumY);
				}
				//
				idxGridX = iPreGridIndex%pGridIndex->m_gridNumX;
				idxGridY = iPreGridIndex/pGridIndex->m_gridNumX;
			}
			//��������
			{
				unsigned uDistPoiCount(0);
				if (i!=(pGridIndex->m_idxCount-1))
				{
					uDistPoiCount = (pIdxEntry+1)->m_bodyIdx-pIdxEntry->m_bodyIdx;
				}
				else
				{
					uDistPoiCount = pGridIndex->m_bodyCount-pIdxEntry->m_bodyIdx;
				}
				if (uDistPoiCount==0)
				{
					logCtrl.Log(_T("����û��poi���ݵ����������\n"));
				}
				int lastKind(0);
				for (int j(0); j<uDistPoiCount; ++j)
				{
					unsigned uPoiIndex(pIdxEntry->m_bodyIdx+j);
					TableEntry *curEntry(pQueryImpl->m_generalDesc.m_fixedRecords+uPoiIndex);
					//
					static double offsetX((1.0 * 100000.) / 8);
					//static double offsetY((5.0 * 100000.) / 60);
					static double offsetY(pGridIndex->m_gridGapY+0.33);
					//static double offsetY(pGridIndex->m_gridGapY);
					//��ȡ����������
					int gridX((curEntry->m_x-pGridIndex->m_gridBaseX)/offsetX);
					if (gridX!=idxGridX)
					{
						logCtrl.Log(_T("db��poi���ڵ�����X����������뵱ǰ���������X�����������ͬ��dbGridX=%d,blockGridX=%d\n"),
							gridX,idxGridX);
					}
#if 0
					int gridY((curEntry->m_y-pGridIndex->m_gridBaseY)/offsetY);
					if (gridY!=idxGridY)
					{
						logCtrl.Log(_T("db��poi���ڵ�����Y����������뵱ǰ���������Y�����������ͬ��dbGridY=%d,blockGridY=%d\n"),
							gridY,idxGridY);
					}
#endif
					//��������
					int subGridX = (curEntry->m_x-(idxGridX*offsetX+pGridIndex->m_gridBaseX))/(offsetX/8);
					int subGridY = (curEntry->m_y-(idxGridY*offsetY+pGridIndex->m_gridBaseY))/(offsetY/8);
					int subGridIdx((subGridY+1)*10+subGridX+1);
					//
//#ifdef USE_NEW_DATA
#if 0
					if ((pGridIndex->m_filterEntries[uPoiIndex].m_subGird&0xff)!=subGridIdx)
					{
						logCtrl.Log(_T("db��poi����Ķ�������������mj��Ӧ���ݸ����Ĳ�ͬ��dbSubGridIdx=%d,mjSubGridIdx=%d\n"),
							subGridIdx,(pGridIndex->m_filterEntries[uPoiIndex].m_subGird&0xff));
					}
#endif
					if (lastKind>pGridIndex->m_filterEntries[uPoiIndex].m_kind)
					{
						logCtrl.Log(_T("������poi�������δ�������ʹ�С�������,preKind=%d,curKind=%d"),
							lastKind,pGridIndex->m_filterEntries[uPoiIndex].m_kind);
					}
					else
					{
						lastKind = pGridIndex->m_filterEntries[uPoiIndex].m_kind;
					}
					//
					if ((iterInfo=poiInfo.find(curEntry))==poiInfo.end())
					{
						poiInfo.insert(GridVerifyMap::value_type(curEntry,pIdxEntry->m_gridIdx));
					}
					else
					{
						if (curEntry==iterInfo->first)
						{
							logCtrl.Log(_T("������ͬpois.db�������,poiIndex=%d\n"),uPoiIndex);
						}
						else
						{
							if (iterInfo->second==pIdxEntry->m_gridIdx)
							{
								CGridIndex::TFilterEntry *pCurFilter(pGridIndex->m_filterEntries+uPoiIndex),
									*pLastFilter(pGridIndex->m_filterEntries+(iterInfo->first-pQueryImpl->m_generalDesc.m_fixedRecords));
								//
								logCtrl.Log(_T("ͬһ�����У�������ͬ���ݵ����,lastGridIdx=%d,curGridIdx=%d,lastKind=%d,curKind=%d,lastSubGrid=%d,curSubGrid=%d,x=%d,y=%d,lastAddrCode=%d,curAddrCode=%d,nameOffset=%d\n"),
									iterInfo->second,pIdxEntry->m_gridIdx,pLastFilter->m_kind,pCurFilter->m_kind,pLastFilter->m_subGird,pCurFilter->m_subGird,curEntry->m_x,curEntry->m_y,iterInfo->first->m_addrCode,
									curEntry->m_addrCode,curEntry->m_nameOffset);
							}
							else
							{
								logCtrl.Log(_T("��ͬ�����У�������ͬ���ݵ����,lastGridIdx=%d,curGridIdx=%d,x=%d,y=%d,lastAddrCode=%d,curAddrCode=%d,nameOffset=%d\n"),
									iterInfo->second,pIdxEntry->m_gridIdx,curEntry->m_x,curEntry->m_y,iterInfo->first->m_addrCode,curEntry->m_addrCode,curEntry->m_nameOffset);
							}
							if (curEntry->m_addrCode!=iterInfo->first->m_addrCode)
							{
								logCtrl.Log(_T("�ҳ�����ͬһ��γ�ȵ����ڲ�ͬ������������\n"));
							}
						}
					}
				}
				iPoiCount += uDistPoiCount;
			}
		}
		if (iPoiCount!=pGridIndex->m_bodyCount)
		{
			logCtrl.Log(_T("ʵ�ʶ�ȡ��poi��Ŀ�����ݸ�����poi��Ŀ��ͬ,realPoiCount=%d,mjBodyCount=%d"),
				iPoiCount,pGridIndex->m_bodyCount);
		}
		return DT_Success;
	}
	unsigned CQueryDataVerify::VerifyKindData(CUeQueryImpl *pQueryImpl)
	{
		UeBase::CDbgLogger logCtrl(_T("VerifyKindData"));
		//
		CUeIndex *pVerifyIndex(0),*pUeIndex(0);
		unsigned rt(InitPoiVerify(IT_Kind,pQueryImpl,pVerifyIndex,pUeIndex,&logCtrl));
		if (rt!=DT_Success)
			return rt;
		GridVerifyMap::iterator iterInfo;
		GridVerifyMap poiInfo(TableEntryPtrCmp);
		CGridIndex *pGridIndex(reinterpret_cast<CGridIndex *>(pUeIndex));
		CKindIndex *pKindIndex(reinterpret_cast<CKindIndex *>(pVerifyIndex));
		//������͡�������м���
		unsigned preKind(0),preDist(0),poiCount(0);
		CKindIndex::KindIndex *pIdxEntry(pKindIndex->m_kindEntries);
		for (int i(0); i<pKindIndex->m_idxCount; ++i,++pIdxEntry)
		{
			//��������
			{
				if (preKind==pIdxEntry->m_kind
					&& preDist>=pIdxEntry->m_addrCode)
				{
					logCtrl.Log(_T("ͬһ�����µ���������û�а������С�����������,kindCode=%d,preDistCode=%d,curDistCode=%d\n"),
						preKind,preDist,pIdxEntry->m_addrCode);
				}
				preDist = pIdxEntry->m_addrCode;
				//
				char cDistNameBuf[256] = {};
				UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(preDist,
					cDistNameBuf,true,false);
				if (cDistNameBuf[0]==0)
				{
					//�����ڵ�����
					logCtrl.Log(_T("����������벻����,curDistCode=%d\n"),
						pIdxEntry->m_addrCode);
				}
#if 0
				TCHAR tchDistName[256];
				CStringBasic::Get().Ascii2Chs(cDistNameBuf,tchDistName,256);
				logCtrl.Log(_T("%s\n"),tchDistName);
#endif
			}
			//��������
			{
				if (preKind>pIdxEntry->m_kind)
				{
					logCtrl.Log(_T("���ͱ���û�д�С�����������,preKindCode=%d,curKindCode=%d\n"),
						preKind,pIdxEntry->m_kind);
					return DT_IndexOrderErr;
				}
				preKind = pIdxEntry->m_kind;
				//�鿴�����Ƿ����
				char cKindNameBuf[256] = {};
				//
				unsigned uKindCode(preKind&0xf000);
				uKindCode <<= 4;
				uKindCode |= preKind&0xfff;
				UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(uKindCode,
					cKindNameBuf,false,false);
				if (cKindNameBuf[0]==0)
				{
					logCtrl.Log(_T("KindIndexs�����ͱ��벻����,curKindCode=%d\n"),
						preKind);
				}
#if 0
				else
				{
					TCHAR tchKindName[256];
					CStringBasic::Get().Ascii2Chs(cKindNameBuf,tchKindName,256);
					logCtrl.Log(_T("%s\n"),tchKindName);
				}
#endif
			}
			//������ݽ��м���
			{
				unsigned blockPoiCount(0);
				if (i!=(pKindIndex->m_idxCount-1))
				{
					blockPoiCount = (pIdxEntry+1)->m_bodyIdx-pIdxEntry->m_bodyIdx;
				}
				else
				{
					blockPoiCount = pKindIndex->m_bodyCount-pIdxEntry->m_bodyIdx;
				}
#ifdef USE_NEW_DATA
				char *pchAcrData(pKindIndex->m_pchAcroEntries+pIdxEntry->m_bodyIdx*pKindIndex->MAXACROENTRY);
#else
				char *pchAcrData(0);
#endif
				for (int j(0); j<blockPoiCount; ++j,pchAcrData+=pKindIndex->MAXACROENTRY)
				{
#ifdef USE_NEW_DATA
					unsigned poiIndex(*(pKindIndex->m_bodyEntries+pIdxEntry->m_bodyIdx+j));
#else
					unsigned poiIndex(0);
#endif
					//
					TableEntry *curEntry(pQueryImpl->m_generalDesc.m_fixedRecords+poiIndex);
					//
#ifdef USE_NEW_DATA
					CGridIndex::TFilterEntry curFilterEntry(*(pGridIndex->m_filterEntries+poiIndex));
					if (pIdxEntry->m_kind!=curFilterEntry.m_kind)
					{
						logCtrl.Log(_T("���ݿ������������grid�и��������Ͳ�ͬ,blockKind=%d,gridKind=%d,poiIndex=%d,x=%d,y=%d,addrCode=%d,nameOffset=%d\n"),
							pIdxEntry->m_kind,curFilterEntry.m_kind,poiIndex,curEntry->m_x,curEntry->m_y,curEntry->m_addrCode,curEntry->m_nameOffset);
					}
					if (curEntry->m_addrCode!=pIdxEntry->m_addrCode)
					{
						logCtrl.Log(_T("���ݿ���������������db�и�����������벻ͬ,blockDist=%d,poiIndex=%d,x=%d,y=%d,addrCode=%d,nameOffset=%d\n"),
							pIdxEntry->m_addrCode,poiIndex,curEntry->m_x,curEntry->m_y,curEntry->m_addrCode,curEntry->m_nameOffset);
					}
					short length(0);
					char *pchTempString(pQueryImpl->m_name);
					pQueryImpl->m_nameTable->GetContent(curEntry->m_nameOffset,
						&pchTempString,length,false);
					//
					TCHAR tchName[256];
					CStringBasic::Get().Ascii2Chs(pchTempString,tchName,128);
					//
					VerifyAcronymData(pchTempString,pchAcrData,pKindIndex->MAXACROENTRY,&logCtrl);

					unsigned uCurFilter(0);
					::memcpy(&uCurFilter,pGridIndex->m_filterEntries+poiIndex,sizeof(curFilterEntry));
					if ((iterInfo=poiInfo.find(curEntry))==poiInfo.end())
					{
						poiInfo.insert(GridVerifyMap::value_type(curEntry,uCurFilter));
					}
					else
					{
						if (curEntry==iterInfo->first)
						{
							logCtrl.Log(_T("%s:�����г�����ͬpois.db���������:poiIdex=%d\n"),tchName,poiIndex);
						}
						else
						{
							CGridIndex::TFilterEntry lastFilterEntry;
							::memcpy(&lastFilterEntry,&(iterInfo->second),sizeof(curFilterEntry));
							if (uCurFilter==iterInfo->second)
							{
								logCtrl.Log(_T("%s:ͬһGrid���������У�������ͬ����,lastPoiIndex=%d,curPoiIndex=%d,lastKind=%u,lastSubGrid=%u,curKind=%u,curSubGrid=%u,x=%d,y=%d,addrCode=%d,nameOffset=%d\n"),
									tchName,iterInfo->first-pQueryImpl->m_generalDesc.m_fixedRecords,poiIndex,lastFilterEntry.m_kind,lastFilterEntry.m_subGird,
									curFilterEntry.m_kind,curFilterEntry.m_subGird,curEntry->m_x,curEntry->m_y,curEntry->m_addrCode,curEntry->m_nameOffset);
							}
							else
							{
								logCtrl.Log(_T("%s:��ͬGrid���������У�������ͬ����,lastPoiIndex=%d,curPoiIndex=%d,lastKind=%u,lastSubGrid=%u,curKind=%u,curSubGrid=%u,x=%d,y=%d,addrCode=%d,nameOffset=%d\n"),
									tchName,iterInfo->first-pQueryImpl->m_generalDesc.m_fixedRecords,poiIndex,lastFilterEntry.m_kind,lastFilterEntry.m_subGird,
									curFilterEntry.m_kind,curFilterEntry.m_subGird,curEntry->m_x,curEntry->m_y,curEntry->m_addrCode,curEntry->m_nameOffset);
							}
						}
					}
#endif
				}
				poiCount += blockPoiCount;
			}
		}
		if (poiCount!=pKindIndex->m_bodyCount)
		{
			logCtrl.Log(_T("ʵ�ʶ�ȡ��poi��Ŀ�����ݸ�����poi��Ŀ��ͬ,realPoiCount=%d,mjBodyCount=%d"),
				poiCount,pKindIndex->m_bodyCount);
			return DT_PoiCountErr;
		}
		return DT_Success;
	}
	unsigned CQueryDataVerify::VerifyCrossData(CUeQueryImpl *pQueryImpl)
	{
		UeBase::CDbgLogger logCtrl(_T("VerifyCross"));
		CUeIndex *pUeIndex(0);
		if (pQueryImpl->GetIndex(IT_Cross,pUeIndex)!=SQL_Success || pUeIndex==0)
		{
			logCtrl.Log(_T("��·���������޷��򿪣�������Ӧ�����ļ�\n"));
			return DT_IndexInitErr;
		}
		RoadVerifyMap::iterator iterInfo;
		RoadVerifyMap roadInfo(TLinkBodyEntryCmp);
		CCrossIndex *pCrossIndex(reinterpret_cast<CCrossIndex *>(pUeIndex));
		//
		unsigned uPreDistCode(0),uRoadCount(0);
		CDistIndex::TDistEntry *pDistEntry(pCrossIndex->m_pDistEntries);
		for (int i(0); i<pCrossIndex->m_idxCount; ++i,++pDistEntry)
		{
			//������������
			{
				if (uPreDistCode>=pDistEntry->m_distCode)
				{
					//�����ǰ���С����˳������
					logCtrl.Log(_T("��������������δ���մ�С�������,preDistCode=%d,curDistCode=%d\n"),
						uPreDistCode,pDistEntry->m_distCode);
					return DT_IndexOrderErr;
				}
				uPreDistCode = pDistEntry->m_distCode;
				//
				char cDistNameBuf[256] = {};
				UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(uPreDistCode,
					cDistNameBuf,true,false);
				if (cDistNameBuf[0]==0)
				{
					//�����ڵ�����
					logCtrl.Log(_T("����������,�����ڸ��������,curDistCode=%d\n"),
						pDistEntry->m_distCode);
					return DT_DistNotExist;
				}
				TCHAR tchDistName[256];
				CStringBasic::Get().Ascii2Chs(cDistNameBuf,tchDistName,256);
				logCtrl.Log(_T("%s\n"),tchDistName);
			}
			//��������
			{
				unsigned uDistRoadCount(0);
				if (i!=(pCrossIndex->m_idxCount-1))
				{
					uDistRoadCount = (pDistEntry+1)->m_startAcro-pDistEntry->m_startAcro;
				}
				else
				{
					uDistRoadCount = pCrossIndex->m_bodyCount-pDistEntry->m_startAcro;
				}
				char *pchRoadAcro(pCrossIndex->m_pchAcroEntries+pDistEntry->m_startAcro*pCrossIndex->MAXACROENTRY);
				for (int j(0); j<uDistRoadCount; ++j,pchRoadAcro+=pCrossIndex->MAXACROENTRY)
				{
					SQLRecord oneRecord;
					oneRecord.m_idx = pDistEntry->m_startAcro+j;


					CCrossIndex::CrossBodyEntry *pCurLinkInfo(pCrossIndex->m_bodyEntries+oneRecord.m_idx);
					TLinkBodyEntry *pCurLinkEntry(static_cast<TLinkBodyEntry *>(::malloc(sizeof(TLinkBodyEntry))));
					if (pCurLinkEntry!=0)
					{
						pCurLinkEntry->m_addrCode = pDistEntry->m_distCode;
						pCurLinkEntry->m_parcelIdx = pCurLinkInfo->m_parcelIdx;
						pCurLinkEntry->m_linkIdx = pCurLinkInfo->m_linkIdx;
						//
						if ((iterInfo=roadInfo.find(pCurLinkEntry))==roadInfo.end())
						{
							roadInfo.insert(pCurLinkEntry);
						}
						else
						{
							//
							logCtrl.Log(_T("��ͬһ�������г�����ͬlink�����,lastAddrCode=%u,curAddrCode=%u,lastParcelIdx=%d,curParcelIdx=%d,lastLinkIdx=%d,curLinkIdx=%d\n"),
								(*iterInfo)->m_addrCode,pCurLinkEntry->m_addrCode,(*iterInfo)->m_parcelIdx,pCurLinkEntry->m_parcelIdx,(*iterInfo)->m_linkIdx,pCurLinkEntry->m_linkIdx);
							//
							::free(pCurLinkEntry);
						}
					}
					//
					if (pCrossIndex->GetRecord(&oneRecord)==SQL_Success)
					{
						if (oneRecord.m_uniName && oneRecord.m_uniLen)
						{
							::strcpy(pQueryImpl->m_name,oneRecord.m_uniName);
							VerifyAcronymData(pQueryImpl->m_name,pchRoadAcro,
								pCrossIndex->MAXACROENTRY,&logCtrl);
						}
						//��ȡ����㣬�ж����Ƿ�����ĵ��Ƿ����ڸ����������
						INetParcel *oneParcel(IRoadNetwork::GetNetwork()->GetParcel(UeModel::PT_Real,
							oneRecord.m_parcelIdx));
						if(oneParcel!=0)
						{
							//��ȡ��·��Ϣ
							INetLink *oneLink(oneParcel->GetLink(oneRecord.m_linkIdx));
							if(oneLink!=0)
							{
								// Get road coords, since m_x & m_y is used to record network info, here use addrcode & telephone to 
								// record road's coords
								CGeoPoint<long> vertice[500];
								short vertexCount = 0; // short vertexCount = 500;
								//��ȡ��·����������꣬��ʵ���Ӧ�÷��ڲ�·�ߵ��Լ�
								//�鿴��·ʱ�ڻ�ȡҲ����,����һ��·�ĵ���Ŀ�Ƿ���г���
								//500�������������Ƕ�ʧ����ô�ɣ�
								oneLink->BuildVertex(vertice, vertexCount, oneRecord.m_linkIdx, oneParcel);
								bool bIsHaveIn(false);
								//��ȡ�����С
								CGeoRect<double> parcelMbr;
								oneParcel->GetMBR(parcelMbr);
								for(int k(0); k < vertexCount; k++)
								{
									if (UeGui::CDistAndTypeHook::GetDistCode(vertice[k].m_x+parcelMbr.m_minX,
										vertice[k].m_y+parcelMbr.m_minY)==pDistEntry->m_distCode)
									{
										bIsHaveIn = true;
										break;
									}
								}
								if (!bIsHaveIn)
								{
									TCHAR tchRoadName[256];
									CStringBasic::Get().Ascii2Chs(oneRecord.m_uniName,tchRoadName,256);
									//
									logCtrl.Log(_T("��·:%s,����ĵ㶼���ڵ�ǰ�������ڣ������Ƿ�����,parcelIdx=%d,linkIdx=%d,curDistCode=%d\n"),
										tchRoadName,oneRecord.m_parcelIdx,oneRecord.m_linkIdx,pDistEntry->m_distCode);
								}
							}
						}
						::free(oneRecord.m_uniName);
					}
				}
				uRoadCount += uDistRoadCount;
			}
		}
		if (uRoadCount!=pCrossIndex->m_bodyCount)
		{
			logCtrl.Log(_T("ʵ�ʶ�ȡ��poi��Ŀ�����ݸ�����poi��Ŀ��ͬ,realRoadCount=%d,mjBodyCount=%d"),
				uRoadCount,pCrossIndex->m_bodyCount);
			return DT_PoiCountErr;
		}
		for (iterInfo=roadInfo.begin(); iterInfo!=roadInfo.end(); ++iterInfo)
		{
			::free(*iterInfo);
		}
		return DT_Success;
	}
	unsigned CQueryDataVerify::VerifyCrossExData(CUeQueryImpl *pQueryImpl)
	{
		UeBase::CDbgLogger logCtrl(_T("VerifyCrossIdx"));
		CUeIndex *pUeIndex(0);
		if (pQueryImpl->GetIndex(IT_CrossEx,pUeIndex)!=SQL_Success || pUeIndex==0)
		{
			logCtrl.Log(_T("����ڼ��������޷��򿪣�������Ӧ�����ļ�\n"));
			return DT_IndexInitErr;
		}
		CrossVerifyMap::iterator iterInfo;
		CrossVerifyMap crossInfo(CrossBodyEntryCmp);
		CCrossIndexExtend *pCrossIndex(reinterpret_cast<CCrossIndexExtend *>(pUeIndex));
		unsigned uPreDistCode(0),uCrossCount(0);
		CDistIndex::TDistEntry *pDistEntry(pCrossIndex->m_pDistEntries);
		for (int i(0); i<pCrossIndex->m_idxCount; ++i,++pDistEntry)
		{
			//������������
			{
				if (uPreDistCode>=pDistEntry->m_distCode)
				{
					//�����ǰ���С����˳������
					logCtrl.Log(_T("��������������δ���մ�С�������,preDistCode=%d,curDistCode=%d\n"),
						uPreDistCode,pDistEntry->m_distCode);
				}
				uPreDistCode = pDistEntry->m_distCode;
				//
				char cDistNameBuf[256] = {};
				UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(uPreDistCode,
					cDistNameBuf,true,false);
				if (cDistNameBuf[0]==0)
				{
					//�����ڵ�����
					logCtrl.Log(_T("����������,�����ڸ��������,curDistCode=%d\n"),
						pDistEntry->m_distCode);
				}
				TCHAR tchDistName[256];
				CStringBasic::Get().Ascii2Chs(cDistNameBuf,tchDistName,256);
				logCtrl.Log(_T("%s\n"),tchDistName);
			}
			//��������
			{
				unsigned uDistCrossCount(0);
				if (i!=(pCrossIndex->m_idxCount-1))
				{
					uDistCrossCount = (pDistEntry+1)->m_startAcro-pDistEntry->m_startAcro;
				}
				else
				{
					uDistCrossCount = pCrossIndex->m_bodyCount-pDistEntry->m_startAcro;
				}
				char *pchCrossAcro(pCrossIndex->m_pchAcroEntries+pDistEntry->m_startAcro*pCrossIndex->MAXACROENTRY);
				for (int j(0); j<uDistCrossCount; ++j,pchCrossAcro+=pCrossIndex->MAXACROENTRY)
				{
					SQLRecord oneRecord;
					oneRecord.m_idx = pDistEntry->m_startAcro+j;
					CCrossIndexExtend::CrossBodyEntry *pCurCrossInfo(pCrossIndex->m_bodyEntries+oneRecord.m_idx);
					TCrossBodyEntry *pCrossEntry(static_cast<TCrossBodyEntry *>(::malloc(sizeof(TCrossBodyEntry))));
					if (pCrossEntry!=0)
					{
						pCrossEntry->m_x = pCurCrossInfo->m_x;
						pCrossEntry->m_y = pCurCrossInfo->m_y;
						pCrossEntry->m_pchRoadInfo = pchCrossAcro;
						//
						if ((iterInfo=crossInfo.find(pCrossEntry))==crossInfo.end())
						{
							crossInfo.insert(CrossVerifyMap::value_type(pCrossEntry,pDistEntry->m_distCode));
						}
						else
						{
							TCHAR tchAcroEntry[128];
							CStringBasic::Get().Ascii2Chs(pchCrossAcro,tchAcroEntry,128);
							if (pDistEntry->m_distCode==iterInfo->second)
							{
								logCtrl.Log(_T("ͬһ���������ڣ�������ͬ����ڵ����,lastAddrCode=%u,curAddrCode=%u,acroEntry=%s\n"),
									iterInfo->second,pDistEntry->m_distCode,tchAcroEntry);
							}
							else
							{
								logCtrl.Log(_T("��ͬ���������ڣ�������ͬ����ڵ����,lastAddrCode=%u,curAddrCode=%u,acroEntry=%s\n"),
									iterInfo->second,pDistEntry->m_distCode,tchAcroEntry);
							}
							::free(pCrossEntry);
						}
					}
					//
					if (pCrossIndex->GetRecord(&oneRecord)==SQL_Success)
					{
						unsigned uDistCode(UeGui::CDistAndTypeHook::GetDistCode(oneRecord.m_x,
							oneRecord.m_y));
						if (uDistCode!=-1 && uDistCode!=pDistEntry->m_distCode)
						{
							short length(0);
							char *pchTempString(pchCrossAcro);
							for (; *pchTempString!='-'; ++pchTempString)
							{
							}
							unsigned roadANameOffset(::atoi(++pchTempString));
							pchTempString = 0;
							IRoadNetwork::GetNetwork()->GetNameTable(UeModel::UNT_Network)->GetContent(roadANameOffset,
								&pchTempString,length,false);
							{
								//TODO ��ʱ�ǵ������������
								length = pchTempString[0];
								::strncpy(pchTempString,pchTempString+1,length);
								pchTempString[length] = 0;
							}
							TCHAR tchRoadAName[256];
							CStringBasic::Get().Ascii2Chs(pchTempString,tchRoadAName,256);
							//
							TCHAR tchRoadBName[256];
							CStringBasic::Get().Ascii2Chs(oneRecord.m_asciiName,tchRoadBName,256);
							//
							logCtrl.Log(_T("��·:%s���·:%s�Ľ�������겻�ڵ�ǰ������,x=%d,y=%d,distCode=%d\n"),
								tchRoadAName,tchRoadBName,oneRecord.m_x,oneRecord.m_y,uDistCode);
							::free(pchTempString);
						}
						::free(oneRecord.m_asciiName);
					}
				}
				uCrossCount += uDistCrossCount;
			}
		}
		if (uCrossCount!=pCrossIndex->m_bodyCount)
		{
			logCtrl.Log(_T("ʵ�ʶ�ȡ�Ľ������Ŀ�����ݸ����Ľ������Ŀ��ͬ,realCrossCount=%d,mjBodyCount=%d"),
				uCrossCount,pCrossIndex->m_bodyCount);
			return DT_PoiCountErr;
		}
		for (iterInfo=crossInfo.begin(); iterInfo!=crossInfo.end(); ++iterInfo)
		{
			::free(iterInfo->first);
		}
		return DT_Success;
	}
	unsigned CQueryDataVerify::VerifyAcronymData(CUeQueryImpl *pQueryImpl)
	{
		UeBase::CDbgLogger logCtrl(_T("VerifyAcronym"));
		//
		CUeIndex *pVerifyIndex(0),*pUeIndex(0);
		unsigned rt(InitPoiVerify(IT_Acronym,pQueryImpl,pVerifyIndex,pUeIndex,&logCtrl));
		if (rt!=DT_Success)
			return rt;
		//
		GridVerifyMap::iterator iterInfo;
		GridVerifyMap poiInfo(TableEntryPtrCmp);
		CGridIndex *pGridIndex(reinterpret_cast<CGridIndex *>(pUeIndex));
		CAcronymIndex *pAcrIndex(reinterpret_cast<CAcronymIndex *>(pVerifyIndex));
		//���������м���
		unsigned uPreDistCode(0),uPoiCount(0);
		CDistIndex::TDistEntry *pDistEntry(pAcrIndex->m_pDistEntries);
		//
		for (int i(0); i<pAcrIndex->m_idxCount; ++i,++pDistEntry)
		{
			//������������
			{
				if (uPreDistCode>=pDistEntry->m_distCode)
				{
					//�����ǰ���С����˳������
					logCtrl.Log(_T("��������������δ���մ�С�������,preDistCode=%d,curDistCode=%d\n"),
						uPreDistCode,pDistEntry->m_distCode);
				}
				uPreDistCode = pDistEntry->m_distCode;
				//
				char cDistNameBuf[256] = {};
				UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(uPreDistCode,
					cDistNameBuf,true,false);
				if (cDistNameBuf[0]==0)
				{
					//�����ڵ�����
					logCtrl.Log(_T("����������,�����ڸ��������,curDistCode=%d\n"),
						pDistEntry->m_distCode);
				}
				TCHAR tchDistName[256];
				CStringBasic::Get().Ascii2Chs(cDistNameBuf,tchDistName,256);
				logCtrl.Log(_T("%s\n"),tchDistName);
			}
			//��������
			{
				if (pDistEntry->m_startAcro>=pAcrIndex->m_bodyCount)
				{
					logCtrl.Log(_T("��ǰ����poi��ʼλ�ô��ڵ����ܵ�poi��Ŀ,startIdx=%d,totalPoi=%d\n"),
						pDistEntry->m_startAcro,pAcrIndex->m_bodyCount);
				}
				unsigned uDistPoiCount(0);
				if (i!=(pAcrIndex->m_idxCount-1))
				{
					uDistPoiCount = (pDistEntry+1)->m_startAcro-pDistEntry->m_startAcro;
				}
				else
				{
					uDistPoiCount = pAcrIndex->m_bodyCount-pDistEntry->m_startAcro;
				}
				char *pchAcrData(pAcrIndex->m_pchAcroEntries+pDistEntry->m_startAcro*pAcrIndex->MAXACROENTRY);
				for (int j(0); j<uDistPoiCount; ++j,pchAcrData+=pAcrIndex->MAXACROENTRY)
				{
					unsigned uPoiIndex(*(pAcrIndex->m_bodyEntries+pDistEntry->m_startAcro+j));
					//
					TableEntry *curEntry(pQueryImpl->m_generalDesc.m_fixedRecords+uPoiIndex);
					//
					if (curEntry->m_addrCode!=pDistEntry->m_distCode)
					{
						logCtrl.Log(_T("db�е���������뵱ǰ���ݿ�������������벻ͬ��dbDist=%d,blockDist=%d\n"),
							curEntry->m_addrCode,pDistEntry->m_distCode);
					}
					short length(0);
					char *pchTempString(pQueryImpl->m_name);
					pQueryImpl->m_nameTable->GetContent(curEntry->m_nameOffset,
						&pchTempString,length,false);
					//
					TCHAR tchName[256];
					CStringBasic::Get().Ascii2Chs(pchTempString,tchName,256);
					//
					if (0)
					{
						VerifyAcronymData(pchTempString,pchAcrData,
							pAcrIndex->MAXACROENTRY,&logCtrl);
					}
#ifdef USE_NEW_DATA
					if (pGridIndex!=0)
					{
						unsigned short poiKind(pGridIndex->GetPoiKind(uPoiIndex));
						unsigned uKindCode(poiKind&0xf000);
						uKindCode <<= 4;
						uKindCode |= poiKind&0xfff;
						//�鿴�����Ƿ����
						char cKindNameBuf[256] = {};
						UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(uKindCode,
							cKindNameBuf,false,false);
						if (cKindNameBuf[0]==0)
						{
							logCtrl.Log(_T("%s:���ͱ��벻����,curKindCode=%d\n"),
								tchName,poiKind);
						}
					}
#endif
					unsigned uDistCode(UeGui::CDistAndTypeHook::GetDistCode(curEntry->m_x,curEntry->m_y));
					if (uDistCode!=-1 && uDistCode!=curEntry->m_addrCode)
					{
						logCtrl.Log(_T("%s:�������겻������Χ��,x=%d,y=%d,distCode=%d\n"),
							tchName,curEntry->m_x,curEntry->m_y,uDistCode);
					}
#ifdef USE_NEW_DATA
					CGridIndex::TFilterEntry curFilterEntry(*(pGridIndex->m_filterEntries+uPoiIndex));
					unsigned uCurFilter(0);
					::memcpy(&uCurFilter,pGridIndex->m_filterEntries+uPoiIndex,sizeof(curFilterEntry));
					if ((iterInfo=poiInfo.find(curEntry))==poiInfo.end())
					{
						poiInfo.insert(GridVerifyMap::value_type(curEntry,uCurFilter));
					}
					else
					{
						if (curEntry==iterInfo->first)
						{
							logCtrl.Log(_T("%s:�����г�����ͬpois.db���������:poiIdex=%d\n"),tchName,uPoiIndex);
						}
						else
						{
							CGridIndex::TFilterEntry lastFilterEntry;
							::memcpy(&lastFilterEntry,&(iterInfo->second),sizeof(curFilterEntry));
							if (uCurFilter==iterInfo->second)
							{
								logCtrl.Log(_T("%s:ͬһGrid���������У�������ͬ����,lastPoiIndex=%d,curPoiIndex=%d,lastKind=%u,lastSubGrid=%u,curKind=%u,curSubGrid=%u,x=%d,y=%d,addrCode=%d,nameOffset=%d\n"),
									tchName,iterInfo->first-pQueryImpl->m_generalDesc.m_fixedRecords,uPoiIndex,lastFilterEntry.m_kind,lastFilterEntry.m_subGird,
									curFilterEntry.m_kind,curFilterEntry.m_subGird,curEntry->m_x,curEntry->m_y,curEntry->m_addrCode,curEntry->m_nameOffset);
							}
							else
							{
								logCtrl.Log(_T("%s:��ͬGrid���������У�������ͬ����,lastPoiIndex=%d,curPoiIndex=%d,lastKind=%u,lastSubGrid=%u,curKind=%u,curSubGrid=%u,x=%d,y=%d,addrCode=%d,nameOffset=%d\n"),
									tchName,iterInfo->first-pQueryImpl->m_generalDesc.m_fixedRecords,uPoiIndex,lastFilterEntry.m_kind,lastFilterEntry.m_subGird,
									curFilterEntry.m_kind,curFilterEntry.m_subGird,curEntry->m_x,curEntry->m_y,curEntry->m_addrCode,curEntry->m_nameOffset);
							}
						}
					}
#endif
				}
				uPoiCount += uDistPoiCount;
			}
		}
		if (uPoiCount!=pAcrIndex->m_bodyCount)
		{
			logCtrl.Log(_T("ʵ�ʶ�ȡ��poi��Ŀ�����ݸ�����poi��Ŀ��ͬ,realPoiCount=%d,mjBodyCount=%d"),
				uPoiCount,pAcrIndex->m_bodyCount);
			return DT_PoiCountErr;
		}
		return DT_Success;
	}
	unsigned CQueryDataVerify::VerifyQuickWordData(CUeQueryImpl *pQueryImpl)
	{
		UeBase::CDbgLogger logCtrl(_T("VerifyQuickWordData"));
		//
		if (pQueryImpl->ConnectToGeneral()!=SQL_Success)
		{
			logCtrl.Log(_T("pois.db�����⣬�������������Ƿ�����°�����"));
			return DT_DBErr;
		}
		//
		CUeIndex *pUeIndex(0);
		if (pQueryImpl->GetIndex(IT_QuickWord,pUeIndex)!=SQL_Success || pUeIndex==0)
		{
			logCtrl.Log(_T("�ִʼ��������޷��򿪣�������Ӧ�����ļ�\n"));
			return DT_IndexInitErr;
		}
		//�������Ʒ��ʶ���
		pQueryImpl->m_nameTable = pQueryImpl->m_poiNameTable;
		CQuickWordIndex *pQuickIndex(reinterpret_cast<CQuickWordIndex *>(pUeIndex));
		//�ȼ�������Ƿ񰴴�С���������
		for (int i(0),preDistCode(0); i<pQuickIndex->m_idxCount; ++i)
		{
			if (preDistCode>=pQuickIndex->m_cities[i])
			{
				//�����ǰ���С����˳������
				logCtrl.Log(_T("��������������δ���մ�С�������,preDistCode=%d,curDistCode=%d\n"),
					preDistCode,pQuickIndex->m_cities[i]);
				return DT_IndexOrderErr;
			}
			preDistCode = pQuickIndex->m_cities[i];
			//
			char cDistNameBuf[256] = {};
#ifndef USE_NEW_DATA
			UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(preDistCode<<8,
				cDistNameBuf,true,false);
#else
			UeGui::CDistAndTypeHook::GetHook()->getItemNameByCode(preDistCode,
				cDistNameBuf,true,false);
#endif
			if (cDistNameBuf[0]==0)
			{
				//�����ڵ�����
				logCtrl.Log(_T("����������,�����ڸ��������,curDistCode=%d\n"),
					preDistCode);
				::itoa(preDistCode,cDistNameBuf,10);
				//return DT_DistNotExist;
			}
			TCHAR tchDistName[256] = {};
			CStringBasic::Get().Ascii2Chs(cDistNameBuf,tchDistName,256);
			logCtrl.Log(_T("%s\n"),tchDistName);
			//�����������ִ�
			CQuickWordIndex::QuickCharacter *pTermInfo(pQuickIndex->m_characters);
			for (int j(0); j<pQuickIndex->m_bodyCount; ++j,++pTermInfo)
			{
				UeQuery::CQuickWordIndex::QuickExtractedWord curWord;
				curWord.m_offset = j;
				//
				TCHAR tchTermChar[256];
				int tStrLen(::strlen(pTermInfo->m_bytes));
				CStringBasic::Get().Ascii2Chs(pTermInfo->m_bytes,tchTermChar,256);
				//
				if (pQuickIndex->GetTIDs(curWord,i) && curWord.m_dataBuffer!=0)
				{
					//logCtrl.Log(_T("	��ǰ����=%s�У��ִ�=%s�������÷ִʵ�poi��ĿΪ%d\n"),
					//	tchDistName,tchTermChar,curWord.m_tids);
#if 1
					//��ȡ�ִ��ڸ������ڵ���ϸ��Ϣ
					int curTidOrder(0);
					// Read group basic information which is leaded by one word and its corresponding city
					unsigned char *cursor = reinterpret_cast<unsigned char *>(curWord.m_dataBuffer);
					//
					unsigned char curGrpOrder(*cursor++);
					unsigned char curBlockOrder(*cursor++);
					// Loop the whole buffer and extract information in group
					while (curGrpOrder!=0xFF)
					{
						// Order indicating each group
						unsigned char nextGrpOrder(*cursor++);
						// Number of blocks belonging to current group
						unsigned char nextFirstBlockOrder(*cursor++);
						// Get header information of each group
						int grpStartPos((curGrpOrder-1)*CQuickWordIndex::m_maxGrpTids);
						//
						while (curBlockOrder!=0xFF)
						{
							// Loop the whole buffer and extract information in blocks
							unsigned char nextBlockOrder(*cursor++);
							unsigned char blocks(*cursor++);
							// Get header information of each block
							for(int t(0),blockStartPos((curBlockOrder-1)*CQuickWordIndex::m_maxBlockTids);
								t<blocks; ++t)
							{
								unsigned poiIndex(*cursor++);
								poiIndex += grpStartPos+blockStartPos;
								TableEntry *curEntry(pQueryImpl->m_generalDesc.m_fixedRecords+poiIndex);

								short length(0);
								char *pchTempString(pQueryImpl->m_name);
								pQueryImpl->m_nameTable->GetContent(curEntry->m_nameOffset,&pchTempString,length,false);
								//
								TCHAR tchPoiName[256];
								CStringBasic::Get().Ascii2Chs(pchTempString,tchPoiName,256);
								//
								UeBase::CStringBasic::Get().clearStringSign(pchTempString);
								//��ȡ�ִʵ�λ����Ϣ
								int posNum(0);
								for (int posTemp(0),curPos(0); ; ++curPos)
								{
									posTemp = (cursor[curPos]>>5);
									if (posTemp==0)
									{
										logCtrl.Log(_T("	�ִ���index=%d,name=%s�г���λ����ĿΪ0�����\n"),
											poiIndex,tchPoiName);
										break;
									}
									posNum += posTemp;
									if (posTemp<7)
										break;
								}
								//
								if (posNum<1)
								{
									logCtrl.Log(_T("	�ִ���index=%d,name=%s�г���λ����ĿС��1�����\n"),
										poiIndex,tchPoiName);
									continue;
								}
								int k(0),m(0),sStrLen(::strlen(pchTempString));
								for (; k<posNum; ++k,++cursor)
								{
									m = UeBase::CStringBasic::Get().Find(pchTempString,sStrLen,
										pTermInfo->m_bytes,tStrLen,m);
									if (m!=(*cursor&0x1f))
									{
										logCtrl.Log(_T("	�ִ���index=%d,name=%s,dbPos=%d,mjDataPos=%d������ʵ��λ�ò�ͬ�����\n"),
											poiIndex,tchPoiName,m,(*cursor&0x1f));
									}
									if (m<sStrLen)
									{
										if (pchTempString[m]<0)
										{
											m += 2;
										}
										else
										{
											++m;
										}
									}
									else
									{
										if (k<(posNum-1))
										{
											logCtrl.Log(_T("	�ִ���index=%d,name=%s,dbPosNum=%d,mjPosNum=%dʵ�ʳ��ֵĴ�������\n"),
												poiIndex,tchPoiName,k,posNum);
										}
										break;
									}
								}
								if (m<sStrLen)
								{
									m = UeBase::CStringBasic::Get().Find(pchTempString,sStrLen,
										pTermInfo->m_bytes,tStrLen,m);
									//
									if (m!=-1)
									{
										logCtrl.Log(_T("	�ִ���index=%d,name=%s,dbPos=%d������û�м��صķִ�λ��\n"),
											poiIndex,tchPoiName,m);
									}
								}
								//
								if (curEntry->m_addrCode!=pQuickIndex->m_cities[i])
								{
									logCtrl.Log(_T("	�ִ���index=%d,name=%s,dbDistCode=%d,mjDistCode���ߵ�������벻ͬ\n"),
										poiIndex,tchPoiName,curEntry->m_addrCode,pQuickIndex->m_cities[i]);
								}
								if (curEntry->m_teleNumber!=0)
								{
									char telBuffer[256];
									::itoa((curEntry->m_teleNumber&0xffffff),telBuffer,10);
								}
								++ curTidOrder;
							}
							curBlockOrder = nextBlockOrder;
						}
						curGrpOrder = nextGrpOrder;
						curBlockOrder = nextFirstBlockOrder;
					}
					if (curTidOrder!=curWord.m_tids)
					{
						logCtrl.Log(_T("	�����÷ִʵ�poi��Ŀͳ�ƴ���,ʵ�ʵ�Ϊ%d\n"),curTidOrder);
					}
#endif
					//
					::free(curWord.m_dataBuffer);
				}
#if 1
				else
				{
					logCtrl.Log(_T("	��ǰ����=%s�У��ִ�=%s��������,��ȷ��!\n"),tchDistName,tchTermChar);
				}
#endif
			}
		}
		return DT_Success;
	}
	unsigned CQueryDataVerify::InitPoiVerify(UeQuery::IndexType verifyMode,
		CUeQueryImpl *pQueryImpl,CUeIndex *&pVerifyIndex,
		CUeIndex *&pGridIndex,UeBase::CDbgLogger *pLogCtrl)
	{
		if (pQueryImpl->GetIndex(verifyMode,pVerifyIndex)!=SQL_Success || pVerifyIndex==0)
		{
			pLogCtrl->Log(_T("������������ʧ�ܣ������Ƿ���ڼ��������ļ�"));
			return DT_DBErr;
		}
		if (pQueryImpl->ConnectToGeneral()!=SQL_Success)
		{
			pLogCtrl->Log(_T("pois.db�����⣬�������������Ƿ�����°�����"));
			return DT_DBErr;
		}
		if (pVerifyIndex->m_bodyCount!=pQueryImpl->m_generalDesc.m_recordNum)
		{
			//��¼���ݲ�һ��
			pLogCtrl->Log(_T("pois.db�е�recordNum=%d,king.mj�е�bodyCound=%d,���߲���ͬ"),
				pQueryImpl->m_generalDesc.m_recordNum,pVerifyIndex->m_bodyCount);
			return DT_PoiCountErr;
		}
		//�������Ʒ��ʶ���
		pQueryImpl->m_nameTable = pQueryImpl->m_poiNameTable;
		pQueryImpl->GetIndex(IT_Grid,pGridIndex);
		return DT_Success;
	}
	unsigned CQueryDataVerify::VerifyAcronymData(char *pchName,
		const char *pchAcroDataInMJ,unsigned maxAcroInMJSize,
		UeBase::CDbgLogger *pLogCtrl)
	{
		char chAcroInDB[128];
		TCHAR uniName[128];
		{
			CStringBasic::Get().Ascii2Chs(pchName,uniName,128);
			CStringBasic::Get().GetAcronym(uniName,chAcroInDB);
			CStringBasic::Get().clearStringSign(chAcroInDB);
			//pLogCtrl->Log(_T("%s\n"),uniName);
		}
		//��acronym.mj�еĵõ�ƴ������ĸ
		char chAcroInMJ[128] = {};
		::strncpy(chAcroInMJ,pchAcroDataInMJ,maxAcroInMJSize);
		//�Ƚ�ƴ������ĸ����
		unsigned uAcroInMJLen(::strlen(chAcroInMJ));
		unsigned uAcroInDBLen(::strlen(chAcroInDB));
		//
		if (uAcroInDBLen>=maxAcroInMJSize)
		{
			if (uAcroInMJLen!=maxAcroInMJSize)
			{
				TCHAR tchAcroInMJ[128];
				CStringBasic::Get().Ascii2Chs(chAcroInMJ,tchAcroInMJ,128);
				TCHAR tchAcroInDB[128];
				CStringBasic::Get().Ascii2Chs(chAcroInDB,tchAcroInDB,128);
				pLogCtrl->Log(_T("db�е���ƴ��mj�е���ƴ��ͬ,%s:AcroInDB=%s,AcroInMJ=%s\n"),
					uniName,tchAcroInDB,tchAcroInMJ);
				//return DT_RecordDataErr;
			}
		}
		else if (uAcroInDBLen!=uAcroInMJLen)
		{
			TCHAR tchAcroInMJ[128];
			CStringBasic::Get().Ascii2Chs(chAcroInMJ,tchAcroInMJ,128);
			TCHAR tchAcroInDB[128];
			CStringBasic::Get().Ascii2Chs(chAcroInDB,tchAcroInDB,128);
			pLogCtrl->Log(_T("db�е���ƴ��mj�е���ƴ��ͬ,%s:AcroInDB=%s,AcroInMJ=%s\n"),
				uniName,tchAcroInDB,tchAcroInMJ);
			//return DT_RecordDataErr;
		}
		//�ж�ƴ��ǰ10������ĸ�Ƿ���ͬ
		for (int k(0); k<uAcroInMJLen; ++k)
		{
			if (chAcroInDB[k]!=chAcroInMJ[k])
			{
				TCHAR tchAcroInMJ[128];
				CStringBasic::Get().Ascii2Chs(chAcroInMJ,tchAcroInMJ,128);
				TCHAR tchAcroInDB[128];
				CStringBasic::Get().Ascii2Chs(chAcroInDB,tchAcroInDB,128);
				pLogCtrl->Log(_T("db�е���ƴ��mj�е���ƴ��ͬ,%s:AcroInDB=%s,AcroInMJ=%s\n"),
					uniName,tchAcroInDB,tchAcroInMJ);
				break;
				//return DT_RecordDataErr;
			}
		}
		return DT_Success;
	}
}