/*
* \����Ȩ�޹���
*/

#ifndef _UEGUI_OPERATIONRIGHT_H
#define _UEGUI_OPERATIONRIGHT_H

#include <stdio.h>
#include <vector>

namespace UeGui
{
  /*
  * \GUI����Ȩ�޶���
  */
  //���˵�
  #define OR_MAP               100       //��ͼ����
  #define OR_FINDPLACE         101       //�ҵط�
  #define OR_ROUTEOPERATION    102       //·�߲���
  #define OR_DDTSERVICE        103       //����ͨ����
  #define OR_MYINFORMATION     104       //�ҵ���Ϣ
  #define OR_NAVSETTING        105       //��������
  #define OR_SYSSETTING        106       //ϵͳ����

  //��ͼ����ģ��  
  #define OR_MAPFASTOPE        10001     //��ݲ���
  #define OR_MAPDIMENSIONS     10002     //2D��3D�л�
  #define OR_BACKTRACKING      10003     //���̹滮

  //�ҵط�ģ��  
  #define OR_QUERYPLACENAME    10101     //�����
  #define OR_QUERYROUTE        10102     //���·
  #define OR_QUERYTYPE         10103     //�ҷ������
  #define OR_QUERYHISTORY      10104     //����ʷ
  #define OR_QUERYADDRESSBOOK  10105     //���ַ��
  #define OR_QUERYAROUND       10106     //���ܱ�
  #define OR_QUERYQCODE        10107     //��Q��
  #define OR_QUERYDISTRICT     10108     //������
  
  //·�߲���ģ�飨���ã�  
  #define OR_PASSEDROUTE       10201     //������·
  #define OR_ADJUSTROUTE       10202     //����·��
  #define OR_DETOURRULE        10203     //��·����
  #define OR_NEXTDESTINATION   10204     //��һĿ�ĵ�
  #define OR_BROWSELINE        10205     //����·��
  #define OR_DEMONAVIGATION    10206     //ģ�⵼��
  #define OR_DELETEROUTE       10207     //ɾ��·��
  
  //����ͨ����ģ�飨���ã�  
  #define OR_FOURSERVICE       10301     //4S���ѯ
  #define OR_SCENICSPOTQUERY   10302     //�����ѯ  
  #define OR_OPERATIONHELP     10303     //��������
  #define OR_UPDATESERVICE     10304     //��������

  //�������������ã�
  #define OR_MAPBROWSE         1030301   //��ͼ���
  #define OR_MAPNAVIGATION     1030302   //��ͼ����
  #define OR_BASICFUCTION      1030303   //��������
  #define OR_DDTSERVICEINFO    1030304   //����ͨ����
  #define OR_FASTDO            1030305   //��������
  #define OR_3DSHOW            1030306   //3D��ʾ
  #define OR_3DCITY            1030307   //3D����

  //�ҵ���Ϣģ�飨���ã�  
  #define OR_HISINFORMATION    10401     //��ʷ��Ϣ
  #define OR_MYADDRESSBOOK     10402     //��ַ��
  #define OR_MYJOURNEY         10403     //�ҵ��г�
  #define OR_MYFAVORITE        10404     //���õ�
  #define OR_CAPACITY          10405     //������Ϣ

  //��ʷ��Ϣ�����ã�
  #define OR_HISRECORD         1040101   //��ʷ��¼
  #define OR_HISTRACK          1040102   //��ʷ�켣
  #define OR_HISROUTE          1040103   //��ʷ·��

  //��������ģ�飨���ã�  
  #define OR_MAPSETTING        10501     //��ͼ��ʾ
  #define OR_CROSSPIC          10502     //·�ڷŴ�ͼ
  #define OR_EEYESETTING       10503     //������
  #define OR_PROMPTSETTING     10504     //��ʾ����
  #define OR_ROUTESETTING      10505     //·������
  #define OR_TRACKSETTING      10506     //�켣����
  #define OR_SAFETYSETTING     10507     //��ȫ����
  #define OR_RESTORE           10508     //��ʼ��

  //��ͼ��ʾ�����ã�
  #define OR_MAPMODEL          1050101   //��ͼģʽ      
  #define OR_MAPSTYLE          1050102   //��ͼ���
  #define OR_MAPDIRECTION      1050103   //������ͼ����
  #define OR_MAPINDICATE       1050104   //������ͼ��ʾ

  //ϵͳ����ģ�� 
  #define OR_VOICESETTING      10601     //��������
  #define OR_CARICONSETTING    10602     //�Գ�ͼ��
  #define OR_TIMECALIBRATION   10603     //ʱ��У׼
  #define OR_STARTDECLARATION  10604     //��������
  #define OR_VERSIONINFO       10605     //�汾��Ϣ  

  //Ȩ�޹������
  class CGuiOperationRight
  {
  public:
    CGuiOperationRight();
    virtual ~CGuiOperationRight();
  public:
		/*!
		* \brief ��ȡ����
		*/
    static CGuiOperationRight* GetGuiOperationRight();
		/*!
		* \brief �ͷŶ���
		*/
    static void Delete();
		/*!
		* \brief�жϵ�ǰ�����Ƿ���Ȩ��
		*/
    static bool HaveRight(unsigned int rightID);
		/*!
		* \brief�жϵ�ǰ�����Ƿ���Ȩ���б���
		*/
    bool ExistsInRightList(unsigned int rightID);
  private:
		/*!
		* \brief��ʼ��Ȩ���б�
		*/
    void InitRightList();
  private:
    //Ȩ�޲�������
    static CGuiOperationRight* m_guiOpeRight;
    //Ȩ���б�
    std::vector<unsigned int> m_opeRightList;
  };
}

#endif
