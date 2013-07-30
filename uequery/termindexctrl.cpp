#ifndef _UEQUERY_TERMINDEXCTRL_H
#include "termindexctrl.h"
#endif
#ifndef _UEQUERY_UERECORD_H
#include "uerecord.h"
#endif
#ifndef _UEQUERY_GRIDINDEXCTRL_H
#include "gridindexctrl.h"
#endif
#ifndef _UEBASE_STRINGBASIC_H
#include "uebase/stringbasic.h"
#endif
#ifndef _UEBASE_PATHBASIC_H
#include "uebase/pathbasic.h"
#endif
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif
#ifndef _UEQUERY_DISTCODEINDEXCTRL_H
#include "distcodeindexctrl.h"
#endif
#ifndef _UEQUERY_GRIDINDEXCTRL_H
#include "gridindexctrl.h"
#endif
#ifndef _UEQUERY_CODEINDEXCTRL_H
#include "codeindexctrl.h"
#endif
#ifndef _UEQUERY_CHWPELLINGCTRL_H
#include "chwpellingctrl.h"
#endif
#include <stdlib.h>
using namespace UeBase;
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	CTermIndexCtrl::CTermIndexCtrl(bool bReadMode,TermDataMode dataMode,
		CDataEntryCtrl *pDataEntryCtrl):CIndexCtrl(bReadMode),m_dataMode(dataMode),
		m_distCount(0),m_pTermsInfo(0),m_startCityIdx(-1),m_endCityIdx(-1),m_curCityIdx(-1),
		m_wordCnt(0),m_queryTermCnt(0),m_pFirstTermReader(0),m_pLastTermReader(0),m_pIndexTmpHandle(0),
		m_pDataEntryCtrl(pDataEntryCtrl),m_recordBufSize(0),m_pDocMathRecord(0),m_comBufCnt(0),
		m_pComCityTermInfo(0),m_bAcroData(false)
	{
#ifdef CREATE_PTIRE_DATA
		m_pPTrieIndexCtrl = 0;
#endif
		::memset(m_pCurRecordTerm,0,sizeof(m_pCurRecordTerm));
		::memset(m_pQueryTermInfo,0,sizeof(m_pQueryTermInfo));
		//
		if (m_pDataEntryCtrl!=0)
		{
			m_distCount = m_pDataEntryCtrl->GetDistCount();
		}
		//
		if (TM_POIACRO==m_dataMode
			|| TM_ROADACRO==m_dataMode
			|| TM_CITYACRO==m_dataMode)
		{
			m_bAcroData = true;
		}
	}
	CTermIndexCtrl::~CTermIndexCtrl(void)
	{
		Close();
	}
	unsigned CTermIndexCtrl::Open(void)
	{
		if (m_pDataFileHandle!=0)
			return SQL_Success;
		//
		tstring tstrIndexFile;
		CGridIndexCtrl::GetDataPath(tstrIndexFile);
		tstrIndexFile += GetIndexFileName();
		const CFileBasic &fileBasic(CFileBasic::Get());
		if (m_bReadMode)
		{
			//�ж��ļ��Ƿ����
			const CPathBasic &pathBasic(CPathBasic::Get());
			if (!pathBasic.IsFileExist(tstrIndexFile))
				return SQL_NotSpecifyIndex;
			//�жϾ���Ƿ���Ч
			m_pDataFileHandle = fileBasic.OpenFile(tstrIndexFile,CFileBasic::UE_FILE_READ);
			if(!fileBasic.IsValidHandle(m_pDataFileHandle))
				return SQL_InvalidIndex;
			//��ȡ�ִ���Ŀ
			int count(1);
			void *pPtr(&m_indexHead);
			fileBasic.ReadFile(m_pDataFileHandle,(void **)&pPtr,sizeof(m_indexHead),count);
			//
			long bufSize(m_indexHead.m_termCount*sizeof(TTermOffsetInfo));
			m_pTermsInfo = static_cast<TTermOffsetInfo *>(::malloc(bufSize));
			fileBasic.ReadFile(m_pDataFileHandle,(void **)&m_pTermsInfo,bufSize,count);
		}
		else
		{
			//�жϾ���Ƿ���Ч
			m_pDataFileHandle = fileBasic.OpenFile(tstrIndexFile,CFileBasic::UE_FILE_WRITE);
			if(!fileBasic.IsValidHandle(m_pDataFileHandle))
				return SQL_InvalidIndex;
			//������ʱ�ļ�
			tstrIndexFile += _T("tmp");
			m_pIndexTmpHandle = fileBasic.OpenFile(tstrIndexFile,CFileBasic::UE_FILE_WRITE);
			if(!fileBasic.IsValidHandle(m_pIndexTmpHandle))
				return SQL_InvalidIndex;
			fileBasic.WriteFile(m_pIndexTmpHandle,&m_indexHead,sizeof(m_indexHead),1);
		}
		return SQL_Success;
	}
	unsigned CTermIndexCtrl::Close(void)
	{
		defWTermList::iterator iterTermInfo(m_wTermsInfo.begin());
		for (; iterTermInfo!=m_wTermsInfo.end(); ++iterTermInfo)
		{
			TWTermIndex *pTermIndex(iterTermInfo->second);
			defCityTermList::iterator iterCityTerm(pTermIndex->m_pCityTermList->begin());
			for (; iterCityTerm!=pTermIndex->m_pCityTermList->end(); ++iterCityTerm)
			{
				delete iterCityTerm->second;
			}
			delete pTermIndex->m_pCityTermList;
			delete pTermIndex;
		}
		m_wTermsInfo.clear();
		//
		for (int i(0); i<TTermInfo::g_maxTermNum; ++i)
		{
			if (m_pQueryTermInfo[i]!=0)
			{
				delete m_pQueryTermInfo[i]->m_pTermDataCtrl;
				delete m_pQueryTermInfo[i];
				m_pQueryTermInfo[i] = 0;
			}
		}
		//
		const CFileBasic &fileBasic(CFileBasic::Get());
		//���ȹر�֮ǰ�򿪵��ļ�
		if (m_pDataFileHandle!=0)
		{
			fileBasic.CloseFile(m_pDataFileHandle);
			m_pDataFileHandle = 0;
		}
		if (m_pIndexTmpHandle!=0)
		{
			fileBasic.CloseFile(m_pIndexTmpHandle);
			m_pIndexTmpHandle = 0;
		}
		if (m_pTermsInfo!=0)
		{
			::free(m_pTermsInfo);
			m_pTermsInfo = 0;
		}
		if (m_pDocMathRecord!=0)
		{
			m_recordBufSize = 0;
			::free(m_pDocMathRecord);
			m_pDocMathRecord = 0;
		}
		if (m_pComCityTermInfo!=0)
		{
			m_comBufCnt = 0;
			::free(m_pComCityTermInfo);
			m_pComCityTermInfo = 0;
		}
#ifdef CREATE_PTIRE_DATA
		if (m_pPTrieIndexCtrl!=0)
		{
			m_pPTrieIndexCtrl->Close();
			delete m_pPTrieIndexCtrl;
			m_pPTrieIndexCtrl = 0;
		}
#endif
		return SQL_Success;
	}
	bool CTermIndexCtrl::CreateTermIndex(TermDataMode dataMode,CDataEntryCtrl *pDataEntryCtrl)
	{
		if (pDataEntryCtrl==0
			|| pDataEntryCtrl->Open()!=SQL_Success)
			return false;
		//������������ƴ���ִ����ݿ��ƶ���
		CTermIndexCtrl *pNameTermIndex(0),
			*pAcroTermIndex(0);
		//
		switch (dataMode)
		{
		case TM_POINAME:
		case TM_POIACRO:
			pNameTermIndex = new CTermIndexCtrl(false,TM_POINAME,pDataEntryCtrl);
			pAcroTermIndex = new CTermIndexCtrl(false,TM_POIACRO,pDataEntryCtrl);
			break;
		case TM_ROADNAME:
		case TM_ROADACRO:
			pNameTermIndex = new CTermIndexCtrl(false,TM_ROADNAME,pDataEntryCtrl);
			pAcroTermIndex = new CTermIndexCtrl(false,TM_ROADACRO,pDataEntryCtrl);
			break;
		case TM_CITYNAME:
		case TM_CITYACRO:
			pNameTermIndex = new CTermIndexCtrl(false,TM_CITYNAME,pDataEntryCtrl);
			pAcroTermIndex = new CTermIndexCtrl(false,TM_CITYACRO,pDataEntryCtrl);
			break;
		default:
			return false;
		}
		if (pNameTermIndex==0)
		{
			delete pAcroTermIndex;
			return false;
		}
		if (pAcroTermIndex==0)
		{
			delete pNameTermIndex;
			return false;
		}
#ifdef CREATE_PTIRE_DATA
		pNameTermIndex->m_pPTrieIndexCtrl = new CPTrieIndexCtrl;
		if (pNameTermIndex->m_pPTrieIndexCtrl==0)
		{
			delete pAcroTermIndex;
			delete pNameTermIndex;
			return false;
		}
#endif
		pAcroTermIndex->Open();
		pNameTermIndex->Open();
		//
#ifdef CREATE_PTIRE_DATA
		pNameTermIndex->m_pPTrieIndexCtrl->Open(false,
			dataMode,pDataEntryCtrl->GetDistCount());
#endif
		//
		SQLRecord *oneRecord(0);
		defDistDocList docRecordList;
		defDistDocList::iterator iterCity;
		for (long i(0); i<pDataEntryCtrl->GetDataCount(); ++i)
		{
			if (oneRecord = pDataEntryCtrl->FixRecord(i))
			{
				iterCity = docRecordList.find(oneRecord->m_addrCode);
				if (iterCity!=docRecordList.end())
				{
					iterCity->second.push_back(i);
				}
				else
				{
					std::vector<long> tempRecord;
					tempRecord.push_back(i);
					docRecordList[oneRecord->m_addrCode] = tempRecord;
				}
				//
				::free(oneRecord->m_uniName);
				::free(oneRecord->m_asciiName);
				::free(oneRecord->m_pchTelStr);
				::free(oneRecord->m_pchAddrStr);
				::free(oneRecord);
			}
		}
		long acroCnt(0);
		vector<string> vecAcroStr;
		const CStringBasic &stringBasic(CStringBasic::Get());
		//���м�����������ڵ����е�poi
		for (iterCity=docRecordList.begin(); iterCity!=docRecordList.end(); ++iterCity)
		{
			for (std::vector<long>::iterator iterDoc(iterCity->second.begin());
				iterDoc!=iterCity->second.end(); ++iterDoc)
			{
				if (oneRecord = pDataEntryCtrl->FixRecord(*iterDoc))
				{
					vecAcroStr.clear();
					char *pchTempStr(oneRecord->m_uniName);
					//
					bool bTest(false);
					CChWSpellingCtrl::GetChWSpellCtrl().GetAcronym(pchTempStr,vecAcroStr);
					for (long k(0); k<vecAcroStr.size(); ++k)
					{
						pAcroTermIndex->InsertTermIndex(*iterDoc,vecAcroStr[k].c_str(),
							oneRecord->m_addrCode);
						//
						if (!bTest && vecAcroStr[k].find('_')!=string::npos)
						{
							bTest = true;
							TCHAR tchAcro[256],tchName[256];
							stringBasic.Ascii2Chs(pchTempStr,tchName,256);
							stringBasic.Ascii2Chs(vecAcroStr[k].c_str(),tchAcro,256);
							//
							pDataEntryCtrl->Log(_T("%s %s\n"),tchName,tchAcro);
						}
					}
					pNameTermIndex->InsertTermIndex(*iterDoc,pchTempStr,oneRecord->m_addrCode);
					//
					::free(oneRecord->m_uniName);
					::free(oneRecord->m_asciiName);
					::free(oneRecord->m_pchTelStr);
					::free(oneRecord->m_pchAddrStr);
					::free(oneRecord);
				}
			}
#ifdef CREATE_PTIRE_DATA
			pNameTermIndex->m_pPTrieIndexCtrl->OutputTrieIndex(iterCity->first);
#endif
		}
		pNameTermIndex->OutputTermIndex();
		pAcroTermIndex->OutputTermIndex();
		//
		delete pNameTermIndex;
		delete pAcroTermIndex;
		return true;
	}
	bool CTermIndexCtrl::InsertTermIndex(defDBIdxType dbIdx,const char *pchTermSrc,defDistCodeType distCodeIndex)
	{
		//ͳ�Ƶ�ǰ����Դ�и������ֵ���Ϣ
		GetTermsInfo(pchTermSrc);
		//���ɸ����ִʵ�����ʱ�ļ��еĴ������
		for (int i(0); i<m_queryTermCnt; ++i)
		{
			AddTermData(dbIdx,*m_pQueryTermInfo[i],distCodeIndex);
		}
#ifdef CREATE_PTIRE_DATA
		if (m_pPTrieIndexCtrl!=0)
		{
			m_pPTrieIndexCtrl->InsertTermIndex(static_cast<TTermInfo **>(&m_pCurRecordTerm[0]),
				m_wordCnt,distCodeIndex);
		}
#endif
		return true;
	}
	bool CTermIndexCtrl::OutputTermIndex(void)
	{
		//
		//���ڴ��еķִ���Ϣȫ��д����ʱ�ļ�
		const CFileBasic &fileBasic(CFileBasic::Get());
		WriteAllMemTermToTmp();
		fileBasic.CloseFile(m_pIndexTmpHandle);
		//���´���ʱ�ļ�
		tstring tstrIndexFile;
		CGridIndexCtrl::GetDataPath(tstrIndexFile);
		tstrIndexFile += GetIndexFileName();
		tstrIndexFile += _T("tmp");
		//�ж���ʱ�ļ�����Ƿ���Ч
		m_pIndexTmpHandle = fileBasic.OpenFile(tstrIndexFile,CFileBasic::UE_FILE_READ);
		if(!fileBasic.IsValidHandle(m_pIndexTmpHandle))
			return false;
		//
#ifdef CREATE_PTIRE_DATA
		if (m_pPTrieIndexCtrl!=0)
		{
			m_pPTrieIndexCtrl->OutputTrieIndex();
		}
#endif
		ConvertTmpToIndexfile();
		//
		Close();
		/* ɾ����ʱ�ļ� */
		{
			CPathBasic::Get().RemoveFile(tstrIndexFile);
		}
		return false;
	}
	unsigned CTermIndexCtrl::Predicate(const SQLSentence &sql)
	{
		if (sql.m_addrOne==-1)
			return SQL_InvalidSentence;
		if (sql.m_acronyms[0]==0)
			return SQL_InvalidSentence;
		if (m_pTermsInfo==0 && Open()!=SQL_Success)
			return SQL_InitIndexFailure;
		if (m_pDataEntryCtrl==0 || m_pDataEntryCtrl->Open()!=SQL_Success)
			return SQL_InitIndexFailure;
		//
		m_sql = sql;
		if (!m_pDataEntryCtrl->GetSubDistIndex(sql.m_addrOne,
			m_startCityIdx,m_endCityIdx))
		{
			return SQL_ZeroRecord;
		}
		if (!GetTermsInfo(sql.m_acronyms))
		{
			return SQL_InvalidSentence;
		}
		if (!GetTermOffset())
		{
			return SQL_InvalidSentence;
		}
		if (m_sql.m_kind!=0)
		{
			m_kindMask = 0xf000;
			if (m_sql.m_kind&0x00ff)
			{
				m_kindMask = 0xffff;
			}
			else if (m_sql.m_kind&0x0f00)
			{
				m_kindMask = 0xff00;
			}
		}
		return First();
	}
	bool CTermIndexCtrl::IsExit(void)
	{
		//���浱ǰ�����
		do 
		{
			//��ȡ�����ִ��ڵ�ǰ�����е���ϸ��Ϣ
			if (GetCityTermData())
			{
				do
				{
					//�ж������Ƿ����Ҫ��
					if (m_sql.m_kind!=0)
					{
						if ((m_pDataEntryCtrl->GetKind(m_pFirstTermReader->m_pTermDataCtrl->Doc())&m_kindMask)!=m_sql.m_kind)
							continue;
					}
					//��ʼ�������ִ����ĵ��е�λ����Ϣ���ж��Ƿ�ƥ��,�Լ�ƥ������Ƿ���ڵ�ǰ��С��
					if (m_wordCnt==1 || (InitTermsPosInfo() && IsMatched()))
					{
						return true;
					}
				}while (AdjustTermDoc2());
			}
			++ m_curCityIdx;
		} while (m_endCityIdx>=m_curCityIdx);
		return false;
	}
	void CTermIndexCtrl::GetFilterNextWord(std::vector<defDistCodeType> &vecExitCity)
	{
		//���浱ǰ�����
		long newQueryTermIdx(0);
		long oldQueryTermCnt(m_queryTermCnt);
		std::list<TFilterInfo *> vecFilterInfo;
		unsigned short *pFilterNextWord(m_sql.m_pFilterNextWord);
		for (defTermType i(0); i<m_sql.m_numOfWantTo; ++i,--m_wordCnt)
		{
			if ((newQueryTermIdx=AddTermInfo(pFilterNextWord[i],
				m_wordCnt))>=oldQueryTermCnt)
			{
				-- m_queryTermCnt;
				if (!GetTermOffset(m_pQueryTermInfo[newQueryTermIdx]))
				{
					continue;
				}
			}
			TFilterInfo *pFilterInfo(reinterpret_cast<TFilterInfo *>(::malloc(sizeof(TFilterInfo))));
			pFilterInfo->m_idx = i;
			pFilterInfo->m_code = pFilterNextWord[i];
			pFilterInfo->m_termIdx = newQueryTermIdx;
			pFilterInfo->m_offset = m_pQueryTermInfo[newQueryTermIdx]->m_offset;
			vecFilterInfo.push_back(pFilterInfo);
		}
		++ m_wordCnt;
		std::list<TFilterInfo *>::iterator iterFilter;
		std::vector<defDistCodeType>::iterator iterInfo(vecExitCity.begin());
		for (; iterInfo!=vecExitCity.end() && vecFilterInfo.size(); ++iterInfo)
		{
			m_curCityIdx = *iterInfo;
			for (iterFilter=vecFilterInfo.begin(); iterFilter!=vecFilterInfo.end(); )
			{
				newQueryTermIdx = (*iterFilter)->m_termIdx;
				//
				TQueryTermInfo *pQueryTermInfo(m_pQueryTermInfo[newQueryTermIdx]);
				m_pCurRecordTerm[m_wordCnt-1] = &pQueryTermInfo->m_termInfo;
				//
				if (newQueryTermIdx>=oldQueryTermCnt)
				{
					++ m_queryTermCnt;
					//�ж����ߵı����Ƿ���ͬ
					if (pQueryTermInfo->m_termInfo.m_code!=(*iterFilter)->m_code)
					{
						//����ͬ�Ļ���֮ǰ�ĵ�������ɾ����
						if (pQueryTermInfo->m_pTermDataCtrl!=0)
						{
							delete pQueryTermInfo->m_pTermDataCtrl;
							pQueryTermInfo->m_pTermDataCtrl = 0;
						}
						pQueryTermInfo->m_offset = (*iterFilter)->m_offset;
						pQueryTermInfo->m_termInfo.m_code = (*iterFilter)->m_code;
					}
				}
				bool bFound(false);
				//��ȡ�����ִ��ڵ�ǰ�����е���ϸ��Ϣ
				if (GetCityTermData())
				{
					do
					{
						//�ж������Ƿ����Ҫ��
						if (m_sql.m_kind!=0)
						{
							if ((m_pDataEntryCtrl->GetKind(m_pFirstTermReader->m_pTermDataCtrl->Doc())&m_kindMask)!=m_sql.m_kind)
								continue;
						}
						//��ʼ�������ִ����ĵ��е�λ����Ϣ���ж��Ƿ�ƥ��,�Լ�ƥ������Ƿ���ڵ�ǰ��С��
						if (m_wordCnt==1 || (InitTermsPosInfo() && IsMatched()))
						{
							bFound = true;
							pFilterNextWord[(*iterFilter)->m_idx] = 0;
							break;
						}
					}while (AdjustTermDoc2());
				}
				//
				if (bFound)
				{
					::free(*iterFilter);
					iterFilter = vecFilterInfo.erase(iterFilter);
				}
				else
				{
					++ iterFilter;
				}
				if (newQueryTermIdx>=oldQueryTermCnt)
					-- m_queryTermCnt;
			}
		}
	}
	unsigned CTermIndexCtrl::InitRecordBuf(unsigned maxNumber)
	{
		//������������
		long curRecordBufSize(maxNumber*2);
		if (curRecordBufSize>m_recordBufSize)
		{
			m_recordBufSize = curRecordBufSize;
			//
			long bufSize(m_recordBufSize*sizeof(*m_pDocMathRecord));
			//
			m_pDocMathRecord = static_cast<TDocMathInfo *>(::realloc(m_pDocMathRecord,bufSize));
			if (m_pDocMathRecord==0)
				return SQL_MeetTail;
		}
		return SQL_Success;
	}
	unsigned CTermIndexCtrl::Next(CMemVector &idxes,unsigned maxNumber)
	{
		//�ж��Ƿ���ڸó�������
		if (m_curCityIdx==-1 || m_curCityIdx>m_endCityIdx)
			return SQL_MeetTail;
		if (InitRecordBuf(maxNumber)!=SQL_Success)
			return SQL_MeetTail;
		long lastDocIdx(-1);
		//���ڹ���
		long minMatchScore(0);
		unsigned char maxNameLen(0xff);
		unsigned char maxStartPos(0xff);
		long curRecordBufSize(maxNumber*2);
		//���浱ǰ�����
		unsigned curPoiKind(0);
		unsigned char curNameLen(0);
		unsigned char curStartPos(0);
		long curDocIdx(0),matchIdx(0);
		double curCityScore(0.),curKindScore(0.);
		//�����¸���
		long cmpCnt(0);
		char assiName[256];
		std::map<defTermType,long> vecNextWord;
		//����ĸ���˳���
		bool bEixtCity(false);
		std::vector<defDistCodeType> vecExitCity;
		//���浱ǰ�����������еĽ������
		TDocMathInfo *pTempDocMathEle(m_pDocMathRecord+m_curRecordCnt);
		do 
		{
			//��ȡ�����ִ��ڵ�ǰ�����е���ϸ��Ϣ
			if (GetCityTermData())
			{
				bEixtCity = false;
				//TODO:���ܸ����ϣ��Ȳ����ֳ���
				//����Խ��ǰ����Խ��
				curCityScore = (m_endCityIdx-m_startCityIdx+1)/(m_curCityIdx-m_startCityIdx+1);
				curCityScore += CCodeIndexCtrl::GetDistCodeCtrl().Score(m_pDataEntryCtrl->GetCode(m_curCityIdx));
				do
				{
					curDocIdx = m_pFirstTermReader->m_pTermDataCtrl->Doc();
					//�ж������Ƿ����Ҫ��
					if (m_sql.m_kind!=0
						&& ((curPoiKind=m_pDataEntryCtrl->GetKind(curDocIdx))&m_kindMask)!=m_sql.m_kind)
						continue;
					//�ж��Ƿ�ƥ��,�Լ�ƥ������Ƿ���ڵ�ǰ��С��
					if (InitTermsPosInfo() && IsMatched())
					{
						++ cmpCnt;
						bEixtCity = true;
#ifdef MAKE_NEXTWORD_DATA
						//�жϿ�ʼλ��
						curStartPos = m_termMathInfo[0];
						//��ȡ�¸�������
						if (m_sql.m_pvecNextWord!=0)
						{
							//hnc?????????
							defTermPosType preWordPos(m_termMathInfo[m_wordCnt-1]);
							defTermType nextWord(m_pCurQueryTerm[m_wordCnt-1]->GetNextWord(preWordPos));
							if (nextWord!=0 && nextWord!=0xffff)
							{
								vecNextWord[nextWord] += m_matchScore-curStartPos;
							}
						}
						//���ϴεķ������бȽ�
						if (m_matchScore<minMatchScore)
							continue;
						if (curStartPos>maxStartPos && m_matchScore==minMatchScore)
							continue;
						curNameLen = m_pDataEntryCtrl->GetNameLen(curDocIdx);
						if (curNameLen>=maxNameLen
							&& m_matchScore==minMatchScore
							&& curStartPos==maxStartPos)
							continue;
#else
						//���ϴεķ������бȽ�
						if (m_matchScore<minMatchScore)
							continue;
						//�жϿ�ʼλ��
						curStartPos = m_termMathInfo[0];
						if (curStartPos>maxStartPos && m_matchScore==minMatchScore)
							continue;
						//��֤�����ּ�¼������ּ��ε����
						if (curDocIdx==lastDocIdx)
						{
							if ((pTempDocMathEle-1)->m_matchScore<m_matchScore
								|| ((pTempDocMathEle-1)->m_matchScore==m_matchScore
								&& (pTempDocMathEle-1)->m_startPos>curStartPos))
							{
								-- m_curRecordCnt;
								-- pTempDocMathEle;
							}
							else
							{
								continue;
							}
						}
						lastDocIdx = curDocIdx;
						//
						curNameLen = m_pDataEntryCtrl->GetNameLen(curDocIdx);
						if (curNameLen>=maxNameLen
							&& m_matchScore==minMatchScore
							&& curStartPos==maxStartPos)
							continue;
						//��ȡ�¸�������
						if (m_sql.m_pvecNextWord!=0)
						{
							defTermPosType preWordPos(m_termMathInfo[m_wordCnt-1]);
							m_pDataEntryCtrl->GetEntryName(curDocIdx,curNameLen,assiName);
							defTermType nextWord(GetNextWord(assiName,preWordPos+1));
							//
							if (nextWord!=0 && nextWord!=0xffff)
							{
								vecNextWord[nextWord] += m_matchScore-curStartPos;
							}
						}
#endif
						//
						pTempDocMathEle->m_idx = curDocIdx;
						pTempDocMathEle->m_nameLen = curNameLen;
						pTempDocMathEle->m_startPos = curStartPos;
						pTempDocMathEle->m_cityScore = curCityScore;
#if 0
						//TODO:���ܸ����ϣ��Ȳ����ֳ���
						pTempDocMathEle->m_kindScore = curPoiKind;
#endif
						pTempDocMathEle->m_matchScore = m_matchScore;
						//
						++ m_curRecordCnt;
						++ pTempDocMathEle;
						if (m_curRecordCnt>=curRecordBufSize)
						{
							std::sort(m_pDocMathRecord,pTempDocMathEle,TDocMathInfo::MatchCompare);
							//
							pTempDocMathEle = m_pDocMathRecord+(maxNumber-1);
							//
							maxNameLen = pTempDocMathEle->m_nameLen;
							maxStartPos = pTempDocMathEle->m_startPos;
							minMatchScore = pTempDocMathEle->m_matchScore;
							//
							++ pTempDocMathEle;
							m_curRecordCnt = maxNumber;
						}
					}
				}while (AdjustTermDoc2());
				//
				if (bEixtCity)
				{
					vecExitCity.push_back(m_curCityIdx);
				}
			}
			++ m_curCityIdx;
		} while (m_endCityIdx>=m_curCityIdx);
		//
Test:
		if (m_sql.m_pvecNextWord)
		{
			long memSize(vecNextWord.size()*sizeof(TNextWordFrq));
			TNextWordFrq *pNextWordInfo(reinterpret_cast<TNextWordFrq *>(::malloc(memSize)));
			TNextWordFrq *pEndNextWord(pNextWordInfo);
			//
			std::map<defTermType,long>::iterator iterInfo(vecNextWord.begin());
			for (; iterInfo!=vecNextWord.end(); ++iterInfo,++pEndNextWord)
			{
				pEndNextWord->m_code = iterInfo->first;
				pEndNextWord->m_frq = iterInfo->second;
			}
			::std::sort(pNextWordInfo,pEndNextWord,TNextWordFrq::Compare);
			//
			char chNextWord[3] = {};
			TNextWordFrq *pTempNextWord(pNextWordInfo);
			for (int i(0); i<m_sql.m_numOfWantTo
				&& pTempNextWord!=pEndNextWord; ++i,++pTempNextWord)
			{
				chNextWord[0] = pTempNextWord->m_code;
				chNextWord[1] = pTempNextWord->m_code>>8;
				m_sql.m_pvecNextWord->push_back(chNextWord);
			}
			::free(pNextWordInfo);
		}
		if (m_sql.m_pFilterNextWord && vecExitCity.size())
		{
			GetFilterNextWord(vecExitCity);
		}
		if (m_curRecordCnt!=0)
		{
#if 0
			//TODO:���ܸ����ϣ��Ȳ����ֳ���
			pTempDocMathEle = m_pDocMathRecord;
			for (int i(0); i<curRecordIdx; ++i,++pTempDocMathEle)
			{
				if (m_sql.m_kind==0)
				{
					pTempDocMathEle->m_kindScore = m_pDataEntryCtrl->GetKind(pTempDocMathEle->m_idx);
				}
				pTempDocMathEle->m_kindScore = CCodeIndexCtrl::GetKindCodeCtrl().Score(pTempDocMathEle->m_kindScore);
			}
			::std::sort(m_pDocMathRecord,pTempDocMathEle,TDocMathInfo::Compare3);
#else
			::std::sort(m_pDocMathRecord,pTempDocMathEle,TDocMathInfo::MatchCompare);
#endif
			//
			//���浱ǰ������
			TDocIdxInfo docIdxInfo;
			pTempDocMathEle = m_pDocMathRecord;
			unsigned recordCount(m_curRecordCnt>maxNumber?maxNumber:m_curRecordCnt);
			for (int i(0); i<recordCount; ++i,++pTempDocMathEle)
			{
				docIdxInfo.m_idx = pTempDocMathEle->m_idx;
				idxes.Add(&docIdxInfo);
			}
		}
		return idxes.GetCount()?SQL_Success:SQL_MeetTail;
	}
	void CTermIndexCtrl::GetKeyWordPosInRecord(const char *pchRecordStr,
		const SQLSentence &sql,unsigned char *posBuffer)
	{
		*posBuffer = 0xff;
		vector<string> vecAcroStr;
		const CStringBasic &stringBasic(CStringBasic::Get());
		//
		if (IT_CityAcro==sql.m_indexType
			|| IT_RoadAcro==sql.m_indexType
			|| IT_PoiAcro==sql.m_indexType)
		{
			CChWSpellingCtrl::GetChWSpellCtrl().GetAcronym(pchRecordStr,vecAcroStr);
		}
		else
		{
			vecAcroStr.push_back(pchRecordStr);
		}
		long maxMatchScore(0),minMatchIdx(1000);
		//����pchKeyWord�еĸ�������pchRecordStr���ֵ�λ��
		CTermIndexCtrl keywordCtrl(true,TM_CITYNAME,0);
		keywordCtrl.GetTermsInfo(sql.m_acronyms);
		keywordCtrl.m_sql.m_misses = sql.m_misses;
		//
		CTermIndexCtrl recordStrCtrl(true,TM_CITYNAME,0);
		for (long k(0); k<vecAcroStr.size(); ++k)
		{
			bool bFind(false);
			recordStrCtrl.GetTermsInfo(vecAcroStr[k].c_str());
			for (defTermPosType i(0); i<keywordCtrl.m_queryTermCnt; ++i)
			{
				for (defTermPosType j(0); j<recordStrCtrl.m_queryTermCnt; ++j)
				{
					if (keywordCtrl.m_pQueryTermInfo[i]->m_termInfo.m_code==recordStrCtrl.m_pQueryTermInfo[j]->m_termInfo.m_code)
					{
						bFind = true;
						keywordCtrl.m_pQueryTermInfo[i]->m_termInfo = recordStrCtrl.m_pQueryTermInfo[j]->m_termInfo;
						break;
					}
				}
				if (!bFind)
					break;
			}
			if (!bFind)
				continue;
			//
			if (keywordCtrl.IsMatched())
			{
				if (keywordCtrl.m_matchScore>maxMatchScore
					|| (keywordCtrl.m_matchScore==maxMatchScore
					&& keywordCtrl.m_termMathInfo[0]<minMatchIdx))
				{
					maxMatchScore = keywordCtrl.m_matchScore;
					minMatchIdx = keywordCtrl.m_termMathInfo[0];
					//
					for (defTermPosType i(0); i<keywordCtrl.m_wordCnt; ++i)
					{
						posBuffer[i] = keywordCtrl.m_termMathInfo[i];
					}
					posBuffer[keywordCtrl.m_wordCnt] = 0xff;
				}
			}
		}
	}
	CTermIndexCtrl::CTermDataReader::CTermDataReader(const unsigned char *pSrcData,
		bool bAcroData):m_pSrcData(pSrcData),m_bAcroData(bAcroData),m_pDataCursor(pSrcData),
		m_curGrpStartIdx(0),m_curBlockStartIdx(0),m_pCurDocPosData(0),m_curTermPosCnt(0),
		m_curDocIndex(-1)
	{
	}
	CTermIndexCtrl::CTermDataReader::~CTermDataReader(void)
	{
		if (m_pSrcData!=0)
		{
			::free(const_cast<unsigned char *>(m_pSrcData));
			m_pSrcData = 0;
		}
	}
	bool CTermIndexCtrl::CTermDataReader::First(void)
	{
		if (m_pSrcData==0)
			return false;
		//
		m_pDataCursor = m_pSrcData;
		//
		m_curGrpStartIdx = (*m_pDataCursor)*g_maxGrpCount;
		++ m_pDataCursor;
		m_curBlockStartIdx = (*m_pDataCursor)*g_maxBlockCount;
		++ m_pDataCursor;
		return true;
	}
	bool CTermIndexCtrl::CTermDataReader::NextDoc(void)
	{
		unsigned char order(0);
		while (1)
		{
			if ((order=*m_pDataCursor)!=0xff)
			{
				//�����ڵ�ǰ�ĵ��е�������Ϣ
				m_pCurDocPosData = ++m_pDataCursor;
				//��ȡ�ִʵ�λ����Ϣ
				m_curTermPosCnt = 0;
				for (unsigned char posTemp(0),curPos(0); ; ++curPos)
				{
					if ((posTemp=(m_pDataCursor[curPos]>>5))==0)
					{
						break;
					}
					m_curTermPosCnt += posTemp;
					if (posTemp<7)
						break;
				}
				m_pDataCursor += m_curTermPosCnt;
#ifdef MAKE_NEXTWORD_DATA
				if (!m_bAcroData)
				{
					m_pDataCursor += m_curTermPosCnt*sizeof(defTermType);
				}
#endif
				m_curDocIndex = order+m_curGrpStartIdx+m_curBlockStartIdx;
				return true;
			}
			else if ((order=*(++m_pDataCursor))!=0xff)
			{
				++ m_pDataCursor;
				m_curBlockStartIdx = order*g_maxBlockCount;
			}
			else if ((order=*(++m_pDataCursor))!=0xff)
			{
				m_curGrpStartIdx = order*g_maxGrpCount;
				m_curBlockStartIdx = (*(++m_pDataCursor))*g_maxBlockCount;
				++ m_pDataCursor;
			}
			else
			{
				return false;
			}
		}
	}
	defTermType CTermIndexCtrl::CTermDataReader::GetNextWord(defTermPosType preWordIdx)
	{
#ifdef MAKE_NEXTWORD_DATA
		if (preWordIdx<m_curTermPosCnt)
		{
			const defTermType *pNextWord(reinterpret_cast<const defTermType *>(m_pCurDocPosData+m_curTermPosCnt));
			return pNextWord[preWordIdx];
		}
#endif
		return 0xffff;
	}
	bool CTermIndexCtrl::CTermDataReader::InitTermInfo(TTermInfo &term,
		defTermPosType offset)
	{
		term.m_frq = 0;
		for (defTermPosType i(0),pos(0); i<m_curTermPosCnt; ++i)
		{
			if ((pos=m_pCurDocPosData[i]&0x1f)>=offset)
			{
				term.m_pos[term.m_frq] = pos;
				++ term.m_frq;
			}
		}
		term.m_idx = 0;
		return term.m_frq;
	}
	defTermType CTermIndexCtrl::TQueryTermInfo::GetNextWord(defTermPosType preWordPos)
	{
		for (defTermPosType i(0); i<m_termInfo.m_frq; ++i)
		{
			if (preWordPos==m_termInfo.m_pos[i])
			{
				return m_pTermDataCtrl->GetNextWord(i);
			}
		}
		return 0xffff;
	}
	void CTermIndexCtrl::WriteAllMemTermToTmp(void)
	{
		TCityTermInfo initData;
		const CFileBasic &fileBasic(CFileBasic::Get());
		defWTermList::iterator iterTermInfo(m_wTermsInfo.begin());
		for (; iterTermInfo!=m_wTermsInfo.end(); ++iterTermInfo)
		{
			//��ȡ��ǰ�ļ�д��������
			defDataOffsetType offset(0);
			//
			TWTermIndex *pTermIndex(iterTermInfo->second);
			//�ж��Ƿ�����˳����б�
			if (pTermIndex->m_fileOffset==0)
			{
				//��¼���Ӧ�ĳ����б�ƫ��
				pTermIndex->m_fileOffset = fileBasic.TellFilePos(m_pIndexTmpHandle);
				//Ԥ���ռ䣬�ȴ��Ժ�����
				fileBasic.SeekFile(m_pIndexTmpHandle,sizeof(initData.m_curLinkPos)*m_distCount,CFileBasic::UE_SEEK_CUR);
			}
			defCityTermList::iterator iterCityTerm(pTermIndex->m_pCityTermList->begin());
			for (; iterCityTerm!=pTermIndex->m_pCityTermList->end(); ++iterCityTerm)
			{
				TCityTermInfo *pCityTermInfo(iterCityTerm->second);
				if (pCityTermInfo->m_curTermCnt==0
					|| pCityTermInfo->m_curRecordCnt==0)
				{
					continue;
				}
				//
				if (pCityTermInfo->m_curLinkPos==0)
				{
					pCityTermInfo->m_curLinkPos = pTermIndex->m_fileOffset+sizeof(initData.m_curLinkPos)*iterCityTerm->first;
				}
				offset = fileBasic.TellFilePos(m_pIndexTmpHandle);
				//��λ����һ������ƫ�Ƽ�¼������¼��ǰ���ݵ�ƫ��
				fileBasic.SeekFile(m_pIndexTmpHandle,pCityTermInfo->m_curLinkPos,CFileBasic::UE_SEEK_BEGIN);
				fileBasic.WriteFile(m_pIndexTmpHandle,&offset,sizeof(offset),1);
				//
				fileBasic.SeekFile(m_pIndexTmpHandle,offset,CFileBasic::UE_SEEK_BEGIN);
				fileBasic.WriteFile(m_pIndexTmpHandle,&pCityTermInfo->m_curTermCnt,sizeof(pCityTermInfo->m_curTermCnt),1);
				fileBasic.WriteFile(m_pIndexTmpHandle,&pCityTermInfo->m_curRecordCnt,sizeof(pCityTermInfo->m_curRecordCnt),1);
				//Ԥ��
				pCityTermInfo->m_curLinkPos = 0;
				fileBasic.WriteFile(m_pIndexTmpHandle,&pCityTermInfo->m_curLinkPos,sizeof(pCityTermInfo->m_curLinkPos),1);
				pCityTermInfo->m_curLinkPos = offset+sizeof(pCityTermInfo->m_curTermCnt)+sizeof(pCityTermInfo->m_curRecordCnt);
				//
				for (TCityTermNode *pTermNode(pCityTermInfo->m_pCurListBeg),*pTempNode(0); pTermNode!=0; )
				{
					fileBasic.WriteFile(m_pIndexTmpHandle,pTermNode->m_pTermData,pTermNode->m_dataLen,1);
					//
					pTempNode = pTermNode;
					pTermNode = pTermNode->m_pNext;
					delete pTempNode;
				}
				//
				pCityTermInfo->m_curTermCnt = 0;
				pCityTermInfo->m_pCurListBeg = 0;
				pCityTermInfo->m_pCurListEnd = 0;
				pCityTermInfo->m_curRecordCnt = 0;
			}
		}
	}
	void CTermIndexCtrl::ConvertTmpToIndexfile(void)
	{
		//������ȡ�ļ�
		int count(1);
		//����ͳ�����ݳ���
		TTermInfo termInfo;
		unsigned total_tid(0);
		//��¼���еķִ���Ŀ
		m_indexHead.m_termCount = m_wTermsInfo.size();
		const CFileBasic &fileBasic(CFileBasic::Get());
		fileBasic.SeekFile(m_pDataFileHandle,0);
		fileBasic.WriteFile(m_pDataFileHandle,&m_indexHead,sizeof(m_indexHead),1);

		//���浱ǰ�ִʵĳ����б�ƫ����Ϣ
		defCityOffsetType cityOffset(0);
		//���浱ǰ�ִ����ļ���λ����Ϣ
		long termOffset(fileBasic.TellFilePos(m_pDataFileHandle));
		//�����ռ���������ִ���Ϣ
		fileBasic.SeekFile(m_pDataFileHandle,m_indexHead.m_termCount*(sizeof(TTermOffsetInfo)),
			CFileBasic::UE_SEEK_CUR);
		//
		bool bCompress(false);
		defDataOffsetType dataOffset(0);
		//
		unsigned char curGrpIdx(0),curBlockIdx(0);
		unsigned char lastGrpIdx(0),lastBlockIdx(0),diff(0);
		//
		defTermPosType posA[TTermInfo::g_maxTermNum];
		//
		defWTermList::iterator iterTermInfo(m_wTermsInfo.begin());
		for (; iterTermInfo!=m_wTermsInfo.end(); ++iterTermInfo)
		{
			//�Ƿ�Ҫѹ��
			bCompress = false;
			//������־�Ƿ�����˳����б�
			cityOffset = 0;
			//
			TWTermIndex *pTermIndex(iterTermInfo->second);
			defCityTermList::iterator iterCityTerm(pTermIndex->m_pCityTermList->begin());
			for (; iterCityTerm!=pTermIndex->m_pCityTermList->end(); ++iterCityTerm)
			{
				void *pPtr(0);
				total_tid = 0;
				bool bFirst(true);
				unsigned uDataLen(0);
				char *pDataBuffer(0),*pDataCursor(0);
				TCityTermInfo *pCityTermInfo(iterCityTerm->second);
				pCityTermInfo->m_curLinkPos = pTermIndex->m_fileOffset+iterCityTerm->first*sizeof(pCityTermInfo->m_curLinkPos);
				//��ȡ�ִ��ڸó��������ݵ��ʼ��ƫ��
				fileBasic.SeekFile(m_pIndexTmpHandle,pCityTermInfo->m_curLinkPos,CFileBasic::UE_SEEK_BEGIN);
				pPtr = &pCityTermInfo->m_curLinkPos;
				fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,sizeof(pCityTermInfo->m_curLinkPos),count);
				//
				while (pCityTermInfo->m_curLinkPos)
				{
					fileBasic.SeekFile(m_pIndexTmpHandle,pCityTermInfo->m_curLinkPos,CFileBasic::UE_SEEK_BEGIN);
					pPtr = &pCityTermInfo->m_curTermCnt;
					fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,sizeof(pCityTermInfo->m_curTermCnt),count);
					pPtr = &pCityTermInfo->m_curRecordCnt;
					fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,sizeof(pCityTermInfo->m_curRecordCnt),count);
					pPtr = &pCityTermInfo->m_curLinkPos;
					fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,sizeof(pCityTermInfo->m_curLinkPos),count);
					//
					unsigned uBlockDataLen(0);
					total_tid += pCityTermInfo->m_curRecordCnt;
					//Ԥ���ĵ�����
					uBlockDataLen = pCityTermInfo->m_curRecordCnt*sizeof(defDBIdxType);
					//
					uBlockDataLen += pCityTermInfo->m_curRecordCnt*sizeof(termInfo.m_frq);
					//Ԥ���ִʵ�λ����Ϣ
