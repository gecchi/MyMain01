#include "jp/ggaf/dx/sound/Bgm.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/IkdLib/OggVorbisFile.h"
#include "jp/ggaf/dx/sound/IkdLib/OggDecoder.h"
#include "jp/ggaf/dx/sound/IkdLib/PCMPlayer.h"
#include "jp/ggaf/dx/manager/BgmManager.h"

#ifdef __GNUG__
    #define __null
    #define NULL    0
    #define __in
    #define __out
#endif
#include <dsound.h>  //←sal.h を include する
#ifdef __GNUG__
    #undef __null
    #undef __in
    #undef __out
#endif
#include <Shlwapi.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


using namespace GgafDx;
using namespace IkdLib;

Bgm::Bgm(const char* prm_bgm_key) : GgafCore::Object() {
    if (Sound::_pIDirectSound8 == nullptr) {
        throwCriticalException("prm_bgm_key="<<prm_bgm_key<<" DirectSound が、まだ初期化されていません。");
    }

    int len = strlen(prm_bgm_key);
    _bgm_key = NEW char[len+1];
    strcpy(_bgm_key, prm_bgm_key);

    _ogg_file_name = GgafCore::Config::_properties.getStr(std::string(_bgm_key));
    if (_ogg_file_name == "") {
        throwCriticalException("prm_bgm_key="<<prm_bgm_key<<" プロパティファイルにキーがありません");
    }
    std::string full_ogg_file_name = getOggFileName(_ogg_file_name);
    _pOggResource = NEW OggVorbisFile( full_ogg_file_name.c_str() );
    _pOggDecoder =  NEW OggDecoder( _pOggResource );
    _pPcmPlayer = NEW PCMPlayer(Sound::_pIDirectSound8 , _pOggDecoder);
    setVolume(GGAF_MAX_VOLUME);
    setPan(0.0f);
}

std::string Bgm::getOggFileName(std::string prm_file) {
    std::string ogg_file = CONFIG::DIR_BGM[2] + "/" + prm_file;
    UTIL::strReplace(ogg_file, "//", "/");
    if (PathFileExists(ogg_file.c_str()) ) {
        return ogg_file;
    } else {
        ogg_file = CONFIG::DIR_BGM[1] + "/" + prm_file;
        UTIL::strReplace(ogg_file, "//", "/");
        if (PathFileExists(ogg_file.c_str()) ) {
            return ogg_file; //ユーザースキンに存在すればそれを優先
        } else {
            ogg_file = CONFIG::DIR_BGM[0] + "/" + prm_file;
            UTIL::strReplace(ogg_file, "//", "/");
            if (PathFileExists(ogg_file.c_str()) ) {
                return ogg_file;
            } else {
                throwCriticalException("oggファイルが見つかりません。ogg_file="<<ogg_file);
            }
        }
    }
}

void Bgm::play(bool prm_is_looping) {
    _pPcmPlayer->play(prm_is_looping);
}

void Bgm::pause() {
    _pPcmPlayer->pause();
}
void Bgm::unpause() {
    _pPcmPlayer->unpause();
}

void Bgm::stop() {
    _pPcmPlayer->stop();
}

void Bgm::setVolume(int prm_volume) {
    _volume = prm_volume;
    //マスターBGM音量率を考慮
    if (_volume > GGAF_MAX_VOLUME) {
        _volume = GGAF_MAX_VOLUME;
    }
    if (_volume < GGAF_MIN_VOLUME) {
        _volume = GGAF_MIN_VOLUME;
    }
    int v = (int)(_volume * Sound::_pBgmManager->getBgmMasterVolumeRate());
    if (v > GGAF_MAX_VOLUME) {
        v = GGAF_MAX_VOLUME;
    }
    if (v < GGAF_MIN_VOLUME) {
        v = GGAF_MIN_VOLUME;
    }
    int db = Sound::_a_db_volume[v];
    _pPcmPlayer->setVolume(db);
}

void Bgm::setPan(float prm_pan) {
    _pan = prm_pan;
    //TODO: マスターパン率はまだ無い
    _pPcmPlayer->setPan(prm_pan*DSBPAN_RIGHT);
}

void Bgm::clear() {
    _pPcmPlayer->clear();
}

bool Bgm::isPlaying() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_PLAY) {
        return true;
    } else {
        return false;
    }
}

bool Bgm::isPause() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_PAUSE) {
        return true;
    } else {
        return false;
    }
}

bool Bgm::isStopping() {
    if (_pPcmPlayer->getState() == PCMPlayer::STATE_STOP) {
        return true;
    } else {
        return false;
    }
}

Bgm::~Bgm() {
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

