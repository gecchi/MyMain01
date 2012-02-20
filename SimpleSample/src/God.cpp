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
    //‚±‚Ì¢‚Ìì¬—á
    Camera* pCamera = new Camera("SIMPLE_CAMERA");                  //ƒJƒƒ‰ì¬‚µA
    Universe* pUniverse = new Universe("SIMPLE_UNIVERSE", pCamera); //‚±‚Ì¢‚ğ¶¬B
    return (GgafUniverse*)pUniverse;
}

God::~God() {
}

