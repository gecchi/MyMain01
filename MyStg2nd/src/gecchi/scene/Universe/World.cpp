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
    _pFont16_Wait = NULL;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
    orderActorToFactory(0, LabelGecchi16Font, "STR01");
    _pStringBoard01 = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pStringBoard01);
    _pStringBoard01->update(Pix2App(CFG_PROPERTY(GAME_BUFFER_WIDTH)/2), Pix2App(100),
                            "WATE A MOMENT PLASE...", ALIGN_CENTER);
//    _pStringBoard01->_pFader->beat(60,10,20,20,-1);

    orderActorToFactory(0, LabelGecchi16Font, "ASTER");
    _pFont16_Wait = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pFont16_Wait);
    _pFont16_Wait->update(Pix2App(CFG_PROPERTY(GAME_BUFFER_WIDTH)), 0, "*", ALIGN_RIGHT);
    _pFont16_Wait->_pFader->beat(60,30,0,0,-1);
#ifdef MY_DEBUG
    ColliAABActor::get();   //当たり判定領域表示用直方体、プリロード
    ColliAAPrismActor::get();   //当たり判定領域表示用直方体、プリロード
    ColliSphereActor::get(); //当たり判定領域表示用球、プリロード
#endif
//#ifdef MY_DEBUG
    orderActorToFactory(0, LabelGecchi16Font, "DebugStr");
    _pFont16_Debug = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pFont16_Debug);
//    orderActorWithModelToFactory(3, DispFpsActor, "FPS_STRING", "28/GECCHI_16FONT");
//    DispFpsActor* pDispFpsActor = (DispFpsActor*)obtainActorFromFactory(3);
//    getDirector()->addSubGroup(KIND_EFFECT, pDispFpsActor);
//#endif

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
//    PreDrawScene* pPreDrawScene = (PreDrawScene*)obtainSceneFromFactory(1);
//    addSubLast(pPreDrawScene);

    orderSceneToFactory(2, GameScene, "Game");

    //GameScene* pGameScene = NEW GameScene("Game");
    //addSubLast(pGameScene);
//#ifdef MY_DEBUG
//    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "28/moji");
//    getDirector()->addSubGroup(KIND_EFFECT, pDispFpsActor);
//#endif

}

void World::processBehavior() {


    if (_is_create_GameScene) {
        //GameScene作成完了
        VB->update(); //入力情報更新
#ifdef MY_DEBUG
        if (P_GOD->_sync_frame_time) {
            _TEXT_("z");
        }
#endif
        if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
            //TODO:終了処理
        }
    } else {
        //GameScene作成完了まで待つ
        if (GgafFactory::chkProgress(1) == 2 && GgafFactory::chkProgress(2) == 2) {
            _pPreDrawScene = (PreDrawScene*)obtainSceneFromFactory(1);
            addSubLast(_pPreDrawScene);
            _pGameScene = (GameScene*)obtainSceneFromFactory(2);
            addSubLast(_pGameScene);
            _is_create_GameScene = true;
            _pStringBoard01->end();
            _pFont16_Wait->end();
        } else {
            //待ちぼうけ
//            _pStringBoard01->_pFader->behave();
            _pFont16_Wait->_pFader->behave();
        }
    }



#ifdef MY_DEBUG
    sprintf(_aBufDebug, "%05uDRAW / %06uCHK / %07uF /%.1fFPS", GgafGod::_num_actor_drawing, CollisionChecker::_num_check, (unsigned int)askGod()->_frame_of_God, askGod()->_fps);
    _pFont16_Debug->update(1*1000, 1*1000, _aBufDebug);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("_aBufDebug="<<_aBufDebug);
    }
#else
    sprintf(_aBufDebug, "%05uDRAW / %.1fFPS", GgafGod::_num_actor_drawing, askGod()->_fps);
    _pFont16_Debug->update(1*1000, 1*1000, _aBufDebug);
#endif


}

void World::processJudgement() {
}

World::~World() {
}

