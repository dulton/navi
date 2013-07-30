#ifndef _UEQUERY_DATAENTRYCTRL_H
#define _UEQUERY_DATAENTRYCTRL_H
//////////////////////////////////////////////////////////////////////////
#ifndef _UEQUERY_QUERYDEF_H
#include "querybasic.h"
#endif
//////////////////////////////////////////////////////////////////////////
namespace UeQuery
{
	class UEQUERY_CLASS CDataEntryCtrl
	{
	public:
		CDataEntryCtrl(void) {};
		virtual ~CDataEntryCtrl(void) {};
		virtual unsigned Open(void) = 0;
		virtual unsigned Close(void) = 0;
		//
		static void Log(const TCHAR *format, ...);
		static void GetDataPath(tstring &tstrPath);
		static void GetDataScrPath(tstring &tstrPath);
		static void GetNameDataPath(tstring &tstrPath);
		//��ȡ������Ŀ
		virtual unsigned GetDistCount(void) const = 0;
		//��ȡ������Ŀ
		virtual unsigned GetDataCount(void) const = 0;
		//��������Ҫ�Ľ������/��ţ���ȡ����
		virtual unsigned GetKind(long docIdx) = 0;
		//��������Ҫ�Ľ������/��ţ���ȡ�������
		virtual unsigned GetCode(long distIdx) const = 0;
		virtual bool GetSubDistIndex(unsigned fDistCode,
			defDistCodeType &sStartIdx,defDistCodeType &sEndIdx) const = 0;
		//��������Ҫ�Ľ������/��ţ���ȡ���Ƴ���
		virtual unsigned GetNameLen(long docIdx)  = 0;
		//��������Ҫ�Ľ������/��ţ�����ѯ���
		virtual SQLRecord *FixRecord(long docIdx) = 0;
		/* ͨ���ĵ�����/��Ż�ȡpoi����
		 * docIdx���ĵ�����
		 * nameLen����poi�ĳ���
		 * pchNameBuffer���������ƵĻ���
		*/
		virtual bool GetEntryName(long docIdx,long nameLen,char *pchNameBuffer) = 0;
	};
}
#endif