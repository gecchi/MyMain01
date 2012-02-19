#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

God::God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) :
      DefaultGod(prm_hInstance, prm_pHWndPrimary, prm_pHWndSecondary) {
}

GgafUniverse* God::createUniverse() {
    //この世の作成例
    Camera* pCamera = new Camera("SIMPLE_CAMERA");                  //カメラ作成し、
    Universe* pUniverse = new Universe("SIMPLE_UNIVERSE", pCamera); //この世を生成。
    return (GgafUniverse*)pUniverse;
}

God::~God() {
}
