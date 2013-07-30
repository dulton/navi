#ifndef _UEQUERY_DISTINDEX_H
#define _UEQUERY_DISTINDEX_H
//////////////////////////////////////////////////////////////////////////
// Refer to its parent
#ifndef _UEQUERY_UEINDEX_H
#include "ueindex.h"
#endif
// Refer to query basic definition
#ifndef _UEQUERY_QUERYDEF_H
#include "querybasic.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	class CDistIndex:public CUeIndex
	{
	public:
#pragma pack(1)
		//���������ֵ����ݿ�����
		struct TDistEntry
		{
#ifndef USE_NEW_DATA
			TDistEntry(void):m_distCode(0), m_startAcro(0),
				m_acroNum(0), m_startBody(0) {};
#else
			TDistEntry(void):m_distCode(0),m_startAcro(0) {};
#endif
			//�������(ʡ��Ϣ|������Ϣ)
			long m_distCode;
			//���������е�·ƴ����д������ƴ��
			//�����е�����(ע��������,ʵ�ʵó���MAXACROENTRY)��
			//�Լ��õ�·�����еĵ�·��Ϣ��CrossBodyEntry������
			//����ʼ����
			long m_startAcro;
#ifndef USE_NEW_DATA
			//�������µ�·��Ŀ���ж���ƴ����д
			long m_acroNum;
			//ʵ������m_startAcro��ͬ��ʵ���Ͽ���ȥ������Ȼ�����ʡ�ܶ�Ŀռ�
			long m_startBody;
#endif
		};
#pragma pack()
		CDistIndex(void):m_pchAcroEntries(0),
			m_pDistEntries(0) {};
	protected:
		//��ȡ��������
		virtual unsigned GetIdxes(void);
		virtual unsigned GetIdxEntrySize(void) const {return sizeof(*m_pDistEntries);};
		//
		int GetIdxes(unsigned codeMask,int startIdx,int endIdx,bool isGetStart);

		//�����е�ƴ������ĸ
		char *m_pchAcroEntries;
		//������������
		TDistEntry *m_pDistEntries;
	};
}
#endif