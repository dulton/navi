#ifndef _UEQUERY_DISTCODEINDEXCTRL_H
#define _UEQUERY_DISTCODEINDEXCTRL_H
//////////////////////////////////////////////////////////////////////////
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif
#ifndef _UEQUERY_QUERYDEF_H
#include "querybasic.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	enum DistCodeMode
	{
		DM_UNKNOWN,
		DM_POIMODE,
		DM_ROADMODE
	};
	class UEQUERY_CLASS CDistCodeIndexCtrl
	{
	public:
		CDistCodeIndexCtrl(bool bReadMode,DistCodeMode codeMode);
		virtual ~CDistCodeIndexCtrl(void) {Close();};
		//
		virtual unsigned Open(void);
		virtual unsigned Close(void);
		//
		//�����������ڻ��ڶ�ģʽ�·���false
		bool AddDistCode(unsigned distCode);
		//����ǰ��ӵ��������������ļ���ȥ
		bool OutputDistCodeIndex(void);
		//
		//����ģʽ�£�Ҫ�ȵ���OutputDistCodeIndex֮��
		//���ܵ���GetDistCodeIndex
		defDistCodeType GetDistCodeIndex(unsigned distCode) const;
		void GetIndexFileName(tstring &fileName) const;
		//
		defDistCodeType GetDistCount(void) const {return m_indexHead.m_distCount;};
		bool GetSubDistIndex(unsigned fDistCode,defDistCodeType &sStartIdx,defDistCodeType &sEndIdx) const;
		//
		unsigned GetDistCode(defDistCodeType idx) const
		{
			if (m_pDistCode!=0 && idx<m_indexHead.m_distCount)
			{
				return m_pDistCode[idx];
			}
			return -1;
		}
	private:
		#pragma pack(1)
		struct TIndexHead
		{
			TIndexHead(void):m_gridVer(0),m_distCount(0)
			{
				::memcpy(head,DATA_HEAD,sizeof(head));
			}
			char head[16];
			unsigned short m_gridVer;
			defDistCodeType m_distCount;
		};
		#pragma pack()
		int GetSubDistIndex(unsigned fDistCode,unsigned codeMask,
			int startIdx,int endIdx,bool isGetStart) const;

		//���浱ǰ��ģʽ
		bool m_bReadMode;
		DistCodeMode m_codeMode;
		//
		TIndexHead m_indexHead;
		unsigned *m_pDistCode;
		std::set<unsigned> m_vecDistCode;
	};
}
#endif