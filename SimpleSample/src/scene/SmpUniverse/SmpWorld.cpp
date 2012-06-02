#include "stdafx.h"
using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");      //キャラ作成＆保持
    getDirector()->addSubGroup(pActor_); //キャラをシーン監督の配下に所属（表示される）
    GgafLib::VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //ボタン１=スペースキー とする。
}
void SmpWorld::initialize() {
    _TRACE_("World::initialize()");
    //TEST
    papTest_ = NEW SmpLabel*[9];
    for (int i = 0; i < 9; i++) {
        papTest_[i] = NEW SmpLabel("tst");
        getDirector()->addSubGroup(papTest_[i]);
    }
    for (int i = 0; i < 9; i++) {
        papTest_[i]->update("ABCDEFGH\nIJKLMN\nOPQRS\nTUVWXY\nZ");
    }
    //papTest_[0]->setAlign(ALIGN_LEFT, VALIGN_TOP);
    //papTest_[0]->locate(0 , 0);


//    papTest_[0]->setAlign(ALIGN_LEFT, VALIGN_BOTTOM);
//    papTest_[0]->locate(0                                      , PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)));
//
//    papTest_[1]->setAlign(ALIGN_CENTER, VALIGN_BOTTOM);
//    papTest_[1]->locate(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2), PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)));
//
//    papTest_[2]->setAlign(ALIGN_RIGHT, VALIGN_BOTTOM);
//    papTest_[2]->locate(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))  , PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)));
//
//
//    papTest_[3]->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
//    papTest_[3]->locate(0                                       , PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2));
//
//    papTest_[4]->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
//    papTest_[4]->locate(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2), PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2));
//
//    papTest_[5]->setAlign(ALIGN_RIGHT, VALIGN_MIDDLE);
//    papTest_[5]->locate(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))  , PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2));
//
//    papTest_[6]->setAlign(ALIGN_LEFT, VALIGN_TOP);
//    papTest_[6]->locate(0                                       , 0);
//
//    papTest_[7]->setAlign(ALIGN_CENTER, VALIGN_TOP);
//    papTest_[7]->locate(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2), 0);
//
//    papTest_[8]->setAlign(ALIGN_RIGHT, VALIGN_TOP);
//    papTest_[8]->locate(PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH))  , 0);
//
//
//





    papTest_[0]->setAlign(ALIGN_LEFT, VALIGN_BOTTOM);
    papTest_[0]->locate(-PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2) , -PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2),0);

    papTest_[1]->setAlign(ALIGN_CENTER, VALIGN_BOTTOM);
    papTest_[1]->locate(0                                         , -PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2),0);

    papTest_[2]->setAlign(ALIGN_RIGHT, VALIGN_BOTTOM);
    papTest_[2]->locate( PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2) , -PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2),0);


    papTest_[3]->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    papTest_[3]->locate(-PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2) , 0,0);

    papTest_[4]->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    papTest_[4]->locate(0                                         , 0,0);

    papTest_[5]->setAlign(ALIGN_RIGHT, VALIGN_MIDDLE);
    papTest_[5]->locate( PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2) , 0,0);

    papTest_[6]->setAlign(ALIGN_LEFT, VALIGN_TOP);
    papTest_[6]->locate(-PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2) , PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2),0);

    papTest_[7]->setAlign(ALIGN_CENTER, VALIGN_TOP);
    papTest_[7]->locate( 0                                        , PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2),0);

    papTest_[8]->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    papTest_[8]->locate( PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2) , PX_C(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2),0);



}

void SmpWorld::processBehavior() {
    //キャラをボタン入力で移動
    vb_.update(); //入力状況更新
    if (vb_.isBeingPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Z += PX_C(2); //奥
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb_.isBeingPressed(VB_RIGHT)) {
            pActor_->_X += PX_C(2); //右
        }
        if (vb_.isBeingPressed(VB_LEFT)) {
            pActor_->_X -= PX_C(2); //左
        }
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Y += PX_C(2); //上
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Y -= PX_C(2); //下
        }
    }
}

SmpWorld::~SmpWorld() {
}
