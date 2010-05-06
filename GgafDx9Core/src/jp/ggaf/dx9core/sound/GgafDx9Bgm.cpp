#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace Dix;

GgafDx9Bgm::GgafDx9Bgm(char* prm_ogg_name) : GgafObject() {
    _TRACE_("GgafDx9Bgm::GgafDx9Bgm "<<prm_ogg_name);
    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDx9Bgm::GgafDx9Bgm("<<prm_ogg_name<<") DirectSound ‚ªA‚Ü‚¾‰Šú‰»‚³‚ê‚Ä‚¢‚Ü‚¹‚ñB");
    }
    _ogg_name = prm_ogg_name;
    string ogg_filename = GGAFDX9_PROPERTY(DIR_OGG) + string(prm_ogg_name) + ".ogg";
    spOggResource = NEW OggVorbisFile( ogg_filename.c_str() );
    spOggDecoder =  NEW OggDecoder( spOggResource );
    pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8 , spOggDecoder);
}


void GgafDx9Bgm::play(int prm_volume, int prm_pan, bool prm_isLoop) {
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
    _TRACE_("pPcmPlayer->setVolume(DSBVOLUME_MIN);");
    pPcmPlayer->setVolume(DSBVOLUME_MIN);
    _TRACE_("pPcmPlayer->terminateThread();");
    pPcmPlayer->terminateThread();
    _TRACE_("DELETE_IMPOSSIBLE_NULL(pPcmPlayer);");
    DELETE_IMPOSSIBLE_NULL(pPcmPlayer);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(spOggDecoder);");
    DELETE_IMPOSSIBLE_NULL(spOggDecoder);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(spOggResource);");
    DELETE_IMPOSSIBLE_NULL(spOggResource);
    _TRACE_("GgafDx9Bgm::~GgafDx9Bgm() end");

}
