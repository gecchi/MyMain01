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
        #include <crtdbg.h>
    #endif
    #if _MSC_VER < 1500
        #define override
    #endif
    #if _MSC_VER < 1600
        #define nullptr 0
    #endif
#endif


#define _HAS_ITERATOR_DEBUGGING 0


#ifdef _MSC_VER
    typedef __int8            int8_t;
    typedef __int16           int16_t;
    typedef __int32           int32_t;
    typedef __int64           int64_t;
    typedef unsigned __int8   uint8_t;
    typedef unsigned __int32  uint16_t;
    typedef unsigned __int32  uint32_t;
    typedef unsigned __int64  uint64_t;
#else
    #include <cstdint>
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

    //メモリ解放用マクロ
    #include "jp/ggaf/core/util/GgafLogger.h"
    /** nullptrかどうか不明なdelete */
    #define GGAF_DELETE_NULLABLE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    } while(0)
    /** nullptrかどうか不明なdelete[] */
    #define GGAF_DELETEARR_NULLABLE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete[] (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    } while(0)

    /** nullptrはありえないdelete */
    #define GGAF_DELETE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "GGAF_DELETE(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にnullptrであるため "<< \
                  #POINTER << " の解放をやむなく無視しました。本来は、ここでnullptrになってこと自体おかしいのでは？。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    } while(0)
    /** nullptrはありえないdelete[] */
    #define GGAF_DELETEARR(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete[] (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "GGAF_DELETEARR(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にnullptrであるため "<< \
                  #POINTER << "の解放をやむなく無視しました。本来は、ここでnullptrになってこと自体おかしいのでは？。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    } while(0)
    /** nullptrかどうか不明なRelease() */
    #define GGAF_RELEASE_NULLABLE(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "GGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、既に参照カウンタ0です。Release() は行いませんでした。調査が必要です！"; \
                GgafCore::GgafLogger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "GGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          #POINTER << "は、まだ解放されません。参照カウンタ="<<rc; \
                    GgafCore::GgafLogger::writeln(ss); \
                } \
            } \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    } while(0)
    /** nullptrはありえないRelease() */
    #define GGAF_RELEASE(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、既に参照カウンタ0です。リリースをやむなく無視しました。調査が必要です！"; \
                GgafCore::GgafLogger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          #POINTER << "は、まだ解放されません。参照カウンタ="<<rc; \
                    GgafCore::GgafLogger::writeln(ss); \
                } \
            } \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にnullptrであるため "<< \
                  #POINTER << "のリリースをやむなく無視しました。本来は、ここでnullptrになってこと自体おかしいのでは？。調査せよ。"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    } while(0)
    /** 自明で検査不要の何も言わないRelease() */
    #define GGAF_RELEASE_BY_FROCE(POINTER) do { \
        if (POINTER) { \
            (POINTER)->Release(); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    } while(0)

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


    //メモリ解放用マクロ
    /** nullptrかもしれない delete */
    #define GGAF_DELETE_NULLABLE(POINTER)       do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrかもしれない delete[] */
    #define GGAF_DELETEARR_NULLABLE(POINTER)    do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrかもしれない Release() */
    #define GGAF_RELEASE_NULLABLE(POINTER)      do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrはありえない delete */
    #define GGAF_DELETE(POINTER)     do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrはありえない delete[] */
    #define GGAF_DELETEARR(POINTER)  do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrはありえない Release() */
    #define GGAF_RELEASE(POINTER)    do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** 自明で検査不要の何も言わないRelease() */
    #define GGAF_RELEASE_BY_FROCE(POINTER)       do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)

#endif

#ifdef MY_DEBUG
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

# else

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
    //#define _TRACEORE(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
#endif
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


//#define HASHVAL(X)  const static uint32_t X=__LINE__*3+/*'"*/__TIME__"

/** ハッシュ数値 */
typedef uint64_t hashval;
/** アクターの種類 */
typedef uint32_t actorkind;
/** フレーム(アプリケーション時間) */
typedef uint32_t frame;
#define MAX_FRAME (UINT_MAX)

#define Obj_SceneBit              (0x80000000)       //0b 10000000 00000000 00000000 00000000

#define Obj_GgafScene             (0x80000001)       //0b 10000000 00000000 00000000 00000001
#define Obj_GgafMainScene         (0x80000002)       //0b 10000000 00000000 00000000 00000010
#define Obj_GgafDisusedScene      (0x80000004)       //0b 10000000 00000000 00000000 00000100
#define Obj_GgafUniverse          (0x80000008)       //0b 10000000 00000000 00000000 00001000

#define Obj_GgafActor             (0x1)              //0b 00000000 00000000 00000000 00000001
#define Obj_GgafMainActor         (0x2)              //0b 00000000 00000000 00000000 00000010
#define Obj_GgafDummyActor        (0x4)              //0b 00000000 00000000 00000000 00000100
#define Obj_GgafSceneDirector     (0x8)              //0b 00000000 00000000 00000000 00001000
#define Obj_GgafGroupHead         (0x10)             //0b 00000000 00000000 00000000 00010000
#define Obj_GgafDisusedActor      (0x20)             //0b 00000000 00000000 00000000 00100000
#define Obj_GgafActorDepository   (0x40)             //0b 00000000 00000000 00000000 01000000
#define Obj_GgafFormation         (0x80)             //0b 00000000 00000000 00000000 10000000

#define P_GOD (GgafCore::GgafGod::_pGod)
#define P_UNIVERSE (P_GOD->_pUniverse)

//前方宣言(forward declaration)
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
class GgafSceneDirector;
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
class GgafQuery;
}

#endif /*GGAFCOMMONHEADER_H_*/
