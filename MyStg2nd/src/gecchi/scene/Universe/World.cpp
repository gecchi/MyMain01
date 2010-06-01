#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");
    _is_create_GameScene = false;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
#ifdef MY_DEBUG
    orderActorWithModelToFactory(3, DispFpsActor, "FPS_STRING", "28/moji");
    DispFpsActor* pDispFpsActor = (DispFpsActor*)obtainActorFromFactory(3);
    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
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
}

void World::processJudgement() {
}

World::~World() {
}

