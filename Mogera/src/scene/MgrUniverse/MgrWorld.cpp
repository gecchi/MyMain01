#include "stdafx.h"
#include "MgrWorld.h"

#include "actor/MgrActor.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "actor/TestActor.h"

using namespace Mogera;
using GgafCore::GgafSceneDirector;

MgrWorld::MgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new MgrActor("TEST");      //�L�����쐬���ێ�
    getSceneDirector()->addSubGroup(pActor_); //�L�������V�[���ē̔z���ɏ����i�\�������j

    getSceneDirector()->addSubGroup(new TestActor("haikei"));
    GgafLib::VirtualButton::_keyboardmap.BUTTON1 = DIK_SPACE; //�{�^���P=�X�y�[�X�L�[ �Ƃ���B
}

void MgrWorld::initialize() {
}

void MgrWorld::processBehavior() {
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

MgrWorld::~MgrWorld() {
}
