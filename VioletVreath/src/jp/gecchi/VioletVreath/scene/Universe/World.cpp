#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");

    pLabel_Aster_ = NEW LabelGecchi16Font("ASTER");
    getDirector()->addSubGroup(pLabel_Aster_);
    pLabel_Aster_->update(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_Aster_->_pFader->beat(60, 30, 0, 0, -1); //チカチカ点滅

    is_create_GameScene_ = false;
    pLabel_Debug_ = NULL;
    pLabel_Title_ = NULL;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    pixcoord cy = GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2;

    pLabel_Title_ = createInFactory(LabelGecchi16Font, "STR01");
    getDirector()->addSubGroup(pLabel_Title_);
    pLabel_Title_->update(PX_C(cx), PX_C(cy),
                          "[ VIOLET VREATH ]\nVERSION 0.0.1\nPLEASE WAIT A MOMENT ...",
                          ALIGN_CENTER, VALIGN_MIDDLE);

#ifdef MY_DEBUG
    ColliAABActor::get();     //当たり判定領域表示用直方体、プリロード
    ColliAAPrismActor::get(); //当たり判定領域表示用プリズム、プリロード
    ColliSphereActor::get();  //当たり判定領域表示用球、プリロード
#endif
    pLabel_Debug_ = createInFactory(LabelGecchi16Font, "DebugStr");
    pLabel_Debug_->update(PX_C(1), PX_C(1), "");
    getDirector()->addSubGroup(pLabel_Debug_);

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
    useProgress(World::PROG_MAINLOOP);
    _pProg->set(World::PROG_INIT);
}

void World::processBehavior() {
    switch (_pProg->get()) {
        case World::PROG_INIT: {
            if (GgafFactory::chkProgress(1) == 2) {
                pPreDrawScene_ = (PreDrawScene*)obtainSceneFromFactory(1);
                addSubLast(pPreDrawScene_);
                _pProg->changeNext();
            }
            pLabel_Aster_->_pFader->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_CALM1: {
            if (_pProg->getFrameInProgress() >= 60 &&
                GgafFactory::chkProgress(2) == 2 &&
                pPreDrawScene_->_pProg->get() == PreDrawScene::PROG_WAIT &&
                P_GOD->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX))
            {
                pLabel_Title_->sayonara();
                _pProg->changeNext();
            }
            pLabel_Aster_->_pFader->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_CALM2: {
            if (_pProg->getFrameInProgress() >= 60 && P_GOD->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                pGameScene_ = (GameScene*)obtainSceneFromFactory(2);
                _pProg->changeNext();
            }
            pLabel_Aster_->_pFader->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_CALM3: {
            if (_pProg->getFrameInProgress() <= 120) {
                pLabel_Aster_->_pFader->behave(); //右上＊チカチカ
                if (_pProg->getFrameInProgress() == 70) {
                    pLabel_Aster_->update("!");
                }
                if (_pProg->getFrameInProgress() == 120) {
                    pLabel_Aster_->sayonara();
                    _pProg->changeNext(); //メインへ！
                }
            }
            break;
        }

        case World::PROG_MAINLOOP: {
            if (_pProg->hasJustChanged()) {
                addSubLast(pGameScene_);
            }

            //GameScene作成完了
            VB->update(); //入力情報更新

            //F5キーが音量下げ
            if (GgafDxInput::isBeingPressedKey(DIK_F5)) {
                GgafDxSound::addMasterVolume(-1);
            }
            //F6キーが音量上げ
            if (GgafDxInput::isBeingPressedKey(DIK_F6)) {
                GgafDxSound::addMasterVolume(1);
            }

            break;
        }
    }

#ifdef MY_DEBUG
    sprintf(aBufDebug_, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / V%03d",
                            GgafGod::_num_actor_drawing,
                            CollisionChecker::_num_check,
                            (unsigned int)askGod()->_frame_of_God,
                            askGod()->_fps,
                            (GgafDxSound::_master_volume)
                            );
    pLabel_Debug_->update(aBufDebug_);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("aBufDebug_="<<aBufDebug_);
    }
    if (P_GOD->_sync_frame_time) {
        _TEXT_("z");
    }
#else
    sprintf(aBufDebug_, "%03.1fFPS", askGod()->_fps);
    pLabel_Debug_->update(aBufDebug_);
#endif

}

void World::processJudgement() {
}

World::~World() {
}

