#include "stdafx.h"

IDirectSound8* GgafDx9Sound::_pIDirectSound8 = NULL;
DSCAPS GgafDx9Sound::_dsCaps;
//CC3DSound* GgafDx9Sound::_pC3DSound = NULL;

void GgafDx9Sound::init() {
	HRESULT hr;
	hr = DirectSoundCreate8(NULL, &_pIDirectSound8, NULL);
	if (hr != D3D_OK) {
		throw_GgafCriticalException("GgafDx9Sound::init() GgafDx9Soundが初期化できません。サウンドカードデバイスに問題ないか確認してください。");
	}
	hr = _pIDirectSound8->SetCooperativeLevel(GgafDx9God::_hWnd, DSSCL_PRIORITY );
	if (hr != D3D_OK) {
		throw_GgafCriticalException("GgafDx9Sound::init() SetCooperativeLevel失敗。");
	}

	_dsCaps.dwSize = sizeof(_dsCaps);
	hr = GgafDx9Sound::_pIDirectSound8->GetCaps(&_dsCaps);
	if (hr != D3D_OK) {
		throw_GgafCriticalException("GgafDx9Sound::init() GetCaps失敗。");
	}

//	if (_pC3DSound == NULL) {
//		_pC3DSound = NEW CC3DSound();
//	}
//
//	if (!_pC3DSound->CreateSound(GgafDx9God::_hWnd)) {
//		throw_GgafCriticalException("GgafDx9Sound::init() GgafDx9Soundが初期化できません。サウンドカードデバイスに問題ないか確認してください。");
//	}
}

void GgafDx9Sound::release() {
	GgafDx9SeManager::clear();
	GgafDx9BgmManager::clear();
	RELEASE_IMPOSSIBLE_NULL(_pIDirectSound8);
//	_pC3DSound -> Release();
//	delete _pC3DSound;
//	_pC3DSound = NULL;
}

GgafDx9Se* GgafDx9Sound::createSe(string prm_wave_name) {
	if (_pIDirectSound8 == NULL) {
		throw_GgafCriticalException("[GgafDx9Sound::createSe] Error! GgafDx9Soundは初期化してません。init()を実行してください。");
	}
	GgafDx9Se* pSe_New = NEW GgafDx9Se(prm_wave_name, 1); //1は最大同時再生数
	return pSe_New;
}

GgafDx9Bgm* GgafDx9Sound::createBgm(string prm_ogg_name) {
	if (_pIDirectSound8 == NULL) {
		throw_GgafCriticalException("[GgafDx9Sound::createBgm] Error! GgafDx9Soundは初期化してません。init()を実行してください。");
	}
	GgafDx9Bgm* pBgm_New = NEW GgafDx9Bgm(prm_ogg_name);
	return pBgm_New;
}
