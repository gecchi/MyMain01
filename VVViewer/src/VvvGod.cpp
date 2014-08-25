#include "VvvGod.h"

#include "actor/VvvCamera.h"
#include "scene/VvvUniverse.h"

using namespace VVViewer;

bool VvvGod::is_wm_dropfiles_ = false;
char VvvGod::dropfiles_[2048];

VvvGod::VvvGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* VvvGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //�J�����쐬���A
    VvvUniverse* pUniverse = new VvvUniverse("SIMPLE_UNIVERSE", pCam); //���̐��𐶐��B
    return pUniverse;
}

VvvGod::~VvvGod() {
}

