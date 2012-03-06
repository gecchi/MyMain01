#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

God::God(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2) :
        DefaultGod(prm_hInstance, prm_hWnd1, prm_hWnd2) {
}

GgafUniverse* God::createUniverse() {
    //この世の作成のサンプル
    Camera* pCam = new Camera("SIMPLE_CAMERA");                  //カメラ作成し、
    Universe* pUniverse = new Universe("SIMPLE_UNIVERSE", pCam); //この世を生成。
    return (GgafUniverse*)pUniverse;
}

God::~God() {
}

