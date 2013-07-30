#ifndef _UEGPS_AUTOCOMPORT_H
#define _UEGPS_AUTOCOMPORT_H

#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

#ifndef _UEGPS_BASE_H
#include "uegps.h"
#endif

#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif

#ifndef _UEGPS_POSINFO_H
#include "gpspos.h"
#endif

#include "iobasic.h"

#pragma warning( push )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4251 )

//#define    OSC_FREQ                22118400L
//#define    BAUD_CNT                 7
//#define    BAUD_115200                256 - (OSC_FREQ/192L)/115200L    // 255
//#define    BAUD_57600                256 - (OSC_FREQ/192L)/57600L    // 254
//#define    BAUD_38400                256 - (OSC_FREQ/192L)/38400L    // 253
//#define    BAUD_28800                256 - (OSC_FREQ/192L)/28800L    // 252
//#define    BAUD_19200                256 - (OSC_FREQ/192L)/19200L    // 250
//#define    BAUD_14400                256 - (OSC_FREQ/192L)/14400L    // 248
//#define    BAUD_9600                256 - (OSC_FREQ/192L)/9600L    // 244

namespace UeGps
{
  //#define MAX_COUNT 100
  const char MAX_COMPORT = 11;  
  const char COMPORT_LIST[] = {1, 2, 3, 4, 5, 6, 7,  8, 9, 10, 11};

  const char MAX_BAUDRATECOUNT = 7;
  const unsigned int BAUDRATE_LIST[] = {4800, 7200, 9600, 14400, 19200, 38400, 57600, 115200, 128000};

  typedef std::vector<char> COMPortList;

  //�˿ڼ������Žṹ
  struct COMHandleInfo
  {
    unsigned char m_COMPort; //�˿�
    void* m_COMHandle; //�˿ڶ�Ӧ���
  };

  //�˿ھ������б�
  typedef std::vector<COMHandleInfo> COMHandleList;

  //�����ʴ���б�
  typedef std::vector<unsigned int> BaudRateList;

  //�˿ڼ����ò����ʽṹ
  struct COMPortInfo
  {
    unsigned char m_COMPort;
    BaudRateList m_BaudRateList;
  };

  //���ö˿��б�
  typedef std::vector<COMPortInfo> COMPortInfoList;

  //����Ӧ�˿ڶ���
  class UEGPS_CLASS CAutoCOMPort
  {
  public:
    CAutoCOMPort();
    virtual ~CAutoCOMPort();
  public:
    static const unsigned int SIZEOFINQUEUE = 1024;
    static const unsigned int SIZEOFOUTQUEUE = 1024;
  public:
    /*
    * ��ʼ��COM���б�ɨ��ʱ�������б�
    * ��һ��ɨ��֮�����������COM�޷����򽫸�COMɾ�����ڶ��ξͲ���ɨ���COM��
    */
    void InitCOMPortList();
    /*
    * ����COM�˿�,ÿ��ɨһ���˿ھ͹رգ��´��ٴ�
    */
    bool SearchCOMPort();
    /*
    * һ�δ����ж˿ڲ����ܹ��򿪵Ķ˿ڷ���
    */
    bool OpenAllCOMPort();
    /*
    * һ�ιر����ж˿ڲ����ܹ��򿪵Ķ˿ڷ���
    */
    bool CloseAllCOMPort();
    /*
    * ����COM�˿�,�ȴ����ж˿ڲ�ɨ�裬ֱ���ҵ����ʵĶ˿ں���ͳһ�ر����ж˿�
    * ע�����ø÷���֮ǰҪ��OpenAllCOMPort() ������ɺ�Ҫ�ǵ� CloseAllCOMPort()
    */
    bool SearchCOMPortB();
    /*
    * �Ƿ��Ѿ��ҵ����õĶ˿�
    */
    bool FindValidCOMPort();
    /*
    * ��ȡ��Ч��COM��
    */
    void GetValidCOMPort(IOSetting& setting);
    /*
    * ���Ժ���
    */
    void TestGPSData();
    /*
    * ��ȡ��������
    */
    void GetTestGPSData(std::string& sGPSData);
  private:
    /*
    * �򿪶˿ڲ����ض˿ھ��
    */
    void* OpenCOMPort(const unsigned char COMPort);
    /*
    * ��COM�˿�,������Ӧ������
    */
    bool AutoBaudRate(const unsigned char COMPort, BaudRateList& baudRateList);
    /*
    * ��COM�˿�,������Ӧ������
    */
    bool AutoBaudRate(void* comHandle, BaudRateList& baudRateList);
    /*
    * ��ָ���Ĳ����ʴӴ��ڶ�����
    */
    bool ReadCOMData(void* comHandle, const unsigned int baudRate);
    /*
    * ���������Ϣ
    */
    void LogMessage(const char* msg);
    /*
    * ��ȡ��ǰϵͳʱ�䣬���ؽ��������
    */
    unsigned int GetNowTime();
    /*
    * �Ƿ���GPS����
    */
    bool IsGPSData(char* data, const unsigned int dataLen);
    /*
    * ����GPS����
    */
    bool ParseGPSData(char* gpsData, const unsigned int dataLen);
    /*
    * ��������
    */
    bool SetCommand(void* comHandle);
    /*
    * ����GPS���
    */
    void MakeCommand(const char *str, char *cmd);
    /*
    * дCOM��
    */
    bool WriteCOM(void* comHandle, void *content, unsigned int length);
    /*
    * ��src�ж�ȡreadLen���ȵ���Ч����
    */
    void GetValidGPSData(const char *src, char *validData, const unsigned int readLen);
    /*
    * ������������Ϊ�жϲ�����
    */
    unsigned int GetBaudRate(unsigned char rByte);
  private:
    //�˿��б�
    COMPortList m_COMPortList;
    //�˿ھ���б�ֻ��һ�δ����ж˿�ʱ�õ���
    COMHandleList m_COMHandleList;
    //���õĶ˿��б�
    COMPortInfoList m_validCOMPortList;
    //GPS���ݽ�������
    CGpsPos* m_explainer;
    ////��Ч��GPS���ݴ���ڴ�
    //char m_validGPSData[SIZEOFOUTQUEUE];
  };
}
#endif