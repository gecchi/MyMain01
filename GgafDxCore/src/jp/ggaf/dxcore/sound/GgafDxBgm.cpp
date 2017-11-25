#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisFile.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggDecoder.h"
#include "jp/ggaf/dxcore/sound/IkdLib/PCMPlayer.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"
#include "Shlwapi.h"
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace IkdLib;

GgafDxBgm::GgafDxBgm(const char* prm_bgm_key) : GgafObject() {
    if (GgafDxSound::_pIDirectSound8 == nullptr) {
        throwGgafCriticalException("prm_bgm_key="<<prm_bgm_key<<" DirectSound が、まだ初期化されていません。");
    }

    int len = strlen(prm_bgm_key);
    _bgm_key = NEW char[len+1];
    strcpy(_bgm_key, prm_bgm_key);

    _ogg_file_name = GgafProperties::_mapProperties[std::string(_bgm_key)];
    if (_ogg_file_name == "") {
        throwGgafCriticalException("prm_bgm_key="<<prm_bgm_key<<" プロパティファイルにキーがありません");
    }
    std::string full_ogg_file_name = getOggFileName(_ogg_file_name);
    _pOggResource = NEW OggVorbisFile( full_ogg_file_name.c_str() );
    _pOggDecoder =  NEW OggDecoder( _pOggResource );
    _pPcmPlayer = NEW PCMPlayer(GgafDxSound::_pIDirectSound8 , _pOggDecoder);
    _volume = GGAF_MAX_VOLUME;
    _pan = 0.0f;
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
                throwGgafCriticalException("oggファイルが見つかりません。ogg_file="<<ogg_file);
            }
        }
    }
}

void GgafDxBgm::play(bool prm_is_looping) {
    _pPcmPlayer->play(prm_is_looping);
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
    _TRACE_("GgafDxBgm::setVolume _bgm_key="<<_bgm_key<<"/prm_volume="<<prm_volume);
    _volume = prm_volume;
    //マスターBGM音量率を考慮
    int v = (int)(_volume * GgafDxSound::_pBgmManager->getBgmMasterVolumeRate());
    if (v > GGAF_MAX_VOLUME) {
        v = GGAF_MAX_VOLUME;
    }
    if (v < GGAF_MIN_VOLUME) {
        v = GGAF_MIN_VOLUME;
    }
    _TRACE_("GgafDxBgm::setVolume rate="<<GgafDxSound::_pBgmManager->getBgmMasterVolumeRate()<<"/v="<<v);
    int db = GgafDxSound::_a_db_volume[v];
    _pPcmPlayer->setVolume(db);
}

void GgafDxBgm::setPan(float prm_pan) {
    _pan = prm_pan;
    //TODO: マスターパン率はまだ無い
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

bool GgafDxBgm::isPause() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_PAUSE) {
        return true;
    } else {
        return false;
    }
}

bool GgafDxBgm::isStopping() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_STOP) {
        return true;
    } else {
        return false;
    }
}

GgafDxBgm::~GgafDxBgm() {
    _TRACE_(FUNC_NAME<<" begin");
    _TRACE_("_pPcmPlayer->setVolume(DSBVOLUME_MIN);");
    _pPcmPlayer->setVolume(DSBVOLUME_MIN);
    _TRACE_("_pPcmPlayer->terminateThread();");
    _pPcmPlayer->terminateThread();
    _TRACE_("GGAF_DELETE(_pPcmPlayer);");
    GGAF_DELETE(_pPcmPlayer);
    _TRACE_("GGAF_DELETE(_pOggDecoder);");
    GGAF_DELETE(_pOggDecoder);
    _TRACE_("GGAF_DELETE(_pOggResource);");
    GGAF_DELETE(_pOggResource);
    GGAF_DELETEARR(_bgm_key);
    _TRACE_(FUNC_NAME<<" end");
}

