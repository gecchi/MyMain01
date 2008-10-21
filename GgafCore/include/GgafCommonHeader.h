#ifndef GGAFCOMMONHEADER_H_
#define GGAFCOMMONHEADER_H_

#define _HAS_ITERATOR_DEBUGGING 0

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
	#include "DetectMemoryLeaks.h"
	#define NEW new(__FILE__, __LINE__ )

	//#define TRACE(X) {std::stringstream ss; ss << X; GgafLogger::write(ss.str()); }
	#define TRACE(X)
	//#define TRACE2(X) {std::stringstream ss; ss << "[別スレッド]" << X; GgafLogger::write(ss.str()); }
	#define TRACE2(X)
	//ダンプ出力用
	#define _TRACE_(X) {std::stringstream ss; ss << X; GgafLogger::write(ss.str()); }
	//デバッグ用
	#define _TRACEORE(X) {std::stringstream ss; ss << X; GgafLogger::write(ss.str()); }

#else
	#define NEW new

	#define TRACE(X)
	#define TRACE2(X)
	//ダンプ出力用
	#define _TRACE_(X)
	//デバッグ用
	#define _TRACEORE(X)

#endif

using namespace std;

#define MAX_HEADACTOR_PER_SCENE 16


typedef unsigned int actorkind;

class GgafObject;
class GgafException;
class GgafCriticalException;
class GgafLogger;
class GgafGod;
class GgafEvent;
class GgafEventmanager;
//class GgafElement;
class GgafScene;
class GgafActor;
class GgafMainActor;
class GgafDummyActor;
class GgafWorld;
class GgafMainScene;
class GgafLordActor;
class GgafHeadActor;
class GgafOrder;
class GgafFactory;
class GgafUtil;
class GgafProperties;
class GgafRect;
class GgafUserRootSceneCreater;


#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/exception/GgafException.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafLogger.h"
#include "jp/ggaf/core/util/GgafProperties.h"
#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/core/GgafNode.hpp"
#include "jp/ggaf/core/GgafElement.hpp"
#include "jp/ggaf/core/util/basic_symbol.hpp"
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/scene/GgafMainScene.h"
#include "jp/ggaf/core/actor/GgafActor.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafDummyActor.h"
#include "jp/ggaf/core/scene/GgafWorld.h"
#include "jp/ggaf/core/actor/GgafLordActor.h"
#include "jp/ggaf/core/actor/GgafHeadActor.h"
#include "jp/ggaf/core/GgafOrder.h"
#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/core/util/GgafDrawActorList.h"


#endif /*GGAFCOMMONHEADER_H_*/
