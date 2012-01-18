#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");
    _is_create_GameScene = false;
    _pLabel_Debug = NULL;
    _pLabel_Aster = NULL;
    _pLabel_Title = NULL;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    pixcoord cy = CFG_PROPERTY(GAME_BUFFER_HEIGHT)/2;
    orderActorToFactory(0, LabelGecchi16Font, "STR01");
    _pLabel_Title = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Title);
    _pLabel_Title->update(PX2CO(cx), PX2CO(cy - 16),
                            "[ VIOLET VREATH ]", ALIGN_CENTER, VALIGN_MIDDLE);

    orderActorToFactory(0, LabelGecchi16Font, "STR01");
    _pLabel_Wait = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Wait);
    _pLabel_Wait->update(PX2CO(cx), PX2CO(cy + 16),
                            "WATE A MOMENT PLASE...", ALIGN_CENTER, VALIGN_MIDDLE);

    orderActorToFactory(0, LabelGecchi16Font, "ASTER");
    _pLabel_Aster = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Aster);
    _pLabel_Aster->update(PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    _pLabel_Aster->_pFader->beat(60, 30, 0, 0, -1); //チカチカ点滅
#ifdef MY_DEBUG
    ColliAABActor::get();     //当たり判定領域表示用直方体、プリロード
    ColliAAPrismActor::get(); //当たり判定領域表示用プリズム、プリロード
    ColliSphereActor::get();  //当たり判定領域表示用球、プリロード
#endif
    orderActorToFactory(0, LabelGecchi16Font, "DebugStr");
    _pLabel_Debug = (LabelGecchi16Font*)obtainActorFromFactory(0);
    getDirector()->addSubGroup(_pLabel_Debug);

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
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
        if (GgafDxInput::isBeingPressedKey(DIK_Q)) {
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
            _pLabel_Title->end();
            _pLabel_Wait->end();
            _pLabel_Aster->end();
        } else {
            //待ちぼうけ
            _pLabel_Aster->_pFader->behave();
        }
    }

#ifdef MY_DEBUG
    sprintf(_aBufDebug, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::_num_check,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
//            ((GgafFactory::CREATING_ORDER->_progress==1) ? GgafFactory::CREATING_ORDER->_pObject_Creation->toString() : "NOTHING"),
            ((GgafFactory::CREATING_ORDER->_progress==1) ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    _pLabel_Debug->update(PX2CO(1), PX2CO(1), _aBufDebug);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("_aBufDebug="<<_aBufDebug);
    }
#else
    sprintf(_aBufDebug, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::_num_check,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
            ((GgafFactory::CREATING_ORDER->_progress==1)  ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    _pLabel_Debug->update(PX2CO(1), PX2CO(1), _aBufDebug);
#endif


}

void World::processJudgement() {
}

World::~World() {
}

