#ifndef _UEQUERY_PTRIEINDEXCTRL_H
#define _UEQUERY_PTRIEINDEXCTRL_H
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
	class UEQUERY_CLASS CPTrieIndexCtrl
	{
	public:
		struct TPTrieNode;
		//
		CPTrieIndexCtrl(void):m_pIndexHandle(0),
			m_curFileOffset(0),m_pPTrieRoot(0) {};
		//
		unsigned Open(bool bReadMode,
			TermDataMode dataMode,
			defDistCodeType distCount=1);
		bool Close(void);
		//����ĵ���¼������Ӧ�Ľڵ�
		bool InsertTermIndex(TTermInfo **pPreKeyWord,
			defTermPosType count,defDistCodeType distCodeIndex);
		//���������ļ�
		bool OutputTrieIndex(void);
		bool OutputTrieIndex(defDistCodeType distCodeIndex);
		//��ȡһ������֮�����һ���ֵļ���
		void GetNextWord(TTermInfo *pPreKeyWord,
			defTermPosType count,defDistCodeType distCodeIndex,
			std::vector<TPTrieNode *> &vecChildren);
		//
	private:
		struct TPTrieNode
		{
			TPTrieNode(void):m_count(0),
				m_key(-1),m_level(0),m_childFileOffset(0) {};
			//
			virtual ~TPTrieNode(void) {};
			static long GetWRootSize(void)
			{
				long size(0);
				//������һ��ƫ��
				size += sizeof(long);
				//������Ŀ
				size += sizeof(defTermType);
				return size;
			}
			static long GetWNodeSize(void)
			{
				long size(0);
				//����ؼ���
				size += sizeof(defTermType);
				//������ֵĴ���
				//size += sizeof(long);
				//������һ��ƫ��
				size += sizeof(long);
				//������Ŀ
				size += sizeof(defTermType);
				return size;
			}
			//
			TPTrieNode *AddNode(defTermType key,defTermPosType level)
			{
				std::list<TPTrieNode>::iterator iterInfo(m_vecChildren.begin());
				for (; iterInfo!=m_vecChildren.end(); ++iterInfo)
				{
					if (iterInfo->m_key==key)
					{
						if (iterInfo->m_level!=level)
						{
							assert(false);
						}
						return &(*iterInfo);
					}
				}
				//
				TPTrieNode node;
				node.m_key = key;
				node.m_level = level;
				return &(*(m_vecChildren.insert(m_vecChildren.begin(),node)));
			}
			void Sort(void);
			void WriteToFile(void *fileHandle);
			void WriteChildren(void *fileHandle);
			void WriteRootToFile(void *fileHandle);
			bool operator < (const TPTrieNode &node2)
			{
				return m_key<node2.m_key;
			}
			unsigned InitChildOffset(defTermPosType level,unsigned curFileOffset);
			//
			//��¼��¼��Ŀ
			unsigned m_count;
			//��ǰ����
			defTermType m_key;
			//
			defTermPosType m_level;
			//�ӽڵ����ļ���ƫ����
			unsigned m_childFileOffset;
			//�뵱ǰ�й�������
			std::list<TPTrieNode> m_vecChildren;
		};
		#pragma pack(1)
		struct TIndexHead
		{
			TIndexHead(void):m_indexVer(0),m_distCount(0)
			{
				::memcpy(head,DATA_HEAD,sizeof(head));
			}
			//
			char head[16];
			unsigned short m_indexVer;
			defDistCodeType m_distCount;
		};
		#pragma pack()
		tstring GetIndexFileName(TermDataMode dataMode) const;
		//
		void *m_pIndexHandle;
		TIndexHead m_indexHead;
		//��ǰҪд�Ľڵ�λ��
		unsigned m_curFileOffset;
		//���������еĸ�
		TPTrieNode *m_pPTrieRoot;
		//ʵ����ӵ�����Ϊg_maxLevel-1,��Ϊ�и���ͬ�ĸ�
		//�ǲ��ŵ��ֵ�
		static const defTermPosType g_maxLevel=3;
	};
}
#endif