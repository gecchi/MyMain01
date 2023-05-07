#include "World.h"

#include <stdio.h>
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/menu/MousePointer.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi8Font.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "World/PreDrawScene.h"
#include "World/GameScene.h"
#include "jp/gecchi/VioletVreath/Version.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_CALM1 ,
    PHASE_CALM2 ,
    PHASE_CALM3 ,
    PHASE_CALM4 ,
    PHASE_MAINLOOP ,
    PHASE_BANPEI,
};

World::World(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");

    pMousePointer_ = nullptr;

    pLabel_aster_ = NEW LabelGecchi16Font("ASTER");
    bringSceneMediator()->appendGroupChild(pLabel_aster_);
    pLabel_aster_->update(PX_C(CONFIG::GAME_BUFFER_WIDTH), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_aster_->getAlphaFader()->beat(30, 15, 0, 15, -1); //チカチカ点滅

    is_create_GameScene_ = false;
    pLabel_debug_ = nullptr;
    pLabel_title_ = nullptr;
    pLabel_resolution1_ = nullptr;
    pLabel_resolution2_ = nullptr;
    pLabel_warn1_ = nullptr;
    pLabel_warn2_ = nullptr;
    pLabel_warn_dual_view_ = nullptr;
    pPreDrawScene_ = nullptr;
    pGameScene_ = nullptr;

    need_reboot_ = 0;
    need_reboot_prev_ = need_reboot_;

    pLabel_need_reboot_ = nullptr;

    hide_cursor_cnt_ = 0;
    is_show_cursor_ = true;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_(FUNC_NAME<<"");
    pixcoord cx = CONFIG::GAME_BUFFER_WIDTH/2;
    pixcoord cy = CONFIG::GAME_BUFFER_HEIGHT/2;
    std::ostringstream os;
    os << "[ VIOLET VREATH ]\n" << VERSION << "\n" << "PLEASE WAIT A MOMENT ...";
    pLabel_title_ = desireActor(LabelGecchi16Font, "STR01");
    bringSceneMediator()->appendGroupChild(pLabel_title_);
    pLabel_title_->update(PX_C(cx), PX_C(cy/2),
                          os.str().c_str(),
                          ALIGN_CENTER, VALIGN_MIDDLE);

#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(nullptr);  //当たり判定領域表示用プリロード
#endif
    pMousePointer_ = desireActor(MousePointer);
    pMousePointer_->setDefaultKind(KIND_2DFIX_MOUSE_POINTER);
    bringSceneMediator()->appendGroupChild(pMousePointer_);

    pLabel_debug_ = desireActor(LabelGecchi16Font, "DebugStr");
    pLabel_debug_->update(PX_C(1), PX_C(1), "");
    bringSceneMediator()->appendGroupChild(pLabel_debug_);

    pLabel_resolution1_ = desireActor(VioletVreath::LabelGecchi16Font, "RESOLUTION1");
    pLabel_resolution1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringSceneMediator()->appendGroupChild(pLabel_resolution1_);
    pLabel_resolution2_ = desireActor(VioletVreath::LabelGecchi16Font, "RESOLUTION2");
    pLabel_resolution2_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringSceneMediator()->appendGroupChild(pLabel_resolution2_);

    pLabel_warn1_ = desireActor(VioletVreath::LabelGecchi8Font, "WARN1");
    pLabel_warn1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringSceneMediator()->appendGroupChild(pLabel_warn1_);
    pLabel_warn2_ = desireActor(VioletVreath::LabelGecchi8Font, "WARN2");
    pLabel_warn2_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringSceneMediator()->appendGroupChild(pLabel_warn2_);

    pLabel_warn_dual_view_ = desireActor(VioletVreath::LabelGecchi8Font, "WARN_DUAL_SCREEN");
    pLabel_warn_dual_view_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringSceneMediator()->appendGroupChild(pLabel_warn_dual_view_);

    pLabel_need_reboot_ = desireActor(VioletVreath::LabelGecchi16Font, "reboot");
    bringSceneMediator()->appendGroupChild(pLabel_need_reboot_);
    pLabel_need_reboot_->update(PX_C(cx), PX_C(cy/2), "", ALIGN_CENTER, VALIGN_MIDDLE);

    std::string primary_fix_str = CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01] ? "ASPECT FIX" : "VIEW STRETCH";
    std::string secondary_fix_str = CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN02] ? "ASPECT FIX" : "VIEW STRETCH";

    pixcoord w1,h1,w2,h2;
    pixcoord w1_bk,h1_bk,w2_bk,h2_bk;
    w1 = h1 = w2 = h2 = 0;
    w1_bk = h1_bk = w2_bk = h2_bk = 0;
    bool is_warn_dual_view = false;
    if (CONFIG::FULL_SCREEN && CONFIG::NUMBER_OF_SCREENS_USED == 1 && CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
        //２画面フルスクリーン指定なのに、無理やり１画面フルスクリーンに設定された。
        is_warn_dual_view = true;
    }
    bool is_warn1 = false;
    bool is_warn2 = false;
    if (CONFIG::NUMBER_OF_SCREENS_USED > 1) {
        if (CONFIG::FULL_SCREEN) {
            w1 = CONFIG::SCREEN_FULL_SCREEN[SCREEN01].WIDTH;
            h1 = CONFIG::SCREEN_FULL_SCREEN[SCREEN01].HEIGHT;
            w2 = CONFIG::SCREEN_FULL_SCREEN[SCREEN02].WIDTH;
            h2 = CONFIG::SCREEN_FULL_SCREEN[SCREEN02].HEIGHT;
            w1_bk = CONFIG::SCREEN_FULL_SCREEN_BK[SCREEN01].WIDTH;
            h1_bk = CONFIG::SCREEN_FULL_SCREEN_BK[SCREEN01].HEIGHT;
            w2_bk = CONFIG::SCREEN_FULL_SCREEN_BK[SCREEN02].WIDTH;
            h2_bk = CONFIG::SCREEN_FULL_SCREEN_BK[SCREEN02].HEIGHT;
            if (w1 != w1_bk || h1 != h1_bk) {
                is_warn1 = true;
            }
            if (w2 != w2_bk || h2 != h2_bk) {
                is_warn2 = true;
            }
        } else {
            w1 = CONFIG::SCREEN_WINDOW[SCREEN01].WIDTH;
            h1 = CONFIG::SCREEN_WINDOW[SCREEN01].HEIGHT;
            w2 = CONFIG::SCREEN_WINDOW[SCREEN02].WIDTH;
            h2 = CONFIG::SCREEN_WINDOW[SCREEN02].HEIGHT;
            w1_bk = w1;
            h1_bk = h1;
            w2_bk = w2;
            h2_bk = h2;
        }
    } else {
        if (CONFIG::FULL_SCREEN) {
            w1 = CONFIG::SCREEN_FULL_SCREEN[SCREEN01].WIDTH;
            h1 = CONFIG::SCREEN_FULL_SCREEN[SCREEN01].HEIGHT;
            w1_bk = CONFIG::SCREEN_FULL_SCREEN_BK[SCREEN01].WIDTH;
            h1_bk = CONFIG::SCREEN_FULL_SCREEN_BK[SCREEN01].HEIGHT;
            if (w1 != w1_bk || h1 != h1_bk) {
                is_warn1 = true;
            }
        } else {
            w1 = CONFIG::SCREEN_WINDOW[SCREEN01].WIDTH;
            h1 = CONFIG::SCREEN_WINDOW[SCREEN01].HEIGHT;
            w1_bk = w1;
            h1_bk = h1;
        }
    }

    if (CONFIG::NUMBER_OF_SCREENS_USED > 1) {
        //解像度情報表示
        pLabel_resolution1_->update(
            PX_C(cx/2), PX_C(cy),
            ("DISPLAY["+XTOS(pCARETAKER->_screen_pry_to_adapter_no[SCREEN01])+"] / PRIMARY GAME SCREEN \n"+
              XTOS(w1)+"*"+XTOS(h1)+"\n"+
              primary_fix_str).c_str()
        );
        if (is_warn1) {
            pLabel_warn1_->update(
                PX_C(cx/2), PX_C(cy+32),
                ("WARNING, "+XTOS(w1_bk)+"*"+XTOS(h1_bk)+" WAS NOT ABLE !").c_str()
            );
        }
        pLabel_resolution2_->update(
            PX_C(cx+(cx/2)), PX_C(cy),
            ("DISPLAY["+XTOS(pCARETAKER->_screen_pry_to_adapter_no[SCREEN02])+"] / SECONDARY GAME SCREEN\n"+
                    XTOS(w2)+"*"+XTOS(h2)+"\n"+
                    secondary_fix_str).c_str()
        );
        if (is_warn2) {
            pLabel_warn2_->update(
                PX_C(cx+(cx/2)), PX_C(cy+32),
                ("WARNING, "+XTOS(w2_bk)+"*"+XTOS(h2_bk)+" WAS NOT ABLE !").c_str()
            );
        }

    } else {
        //解像度情報表示
        pLabel_resolution1_->update(
            PX_C(cx), PX_C(cy),
            (""+XTOS(w1)+"*"+XTOS(h1)+"\n"+
                    primary_fix_str).c_str()
        );
        if (is_warn1) {
            pLabel_warn1_->update(
                PX_C(cx), PX_C(cy+32),
                ("WARNING, "+XTOS(w1_bk)+"*"+XTOS(h1_bk)+" WAS NOT ABLE !").c_str()
            );
        }
        //強制１画面警告表示
        if (is_warn_dual_view) {
            pLabel_warn_dual_view_->update(
                PX_C(cx), PX_C(cy-32),
                "WARNING, CAN NOT DUAL VIEW !"
            );
        }
    }
    requestScene(1, PreDrawScene);
    requestScene(2, GameScene);
    getPhase()->reset(PHASE_INIT);
}

