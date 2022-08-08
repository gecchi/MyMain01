#include "SmpCaretaker.h"

#include "actor/SmpCamera.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpCaretaker::SmpCaretaker() : GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* SmpCaretaker::createSpacetime() {
    //�u���̐��v�̍쐬�������I�[�o�[���C�h���A�������Ă��������B
    SmpCamera* pCam = new SmpCamera("SMP_CAM"); //�J�����쐬���A
    SmpSpacetime* pSpacetime = new SmpSpacetime("SMP_SPACETIME", pCam); //�J�����������Ɂu���̐��v�𐶐����A
    return pSpacetime; //���������u���̐��v��Ԓl�Ƃ��܂��B
}

SmpCaretaker::~SmpCaretaker() {
}

