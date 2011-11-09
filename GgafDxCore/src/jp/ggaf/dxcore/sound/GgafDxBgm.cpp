#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace Dix;

//GgafDxBgm::GgafDxBgm(char* prm_ogg_name) : GgafObject() {
//    _TRACE_("GgafDxBgm::GgafDxBgm "<<prm_ogg_name);
//    if (GgafDxSound::_pIDirectSound8 == NULL) {
//        throwGgafCriticalException("GgafDxBgm::GgafDxBgm("<<prm_ogg_name<<") DirectSound ���A�܂�����������Ă��܂���B");
//    }
//    _file_name = string(prm_ogg_name);
//    string ogg_filename = CFG_PROPERTY(DIR_OGG) + _file_name + ".ogg";
//    _pOggResource = NEW OggVorbisFile( ogg_filename.c_str() );
//    _pOggDecoder =  NEW OggDecoder( _pOggResource );
//    _pPcmPlayer = NEW PCMPlayer(GgafDxSound::_pIDirectSound8 , _pOggDecoder);
//}

GgafDxBgm::GgafDxBgm(char* prm_bgm_key) : GgafObject() {
    if (GgafDxSound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDxBgm::GgafDxBgm("<<prm_bgm_key<<") DirectSound ���A�܂�����������Ă��܂���B");
    }
    string bgm_key = string(prm_bgm_key);
    _ogg_file_name = (*GgafProperties::_pMapProperties)[bgm_key+"_OGG"];
    _bpm = atoi((*GgafProperties::_pMapProperties)[bgm_key+"_BPM"].c_str());
    _title = (*GgafProperties::_pMapProperties)[bgm_key+"_TITLE"];
    _TRACE_("GgafDxBgm::GgafDxBgm KEY="<<prm_bgm_key<<" _file_name="<<_ogg_file_name<<" _bpm="<<_bpm<<" _title="<<_title);
    string full_ogg_file_name = CFG_PROPERTY(DIR_OGG) + string(_ogg_file_name);
    _pOggResource = NEW OggVorbisFile( full_ogg_file_name.c_str() );
    _pOggDecoder =  NEW OggDecoder( _pOggResource );
    _pPcmPlayer = NEW PCMPlayer(GgafDxSound::_pIDirectSound8 , _pOggDecoder);
}

void GgafDxBgm::play(int prm_volume, float prm_pan, bool prm_is_looping) {
    setVolume(prm_volume);
    setPan(prm_pan);
    _pPcmPlayer->play(prm_is_looping);
}

void GgafDxBgm::pause() {
    _pPcmPlayer->pause();
}

void GgafDxBgm::stop() {
    _pPcmPlayer->stop();
}

void GgafDxBgm::setVolume(int prm_volume) {
    //�{�����[�����f�V�x��
    int db = GgafDxSound::aDbVolume[(LONG)(prm_volume * GgafDxSound::_master_volume_rate * GgafDxSound::_bgm_volume_rate)];
    _pPcmPlayer->setVolume(db);
}

void GgafDxBgm::setPan(float prm_pan) {

    _pPcmPlayer->setPan(prm_pan*DSBPAN_RIGHT);
}

void GgafDxBgm::clear() {
    _pPcmPlayer->clear();
}

bool GgafDxBgm::isActive() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_PLAY) {
        return true;
    } else {
        return false;
    }
}

GgafDxBgm::~GgafDxBgm() {
    _TRACE_("GgafDxBgm::~GgafDxBgm() begin");
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
    _TRACE_("GgafDxBgm::~GgafDxBgm() end");

}