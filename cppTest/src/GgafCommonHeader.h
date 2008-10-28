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
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <sstream>

using namespace std;
#define ACTOR_DEFAULT_KIND "nokind"
#define ACTOR_DEFAULT_NAME "noname"
#define MAXSCENE_PER_LEVEL 100
#define MAX_HEADACTOR_PER_SCENE 256

//#define TRACE(X) {std::stringstream ss; ss << X; GgafLogger::write(ss.str()); }
#define TRACE(X)
//#define TRACE2(X) {std::stringstream ss; ss << "[別スレッド]" << X; GgafLogger::write(ss.str()); }
#define TRACE2(X)
//ダンプ出力用
#define _TRACE_(X) {std::stringstream ss; ss << X; GgafLogger::write(ss.str()); }
//デバッグ用
#define _TRACEORE(X) {std::stringstream ss; ss << X; GgafLogger::write(ss.str()); }

//class GgafObject;
//class GgafException;
//class GgafCriticalException;
//class GgafLogger;
//class GgafGod;
//class GgafEvent;
//class GgafEventmanager;
////class GgafTreeNode;
//class GgafScene;
//class GgafActor;
//class GgafMainActor;
//class GgafDummyActor;
//class GgafWorldScene;
//class GgafMainScene;
//class GgafLordActor;
//class GgafHeadActor;
//class GgafOrder;
//class GgafFactory;
//class GgafUtil;

//class GgafRect;
//class GgafUserRootSceneCreater;
//#include "jp/ggaf/core/GgafObject.h"
//#include "jp/ggaf/core/exception/GgafException.h"
//#include "jp/ggaf/core/exception/GgafCriticalException.h"
//#include "jp/ggaf/core/util/GgafLogger.h"

//#include "jp/ggaf/core/GgafGod.h"
//#include "jp/ggaf/core/GgafTreeNode.hpp"
//#include "jp/ggaf/core/scene/GgafScene.h"
//#include "jp/ggaf/core/scene/GgafMainScene.h"
//#include "jp/ggaf/core/actor/GgafActor.h"
//#include "jp/ggaf/core/actor/GgafMainActor.h"
//#include "jp/ggaf/core/actor/GgafDummyActor.h"
//#include "jp/ggaf/core/scene/GgafWorldScene.h"
//#include "jp/ggaf/core/actor/GgafLordActor.h"
//#include "jp/ggaf/core/actor/GgafHeadActor.h"
//
//#include "jp/ggaf/core/GgafOrder.h"
//#include "jp/ggaf/core/GgafFactory.h"
//#include "jp/ggaf/core/util/GgafUtil.h"

#endif /*GGAFCOMMONHEADER_H_*/
