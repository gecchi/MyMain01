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
//    string ogg_filename = CFG_PROPERTY(DIR_OGG) + _file_name + ".ogg";
//    _pOggResource = NEW OggVorbisFile( ogg_filename.c_str() );
//    _pOggDecoder =  NEW OggDecoder( _pOggResource );
//    _pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8 , _pOggDecoder);
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
    string full_ogg_file_name = CFG_PROPERTY(DIR_OGG) + string(_ogg_file_name);
    _pOggResource = NEW OggVorbisFile( full_ogg_file_name.c_str() );
    _pOggDecoder =  NEW OggDecoder( _pOggResource );
    _pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8 , _pOggDecoder);
}

void GgafDx9Bgm::play(int prm_volume, float prm_pan, bool prm_is_looping) {
    setVolume(prm_volume);
    setPan(prm_pan);
    _pPcmPlayer->play(prm_is_looping);
}

void GgafDx9Bgm::pause() {
    _pPcmPlayer->pause();
}

void GgafDx9Bgm::stop() {
    _pPcmPlayer->stop();
}

void GgafDx9Bgm::setVolume(int prm_volume) {
    //ボリューム→デシベル
    int db = GgafDx9Sound::aDbVolume[(LONG)(prm_volume * GgafDx9Sound::_master_volume_rate * GgafDx9Sound::_bgm_volume_rate)];
    _pPcmPlayer->setVolume(db);
}

void GgafDx9Bgm::setPan(float prm_pan) {

    _pPcmPlayer->setPan(prm_pan*DSBPAN_RIGHT);
}

void GgafDx9Bgm::clear() {
    _pPcmPlayer->clear();
}

bool GgafDx9Bgm::isActiveActor() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_PLAY) {
        return true;
    } else {
        return false;
    }
}

GgafDx9Bgm::~GgafDx9Bgm() {
    _TRACE_("GgafDx9Bgm::~GgafDx9Bgm() begin");
    _TRACE_("_pPcmPlayer->setVolume(DSBVOLUME_MIN);");
    _pPcmPlayer->setVolume(DSBVOLUME_MIN);
    _TRACE_("_pPcmPlayer->terminateThread();");
    _pPcmPlayer->terminateThread();
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pPcmPlayer);");
    DELETE_IMPOSSIBLE_NULL(_pPcmPlayer);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pOggDecoder);");
    DELETE_IMPOSSIBLE_NULL(_pOggDecoder);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pOggResource);");
    DELETE_IMPOSSIBLE_NULL(_pOggResource);
    _TRACE_("GgafDx9Bgm::~GgafDx9Bgm() end");

}
