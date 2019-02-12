#include "HgrGod.h"

#include "actor/camera/HgrCamera.h"
#include "scene/HgrSpacetime.h"

using namespace Hogera;

HgrGod::HgrGod() :
        GgafLib::DefaultGod() {
}

GgafCore::Spacetime* HgrGod::createSpacetime() {
    //���̐��̍쐬�̃T���v��
    HgrCamera* pCam = NEW HgrCamera("HOGERA_HGRCAMERA");                  //�J�����쐬���A
    HgrSpacetime* pSpacetime = NEW HgrSpacetime("HOGERA_SPACETIME", pCam); //���̐��𐶐��B
    return pSpacetime;
}

HgrGod::~HgrGod() {
}

