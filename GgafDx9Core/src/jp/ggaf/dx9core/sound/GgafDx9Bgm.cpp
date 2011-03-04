#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace Dix;

//GgafDx9Bgm::GgafDx9Bgm(char* prm_ogg_name) : GgafObject() {
//    _TRACE_("GgafDx9Bgm::GgafDx9Bgm "<<prm_ogg_name);
//    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
//        throwGgafCriticalException("GgafDx9Bgm::GgafDx9Bgm("<<prm_ogg_name<<") DirectSound が、まだ初期化されていません。");
//    }
//    _file_name = string(prm_ogg_name);
//    string ogg_filename = GGAFDX9_PROPERTY(DIR_OGG) + _file_name + ".ogg";
//    pOggResource = NEW OggVorbisFile( ogg_filename.c_str() );
//    pOggDecoder =  NEW OggDecoder( pOggResource );
//    pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8 , pOggDecoder);
//}

GgafDx9Bgm::GgafDx9Bgm(char* prm_bgm_key) : GgafObject() {
    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDx9Bgm::GgafDx9Bgm("<<prm_bgm_key<<") DirectSound が、まだ初期化されていません。");
    }
    string bgm_key = string(prm_bgm_key);
    _ogg_file_name = (*GgafProperties::_pMapProperties)[bgm_key+"_OGG"];
    _bpm = atoi((*GgafProperties::_pMapProperties)[bgm_key+"_BPM"].c_str());
    _title = (*GgafProperties::_pMapProperties)[bgm_key+"_TITLE"];
    _TRACE_("GgafDx9Bgm::GgafDx9Bgm KEY="<<prm_bgm_key<<" _file_name="<<_ogg_file_name<<" _bpm="<<_bpm<<" _title="<<_title);
    string full_ogg_file_name = GGAFDX9_PROPERTY(DIR_OGG) + string(_ogg_file_name);
    pOggResource = NEW OggVorbisFile( full_ogg_file_name.c_str() );
    pOggDecoder =  NEW OggDecoder( pOggResource );
    pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8 , pOggDecoder);
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
    int db = GgafDx9Sound::aDbVolume[(LONG)(prm_volume * GgafDx9Sound::_master_volume_rate * GgafDx9Sound::_bgm_volume_rate)];
    pPcmPlayer->setVolume(db);
}

void GgafDx9Bgm::setPan(int prm_pan) {
    pPcmPlayer->setPan(prm_pan*DSBPAN_RIGHT);
}

void GgafDx9Bgm::clear() {
    pPcmPlayer->clear();
}

bool GgafDx9Bgm::isActiveActor() {
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
    _TRACE_("DELETE_IMPOSSIBLE_NULL(pOggDecoder);");
    DELETE_IMPOSSIBLE_NULL(pOggDecoder);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(pOggResource);");
    DELETE_IMPOSSIBLE_NULL(pOggResource);
    _TRACE_("GgafDx9Bgm::~GgafDx9Bgm() end");

}