#ifndef MAKE_NEXTWORD_DATA
					uBlockDataLen += pCityTermInfo->m_curTermCnt*(sizeof(termInfo.m_pos)/TTermInfo::g_maxTermNum);
#else
					uBlockDataLen += pCityTermInfo->m_curTermCnt*(sizeof(termInfo.m_pos)/TTermInfo::g_maxTermNum+sizeof(termInfo.m_nextWord)/TTermInfo::g_maxTermNum);
#endif
					//
					pDataBuffer = static_cast<char *>(::realloc(pDataBuffer,uDataLen+uBlockDataLen+100));
					pDataCursor = pDataBuffer+uDataLen;
					//
					for (defDBIdxType i(0),docIdx; i<pCityTermInfo->m_curRecordCnt; ++i)
					{
						pPtr = &docIdx;
						fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,sizeof(docIdx),count);
						//�ж��ĵ��������Ƿ񳬳����ܱ�ʾ�ķ�Χ
						if (docIdx>(g_maxBlockCount*g_maxGrpCount))
							break;
						curGrpIdx = docIdx/g_maxGrpCount;
						curBlockIdx = (docIdx%g_maxGrpCount)/g_maxBlockCount;
						diff = (docIdx%g_maxGrpCount)%g_maxBlockCount;
						//
						if (bFirst)
						{
							bFirst = false;
							*pDataCursor++ = lastGrpIdx = curGrpIdx;
							*pDataCursor++ = lastBlockIdx = curBlockIdx;
						}
						else if (curGrpIdx!=lastGrpIdx)
						{
							//��һ��diff������־
							*pDataCursor++ = 0xff;
							//��һ��block������־
							*pDataCursor++ = 0xff;
							//
							*pDataCursor++ = lastGrpIdx = curGrpIdx;
							*pDataCursor++ = lastBlockIdx = curBlockIdx;
						}
						else if (curBlockIdx!=lastBlockIdx)
						{
							//��һ��diff������־
							*pDataCursor++ = 0xff;
							*pDataCursor++ = lastBlockIdx = curBlockIdx;
						}
						*pDataCursor++ = diff;
						//���λ����Ϣ
						pPtr = &termInfo.m_frq;
						fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,sizeof(termInfo.m_frq),count);
						pPtr = termInfo.m_pos;
						fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,termInfo.m_frq*(sizeof(termInfo.m_pos)/TTermInfo::g_maxTermNum),count);
