#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

IDirectSound8* GgafDx9Sound::_pIDirectSound8 = NULL;

GgafDx9BgmManager* GgafDx9Sound::_pBgmManager = NULL;
GgafDx9SeManager* GgafDx9Sound::_pSeManager = NULL;
LONG GgafDx9Sound::aDbVolume[101];

DSCAPS GgafDx9Sound::_dsCaps;

float GgafDx9Sound::_master_volume_rate = 1.0;
float GgafDx9Sound::_bgm_volume_rate = 1.0;
float GgafDx9Sound::_se_volume_rate = 1.0;


void GgafDx9Sound::init() {
    HRESULT hr;
    hr = DirectSoundCreate8(NULL, &_pIDirectSound8, NULL);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDx9Sound::init() GgafDx9Sound���������ł��܂���B�T�E���h�J�[�h�f�o�C�X�ɖ��Ȃ����m�F���Ă��������B");
    }
    hr = _pIDirectSound8->SetCooperativeLevel(GgafDx9God::_pHWndPrimary, DSSCL_PRIORITY );
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDx9Sound::init() SetCooperativeLevel���s�B");
    }
    _dsCaps.dwSize = sizeof(_dsCaps);
    hr = GgafDx9Sound::_pIDirectSound8->GetCaps(&_dsCaps);
    if (hr != D3D_OK) {
        throwGgafCriticalException("GgafDx9Sound::init() GetCaps���s�B");
    }
    _pBgmManager = NEW GgafDx9BgmManager("OggBgmManager");
    _pSeManager = NEW GgafDx9SeManager("SoundEffectManager");

    GgafDx9Sound::setBgmVolume(1.0*CFG_PROPERTY(BGM_VOLUME)/GGAF_MAX_VOLUME);
    GgafDx9Sound::setSeVolume(1.0*CFG_PROPERTY(SE_VOLUME)/GGAF_MAX_VOLUME);
    GgafDx9Sound::setMasterVolume(1.0*CFG_PROPERTY(MASTER_VOLUME)/GGAF_MAX_VOLUME);

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

void GgafDx9Sound::release() {
    _TRACE_("GgafDx9Sound::release() begin");
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pBgmManager);");
    DELETE_IMPOSSIBLE_NULL(_pBgmManager);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pSeManager);");
    DELETE_IMPOSSIBLE_NULL(_pSeManager);
    _TRACE_("RELEASE_IMPOSSIBLE_NULL(_pIDirectSound8);");
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSound8);
    _TRACE_("GgafDx9Sound::release() end");
}
