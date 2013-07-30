/*
*������������goodssource.db����Դ��Ϣ�� �� sourcedetail.db���������飩�ļ�
*/


#ifndef _UEGUI_GOODSSOURCEMGR_H
#define _UEGUI_GOODSSOURCEMGR_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#ifndef _UEGUI_FILECONTROLLER_H
#include "FileController.h"
#endif

namespace UeGui
{
	class CmakeDataFiles
	{
	public:
		CmakeDataFiles();
		void makeGoodsSource();
		void makeGoodsSourceDetail();
	private:
		CFileController<LogisticsTrackInfo> &m_LogisticsTrackMgr;
		CFileController<GoodsSource> &m_goodSourceMgr;
		CFileController<GoodsSourceDetail> &m_GSDetailMgr;
	};
}

#endif

