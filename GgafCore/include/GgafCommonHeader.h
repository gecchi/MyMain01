#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_
/**
 * Ggaf���C�u�����w�b�_�[�S�w�b�_�[
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
    #include "jp/ggaf/core/util/GgafLogger.h"
    /** nullptr �͂��肦�Ȃ��A���ʂ� delete */
    #define GGAF_DELETE(POINTER) do { \
        if (POINTER) { \
            POINTER = POINTER + 0; /* �s���S�^�ȈՃ`�F�b�N */ \
            delete (POINTER); \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "���x����GGAF_DELETE(file:"<<__FILE__<<" line:"<<__LINE__<<") ����nullptr�ł��邽�� "<< \
                  #POINTER << " �̉������ނȂ��������܂����B�{���́A������ nullptr �ɂȂ��Ă��Ǝ��̂��������̂ł́H�B��������I"; \
            GgafCore::GgafLogger::writeln(ss); \
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
            ss << "���x����GGAF_DELETEARR(file:"<<__FILE__<<" line:"<<__LINE__<<") ����nullptr�ł��邽�� "<< \
                  #POINTER << "�̉������ނȂ��������܂����B�{���́A������ nullptr �ɂȂ��Ă��Ǝ��̂��������̂ł́H�B��������I"; \
            GgafCore::GgafLogger::writeln(ss); \
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
            int rc = (POINTER)->AddRef(); \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "���x����GGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "�́A���ɎQ�ƃJ�E���^0�ł��BRelease() �͍s���܂���ł����B�������K�v�ł��I"; \
                GgafCore::GgafLogger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "�����GGAF_RELEASE_NULLABLE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; \
                    GgafCore::GgafLogger::writeln(ss); \
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
            int rc = (POINTER)->AddRef(); \
            rc = (POINTER)->Release(); \
            if (rc == 0) { \
                std::stringstream ss; \
                ss << "���x����GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "�́A���ɎQ�ƃJ�E���^0�ł��B�����[�X����ނȂ��������܂����B�������K�v�ł��I"; \
                GgafCore::GgafLogger::writeln(ss); \
            } else { \
                rc = (POINTER)->Release(); \
                if (rc > 0) { \
                    std::stringstream ss; \
                    ss << "�����GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                          #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; \
                    GgafCore::GgafLogger::writeln(ss); \
                } \
            } \
            (POINTER) = nullptr; \
        } else { \
            std::stringstream ss; \
            ss << "GGAF_RELEASE(file:"<<__FILE__<<" line:"<<__LINE__<<") ����nullptr�ł��邽�� "<< \
                  #POINTER << "�̃����[�X����ނȂ��������܂����B�{���́A������nullptr�ɂȂ��Ă��Ǝ��̂��������̂ł́H�B��������B"; \
            GgafCore::GgafLogger::writeln(ss); \
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
    #define GGAF_DELETE(POINTER)     do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr�͂��肦�Ȃ� delete[] */
    #define GGAF_DELETEARR(POINTER)  do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr��������Ȃ� delete */
    #define GGAF_DELETE_NULLABLE(POINTER)       do { if(POINTER) { delete (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr��������Ȃ� delete[] */
    #define GGAF_DELETEARR_NULLABLE(POINTER)    do { if(POINTER) { delete[] (POINTER); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr��������Ȃ� Release() */
    #define GGAF_RELEASE_NULLABLE(POINTER)      do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** nullptr�͂��肦�Ȃ� Release() */
    #define GGAF_RELEASE(POINTER)    do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)
    /** �����Ō����s�v�̉�������Ȃ�Release() */
    #define GGAF_RELEASE_BY_FROCE(POINTER)       do { if(POINTER) { (POINTER)->Release(); (POINTER)=nullptr; } else { (POINTER)=nullptr; } } while(0)

#endif

#ifdef MY_DEBUG
    /** �f�o�b�O�p�ʏ탍�O */
    #define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    //#define _TRACE_(X)
    #define _TEXT_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss); }
    //#define _TEXT_(X)

    /** �H��֘A�֘A���O */
    //#define TRACE2(X) {std::stringstream ss; ss << "[�����H��]" << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE2(X)

    /** �����}�l�[�W���A�R�l�N�V�����֘A���O */
    //#define TRACE3(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE3(X)

    /** �G�t�F�N�g�A�p�X�ADraw�֘A���O */
    //#define TRACE4(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE4(X)

    /** �W���؁A�����蔻��֘A���O */
    //#define TRACE5(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE5(X)
    //#define TEXT5(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss); }
    #define TEXT5(X)

# else
    //#define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define _TRACE_(X)
    //#define _TEXT_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss); }
    #define _TEXT_(X)

    #define TRACE2(X)
    #define TRACE3(X)
    #define TRACE4(X)
    #define TRACE5(X)
    #define TEXT5(X)
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
                    _will_mv_last_in_next_frame_flg<< \
                    ","<< \
                    "prog="<<"("<<(_pProg?_pProg->_progress_prev:-9)<<")"<<(_pProg?_pProg->_progress:-9)<<"("<<(_pProg?_pProg->_progress_next:-9)<<")"

/** ���ʒx������t���[���� */
#define GGAF_END_DELAY (60*60)
//GGAF_END_DELAY�͑SElement���ʂ̉���x���t���[�����ŁA
//�A�N�^�[������A�����ɕs���|�C���^�ɂȂ�̂ł͂Ȃ��A���΂炭�Q�Ƃ��\�Ƃ��邽�߂̎d�g�݁B
//�������߂ɐݒ肵�Ȃ��ƁA���낢��s�s���������B
//�Ⴆ�΁A���Ō�̔���SE���ŁA3D���ʂ̂���SE���������W��񂪂��΂炭�K�v�Ƃ��A
//���Ō�̏��ŃA�N�^�[�z���ɑ����锭�˒e�i�q�A�N�^�[�j���A�e�A�N�^�[�̍��W���Q�Ƃ��Ă���ȂǁA
//���ł��Ă��A���΂炭�͎c�������Ȃ���΂����Ȃ��ꍇ�����X����B
//GGAF_END_DELAY�ɂ́A��{�I�ɁA��ʂ�����Ŋm�聨���S��delete�܂ł̃t���[���̍ő�t���[�����w�肷��B
//���݂�1�b(60*60)�B
//�����AGGAF_END_DELAY��Z�߂ɐݒ肷��ƁA
//���Ō�̎q�̔��˒e�ɂ��ẮA�c���ꂽ���˒e���ˑR������̂ŏ����s���R�B�Ƃ������x�Ŗ��͂Ȃ��B
//�������ASE��3D���ʂ́A�G���[�ɂȂ邽�߁ASE�Đ����Ԃ̍ő�t���[������ݒ肵�Ȃ���΂����Ȃ��B
//�Ⴆ�Ό��ʉ����P���ȏォ����悤��WAVE����ł�����Ȃ�΁A(60*60)�ȏ��ݒ肵�Ȃ���΂Ȃ�Ȃ��B


/** �A�N�^�[�̎�� */
typedef uint32_t actorkind;
/** �t���[��(�A�v���P�[�V��������) */
typedef uint32_t frame;
#define MAX_FRAME (UINT_MAX)

#define Obj_SceneBit              (0x80000000U)       //0b 10000000 00000000 00000000 00000000

#define Obj_GgafScene             (0x80000001U)       //0b 10000000 00000000 00000000 00000001
#define Obj_GgafMainScene         (0x80000002U)       //0b 10000000 00000000 00000000 00000010
#define Obj_GgafDisusedScene      (0x80000004U)       //0b 10000000 00000000 00000000 00000100
#define Obj_GgafUniverse          (0x80000008U)       //0b 10000000 00000000 00000000 00001000

#define Obj_GgafActor             (0x1U)              //0b 00000000 00000000 00000000 00000001
#define Obj_GgafMainActor         (0x2U)              //0b 00000000 00000000 00000000 00000010
#define Obj_GgafDummyActor        (0x4U)              //0b 00000000 00000000 00000000 00000100
#define Obj_GgafSceneDirector     (0x8U)              //0b 00000000 00000000 00000000 00001000
#define Obj_GgafGroupHead         (0x10U)             //0b 00000000 00000000 00000000 00010000
#define Obj_GgafDisusedActor      (0x20U)             //0b 00000000 00000000 00000000 00100000
#define Obj_GgafActorDepository   (0x40U)             //0b 00000000 00000000 00000000 01000000
#define Obj_GgafFormation         (0x80U)             //0b 00000000 00000000 00000000 10000000


//�O���錾(forward declaration)
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
