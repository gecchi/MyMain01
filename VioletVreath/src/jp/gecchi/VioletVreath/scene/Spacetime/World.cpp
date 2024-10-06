#include "World.h"

#include <stdio.h>
#include "jp/ggaf/core/actor/SceneChief.h"
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
    getSceneChief()->appendChild(pLabel_aster_);
    pLabel_aster_->update(PX_C(CONFIG::GAME_BUFFER_WIDTH), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_aster_->getAlphaFader()->beat(30, 15, 0, 15, -1); //チカチカ点滅

    is_create_GameScene_ = false;
    pLabel_debug_ = nullptr;
    pLabel_title_ = nullptr;
//    pLabel_resolution1_ = nullptr;
//    pLabel_resolution2_ = nullptr;
    papLabel_resolution_ = nullptr;
//    pLabel_warn1_ = nullptr;
//    pLabel_warn2_ = nullptr;
    papLabel_warn_ = nullptr;

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
    getSceneChief()->appendChild(pLabel_title_);
    pLabel_title_->update(PX_C(cx), PX_C(cy/2),
                          os.str().c_str(),
                          ALIGN_CENTER, VALIGN_MIDDLE);

#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(nullptr);  //当たり判定領域表示用プリロード
#endif
    pMousePointer_ = desireActor(MousePointer);
    pMousePointer_->setCheckerKind(KIND_2DFIX_MOUSE_POINTER);
    getSceneChief()->appendChild(pMousePointer_);

    pLabel_debug_ = desireActor(LabelGecchi16Font, "DebugStr");
    pLabel_debug_->update(PX_C(1), PX_C(1), "");
    getSceneChief()->appendChild(pLabel_debug_);

    papLabel_resolution_ = NEW LabelGecchi16Font*[CONFIG::NUMBER_OF_SCREENS_USED];
    for (int n = 0; n < CONFIG::NUMBER_OF_SCREENS_USED; n++) {
        papLabel_resolution_[n] = desireActor(VioletVreath::LabelGecchi16Font, "RESOLUTION");
        papLabel_resolution_[n]->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        getSceneChief()->appendChild(papLabel_resolution_[n]);
    }

    papLabel_warn_ = NEW LabelGecchi8Font*[CONFIG::NUMBER_OF_SCREENS_USED];
    for (int n = 0; n < CONFIG::NUMBER_OF_SCREENS_USED; n++) {
        papLabel_warn_[n] =  desireActor(VioletVreath::LabelGecchi8Font, "WARN");
        papLabel_warn_[n]->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        getSceneChief()->appendChild(papLabel_warn_[n]);
    }
    pLabel_warn_dual_view_ = desireActor(VioletVreath::LabelGecchi8Font, "WARN_DUAL_SCREEN");
    pLabel_warn_dual_view_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    getSceneChief()->appendChild(pLabel_warn_dual_view_);

    pLabel_need_reboot_ = desireActor(VioletVreath::LabelGecchi16Font, "reboot");
    getSceneChief()->appendChild(pLabel_need_reboot_);
    pLabel_need_reboot_->update(PX_C(cx), PX_C(cy/2), "", ALIGN_CENTER, VALIGN_MIDDLE);

    std::string primary_fix_str = CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01] ? "ASPECT FIX" : "VIEW STRETCH";
    std::string secondary_fix_str = CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN02] ? "ASPECT FIX" : "VIEW STRETCH";

    pixcoord w[MAX_SCREENS];
    pixcoord h[MAX_SCREENS];
    pixcoord w_bk[MAX_SCREENS];
    pixcoord h_bk[MAX_SCREENS];
    bool is_warn[MAX_SCREENS];
    for (int n = 0; n < MAX_SCREENS; n++) {
        w[n] = h[n] = w_bk[n] = h_bk[n] = 0;
        is_warn[n] = false;
    }

    bool is_warn_dual_view = false;
    if (CONFIG::FULL_SCREEN && CONFIG::NUMBER_OF_SCREENS_USED == 1 && CONFIG::_properties.getInt("NUMBER_OF_SCREENS_USED") > 1) {
        //２画面フルスクリーン指定なのに、無理やり１画面フルスクリーンに設定された。
        is_warn_dual_view = true;
    }
    if (CONFIG::FULL_SCREEN) {
        for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) {
            w[pry] =  CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
            h[pry] = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            w_bk[pry] = CONFIG::SCREEN_FULL_SCREEN_BK[pry].WIDTH;
            h_bk[pry] = CONFIG::SCREEN_FULL_SCREEN_BK[pry].HEIGHT;
            if (w[pry] != w_bk[pry] || h[pry] != h_bk[pry]) {
                is_warn[pry] = true;
            }

        }
    } else {
        for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) {
            w[pry] =  CONFIG::SCREEN_WINDOW[pry].WIDTH;
            h[pry] = CONFIG::SCREEN_WINDOW[pry].HEIGHT;
            w_bk[pry] = w[pry];
            h_bk[pry] = h[pry];
        }
    }

    for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) {
         //解像度情報表示
        pixcoord s_left = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT;
        pixcoord s_top = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP;
        pixcoord s_width = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH;
        pixcoord s_height = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT;
        int ncx = s_left + (s_width/2);
        int ncy = s_top + (s_height/2);
        papLabel_resolution_[pry]->update(
            PX_C(ncx), PX_C(ncy),
            ("GAME SCREEN "+XTOS(pry+1)+" / DISPLAY "+XTOS(pCARETAKER->_screen_pry_to_adapter_index[pry] + 1)+" \n"+
              XTOS(w[pry])+"*"+XTOS(h[pry])+"\n"+
              primary_fix_str).c_str()
        );
        if (is_warn[pry]) {
            papLabel_warn_[pry]->update(
                PX_C(ncx), PX_C(ncy+32),
                ("(WARNING !, FAILED TO "+XTOS(w_bk[pry])+"*"+XTOS(h_bk[pry])+")").c_str()
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
                for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) {
                    papLabel_resolution_[pry]->sayonara();
                    papLabel_warn_[pry]->sayonara();
                }
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
    int honrai_check_num = (WorldCollisionChecker::_num_check - WorldCollisionChecker::_num_zannen_check + WorldCollisionChecker::_num_otoku_check_actors);
    int otoku_per = 0;
    if (honrai_check_num > 0 ) {
        otoku_per = (int)((1.0 - ((WorldCollisionChecker::_num_check * 1.0) / honrai_check_num)) * 100);
    }

    sprintf(aBufDebug_, "%07uF, %05u/%05uACT, %04uDRAW@%04uACT, %06uCHK3D(%03d%%CUT)@%05uACT, %02uCHK2D@%02uACT, %03.1fFPS(SLOW%d), V%03d",
                            pCaretaker->_frame_of_Caretaker,
                            GgafCore::Caretaker::_num_active_actors,
                            GgafCore::Actor::_num_actors,
                            GgafCore::Caretaker::_num_draw,
                            GgafCore::Caretaker::_num_draw_actors,
                            WorldCollisionChecker::_num_check,
                            otoku_per,
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
    GGAF_DELETEARR(papLabel_resolution_);
    GGAF_DELETEARR(papLabel_warn_);
    showCursor(true);
}

