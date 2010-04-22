#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");
    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void World::initialize() {
    _TRACE_("World::initialize()");
    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
#ifdef MY_DEBUG
    orderActorWithModelToFactory(3, DispFpsActor, "FPS_STRING", "28/moji");
#endif
    PreDrawScene* pPreDrawScene = (PreDrawScene*)obtainSceneFromFactory(1);
    addSubLast(pPreDrawScene);
#ifdef MY_DEBUG
    DispFpsActor* pDispFpsActor = (DispFpsActor*)obtainActorFromFactory(3);
    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
#endif
    //GameScene* pGameScene = NEW GameScene("Game");
    //addSubLast(pGameScene);
//#ifdef MY_DEBUG
//    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "28/moji");
//    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
//#endif

}

void World::processBehavior() {
    if ( getPartFrame() == 180 ) {
        GameScene* pGameScene = (GameScene*)obtainSceneFromFactory(2);
        addSubLast(pGameScene);
    }

    VB_PLAY->update(); //���͏��X�V

}

void World::processJudgement() {
}

World::~World() {
}



