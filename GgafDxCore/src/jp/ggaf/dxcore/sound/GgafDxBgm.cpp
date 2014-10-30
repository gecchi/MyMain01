#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"

#include "Shlwapi.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisFile.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggDecoder.h"
#include "jp/ggaf/dxcore/sound/IkdLib/PCMPlayer.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace IkdLib;

//GgafDxBgm::GgafDxBgm(char* prm_ogg_name) : GgafObject() {
//    _DTRACE_("GgafDxBgm::GgafDxBgm "<<prm_ogg_name);
//    if (GgafDxSound::_pIDirectSound8 == nullptr) {
//        throwGgafCriticalException("GgafDxBgm::GgafDxBgm("<<prm_ogg_name<<") DirectSound が、まだ初期化されていません。");
//    }
//    _file_name = std::string(prm_ogg_name);
//    std::string ogg_filename = PROPERTY::DIR_OGG[0] + _file_name + ".ogg";
//    _pOggResource = NEW OggVorbisFile( ogg_filename.c_str() );
//    _pOggDecoder =  NEW OggDecoder( _pOggResource );
//    _pPcmPlayer = NEW PCMPlayer(GgafDxSound::_pIDirectSound8 , _pOggDecoder);
//}

GgafDxBgm::GgafDxBgm(char* prm_bgm_key) : GgafObject() {
    if (GgafDxSound::_pIDirectSound8 == nullptr) {
        throwGgafCriticalException("GgafDxBgm::GgafDxBgm("<<prm_bgm_key<<") DirectSound が、まだ初期化されていません。");
    }
    std::string bgm_key = std::string(prm_bgm_key);
    _ogg_file_name = (*GgafProperties::_pMapProperties)[bgm_key];
    if (_ogg_file_name == "") {
        throwGgafCriticalException("GgafDxBgm::GgafDxBgm("<<prm_bgm_key<<") プロパティファイルにキーがありません");
    }
//    _bpm = atoi((*GgafProperties::_pMapProperties)[bgm_key+"_BPM"].c_str());
//    _title = (*GgafProperties::_pMapProperties)[bgm_key+"_TITLE"];
//    _DTRACE_("GgafDxBgm::GgafDxBgm KEY="<<prm_bgm_key<<" _file_name="<<_ogg_file_name<<" _bpm="<<_bpm<<" _title="<<_title);
    std::string full_ogg_file_name = getOggFileName(_ogg_file_name);
    _pOggResource = NEW OggVorbisFile( full_ogg_file_name.c_str() );
    _pOggDecoder =  NEW OggDecoder( _pOggResource );
    _pPcmPlayer = NEW PCMPlayer(GgafDxSound::_pIDirectSound8 , _pOggDecoder);
}

std::string GgafDxBgm::getOggFileName(std::string prm_file) {
    std::string ogg_file = PROPERTY::DIR_OGG[2] + "/" + prm_file;
    UTIL::strReplace(ogg_file, "//", "/");
    if (PathFileExists(ogg_file.c_str()) ) {
        return ogg_file;
    } else {
        ogg_file = PROPERTY::DIR_OGG[1] + "/" + prm_file;
        UTIL::strReplace(ogg_file, "//", "/");
        if (PathFileExists(ogg_file.c_str()) ) {
            return ogg_file; //ユーザースキンに存在すればそれを優先
        } else {
            ogg_file = PROPERTY::DIR_OGG[0] + "/" + prm_file;
            UTIL::strReplace(ogg_file, "//", "/");
            if (PathFileExists(ogg_file.c_str()) ) {
                return ogg_file;
            } else {
                throwGgafCriticalException("GgafDxBgm::getOggFileName oggファイルが見つかりません。ogg_file="<<ogg_file);
            }
        }
    }
}

void GgafDxBgm::play(int prm_volume, float prm_pan, bool prm_is_looping) {
    setVolume(prm_volume);
    setPan(prm_pan);
    _pPcmPlayer->play(prm_is_looping);
}
void GgafDxBgm::play(bool prm_is_looping) {
    play(GGAF_MAX_VOLUME, 0.0f, prm_is_looping);
}
void GgafDxBgm::pause() {
    _pPcmPlayer->pause();
}
void GgafDxBgm::unpause() {
    _pPcmPlayer->unpause();
}

void GgafDxBgm::stop() {
    _pPcmPlayer->stop();
}

void GgafDxBgm::setVolume(int prm_volume) {
    //ボリューム→デシベル
    int db = GgafDxSound::_a_db_volume[(int)(prm_volume * GgafDxSound::_app_master_volume_rate * GgafDxSound::_bgm_master_volume_rate)];
    _pPcmPlayer->setVolume(db);
}

void GgafDxBgm::setPan(float prm_pan) {
    _pPcmPlayer->setPan(prm_pan*DSBPAN_RIGHT);
}


void GgafDxBgm::clear() {
    _pPcmPlayer->clear();
}

bool GgafDxBgm::isPlaying() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_PLAY) {
        return true;
    } else {
        return false;
    }
}

GgafDxBgm::~GgafDxBgm() {
    _DTRACE_("GgafDxBgm::~GgafDxBgm() begin");
    _DTRACE_("_pPcmPlayer->setVolume(DSBVOLUME_MIN);");
    _pPcmPlayer->setVolume(DSBVOLUME_MIN);
    _DTRACE_("_pPcmPlayer->terminateThread();");
    _pPcmPlayer->terminateThread();
    _DTRACE_("GGAF_DELETE(_pPcmPlayer);");
    GGAF_DELETE(_pPcmPlayer);
    _DTRACE_("GGAF_DELETE(_pOggDecoder);");
    GGAF_DELETE(_pOggDecoder);
    _DTRACE_("GGAF_DELETE(_pOggResource);");
    GGAF_DELETE(_pOggResource);
    _DTRACE_("GgafDxBgm::~GgafDxBgm() end");
}

