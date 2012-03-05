#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");
    is_create_GameScene_ = false;
    pLabel_Debug_ = NULL;
    pLabel_Aster_ = NULL;
    pLabel_Title_ = NULL;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    pixcoord cy = GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2;
    orderActorToFactory(0, LabelGecchi16Font, "STR01");
    pLabel_Title_ = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(pLabel_Title_);
    pLabel_Title_->update(PX2CO(cx), PX2CO(cy - 16),
                            "[ VIOLET VREATH ]", ALIGN_CENTER, VALIGN_MIDDLE);

    orderActorToFactory(0, LabelGecchi16Font, "STR01");
    pLabel_Wait_ = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(pLabel_Wait_);
    pLabel_Wait_->update(PX2CO(cx), PX2CO(cy + 16),
                            "WATE A MOMENT PLASE...", ALIGN_CENTER, VALIGN_MIDDLE);

    orderActorToFactory(0, LabelGecchi16Font, "ASTER");
    pLabel_Aster_ = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(pLabel_Aster_);
    pLabel_Aster_->update(PX2CO(GGAF_PROPERTY(GAME_BUFFER_WIDTH)), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_Aster_->_pFader->beat(60, 30, 0, 0, -1); //チカチカ点滅
#ifdef MY_DEBUG
    ColliAABActor::get();     //当たり判定領域表示用直方体、プリロード
    ColliAAPrismActor::get(); //当たり判定領域表示用プリズム、プリロード
    ColliSphereActor::get();  //当たり判定領域表示用球、プリロード
#endif
    orderActorToFactory(0, LabelGecchi16Font, "DebugStr");
    pLabel_Debug_ = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(pLabel_Debug_);

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
}

void World::processBehavior() {
    if (is_create_GameScene_) {
        //GameScene作成完了
        VB->update(); //入力情報更新
#ifdef MY_DEBUG
        if (P_GOD->_sync_frame_time) {
            _TEXT_("z");
        }
#endif
        if (GgafDxInput::isBeingPressedKey(DIK_Q)) {
            //TODO:終了処理
        }
    } else {
        //GameScene作成完了まで待つ
        if (GgafFactory::chkProgress(1) == 2 && GgafFactory::chkProgress(2) == 2) {
            pPreDrawScene_ = (PreDrawScene*)obtainSceneFromFactory(1);
            addSubLast(pPreDrawScene_);
            pGameScene_ = (GameScene*)obtainSceneFromFactory(2);
            addSubLast(pGameScene_);
            is_create_GameScene_ = true;
            pLabel_Title_->end();
            pLabel_Wait_->end();
            pLabel_Aster_->end();
        } else {
            //待ちぼうけ
            pLabel_Aster_->_pFader->behave();
        }
    }

#ifdef MY_DEBUG
    sprintf(aBufDebug_, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::_num_check,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
//            ((GgafFactory::CREATING_ORDER->progress_==1) ? GgafFactory::CREATING_ORDER->pObject_Creation_->toString() : "NOTHING"),
            ((GgafFactory::CREATING_ORDER->_progress==1) ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    pLabel_Debug_->update(PX2CO(1), PX2CO(1), aBufDebug_);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("aBufDebug_="<<aBufDebug_);
    }
#else
    sprintf(aBufDebug_, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::num_check_,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
            ((GgafFactory::CREATING_ORDER->progress_==1)  ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    pLabel_Debug_->update(PX2CO(1), PX2CO(1), aBufDebug_);
#endif


}

void World::processJudgement() {
}

World::~World() {
}

