#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_

/**
 * Ggaf���C�u�����w�b�_�[�S�w�b�_�[
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */


#ifndef _MSC_VER
#define _WIN32_IE 0x0300
#endif

#define _HAS_ITERATOR_DEBUGGING 0

// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>
// C �����^�C�� �w�b�_�[ �t�@�C��
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

//���f
//#define OREDEBUG 1


#ifdef OREDEBUG
    #include "DetectMemoryLeaks.h"
    #define NEW new(__FILE__, __LINE__)
    //#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

    //#define TRACE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss.str()); }
    #define TRACE(X)

    //�H��֘A
    //#define TRACE2(X) {std::stringstream ss; ss << "[�ʃX���b�h]" << X; GgafCore::GgafLogger::writeln(ss.str()); }
    #define TRACE2(X)

    //�����A�}�l�[�W���A�R�l�N�V�����֘A
    //#define TRACE3(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss.str()); }
    #define TRACE3(X)

    //�G�t�F�N�g�A�p�X�ADraw�֘A
    //#define TRACE4(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss.str()); }
    #define TRACE4(X)

    //�W���؊֘A
    //#define TRACE5(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss.str()); }
    //#define TEXT5(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }

    #define TRACE5(X)
    #define TEXT5(X)



    //�_���v�o�͗p
    #define _TRACE_(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss.str()); }
    //#define _TRACE_(X)
    //�_���v�o�͗p
    #define _TEXT_(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }

    //�f�o�b�O�p
    #define _TRACEORE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::writeln(ss.str()); }


    //����������p�}�N��
    //NULL��������Ȃ� delete
    #define DELETE_POSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL��������Ȃ� delete[]
    #define DELETEARR_POSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL��������Ȃ� Release()
    #define RELEASE_POSSIBLE_NULL(POINTER)      { if(POINTER) { int rc = (POINTER)->Release(); if (rc > 0) { std::stringstream ss; ss << "RELEASE_POSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; GgafCore::GgafLogger::writeln(ss.str()); } (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL�͂��肦�Ȃ� delete
    #define DELETE_IMPOSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << " �̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::writeln(ss.str()); (POINTER)=NULL; }  }
    //NULL�͂��肦�Ȃ� delete[]
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETEARR_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << "�̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::writeln(ss.str()); (POINTER)=NULL; }  }
    //NULL�͂��肦�Ȃ� Release()
    #define RELEASE_IMPOSSIBLE_NULL(POINTER)      { if(POINTER) { int rc = (POINTER)->Release(); if (rc > 0) { std::stringstream ss; ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; GgafCore::GgafLogger::writeln(ss.str()); } (POINTER)=NULL; } else {std::stringstream ss; ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << "�̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::writeln(ss.str());  (POINTER)=NULL; }  }
    //��������Ȃ� Release()
    #define RELEASE_SAFETY(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }

#else
    #define NEW new

    #define TRACE(X)
    #define TRACE2(X)
    #define TRACE3(X)
    #define TRACE4(X)
    #define TRACE5(X)
    #define TEXT5(X)
    //�_���v�o�͗p
    #define _TRACE_(X)
    #define _TEXT_(X)
    //�f�o�b�O�p
    #define _TRACEORE(X)

    //����������p�}�N��
    //NULL��������Ȃ� delete
    #define DELETE_POSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL��������Ȃ� delete[]
    #define DELETEARR_POSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL��������Ȃ� Release()
    #define RELEASE_POSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL�͂��肦�Ȃ� delete
    #define DELETE_IMPOSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL�͂��肦�Ȃ� delete[]
    #define DELETEARR_IMPOSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //NULL�͂��肦�Ȃ� Release()
    #define RELEASE_IMPOSSIBLE_NULL(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }
    //��������Ȃ� Release()
    #define RELEASE_SAFETY(POINTER)      { if(POINTER) { (POINTER)->Release(); (POINTER)=NULL; } else { (POINTER)=NULL; } }

#endif


#define MAX_HEADACTOR_PER_SCENE 16

typedef DWORD actorkind;

namespace GgafCore {
class GgafUtil;
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
class GgafGarbageRootScene;
class GgafActor;
class GgafStatus;
class GgafGarbageRootActor;
class GgafMainActor;
class GgafDummyActor;
class GgafUniverse;
class GgafMainScene;
class GgafLordActor;
class GgafHeadActor;
class GgafOrder;

class GgafProperties;

class GgafLinearOctree;
class GgafLinearOctreeSpace;
class GgafLinearOctreeElem;


}

#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/exception/GgafException.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/core/util/GgafLogger.h"
#include "jp/ggaf/core/util/GgafProperties.h"
#include "jp/ggaf/core/GgafGod.h"

#include "jp/ggaf/core/GgafResourceConnection.hpp"
#include "jp/ggaf/core/GgafResourceManager.hpp"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/GgafGarbageBox.h"

#include "jp/ggaf/core/GgafNode.hpp"
#include "jp/ggaf/core/GgafElement.hpp"
#include "jp/ggaf/core/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/scene/GgafGarbageRootScene.h"
#include "jp/ggaf/core/scene/GgafMainScene.h"
#include "jp/ggaf/core/actor/GgafActor.h"

#include "jp/ggaf/core/actor/GgafGarbageRootActor.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafDummyActor.h"
#include "jp/ggaf/core/scene/GgafUniverse.h"
#include "jp/ggaf/core/actor/GgafLordActor.h"
#include "jp/ggaf/core/actor/GgafHeadActor.h"
#include "jp/ggaf/core/GgafOrder.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearOctreeSpace.h"
#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"



#endif /*GGAFCOMMONHEADER_H_*/
