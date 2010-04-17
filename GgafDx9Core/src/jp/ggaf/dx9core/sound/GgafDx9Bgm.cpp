#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace Dix;

GgafDx9Bgm::GgafDx9Bgm(char* prm_ogg_name) : GgafObject() {
    _TRACE_("GgafDx9Bgm::GgafDx9Bgm "<<prm_ogg_name);
    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDx9Bgm::GgafDx9Bgm("<<prm_ogg_name<<") DirectSound が、まだ初期化されていません。");
    }
    _ogg_name = prm_ogg_name;
    string ogg_filename = GGAFDX9_PROPERTY(DIR_OGG) + string(prm_ogg_name) + ".ogg";
    spOggResource.SetPtr(NEW OggVorbisFile( ogg_filename.c_str() ));
    spOggDecoder.SetPtr( NEW OggDecoder( spOggResource ) );
    pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8 , spOggDecoder);
    _is_fade = false;
    _now_volume = DSBVOLUME_MAX;
    _target_volume = DSBVOLUME_MAX;
    _inc_volume = 0;
}

void GgafDx9Bgm::behave() {
    if (_is_fade) {
		_now_volume += _inc_volume;
	    pPcmPlayer->setVolume((int)(DSBVOLUME_MIN + ((_now_volume - DSBVOLUME_MIN) * GgafDx9Sound::_master_volume_rate * GgafDx9Sound::_bgm_volume_rate)));
		//ここでsetVolumeで呼び出すと、_now_volumeが丸め込まれて、永遠に_target_volumeにならない場合がある
        if (_inc_volume > 0 && _now_volume >= _target_volume) {
            //増音量時
            setVolume((int)_target_volume);
            _is_fade = false;
        } else if (_inc_volume < 0 && _now_volume <= _target_volume) {
            //減音量時
            setVolume((int)_target_volume);
            _is_fade = false;
        }
    }
}

void GgafDx9Bgm::fade(DWORD prm_frame, int prm_target_volume) {
    _is_fade = true;
    _target_volume = (double)prm_target_volume;
    _inc_volume = (prm_target_volume - _now_volume) / (double)prm_frame;
}

void GgafDx9Bgm::play(int prm_volume, int prm_pan, bool prm_isLoop) {
    _is_fade = false;
    setVolume(prm_volume);
    setPan(prm_pan);
    pPcmPlayer->play(prm_isLoop);
}

void GgafDx9Bgm::pause() {
    pPcmPlayer->pause();
}

void GgafDx9Bgm::stop() {
    pPcmPlayer->stop();
}

void GgafDx9Bgm::setVolume(int prm_volume) {
    _now_volume = (double)prm_volume;
	_TRACE_("GgafDx9Bgm::setVolume("<<_now_volume<<") 実値="<<(int)(DSBVOLUME_MIN + ((prm_volume - DSBVOLUME_MIN) * GgafDx9Sound::_master_volume_rate * GgafDx9Sound::_bgm_volume_rate))<<" _ogg_name="<<_ogg_name);
    pPcmPlayer->setVolume(DSBVOLUME_MIN + ((prm_volume - DSBVOLUME_MIN) * GgafDx9Sound::_master_volume_rate * GgafDx9Sound::_bgm_volume_rate));
	
}

void GgafDx9Bgm::setPan(int prm_pan) {
    pPcmPlayer->setPan(prm_pan);
}

void GgafDx9Bgm::clear() {
    pPcmPlayer->clear();
}

bool GgafDx9Bgm::isActive() {
    if (pPcmPlayer->getState() == PCMPlayer::STATE_PLAY) {
        return true;
    } else {
        return false;
    }
}

GgafDx9Bgm::~GgafDx9Bgm() {
    _TRACE_("GgafDx9Bgm::~GgafDx9Bgm() begin");
    pPcmPlayer->terminateThread();
    pPcmPlayer->stop();
    _TRACE_("GgafDx9Bgm::~GgafDx9Bgm() end");
    delete pPcmPlayer;

}
