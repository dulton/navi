#ifndef _UEGUI_GOODSSOURCEMGR_H
#include "GoodsSourceMgr.h"
#endif
#include <string.h>
using namespace UeGui;

CmakeDataFiles::CmakeDataFiles():m_goodSourceMgr(CFileController<GoodsSource>::getGoodsSourceCtrl()),
m_LogisticsTrackMgr(CFileController<LogisticsTrackInfo>::getLogisticsTrackCtrl()),
m_GSDetailMgr(CFileController<GoodsSourceDetail>::getGoodsSourceDetailCtrl())
{

}
void CmakeDataFiles::makeGoodsSourceDetail()
{
	m_GSDetailMgr.ConnectToFile();
	if (m_GSDetailMgr.GetCount()<1)
		//if( 1==2 )
	{
		GoodsSourceDetail tmp;
		memset(&tmp,0,sizeof(GoodsSourceDetail));

		tmp.Idx_GoodsSource=0;
		::sprintf( (char *)tmp.goods_type, "ʳƷ" );
		::sprintf( (char *)tmp.srcPlace, "˳�����´���ʯ�ݹ�ҵ��1��" );
		::sprintf( (char *)tmp.srcQcode, "xjsatj8b1" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��������ʦ�Ҵ�·" );
		::sprintf( (char *)tmp.dstQcode, "03088jcyx" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "��С��" );
		::sprintf( (char *)tmp.telphone, "15526837898" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=1;
		::sprintf( (char *)tmp.goods_type, "����" );
		::sprintf( (char *)tmp.srcPlace, "˳�����������б�·38��" );
		::sprintf( (char *)tmp.srcQcode, "xqnkw97fg" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��ɳ�з�ҳ�" );
		::sprintf( (char *)tmp.dstQcode, "33y6k1qma" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18688487719" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=2;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "ddi4vs3c4" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ����������·223��" );
		::sprintf( (char *)tmp.dstQcode, "0jb112ii9" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13041996990" );
		::sprintf( (char *)tmp.notes, "��9.6�׵��ų��������" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=3;
		::sprintf( (char *)tmp.goods_type, "��е" );
		::sprintf( (char *)tmp.srcPlace, "˳���ݹ�ҵ��·13��" );
		::sprintf( (char *)tmp.srcQcode, "x4m6vfi0n" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��ɽ׳������������ɽ�ؽ�ʯ·" );
		::sprintf( (char *)tmp.dstQcode, "dt0eguhpy" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13825099145" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=4;
		::sprintf( (char *)tmp.goods_type, "����" );
		::sprintf( (char *)tmp.srcPlace, "˳�����ִ���������������3�ŵ�H��11��" );
		::sprintf( (char *)tmp.srcQcode, "x1qdk3m9v" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�����������12��5��" );
		::sprintf( (char *)tmp.dstQcode, "6k2190at2" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13710068629" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=5;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳�´������ǻ�԰" );
		::sprintf( (char *)tmp.srcQcode, "x4mkcxbnd" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��֣������·" );
		::sprintf( (char *)tmp.dstQcode, "8skuakw73" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13725223815" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=6;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳�����ݹ����ĺ���·23��" );
		::sprintf( (char *)tmp.srcQcode, "x7thnai5p" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�人�н�������ҵ·" );
		::sprintf( (char *)tmp.dstQcode, "5up6w30f2" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13376148369" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=7;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�ִ�����¡��ҵ��" );
		::sprintf( (char *)tmp.srcQcode, "xksedav57" );
		::sprintf( (char *)tmp.dstPlace, "�����ж�������������ͬ" );
		::sprintf( (char *)tmp.dstQcode, "ceyxw8ttq" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13345672168" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=8;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳�����׽���" );
		::sprintf( (char *)tmp.srcQcode, "xwp8pur1t" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ������½����" );
		::sprintf( (char *)tmp.dstQcode, "0pahhfy80" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15346146819" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=9;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳���ִ�" );
		::sprintf( (char *)tmp.srcQcode, "x6t07ujug" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�������ռ��������˽�" );
		::sprintf( (char *)tmp.dstQcode, "fs46h07ya" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15302240018" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=10;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳�����ִ���" );
		::sprintf( (char *)tmp.srcQcode, "x9rfmjkyb" );
		::sprintf( (char *)tmp.dstPlace, "�Ĵ�ʡ�����и�������԰·����" );
		::sprintf( (char *)tmp.dstQcode, "6a9ivb1gk" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13708465724" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=11;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳��������������·52�� " );
		::sprintf( (char *)tmp.srcQcode, "x5n9shu19" );
		::sprintf( (char *)tmp.dstPlace, "�㽭ʡ����������Ϫ�ж�·258�š�260��" );
		::sprintf( (char *)tmp.dstQcode, "49av2hvss" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13708465724" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=12;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳�����´���" );
		::sprintf( (char *)tmp.srcQcode, "xht1xn85s" );
		::sprintf( (char *)tmp.dstPlace, "���ɹŰ�ͷ���ƶ��������㳡����" );
		::sprintf( (char *)tmp.dstQcode, "fj9945daq" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13978691611" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=13;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳���׽�����ɵ���66��" );
		::sprintf( (char *)tmp.srcQcode, "xcpsct6jh" );
		::sprintf( (char *)tmp.dstPlace, "�㶫ʡտ���г࿲��" );
		::sprintf( (char *)tmp.dstQcode, "u0e7mvhn1" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18902279093" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=14;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳�����̽���" );
		::sprintf( (char *)tmp.srcQcode, "xerndehdb" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�������������������·68��" );
		::sprintf( (char *)tmp.dstQcode, "9nymkcpm3" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18633569097" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=15;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "����������������3��103��" );
		::sprintf( (char *)tmp.srcQcode, "xwqg4f75h" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ������μ����������·44��" );
		::sprintf( (char *)tmp.dstQcode, "8aj7fs2ne" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13500569456" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=16;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "˳�����������б�·38��" );
		::sprintf( (char *)tmp.srcQcode, "x1nswx5n9" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�����о��������ݴ��" );
		::sprintf( (char *)tmp.dstQcode, "55fmn6hvq" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13135337569" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=17;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xxks6h7q8" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�γ�����ˮ��204����" );
		::sprintf( (char *)tmp.dstQcode, "8tfpujkgv" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:45" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18935699183" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=18;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xbk3u7rbd" );
		::sprintf( (char *)tmp.dstPlace, "�Ϻ��б�ɽ�����·352Ū400��" );
		::sprintf( (char *)tmp.dstQcode, "6h5ih3emf" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13233118690" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=19;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xtpjep6e6" );
		::sprintf( (char *)tmp.dstPlace, "�Ĵ�ʡ�ɶ���������������" );
		::sprintf( (char *)tmp.dstQcode, "5eqb7fi9v" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18644585689" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=20;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "x8pgreh26" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ������ͬ����������·74��֮11" );
		::sprintf( (char *)tmp.dstQcode, "032hfjb7b" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15333192297" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=21;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xbpewiumm" );
		::sprintf( (char *)tmp.dstPlace, "������ʡ��������и�ԣ��" );
		::sprintf( (char *)tmp.dstQcode, "mydn5bbnn" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13208979986" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=22;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xtn9mm00f" );
		::sprintf( (char *)tmp.dstPlace, "�㽭ʡ��������ɽ��ͨ����·" );
		::sprintf( (char *)tmp.dstQcode, "53ahxncs8" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18633966490" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=23;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xgsnfiva4" );
		::sprintf( (char *)tmp.dstPlace, "�½�ʡ������" );
		::sprintf( (char *)tmp.dstQcode, "eyv0bf94c" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15900787984" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=24;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "x4s6k7ft0" );
		::sprintf( (char *)tmp.dstPlace, "�㶫ʡ÷����÷����������·" );
		::sprintf( (char *)tmp.dstQcode, "d7snb903b" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13735339999" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=25;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xxsjucrbd" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��Ȫ�й�����ԨȪ��" );
		::sprintf( (char *)tmp.dstQcode, "e9av6mpja" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15900997981" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=26;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xysgcqiq8" );
		::sprintf( (char *)tmp.dstPlace, "������ʡ������������ֱ�ָ�71��" );
		::sprintf( (char *)tmp.dstQcode, "j01q1ajyb" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13244689987" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=27;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xcr699fm9" );
		::sprintf( (char *)tmp.dstPlace, "�㶫ʡ��������ɳ�����" );
		::sprintf( (char *)tmp.dstQcode, "dexr8n29r" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "2012-10-22 13:48" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13302571512" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=28;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xhsv4ei20" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��������������ʮ��·24��" );
		::sprintf( (char *)tmp.dstQcode, "ff92qaw44" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13244686172" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=29;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xprxriqpy" );
		::sprintf( (char *)tmp.dstPlace, "�Ĵ�ʡۯ��" );
		::sprintf( (char *)tmp.dstQcode, "5yv7emnt4" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15866791181" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=30;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "x9sj1a8im" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�������������ķ���" );
		::sprintf( (char *)tmp.dstQcode, "6th8i3ihm" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15300983086" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=31;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xtr4adf0b" );
		::sprintf( (char *)tmp.dstPlace, "�ӱ�ʡ�����" );
		::sprintf( (char *)tmp.dstQcode, "" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13966668607" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=32;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "x6tdb5emh" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�Ƿ����������" );
		::sprintf( (char *)tmp.dstQcode, "8in0ehw62" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15322224489" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=33;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xssapm9cd" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��ɳ�����������ſ��̼���162��" );
		::sprintf( (char *)tmp.dstQcode, "3nt43hedw" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18900797980" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=34;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xuvdn7efq" );
		::sprintf( (char *)tmp.dstPlace, "�㽭ʡ�����к����س���·" );
		::sprintf( (char *)tmp.dstQcode, "5dm24f8kv" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18600077589" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=35;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xvt4hs6um" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ������" );
		::sprintf( (char *)tmp.dstQcode, "3cd1bp2tk" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15366795867" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=36;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xmv716y9j" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ������������ѩ��·" );
		::sprintf( (char *)tmp.dstQcode, "8j6qp9amb" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18673498934" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=37;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xrvsa9tdk" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ������" );
		::sprintf( (char *)tmp.dstQcode, "3jf7jd1y1" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13925228609" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=38;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xjtebwpdi" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ������������" );
		::sprintf( (char *)tmp.dstQcode, "9s9aue7ga" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "18623249890" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=39;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xtwyr64rb" );
		::sprintf( (char *)tmp.dstPlace, "�Ĵ�ʡ�ɶ�����Ȫ������ƽ·2��4��" );
		::sprintf( (char *)tmp.dstQcode, "59q32prd9" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13369695087" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=40;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xdw1bff41" );
		::sprintf( (char *)tmp.dstPlace, "�Ϻ����ֶ���������г�" );
		::sprintf( (char *)tmp.dstQcode, "602h9sqpj" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15600245382" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=41;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xeyhvmxpw" );
		::sprintf( (char *)tmp.dstPlace, "������ʡ��������и�ԣ��" );
		::sprintf( (char *)tmp.dstQcode, "mydn5bbnn" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15668866791" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=42;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "x7w5gp7jt" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ��������ʦ�Ҵ�·" );
		::sprintf( (char *)tmp.dstQcode, "03088jcyx" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15969799768" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=43;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xhy9mbs4k" );
		::sprintf( (char *)tmp.dstPlace, "�㶫ʡ��������ɳ�����" );
		::sprintf( (char *)tmp.dstQcode, "dexr8n29r" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13525226138" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=44;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "x6y5abk2a" );
		::sprintf( (char *)tmp.dstPlace, "�½�ʡ���������� ��·" );
		::sprintf( (char *)tmp.dstQcode, "hxd68v0i3" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "15300899003" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=45;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xeyeki7ej" );
		::sprintf( (char *)tmp.dstPlace, "����ʡ�����б��������½�3����������" );
		::sprintf( (char *)tmp.dstQcode, "83gqbs370" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13822215469" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=46;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xfyt959ft" );
		::sprintf( (char *)tmp.dstPlace, "������ʡ�ں��������" );
		::sprintf( (char *)tmp.dstQcode, "m4m4q3qpg" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13288732181" );
		::sprintf( (char *)tmp.notes, "" );
		m_GSDetailMgr.AddOneItem(tmp);

		tmp.Idx_GoodsSource=47;
		::sprintf( (char *)tmp.goods_type, "" );
		::sprintf( (char *)tmp.srcPlace, "�㶫ʡ��ɽ��" );
		::sprintf( (char *)tmp.srcQcode, "xjw3abw18" );
		::sprintf( (char *)tmp.dstPlace, "�Ĵ�ʡ�Թ��и�˳������·" );
		::sprintf( (char *)tmp.dstQcode, "41jvhdm24" );
		::sprintf( (char *)tmp.sendOutTime, "" );
		tmp.transPrice=0;
		::sprintf( (char *)tmp.limitTime, "" );
		::sprintf( (char *)tmp.payWay, "" );
		::sprintf( (char *)tmp.publishTime, "" );
		::sprintf( (char *)tmp.publisher, "" );
		::sprintf( (char *)tmp.telphone, "13394382189" );
		::sprintf( (char *)tmp.notes, "��ƴ��" );
		m_GSDetailMgr.AddOneItem(tmp);

	}
	m_GSDetailMgr.DisconnectFile();
}
void CmakeDataFiles::makeGoodsSource()
{
	m_goodSourceMgr.ConnectToFile();
	if (m_goodSourceMgr.GetCount()<1)
		//if (1==2)
	{
		GoodsSource tmp;

		::sprintf( (char *)tmp.code, "GDFS000001" );
		::sprintf( (char *)tmp.goods_name, "����" );
		::sprintf( (char *)tmp.total_size, "500��" );
		::sprintf( (char *)tmp.address, "��ɽ��˳���������豸���޹�˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000002" );
		::sprintf( (char *)tmp.goods_name, "��ש" );
		::sprintf( (char *)tmp.total_size, "40��" );
		::sprintf( (char *)tmp.address, "��ӯ�Ƶ� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS00003" );
		::sprintf( (char *)tmp.goods_name, "��֯��" );
		::sprintf( (char *)tmp.total_size, "10��" );
		::sprintf( (char *)tmp.address, "�����������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000004" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "18��" );
		::sprintf( (char *)tmp.address, "��͵��� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000005" );
		::sprintf( (char *)tmp.goods_name, "����" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "��ɽ��˳����·���ֲ����޹�˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000006" );
		::sprintf( (char *)tmp.goods_name, "���Ͽ���" );
		::sprintf( (char *)tmp.total_size, "38��" );
		::sprintf( (char *)tmp.address, "��ͨ��˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000007" );
		::sprintf( (char *)tmp.goods_name, "���" );
		::sprintf( (char *)tmp.total_size, "15��" );
		::sprintf( (char *)tmp.address, "��ɽ�������� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000008" );
		::sprintf( (char *)tmp.goods_name, "�ٻ�" );
		::sprintf( (char *)tmp.total_size, "32��" );
		::sprintf( (char *)tmp.address, "��ɽ�ж����������޹�˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000009" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "20��" );
		::sprintf( (char *)tmp.address, "˳���������������޹�˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000010" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "4��" );
		::sprintf( (char *)tmp.address, "��ԼҾ�ó�׹�˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000011" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "24��" );
		::sprintf( (char *)tmp.address, "�˰����� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000012" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "42��" );
		::sprintf( (char *)tmp.address, "��˳���� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000013" );
		::sprintf( (char *)tmp.goods_name, "���" );
		::sprintf( (char *)tmp.total_size, "25��" );
		::sprintf( (char *)tmp.address, "��ɽ��¡������Ͻ����޹�˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000014" );
		::sprintf( (char *)tmp.goods_name, "��ש" );
		::sprintf( (char *)tmp.total_size, "40��" );
		::sprintf( (char *)tmp.address, "���ƹ�˾ �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000015" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "3��" );
		::sprintf( (char *)tmp.address, "��˳�ز� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000016" );
		::sprintf( (char *)tmp.goods_name, "��ɴ" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "������� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000017" );
		::sprintf( (char *)tmp.goods_name, "�ػ�" );
		::sprintf( (char *)tmp.total_size, "50��" );
		::sprintf( (char *)tmp.address, "��ӯ�Ƶ� �����Ϣ��" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000018" );
		::sprintf( (char *)tmp.goods_name, "�ֹ�" );
		::sprintf( (char *)tmp.total_size, "14��" );
		::sprintf( (char *)tmp.address, "�·���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000019" );
		::sprintf( (char *)tmp.goods_name, "����" );
		::sprintf( (char *)tmp.total_size, "25��" );
		::sprintf( (char *)tmp.address, "ϸ����������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000020" );
		::sprintf( (char *)tmp.goods_name, "��" );
		::sprintf( (char *)tmp.total_size, "19��" );
		::sprintf( (char *)tmp.address, "������������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000021" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "24��" );
		::sprintf( (char *)tmp.address, "������������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000022" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "15��" );
		::sprintf( (char *)tmp.address, "���޹�����������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000023" );
		::sprintf( (char *)tmp.goods_name, "����ʯ" );
		::sprintf( (char *)tmp.total_size, "38��" );
		::sprintf( (char *)tmp.address, "˳������������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000024" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "������������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000025" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "14��" );
		::sprintf( (char *)tmp.address, "ɳ���մɲִ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000026" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "33��" );
		::sprintf( (char *)tmp.address, "��ش���ҵ��������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000027" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "�����մ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000028" );
		::sprintf( (char *)tmp.goods_name, "��ש" );
		::sprintf( (char *)tmp.total_size, "����" );
		::sprintf( (char *)tmp.address, "�ִ������ֲ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000029" );
		::sprintf( (char *)tmp.goods_name, "����" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "�㷢.����˹��������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000032" );
		::sprintf( (char *)tmp.goods_name, "�ٻ�" );
		::sprintf( (char *)tmp.total_size, "33��" );
		::sprintf( (char *)tmp.address, "���ֹ�����������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000031" );
		::sprintf( (char *)tmp.goods_name, "��ש" );
		::sprintf( (char *)tmp.total_size, "45��" );
		::sprintf( (char *)tmp.address, "��ش���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000032" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "�񶫸�����������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000033" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "����ͨ��������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000034" );
		::sprintf( (char *)tmp.goods_name, "�������Ϲ�" );
		::sprintf( (char *)tmp.total_size, "14��" );
		::sprintf( (char *)tmp.address, "����ִ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000035" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "����������ɽ��������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000036" );
		::sprintf( (char *)tmp.goods_name, "�������Ϲ�" );
		::sprintf( (char *)tmp.total_size, "16��" );
		::sprintf( (char *)tmp.address, "�»������������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000037" );
		::sprintf( (char *)tmp.goods_name, "��ש" );
		::sprintf( (char *)tmp.total_size, "40��" );
		::sprintf( (char *)tmp.address, "��ɽ�гǱ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000038" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "8��" );
		::sprintf( (char *)tmp.address, "�°���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000039" );
		::sprintf( (char *)tmp.goods_name, "�ֹ�" );
		::sprintf( (char *)tmp.total_size, "37��" );
		::sprintf( (char *)tmp.address, "�����մ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000040" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "10��" );
		::sprintf( (char *)tmp.address, "������������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000041" );
		::sprintf( (char *)tmp.goods_name, "����" );
		::sprintf( (char *)tmp.total_size, "8��" );
		::sprintf( (char *)tmp.address, "����������������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000042" );
		::sprintf( (char *)tmp.goods_name, "�Ҿ�" );
		::sprintf( (char *)tmp.total_size, "20��" );
		::sprintf( (char *)tmp.address, "���͸����ִ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000043" );
		::sprintf( (char *)tmp.goods_name, "����" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "�Ϸ��ز���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000044" );
		::sprintf( (char *)tmp.goods_name, "����ˮ��" );
		::sprintf( (char *)tmp.total_size, "15��" );
		::sprintf( (char *)tmp.address, "��־��������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000045" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "23��" );
		::sprintf( (char *)tmp.address, "�غ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000046" );
		::sprintf( (char *)tmp.goods_name, "�޻���" );
		::sprintf( (char *)tmp.total_size, "35��" );
		::sprintf( (char *)tmp.address, "��ͨ��������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000047" );
		::sprintf( (char *)tmp.goods_name, "����" );
		::sprintf( (char *)tmp.total_size, "26��" );
		::sprintf( (char *)tmp.address, "���԰�ִ���������" );
		m_goodSourceMgr.AddOneItem(tmp);

		::sprintf( (char *)tmp.code, "GDFS000048" );
		::sprintf( (char *)tmp.goods_name, "�豸" );
		::sprintf( (char *)tmp.total_size, "2��" );
		::sprintf( (char *)tmp.address, "�ǲ�������������" );
		m_goodSourceMgr.AddOneItem(tmp);
	}
	m_goodSourceMgr.DisconnectFile();
}

		