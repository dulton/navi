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
#ifndef _UEROUTE_UEVOICE_H
#define _UEROUTE_UEVOICE_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to route basic definition
#ifndef _UEROUTE_ROUTEBASIC_H
#include "routebasic.h"
#endif

// Refer to eEye definition
#ifndef _UEROUTE_SIDEPROPS_H
#include "uesideprops.h"
#endif

// Refer to road nametable definition
#ifndef _UEMODEL_NAMETABLE_H
#include "uemodel\netnametable.h"
#endif
using namespace UeModel;

// Refer sync object
#ifndef _UEBASE_SYNOBJECT_H
#include "uebase\synobject.h"
#endif

// Refer to path basic
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif

// Refer to string basic
#ifndef _UEBASE_STRINGBASIC_H
#include "uebase\stringbasic.h"
#endif

// Refer to voice settings
#ifndef _UEBASE_UESETTINGSIO_H
#include "uebase\uesettingio.h"
#endif

// Refer to dynamic library
#ifndef _UEBASE_DYNLIB_H
#include "uebase\dynlib.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning( disable: 4275 )  // Deprecated function calling
#pragma warning( disable: 4251 )  // Deprecated function calling

// Declare namespace
namespace UeRoute
{
  // Forward class
  class CUeGuider;
  class CUeTTS;

  /**
  * \brief �����г�ָ���·������Ϣ��ʾ
  */
  class UEROUTE_CLASS CUeVoice
  {
    //
    friend class CUeGuider;
    friend class IRoute;

    //
    typedef std::map<int, tstring> VoiceMap;
    typedef VoiceMap::iterator voice_itr;
    typedef VoiceMap::const_iterator voice_citr;

    //
    typedef std::map<unsigned char, std::string> SideMap;
    typedef SideMap::iterator side_itr;
    typedef SideMap::const_iterator side_citr;

  public:
    // constants
    static const int BufMaximum = 10;
    static const int CompleteFlag = 0x15;
    static const int MAXUTURNDIST = 250;
    static const int MINFOLLOWDIST = 350;
    static const int MINTARGETDIST = 1000.;
    static const int MINTWICEDIST = 150;
    static const int MINPLAYDIST = 20;
    static const int MINOUTLETDIST = 500;
    static const int DESTINATIONDIST = 70;

    //
    //
    //
    /**
    * \brief ���캯��
    */
    CUeVoice(CUeGuider *parent);

    /**
    * \brief ��������
    */
    ~CUeVoice();

  public:
    //
    //
    //
    /**
    * \brief �����ڴ�ռ䲢��ʼ��
    */
    unsigned int Prepare(bool isReady = true);

    /**
    * \brief ����ָ��������
    */
    unsigned int PlayVoice(UeSound &snd);

    /**
    * \brife ����ָ����ָ��
    *
    * \param type ָ������
    * \param speed ��ǰ�г��ٶ�
    * \param distForSnd ����ִ��ָ��λ�õľ���
    */
    unsigned int PlayVoice(short type, double speed, double distForSnd);

    /**
    * \brief ������������ʾ�������ڷ�����״̬��ʹ�á�
    *
    * \param dist �����ڵ�ǰ·��ʣ��ľ���
    * \param parcelIdx ��ǰ·�����������
    * \param linkIdx ��ǰ·�ε�ID
    * \param direction ��ǰ·�εĽ�ͨ������
    */
    bool PlayElecEye(double dist, int parcelIdx, int linkIdx, int trafficFlow, bool isNext = false);

    /**
    * \brief ȡ�õ�ǰ�貥���ĵ�������Ϣ
    */
    bool GetCurElecEye(EEyeProp &elecEye);

    /**
    *
    */
    UeSound *GetBufs()
    {
      assert(m_bufs);

      return m_bufs;
    }

    /**
    *
    */
    UeSound &GetCurBuf()
    {
      return m_curBuf;
    }

    /**
    *
    */
    int GetIndexNum()
    {
      return m_indexNum;
    }

    /**
    *
    */
    SndIndex *GetIndice()
    {
      return m_indice;
    }

    /**
    *
    */
    unsigned char *GetData()
    {
      return m_data;
    }

    /**
    *
    */
    void *GetFileHandle()
    {
      return m_file;
    }

    /**
    *
    */
    CUeTTS *GetTTS()
    {
      assert(m_tts);
      return m_tts;
    }

    /**
    * \brief �����ظ�����
    * \param infoCode  ��Ϣ��
    * \param dirCode ת��
    * \param distForSnd ����ת��ľ���
    */
    void ReplayVoice(unsigned char infoCode, unsigned char dirCode, int distForSnd);

    /**
    * \brief ��ȡ����Э���
    */
    CDynamicLibrary &GetSoundProtocolLib();

