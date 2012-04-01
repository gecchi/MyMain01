#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_
/**
 * Ggafライブラリヘッダー郡ヘッダー
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */

//MY_DEBUGは自分用のデバッグビルド
#ifdef _DEBUG
    //#undef _DEBUG
    #define MY_DEBUG _DEBUG
#endif


//Windows XP 以上。
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
//GCCの場合、上の２つのシンボルはコンパイラの
//引数で設定する方が無難。

#ifdef _MSC_VER
    #ifdef _DEBUG
        #define _CRTDBG_MAP_ALLOC
        #define _CRTDBG_MAP_ALLOC_NEW
    #endif
    #if _MSC_VER < 1500
        #define override
    #endif
#else
   #define override
#endif

#define _HAS_ITERATOR_DEBUGGING 0

// Windows ヘッダー ファイル:
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

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
#include <list>
#include <stack>
#include <sstream>
#include <cstddef>



#ifdef _MSC_VER
#define __map__ std::map
#else
#define __map__ std::map
//#include <unordered_map>
//#define __map__ unordered_map
#endif

#ifndef _MSC_VER
    //GCCの場合、sal.hを別途インクルード
    #include "sal.h"
    // GCCの場合sal.hで何故かNULL が __null で 未定義のため強制的に再定義(ﾅﾝﾉｺｯﾁｬ)
    // /GgafCore/MSVC_include/sal.h コード内の忘備録メモを参照
    #undef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void*)0)
    #endif
#endif


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
        //#include "jp/ggaf/core/DetectMemoryLeaks.h"
        //#define NEW new(__FILE__, __LINE__)
        #define NEW new
    #endif

    //#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

    /** コンストラクタ、主要メソッド、デストラクタ関連ログ */
    //#define TRACE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE(X)

    /** 工場関連関連ログ */
    //#define TRACE2(X) {std::stringstream ss; ss << "[製造工場]" << X; GgafCore::GgafLogger::writeln(ss); }
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
    #define DELETE_POSSIBLE_NULL(POINTER) do { \
        if (POINTER) { \
            delete (POINTER); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    } while(0)
    /** NULLかどうか不明なdelete[] */
    #define DELETEARR_POSSIBLE_NULL(POINTER) do { \
        if (POINTER) { \
            delete[] (POINTER); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    } while(0)

    /** NULLはありえないdelete */
    #define DELETE_IMPOSSIBLE_NULL(POINTER) do { \
        if (POINTER) { \
            delete (POINTER); \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "DELETE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< \
                  #POINTER << " の解放をやむなく無視しました。本来は、ここでNULLになってこと自体おかしいのでは？。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    } while(0)
    /** NULLはありえないdelete[] */
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER) do { \
        if (POINTER) { \
            delete[] (POINTER); \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "DELETEARR_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< \
                  #POINTER << "の解放をやむなく無視しました。本来は、ここでNULLになってこと自体おかしいのでは？。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    } while(0)
    /** NULLかどうか不明なRelease() */
    #define RELEASE_POSSIBLE_NULL(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "RELEASE_POSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、既に参照カウンタ0です。Release() は行いませんでした。調査が必要です！"; \
                GgafCore::GgafLogger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "RELEASE_POSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          #POINTER << "は、まだ解放されません。参照カウンタ="<<rc; \
                    GgafCore::GgafLogger::writeln(ss); \
                } \
            } \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    } while(0)
    /** NULLはありえないRelease() */
    #define RELEASE_IMPOSSIBLE_NULL(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "RELEASE_POSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、既に参照カウンタ0です。リリースをやむなく無視しました。調査が必要です！"; \
                GgafCore::GgafLogger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          #POINTER << "は、まだ解放されません。参照カウンタ="<<rc; \
                    GgafCore::GgafLogger::writeln(ss); \
                } \
            } \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にNULLであるため "<< \
                  #POINTER << "のリリースをやむなく無視しました。本来は、ここでNULLになってこと自体おかしいのでは？。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    } while(0)
    /** 自明で検査不要の何も言わないRelease() */
    #define RELEASE_SAFETY(POINTER) do { \
        if (POINTER) { \
            (POINTER)->Release(); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    } while(0)