#ifdef MAKE_NEXTWORD_DATA
						pPtr = termInfo.m_nextWord;
						fileBasic.ReadFile(m_pIndexTmpHandle,&pPtr,termInfo.m_frq*(sizeof(termInfo.m_nextWord)/TTermInfo::g_maxTermNum),count);
#endif
						//�����Ƶhnc?????
						//*pDataCursor ++ = termInfo.m_frq;
						//
						for (defTermPosType j(0),posCntCtrl(termInfo.m_frq); j<termInfo.m_frq; ++j,++pDataCursor)
						{
							defTermPosType temp(0);
							if (posCntCtrl>0x07)
							{
								temp = 0x07;
								posCntCtrl -= 0x07;
							}
							else
							{
								temp = posCntCtrl;
								posCntCtrl = 0;
							}
							*pDataCursor = (temp<<5)|termInfo.m_pos[j];
						}
#ifdef MAKE_NEXTWORD_DATA
						if (!m_bAcroData)
						{
							for (defTermPosType j(0); j<termInfo.m_frq; ++j)
							{
								*pDataCursor++ = termInfo.m_nextWord[j];
								*pDataCursor++ = (termInfo.m_nextWord[j]>>8);
							}
						}
#endif
					}
					uDataLen = pDataCursor-pDataBuffer;
				}
				*pDataCursor++ = 0xff;
				*pDataCursor++ = 0xff;
				*pDataCursor++ = 0xff;
				//
				uDataLen = pDataCursor-pDataBuffer;
				//hnc??????
				if (uDataLen>=0xffff)
				{
					char tempStr[3] = {};
					tempStr[0] = iterTermInfo->first;
					tempStr[1] = iterTermInfo->first>>8;
					TCHAR tchTempStr[2] = {};
					const CStringBasic &stringBasic(CStringBasic::Get());
					stringBasic.Ascii2Chs(tempStr,tchTempStr,2);
					m_pDataEntryCtrl->Log(_T("�ִ�:%s,����:%x,�������ݴ�СΪ��%0.2fk\n"),
						tchTempStr,m_pDataEntryCtrl->GetCode(iterCityTerm->first),uDataLen/1024.);
				}
				//�ж��Ƿ�����˳����б�
				if (cityOffset==0)
				{
					//��¼��ǰ��λ��
					cityOffset = fileBasic.TellFilePos(m_pDataFileHandle);
					//�ж��Ƿ�Ҫѹ�����
					long nomarlSize = m_distCount*sizeof(defDataOffsetType);
					defDistCodeType distCount(pTermIndex->m_pCityTermList->size());
					long compressSize = distCount*(sizeof(defDistCodeType)+sizeof(defDataOffsetType))+sizeof(distCount);
					if (bCompress=(nomarlSize>compressSize))
					{
						cityOffset += sizeof(distCount);
						//
						fileBasic.WriteFile(m_pDataFileHandle,&distCount,sizeof(distCount),count);
						fileBasic.SeekFile(m_pDataFileHandle,compressSize-sizeof(distCount),CFileBasic::UE_SEEK_CUR);
					}
					else
					{
						fileBasic.SeekFile(m_pDataFileHandle,nomarlSize,CFileBasic::UE_SEEK_CUR);
					}
				}
				dataOffset = fileBasic.TellFilePos(m_pDataFileHandle);
				if (bCompress)
				{
					//��λ����س��д�
					fileBasic.SeekFile(m_pDataFileHandle,cityOffset,CFileBasic::UE_SEEK_BEGIN);
					fileBasic.WriteFile(m_pDataFileHandle,&iterCityTerm->first,sizeof(iterCityTerm->first),count);
					//
					cityOffset += sizeof(iterCityTerm->first);
					cityOffset += sizeof(dataOffset);
				}
				else
				{
					//��λ����س��д�
					fileBasic.SeekFile(m_pDataFileHandle,cityOffset+sizeof(dataOffset)*iterCityTerm->first,CFileBasic::UE_SEEK_BEGIN);
				}
				fileBasic.WriteFile(m_pDataFileHandle,&dataOffset,sizeof(dataOffset),count);
				fileBasic.SeekFile(m_pDataFileHandle,dataOffset,CFileBasic::UE_SEEK_BEGIN);
