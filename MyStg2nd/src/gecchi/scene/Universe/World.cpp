#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");
    _is_create_GameScene = false;
    _pFont16_Debug = NULL;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
#ifdef MY_DEBUG
    orderActorToFactory(0, LabelGecchi16Font, "DebugStr");
    _pFont16_Debug = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getLordActor()->addSubGroup(_pFont16_Debug);
//    orderActorWithModelToFactory(3, DispFpsActor, "FPS_STRING", "28/GECCHI_16FONT");
//    DispFpsActor* pDispFpsActor = (DispFpsActor*)obtainActorFromFactory(3);
//    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
#endif

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");

    //GameScene* pGameScene = NEW GameScene("Game");
    //addSubLast(pGameScene);
//#ifdef MY_DEBUG
//    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "28/moji");
//    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
//#endif

}

void World::processBehavior() {
    if (_is_create_GameScene) {
        VB->update(); //入力情報更新
        if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
            //TODO:終了処理
        }
    } else {
        if (MyFactory::chkProgress(2) == 2) {
            GameScene* pGameScene = (GameScene*)obtainSceneFromFactory(2);
            addSubLast(pGameScene);
            PreDrawScene* pPreDrawScene = (PreDrawScene*)obtainSceneFromFactory(1);
            addSubLast(pPreDrawScene);
            _is_create_GameScene = true;
        }
    }


#ifdef MY_DEBUG
    sprintf(_aBufDebug, "%05u DRAW/%06u CHK/%07u F/%.1f FPS", GgafGod::_num_actor_drawing, CollisionChecker::_num_check, (unsigned int)askGod()->_godframe, askGod()->_fps);
    _pFont16_Debug->update(1, 1, _aBufDebug);
#endif
}

void World::processJudgement() {
}

World::~World() {
}

