#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpUniverse.h"

using namespace SimpleSample;

SmpGod::SmpGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* SmpGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    SmpCamera* pCam = new SmpCamera("SMP_CAM");                 //�J�����쐬���A
    SmpUniverse* pUniverse = new SmpUniverse("SMP_UNIV", pCam); //�J�����������ɂ��̐��𐶐��B
    return pUniverse;
}

SmpGod::~SmpGod() {
}

