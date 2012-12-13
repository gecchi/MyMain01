#include "stdafx.h"
using namespace Mogera;

MgrGod::MgrGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2) :
        GgafLib::DefaultGod(prm_hInstance, prm_hWnd1, prm_hWnd2) {
}

GgafCore::GgafUniverse* MgrGod::createUniverse() {
    //この世の作成のサンプル
    MgrCamera* pCam = new MgrCamera("SIMPLE_CAMERA");                  //カメラ作成し、
    MgrUniverse* pUniverse = new MgrUniverse("SIMPLE_UNIVERSE", pCam); //この世を生成。
    return pUniverse;
}

MgrGod::~MgrGod() {
}