//#define RELEASE_POSSIBLE_NULL(POINTER) {(POINTER) = NULL;}
//#define RELEASE_IMPOSSIBLE_NULL(POINTER) {(POINTER) = NULL;}
//#define RELEASE_SAFETY(POINTER) {(POINTER) = NULL;}

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
    //#define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define _TRACE_(X)
    //#define _TEXT_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss); }
    #define _TEXT_(X)
    #define _TRACEORE(X)

    //メモリ解放用マクロ
    /** NULLかもしれない delete */
    #define DELETE_POSSIBLE_NULL(POINTER)       do { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } } while(0)
    /** NULLかもしれない delete[] */
    #define DELETEARR_POSSIBLE_NULL(POINTER)    do { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } } while(0)
    /** NULLかもしれない Release() */
    #define RELEASE_POSSIBLE_NULL(POINTER)      do { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } } while(0)
    /** NULLはありえない delete */
    #define DELETE_IMPOSSIBLE_NULL(POINTER)     do { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } } while(0)
    /** NULLはありえない delete[] */
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER)  do { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } } while(0)
    /** NULLはありえない Release() */
    #define RELEASE_IMPOSSIBLE_NULL(POINTER)    do { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } } while(0)
    /** 自明で検査不要の何も言わないRelease() */
    #define RELEASE_SAFETY(POINTER)       do { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } } while(0)

#endif


#define MAX_FRAME MAXDWORD

#define DUMP_FLGS   "@"<< \
                    _frame_of_behaving_since_onActive<< \
                    "/"<< \
                    _frame_of_behaving<< \
                    "/"<< \
                    _frame_of_life<< \
                    ","<< \
                    _can_live_flg<<\
                    _was_initialize_flg<< \
                    _was_paused_flg<< \
                    "("<<_was_paused_flg_in_next_frame<<")"<< \
                    ","<< \
                    _is_active_in_the_tree_flg<< \
                    _is_active_flg<< \
                    "-"<< \
                    _will_activate_after_flg<< \
                    "("<<_frame_of_life_when_activation<<")"<< \
                    _on_change_to_active_flg<< \
                    "-"<< \
                    _will_inactivate_after_flg<< \
                    "("<<_frame_of_life_when_inactivation<<")"<< \
                    _on_change_to_inactive_flg<< \
                    ","<< \
                    _will_end_after_flg<< \
                    "("<<(_frame_of_life_when_end==MAX_FRAME ? 0 : _frame_of_life_when_end)<<")"<< \
                    ","<< \
                    _will_mv_first_in_next_frame_flg<< \
                    _will_mv_last_in_next_frame_flg


#define throwGgafCriticalException(X)  do { \
    std::stringstream ss; \
    ss <<__FILE__<<"("<<__LINE__<<") : "<< X; \
    throw GgafCore::GgafCriticalException(ss.str()); \
} while(0)

//#define PP_ADD_0_0 0
//#define PP_ADD_0_1 1
//#define PP_ADD_0_2 2
//#define PP_ADD_0_3 3
//#define PP_ADD_1_0 1
//#define PP_ADD_1_1 2
//
//#define PP_ADD(m, n) PP_ADD_I(m, n)
//#define PP_ADD_I(m, n) PP_ADD_ ## m ## _ ## n

#define DECLARE_CONST(X) const static hashval X = GgafCore::GgafUtil::easy_hash(#X)

/** 共通遅延解放フレーム数 */
#define GGAF_SAYONARA_DELAY (60*15)
//GGAF_SAYONARA_DELAYは全Element共通の解放遅延フレーム数で、
//長めに設定しないと、いろいろ不都合が多い。
//消失後もなお参照が可能とするための仕組みで、
//例えば、消滅後の爆発SE等で、3D効果のためSE発声元座標情報がしばらく必要とか、
//消滅後の消滅アクターに属する子アクターの発射弾が、親アクターの座標を参照しているなど、
//消滅しても、しばらくは残存させなければいけない場合がある。
//基本的に、消滅確定→完全に消失までのフレームの最大フレームを指定する。
//GGAF_SAYONARA_DELAYを短めに設定すると、現在は10秒(60*15)
//消滅後の子の発射弾については、残された発射弾が突然消えるので少し不自然。という程度で問題はない。
//しかし、SEの3D効果は、エラーになるため、SE再生時間の最大フレーム数を設定しなければいけない。
//例えば爆発SEが１分かかるような物が一つでも使用したい場合は、最大の1分(60*60)を設定しなければならない。


