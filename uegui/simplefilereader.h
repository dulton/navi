/*
* ������Ҫ��ʵ��ͨ���ڴ�ӳ��ļ�������ȡ�ļ��������ļ���IO�ͼ����ڴ�ռ�á�
* ͬʱ���ܹ�����ļ��Ķ�ȡЧ�ʣ����ڴ�������������ļ�ʱ�����൱��Ҫ�����ã�
* ������Ҫ�����˿ɼ����ڴ�ʹ�ú�Ƶ��IO�ļ����ŵ㡣
* 
* ʹ��˵��:
* ����Ϊ��ͨ��ֻ֧�ֵ�λ���ݶ����Ĵ洢�Ͷ�ȡ����Ҫ����ֻ�������ݶ�ȡ������ר�����ݡ�
*
* by QiuJunWei 2012-11-1
*/

#ifndef _UEBASE_SIMPLEFILEREADER_H
#define _UEBASE_SIMPLEFILEREADER_H



#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif
#ifndef _UEBASE_STRINGBASIC_H
#include "uebase\stringbasic.h"
#endif

namespace UeBase
{ 
  //����ֻ�ܲ����������ݵĴ洢
  class CSimpleFileReader
  {
  public:
    CSimpleFileReader(const tstring& fileName, unsigned int blockSize);
    virtual ~CSimpleFileReader() {}
  public:
    //�����ļ�ӳ���ڴ�
    bool ConnectFile();
    //ͨ���ƶ����ļ��������ļ�ӳ���ڴ�
    bool ConnectFile(tstring fileName);
    //�Ͽ�����
    bool DisconnectFile();
    //���������������ļ��ж�ȡ���� ����blockSizeΪ��ȡ�����ݴ�С��ֻ�ж���ʹ�ò�ʹ�õ�ConnectFile()��DisconnectFile()
    const char* GetBlockData(const unsigned int dataIndex, unsigned int& readSize);
    //��ȡ�ļ���������,����֮ǰ����Ҫ����ConnectFile()��DisconnectFile()
    unsigned int GetDataCount();

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