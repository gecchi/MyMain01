#include "stdafx.h"
#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpUniverse.h"

using namespace SimpleSample;

SmpGod::SmpGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2) :
        GgafLib::DefaultGod(prm_hInstance, prm_hWnd1, prm_hWnd2) {
}

GgafCore::GgafUniverse* SmpGod::createUniverse() {
    //���̐��̍쐬�̃T���v��
    SmpCamera* pCam = new SmpCamera("SIMPLE_CAMERA");                  //�J�����쐬���A
    SmpUniverse* pUniverse = new SmpUniverse("SIMPLE_UNIVERSE", pCam); //���̐��𐶐��B
    return pUniverse;
}

SmpGod::~SmpGod() {
}

