#include "stdafx.h"
#include "World.h"

#include <stdio.h>
#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi8Font.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/PreDrawScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"
#include "jp/gecchi/VioletVreath/actor/InnerTitleBar.h"
#include "Version.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");

    pLabel_aster_ = NEW LabelGecchi16Font("ASTER");
    getSceneDirector()->addSubGroup(pLabel_aster_);
    pLabel_aster_->update(PX_C(PROPERTY::GAME_BUFFER_WIDTH), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_aster_->pAFader_->beat(30, 15, 0, 15, -1); //�`�J�`�J�_��

    is_create_GameScene_ = false;
    pLabel_debug_ = nullptr;
    pLabel_title_ = nullptr;
    pLabel_resolution1_ = nullptr;
    pLabel_resolution2_ = nullptr;
    pLabel_warn_dual_view_ = nullptr;
    pPreDrawScene_ = nullptr;
    pGameScene_ = nullptr;

    need_reboot_ = 0;
    need_reboot_prev_ = need_reboot_;

    pInnerTitleBar01_ = nullptr;
    pInnerTitleBar02_ = nullptr;
    close01_x1_ = 0;
    close01_y1_ = 0;
    close01_x2_ = 0;
    close01_y2_ = 0;
    close02_x1_ = 0;
    close02_y1_ = 0;
    close02_x2_ = 0;
    close02_y2_ = 0;
    hide_cursor_cnt_ = 0;
    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = PROPERTY::GAME_BUFFER_WIDTH/2;
    pixcoord cy = PROPERTY::GAME_BUFFER_HEIGHT/2;
    std::ostringstream os;
    os << "[ VIOLET VREATH ]\n" << VERSION << "\n" << "PLEASE WAIT A MOMENT ...";
    pLabel_title_ = createInFactory(LabelGecchi16Font, "STR01");
    getSceneDirector()->addSubGroup(pLabel_title_);
    pLabel_title_->update(PX_C(cx), PX_C(cy/2),
                          os.str().c_str(),
                          ALIGN_CENTER, VALIGN_MIDDLE);

#ifdef MY_DEBUG
    ColliAABActor::get();     //�����蔻��̈�\���p�����́A�v�����[�h
    ColliAAPrismActor::get(); //�����蔻��̈�\���p�v���Y���A�v�����[�h
    ColliSphereActor::get();  //�����蔻��̈�\���p���A�v�����[�h
#endif
    pLabel_debug_ = createInFactory(LabelGecchi16Font, "DebugStr");
    pLabel_debug_->update(PX_C(1), PX_C(1), "");
    getSceneDirector()->addSubGroup(pLabel_debug_);

    pLabel_resolution1_ = createInFactory(VioletVreath::LabelGecchi16Font, "RESOLUTION1");
    pLabel_resolution1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getSceneDirector()->addSubGroup(pLabel_resolution1_);
    pLabel_resolution2_ = createInFactory(VioletVreath::LabelGecchi16Font, "RESOLUTION2");
    pLabel_resolution2_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getSceneDirector()->addSubGroup(pLabel_resolution2_);

    pLabel_warn1_ = createInFactory(VioletVreath::LabelGecchi8Font, "WARN1");
    pLabel_warn1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getSceneDirector()->addSubGroup(pLabel_warn1_);
    pLabel_warn2_ = createInFactory(VioletVreath::LabelGecchi8Font, "WARN2");
    pLabel_warn2_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getSceneDirector()->addSubGroup(pLabel_warn2_);

    pLabel_warn_dual_view_ = createInFactory(VioletVreath::LabelGecchi8Font, "WARN_DUAL_VIEW");
    pLabel_warn_dual_view_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getSceneDirector()->addSubGroup(pLabel_warn_dual_view_);

    pLabel_need_reboot_ = createInFactory(VioletVreath::LabelGecchi16Font, "reboot");
    getSceneDirector()->addSubGroup(pLabel_need_reboot_);
    pLabel_need_reboot_->update(PX_C(cx), PX_C(cy/2), "", ALIGN_CENTER, VALIGN_MIDDLE);

    std::string fix_str = PROPERTY::FIXED_GAME_VIEW_ASPECT ? "ASPECT FIX" : "VIEW STRETCH";
    int w1,h1,w2,h2;
    int w1_bk,h1_bk,w2_bk,h2_bk;
    w1 = h1 = w2 = h2 = 0;
    w1_bk = h1_bk = w2_bk = h2_bk = 0;
    bool is_warn_dual_view = false;
    if (PROPERTY::FULL_SCREEN && !PROPERTY::DUAL_VIEW && PROPERTY::getBool("DUAL_VIEW")) {
        //�Q��ʃt���X�N���[���w��Ȃ̂ɁA�������P��ʃt���X�N���[���ɐݒ肳�ꂽ�B
        is_warn_dual_view = true;
    }
    bool is_warn1 = false;
    bool is_warn2 = false;
    if (PROPERTY::DUAL_VIEW) {
        if (PROPERTY::FULL_SCREEN) {
            w1 = PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH;
            h1 = PROPERTY::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
            w2 = PROPERTY::DUAL_VIEW_FULL_SCREEN2_WIDTH;
            h2 = PROPERTY::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
            w1_bk = PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK;
            h1_bk = PROPERTY::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK;
            w2_bk = PROPERTY::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK;
            h2_bk = PROPERTY::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK;
            if (w1 != w1_bk || h1 != h1_bk) {
                is_warn1 = true;
            }
            if (w2 != w2_bk || h2 != h2_bk) {
                is_warn2 = true;
            }

            pInnerTitleBar01_ = createInFactory(VioletVreath::InnerTitleBar, "InnerTitleBar01");
            pInnerTitleBar01_->graduate(0, PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH, PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH);
            pInnerTitleBar01_->position(C_PX(0), C_PX(0));
            getSceneDirector()->addSubGroup(pInnerTitleBar01_);
            //����{�^���̈�P
            coord h1 = (coord) pInnerTitleBar01_->getModelHeight();
            close01_x1_ = PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH - h1;
            close01_y1_ = 0;
            close01_x2_ = close01_x1_ + h1 - 1;
            close01_y2_ = close01_y1_ + h1 - 1;

            pInnerTitleBar02_ = createInFactory(VioletVreath::InnerTitleBar, "InnerTitleBar02");
            pInnerTitleBar02_->graduate(0, PROPERTY::DUAL_VIEW_FULL_SCREEN2_WIDTH, PROPERTY::DUAL_VIEW_FULL_SCREEN2_WIDTH);
            pInnerTitleBar02_->position(C_PX(0), C_PX(PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH));
            getSceneDirector()->addSubGroup(pInnerTitleBar02_);
            //����{�^���̈�Q
            coord h2 = (coord) pInnerTitleBar02_->getModelHeight();
            close02_x1_ = PROPERTY::DUAL_VIEW_FULL_SCREEN1_WIDTH + PROPERTY::DUAL_VIEW_FULL_SCREEN2_WIDTH - h2;
            close02_y1_ = 0;
            close02_x2_ = close02_x1_ + h2 - 1;
            close02_y2_ = close01_y1_ + h2 - 1;
        } else {
            w1 = PROPERTY::DUAL_VIEW_WINDOW1_WIDTH;
            h1 = PROPERTY::DUAL_VIEW_WINDOW1_HEIGHT;
            w2 = PROPERTY::DUAL_VIEW_WINDOW2_WIDTH;
            h2 = PROPERTY::DUAL_VIEW_WINDOW2_HEIGHT;
            w1_bk = w1;
            h1_bk = h1;
            w2_bk = w2;
            h2_bk = h2;
        }
    } else {
        if (PROPERTY::FULL_SCREEN) {
            w1 = PROPERTY::SINGLE_VIEW_FULL_SCREEN_WIDTH;
            h1 = PROPERTY::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
            w1_bk = PROPERTY::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK;
            h1_bk = PROPERTY::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK;
            if (w1 != w1_bk || h1 != h1_bk) {
                is_warn1 = true;
            }
            pInnerTitleBar01_ = createInFactory(VioletVreath::InnerTitleBar, "InnerTitleBar01");
            pInnerTitleBar01_->graduate(0, PROPERTY::SINGLE_VIEW_FULL_SCREEN_WIDTH, PROPERTY::SINGLE_VIEW_FULL_SCREEN_WIDTH);
            pInnerTitleBar01_->position(C_PX(0), C_PX(0));
            getSceneDirector()->addSubGroup(pInnerTitleBar01_);

            //����{�^���̈�P
            coord h1 = (coord) pInnerTitleBar01_->getModelHeight();
            close01_x1_ = PROPERTY::SINGLE_VIEW_FULL_SCREEN_WIDTH - h1;
            close01_y1_ = 0;
            close01_x2_ = close01_x1_ + h1 - 1;
            close01_y2_ = close01_y1_ + h1 - 1;

        } else {
            w1 = PROPERTY::SINGLE_VIEW_WINDOW_WIDTH;
            h1 = PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT;
            w1_bk = w1;
            h1_bk = h1;
        }
    }

    if (PROPERTY::DUAL_VIEW) {
        //�𑜓x���\��
        pLabel_resolution1_->update(
            PX_C(cx/2), PX_C(cy),
            ("[0] "+XTOS(w1)+"*"+XTOS(h1)+"\n"+
                    fix_str).c_str()
        );
        if (is_warn1) {
            pLabel_warn1_->update(
                PX_C(cx/2), PX_C(cy+32),
                ("WARNING, "+XTOS(w1_bk)+"*"+XTOS(h1_bk)+" WAS NOT ABLE !").c_str()
            );
        }
        pLabel_resolution2_->update(
            PX_C(cx+(cx/2)), PX_C(cy),
            ("[1] "+XTOS(w2)+"*"+XTOS(h2)+"\n"+
                    fix_str).c_str()
        );
        if (is_warn2) {
            pLabel_warn2_->update(
                PX_C(cx+(cx/2)), PX_C(cy+32),
                ("WARNING, "+XTOS(w2_bk)+"*"+XTOS(h2_bk)+" WAS NOT ABLE !").c_str()
            );
        }

    } else {
        //�𑜓x���\��
        pLabel_resolution1_->update(
            PX_C(cx), PX_C(cy),
            (""+XTOS(w1)+"*"+XTOS(h1)+"\n"+
                    fix_str).c_str()
        );
        if (is_warn1) {
            pLabel_warn1_->update(
                PX_C(cx), PX_C(cy+32),
                ("WARNING, "+XTOS(w1_bk)+"*"+XTOS(h1_bk)+" WAS NOT ABLE !").c_str()
            );
        }
        //�����P��ʌx���\��
        if (is_warn_dual_view) {
            pLabel_warn_dual_view_->update(
                PX_C(cx), PX_C(cy-32),
                "WARNING, CAN NOT DUAL VIEW !"
            );
        }

    }

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
    useProgress(World::PROG_BANPEI-1);
    getProgress()->reset(World::PROG_INIT);
}

