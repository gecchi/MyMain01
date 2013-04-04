#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

IDirectSound8* GgafDxSound::_pIDirectSound8 = nullptr;

GgafDxBgmManager* GgafDxSound::_pBgmManager = nullptr;
GgafDxSeManager* GgafDxSound::_pSeManager = nullptr;
int GgafDxSound::aDbVolume[101];

DSCAPS GgafDxSound::_dsCaps;
int GgafDxSound::_app_master_volume = 100;
int GgafDxSound::_bgm_master_volume = 100;
int GgafDxSound::_se_master_volume = 100;
float GgafDxSound::_app_master_volume_rate = 1.0;
float GgafDxSound::_bgm_master_volume_rate = 1.0;
float GgafDxSound::_se_master_volume_rate = 1.0;


void GgafDxSound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(nullptr, &_pIDirectSound8, nullptr);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSound::init() GgafDxSoundが初期化できません。サウンドカードデバイスに問題ないか確認してください。");
    }
    hr = _pIDirectSound8->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSound::init() SetCooperativeLevel失敗。");
    }
    _dsCaps.dwSize = sizeof(_dsCaps);
    hr = GgafDxSound::_pIDirectSound8->GetCaps(&_dsCaps);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSound::init() GetCaps失敗。");
    }
    _pBgmManager = NEW GgafDxBgmManager("OggBgmManager");
    _pSeManager = NEW GgafDxSeManager("SoundEffectManager");

    //メモ：ボリューム値(0~100)、減衰デシベル(DSBVOLUME_MIN~DSBVOLUME_MAX)変換配列
    //DirectSounnd の SetVolume の引数の値(単位：1/100dB) ＝ 33.22f * 100.0 * log10(volume)   但し0.0 < volume <= 1.0
    //<音量とデシベルの関係>
    //    100%    0db
    //    90% -1.52db
    //    80% -3.22db
    //    70% -5.15db
    //    60% -7.37db
    //    50% -10.00db
    //    40% -13.22db
    //    30% -17.37db
    //    20% -23.22db
    //    10% -33.22db
    aDbVolume[GGAF_MIN_VOLUME] = DSBVOLUME_MIN;
    for (int i = 1; i <= GGAF_MAX_VOLUME-1; i++) {
        aDbVolume[i] = (int)(33.22f * 100.0 * log10(1.0*i / GGAF_MAX_VOLUME));
    }
    aDbVolume[GGAF_MAX_VOLUME] = DSBVOLUME_MAX;

    GgafDxSound::setBgmMasterVolume(PROPERTY::BGM_VOLUME);
    GgafDxSound::setSeMasterVolume(PROPERTY::SE_VOLUME);
    GgafDxSound::setAppMasterVolume(PROPERTY::MASTER_VOLUME);
}

void GgafDxSound::setAppMasterVolume(int prm_app_master_volume) {
    _app_master_volume = prm_app_master_volume;
    if (_app_master_volume > GGAF_MAX_VOLUME) {
        _app_master_volume = GGAF_MAX_VOLUME;
    } else if (_app_master_volume < GGAF_MIN_VOLUME) {
        _app_master_volume = GGAF_MIN_VOLUME;
    }
    _app_master_volume_rate = 1.0f * _app_master_volume / GGAF_MAX_VOLUME;
    GgafDxSound::_pBgmManager->updateVolume(); //音量を更新
    GgafDxSound::_pSeManager->updateVolume(); //音量を更新
}

void GgafDxSound::addAppMasterVolume(int prm_app_master_volume_offset) {
    setAppMasterVolume(_app_master_volume+prm_app_master_volume_offset);
}

void GgafDxSound::setBgmMasterVolume(float prm_bgm_master_volume) {
    _bgm_master_volume = prm_bgm_master_volume;
    if (_bgm_master_volume > GGAF_MAX_VOLUME) {
        _bgm_master_volume = GGAF_MAX_VOLUME;
    } else if (_bgm_master_volume < GGAF_MIN_VOLUME) {
        _bgm_master_volume = GGAF_MIN_VOLUME;
    }
    _bgm_master_volume_rate = 1.0f * _bgm_master_volume / GGAF_MAX_VOLUME;
    GgafDxSound::_pBgmManager->updateVolume(); //音量を更新
}

void GgafDxSound::addBgmMasterVolume(int prm_bgm_master_volume_offset) {
    setBgmMasterVolume(_bgm_master_volume+prm_bgm_master_volume_offset);
}

void GgafDxSound::setSeMasterVolume(float prm_se_master_volume) {
    _se_master_volume = prm_se_master_volume;
    if (_se_master_volume > GGAF_MAX_VOLUME) {
        _se_master_volume = GGAF_MAX_VOLUME;
    } else if (_se_master_volume < GGAF_MIN_VOLUME) {
        _se_master_volume = GGAF_MIN_VOLUME;
    }
    _se_master_volume_rate = 1.0f * _se_master_volume / GGAF_MAX_VOLUME;
    GgafDxSound::_pSeManager->updateVolume(); //音量を更新
}

void GgafDxSound::addSeMasterVolume(int prm_se_master_volume_offset) {
    setSeMasterVolume(_se_master_volume+prm_se_master_volume_offset);
}

void GgafDxSound::release() {
    _TRACE_("GgafDxSound::release() begin");
    _TRACE_("GGAF_DELETE(_pBgmManager);");
    GGAF_DELETE(_pBgmManager);
    _TRACE_("GGAF_DELETE(_pSeManager);");
    GGAF_DELETE(_pSeManager);
    _TRACE_("GGAF_RELEASE(_pIDirectSound8);");
    GGAF_RELEASE(_pIDirectSound8);
    _TRACE_("GgafDxSound::release() end");
}