#if 0 //TODO:��ʱ����
				//TODO:����������������£����ܱ�ʾ���£�����÷ִ��ڵ�ǰ�����г��ֵĴ���
				fileBasic.WriteFile(m_pDataFileHandle,&total_tid,3,count);
#endif
				//����÷ִ��ڵ�ǰ�����е���ϸ��Ϣ�����ݴ�С
				fileBasic.WriteFile(m_pDataFileHandle,&uDataLen,3,count);
				//add by gds 2008.12.05 for compress test
				//�������ļ�������÷ִ��ڵ�ǰ�������ϸ��Ϣ
				fileBasic.WriteFile(m_pDataFileHandle,pDataBuffer,uDataLen,count);
				free(pDataBuffer);
			}
			//��¼��ǰ�ķִ���Ϣ
			fileBasic.SeekFile(m_pDataFileHandle,termOffset,CFileBasic::UE_SEEK_BEGIN);
			//
			TTermOffsetInfo outputTermInfo;
			outputTermInfo.m_code = iterTermInfo->first;
			fileBasic.WriteFile(m_pDataFileHandle,&outputTermInfo.m_code,sizeof(outputTermInfo.m_code),count);
			if (bCompress)
			{
				defDistCodeType distCount(pTermIndex->m_pCityTermList->size());
				cityOffset -= distCount*(sizeof(defDistCodeType)+sizeof(defDataOffsetType))+sizeof(distCount);
				cityOffset |= 0x80000000;
			}
			fileBasic.WriteFile(m_pDataFileHandle,&cityOffset,sizeof(cityOffset),count);
			//
			termOffset += sizeof(outputTermInfo);
			//
			fileBasic.SeekFile(m_pDataFileHandle,0,CFileBasic::UE_SEEK_END);
		}
	}
	tstring CTermIndexCtrl::GetIndexFileName(void) const
	{
		switch (m_dataMode)
		{
		case TM_POINAME:
			return _T("poinameterm.mj");
		case TM_POIACRO:
			return _T("poiacroterm.mj");
		case TM_ROADNAME:
			return _T("roadnameterm.mj");
		case TM_ROADACRO:
			return _T("roadacroterm.mj");
		case TM_CITYNAME:
			return _T("citynameterm.mj");
		case TM_CITYACRO:
			return _T("cityacroterm.mj");
		default:
			return _T("");
		}
	}
	bool CTermIndexCtrl::GetTermsInfo(const char *pchTermSrc)
	{
		m_wordCnt = 0;
		defTermType code;
		m_queryTermCnt = 0;
		//
		char chTermStr[10] = {};
		for (unsigned char pos(0); *pchTermSrc && pos<g_maxWordPosCnt; ++pos)
		{
			if (CChWSpellingCtrl::GetChWSpellCtrl().AdjustSingleWord(pchTermSrc,chTermStr))
			{
				::memcpy(&code,chTermStr,sizeof(code));
				AddTermInfo(code,pos);
			}
			pchTermSrc += pchTermSrc[0]>0?1:2;
		}
		return (m_queryTermCnt!=0);
	}
	defTermType CTermIndexCtrl::GetNextWord(const char *pchTermSrc,
		unsigned char seekWordPos)
	{
		char chTempStr[3] = {};
		for (unsigned char pos(0); *pchTermSrc; ++pos)
		{
			if (CChWSpellingCtrl::GetChWSpellCtrl().AdjustSingleWord(pchTermSrc,chTempStr))
			{
				if (pos>=seekWordPos)
				{
					unsigned char tempChr(chTempStr[0]);
					defTermType code(tempChr);
					tempChr = chTempStr[1];
					code |= (tempChr<<8);
					return code;
				}
			}
			pchTermSrc += pchTermSrc[0]>0?1:2;
		}
		return -1;
	}
	long CTermIndexCtrl::AddTermInfo(defTermType code,short pos)
	{
#ifdef MAKE_NEXTWORD_DATA
		if (m_wordCnt!=0)
		{
			TTermInfo *pTermInfo(m_pCurRecordTerm[m_wordCnt-1]);
			pTermInfo->m_nextWord[pTermInfo->m_frq-1] = code;
		}
#endif
		TQueryTermInfo *pQueryTermInfo(0);
		for (defTermPosType i(0); i<m_queryTermCnt; ++i)
		{
			pQueryTermInfo = m_pQueryTermInfo[i];
			if (pQueryTermInfo->m_termInfo.m_code==code)
			{
				pQueryTermInfo->m_termInfo.m_pos[pQueryTermInfo->m_termInfo.m_frq] = pos;
				++ pQueryTermInfo->m_termInfo.m_frq;
				//
				m_pCurQueryTerm[m_wordCnt] = pQueryTermInfo;
				m_pCurRecordTerm[m_wordCnt] = &pQueryTermInfo->m_termInfo;
				++ m_wordCnt;
				return i;
			}
		}
		if ((pQueryTermInfo=m_pQueryTermInfo[m_queryTermCnt])==0)
		{
			pQueryTermInfo = new TQueryTermInfo;
			m_pQueryTermInfo[m_queryTermCnt] = pQueryTermInfo;
		}
		else
		{
			//�ж����ߵı����Ƿ���ͬ
			if (pQueryTermInfo->m_termInfo.m_code!=code)
			{
				//����ͬ�Ļ���֮ǰ�ĵ�������ɾ����
				if (pQueryTermInfo->m_pTermDataCtrl!=0)
				{
					delete pQueryTermInfo->m_pTermDataCtrl;
				}
				//����������Ϣ
				::memset(pQueryTermInfo,0,sizeof(*pQueryTermInfo));
			}
		}
		pQueryTermInfo->m_termInfo.m_code = code;
		pQueryTermInfo->m_termInfo.m_frq = 1;
		pQueryTermInfo->m_termInfo.m_pos[0] = pos;
		//
		m_pCurQueryTerm[m_wordCnt] = pQueryTermInfo;
		m_pCurRecordTerm[m_wordCnt] = &pQueryTermInfo->m_termInfo;
		//
		++ m_wordCnt;
		++ m_queryTermCnt;
		//
		return m_queryTermCnt-1;
	}
	void CTermIndexCtrl::AddTermData(defDBIdxType dbIdx,
		const TQueryTermInfo &termData,defDistCodeType distCodeIndex)
	{
		if (m_bAcroData)
		{
			//ȥ����ʱ���õ��ַ�
			if ((termData.m_termInfo.m_code>=_T('0')
				&& termData.m_termInfo.m_code<=_T('9'))
				|| termData.m_termInfo.m_code==_T('i')
				|| termData.m_termInfo.m_code==_T('v')
				|| termData.m_termInfo.m_code==_T('u'))
				return;
		}
		if (m_indexHead.m_termCount>=g_maxMemTermCount)
		{
			WriteAllMemTermToTmp();
			m_indexHead.m_termCount = 0;
		}
		//
		++ m_indexHead.m_termCount;
		long posBufSize((sizeof(termData.m_termInfo.m_pos)/TTermInfo::g_maxTermNum)*termData.m_termInfo.m_frq);
#ifdef MAKE_NEXTWORD_DATA
		long nextWordBufSize((sizeof(termData.m_termInfo.m_nextWord)/TTermInfo::g_maxTermNum)*termData.m_termInfo.m_frq);
#endif
		//
		TCityTermNode *pTermNoe = new TCityTermNode;
#ifndef MAKE_NEXTWORD_DATA
		pTermNoe->m_dataLen = sizeof(dbIdx)/*���dbIdx*/+sizeof(termData.m_termInfo.m_frq)+posBufSize;
#else
		pTermNoe->m_dataLen = sizeof(dbIdx)/*���dbIdx*/+sizeof(termData.m_termInfo.m_frq)+posBufSize+nextWordBufSize;
#endif
		pTermNoe->m_pTermData = static_cast<char *>(::malloc(pTermNoe->m_dataLen));
		//
		::memcpy(pTermNoe->m_pTermData,&dbIdx,sizeof(dbIdx));
		long offset(sizeof(dbIdx));
		::memcpy(pTermNoe->m_pTermData+offset,&termData.m_termInfo.m_frq,sizeof(termData.m_termInfo.m_frq));
		offset += sizeof(termData.m_termInfo.m_frq);
		::memcpy(pTermNoe->m_pTermData+offset,termData.m_termInfo.m_pos,posBufSize);
#ifdef MAKE_NEXTWORD_DATA
		offset += posBufSize;
		::memcpy(pTermNoe->m_pTermData+offset,termData.m_termInfo.m_nextWord,nextWordBufSize);
#endif
		//�鿴�Ƿ��и÷ִ���Ϣ
		TCityTermInfo *pCityTermInfo(0);
		defWTermList::iterator iterTermInfo(m_wTermsInfo.find(termData.m_termInfo.m_code));
		if (iterTermInfo!=m_wTermsInfo.end())
		{
			defCityTermList *pCityTermList(iterTermInfo->second->m_pCityTermList);
			//�鿴�Ƿ��иó�����Ϣ
			defCityTermList::iterator iterCityInfo(pCityTermList->find(distCodeIndex));
			if (iterCityInfo!=pCityTermList->end())
			{
				pCityTermInfo = iterCityInfo->second;
			}
			else
			{
				pCityTermInfo = new TCityTermInfo;
				pCityTermList->insert(defCityTermList::value_type(distCodeIndex,pCityTermInfo));
			}
		}
		else
		{
			//
			TWTermIndex *pTermIndex = new TWTermIndex;
			pTermIndex->m_pCityTermList = new defCityTermList;
			//
			pCityTermInfo = new TCityTermInfo;
			pTermIndex->m_pCityTermList->insert(defCityTermList::value_type(distCodeIndex,pCityTermInfo));
			//
			m_wTermsInfo.insert(defWTermList::value_type(termData.m_termInfo.m_code,pTermIndex));
		}
		if (pCityTermInfo->m_pCurListBeg==0)
		{
			pCityTermInfo->m_pCurListBeg = pTermNoe;
			pCityTermInfo->m_pCurListEnd = pTermNoe;
		}
		else
		{
			pCityTermInfo->m_pCurListEnd->m_pNext = pTermNoe;
			pCityTermInfo->m_pCurListEnd = pTermNoe;
		}
		++ pCityTermInfo->m_curRecordCnt;
		pCityTermInfo->m_curTermCnt += termData.m_termInfo.m_frq;
	}
	bool CTermIndexCtrl::GetTermOffset(TQueryTermInfo *pQueryTermInfo)
	{
		//�ж��Ƿ��ϴμ����Ѿ���ȡ����
		if (pQueryTermInfo->m_offset!=0)
			return true;
		//
		defTermType code(pQueryTermInfo->m_termInfo.m_code);
		long low(0),high(m_indexHead.m_termCount-1),mid(0),cmp(0);
		//
		while (low<=high)
		{
			mid = (low+high)>>1;
			cmp = m_pTermsInfo[mid].m_code-code;
			if (cmp==0)
			{
				pQueryTermInfo->m_offset = m_pTermsInfo[mid].m_offset;
				return true;
			}
			else if (cmp>0)
			{
				high = mid-1;
			}
			else
			{
				low = mid+1;
			}
		}
		return false;
	}
	bool CTermIndexCtrl::GetCityTermData(void)
	{
		m_tmpQueryTermCnt = 0;
		for (int i(0); i<m_queryTermCnt; ++i)
		{
			TQueryTermInfo *pQueryTermInfo(m_pQueryTermInfo[i]);
			//��ȡ��ǰ�ķִʵĵ�����Ϣ
			if (!GetCityTermData(pQueryTermInfo))
				return false;
			//����
			if (!pQueryTermInfo->m_pTermDataCtrl->First())
				return false;
			if (!pQueryTermInfo->m_pTermDataCtrl->NextDoc())
				return false;
			++ m_tmpQueryTermCnt;
			m_pTmpQueryTermInfo[i] = pQueryTermInfo;
		}
		//���ĵ��������
		SortQueryTermInfo2();
		//�ж��Ƿ��н���
		if (!AdjustTermDoc())
			return false;
		return true;
	}
	bool CTermIndexCtrl::GetCityTermData(TQueryTermInfo *pQueryTermInfo)
	{
		//�ж�֮ǰ�Ƿ��л�ȡ���õ�����Ϣ
		if (pQueryTermInfo->m_pTermDataCtrl)
		{
			//�жϸõ�����Ϣ�Ƿ��Ӧͬһ����
			if (pQueryTermInfo->m_curCityIdx==m_curCityIdx)
				return true;
			//�жϸõ�����Ϣ�Ƿ��Ӧ��ͬ������,��֮ǰ����Ϣ�ͷŵ�
			delete pQueryTermInfo->m_pTermDataCtrl;
			pQueryTermInfo->m_pTermDataCtrl = 0;
		}
		pQueryTermInfo->m_curCityIdx = m_curCityIdx;
		//
		int count(1);
		const CFileBasic &fileBasic(CFileBasic::Get());
		defDistCodeType distCount,*pDistCount(&distCount);
		//��ȡ��ǰ�����и÷ִ���ϸ��Ϣ���ļ��е�ƫ��
		defDataOffsetType dataOffset(0);
		defCityOffsetType cityOffset(pQueryTermInfo->m_offset);
		//ѹ��ģʽ��
		if (cityOffset&0x80000000)
		{
			fileBasic.SeekFile(m_pDataFileHandle,cityOffset&0x7fffffff);
			fileBasic.ReadFile(m_pDataFileHandle,(void **)&pDistCount,sizeof(*pDistCount),count);
			//�����ڴ�׼����ȡ����
			if (distCount>m_comBufCnt)
			{
				m_comBufCnt = distCount;
				::free(m_pComCityTermInfo);
				m_pComCityTermInfo = static_cast<TComCityTermInfo *>(::malloc(m_comBufCnt*sizeof(TComCityTermInfo)));
			}
			fileBasic.ReadFile(m_pDataFileHandle,(void **)&m_pComCityTermInfo,distCount*sizeof(TComCityTermInfo),count);
			//
			int low(0),high(distCount-1),mid(0),cmp;
			while (low<=high)
			{
				mid = (low+high)>>1;
				cmp = m_pComCityTermInfo[mid].m_distIndex-m_curCityIdx;
				if (cmp==0)
				{
					dataOffset = m_pComCityTermInfo[mid].m_dataOffset;
					break;
				}
				else if (cmp>0)
				{
					high = mid-1;
				}
				else
				{
					low = mid+1;
				}
			}
		}
		else
		{
			defDataOffsetType *pDataOffset(&dataOffset);
			fileBasic.SeekFile(m_pDataFileHandle,cityOffset+m_curCityIdx*sizeof(defDataOffsetType));
			fileBasic.ReadFile(m_pDataFileHandle,(void **)&pDataOffset,sizeof(*pDataOffset),count);
		}
		if (dataOffset!=0)
		{
			//��λ���ִ����ݴ�
			fileBasic.SeekFile(m_pDataFileHandle,dataOffset);
			//��ȡ���ݴ�С
			long dataSize(0);
#if 0 //TODO:��ʱ����
			//��ȡpoi��Ŀ
			void *pPtr(&pQueryTermInfo->m_curRecordCnt);
			fileBasic.ReadFile(m_pDataFileHandle,&pPtr,3,count);
			pPtr = &dataSize;
#else
			void *pPtr = &dataSize;
#endif
			fileBasic.ReadFile(m_pDataFileHandle,&pPtr,3,count);
			//����ռ�׼����ȡ����
			unsigned char *pDataBuffer(static_cast<unsigned char *>(::malloc(dataSize)));
			if (pDataBuffer!=0)
			{
				pPtr = pDataBuffer;
				fileBasic.ReadFile(m_pDataFileHandle,&pPtr,dataSize,count);
				pQueryTermInfo->m_pTermDataCtrl = new CTermDataReader(pDataBuffer,
					m_bAcroData);
				return true;
			}
			else
			{
				m_pDataEntryCtrl->Log(_T("GetCityTermData�е��������ڴ����ʧ��!\n"));
			}
		}
		return false;
	}
	void CTermIndexCtrl::SortQueryTermInfo2(void)
	{
		m_pLastTermReader = 0;
		m_pFirstTermReader = 0;
		//
		TQueryTermInfo *pQueryTermInfo(0);
		std::sort(m_pTmpQueryTermInfo,m_pTmpQueryTermInfo+m_tmpQueryTermCnt,CmpQueryTermInfo);
		//
		for (int i(0); i<m_tmpQueryTermCnt; ++i)
		{
			pQueryTermInfo = m_pTmpQueryTermInfo[i];
			if (m_pLastTermReader!=0)
			{
				m_pLastTermReader->m_pNext = pQueryTermInfo;
			}
			else
			{
				m_pFirstTermReader = pQueryTermInfo;
			}
			m_pLastTermReader = pQueryTermInfo;
			m_pLastTermReader->m_pNext = 0;
		}
	}
	void CTermIndexCtrl::FirstQueryTermToLast(void)
	{
		if (m_pLastTermReader!=0 && m_pFirstTermReader!=0)
		{
			m_pLastTermReader->m_pNext = m_pFirstTermReader;
			m_pLastTermReader = m_pFirstTermReader;
			//
			m_pFirstTermReader = m_pFirstTermReader->m_pNext;
			m_pLastTermReader->m_pNext = 0;
		}
	}
	bool CTermIndexCtrl::IsMatched(void)
	{
		//�жϵ�ǰ�Ƿ�ֻ����һ���ؼ���
		if (m_wordCnt==1)
		{
			m_termMathInfo[0] = m_pCurRecordTerm[0]->Position();
			m_matchScore = MAXMATCHSORCE-m_termMathInfo[0];
			return true;
		}
		m_matchScore = 0;
		//
		bool bIsHave(true);
		long lastMisses(0);
		TTermInfo *pTermInfo1(m_pCurRecordTerm[0]);
		defTermPosType i(0),prePos(0),curPos(0),misses(0);
		long copySize(sizeof(defTermPosType)*m_wordCnt);
		long minMisses(m_wordCnt-2+m_sql.m_misses);
		do 
		{
			bool bTest = false;
			prePos = pTermInfo1->Position();
			m_termMathTemp[0] = prePos;
			for (lastMisses=0,i=1; i<m_wordCnt; )
			{
				TTermInfo *pTermInfo(m_pCurRecordTerm[i]);
				//�ж�ǰ�������ֵľ���
				do 
				{
					curPos = pTermInfo->Position();
					misses = curPos-prePos;
				} while (misses<1 && (bIsHave=pTermInfo->NextPosition()));
				//�ж�����Ƿ��Ѿ�û��λ�ÿ����ж���
				if (!bIsHave)
				{
					break;
				}
				//�ж����߾����Ƿ񳬳������ǵ�������
				if (misses>m_sql.m_misses)
				{
					//���ص���һ��,��������һ��λ��
					if (--i)
					{
						if (bIsHave=m_pCurRecordTerm[i]->NextPosition())
						{
							bTest = true;
							prePos = m_pCurRecordTerm[i-1]->Position();
							continue;
						}
					}
					break;
				}
				//
				prePos = curPos;
				lastMisses += misses;
				//
				m_termMathTemp[i] = curPos;
				++ i;
			}
			//
			if (!bIsHave)
			{
				break;
			}
			if (i>=m_wordCnt && lastMisses<=minMisses)
			{
				//ƥ��ؼ��ּ������Խ�����ԽС
				long tempSorce(MAXMATCHSORCE-lastMisses);
				//
				if (tempSorce>m_matchScore)
				{
					m_matchScore = tempSorce;
					::memcpy(m_termMathInfo,m_termMathTemp,copySize);
				}
			}
		} while (bIsHave && pTermInfo1->NextPosition());
		//
		return m_matchScore;
	}
}