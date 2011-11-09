#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

IDirectSound8* GgafDxSound::_pIDirectSound8 = NULL;

GgafDxBgmManager* GgafDxSound::_pBgmManager = NULL;
GgafDxSeManager* GgafDxSound::_pSeManager = NULL;
LONG GgafDxSound::aDbVolume[101];

DSCAPS GgafDxSound::_dsCaps;

float GgafDxSound::_master_volume_rate = 1.0;
float GgafDxSound::_bgm_volume_rate = 1.0;
float GgafDxSound::_se_volume_rate = 1.0;


void GgafDxSound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(NULL, &_pIDirectSound8, NULL);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSound::init() GgafDxSound���������ł��܂���B�T�E���h�J�[�h�f�o�C�X�ɖ��Ȃ����m�F���Ă��������B");
    }
    hr = _pIDirectSound8->SetCooperativeLevel(GgafDxGod::_pHWndPrimary, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSound::init() SetCooperativeLevel���s�B");
    }
    _dsCaps.dwSize = sizeof(_dsCaps);
    hr = GgafDxSound::_pIDirectSound8->GetCaps(&_dsCaps);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDxSound::init() GetCaps���s�B");
    }
    _pBgmManager = NEW GgafDxBgmManager("OggBgmManager");
    _pSeManager = NEW GgafDxSeManager("SoundEffectManager");

    GgafDxSound::setBgmVolume(1.0*CFG_PROPERTY(BGM_VOLUME)/GGAF_MAX_VOLUME);
    GgafDxSound::setSeVolume(1.0*CFG_PROPERTY(SE_VOLUME)/GGAF_MAX_VOLUME);
    GgafDxSound::setMasterVolume(1.0*CFG_PROPERTY(MASTER_VOLUME)/GGAF_MAX_VOLUME);

    //�{�����[��(0~100)�A�����f�V�x��(DSBVOLUME_MIN~DSBVOLUME_MAX)�ϊ��z��
    //DirectSounnd��SetVolume�̈����̒l(�P�ʁF1/100dB) �� 33.22f * 100.0 * log10(volume)   �A��0.0 < volume <= 1.0
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
    aDbVolume[GGAF_MIN_VOLUME] = DSBVOLUME_MIN;
    for (int i = 1; i <= GGAF_MAX_VOLUME-1; i++) {
        aDbVolume[i] = (int)(33.22f * 100.0 * log10(1.0*i / GGAF_MAX_VOLUME));
    }
    aDbVolume[GGAF_MAX_VOLUME] = DSBVOLUME_MAX;
}

void GgafDxSound::release() {
    _TRACE_("GgafDxSound::release() begin");
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pBgmManager);");
    DELETE_IMPOSSIBLE_NULL(_pBgmManager);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pSeManager);");
    DELETE_IMPOSSIBLE_NULL(_pSeManager);
    _TRACE_("RELEASE_IMPOSSIBLE_NULL(_pIDirectSound8);");
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSound8);
    _TRACE_("GgafDxSound::release() end");
}