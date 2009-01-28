#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_
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
#define OREDEBUG 1


#ifdef OREDEBUG
	#include "DetectMemoryLeaks.h"
	#define NEW new(__FILE__, __LINE__ )
	//#define PFUNC std::cout << __PRETTY_FUNCTION__ << std::endl

	//#define TRACE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }
	#define TRACE(X)
	//#define TRACE2(X) {std::stringstream ss; ss << "[�ʃX���b�h]" << X; GgafCore::GgafLogger::write(ss.str()); }
	#define TRACE2(X)
	//�_���v�o�͗p
	#define _TRACE_(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }
	//�f�o�b�O�p
	#define _TRACEORE(X) {std::stringstream ss; ss << X; GgafCore::GgafLogger::write(ss.str()); }

#else
	#define NEW new

	#define TRACE(X)
	#define TRACE2(X)
	//�_���v�o�͗p
	#define _TRACE_(X)
	//�f�o�b�O�p
	#define _TRACEORE(X)

#endif

//����������p�}�N��
//NULL��������Ȃ� delete
#define DELETE_POSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULL��������Ȃ� delete[]
#define DELETEARR_POSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULL��������Ȃ� Release()
#define RELEASE_POSSIBLE_NULL(POINTER)      { if(POINTER) { int rc = (POINTER)->Release(); if (rc > 0) { std::stringstream ss; ss << "RELEASE_POSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; GgafCore::GgafLogger::write(ss.str()); } (POINTER)=NULL; } else { (POINTER)=NULL; } }
//NULL�͂��肦�Ȃ� delete
#define DELETE_IMPOSSIBLE_NULL(POINTER)       { if(POINTER) { delete (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << " �̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::write(ss.str()); (POINTER)=NULL; }  }
//NULL�͂��肦�Ȃ� delete[]
#define DELETEARR_IMPOSSIBLE_NULL(POINTER)    { if(POINTER) { delete[] (POINTER); (POINTER)=NULL; } else {std::stringstream ss; ss << "DELETEARR_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << "�̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::write(ss.str()); (POINTER)=NULL; }  }
//NULL�͂��肦�Ȃ� Release()
#define RELEASE_IMPOSSIBLE_NULL(POINTER)      { if(POINTER) { int rc = (POINTER)->Release(); if (rc > 0) { std::stringstream ss; ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") "<< #POINTER << "�́A�܂��������܂���B�Q�ƃJ�E���^="<<rc; GgafCore::GgafLogger::write(ss.str()); } (POINTER)=NULL; } else {std::stringstream ss; ss << "RELEASE_IMPOSSIBLE_NULL(file:"<<__FILE__<<" line:"<<__LINE__<<") ����NULL�ł��邽�� "<< #POINTER << "�̉���𖳎����܂������A�{��������NULL�ł���ׂ��ł͖����B�v����"; GgafCore::GgafLogger::write(ss.str());  (POINTER)=NULL; }  }


#define MAX_HEADACTOR_PER_SCENE 16

typedef unsigned int actorkind;

namespace GgafCore {
class GgafUtil;
class GgafObject;
class GgafException;
class GgafCriticalException;
class GgafLogger;
class GgafGod;

//class GgafElement;
//class GgafResource;
//class GgafResourceManager;

class GgafFactory;
class GgafGarbageBox;
class GgafScene;
class GgafGarbageRootScene;
class GgafActor;
class GgafGarbageRootActor;
class GgafMainActor;
class GgafDummyActor;
class GgafWorld;
class GgafMainScene;
class GgafLordActor;
class GgafHeadActor;
class GgafOrder;

class GgafProperties;
class GgafRect;
class GgafUserRootSceneCreater;
}

#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/exception/GgafException.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafLogger.h"
#include "jp/ggaf/core/util/GgafProperties.h"
#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/core/GgafResource.hpp"
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
#include "jp/ggaf/core/scene/GgafWorld.h"
#include "jp/ggaf/core/actor/GgafLordActor.h"
#include "jp/ggaf/core/actor/GgafHeadActor.h"
#include "jp/ggaf/core/GgafOrder.h"

#endif /*GGAFCOMMONHEADER_H_*/
