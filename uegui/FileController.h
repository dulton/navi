#ifndef _UEGUI_FILECONTROLLER_H
#define _UEGUI_FILECONTROLLER_H

#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif
// #ifndef _UEBASE_STRINGBASIC_H
// #include "uebase\stringbasic.h"
// #endif
#ifndef _UEBASE_FILEREADER_H
#include "uebase\customerfilereader.h"
#endif
using namespace UeBase;

#ifndef _UEGUI_DATASFORTRUCK_H
#include "datasfortruck.h"
#endif


namespace UeGui
{
	template <class T>
	class CFileController
	{
	public:
		static CFileController<GoodsSource>& getGoodsSourceCtrl()
		{
			static CFileController<GoodsSource> m_SingleGoodsSource(_T("goodssource.db"));
			return m_SingleGoodsSource;
		}
		static CFileController<GoodsSourceDetail>& getGoodsSourceDetailCtrl()
		{
			static CFileController<GoodsSourceDetail> m_SingleGSDetail(_T("sourcedetail.db"));
			return m_SingleGSDetail;
		}
		static CFileController<LogisticsTrackInfo>& getLogisticsTrackCtrl()
		{
			static CFileController<LogisticsTrackInfo> m_SingleLogist(_T("LogisticsTrack.db"));
			return m_SingleLogist;
		}

	public:
		~CFileController(void)
		{
			if (m_pFileReaderCtrl != 0)
			{
				delete m_pFileReaderCtrl;
				m_pFileReaderCtrl = 0;
			}
		}

		//��ʼ���ļ����
		bool InitFileReaderCtrl(void)
		{
			if (m_pFileReaderCtrl==0)
			{
        m_fileName = CPathConfig::GetCommonPath(CPathConfig::CPK_AttrsPath)+m_fileName;
				m_pFileReaderCtrl = new CCustomerFileReader(m_fileName,sizeof(T));
				//����ļ��������򴴽���
				if (!m_pathBasic.IsFileExist(theFile))
				{
					//������Ϊ�ú������ԴﵽЧ����ʹ�ã������Ƴ��������ݵ���˼
					m_pFileReaderCtrl->RemoveAllData(); 
				}
			}
			return (m_pFileReaderCtrl!=0);
		}

		//���ӵ��ļ�
		bool ConnectToFile(void)
		{
			if ( !InitFileReaderCtrl() )
				return false;
			if (m_pFileReaderCtrl->ConnectFile())
				return true;
			return false;
		}

		//�ͷ��ļ�
		bool DisconnectFile(void)
		{
			if ( m_pFileReaderCtrl!=0 && m_pFileReaderCtrl->DisconnectFile() )
			{
				return true;
			}
			return false;
		}

		//��ȡ��¼����Ŀ
		int GetCount(void)
		{
			if (m_pFileReaderCtrl!=0)
			{
				return m_pFileReaderCtrl->GetDataCount();
			}
			return -1;
		}
		//��ȡ����Ϊidx�ļ�¼
		const T* GetOneItem (int idx)
		{
			if (m_pFileReaderCtrl!=0)
			{
				size_t readSize;
				return reinterpret_cast<const T *>(
					m_pFileReaderCtrl->GetBlockData(idx,readSize));
			}
			return 0;
		}
		//���һ����¼
		bool AddOneItem (const T &curItem)
		{
			if (m_pFileReaderCtrl!=0)
			{
				m_pFileReaderCtrl->AddBlockData(
					reinterpret_cast<const char *>(&curItem), CFileBasic::UE_SEEK_END
					);
				return true;
			}
			return false;
		}
		//ɾ������Ϊidx�ļ�¼
		bool RemoveOneItem(int idx)
		{
			if (m_pFileReaderCtrl!=0)
			{
				m_pFileReaderCtrl->RemoveBlockData(idx);
				return true;
			}
			return false;
		}
		//ɾ�����м�¼
// 		bool RemoveAllItem()
// 		{
// 			HANDLE handleWrite;
// 			// ����ԭ�ļ�
// 			handleWrite=::CreateFile(m_fileName.c_str(),GENERIC_WRITE,0,
// 				NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
// 			if (INVALID_HANDLE_VALUE==handleWrite)
// 			{
// 				return false;
// 			}
// 			//�����ļ�
// 			int irealRWSize=0;
// 			int value=0;
// 			SetFilePointer(handleWrite,0,0,FILE_BEGIN);
// 			if ( !(WriteFile(handleWrite,&value,sizeof(int),(LPDWORD)&irealRWSize,NULL)) )
// 			{
// 				CloseHandle(handleWrite);
// 				return false;
// 			}
// 			//�ر��ļ�
// 			CloseHandle(handleWrite);
// 			return true;
// 		}
		//��������Ϊidx�ļ�¼
		bool UpdateOneItem(const T &curItem,int idx)
		{
			if (m_pFileReaderCtrl!=0)
			{
				m_pFileReaderCtrl->EditBlockData(idx,reinterpret_cast<const char *>(&curItem));
				return true;
			}
			return false;
		}


	private:
		CFileController(tstring fileName):m_pathBasic(CPathBasic::Get()), 
			m_fileBasic(CFileBasic::Get()),m_fileName(fileName),m_pFileReaderCtrl(0)
		{
			if ( !InitFileReaderCtrl() )
			{
				assert("�ļ���ʼ��ʧ��");
				return;
			}
		}
		//CFileController(void){};
		// ��ֹʹ�ø�ֵʱ����Ĭ�Ͽ������캯��
		CFileController & operator = (const CFileController& var);
		CFileController(const CFileController& var);

		tstring m_fileName;	//�ļ���
		const CPathBasic &m_pathBasic;
		const CFileBasic &m_fileBasic;
		//const CStringBasic &m_stringBasic;
		CCustomerFileReader *m_pFileReaderCtrl;
	};
}
#endif


