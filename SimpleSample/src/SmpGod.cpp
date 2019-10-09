#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpGod::SmpGod() : GgafLib::DefaultGod() {
}

GgafCore::Spacetime* SmpGod::createSpacetime() {
    //�u���̐��v�̍쐬�������I�[�o�[���C�h���A�������Ă��������B
    SmpCamera* pCam = new SmpCamera("SMP_CAM"); //�J�����쐬���A
    SmpSpacetime* pSpacetime = new SmpSpacetime("SMP_SPACETIME", pCam); //�J�����������Ɂu���̐��v�𐶐����A
    return pSpacetime; //���������u���̐��v��Ԓl�Ƃ��܂��B
}

SmpGod::~SmpGod() {
}

