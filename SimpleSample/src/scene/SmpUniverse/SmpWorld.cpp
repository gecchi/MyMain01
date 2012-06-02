#include "stdafx.h"
using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");      //�L�����쐬���ێ�
    getDirector()->addSubGroup(pActor_); //�L�������V�[���ē̔z���ɏ����i�\�������j
    GgafLib::VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //�{�^���P=�X�y�[�X�L�[ �Ƃ���B
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
    //�L�������{�^�����͂ňړ�
    vb_.update(); //���͏󋵍X�V
    if (vb_.isBeingPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Z += PX_C(2); //��
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb_.isBeingPressed(VB_RIGHT)) {
            pActor_->_X += PX_C(2); //�E
        }
        if (vb_.isBeingPressed(VB_LEFT)) {
            pActor_->_X -= PX_C(2); //��
        }
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Y += PX_C(2); //��
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Y -= PX_C(2); //��
        }
    }
}

SmpWorld::~SmpWorld() {
}
