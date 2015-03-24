#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpGod::SmpGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafSpacetime* SmpGod::createSpacetime() {
    //���̐��̍쐬�̃T���v��
    SmpCamera* pCam = new SmpCamera("SMP_CAM");                 //�J�����쐬���A
    SmpSpacetime* pSpacetime = new SmpSpacetime("SMP_UNIV", pCam); //�J�����������ɂ��̐��𐶐��B
    return pSpacetime;
}

SmpGod::~SmpGod() {
}

