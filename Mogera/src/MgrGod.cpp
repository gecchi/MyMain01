#include "stdafx.h"
#include "MgrGod.h"

#include "actor/MgrCamera.h"
#include "scene/MgrUniverse.h"

using namespace Mogera;

MgrGod::MgrGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2) :
        GgafLib::DefaultGod(prm_hInstance, prm_hWnd1, prm_hWnd2) {
}

GgafCore::GgafUniverse* MgrGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    MgrCamera* pCam = new MgrCamera("MOGERA_CAMERA");                  //�J�����쐬���A
    MgrUniverse* pUniverse = new MgrUniverse("MOGERA_UNIVERSE", pCam); //���̐��𐶐��B
    return pUniverse;
}

MgrGod::~MgrGod() {
}

