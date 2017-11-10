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
int GgafDxSound::_app_master_volume = GGAF_MAX_VOLUME;
int GgafDxSound::_bgm_master_volume = GGAF_MAX_VOLUME;
int GgafDxSound::_se_master_volume = GGAF_MAX_VOLUME;


void GgafDxSound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(nullptr, &GgafDxSound::_pIDirectSound8, nullptr);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSound���������ł��܂���B�T�E���h�J�[�h�f�o�C�X�ɖ��Ȃ����m�F���Ă��������B");
    }
    hr = GgafDxSound::_pIDirectSound8->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throwGgafCriticalException("SetCooperativeLevel���s�B");
    }
    GgafDxSound::_dsCaps.dwSize = sizeof(GgafDxSound::_dsCaps);
    hr = GgafDxSound::_pIDirectSound8->GetCaps(&GgafDxSound::_dsCaps);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GetCaps���s�B");
    }
    GgafDxSound::_pBgmManager = NEW GgafDxBgmManager("OggBgmManager");
    GgafDxSound::_pSeManager = NEW GgafDxSeManager("SoundEffectManager");

    //�����F�{�����[���l(0~100)�A�����f�V�x��(DSBVOLUME_MIN~DSBVOLUME_MAX)�ϊ��z��
    //DirectSounnd �� SetVolume �̈����̒l(�P�ʁF1/100dB) �� 33.22f * 100.0 * log10(volume)   �A��0.0 < volume <= 1.0
    //<���ʂƃf�V�x���̊֌W>
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

void GgafDxSound::setAppMasterVolume(int prm_app_master_volume)  {
    _app_master_volume = prm_app_master_volume;
    if (_app_master_volume > GGAF_MAX_VOLUME) {
        _app_master_volume = GGAF_MAX_VOLUME;
    } else if (_app_master_volume < GGAF_MIN_VOLUME) {
        _app_master_volume = GGAF_MIN_VOLUME;
    }
    double bgm_master_volume_rate =
            1.0 * (_app_master_volume * _bgm_master_volume) / _MAXMAX_VOLUME;
    GgafDxSound::_pBgmManager->setBgmMasterVolumeRate(bgm_master_volume_rate); //�}�X�^�[BGM���ʗ����X�V

    double se_master_volume_rate  =
            1.0 * (_app_master_volume * _se_master_volume ) / _MAXMAX_VOLUME;
    GgafDxSound::_pSeManager->setSeMasterVolumeRate(se_master_volume_rate);   //�}�X�^�[SE���ʗ����X�V
}

void GgafDxSound::setBgmMasterVolume(float prm_bgm_master_volume) {
    _bgm_master_volume = prm_bgm_master_volume;
    if (_bgm_master_volume > GGAF_MAX_VOLUME) {
        _bgm_master_volume = GGAF_MAX_VOLUME;
    } else if (_bgm_master_volume < GGAF_MIN_VOLUME) {
        _bgm_master_volume = GGAF_MIN_VOLUME;
    }
    double bgm_master_volume_rate =
            1.0 * (_app_master_volume * _bgm_master_volume) / _MAXMAX_VOLUME;
    GgafDxSound::_pBgmManager->setBgmMasterVolumeRate(bgm_master_volume_rate); //�}�X�^�[BGM���ʗ����X�V
}

void GgafDxSound::setSeMasterVolume(float prm_se_master_volume)  {
    _se_master_volume = prm_se_master_volume;
    if (_se_master_volume > GGAF_MAX_VOLUME) {
        _se_master_volume = GGAF_MAX_VOLUME;
    } else if (_se_master_volume < GGAF_MIN_VOLUME) {
        _se_master_volume = GGAF_MIN_VOLUME;
    }
    double se_master_volume_rate  =
            1.0 * (_app_master_volume * _se_master_volume ) / _MAXMAX_VOLUME;
    GgafDxSound::_pSeManager->setSeMasterVolumeRate(se_master_volume_rate);   //�}�X�^�[SE���ʗ����X�V
}
