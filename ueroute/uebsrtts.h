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
#ifndef _UEROUTE_UEBSRTTS_H
#define _UEROUTE_UEBSRTTS_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to its parent
#ifndef _UEROUTE_UETTS_H
#include "uetts.h"
#endif

// Refer to path basic definition
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif

// Refer to string basic definition
#ifndef _UEBASE_STRINGBASIC_H
#include "uebase\stringbasic.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning( disable: 4275 )  // Deprecated function calling

namespace UeRoute
{
  /**
  * Default TTS implementation using TW side product
  **/
  class UEROUTE_CLASS CUeBsrTTS : public CUeTTS
  {
  public:
    //
    //
    //
    /**
    *
    */
    CUeBsrTTS();

    /**
    *
    */
    virtual ~CUeBsrTTS();

  public:
    //
    //
    //
    /**
    *
    */
    virtual unsigned int Prepare(bool isReady = true);

    /**
    *
    */
    virtual unsigned int TextOut(char *str);

  private:
    //
    void *m_handle;

    //
    const CPathBasic &m_pathBasic;

    //
    const CStringBasic &m_stringBasic;
  };
}

#endif