/*
* ������Ҫ��ʵ��ͨ���ڴ�ӳ��ļ�������ȡ�ļ��������ļ���IO�ͼ����ڴ�ռ�á�
* ͬʱ���ܹ�����ļ��Ķ�ȡЧ�ʣ����ڴ�������������ļ�ʱ�����൱��Ҫ�����ã�
* ������Ҫ�����˿ɼ����ڴ�ʹ�ú�Ƶ��IO�ļ����ŵ㡣
* 
* ʹ��˵��:
* ����Ϊ��ͨ��ֻ֧�ֵ�λ���ݶ����Ĵ洢�Ͷ�д����֧�ֶ������ݵĶ�дʹ�á�
*
* by HeJiangDong 2012-08-24
*/

#ifndef _UEBASE_FILEREADER_H
#define _UEBASE_FILEREADER_H

#include "uebase.h"
#include "pathbasic.h"
#include "filebasic.h"

namespace UeBase
{ 
  //����ֻ�ܲ����������ݵĴ洢
  class UEBASE_CLASS CCustomerFileReader
  {
  public:
    CCustomerFileReader(tstring& fileName, unsigned int blockSize);
    virtual ~CCustomerFileReader() {}
  public:
    //�����ļ�ӳ���ڴ�
    bool ConnectFile();
    //�Ͽ�����
    bool DisconnectFile();
    //���������������ļ��ж�ȡ���� ����blockSizeΪ��ȡ�����ݴ�С��ֻ�ж���ʹ�ò�ʹ�õ�ConnectFile()��DisconnectFile()
    const char* GetBlockData(const unsigned int dataIndex, unsigned int& readSize);
    //��ȡ�ļ���������,����֮ǰ����Ҫ����ConnectFile()��DisconnectFile()
    unsigned int GetDataCount();
    /*
    * ��ӿ�����
    * parameter whence : UE_SEEK_END��ӵ��ļ�ĩβ UE_SEEK_BEGIN��ӵ��ļ�ͷ�� Ĭ����ӵ��ļ���β
    */
    bool AddBlockData(const char* blockData, int whence = CFileBasic::UE_SEEK_BEGIN);
    //ɾ��������
    bool RemoveBlockData(const unsigned int dataIndex);
    //ɾ����������
    bool RemoveAllData();
    /*
    * �޸Ŀ�����
    * parameter whence : UE_SEEK_BEGIN�޸ĺ������Ƶ��ļ�ͷ UE_SEEK_CUR �޸ĺ�������Ȼ���浽��ǰλ��
    */
    bool EditBlockData(const unsigned int dataIndex, const char* editData, int whence = CFileBasic::UE_SEEK_CUR);
  private:
    //��������������ȡ��ǰ�������ļ��е���ʼλ��
    unsigned int GetPosition(const unsigned int dataIndex);
  private:
    //�Ƿ��ļ��Ѿ���������״̬
    bool m_connected;
    tstring m_fileName;
    unsigned int m_blockSize;
    unsigned int m_dataCount;
    void *m_fileHandle;
    void *m_mappedMemory;
    unsigned char *m_dataBegin;

    const CPathBasic &m_pathBasic;
    const CFileBasic &m_fileBasic;
  };
}
#endif