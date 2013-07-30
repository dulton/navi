/************************************************************************/
/* 
�����ļ���ԭʼ��ini��ʽ��
[COMMON]
ROOTPATH=
RESPATH=\Res\
ATTRSPATH=\attrs\
CODESPATH=\codes\
FONTSPATH=\fonts\
NAMESPATH=\names\
SNDSPATH=\snds\
[800x480]
HOOKSPATH=\res\hooks\
IMAGESPATH=\res\images\
MAPSTYLEPATH=\res\mapstyle\
[480x272]
.....
��������ת���ɶ����Ƶĸ�ʽ
*/
/************************************************************************/
#ifndef _UEBASE_CONFIGTOBIN_H
#define _UEBASE_CONFIGTOBIN_H
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Portable definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

#ifndef _UEBASE_PATHBASIC_H
#include "pathbasic.h"
#endif
#ifndef _UEBASE_FILEBASIC_H
#include "filebasic.h"
#endif

namespace UeBase {

class UEBASE_CLASS CPathConfig
{
public:
  #define  COMMON_COUNT  9
  #define  RESOLUTION_COUNT   5
  enum CommonPathKey : unsigned char
  {
    CPK_RootPath = 0,
    CPK_ResPath,
    CPK_AttrsPath,
    CPK_CodesPath,
    CPK_FontsPath,
    CPK_NamesPath,
    CPK_SndsPath,
    CPK_MapsPath,
    CPK_UserPath,
    CPK_END
  };
  
  enum ResolutionPathKey : unsigned char
  {
    RPK_HooksPath = 0,
    RPK_ImagesPath,
    RPK_MapstylePath,
    RPK_END
  };

  enum SectionKey  : unsigned char
  {
    SK_800_480 = 0,
    SK_480_272,
    SK_480_234,
    SK_400_234,
    SK_320_240,
    SK_COMMON,
    SK_END
  };

  const static int MAXPATHLENGTH = 128;
  //�������ļ��Ľṹ��ͨ��������ֵ�������Ӧ��Ŀ¼
  struct PathStruct 
  {
    unsigned char    sectionKey;
    unsigned char    pathKey;        
    TCHAR            pathValue[MAXPATHLENGTH];
    PathStruct() { ::memset(this, 0, sizeof(PathStruct));}
  };
  
public:
  
  CPathConfig(void);
  ~CPathConfig(void);
  
  /**
    * \brief ��ȡͨ�õ����õ�ֵ���������ݷֱ������ֵ�Ŀ¼
    * \param pathKey��CommonPathKey��ö��ֵ
   */
  static tstring GetCommonPath(unsigned char pathKey, const TCHAR *fileName = _T("ueconfig.dat"));

  /**
    * \brief ��ȡ��Ӧ�ķֱ��ʵ�ֵ���ֱ���ͨ��SetResolutionRatio���á�
    * \param pathKey��ResolutionPathKey��ö��ֵ
   */
  static tstring GetResolutionPath(unsigned char pathKey, const TCHAR *fileName = _T("ueconfig.dat"));

  //��ȡ�����ļ��ĸ�Ŀ¼��û����������GetModulePath����ȡ��
  /**
    * \brief ��ȡ�����ļ��ĸ�Ŀ¼��û����������GetModulePath����ȡ��
   */
  static tstring GetRootPath(const TCHAR *fileName = _T("ueconfig.dat"));

  /**
    * \brief ���÷ֱ��ʵ�����
    * \param type�� SectionKey ö�����ֵ��������SK_COMMON
   */
  static void SetResolutionRatio(unsigned char type);
private:
  struct ResolutionPath 
  {
    TCHAR   hooksPath[MAXPATHLENGTH];
    TCHAR   imagesPath[MAXPATHLENGTH];
    TCHAR   mapstylePath[MAXPATHLENGTH];
  };
private:
  static tstring GetPath(unsigned char sectionKey, unsigned char pathkey, const TCHAR *fileName = _T("ueconfig.dat"));
  static void LoadPath(const TCHAR *fileName);
private:
  //��¼��ǰ�ֱ������͡�
  static unsigned char m_resolutionRatio;
  
  static TCHAR m_commonPath[COMMON_COUNT][MAXPATHLENGTH];
  static ResolutionPath m_resolutionPath[RESOLUTION_COUNT];
  static bool m_isLoad;
};
}
#endif