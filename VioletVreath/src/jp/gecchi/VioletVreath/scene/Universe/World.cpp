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
    bringDirector()->addSubGroup(pLabel_aster_);
    pLabel_aster_->update(PX_C(PROPERTY::GAME_BUFFER_WIDTH), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_aster_->pAFader_->beat(30, 15, 0, 15, -1); //チカチカ点滅

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

    hide_cursor_cnt_ = 0;
    is_show_cursor_ = true;
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = PROPERTY::GAME_BUFFER_WIDTH/2;
    pixcoord cy = PROPERTY::GAME_BUFFER_HEIGHT/2;
    std::ostringstream os;
    os << "[ VIOLET VREATH ]\n" << VERSION << "\n" << "PLEASE WAIT A MOMENT ...";
    pLabel_title_ = createInFactory(LabelGecchi16Font, "STR01");
    bringDirector()->addSubGroup(pLabel_title_);
    pLabel_title_->update(PX_C(cx), PX_C(cy/2),
                          os.str().c_str(),
                          ALIGN_CENTER, VALIGN_MIDDLE);

#ifdef MY_DEBUG
    ColliAABActor::get();     //当たり判定領域表示用直方体、プリロード
    ColliAAPrismActor::get(); //当たり判定領域表示用プリズム、プリロード
    ColliSphereActor::get();  //当たり判定領域表示用球、プリロード
#endif
    pLabel_debug_ = createInFactory(LabelGecchi16Font, "DebugStr");
    pLabel_debug_->update(PX_C(1), PX_C(1), "");
    bringDirector()->addSubGroup(pLabel_debug_);

    pLabel_resolution1_ = createInFactory(VioletVreath::LabelGecchi16Font, "RESOLUTION1");
    pLabel_resolution1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringDirector()->addSubGroup(pLabel_resolution1_);
    pLabel_resolution2_ = createInFactory(VioletVreath::LabelGecchi16Font, "RESOLUTION2");
    pLabel_resolution2_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringDirector()->addSubGroup(pLabel_resolution2_);

    pLabel_warn1_ = createInFactory(VioletVreath::LabelGecchi8Font, "WARN1");
    pLabel_warn1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringDirector()->addSubGroup(pLabel_warn1_);
    pLabel_warn2_ = createInFactory(VioletVreath::LabelGecchi8Font, "WARN2");
    pLabel_warn2_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringDirector()->addSubGroup(pLabel_warn2_);

    pLabel_warn_dual_view_ = createInFactory(VioletVreath::LabelGecchi8Font, "WARN_DUAL_VIEW");
    pLabel_warn_dual_view_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    bringDirector()->addSubGroup(pLabel_warn_dual_view_);

    pLabel_need_reboot_ = createInFactory(VioletVreath::LabelGecchi16Font, "reboot");
    bringDirector()->addSubGroup(pLabel_need_reboot_);
    pLabel_need_reboot_->update(PX_C(cx), PX_C(cy/2), "", ALIGN_CENTER, VALIGN_MIDDLE);

    std::string fix_str = PROPERTY::FIXED_GAME_VIEW_ASPECT ? "ASPECT FIX" : "VIEW STRETCH";
    pixcoord w1,h1,w2,h2;
    pixcoord w1_bk,h1_bk,w2_bk,h2_bk;
    w1 = h1 = w2 = h2 = 0;
    w1_bk = h1_bk = w2_bk = h2_bk = 0;
    bool is_warn_dual_view = false;
    if (PROPERTY::FULL_SCREEN && !PROPERTY::DUAL_VIEW && PROPERTY::getBool("DUAL_VIEW")) {
        //２画面フルスクリーン指定なのに、無理やり１画面フルスクリーンに設定された。
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
        } else {
            w1 = PROPERTY::SINGLE_VIEW_WINDOW_WIDTH;
            h1 = PROPERTY::SINGLE_VIEW_WINDOW_HEIGHT;
            w1_bk = w1;
            h1_bk = h1;
        }
    }

    if (PROPERTY::DUAL_VIEW) {
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
            pLabel_aster_->pAFader_->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_CALM1: {
            if (pPreDrawScene_->getProgress()->get() == PreDrawScene::PROG_WAIT) {
                pLabel_title_->sayonara();
                pPreDrawScene_->sayonara(120);
                pProg->changeNext();
            }
            pLabel_aster_->pAFader_->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_CALM2: {
            if ((pProg->getFrame() >= 60 && P_GOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) || pProg->getFrame() >= 60*60*5) {
                pGameScene_ = (GameScene*)obtainSceneFromFactory(2);
                pProg->changeNext();
            }
            pLabel_aster_->pAFader_->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_CALM3: {
            if (pProg->isJustChanged()) {
            }
            if ((pProg->getFrame() >= 60 && P_GOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) || pProg->getFrame() >= 60*60*5) {
                pProg->changeNext();
            }
            pLabel_aster_->pAFader_->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_CALM4: {
            if (pProg->isJustChanged()) {
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
            pLabel_aster_->pAFader_->behave(); //右上＊チカチカ
            break;
        }

        case World::PROG_MAINLOOP: { //世界のメインループ
            if (pProg->isJustChanged()) {
                addSubLast(pGameScene_);
            }

            VB->update(); //入力情報更新

            //F5キーが音量下げ
            if (GgafDxInput::isBeingPressedKey(DIK_F5)) {
                GgafDxSound::addAppMasterVolume(-1);
            }
            //F6キーが音量上げ
            if (GgafDxInput::isBeingPressedKey(DIK_F6)) {
                GgafDxSound::addAppMasterVolume(1);
            }

            break;
        }
    }
    if (PROPERTY::FULL_SCREEN) {
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
        _TRACE_N_("z");
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
    showCursor(true);
}