    /**
    * \brief ��������ǰ�����豸����
    *
    * \return �������µķ���ֵ
    * -1����ȡʧ��
    * 0:	�ɹ��������ȼ����������豸��
    * 1:	�ɹ�������Ϊ�������ţ�
    */
    long StartPlaySound(void *pParam, long ltime);

    /**
    * \brief �������������豸����
    */
    void EndPlaySound(void* pParam);

  private:
    //
    //
    //
    /**
    * \brief �������������߳�
    */
    unsigned int BeginBroadcast(const UeSound &snd);

    /**
    * \brief �˳����������߳�
    */
    unsigned int StopBroadcast();

    /**
    * \brief �����г��ٶȼ���ǰ���벥����λ�ã���ò����ľ���ָ�2km, 1km, 500m, ...
    *
    * \param prompt ָ�����
    * \param snd ���ص�������Ϣ
    * \param speed ��ǰ�г��ٶ�
    * \param distForSnd �ಥ����ľ���
    */
    unsigned int ForwardSND(SndPrompt &prompt, UeSound &snd, double speed, int distForSnd);

    /**
    *
    */
    unsigned int LoadSnds();

    /**
    * \brief ȡ�÷���ָ��
    *
    * \param indicators ��ǰ·��������ָ���
    * \param curIndicator ��ǰ����ָ��
    * \param curOrder ��ǰ����ָ������
    * \param nameOffset ����ƫ����
    * \param snd �����������Ϣ
    */
    bool DirCmd(GuidanceIndicator **indicators, GuidanceIndicator *curIndicator, int &curOrder, int &nameOffset, UeSound &snd);

    /**
    * \brief ȡ����Ϣָ��
    *
    * \param prompt ָ�����
    * \param snd �����������Ϣ
    * \param curOrder ��ǰ����ָ������
    * \param indicators ��ǰ·��������ָ���
    */
    bool InfoCmd(SndPrompt &prompt, UeSound &snd, int curOrder, GuidanceIndicator **indicators);

    /**
    * \brief ���ж��벥�������ʱ���������貥����·��
    */
    bool IsContinue(int order, GuidanceIndicator **indicators, bool isFirst, bool isEyeContinue = true);

    /**
    *
    */
    bool IsIgnore(GuidanceIndicator *indicator);

    /**
    *
    */
    bool IsGeneralRoadForm(GuidanceIndicator *indicator);

    /**
    *
    */
    bool IsRoundAboutInfo(const SndPrompt &prompt);

    /**
    *
    */
    bool IsUTurn(short curDir, short nextDir);

    /**
    *
    **/
    bool IsUTurn(GuidanceIndicator **indicators, int order, int nextOrder);

    /**
    *
    */
    bool IsValidString(char *str);

    /**
    *
    **/
    bool IsSpecialInfo(int infoCode);

    /**
    *
    **/
    bool IsGeneralInfo(const SndPrompt &prompt);

    /**
    * \brief ������һ��ָ����������ָ��
    */
    unsigned int PlayFollow(int curOrder, GuidanceIndicator **indicators, UeSound &snd, int &nameOffset);

    /**
    * \brief ����ĳЩ������������磺��ʼ�����������յ㡢���١�...
    */
    unsigned int PlaySpecial(short type, double speed, double distForSnd, int curOffet, GuidanceIndicator *curIndicator, SndPrompt &prompt);

    /**
    * \brief �жϸô��ĸ���·����ʻ��
    */
    bool WhichMainOutlet(GuidanceIndicator **indicators, int curOrder, int curSndCode, UeSound &snd);

    /**
    * \brief �жϸô��ĸ���������ʻ��
    */
    bool WhichRoundAboutOutlet(GuidanceIndicator **indicators, int curOrder, int curSndCode, UeSound &snd);

    /**
    * \brief �ж��Ƿ�ʻ����·
    */
    bool IsExitMain(GuidanceIndicator *nextIndicator, GuidanceIndicator *curIndicator);

    /**
    * \brief ����ָ��������������
    */
    void MakeTTS(int code, UeSound &snd);

    /**
    * \brief ����ָ���������ָ������
    */
    void MakeVoices();

    /**
    * \brief �����յ㷽��
    */
    void GetDestinationDirection(UeSound &snd);

    /**
    * \brief ����������������
    */
    void SetVoiceSettings(const UeBase::VoiceSettings &settings);

    /**
    * \brief ����TTS�������ɫ
    */
    unsigned int SetRole(UETTS_Role role);

    /**
    * \brief ȡ�õ����۴���
    */
    unsigned char GetEyeCode(const GuidanceIndicator *const curIndicator);

    /**
    * \brief ���·�ι�����Ϣ
    */
    //unsigned char GetSideProp(const GuidanceIndicator *curIndicator, const GuidanceIndicator *nextIndicator, char *prop);

