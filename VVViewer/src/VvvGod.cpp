#include "stdafx.h"
#include "VvvGod.h"

using namespace VVViewer;

bool VvvGod::is_wm_dropfiles_ = false;
char VvvGod::dropfiles_[2048];

VvvGod::VvvGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2) :
        GgafLib::DefaultGod(prm_hInstance, prm_hWnd1, prm_hWnd2) {
}

GgafCore::GgafUniverse* VvvGod::createUniverse() {
    //この世の作成のサンプル
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //カメラ作成し、
    VvvUniverse* pUniverse = new VvvUniverse("SIMPLE_UNIVERSE", pCam); //この世を生成。
    return pUniverse;
}

VvvGod::~VvvGod() {
}

