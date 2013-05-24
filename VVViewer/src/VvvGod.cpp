#include "stdafx.h"
#include "VvvGod.h"

using namespace VVViewer;

bool VvvGod::is_wm_dropfiles_ = false;
char VvvGod::dropfiles_[2048];

VvvGod::VvvGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2) :
        GgafLib::DefaultGod(prm_hInstance, prm_hWnd1, prm_hWnd2) {
}

GgafCore::GgafUniverse* VvvGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //�J�����쐬���A
    VvvUniverse* pUniverse = new VvvUniverse("SIMPLE_UNIVERSE", pCam); //���̐��𐶐��B
    return pUniverse;
}

VvvGod::~VvvGod() {
}

