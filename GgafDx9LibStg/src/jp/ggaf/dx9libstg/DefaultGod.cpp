#include "stdafx.h"

DefaultGod::DefaultGod(HINSTANCE prm_hInstance, HWND _hWnd) : GgafDx9God(prm_hInstance, _hWnd) {
	VirtualButton::init();
}

DefaultGod::~DefaultGod() {

	VirtualButton::clear();
	DelineateActor::release();
}
