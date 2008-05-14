
// ATTENTION : ce fichier doit etre inclus AVANT tout new mais APRES les includes systemes

#ifndef	CRTDBG_H__
#define	CRTDBG_H__

#ifdef WIN32
	#ifdef	_DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
		#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__ )
		#define new DEBUG_NEW
	#endif
#else
	#define _CrtDumpMemoryLeaks()	((int)0)
	#define _CrtSetBreakAlloc(a)	((long)0)
#endif

#endif	// !CRTDBG_H__
