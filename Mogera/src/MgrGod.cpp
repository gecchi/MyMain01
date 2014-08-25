#include "MgrGod.h"

#include "actor/MgrCamera.h"
#include "scene/MgrUniverse.h"

using namespace Mogera;

MgrGod::MgrGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* MgrGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    MgrCamera* pCam = NEW MgrCamera("MOGERA_CAMERA");                  //�J�����쐬���A
    MgrUniverse* pUniverse = NEW MgrUniverse("MOGERA_UNIVERSE", pCam); //���̐��𐶐��B
    return pUniverse;
}

MgrGod::~MgrGod() {
}

