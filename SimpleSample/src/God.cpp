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
    //���̐��̍쐬�̃T���v��
    Camera* pCam = new Camera("SIMPLE_CAMERA");                  //�J�����쐬���A
    Universe* pUniverse = new Universe("SIMPLE_UNIVERSE", pCam); //���̐��𐶐��B
    return (GgafUniverse*)pUniverse;
}

God::~God() {
}

