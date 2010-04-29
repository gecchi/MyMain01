#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

IDirectSound8* GgafDx9Sound::_pIDirectSound8 = NULL;

GgafDx9BgmManager* GgafDx9Sound::_pBgmManager = NULL;
GgafDx9SeManager* GgafDx9Sound::_pSeManager = NULL;


DSCAPS GgafDx9Sound::_dsCaps;

float GgafDx9Sound::_master_volume_rate = 1.0;
float GgafDx9Sound::_bgm_volume_rate = 1.0;
float GgafDx9Sound::_se_volume_rate = 1.0;


void GgafDx9Sound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(NULL, &_pIDirectSound8, NULL);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDx9Sound::init() GgafDx9Soundが初期化できません。サウンドカードデバイスに問題ないか確認してください。");
    }
    hr = _pIDirectSound8->SetCooperativeLevel(GgafDx9God::_hWnd, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDx9Sound::init() SetCooperativeLevel失敗。");
    }
    _dsCaps.dwSize = sizeof(_dsCaps);
    hr = GgafDx9Sound::_pIDirectSound8->GetCaps(&_dsCaps);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDx9Sound::init() GetCaps失敗。");
    }
    _pBgmManager = NEW GgafDx9BgmManager("OggBgmManager");
    _pSeManager = NEW GgafDx9SeManager("SoundEffectManager");

    GgafDx9Sound::setBgmVolume(GGAFDX9_PROPERTY(BGM_VOLUME)/100.0);
    GgafDx9Sound::setSeVolume(GGAFDX9_PROPERTY(SE_VOLUME)/100.0);
    GgafDx9Sound::setMasterVolume(GGAFDX9_PROPERTY(MASTER_VOLUME)/100.0);
}

void GgafDx9Sound::release() {
    DELETE_IMPOSSIBLE_NULL(_pBgmManager);
    DELETE_IMPOSSIBLE_NULL(_pSeManager);
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSound8);
}
