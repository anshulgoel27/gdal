/*****************************************************************************
*       Copyright 1999, 2020 Precisely.
*       All  rights reserved.
*
*       This document contains unpublished, confidential, and proprietary
*       information of Precisely. No disclosure or use of any portion of
*       the contents of this document may be made without the express
*       written consent of Precisely.
*
* $Workfile:  $
* $Revision:  $
* $Modtime:  $
*
* $Log:  $
*
* Description: EFAL
*
*****************************************************************************/

#ifndef EFALAPI_H
#define EFALAPI_H
#ifndef EFAL_STRUCTS_ONLY

#if defined(_MSC_VER)
#pragma once
#endif
#include "MIDefs.h"

#if ELLIS_OS_IS_WINOS
#include <windows.h>

#define dynlib HMODULE
#define dynlib_open(path) LoadLibraryA(path)
#define dynlib_sym(handle,symbol) GetProcAddress(handle,symbol)
#define dynlib_close(handle) FreeLibrary(handle)

#else

#include <dlfcn.h>

#define HMODULE void*
#define LoadLibrary(path) dlopen(path, RTLD_LAZY | RTLD_LOCAL)
#define GetProcAddress(handle,symbol) dlsym(handle,symbol)
#define FreeLibrary(handle) dlclose(handle)

#define dynlib void*
#define dynlib_open(path) dlopen(path, RTLD_LAZY | RTLD_LOCAL)
#define dynlib_sym(handle,symbol) dlsym(handle,symbol)
#define dynlib_close(handle) dlclose(handle)
#define dynlib_error(handle) dlerror()
#define __cdecl 

#if !defined(stricmp)
#define stricmp strcasecmp 
#endif
#if !defined(strnicmp)
#define strnicmp strncasecmp 
#endif
#if !defined(wcscpy_s)
#define wcscpy_s(dest,destsz,src) wcscpy(dest,src)
#endif
#endif


#if ELLIS_OS_ISUNIX
#define EFALFUNCTION
#define EFALCLASS   class 
#elif defined MICOMPONENT_STATIC
#define EFALFUNCTION
#define EFALCLASS   class 
#elif defined __EFALDLL__
#define EFALFUNCTION __declspec(dllexport)
#define EFALCLASS   class __declspec(dllexport)
#else
#define EFALFUNCTION __declspec(dllimport)
#define EFALCLASS   class  __declspec(dllimport)
#endif // MICOMPONENT_STATIC

typedef MI_UINT64 EFALHANDLE;
// Callback type for getting the custom EFAL string resources from client application.
typedef const wchar_t* (ResourceStringCallback)(const wchar_t* resourceStringName);

// Callbacks for OGC WKT
typedef const wchar_t *  (CoordSys_PRJ2OGCWKT_Callback)(const wchar_t * szPRJString);
typedef const wchar_t *  (CoordSys_OGCWKT2PRJ_Callback)(const wchar_t * szWKTString);

#endif

enum EFALSTYLETYPE : int
{
	SYMBOL,
	AREA,
	LINE,
	TEXT
};


enum EFALSYMBOLTYPE : int
{
	VECTORSYMBOL,
	FONTSYMBOL,
	CUSTOMSYMBOL,
};

/* ***********************************************************
* Date & Time structs
* ***********************************************************
*/
typedef struct EFALDATE
{
	int year;
	int month;
	int day;
}EFALDATE;

typedef struct EFALTIME
{
	int hour;
	int minute;
	int second;
	int millisecond;
}EFALTIME;

typedef struct EFALDATETIME
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisecond;
}EFALDATETIME;

typedef struct EFALSYMBOL
{
	short symbolCode;
	MI_UINT32 color;
	MI_INT16 pointSize;
}EFALSYMBOL, EFALVECTORSYMBOL;


/*
0	Plain
1	Bold
16	Border (black outline)
32	Drop Shadow
256	Halo (white outline)
To specify two or more style attributes, add the values from the left column.
For example, to specify both the Bold and the Drop Shadow attributes, use a
fontstyle value of 33. Border and Halo are mutually exclusive.
*/

typedef struct EFALFONTSYMBOL
{
	EFALSYMBOL symbol;
	wchar_t fontname[260];
	int fontstyle;
	MI_INT16 angle;
}EFALFONTSYMBOL;

/*
0	The Show Background, the Apply Color, and the Display at Actual Size settings are off; the symbol appears in its default state at the point size specified by the size parameter.White pixels in the bitmap are displayed as transparent, allowing whatever is behind the symbol to show through.
1	The Show Background setting is on; white pixels in the bitmap are opaque.
2	The Apply Color setting is on; non - white pixels in the bitmap are replaced with the symbol's color setting.
3	Both Show Background and Apply Color are on.
4	The Display at Actual Size setting is on; the bitmap image is rendered at its native width and height in pixels.
5	The Show Background and Display at Actual Size settings are on.
7	The Show Background, the Apply Color, and the Display at Actual Size settings are on.
*/
typedef struct EFALCUSTOMSYMBOL
{
	wchar_t filename[260];
	MI_UINT32 color;
	MI_INT16 size; // from 1 to 48
	MI_INT16 effStyle; // See above.
}EFALCUSTOMSYMBOL;

typedef struct EFALBRUSH
{
	int pattern;
	MI_UINT32 foreColor;
	MI_UINT32 backColor;
	bool transparent;
}EFALBRUSH;

typedef struct EFALPEN
{
	int pattern;
	MI_INT16 width;
	MI_UINT32 color;
}EFALPEN;

typedef struct EFALFONT
{
	wchar_t fontname[260];
	bool bold;
	bool italic;
	bool underline;
	bool strikeout;
	bool halo;
	bool allcaps;
	MI_UINT32 foreColor;
	MI_UINT32 backColor;
	double height;
}EFALFONT;

typedef struct EFALREGIONSTYLE {
	EFALBRUSH brush;
	EFALPEN pen;
}EFALREGIONSTYLE;

typedef struct EFALLINESTYLE {
	EFALPEN linePen;
}EFALLINESTYLE;

typedef struct EFALSYMBOLSTYLE {
	EFALSYMBOLTYPE symbolType;
	union {
		EFALVECTORSYMBOL vectorSymbol;
		EFALFONTSYMBOL fontSymbol;
		EFALCUSTOMSYMBOL customSymbol;
	};
}EFALSYMBOLSTYLE;

typedef struct EFALTEXTSTYLE {
	EFALFONT font;
}EFALTEXTSTYLE;

typedef struct EFALSTYLE
{
	EFALSTYLETYPE type;
	union {
		EFALREGIONSTYLE areaStyle;
		EFALLINESTYLE lineStyle;
		EFALSYMBOLSTYLE symbolStyle;
		EFALTEXTSTYLE textStyle;
	};
}EFALSTYLE;

#endif

