#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpUniverse.h"

using namespace SimpleSample;

SmpGod::SmpGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* SmpGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    SmpCamera* pCam = new SmpCamera("SIMPLE_CAMERA");                  //�J�����쐬���A
    SmpUniverse* pUniverse = new SmpUniverse("SIMPLE_UNIVERSE", pCam); //�J�����������ɂ��̐��𐶐��B
    return pUniverse;
}

SmpGod::~SmpGod() {
}

