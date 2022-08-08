#include "VvvCaretaker.h"

#include "actor/VvvCamera.h"

using namespace VVViewer;

bool VvvCaretaker::is_wm_dropfiles_ = false;
char VvvCaretaker::dropfiles_[2048];

VvvCaretaker::VvvCaretaker() :
        GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* VvvCaretaker::createSpacetime() {
    //���̐��̍쐬�̃T���v��
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //�J�����쐬���A
    VvvSpacetime* pSpacetime = new VvvSpacetime("SIMPLE_SPACETIME", pCam); //���̐��𐶐��B
    return pSpacetime;
}

VvvCaretaker::~VvvCaretaker() {
}

