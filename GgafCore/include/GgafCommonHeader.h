#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_

/**
 * Ggaf���C�u�����w�b�_�[�S�w�b�_�[
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

// Windows �w�b�_�[ �t�@�C��:
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

//�����p�f�o�b�O�r���h(�R�����g���O���Ύg�p�\)
#define MY_DEBUG 1


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
        #include "DetectMemoryLeaks.h"
        #define NEW new(__FILE__, __LINE__)
    #endif

    //#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

    /** �R���X�g���N�^�A��v���\�b�h�A�f�X�g���N�^�֘A���O */
    //#define TRACE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    #define TRACE(X)

    /** �H��֘A�֘A���O */
    //#define TRACE2(X) {std::stringstream ss; ss << "[�ʃX���b�h]" << X; GgafCore::GgafLogger::writeln(ss); }
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

    /** �f�o�b�O�p�ʏ탍�O */
    #define _TRACE_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss); }
    //#define _TRACE_(X)
    #define _TEXT_(X) { std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss); }
    //#define _TEXT_(X)

    //����������p�}�N��
    /** NULL���ǂ����s����delete */
    #define DELETE_POSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete (POINTER); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }
    /** NULL���ǂ����s����delete[] */
    #define DELETEARR_POSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete[] (POINTER); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }
    /** NULL���ǂ����s����Release() */
    #define RELEASE_POSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            int rc = (POINTER)->Release(); \
            if (rc > 0) { \
                std::stringstream ss; \
                ss << "RELEASE_POSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; \
                GgafCore::GgafLogger::writeln(ss); \
            } \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }
    /** NULL�͂��肦�Ȃ�delete */
    #define DELETE_IMPOSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete (POINTER); \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "DELETE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< \
                  #POINTER << " �̉������ނȂ��������܂����B�{���́A������NULL�ɂȂ��Ă��Ǝ��̂��������B��������B"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    }
    /** NULL�͂��肦�Ȃ�delete[] */
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            delete[] (POINTER); \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "DELETEARR_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< \
                  #POINTER << "�̉������ނȂ��������܂����B�{���́A������NULL�ɂȂ��Ă��Ǝ��̂��������B��������B"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    }
    /** NULL�͂��肦�Ȃ�Release() */
    #define RELEASE_IMPOSSIBLE_NULL(POINTER) { \
        if (POINTER) { \
            int rc = (POINTER)->Release(); \
            if (rc > 0) { \
                std::stringstream ss; \
                ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< \
                      #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; \
                GgafCore::GgafLogger::writeln(ss); \
            } \
            (POINTER) = NULL; \
        } else { \
            std::stringstream ss; \
            ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< \
                  #POINTER << "�̃����[�X����ނȂ��������܂����B�{���́A������NULL�ɂȂ��Ă��Ǝ��̂��������B��������B"; \
            GgafCore::GgafLogger::writeln(ss); \
            (POINTER) = NULL; \
        } \
    }
    /** �����Ō����s�v�̉�������Ȃ�Release() */
    #define RELEASE_SAFETY(POINTER) { \
        if (POINTER) { \
            (POINTER)->Release(); \
            (POINTER) = NULL; \
        } else { \
            (POINTER) = NULL; \
        } \
    }

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

    //����������p�}�N��
    /** NULL��������Ȃ� delete */
    #define DELETE_POSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULL��������Ȃ� delete[] */
    #define DELETEARR_POSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULL��������Ȃ� Release() */
    #define RELEASE_POSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULL�͂��肦�Ȃ� delete */
    #define DELETE_IMPOSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULL�͂��肦�Ȃ� delete[] */
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** NULL�͂��肦�Ȃ� Release() */
    #define RELEASE_IMPOSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    /** �����Ō����s�v�̉�������Ȃ�Release() */
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
//GCC�̏ꍇsal.h�ŉ��̂�NULL �� __null �� ����`�̂��ߋ����I�ɍĒ�`(�i���m�R�b�`��)
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
