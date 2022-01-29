#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_
/**
 * ���C�u�����w�b�_�[�S�w�b�_�[
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */


//MY_DEBUG�͎����p�̃f�o�b�O�r���h
#ifdef _DEBUG
    //#undef _DEBUG
    #define MY_DEBUG _DEBUG
#endif

//Windows XP �ȏ�B
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
//GCC�̏ꍇ�A��̂Q�̃V���{���̓R���p�C����
//�����Őݒ肷���������B

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
//�����p�f�o�b�O�r���h�̏ꍇ
    #ifdef _MSC_VER
        #ifdef _DEBUG
            //�����p�f�o�b�O ���� VC++�� �f�o�b�O�r���h��
            //VC++�̃��[�N���o���d����
            #define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__ )
        #else
            //�����p�f�o�b�O ���� VC++�̃����[�X�r���h��
            #define NEW new
        #endif
    #else
        //GCC �Ŏ����p�f�o�b�O�r���h��
        //GCC�p�̃��[�N���o���d����
        //#include "jp/ggaf/core/DetectMemoryLeaks.h"
        //#define NEW new(__FILE__, __LINE__)
        #define NEW new
    #endif
    //#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

    //����������p�}�N��
    #include "jp/ggaf/core/util/Logger.h"
    /** nullptr �͂��肦�Ȃ��A���ʂ� delete */
    #define GGAF_DELETE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* �s���S�^�ȈՃ`�F�b�N */ \
            delete (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "�y�x���zGGAF_DELETE(file:"<<__FILE__<<" line:"<<__LINE__<<") ����nullptr�ł��邽�� "<< \
                  #POINTER << " �̉������ނȂ��������܂����B�{���́A������ nullptr �ɂȂ��Ă��Ǝ��̂��������̂ł́H�B��������I"; \
            GgafCore::Logger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr �͂��肦�Ȃ��A���ʂ� delete[] */
    #define GGAF_DELETEARR(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* �s���S�^�ȈՃ`�F�b�N */ \
            delete[] (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "�y�x���zGGAF_DELETEARR(file:"<<__FILE__<<" line:"<<__LINE__<<") ����nullptr�ł��邽�� "<< \
                  #POINTER << "�̉������ނȂ��������܂����B�{���́A������ nullptr �ɂȂ��Ă��Ǝ��̂��������̂ł́H�B��������I"; \
            GgafCore::Logger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr ���ǂ����s���ȁA���ʂ� delete */
    #define GGAF_DELETE_NULLABLE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* �s���S�^�ȈՃ`�F�b�N */ \
            delete (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr ���ǂ����s���ȁA���ʂ� delete[] */
    #define GGAF_DELETEARR_NULLABLE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* �s���S�^�ȈՃ`�F�b�N */ \
            delete[] (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr���ǂ����s����Release() */
    #define GGAF_RELEASE_NULLABLE(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); /* AddRef(), Release() �Ƃ��邱�ƂŁA���݂̎Q�ƃJ�E���^�𓾂�B */  \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "�y�x���zGGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "�́A���ɎQ�ƃJ�E���^ 0 �ł��B�����[�X����ނȂ��������܂������A�Ӑ}���Ȃ��ꍇ�͒������K�v�ł��I"; \
                GgafCore::Logger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "�y���zGGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          "�Q�ƃJ�E���^�� -1 ���܂����B" \
                          #POINTER << "�́A�܂��������Ă܂���B�挻�݂̎Q�ƃJ�E���^="<<rc; \
                    GgafCore::Logger::writeln(ss); \
                } \
            } \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** nullptr�͂��肦�Ȃ�Release() */
    #define GGAF_RELEASE(POINTER) do { \
        if (POINTER) { \
            int rc = (POINTER)->AddRef(); /* AddRef(), Release() �Ƃ��邱�ƂŁA���݂̎Q�ƃJ�E���^�𓾂�B */ \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "�y�x���zGGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "�́A���ɎQ�ƃJ�E���^ 0 �ł��B�����[�X����ނȂ��������܂������A�Ӑ}���Ȃ��ꍇ�͒������K�v�ł��I"; \
                GgafCore::Logger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "�y���zGGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          "�Q�ƃJ�E���^�� -1 ���܂����B" \
                          #POINTER << "�́A�܂��������܂���B��Q�ƃJ�E���^="<<rc; \
                    GgafCore::Logger::writeln(ss); \
                } \
            } \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "�y�x���zGGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") ����nullptr�ł��邽�� "<< \
                  #POINTER << "�̃����[�X����ނȂ��������܂����B�{���́A������nullptr�ɂȂ��Ă��Ǝ��̂��������̂ł́H�B��������I�I"; \
            GgafCore::Logger::writeln(ss); \
            (POINTER) = nullptr; \
        } \
    }while(0)

    /** �����Ō����s�v�̉�������Ȃ�Release() */
    #define GGAF_RELEASE_BY_FROCE(POINTER) do { \
        if (POINTER) { \
            (POINTER)->Release(); \
            (POINTER) = nullptr; \
        } else { \
            (POINTER) = nullptr; \
        } \
    }while(0)

#else
//�����p�����[�X�r���h��

    #ifdef _MSC_VER
        #ifdef _DEBUG
            //�����p�����[�X�r���h�� ���� VC++�� �f�o�b�O�r���h��
            //VC++�̃��[�N���o����i�ɂ��Ă������j
            #define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__ )
        #else
            //�����p�����[�X�r���h�� VC++�� �����[�X�r���h��
            #define NEW new
        #endif
    #else
        //GCC �Ŏ����p�����[�X�r���h��
        #define NEW new
    #endif


    //����������p�}�N��
    /** nullptr�͂��肦�Ȃ� delete */
    #define GGAF_DELETE(POINTER)             do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr�͂��肦�Ȃ� delete[] */
    #define GGAF_DELETEARR(POINTER)          do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr��������Ȃ� delete */
    #define GGAF_DELETE_NULLABLE(POINTER)    do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr��������Ȃ� delete[] */
    #define GGAF_DELETEARR_NULLABLE(POINTER) do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr��������Ȃ� Release() */
    #define GGAF_RELEASE_NULLABLE(POINTER)   do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr�͂��肦�Ȃ� Release() */
    #define GGAF_RELEASE(POINTER)            do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** �����Ō����s�v�̉�������Ȃ�Release() */
    #define GGAF_RELEASE_BY_FROCE(POINTER)   do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)

#endif

#ifdef MY_DEBUG
    /** �f�o�b�O�p�ʏ탍�O */
    #define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::Logger::writeln(ss); }
    //#define _TRACE_(X)
    #define _TRACE_N_(X) { std::stringstream ss; ss << X; GgafCore::Logger::write(ss); }
    //#define _TRACE_N_(X)

    /** ���֘A�֘A���O */
    //#define _TRACE2_(X) {std::stringstream ss; ss << "[�j����]" << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE2_(X)

    /** �����}�l�[�W���A�R�l�N�V�����֘A���O */
    //#define _TRACE3_(X) {std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE3_(X)

    /** �G�t�F�N�g�A�p�X�ADraw�֘A���O */
    //#define _TRACE4_(X) {std::stringstream ss; ss << FUNC_NAME << " " << X; GgafCore::Logger::writeln(ss); }
    #define _TRACE4_(X)

    /** �����؁A�����蔻��֘A���O */
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
                    "prog="<<(_pProg?_pProg->_progress:-9)<<"("<<(_pProg?_pProg->getFrame():0)<<")"<< \
                    ","<< \
                    "id="<<getId()


/** ���ʒx������t���[�����i���G�t�F�N�g�ő�Đ����ԁj */
#define GGAF_END_DELAY (60*90)
//GGAF_END_DELAY�͑SElement���ʂ̉���x���t���[�����ŁA
//�A�N�^�[������A�����ɕs���|�C���^�ɂȂ�̂ł͂Ȃ��A���΂炭�Q�Ƃ��\�Ƃ��邽�߂̎d�g�݁B
//�������߂ɐݒ肵�Ȃ��ƁA���낢��s�s���������B
//�Ⴆ�΁A���Ō�̔���SE���ŁA3D���ʂ̂���SE���������W��񂪂��΂炭�K�v�Ƃ��A
//���Ō�̏��ŃA�N�^�[�z���ɑ����锭�˒e�i�q�A�N�^�[�j���A�e�A�N�^�[�̍��W���Q�Ƃ��Ă���ȂǁA
//���ł��Ă��A���΂炭�͎c�������Ȃ���΂����Ȃ��ꍇ�����X����B
//GGAF_END_DELAY�ɂ́A��{�I�ɁA��ʂ�����Ŋm�聨���S��delete�܂ł̃t���[���̍ő�t���[�����w�肷��B
//���݂�90�b�B
//�����AGGAF_END_DELAY��Z�߂ɐݒ肷��ƁA
//���Ō�̎q�̔��˒e�ɂ��ẮA�c���ꂽ���˒e���ˑR������̂ŏ����s���R�B�Ƃ������x�Ŗ��͂Ȃ��B
//�������ASE��3D���ʂ́A�G���[�ɂȂ邽�߁ASE�Đ����Ԃ̍ő�t���[������ݒ肵�Ȃ���΂����Ȃ��B
//�Ⴆ�Ό��ʉ���90�b�ȏォ����悤��WAVE����ł�����Ȃ�΁A90�b�ȏ��ݒ肵�Ȃ���΂Ȃ�Ȃ��B


/** �A�N�^�[�̎��(�eBit����ʂ�\��1�𗧂ĂĂ����B���ނ�32���(bit)���鎖�ƂȂ�) */
typedef uint32_t kind_t;
/** �t���[��(�A�v���P�[�V��������) */
typedef uint_fast32_t frame;
/** �n�b�V�����l */
typedef uint64_t hashval;

#define Obj_SceneBit              (0x8000000000000000ULL)       //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000

#define Obj_ggaf_Scene             ((0x1ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
#define Obj_ggaf_MainScene         ((0x2ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010
#define Obj_ggaf_DisusedScene      ((0x4ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000100
#define Obj_ggaf_Spacetime         ((0x8ULL) | Obj_SceneBit)     //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00001000

#define Obj_ggaf_Actor              (0x1ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
#define Obj_ggaf_MainActor          (0x2ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000010
#define Obj_ggaf_DestructActor      (0x4ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000100
#define Obj_ggaf_SceneMediator      (0x8ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001000
#define Obj_ggaf_GroupHead         (0x10ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00010000
#define Obj_ggaf_DisusedActor      (0x20ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00100000
#define Obj_ggaf_ActorDepository   (0x40ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 01000000
#define Obj_ggaf_Formation         (0x80ULL)                     //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000000 10000000

#define MAX_FRAME (0xffffffff)

//�O���錾(forward declaration)
namespace GgafCore {

class Util;
class RepeatSeq;
class Object;
class Exception;
class CriticalException;
class Logger;
class God;

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
class LinkedListRing;

template<class VAL_TYPE>
class TrapezoidalVeloValue;

template<class VAL_TYPE>
class TransitionValue;

template<class VAL_TYPE, int N>
class TransitionValueSet;

class GarbageBox;
class Progress;
class Scene;
class DisusedScene;
class Actor;
class Status;
class DisusedActor;
class MainActor;
class DestructActor;
class Spacetime;
class MainScene;
class SceneMediator;
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
class LinearOctree;

template<uint32_t DIMENSION>
class TreeSpace;

template<uint32_t DIMENSION>
class TreeElem;

class LinearQuadtree;

//class Curtain;
class Table;

class EnumIndex;

class Xpm;

template<class T, uint32_t DIMENSION>
class LinearTreeRounder;

}

#endif /*GGAFCOMMONHEADER_H_*/
