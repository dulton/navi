#ifndef _UEGUI_DATASFORTRUCK_H
#define _UEGUI_DATASFORTRUCK_H

namespace UeGui
{
	//��Դ��Ϣ
	typedef struct GoodsSource
	{
		const static int MaxLength=128;
		const static int MinLength=32;

		//���
		char code[MinLength];
		//��������
		char goods_name[MaxLength];	
		//��������/���
		char total_size[MinLength];
		//���վ
		char address[MaxLength];

		GoodsSource()
		{
			memset(code,0,MinLength);
			memset(goods_name,0,MaxLength);
			memset(total_size,0,MinLength);
			memset(address,0,MaxLength);
		}
	} GoodsSource;

	//��������
	typedef struct GoodsSourceDetail
	{
		const static int MaxLength=128;
		const static int MinLength=32;

		//��Դ��Ϣ����
		int Idx_GoodsSource;
		//��������
		char goods_type[MinLength];
		//��װ��ʽ
		int packingWay;
		//�����ص�
		char srcPlace[MaxLength];
		//Ŀ�ĵص�
		char dstPlace[MaxLength];
		//������Q��
		char srcQcode[10];
		//Ŀ�ĵ�Q��
		char dstQcode[10];
		//����ʱ��
		char sendOutTime[MinLength];
		//����۸�
		float transPrice;
		//����ʱ������
		char limitTime[MinLength];
		//���㷽ʽ
		char payWay[MinLength];
		//��������
		char publishTime[MinLength];
		//�����̼�
		char publisher[MinLength];
		//��ϵ�绰
		char telphone[MinLength];
		//��ע
		char notes[MinLength];
	} GoodsSourceDetail;

	//������Ϣ
	typedef struct LogisticsTrackInfo
	{
		const static int MaxLength=128;
		//const static int MinLength=32;

		//����
		int idx_SourceDetail;
		//��ע
		char notes[MaxLength];

		LogisticsTrackInfo():idx_SourceDetail(-1)
		{
			memset(notes,0,MaxLength);
		}
	} LogisticsTrackInfo;

}

#endif