void World::processBehavior() {
    DECLARE_EVENT_VAL(ASTER);
    Caretaker* pCaretaker = (Caretaker*)askCaretaker();
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            if (pCaretaker->chkCradle(1) == 2) {
                pPreDrawScene_ = (PreDrawScene*)receiveScene(1);
                appendChild(pPreDrawScene_);
                pPhase->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PHASE_CALM1: {
            if (pPreDrawScene_->getPhase()->getCurrent() == PreDrawScene::PHASE_WAIT) {
                pLabel_title_->sayonara();
                pPreDrawScene_->sayonara(120);
                pPhase->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PHASE_CALM2: {
            if ((pPhase->getFrame() >= SEC_F(0.5) && pCaretaker->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX && pCaretaker->_fps <= CONFIG::FPS*1.01) || pPhase->getFrame() >= SEC_F(60*3)) {
                waitForRequestActor(2); //GameScene 作成完了まで待つ
                pPhase->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PHASE_CALM3: {
            if (pPhase->hasJustChanged()) {
            }
            if ((pPhase->getFrame() >= 30 && pCaretaker->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX && pCaretaker->_fps <= CONFIG::FPS*1.01) || pPhase->getFrame() >= 60*60*3) {
                pPhase->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PHASE_CALM4: {
            if (pPhase->hasJustChanged()) {
            }
            if (pPhase->getFrame() >= SEC_F(1)) {
                pLabel_aster_->update("*");
                pLabel_aster_->sayonara(SEC_F(1));
                pLabel_resolution1_->sayonara();
                pLabel_resolution2_->sayonara();
                pLabel_warn1_->sayonara();
                pLabel_warn2_->sayonara();
                pLabel_warn_dual_view_->sayonara();
                pPhase->changeNext(); //メインへループ
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PHASE_MAINLOOP: { //世界のメインループ
            if (pPhase->hasJustChanged()) {
                pGameScene_ = (GameScene*)receiveScene(2);
                appendChild(pGameScene_);
            }

            VVB->update(); //入力情報更新

            //1キーが音量下げ
            if (GgafDx::Input::isPressedKey(DIK_1)) {
                GgafDx::Sound::addAppMasterVolume(-10);
            }
            //2キーが音量上げ
            if (GgafDx::Input::isPressedKey(DIK_2)) {
                GgafDx::Sound::addAppMasterVolume(10);
            }
            if (CONFIG::FULL_SCREEN) {
                //しばらくカーソルを動かさなければ消す。
                long mdx, mdy, mdz;
                GgafDx::Input::getMousePointer_REL(&mdx, &mdy, &mdz);
                if (mdx == 0 && mdy == 0 && mdz == 0) {
                    hide_cursor_cnt_++;
                    if (hide_cursor_cnt_ == SEC_F(3)) {
                        showCursor(false);
                        pMousePointer_->inactivate();
                    }
                } else {
                    hide_cursor_cnt_ = 0;
                    showCursor(true);
                    pMousePointer_->activate();
                }
            }

            break;
        }
    }



#ifdef MY_DEBUG

    sprintf(aBufDebug_, "%07uF, %05u/%05uACT, %04u/%04uDRAW, %06u(%06u/%03uDUP)CHK3D(%05uACT), %02uCHK2D(%02uACT), %03.1fFPS(SLOW%d), V%03d",
                            pCaretaker->_frame_of_Caretaker,
                            GgafCore::Caretaker::_num_active_actors,
                            GgafCore::Actor::_num_actors,
                            GgafCore::Caretaker::_num_draw,
                            GgafCore::Caretaker::_num_draw_actors,
                            WorldCollisionChecker::_num_check,
                            WorldCollisionChecker::_num_otoku_check,
                            WorldCollisionChecker::_num_zannen_check,
                            WorldCollisionChecker::_num_check_actors,
                            ViewCollisionChecker::_num_check,
                            ViewCollisionChecker::_num_check_actors,
                            pCaretaker->_fps,
                            pCaretaker->_slowdown_mode,
                            (GgafDx::Sound::getAppMasterVolume())
                            );
    pLabel_debug_->update(aBufDebug_);

    if (getActiveFrame() % CONFIG::FPS == 0) {
        _TRACE_("***** "<<aBufDebug_);
    }
//    if (pCaretaker->_sync_frame_time) {
//        _TRACE_N_("z");
//    }
#else
    sprintf(aBufDebug_, "%03.1fFPS(SLOW%d)", pCaretaker->_fps, pCaretaker->_slowdown_mode);
    pLabel_debug_->update(aBufDebug_);
#endif


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
    showCursor(true);
}

