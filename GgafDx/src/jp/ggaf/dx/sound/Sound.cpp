#include "jp/ggaf/dx/sound/Sound.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/manager/BgmManager.h"
#include "jp/ggaf/dx/manager/SeManager.h"
#include "jp/ggaf/dx/sound/Se.h"
#include "jp/ggaf/dx/sound/Bgm.h"

#ifdef __GNUG__
    #define __null
    #define NULL    0
    #define __in
    #define __out
#endif
#include <dsound.h>  //←sal.h を include する
#ifdef __GNUG__
    #undef __null
    #undef __in
    #undef __out
#endif


using namespace GgafDx;

IDirectSound8* Sound::_pIDirectSound8 = nullptr;

BgmManager* Sound::_pBgmManager = nullptr;
SeManager* Sound::_pSeManager = nullptr;
double Sound::_a_db_volume[GGAF_MAX_VOLUME+1];

DSCAPS* Sound::_pDsCaps = nullptr;
int Sound::_app_master_volume = GGAF_MAX_VOLUME;
int Sound::_bgm_master_volume = GGAF_MAX_VOLUME;
int Sound::_se_master_volume = GGAF_MAX_VOLUME;


void Sound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(nullptr, &Sound::_pIDirectSound8, nullptr);
    if (hr != D3D_OK) {
        throwCriticalException("Soundが初期化できません。サウンドカードデバイスに問題ないか確認してください。");
    }
    hr = Sound::_pIDirectSound8->SetCooperativeLevel(pCARETAKER->_pHWndPrimary, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throwCriticalException("SetCooperativeLevel失敗。");
    }
    Sound::_pDsCaps = NEW DSCAPS;
    Sound::_pDsCaps->dwSize = sizeof(DSCAPS);
    hr = Sound::_pIDirectSound8->GetCaps(Sound::_pDsCaps);
    if (hr != D3D_OK) {
        throwCriticalException("GetCaps失敗。");
    }
    Sound::_pBgmManager = NEW BgmManager("OggBgmManager");
    Sound::_pSeManager = NEW SeManager("SoundEffectManager");

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
    Sound::_a_db_volume[GGAF_MIN_VOLUME] = DSBVOLUME_MIN;
    for (int i = 1; i <= GGAF_MAX_VOLUME-1; i++) {
        Sound::_a_db_volume[i] = (33.22f * 100.0 * log10(1.0*i / GGAF_MAX_VOLUME));
    }
    Sound::_a_db_volume[GGAF_MAX_VOLUME] = DSBVOLUME_MAX;

    Sound::setBgmMasterVolume(CONFIG::BGM_VOLUME);
    Sound::setSeMasterVolume(CONFIG::SE_VOLUME);
    Sound::setAppMasterVolume(CONFIG::MASTER_VOLUME);
}


void Sound::release() {
    _TRACE_(FUNC_NAME<<" begin");
    GGAF_DELETE(Sound::_pDsCaps);
    _TRACE_("GGAF_DELETE(Sound::_pBgmManager);");
    GGAF_DELETE(Sound::_pBgmManager);
    _TRACE_("GGAF_DELETE(Sound::_pSeManager);");
    GGAF_DELETE(Sound::_pSeManager);
    _TRACE_("GGAF_RELEASE(Sound::_pIDirectSound8);");
    GGAF_RELEASE(Sound::_pIDirectSound8);
    _TRACE_(FUNC_NAME<<" end");
}

void Sound::setAppMasterVolume(int prm_app_master_volume)  {
    _app_master_volume = prm_app_master_volume;
    if (_app_master_volume > GGAF_MAX_VOLUME) {
        _app_master_volume = GGAF_MAX_VOLUME;
    } else if (_app_master_volume < GGAF_MIN_VOLUME) {
        _app_master_volume = GGAF_MIN_VOLUME;
    }
    double bgm_master_volume_rate =
            1.0 * (_app_master_volume * _bgm_master_volume) / _MAXMAX_VOLUME;
    Sound::_pBgmManager->setBgmMasterVolumeRate(bgm_master_volume_rate); //マスターBGM音量率を更新

    double se_master_volume_rate  =
            1.0 * (_app_master_volume * _se_master_volume ) / _MAXMAX_VOLUME;
    Sound::_pSeManager->setSeMasterVolumeRate(se_master_volume_rate);   //マスターSE音量率を更新
}

void Sound::setBgmMasterVolume(float prm_bgm_master_volume) {
    _bgm_master_volume = prm_bgm_master_volume;
    if (_bgm_master_volume > GGAF_MAX_VOLUME) {
        _bgm_master_volume = GGAF_MAX_VOLUME;
    } else if (_bgm_master_volume < GGAF_MIN_VOLUME) {
        _bgm_master_volume = GGAF_MIN_VOLUME;
    }
    double bgm_master_volume_rate =
            1.0 * (_app_master_volume * _bgm_master_volume) / _MAXMAX_VOLUME;
    Sound::_pBgmManager->setBgmMasterVolumeRate(bgm_master_volume_rate); //マスターBGM音量率を更新
}

void Sound::setSeMasterVolume(float prm_se_master_volume)  {
    _se_master_volume = prm_se_master_volume;
    if (_se_master_volume > GGAF_MAX_VOLUME) {
        _se_master_volume = GGAF_MAX_VOLUME;
    } else if (_se_master_volume < GGAF_MIN_VOLUME) {
        _se_master_volume = GGAF_MIN_VOLUME;
    }
    double se_master_volume_rate  =
            1.0 * (_app_master_volume * _se_master_volume ) / _MAXMAX_VOLUME;
    Sound::_pSeManager->setSeMasterVolumeRate(se_master_volume_rate);   //マスターSE音量率を更新
}
