#include "stdafx.h"

DefaultGod::DefaultGod(HINSTANCE prm_hInstance, HWND _hWnd) : GgafDx9God(prm_hInstance, _hWnd) {
	VirtualButton::init();
	CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 ‚Í Seed
}

DefaultGod::~DefaultGod() {
	CmRandomNumberGenerator::getInstance()->release();
	VirtualButton::clear();
	DelineateActor::release();
}