//#define DECLARE_CONST(X)  const static UINT32 X=__LINE__*3+/*'"*/__TIME__"


typedef UINT64 hashval;
typedef UINT32 actorkind;
typedef UINT32 frame;


typedef std::map<std::string, std::string> GgafStrMap;


#define Obj_GgafScene             (0x80000001)       //0b 10000000 00000000 00000000 00000001
#define Obj_GgafMainScene         (0x80000002)       //0b 10000000 00000000 00000000 00000010
#define Obj_GgafDisusedScene      (0x80000004)       //0b 10000000 00000000 00000000 00000100
#define Obj_GgafUniverse          (0x80000008)       //0b 10000000 00000000 00000000 00001000

#define Obj_GgafActor             (0x1)              //0b 00000000 00000000 00000000 00000001
#define Obj_GgafMainActor         (0x2)              //0b 00000000 00000000 00000000 00000010
#define Obj_GgafDummyActor        (0x4)              //0b 00000000 00000000 00000000 00000100
#define Obj_GgafDirector          (0x8)              //0b 00000000 00000000 00000000 00001000
#define Obj_GgafGroupHead         (0x10)             //0b 00000000 00000000 00000000 00010000
#define Obj_GgafDisusedActor      (0x20)             //0b 00000000 00000000 00000000 00100000
#define Obj_GgafActorDepository   (0x40)             //0b 00000000 00000000 00000000 01000000
#define Obj_GgafFormation         (0x80)             //0b 00000000 00000000 00000000 10000000

#define P_GOD (GgafCore::GgafGod::_pGod)
#define P_UNIVERSE (P_GOD->_pUniverse)

namespace GgafCore {
class GgafUtil;
class GgafRepeatSeq;
class GgafObject;
class GgafException;
class GgafCriticalException;
class GgafLogger;
class GgafGod;

class CmRandomNumberGenerator;

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
class GgafProgress;
class GgafScene;
class GgafDisusedScene;
class GgafActor;
class GgafStatus;
class GgafDisusedActor;
class GgafMainActor;
class GgafDummyActor;
class GgafUniverse;
class GgafMainScene;
class GgafDirector;
class GgafGroupHead;

class GgafFormation;
class GgafTreeFormation;
class GgafDepositoryFormation;
class GgafActorDepository;
class GgafActorDepositoryStore;

class GgafOrder;
class GgafRgb;

class GgafProperties;

class GgafLinearOctree;
class GgafLinearOctreeSpace;
class GgafLinearOctreeElem;

class GgafCurtain;
}

#include "jp/ggaf/core/util/CmRandomNumberGenerator.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/exception/GgafException.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/core/util/GgafLogger.h"
#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/ggaf/core/GgafProperties.h"
#include "jp/ggaf/core/GgafGod.h"

#include "jp/ggaf/core/GgafResourceConnection.hpp"
#include "jp/ggaf/core/GgafResourceManager.hpp"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/GgafProgress.h"
#include "jp/ggaf/core/GgafNode.hpp"
#include "jp/ggaf/core/GgafElement.hpp"
#include "jp/ggaf/core/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/scene/GgafDisusedScene.h"
#include "jp/ggaf/core/scene/GgafMainScene.h"
#include "jp/ggaf/core/actor/GgafActor.h"

#include "jp/ggaf/core/actor/GgafDisusedActor.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafDummyActor.h"
#include "jp/ggaf/core/scene/GgafUniverse.h"
#include "jp/ggaf/core/actor/GgafDirector.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/actor/ex/GgafFormation.h"
#include "jp/ggaf/core/actor/ex/GgafTreeFormation.h"
#include "jp/ggaf/core/actor/ex/GgafDepositoryFormation.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/core/GgafOrder.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearOctreeSpace.h"
#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"
#include "jp/ggaf/core/util/GgafCurtain.h"


#endif /*GGAFCOMMONHEADER_H_*/