    /**
    * \brief ȡ�÷��򿴰��еĸ��ٳ�����Ϣ
    */
    bool GetHighwayOutlets(CMemVector &outlets);

    /**
    * \brief ��sides�ļ��л�ȡ���������ݻ�ͨ��ʾ����
    */
    bool GetTrafficSign(const GuidanceIndicator *indicator, bool isEye, CMemVector &signs);

    /**
    * \brief ��õ�·������Ϣ
    */
    unsigned char GetSideProp(unsigned char type, const GuidanceIndicator *curIndicator, const GuidanceIndicator *nextIndicator, char *prop);

    /**
    * \brief ���������Ϣ
    */
    void ClearSideProp(unsigned char type);

    /**
    * \brief ��ȡ������Ϣ����
    */
    unsigned char GetSideType(const GuidanceIndicator *curIndicator, const GuidanceIndicator *nextIndicator);

    /**
    * \brief ������ʾ�����ۼ���ͨ��ʾ
    */
    void PlaySideSigns(double distForSnd, double speed, const GuidanceIndicator *curIndicator, const GuidanceIndicator *nextIndicator);

    /**
    * \brief ��ȡ����λ��������۵ĵ�·����
    *
    * \param distForSnd �����ڵ�ǰ��·ʣ�����ʻ����
    * \param pSign ��ͨ��ʾ��Ϣ
    * \param curIndicator ��ǰ·�������Ϣ
    *
    * \return ����ֵ-10Ϊ�Ƿ�ֵ
    */
    double GetTrafficSignDist(double distForSnd, EEyeProp *pSign, const GuidanceIndicator *curIndicator);

    /**
    * \brief ��ͨ��ʾ������ʾ
    */
    bool PlayTrafficSign(double distForSnd, short type);

    /**
    * \brief ��ȡ����λ��������۵ĵ�·����
    *
    * \param distForSnd �����ڵ�ǰ��·ʣ�����ʻ����
    * \param pEye ��������Ϣ
    * \param indicator ·����Ϣ
    * \param isNextIndicator ���������ڵ�ǰ��·��������һ·��
    *
    * \return ����ֵ-10Ϊ�Ƿ�ֵ
    */
    double GetElecEyeDist(double distForSnd, EEyeProp *pEye, const GuidanceIndicator *indicator, bool isNextIndicator = false);

    /**
    * \brief ������������ʾ
    */
    bool PlayElecEye(double distForSnd, unsigned short type, unsigned short speed, bool isHighway = false);

    /**
    * \brief ����·��
    */
    void PlayRoadName(unsigned int rt, int curOrder, unsigned int nameOffset, int curOffset, const SndPrompt &prompt, UeSound &snd, GuidanceIndicator **indicators);

    /**
    * \brief �������򿴰�
    */
    void PlaySignPost(unsigned int rt, int curOrder, UeSound &snd, GuidanceIndicator **indicators, bool isNext = false);

    /**
    * \brief ���������ۼ�ؽ������ʾ��
    */
    void PlayEyeOffVoice();

    /**
    * \brief �������
    */
    void PlayAdvance(char *prop);

    /**
    * \brief UE��PSF������Ľ�ͨ������ԭʼ��ͨ������ȡֵ��ת��
    */
    int GetTrafficDirection(int trafficFlow);

    /**
    * \brief ��ȡָ���������ڵ�������
    */
    int GetDistrictIdx(const CGeoPoint<long> &pos);

    /**
    * \brief ��ȡָ����������������������
    */
    void GetDistrictName(const CGeoPoint<long> &pos, char *distName);



  protected:
    //
    SndPrompt m_prePrompt;

    //
    short m_prevDistFlag;
    short m_distFlag;
    int m_distForSnd;
    int m_orderForSnd;
    int m_nextDistForSnd;
    int m_nextOrderForSnd;
    int m_preIndicator;
    int m_curSndCode;
    int m_nextSndCode;

    // 
    int m_latestAdminOrder;

    //
    UeSound m_preBuf;
    UeSound m_curBuf;
    UeSound *m_bufs;

    //
    void *m_file;
    void *m_thread;

    //
    short m_indexNum;
    SndIndex *m_indice;
    unsigned char *m_data;

    //
    CUeGuider *m_parent;
    INameTable *m_nameTable;

    //
    VoiceMap m_vStrings;
    CUeTTS *m_tts;

    // System and voice settings
    UeBase::SystemSettings m_sysSettings;
    UeBase::VoiceSettings m_voiceSettings;

    // eSide Properties definition
    CUeSideProps *m_sides;
    SideMap m_sideProps;

    //
    short m_eyeDistFlag;
    short m_trafficDistFlag;
    EEyeProp m_curElecEye;

    //
    unsigned char m_velocityType;
    const CPathBasic &m_pathBasic;
    const CStringBasic &m_stringBasic;
    static CSynGuard m_synObject;
  };
}

#endif
