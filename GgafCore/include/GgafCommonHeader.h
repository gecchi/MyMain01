#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_

/**
 * Ggafライブラリヘッダー郡ヘッダー
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
#ifdef _MSC_VER
    #ifdef _DEBUG
        #define _CRTDBG_MAP_ALLOC
        #define _CRTDBG_MAP_ALLOC_NEW
    #endif
    #if _MSC_VER < 1500
        #define override
    #endif
#else
   #define _WIN32_IE 0x0300
   #define override
#endif

#define _HAS_ITERATOR_DEBUGGING 0

// Windows ヘッダー ファイル:
#include <windows.h>
#include <stdio.h>


#include <stdlib.h>
#ifdef _MSC_VER
    #ifdef _DEBUG
        #include <crtdbg.h>
    #endif
#endif

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
#include <stack>
#include <sstream>
#include <cstddef>

#ifdef _MSC_VER
#else
#include "sal.h"
#endif

//自分用デバッグビルド(コメントを外せば使用可能)
#define MY_DEBUG 1


#ifdef MY_DEBUG
//自分用デバッグビルドの場合

    #ifdef _MSC_VER
        #ifdef _DEBUG
            //自分用デバッグ かつ VC++の デバッグビルド時
            //VC++のリーク検出を仕込む
            #define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__ )
        #else
            //自分用デバッグ かつ VC++のリリースビルド時
            #define NEW new
        #endif
    #else
        //GCC で自分用デバッグビルド時
        //GCC用のリーク検出を仕込む
        #include "DetectMemoryLeaks.h"
        #define NEW new(__FILE__, __LINE__)
    #endif

    //#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

    /** コンストラクタ、主要メソッド、デストラクタ関連ログ */
    //#define TRACE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE(X)

    /** 工場関連関連ログ */
    //#define TRACE2(X) {std::stringstream ss; ss << "[別スレッド]" << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE2(X)

    /** 資源マネージャ、コネクション関連ログ */
    //#define TRACE3(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE3(X)

    /** エフェクト、パス、Draw関連ログ */
    //#define TRACE4(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE4(X)

    /** ８分木、あたり判定関連ログ */
    //#define TRACE5(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE5(X)
    //#define TEXT5(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss); }
    #define TEXT5(X)

    /** デバッグ用通常ログ */
    #define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    //#define _TRACE_(X)
    #define _TEXT_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss); }
    //#define _TEXT_(X)

    //メモリ解放用マクロ
    /** NULLかどうか不明なdelete */
    #define DELETE_POSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete (POINTER); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }
    /** NULLかどうか不明なdelete[] */
    #define DELETEARR_POSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete[] (POINTER); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }
    /** NULLかどうか不明なRelease() */
    #define RELEASE_POSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            int rc = (POINTER)->Release(); \
            if (rc > 0) { \
                std::stringstream ss; \
                ss << "RELEASE_POSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、まだ解放されません。参照カウンタ="<<rc; \
                GgafCore::GgafLogger::writeln(ss); \
            } \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }
    /** NULLはありえないdelete */
    #define DELETE_IMPOSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete (POINTER); \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "DELETE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< \
                  #POINTER << " の解放をやむなく無視しました。本来は、ここでNULLになってこと自体おかしい。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    }
    /** NULLはありえないdelete[] */
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete[] (POINTER); \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "DELETEARR_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< \
                  #POINTER << "の解放をやむなく無視しました。本来は、ここでNULLになってこと自体おかしい。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    }
    /** NULLはありえないRelease() */
    #define RELEASE_IMPOSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            int rc = (POINTER)->Release(); \
            if (rc > 0) { \
                std::stringstream ss; \
                ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、まだ解放されません。参照カウンタ="<<rc; \
                GgafCore::GgafLogger::writeln(ss); \
            } \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< \
                  #POINTER << "のリリースをやむなく無視しました。本来は、ここでNULLになってこと自体おかしい。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    }
    /** 自明で検査不要の何も言わないRelease() */
    #define RELEASE_SAFETY(POINTER) { \
        if (POINTER) { \
            (POINTER)->Release(); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }

