#include "SmpWorld.h"

#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) :
        GgafLib::DefaultScene(prm_name) {
    SmpActor* pActor = new SmpActor("TEST");  //�L�����N�^�[�쐬
    bringSceneMediator()->addSubGroup(pActor);  //�L�����N�^�[���V�[���ē̔z���ɏ����i�\�������j
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
}

SmpWorld::~SmpWorld() {
}
