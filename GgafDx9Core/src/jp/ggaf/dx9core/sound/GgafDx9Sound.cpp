#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

IDirectSound8* GgafDx9Sound::_pIDirectSound8 = NULL;

GgafDx9BgmManager* GgafDx9Sound::_pBgmManager = NULL;
GgafDx9SeManager* GgafDx9Sound::_pSeManager = NULL;
DSCAPS GgafDx9Sound::_dsCaps;
//CC3DSound* GgafDx9Sound::_pC3DSound = NULL;

void GgafDx9Sound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(NULL, &_pIDirectSound8, NULL);
    if (hr != D3D_OK) {
        return;

        //throw_GgafCriticalException("GgafDx9Sound::init() GgafDx9Sound���������ł��܂���B�T�E���h�J�[�h�f�o�C�X�ɖ��Ȃ����m�F���Ă��������B");
    }
    hr = _pIDirectSound8->SetCooperativeLevel(GgafDx9God::_hWnd, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throw_GgafCriticalException("GgafDx9Sound::init() SetCooperativeLevel���s�B");
    }

    _dsCaps.dwSize = sizeof(_dsCaps);
    hr = GgafDx9Sound::_pIDirectSound8->GetCaps(&_dsCaps);
    if (hr != D3D_OK) {
        throw_GgafCriticalException("GgafDx9Sound::init() GetCaps���s�B");
    }

    _pBgmManager = NEW GgafDx9BgmManager("OggBgmManager");
    _pSeManager = NEW GgafDx9SeManager("SoundEffectManager");

    //	if (_pC3DSound == NULL) {
            //		_pC3DSound = NEW CC3DSound();
            //	}
            //
            //	if (!_pC3DSound->CreateSound(GgafDx9God::_hWnd)) {
            //		throw_GgafCriticalException("GgafDx9Sound::init() GgafDx9Sound���������ł��܂���B�T�E���h�J�[�h�f�o�C�X�ɖ��Ȃ����m�F���Ă��������B");
            //	}
        }

void GgafDx9Sound::release() {
    //	GgafDx9SeManager::clear();
    //	GgafDx9BgmManager::clear();
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSound8);
    DELETE_IMPOSSIBLE_NULL(_pBgmManager);
    DELETE_IMPOSSIBLE_NULL(_pSeManager);

    //	_pC3DSound->Release();
    //	delete _pC3DSound;
    //	_pC3DSound = NULL;
}
//
//GgafDx9Se* GgafDx9Sound::createSe(string prm_wave_name) {
//	if (_pIDirectSound8 == NULL) {
//		throw_GgafCriticalException("[GgafDx9Sound::createSe] Error! GgafDx9Sound�͏��������Ă܂���Binit()�����s���Ă��������B");
//	}
//	GgafDx9Se* pSe_New = NEW GgafDx9Se(prm_wave_name, 1); //1�͍ő哯��������
//	return pSe_New;
//}
//
//GgafDx9Bgm* GgafDx9Sound::createBgm(string prm_ogg_name) {
//	if (_pIDirectSound8 == NULL) {
//		throw_GgafCriticalException("[GgafDx9Sound::createBgm] Error! GgafDx9Sound�͏��������Ă܂���Binit()�����s���Ă��������B");
//	}
//	GgafDx9Bgm* pBgm_New = NEW GgafDx9Bgm(prm_ogg_name);
//	return pBgm_New;
//}
