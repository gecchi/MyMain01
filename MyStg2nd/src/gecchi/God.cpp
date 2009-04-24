#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

God::God(HINSTANCE prm_hInstance, HWND _hWnd) : DefaultGod(prm_hInstance, _hWnd) {
}

GgafUniverse* God::createUniverse() {
    Universe* pUniverse = NEW Universe("MYUNIVERSE");
    return (GgafUniverse*)pUniverse;
}

God::~God() {
    _pUniverse->dump();
}
