#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_
/**
 * ライブラリヘッダー郡ヘッダー
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
    #if _MSC_VER < 1600
    typedef __int8            int8_t;
    typedef __int16           int16_t;
    typedef __int32           int32_t;
    typedef __int64           int64_t;
    typedef unsigned __int8   uint8_t;
    typedef unsigned __int32  uint16_t;
    typedef unsigned __int32  uint32_t;
    typedef unsigned __int64  uint64_t;
    typedef __int8            int_fast8_t;
    typedef __int16           int_fast16_t;
    typedef __int32           int_fast32_t;
    typedef __int64           int_fast64_t;
    typedef unsigned __int8   uint_fast8_t;
    typedef unsigned __int32  uint_fast16_t;
    typedef unsigned __int32  uint_fast32_t;
    typedef unsigned __int64  uint_fast64_t;
    #else
    #include <cstdint>
    #endif
    #define FUNC_NAME __FUNCSIG__
#else
    #include <cstdint>
    #define FUNC_NAME __PRETTY_FUNCTION__
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
    #include "jp/ggaf/core/util/Logger.h"
    /** nullptr はありえない、普通の delete */
    #define GGAF_DELETE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "【警告】GGAF_DELETE(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にnullptrであるため "<< \
                  #POINTER << " の解放をやむなく無視しました。本来は、ここで nullptr になってこと自体おかしいのでは？。調査せよ！"; \
            GgafCore::Logger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr はありえない、普通の delete[] */
    #define GGAF_DELETEARR(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete[] (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "【警告】GGAF_DELETEARR(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にnullptrであるため "<< \
                  #POINTER << "の解放をやむなく無視しました。本来は、ここで nullptr になってこと自体おかしいのでは？。調査せよ！"; \
            GgafCore::Logger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr かどうか不明な、特別な delete */
    #define GGAF_DELETE_NULLABLE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr かどうか不明な、特別な delete[] */
    #define GGAF_DELETEARR_NULLABLE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* 不完全型簡易チェック */ \
            delete[] (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptrかどうか不明なRelease() */
    #define GGAF_RELEASE_NULLABLE(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); /* AddRef(), Release() とすることで、現在の参照カウンタを得る。 */  \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "【警告】GGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、既に参照カウンタ 0 です。リリースをやむなく無視しましたが、意図しない場合は調査が必要です！"; \
                GgafCore::Logger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "【情報】GGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          "参照カウンタを -1 しました。" \
                          #POINTER << "は、まだ解放されてません。∵現在の参照カウンタ="<<rc; \
                    GgafCore::Logger::writeln(ss); \
                } \
            } \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptrはありえないRelease() */
    #define GGAF_RELEASE(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); /* AddRef(), Release() とすることで、現在の参照カウンタを得る。 */ \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "【警告】GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "は、既に参照カウンタ 0 です。リリースをやむなく無視しましたが、意図しない場合は調査が必要です！"; \
                GgafCore::Logger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "【情報】GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          "参照カウンタを -1 しました。" \
                          #POINTER << "は、まだ解放されません。∵参照カウンタ="<<rc; \
                    GgafCore::Logger::writeln(ss); \
                } \
            } \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "【警告】GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") 既にnullptrであるため "<< \
                  #POINTER << "のリリースをやむなく無視しました。本来は、ここでnullptrになってこと自体おかしいのでは？。調査せよ！！"; \
            GgafCore::Logger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** 自明で検査不要の何も言わないRelease() */
    #define GGAF_RELEASE_BY_FROCE(POINTER) do { \
        if (POINTER) { \
            (POINTER)->Release(); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

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
    /** nullptrはありえない delete */
    #define GGAF_DELETE(POINTER)             do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrはありえない delete[] */
    #define GGAF_DELETEARR(POINTER)          do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrかもしれない delete */
    #define GGAF_DELETE_NULLABLE(POINTER)    do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrかもしれない delete[] */
    #define GGAF_DELETEARR_NULLABLE(POINTER) do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrかもしれない Release() */
    #define GGAF_RELEASE_NULLABLE(POINTER)   do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptrはありえない Release() */
    #define GGAF_RELEASE(POINTER)            do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** 自明で検査不要の何も言わないRelease() */
    #define GGAF_RELEASE_BY_FROCE(POINTER)   do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)

#endif

#ifdef MY_DEBUG
    /** デバッグ用通常ログ */
    #define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::Logger::writeln(ss); }
    //#define _TRACE_(X)
    #define _TRACE_N_(X) { std::stringstream ss; ss << X; GgafCore::Logger::write(ss); }
    //#define _TRACE_N_(X)

    /** 愛関連関連ログ */
    //#define _TRACE2_(X) {std::stringstream ss; ss << "[祝福愛]" << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE2_(X)

    /** 資源マネージャ、コネクション関連ログ */
    //#define _TRACE3_(X) {std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE3_(X)

    /** エフェクト、パス、Draw関連ログ */
    //#define _TRACE4_(X) {std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE4_(X)

    /** 八分木、あたり判定関連ログ */
    //#define _TRACE5_(X) {std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE5_(X)
    //#define _TRACE5_N_(X) {std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::write(ss); }
    #define _TRACE5_N_(X)

# else
    //#define _TRACE_(X) { std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE_(X)
    //#define _TRACE_N_(X) { std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::write(ss); }
    #define _TRACE_N_(X)

    #define _TRACE2_(X)
    #define _TRACE3_(X)
    #define _TRACE4_(X)
    #define _TRACE5_(X)
    #define _TRACE5_N_(X)
#endif

#define NODE_INFO        (_frame_of_life_when_end < _frame_of_life ? "" : "#") << _class_name<<"["<<_name<<"]("<<this<<")"
#define NODE_INFO_P(P)   ((P)->_frame_of_life_when_end < (P)->_frame_of_life ? "" : "#") << ((P)->_class_name)<<"["<<((P)->_name)<<"]("<<(P)<<")"

#define DUMP_FLGS   "@"<< \
                    _frame_of_behaving_since_onActive<< \
                    "/"<< \
                    _frame_of_behaving<< \
                    "/"<< \
                    _frame_of_life<< \
                    ","<< \
                    _can_live_flg<<\
                    _was_initialize_flg<< \
                    ","<< \
                    _is_active_in_the_tree_flg<< \
                    _is_active_flg<< \
                    "-"<< \
                    _frame_of_life_when_activation<< \
                    "-"<< \
                    _frame_of_life_when_inactivation<< \
                    ","<< \
                    _frame_of_life_when_end<< \
                    ","<< \
                    "phase="<<(_pPhase->_phase_no)<<"("<<(_pPhase->getFrame())<<")"<< \
                    ","<< \
                    "id="<<getId()


#define DUMP_FLGS_SCENE   "@"<< \
                    _frame_of_behaving_since_onActive<< \
                    "/"<< \
                    _frame_of_behaving<< \
                    "/"<< \
                    _frame_of_life<< \
                    ","<< \
                    _can_live_flg<<\
                    _was_initialize_flg<< \
                    ","<< \
                    _was_paused_flg<< \
                    "("<<_was_paused_flg_in_next_frame<<")"<< \
                    ","<< \
                    _is_active_in_the_tree_flg<< \
                    _is_active_flg<< \
                    "-"<< \
                    _frame_of_life_when_activation<< \
                    "-"<< \
                    _frame_of_life_when_inactivation<< \
                    ","<< \
                    _frame_of_life_when_end<< \
                    ","<< \
                    "phase="<<(_pPhase->_phase_no)<<"("<<(_pPhase->getFrame())<<")"<< \
                    ","<< \
                    "id="<<getId()


/** アクターの種類(各Bitが種別を表し1を立てていく。分類は32種類(bit)ある事となる) */
typedef uint32_t kind_t;
/** フレーム(アプリケーション時間) */
typedef uint_fast32_t frame;
/** ハッシュ数値 */
typedef uint64_t hashval;
typedef hashval eventval;
#define Obj_SceneBit              (0x8000000000000000ULL)       //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000

#define Obj_ggaf_Scene             ((0x1ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
#define Obj_ggaf_MainScene         ((0x2ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010
#define Obj_ggaf_DisusedScene      ((0x4ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000100
#define Obj_ggaf_Spacetime         ((0x8ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00001000

#define Obj_ggaf_Actor              (0x1ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
#define Obj_ggaf_MainActor          (0x2ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010
#define Obj_ggaf_DestructActor      (0x4ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000100
#define Obj_ggaf_SceneChief      (0x8ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001000
#define Obj_ggaf_GroupHead         (0x10ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00010000
#define Obj_ggaf_DisusedActor      (0x20ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00100000
#define Obj_ggaf_ActorDepository   (0x40ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 01000000
#define Obj_ggaf_Formation         (0x80ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 10000000

#define MAX_FRAME (0xffffffff)

//前方宣言(forward declaration)
namespace GgafCore {

class Util;
class RepeatSeq;
class Object;
class Exception;
class CriticalException;
class Logger;
class Caretaker;

class CmRandomNumberGenerator;

template<class T>
class ResourceConnection;

template<class T>
class ResourceManager;

template<class T>
class Node;

template<class T>
class Element;

template<class T>
class RingLinkedList;

template<class VAL_TYPE>
class TrapezoidalVeloValue;

template<class VAL_TYPE>
class TransitionValue;

template<class VAL_TYPE, int N>
class ValueTransitioner;

class GarbageBox;
class Phase;
class Scene;
class DisusedScene;
class Actor;
class Status;
class DisusedActor;
class MainActor;
class DestructActor;
class Spacetime;
class MainScene;
class SceneChief;
class GroupHead;

class Formation;
class TreeFormation;
class DepositoryFormation;
class ActorDepository;
class ActorDepositoryStore;

class Cradle;
class Rgb;

class Config;
class Properties;

template<class T, int DIM, int N>
class LinearTree;

template<class T>
class LinearQuadtree;

template<class T>
class LinearOctree;

template<class T, int DIM, int N>
class LinearTreeRounder;

template<class T>
class LinearOctreeRounder;

template<class T>
class LinearQuadtreeRounder;

//class Curtain;
class Table;
class EnumIndex;
class Xpm;


}

#endif /*GGAFCOMMONHEADER_H_*/

