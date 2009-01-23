// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once
// Windows ヘッダー ファイル:
#include <windows.h>
// C ランタイム ヘッダー ファイル
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmsystem.h>
#include <process.h>
#include <conio.h>
#include <math.h>
#include <limits.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cstddef>
//#include <crtdbg.h>

//俺デ
#define OREDEBUG 1


#ifdef OREDEBUG
	#define NEW new(__FILE__, __LINE__ )
	//#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

	//#define TRACE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }
	#define TRACE(X)
	//#define TRACE2(X) {std::stringstream ss; ss << "[別スレッド]" << X; GgafCore::GgafLogger::write(ss.str()); }
	#define TRACE2(X)
	//ダンプ出力用
	#define _TRACE_(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }
	//デバッグ用
	#define _TRACEORE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }

#else
	#define NEW new

	#define TRACE(X)
	#define TRACE2(X)
	//ダンプ出力用
	#define _TRACE_(X)
	//デバッグ用
	#define _TRACEORE(X)

#endif

//メモリ解放用マクロ
//NULLかもしれない delete
#define DELETE_POSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULLかもしれない delete[]
#define DELETEARR_POSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULLかもしれない Release()
#define RELEASE_POSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULLはありえない delete
#define DELETE_IMPOSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< #POINTER << " の解放を無視しましたが、本来ここでNULLであるべきでは無い。要調査"; GgafCore::GgafLogger::write(ss.str()); (POINTER)=NULL; }  }
//NULLはありえない delete[]
#define DELETEARR_IMPOSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETEARR_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< #POINTER << "の解放を無視しましたが、本来ここでNULLであるべきでは無い。要調査"; GgafCore::GgafLogger::write(ss.str()); (POINTER)=NULL; }  }
//NULLはありえない Release()
#define RELEASE_IMPOSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else {std::stringstream ss; ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< #POINTER << "の解放を無視しましたが、本来ここでNULLであるべきでは無い。要調査"; GgafCore::GgafLogger::write(ss.str());  (POINTER)=NULL; }  }


#define MAX_HEADACTOR_PER_SCENE 16

typedef unsigned int actorkind;
#define throw_GgafCriticalException(X)

class GgafActor;
class GgafObject;
class GgafGod;
class GgafLogger;

#include "GgafLogger.h"
#include "GgafObject.h"

#include "GgafNode.hpp"
#include "GgafElement.hpp"
#include "GgafActor.h"
#include "GgafGod.h"

//ふふふhohohoho
//MAINdesu