#else
//自分用リリースビルド時

    #ifdef _MSC_VER
        #ifdef _DEBUG
            //自分用リリースビルド時 かつ VC++の デバッグビルド時
            //VC++のリーク検出あり（にしておこう）
            #define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__ )
        #else
            //自分用リリースビルド時 VC++の リリースビルド時
            #define NEW new
        #endif
    #else
        //GCC で自分用リリースビルド時
        #define NEW new
    #endif

    #define TRACE(X)
    #define TRACE2(X)
    #define TRACE3(X)
    #define TRACE4(X)
    #define TRACE5(X)
    #define TEXT5(X)
    #define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    //#define _TRACE_(X)
    #define _TEXT_(X)
    #define _TRACEORE(X)

    //メモリ解放用マクロ
    /** NULLかもしれない delete */
    #define DELETE_POSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULLかもしれない delete[] */
    #define DELETEARR_POSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULLかもしれない Release() */
    #define RELEASE_POSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULLはありえない delete */
    #define DELETE_IMPOSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULLはありえない delete[] */
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULLはありえない Release() */
    #define RELEASE_IMPOSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** 自明で検査不要の何も言わないRelease() */
    #define RELEASE_SAFETY(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }

#endif





//#define MAX_GROUPACTOR_PER_SCENE 16

typedef DWORD actorkind;

#define Obj_GgafScene             (0x1)              //&B 00000000 00000000 00000000 00000001
#define Obj_GgafMainScene         (0x2)              //&B 00000000 00000000 00000000 00000010
#define Obj_GgafSayonaraScene     (0x4)              //&B 00000000 00000000 00000000 00000100
#define Obj_GgafUniverse          (0x8)              //&B 00000000 00000000 00000000 00001000

#define Obj_GgafActor                   (0x1)              //&B 00000000 00000000 00000000 00000001
#define Obj_GgafMainActor               (0x2)              //&B 00000000 00000000 00000000 00000010
#define Obj_GgafDummyActor              (0x4)              //&B 00000000 00000000 00000000 00000100
#define Obj_GgafLordActor               (0x8)              //&B 00000000 00000000 00000000 00001000
#define Obj_GgafGroupActor              (0x10)             //&B 00000000 00000000 00000000 00010000
#define Obj_GgafSayonaraActor           (0x20)             //&B 00000000 00000000 00000000 00100000
#define Obj_GgafActorDispatcher         (0x40)             //&B 00000000 00000000 00000000 01000000


namespace GgafCore {
class GgafUtil;
class GgafRepeatSeq;
class GgafObject;
class GgafException;
class GgafCriticalException;
class GgafLogger;
class GgafGod;

template<class T>
class GgafResourceConnection;

template<class T>
class GgafResourceManager;

template<class T>
class GgafNode;

template<class T>
class GgafElement;

template<class T>
class GgafLinkedListRing;


class GgafFactory;
class GgafGarbageBox;

class GgafScene;
class GgafSayonaraScene;
class GgafActor;
class GgafStatus;
class GgafSayonaraActor;
class GgafMainActor;
class GgafDummyActor;
class GgafUniverse;
class GgafMainScene;
class GgafLordActor;
class GgafGroupActor;
class GgafActorDispatcher;

class GgafOrder;

class GgafProperties;

class GgafLinearOctree;
class GgafLinearOctreeSpace;
class GgafLinearOctreeElem;

class GgafCurtain;
}

#ifdef _MSC_VER

#else
//GCCの場合sal.hで何故かNULL が __null で 未定義のため強制的に再定義(ナンノコッチャ)
#define NULL 0
#endif

#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/exception/GgafException.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/core/util/GgafLogger.h"
#include "jp/ggaf/core/GgafProperties.h"
#include "jp/ggaf/core/GgafGod.h"

#include "jp/ggaf/core/GgafResourceConnection.hpp"
#include "jp/ggaf/core/GgafResourceManager.hpp"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/GgafGarbageBox.h"

#include "jp/ggaf/core/GgafNode.hpp"
#include "jp/ggaf/core/GgafElement.hpp"
#include "jp/ggaf/core/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/scene/GgafSayonaraScene.h"
#include "jp/ggaf/core/scene/GgafMainScene.h"
#include "jp/ggaf/core/actor/GgafActor.h"

#include "jp/ggaf/core/actor/GgafSayonaraActor.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafDummyActor.h"
#include "jp/ggaf/core/scene/GgafUniverse.h"
#include "jp/ggaf/core/actor/GgafLordActor.h"
#include "jp/ggaf/core/actor/GgafGroupActor.h"
#include "jp/ggaf/core/actor/GgafActorDispatcher.h"
#include "jp/ggaf/core/GgafOrder.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearOctreeSpace.h"
#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"
#include "jp/ggaf/core/util/GgafCurtain.h"
#endif /*GGAFCOMMONHEADER_H_*/
