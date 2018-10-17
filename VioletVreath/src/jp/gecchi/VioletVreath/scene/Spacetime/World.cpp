#include "World.h"

#include <stdio.h>
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi8Font.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "World/PreDrawScene.h"
#include "World/GameScene.h"
#include "Version.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_CALM1 ,
    PROG_CALM2 ,
    PROG_CALM3 ,
    PROG_CALM4 ,
    PROG_MAINLOOP ,
    PROG_BANPEI,
};

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");

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
    CollisionChecker::drawHitArea(nullptr);  //当たり判定領域表示用プリロード
#endif
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

    pLabel_warn_dual_view_ = desireActor(VioletVreath::LabelGecchi8Font, "WARN_DUAL_VIEW");
    pLabel_warn_dual_view_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringSceneMediator()->appendGroupChild(pLabel_warn_dual_view_);

    pLabel_need_reboot_ = desireActor(VioletVreath::LabelGecchi16Font, "reboot");
    bringSceneMediator()->appendGroupChild(pLabel_need_reboot_);
    pLabel_need_reboot_->update(PX_C(cx), PX_C(cy/2), "", ALIGN_CENTER, VALIGN_MIDDLE);

    std::string fix_str = CONFIG::FIXED_GAME_VIEW_ASPECT ? "ASPECT FIX" : "VIEW STRETCH";
    pixcoord w1,h1,w2,h2;
    pixcoord w1_bk,h1_bk,w2_bk,h2_bk;
    w1 = h1 = w2 = h2 = 0;
    w1_bk = h1_bk = w2_bk = h2_bk = 0;
    bool is_warn_dual_view = false;
    if (CONFIG::FULL_SCREEN && !CONFIG::DUAL_VIEW && CONFIG::_properties.getBool("DUAL_VIEW")) {
        //２画面フルスクリーン指定なのに、無理やり１画面フルスクリーンに設定された。
        is_warn_dual_view = true;
    }
    bool is_warn1 = false;
    bool is_warn2 = false;
    if (CONFIG::DUAL_VIEW) {
        if (CONFIG::FULL_SCREEN) {
            w1 = CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH;
            h1 = CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
            w2 = CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH;
            h2 = CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
            w1_bk = CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH_BK;
            h1_bk = CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK;
            w2_bk = CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH_BK;
            h2_bk = CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK;
            if (w1 != w1_bk || h1 != h1_bk) {
                is_warn1 = true;
            }
            if (w2 != w2_bk || h2 != h2_bk) {
                is_warn2 = true;
            }
        } else {
            w1 = CONFIG::DUAL_VIEW_WINDOW1_WIDTH;
            h1 = CONFIG::DUAL_VIEW_WINDOW1_HEIGHT;
            w2 = CONFIG::DUAL_VIEW_WINDOW2_WIDTH;
            h2 = CONFIG::DUAL_VIEW_WINDOW2_HEIGHT;
            w1_bk = w1;
            h1_bk = h1;
            w2_bk = w2;
            h2_bk = h2;
        }
    } else {
        if (CONFIG::FULL_SCREEN) {
            w1 = CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH;
            h1 = CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
            w1_bk = CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK;
            h1_bk = CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK;
            if (w1 != w1_bk || h1 != h1_bk) {
                is_warn1 = true;
            }
        } else {
            w1 = CONFIG::SINGLE_VIEW_WINDOW_WIDTH;
            h1 = CONFIG::SINGLE_VIEW_WINDOW_HEIGHT;
            w1_bk = w1;
            h1_bk = h1;
        }
    }

    if (CONFIG::DUAL_VIEW) {
        //解像度情報表示
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
        //解像度情報表示
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
    useProgress(PROG_BANPEI);
    getProgress()->reset(PROG_INIT);
}

void World::processBehavior() {

#ifdef MY_DEBUG
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_T)) {
        _TRACE_("-------------------- World dump() start --------------------------------");
        dump();
        _TRACE_("-------------------- World dump() end   --------------------------------");
    }
#endif


    DECLARE_HASHVAL(ASTER);

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            if (pGOD->chkCradle(1) == 2) {
                pPreDrawScene_ = (PreDrawScene*)receiveScene(1);
                appendChild(pPreDrawScene_);
                pProg->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PROG_CALM1: {
            if (pPreDrawScene_->getProgress()->get() == PreDrawScene::PROG_WAIT) {
                pLabel_title_->sayonara();
                pPreDrawScene_->sayonara(120);
                pProg->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PROG_CALM2: {
            if ((pProg->getFrame() >= 30 && pGOD->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX && pGOD->_fps <= 64.0f) || pProg->getFrame() >= 60*60*3) {
                pGameScene_ = (GameScene*)receiveScene(2);
                pProg->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PROG_CALM3: {
            if (pProg->hasJustChanged()) {
            }
            if ((pProg->getFrame() >= 30 && pGOD->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX && pGOD->_fps <= 64.0f) || pProg->getFrame() >= 60*60*3) {
                pProg->changeNext();
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PROG_CALM4: {
            if (pProg->hasJustChanged()) {
            }
            if (pProg->getFrame() >= 60) {
                pLabel_aster_->update("*");
                pLabel_aster_->sayonara(60);
                pLabel_resolution1_->sayonara();
                pLabel_resolution2_->sayonara();
                pLabel_warn1_->sayonara();
                pLabel_warn2_->sayonara();
                pLabel_warn_dual_view_->sayonara();
                pProg->changeNext(); //メインへループ
            }
            pLabel_aster_->getAlphaFader()->behave(); //右上＊チカチカ
            break;
        }

        case PROG_MAINLOOP: { //世界のメインループ
            if (pProg->hasJustChanged()) {
                appendChild(pGameScene_);
            }

            VB->update(); //入力情報更新

            //1キーが音量下げ
            if (GgafDxInput::isPressedKey(DIK_1)) {
                GgafDxSound::addAppMasterVolume(-10);
            }
            //2キーが音量上げ
            if (GgafDxInput::isPressedKey(DIK_2)) {
                GgafDxSound::addAppMasterVolume(10);
            }

            break;
        }
    }
    if (CONFIG::FULL_SCREEN) {
        //しばらくカーソルを動かさなければ消す。
        long mdx, mdy, mdz;
        GgafDxInput::getMousePointer_REL(&mdx, &mdy, &mdz);
        if (mdx == 0 && mdy == 0 && mdz == 0) {
            hide_cursor_cnt_++;
            if (hide_cursor_cnt_ == 3*60) {
                showCursor(false);
            }
        } else {
            hide_cursor_cnt_ = 0;
            showCursor(true);
        }
    }



#ifdef MY_DEBUG
    sprintf(aBufDebug_, "%07uF, %06u/%06uACT, %06uDRAW, %06uCHK, %03.1fFPS(SLOW%d), V%03d",
                            askGod()->_frame_of_God,
                            GgafGod::_num_active_actor,
                            GgafActor::_num_actors,
                            GgafGod::_num_drawing,
                            CollisionChecker::_num_check,
                            askGod()->_fps,
                            askGod()->_slowdown_mode,
                            (GgafDxSound::getAppMasterVolume())
                            );
    pLabel_debug_->update(aBufDebug_);
    if (getActiveFrame() % 60U == 0) {
        _TRACE_("***** "<<aBufDebug_);
    }
    if (pGOD->_sync_frame_time) {
        _TRACE_N_("z");
    }
#else
    sprintf(aBufDebug_, "%03.1fFPS", askGod()->_fps);
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

