#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _pActor = new TestActor("TEST");     //�L�����쐬���ێ�
    getDirector()->addSubGroup(_pActor); //�L�������V�[���ē̔z���ɏ����i�\�������j
    VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //�{�^���P=�X�y�[�X�L�[ �Ƃ���B
}

void World::processBehavior() {
    //�L�������{�^�����͂ňړ�
    _vb.update(); //���͏󋵍X�V
    if (_vb.isBeingPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (_vb.isBeingPressed(VB_UP)) {
            _pActor->_Z += PX2CO(2); //��
        }
        if (_vb.isBeingPressed(VB_DOWN)) {
            _pActor->_Z -= PX2CO(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (_vb.isBeingPressed(VB_RIGHT)) {
            _pActor->_X += PX2CO(2); //�E
        }
        if (_vb.isBeingPressed(VB_LEFT)) {
            _pActor->_X -= PX2CO(2); //��
        }
        if (_vb.isBeingPressed(VB_UP)) {
            _pActor->_Y += PX2CO(2); //��iY���͏オ���j
        }
        if (_vb.isBeingPressed(VB_DOWN)) {
            _pActor->_Y -= PX2CO(2); //��
        }
    }
}

World::~World() {
}
