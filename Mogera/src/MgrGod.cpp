#include "stdafx.h"
using namespace Mogera;

MgrGod::MgrGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2) :
        GgafLib::DefaultGod(prm_hInstance, prm_hWnd1, prm_hWnd2) {
}

GgafCore::GgafUniverse* MgrGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    MgrCamera* pCam = new MgrCamera("SIMPLE_CAMERA");                  //�J�����쐬���A
    MgrUniverse* pUniverse = new MgrUniverse("SIMPLE_UNIVERSE", pCam); //���̐��𐶐��B
    return pUniverse;
}

MgrGod::~MgrGod() {
}

