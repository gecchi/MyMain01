#include "stdafx.h"
using namespace VVViewer;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    getDirector()->addSubGroup(NEW VvvCamWorker("VvvCamWorker"));

    pActor_ = new VvvActor("TEST");      //�L�����쐬���ێ�
    getDirector()->addSubGroup(pActor_); //�L�������V�[���ē̔z���ɏ����i�\�������j

    vb_ = NEW GgafLib::VirtualButton();
    GgafLib::VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //�{�^���P=�X�y�[�X�L�[ �Ƃ���B

}
void VvvWorld::initialize() {
}

void VvvWorld::processBehavior() {
    vb_->update(); //���͏󋵍X�V
    if (VvvGod::is_wm_dropfiles_) {
        VvvGod::is_wm_dropfiles_ = false;
//        getDirector()->addSubGroup(createInFactory(GgafLib::DefaultMeshActor, VvvGod::is_wm_dropfiles_));
    }
}

VvvWorld::~VvvWorld() {
}