void World::processBehavior() {

#ifdef MY_DEBUG
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_T)) {
        _TRACE_("-------------------- World dump() start --------------------------------");
        dump();
        _TRACE_("-------------------- World dump() end   --------------------------------");
    }
#endif
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case World::PROG_INIT: {
            if (GgafFactory::chkProgress(1) == 2) {
                pPreDrawScene_ = (PreDrawScene*)obtainSceneFromFactory(1);
                addSubLast(pPreDrawScene_);
                pProg->changeNext();
            }
            pLabel_aster_->pAFader_->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM1: {
            if (pPreDrawScene_->getProgress()->get() == PreDrawScene::PROG_WAIT) {
                pLabel_title_->sayonara();
                pPreDrawScene_->sayonara(120);
                pProg->changeNext();
            }
            pLabel_aster_->pAFader_->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM2: {
            if ((pProg->getFrameInProgress() >= 60 && P_GOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) || pProg->getFrameInProgress() >= 60*60*5) {
                pGameScene_ = (GameScene*)obtainSceneFromFactory(2);
                pProg->changeNext();
            }
            pLabel_aster_->pAFader_->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM3: {
            if (pProg->isJustChanged()) {
            }
            if ((pProg->getFrameInProgress() >= 60 && P_GOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) || pProg->getFrameInProgress() >= 60*60*5) {
                pProg->changeNext();
            }
            pLabel_aster_->pAFader_->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_CALM4: {
            if (pProg->isJustChanged()) {
            }
            if (pProg->getFrameInProgress() >= 60) {
                pLabel_aster_->update("*");
                pLabel_aster_->sayonara(60);
                pLabel_resolution1_->sayonara();
                pLabel_resolution2_->sayonara();
                pLabel_warn1_->sayonara();
                pLabel_warn2_->sayonara();
                pLabel_warn_dual_view_->sayonara();
                pProg->changeNext(); //���C���փ��[�v
            }
            pLabel_aster_->pAFader_->behave(); //�E�ざ�`�J�`�J
            break;
        }

        case World::PROG_MAINLOOP: { //���E�̃��C�����[�v
            if (pProg->isJustChanged()) {
                addSubLast(pGameScene_);
            }

            VB->update(); //���͏��X�V

            //F5�L�[�����ʉ���
            if (GgafDxInput::isBeingPressedKey(DIK_F5)) {
                GgafDxSound::addAppMasterVolume(-1);
            }
            //F6�L�[�����ʏグ
            if (GgafDxInput::isBeingPressedKey(DIK_F6)) {
                GgafDxSound::addAppMasterVolume(1);
            }

            break;
        }
    }
    GgafDxInput::updateMouseState();
    if (PROPERTY::FULL_SCREEN) {
        long mx,my,mz,mdx,mdy,mdz;
        GgafDxInput::getMousePointer(&mx, &my, &mz);
        GgafDxInput::getMousePointer_REL(&mdx, &mdy, &mdz);

        //���΂炭�J�[�\���𓮂����Ȃ���Ώ����B
        if (mdx == 0 && mdy == 0) {
            hide_cursor_cnt_++;
            if (hide_cursor_cnt_ == 3*60) {
                ShowCursor(FALSE);
            }
        } else {
            ShowCursor(TRUE);
            hide_cursor_cnt_ = 0;
        }
        //�t���X�N���[���p�^�C�g���o�[����
        if (pInnerTitleBar01_) {
            pInnerTitleBar01_->setAlpha(0.0);
            if (pInnerTitleBar02_) {
                pInnerTitleBar02_->setAlpha(0.0);
            }
            if (my <= close01_y2_) {
                //�o�[�P�o��
                if (0 <= mx || mx <= close01_x2_) {
                    if (hide_cursor_cnt_ < 3*60) {
                        pInnerTitleBar01_->setAlpha(1.0);
                    }
                }
                if (pInnerTitleBar02_) {
                    if (close01_x2_+1 <= mx || mx <= close02_x2_) {
                        //�o�[�Q�o��
                        if (hide_cursor_cnt_ < 3*60) {
                            pInnerTitleBar02_->setAlpha(1.0);
                        }
                    }
                }
            }
            if (GgafDxInput::isPushedDownMouseButton(0)) {
                ShowCursor(TRUE);
                hide_cursor_cnt_ = 0;
                //�o�c�{�^���͈̔͂ŃN���b�N�Ȃ�Α��I��
                if (close01_x1_ <= mx && mx <= close01_x2_ &&
                    close01_y1_ <= my && my <= close01_y2_ ) {
                    PostQuitMessage(0);
                }
                if (pInnerTitleBar02_) {
                    if (close02_x1_ <= mx && mx <= close02_x2_ &&
                        close02_y1_ <= my && my <= close02_y2_ ) {
                        PostQuitMessage(0);
                    }
                }
            }
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
    if (getActiveFrame() % 60U == 0) {
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
    if (need_reboot_prev_ != need_reboot_) {
        if (need_reboot_ > 0) {
            pLabel_need_reboot_->update("YOU NEED REBOOT !!!!");
        } else {
            pLabel_need_reboot_->update("");
        }
    }
    need_reboot_prev_ = need_reboot_;
}

World::~World() {
}

