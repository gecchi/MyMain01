#include "MgrGod.h"

#include "actor/camera/MgrCamera.h"
#include "scene/MgrSpacetime.h"

using namespace Mogera;

MgrGod::MgrGod() :
        GgafLib::DefaultGod() {
}

GgafCore::Spacetime* MgrGod::createSpacetime() {
    //���̐��̍쐬�̃T���v��
    MgrCamera* pCam = NEW MgrCamera("MOGERA_MGRCAMERA");                  //�J�����쐬���A
    MgrSpacetime* pSpacetime = NEW MgrSpacetime("MOGERA_SPACETIME", pCam); //���̐��𐶐��B
    return pSpacetime;
}

MgrGod::~MgrGod() {
}

