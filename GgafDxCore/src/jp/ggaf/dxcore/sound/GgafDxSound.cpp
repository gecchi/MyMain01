#include "jp/ggaf/dxcore/sound/GgafDxSound.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"

using namespace GgafCore;
using namespace GgafDxCore;

IDirectSound8* GgafDxSound::_pIDirectSound8 = nullptr;

GgafDxBgmManager* GgafDxSound::_pBgmManager = nullptr;
GgafDxSeManager* GgafDxSound::_pSeManager = nullptr;
double GgafDxSound::_a_db_volume[GGAF_MAX_VOLUME+1];

DSCAPS GgafDxSound::_dsCaps;
int GgafDxSound::_app_master_volume = 1000;
int GgafDxSound::_bgm_master_volume = 1000;
int GgafDxSound::_se_master_volume = 1000;
float GgafDxSound::_app_master_volume_rate = 1.0;
float GgafDxSound::_bgm_master_volume_rate = 1.0;
float GgafDxSound::_se_master_volume_rate = 1.0;


void GgafDxSound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(nullptr, &GgafDxSound::_pIDirectSound8, nullptr);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSoundが初期化できません。サウンドカードデバイスに問題ないか確認してください。");
    }
    hr = GgafDxSound::_pIDirectSound8->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throwGgafCriticalException("SetCooperativeLevel失敗。");
    }
    GgafDxSound::_dsCaps.dwSize = sizeof(GgafDxSound::_dsCaps);
    hr = GgafDxSound::_pIDirectSound8->GetCaps(&GgafDxSound::_dsCaps);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GetCaps失敗。");
    }
    GgafDxSound::_pBgmManager = NEW GgafDxBgmManager("OggBgmManager");
    GgafDxSound::_pSeManager = NEW GgafDxSeManager("SoundEffectManager");

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
    GgafDxSound::_a_db_volume[GGAF_MIN_VOLUME] = DSBVOLUME_MIN;
    for (int i = 1; i <= GGAF_MAX_VOLUME-1; i++) {
        GgafDxSound::_a_db_volume[i] = (33.22f * 100.0 * log10(1.0*i / GGAF_MAX_VOLUME));
    }
    GgafDxSound::_a_db_volume[GGAF_MAX_VOLUME] = DSBVOLUME_MAX;

    GgafDxSound::setBgmMasterVolume(PROPERTY::BGM_VOLUME);
    GgafDxSound::setSeMasterVolume(PROPERTY::SE_VOLUME);
    GgafDxSound::setAppMasterVolume(PROPERTY::MASTER_VOLUME);
}

void GgafDxSound::setAppMasterVolume(int prm_app_master_volume) {
    GgafDxSound::_app_master_volume = prm_app_master_volume;
    if (GgafDxSound::_app_master_volume > GGAF_MAX_VOLUME) {
        GgafDxSound::_app_master_volume = GGAF_MAX_VOLUME;
    } else if (GgafDxSound::_app_master_volume < GGAF_MIN_VOLUME) {
        GgafDxSound::_app_master_volume = GGAF_MIN_VOLUME;
    }
    GgafDxSound::_app_master_volume_rate = 1.0f * GgafDxSound::_app_master_volume / GGAF_MAX_VOLUME;
    GgafDxSound::_pBgmManager->updateVolume(); //音量を更新
    GgafDxSound::_pSeManager->updateVolume(); //音量を更新
}

void GgafDxSound::addAppMasterVolume(int prm_app_master_volume_offset) {
    GgafDxSound::setAppMasterVolume(GgafDxSound::_app_master_volume+prm_app_master_volume_offset);
}

void GgafDxSound::setBgmMasterVolume(float prm_bgm_master_volume) {
    GgafDxSound::_bgm_master_volume = prm_bgm_master_volume;
    if (GgafDxSound::_bgm_master_volume > GGAF_MAX_VOLUME) {
        GgafDxSound::_bgm_master_volume = GGAF_MAX_VOLUME;
    } else if (GgafDxSound::_bgm_master_volume < GGAF_MIN_VOLUME) {
        GgafDxSound::_bgm_master_volume = GGAF_MIN_VOLUME;
    }
    GgafDxSound::_bgm_master_volume_rate = 1.0f * GgafDxSound::_bgm_master_volume / GGAF_MAX_VOLUME;
    GgafDxSound::_pBgmManager->updateVolume(); //音量を更新
}

void GgafDxSound::addBgmMasterVolume(int prm_bgm_master_volume_offset) {
    GgafDxSound::setBgmMasterVolume(GgafDxSound::_bgm_master_volume+prm_bgm_master_volume_offset);
}

void GgafDxSound::setSeMasterVolume(float prm_se_master_volume) {
    GgafDxSound::_se_master_volume = prm_se_master_volume;
    if (GgafDxSound::_se_master_volume > GGAF_MAX_VOLUME) {
        GgafDxSound::_se_master_volume = GGAF_MAX_VOLUME;
    } else if (GgafDxSound::_se_master_volume < GGAF_MIN_VOLUME) {
        GgafDxSound::_se_master_volume = GGAF_MIN_VOLUME;
    }
    GgafDxSound::_se_master_volume_rate = 1.0f * GgafDxSound::_se_master_volume / GGAF_MAX_VOLUME;
    GgafDxSound::_pSeManager->updateVolume(); //音量を更新
}

void GgafDxSound::addSeMasterVolume(int prm_se_master_volume_offset) {
    setSeMasterVolume(GgafDxSound::_se_master_volume+prm_se_master_volume_offset);
}

void GgafDxSound::release() {
    _TRACE_(FUNC_NAME<<" begin");
    _TRACE_("GGAF_DELETE(GgafDxSound::_pBgmManager);");
    GGAF_DELETE(GgafDxSound::_pBgmManager);
    _TRACE_("GGAF_DELETE(GgafDxSound::_pSeManager);");
    GGAF_DELETE(GgafDxSound::_pSeManager);
    _TRACE_("GGAF_RELEASE(GgafDxSound::_pIDirectSound8);");
    GGAF_RELEASE(GgafDxSound::_pIDirectSound8);
    _TRACE_(FUNC_NAME<<" end");
}
