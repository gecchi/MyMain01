#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");

    pLabel_aster_ = NEW LabelGecchi16Font("ASTER");
    getDirector()->addSubGroup(pLabel_aster_);
    pLabel_aster_->update(PX_C(PROPERTY::GAME_BUFFER_WIDTH), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_aster_->_pAFader->beat(30, 15, 0, 0, -1); //�`�J�`�J�_��

    is_create_GameScene_ = false;
    pLabel_debug_ = nullptr;
    pLabel_title_ = nullptr;
    pLabel_resolution1_ = nullptr;
    pLabel_resolution2_ = nullptr;
    pPreDrawScene_ = nullptr;
    pGameScene_ = nullptr;
    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = PROPERTY::GAME_BUFFER_WIDTH/2;
    pixcoord cy = PROPERTY::GAME_BUFFER_HEIGHT/2;

    pLabel_title_ = createInFactory(VioletVreath::LabelGecchi16Font, "STR01");
    getDirector()->addSubGroup(pLabel_title_);
    pLabel_title_->update(PX_C(cx), PX_C(cy/2),
                          "[ VIOLET VREATH ]\nPLEASE WAIT A MOMENT ...",
                          ALIGN_CENTER, VALIGN_MIDDLE);

#ifdef MY_DEBUG
    ColliAABActor::get();     //�����蔻��̈�\���p�����́A�v�����[�h
    ColliAAPrismActor::get(); //�����蔻��̈�\���p�v���Y���A�v�����[�h
    ColliSphereActor::get();  //�����蔻��̈�\���p���A�v�����[�h
#endif
    pLabel_debug_ = createInFactory(VioletVreath::LabelGecchi16Font, "DebugStr");
    pLabel_debug_->update(PX_C(1), PX_C(1), "");
    getDirector()->addSubGroup(pLabel_debug_);

    pLabel_resolution1_ = createInFactory(VioletVreath::LabelGecchi16Font, "RESOLUTION1");
    pLabel_resolution1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getDirector()->addSubGroup(pLabel_resolution1_);
    pLabel_resolution2_ = createInFactory(VioletVreath::LabelGecchi16Font, "RESOLUTION2");
    pLabel_resolution2_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getDirector()->addSubGroup(pLabel_resolution2_);

    std::string fix_str = PROPERTY::FIXED_GAME_VIEW_ASPECT ? "ASPECT FIX" : "ASPECT STRETCH";
    if (PROPERTY::DUAL_VIEW) {
        //�Q���
        if (PROPERTY::FULL_SCREEN) {
            pLabel_resolution1_->update(
                PX_C(cx/2), PX_C(cy),
                ("(1) "+XTOS(PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH)+"X"+XTOS(PROPERTY::DUAL_VIEW_FULL_SCREEN1_HEIGHT)+"\n"+
                        fix_str).c_str()
            );
            pLabel_resolution2_->update(
                PX_C(cx+(cx/2)), PX_C(cy),
                ("(2) "+XTOS(PROPERTY::DUAL_VIEW_FULL_SCREEN2_WIDTH)+"X"+XTOS(PROPERTY::DUAL_VIEW_FULL_SCREEN2_HEIGHT)+"\n"+
                        fix_str).c_str()
            );
        } else {
            pLabel_resolution1_->update(
                PX_C(cx/2), PX_C(cy),
                ("(1) "+XTOS(PROPERTY::DUAL_VIEW_WINDOW1_WIDTH)+"X"+XTOS(PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT)+"\n"+
                        fix_str).c_str()
            );
            pLabel_resolution2_->update(
                PX_C(cx+(cx/2)), PX_C(cy),
                ("(2) "+XTOS(PROPERTY::DUAL_VIEW_WINDOW2_WIDTH)+"X"+XTOS(PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT)+"\n"+
                        fix_str).c_str()
            );
        }
    } else {
        //�P���
        pLabel_resolution2_->update("");
        if (PROPERTY::FULL_SCREEN) {
            pLabel_resolution1_->update(
                PX_C(cx), PX_C(cy),
                (XTOS(PROPERTY::SINGLE_VIEW_FULL_SCREEN_WIDTH) + "X" + XTOS(PROPERTY::SINGLE_VIEW_FULL_SCREEN_HEIGHT)+"\n"+
                        fix_str).c_str()
            );
        } else {
            pLabel_resolution1_->update(
                PX_C(cx), PX_C(cy),
                (XTOS(PROPERTY::SINGLE_VIEW_WINDOW_WIDTH) + "X" + XTOS(PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT)+"\n"+
                        fix_str).c_str()
            );
        }
    }


    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
    useProgress(World::PROG_MAINLOOP);
    _pProg->reset(World::PROG_INIT);
}

void World::processBehavior() {
    switch (_pProg->get()) {
        case World::PROG_INIT: {
            if (GgafFactory::chkProgress(1) == 2) {
                pPreDrawScene_ = (PreDrawScene*)obtainSceneFromFactory(1);
                addSubLast(pPreDrawScene_);
                _pProg->changeNext();
            }
            pLabel_aster_->_pAFader->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM1: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() >= 60 &&
                GgafFactory::chkProgress(2) == 2 &&
                pPreDrawScene_->_pProg->get() == PreDrawScene::PROG_WAIT &&
                 ( P_GOD->_fps > PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX || _pProg->getFrameInProgress() == 60*60*10)
            ) {
                pLabel_title_->sayonara();
                _pProg->changeNext();
            }
            pLabel_aster_->_pAFader->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM2: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() >= 60 &&
                ( P_GOD->_fps > PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX || _pProg->getFrameInProgress() == 60*60*5)
            ) {
                pGameScene_ = (GameScene*)obtainSceneFromFactory(2);
                _pProg->changeNext();
            }
            pLabel_aster_->_pAFader->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM3: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() >= 60 &&
                ( P_GOD->_fps > PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX || _pProg->getFrameInProgress() == 60*60*5)
            ) {
                _pProg->changeNext();
            }
            pLabel_aster_->_pAFader->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM4: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() == 60) {
                pLabel_aster_->update("*");
                pLabel_aster_->sayonara(60);
                pLabel_resolution1_->sayonara();
                pLabel_resolution2_->sayonara();
                _pProg->changeNext(); //���C���փ��[�v
            }
            pLabel_aster_->_pAFader->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_MAINLOOP: { //���E�̃��C�����[�v
            if (_pProg->isJustChanged()) {
                addSubLast(pGameScene_);
            }

            VB->update(); //���͏��X�V

            //F5�L�[�����ʉ���
            if (GgafDxInput::isBeingPressedKey(DIK_F5)) {
                GgafDxSound::addApplicationMasterVolume(-1);
            }
            //F6�L�[�����ʏグ
            if (GgafDxInput::isBeingPressedKey(DIK_F6)) {
                GgafDxSound::addApplicationMasterVolume(1);
            }

            break;
        }
    }

#ifdef MY_DEBUG
    sprintf(aBufDebug_, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / V%03d",
                            GgafGod::_num_actor_drawing,
                            CollisionChecker3D::_num_check,
                            (unsigned int)askGod()->_frame_of_God,
                            askGod()->_fps,
                            (GgafDxSound::_app_master_volume)
                            );
    pLabel_debug_->update(aBufDebug_);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("aBufDebug_="<<aBufDebug_);
    }
    if (P_GOD->_sync_frame_time) {
        _TEXT_("z");
    }
#else
    sprintf(aBufDebug_, "%03.1fFPS", askGod()->_fps);
    pLabel_debug_->update(aBufDebug_);
#endif

}

void World::processJudgement() {
}

World::~World() {
}

