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
#ifndef _UEFACADE_WRAPPER_H
#define _UEFACADE_WRAPPER_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEFACADE_BASE_H
#include "uefacade.h"
#endif

#include "portability.h"

// Refer to geometry basic definition
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif
using namespace UeBase;

// Specify namespace UeFacade
namespace UeFacade
{
  // Forward classes
  class CUeWrapperImpl;

  /*! \class IUeWrapper
  * \brief �ṩ������ڵĽӿ���,facade���ģʽ
  */
  class UEFACADE_CLASS IUeWrapper
  {
  public:
    //
    // ����&����
    //
    /*!
    * \brief ���캯��
    *
    * \param oneImpl ����ʵ����ָ��
    */
    IUeWrapper(CUeWrapperImpl *oneImpl);

    /*!
    * \brief ��������
    */
    ~IUeWrapper();

  public:
    //
    // Basic interface definitions
    //
    /*!
    * \brief ����IUeWrapper����
    *
    * \param oneImpl ָ��IUeWrapper�ӿھ���ʵ�����ʵ���ָ��
    */
    static IUeWrapper *GetWrapper(CUeWrapperImpl *oneImpl);

    /*!
    * \brief ��̬����uewrapper��
    */
    static IUeWrapper *GetWrapper();

    /*!
    * \brief �ͷ�Wrapper
    */
    void Delete();

    //
    // Schema interface defintion
    //
    /*!
    * \brief ���ظ���ģ�����Դ����Ϊ��Ӧģ��ע��mediator����Դ��������
    *
    * \param oneSchema According to schema definition, we can load different modules or specify special behaviors of one module
    */
    unsigned int Load(short oneSchema);

    /*!
    * \brief �ͷŸ���ģ�����Դ
    */
    unsigned int UnLoad();

    /*!
    * \brief ��ȡָ��ģ�����ӿڣ����ģ����δ���أ������֮��
    *
    * \param ģ���Ӧ��ö��ֵ��ö�ٶ���鿴PackageDefinition
    */
    void *GetModel(short type);

    /*!
    * \brief ������ͼ�Ĵ��ھ������С
    *
    * \param handle ���ھ��
    * \param width ���ڿ��
    * \param height ���ڸ߶�
    */
    bool Attach(void *handle, int width, int height);

    /*!
    * \brief Ԥ�ȼ��ص�ͼ
    *
    * \param schema ���ص�ͼ�ķ�ʽ��ö�ٶ�����鿴LayerSchema��
    * ʾ����UeMap::LSH_Shape | UeMap::LSH_Index | LSH_Network | UeMap::LSH_RoutePlan | LSH_BackGround
    *
    * \param fileName shp�ļ���(�������)������Ϊ���ַ���
    * \param scaleLevel ��ͼ���ڱ����ߵȼ�
    * \param angle ��ͼ��ת�Ƕ�
    */
    bool Prepare(short schema, const tstring &fileName, short scaleLevel = 1, double angle = 0.);

    /*!
    * \brief TODO:������
    *
    * \scaleLevels
    * \scaleGroups
    * \mapExtent
    * \gridWidth
    * \gridHeight
    */
    bool CreateIndex(short scaleLevels, int scaleGroups, const CGeoRect<double> &mapExtent, double gridWidth, double gridHeight);

    //
    //
    //
    /*!
    * \brief ��Ӧ�ػ�����
    */
    void OnPaint();

    /*!
    * \brief ��Ӧ���ڴ�С�仯
    *
    * \param width �ı��Ĵ��ڿ��
    * \param height �ı��Ĵ��ڸ߶�
    */
    void OnSize(int width, int height);

    /*!
    * \brief ��Ӧ������/��갴�²���
    *
    * \param scrPoint �������Ļ����
    */
    void MouseDown(CGeoPoint<short> &scrPoint);

    /*!
    * \brief ��Ӧ����ƶ�����
    *
    * \param scrPoint ��Ļ����
    */
    void MouseMove(CGeoPoint<short> &scrPoint);

    /*!
    * \brief ��Ӧ���ſ�����
    *
    * \param scrPoint ��Ļ����
    */
    void MouseUp(CGeoPoint<short> &scrPoint);

    /*!
    * \brief ��ʱ���������
    */
    void TimerProc();

    /*!
    * \brief ���д������
    */
    void IdleProc();

    //
    //
    //
    /*!
    * \brief ע��GPS������ܺ���
    *
    * \param func ���ܺ����ĺ���ָ��
    */
    bool RegisterDecryptFunc(void *func);

    /*!
    * \brief ע����ܼ���ϵ�к���
    */
    bool RegisterActiveFunc(void *getuuid, void *checkIsActive, void *checkActiveID, void *saveActiveFile);

    /*!
    * \brief ���SD��
    */
    bool DetectSDCard();

  private:
    /// One kind of implementation
    CUeWrapperImpl *m_wrapperImpl;

    /// Singleton for this wrapper
    static IUeWrapper *m_wrapper;
  };
}
#endif