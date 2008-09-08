#include "stdafx.h"

God::God(HINSTANCE prm_hInstance, HWND _hWnd) : DefaultGod(prm_hInstance, _hWnd) {
}

GgafWorld* God::createWorld() {
	World* sceneWorld = NEW World("MYWORLD");
	return (GgafWorld*)sceneWorld;
}

God::~God() {
	_pWorld->dump();
}
