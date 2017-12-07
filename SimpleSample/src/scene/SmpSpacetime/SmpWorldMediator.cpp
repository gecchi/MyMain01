#include "SmpWorldMediator.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "actor/SmpActor.h"
#include "SmpWorld.h"

using namespace SimpleSample;

SmpWorldMediator::SmpWorldMediator(GgafLib::DefaultScene* prm_pScene) :
        DefaultSceneMediator(prm_pScene) {
    pActor_ = new SmpActor("TEST");  //�L�����N�^�[�쐬���ێ�
    addSubGroup(pActor_);  //�L�����N�^�[���V�[������҂̔z���ɏ����i�\�������j
}
void SmpWorldMediator::initialize() {
}

void SmpWorldMediator::processBehavior() {
    //�L�������{�^�����͂ňړ�
    GgafLib::VirtualButton* vb = ((SmpWorld*)getPlatformScene())->getVB();
    if (vb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (vb->isPressed(VB_UP)) {
            pActor_->_z += PX_C(2); //��
        }
        if (vb->isPressed(VB_DOWN)) {
            pActor_->_z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (vb->isPressed(VB_RIGHT)) {
            pActor_->_x += PX_C(2); //�E
        }
        if (vb->isPressed(VB_LEFT)) {
            pActor_->_x -= PX_C(2); //��
        }
        if (vb->isPressed(VB_UP)) {
            pActor_->_y += PX_C(2); //��
        }
        if (vb->isPressed(VB_DOWN)) {
            pActor_->_y -= PX_C(2); //��
        }
    }
}

SmpWorldMediator::~SmpWorldMediator() {
}
