#include "VvGod.h"

#include "actor/camera/VvCamera.h"
#include "scene/VvSpacetime.h"

using namespace VioletVrain;

VvGod::VvGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafSpacetime* VvGod::createSpacetime() {
    //���̐��̍쐬�̃T���v��
    VvCamera* pCam = NEW VvCamera("VIOLETVRAIN_VVCAMERA");                  //�J�����쐬���A
    VvSpacetime* pSpacetime = NEW VvSpacetime("VIOLETVRAIN_SPACETIME", pCam); //���̐��𐶐��B
    return pSpacetime;
}

VvGod::~VvGod() {
}

