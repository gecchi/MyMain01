#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");
    _is_create_GameScene = false;
    _pFont16_Debug = NULL;

    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard01->update(0,50,"WATE A MOMENT PLASE...");
#ifdef MY_DEBUG
    ColliAABActor::get();   //当たり判定領域表示用直方体、プリロード
    ColliAAPrismActor::get();   //当たり判定領域表示用直方体、プリロード
    ColliSphereActor::get(); //当たり判定領域表示用球、プリロード
#endif
//#ifdef MY_DEBUG
    orderActorToFactory(0, LabelGecchi16Font, "DebugStr");
    _pFont16_Debug = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getLordActor()->addSubGroup(_pFont16_Debug);
//    orderActorWithModelToFactory(3, DispFpsActor, "FPS_STRING", "28/GECCHI_16FONT");
//    DispFpsActor* pDispFpsActor = (DispFpsActor*)obtainActorFromFactory(3);
//    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
//#endif

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    PreDrawScene* pPreDrawScene = (PreDrawScene*)obtainSceneFromFactory(1);
    addSubLast(pPreDrawScene);
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
        if (P_GOD->_sync_frame_time) {
            _TEXT_("z");
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
            //TODO:終了処理
        }
    } else {
        //GameScene作成完了まで待つ
        if (MyFactory::chkProgress(2) == 2) {
            _pGameScene = (GameScene*)obtainSceneFromFactory(2);
            addSubLast(_pGameScene);
            _is_create_GameScene = true;
            _pStringBoard01->end();
        }
    }


#ifdef MY_DEBUG
    sprintf(_aBufDebug, "%05uDRAW / %06uCHK / %07uF /%.1fFPS", GgafGod::_num_actor_drawing, CollisionChecker::_num_check, (unsigned int)askGod()->_frame_of_God, askGod()->_fps);
    _pFont16_Debug->update(1, 1, _aBufDebug);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("_aBufDebug="<<_aBufDebug);
    }
#else
    sprintf(_aBufDebug, "%05uDRAW / %.1fFPS", GgafGod::_num_actor_drawing, askGod()->_fps);
    _pFont16_Debug->update(1, 1, _aBufDebug);
#endif


}

void World::processJudgement() {
}

World::~World() {
}

