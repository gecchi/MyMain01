#include "VvvGod.h"

#include "actor/VvvCamera.h"

using namespace VVViewer;

bool VvvGod::is_wm_dropfiles_ = false;
char VvvGod::dropfiles_[2048];

VvvGod::VvvGod() :
        GgafLib::DefaultGod() {
}

GgafCore::Spacetime* VvvGod::createSpacetime() {
    //���̐��̍쐬�̃T���v��
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //�J�����쐬���A
    VvvSpacetime* pSpacetime = new VvvSpacetime("SIMPLE_SPACETIME", pCam); //���̐��𐶐��B
    return pSpacetime;
}

VvvGod::~VvvGod() {
}

