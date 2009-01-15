#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

God::God(HINSTANCE prm_hInstance, HWND _hWnd) : DefaultGod(prm_hInstance, _hWnd) {
}

GgafWorld* God::createWorld() {
	World* sceneWorld = NEW World("MYWORLD");
	return (GgafWorld*)sceneWorld;
}

God::~God() {
	_pWorld->dump();
}
