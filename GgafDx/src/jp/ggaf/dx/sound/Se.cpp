#include "jp/ggaf/dx/sound/Se.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/CWaveDecorder.h"
#include "jp/ggaf/dx/manager/SeManager.h"
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
#include <d3d9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


using namespace GgafDx;

Se::Se(const char* prm_wave_key) : GgafCore::Object() {
    if (Sound::_pIDirectSound8 == nullptr) {
        throwCriticalException("prm_wave_key="<<prm_wave_key<<" DirectSound が、まだ初期化されていません。");
    }

    int len = strlen(prm_wave_key);
    _wave_key = NEW char[len+1];
    strcpy(_wave_key, prm_wave_key);

    _wave_file_name = GgafCore::Config::_properties.getStr(std::string(_wave_key));
    std::string full_wave_file_name = getWaveFileName(_wave_file_name);

    HRESULT hr;
    // Waveファイルを開く
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)full_wave_file_name.c_str())) {
        throwCriticalException("prm_wave_key="<<prm_wave_key<<" ファイル "<<full_wave_file_name<<" が開けませんでした。");
        //return false;
    }

    // セカンダリバッファ作成
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    //dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;//| DSBCAPS_GETCURRENTPOSITION2;// | DSBCAPS_LOCSOFTWARE;
    //TODO:DSBCAPS_LOCSOFTWARE or DSBCAPS_LOCDEFERかどっち？
    //TODO:Bgm と統一しなくても大丈夫？
    dsbdesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS;
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    // バッファ作成
    hr = Sound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, nullptr);
    checkDxException(hr, D3D_OK, "prm_wave_key="<<prm_wave_key<<" CreateSoundBufferに失敗しました。サウンドカードは有効ですか？");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("Se::Se("<<prm_wave_key<<") 【警告】Se::writeBuffer()が失敗しています。");
    }
    hr = _pIDirectSoundBuffer->GetFrequency(&_default_frequency);
    checkDxException(hr, D3D_OK, "prm_wave_key="<<prm_wave_key<<" GetFrequency に失敗しました。サウンドカードは有効ですか？");

    _pActor_last_played = nullptr;
    setVolume(GGAF_MAX_VOLUME);
    setPan(0.0f);
    setFrequencyRate(1.0);
    _TRACE_("Se::Se("<<prm_wave_key<<") _wave_file_name="<<_wave_file_name<<" this="<<this<<" _id="<<getId());
}


std::string Se::getWaveFileName(std::string prm_file) {
    std::string wave_file = CONFIG::DIR_SE[2] + "/" + prm_file;
    UTIL::strReplace(wave_file, "//", "/");
    if (PathFileExists(wave_file.c_str()) ) {
        return wave_file;
    } else {
        wave_file = CONFIG::DIR_SE[1] + "/" + prm_file;
        UTIL::strReplace(wave_file, "//", "/");
        if (PathFileExists(wave_file.c_str()) ) {
            return wave_file; //ユーザースキンに存在すればそれを優先
        } else {
            wave_file = CONFIG::DIR_SE[0] + "/" + prm_file;
            UTIL::strReplace(wave_file, "//", "/");
            if (PathFileExists(wave_file.c_str()) ) {
                return wave_file;
            } else {
                throwCriticalException("Se::getWaveFileName() waveファイルが見つかりません。wave_file="<<wave_file);
            }
        }
    }
}

int Se::writeBuffer(CWaveDecorder& WaveFile) {
    // セカンダリ・バッファにWaveデータを書き込む
    LPVOID lpvPtr1; // 最初のブロックのポインタ
    DWORD dwBytes1; // 最初のブロックのサイズ
    LPVOID lpvPtr2; // ２番目のブロックのポインタ
    DWORD dwBytes2; // ２番目のブロックのサイズ
    HRESULT hr;
    hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
    // DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
    if (DSERR_BUFFERLOST == hr) {
        _TRACE_("DSERR_BUFFERLOST が返されました。バッファ復元を試みます");
        _pIDirectSoundBuffer->Restore();
        hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
    }

    if (hr != D3D_OK) {
        return false;
    }
    // ロック成功
    // ここで，バッファに書き込む
    // バッファにデータをコピーする
    long lSize = WaveFile.GetWave(static_cast<LPBYTE> (lpvPtr1), dwBytes1);
    if (lSize > 0 && dwBytes2 != 0) {
        lSize = WaveFile.GetWave(static_cast<LPBYTE> (lpvPtr2), dwBytes2);
    }
    // 書き込みが終わったらすぐにUnlockする．
    _pIDirectSoundBuffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
    if (lSize < 0) {
        return false;
    }
    return true;
}

void Se::play(bool prm_is_looping) {
    int v = (int)(_volume * Sound::_pSeManager->getSeMasterVolumeRate());
    if (v == 0) {
        return;
    }
    if (_pIDirectSoundBuffer == nullptr) {
        _TRACE_("_pIDirectSoundBuffer==nullptr;!");
    }
    DWORD dwStatus;
    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("失敗");
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("失敗");
        }
        if (!restore()) {
            _TRACE_("失敗");
        }
    }
    HRESULT hr;
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //バッファ頭だし
    checkDxException(hr, DS_OK, "SetCurrentPosition(0) が失敗しました。");
    if (prm_is_looping) {
        hr = _pIDirectSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
        checkDxException(hr, DS_OK, "Play(0, 0, DSBPLAY_LOOPING) が失敗しました。");
    } else {
        hr = _pIDirectSoundBuffer->Play(0, 0, 0x00000000);
        checkDxException(hr, DS_OK, "Play(0, 0, 0x00000000) が失敗しました。");
    }
}

void Se::stop() {
    HRESULT hr;
    hr = _pIDirectSoundBuffer->Stop();
#ifdef MY_DEBUG
    if (hr != DS_OK) {
        _TRACE_("Se::stop() Stop() 失敗しました。_wave_key="<<_wave_key);
    }
#endif
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //バッファ頭だし
#ifdef MY_DEBUG
    if (hr != DS_OK) {
        _TRACE_("Se::stop() SetCurrentPosition(0) 失敗しました。_wave_key="<<_wave_key);
    }
#endif
}

void Se::setVolume(int prm_volume) {
    _volume = prm_volume;
    //マスターSE音量率を考慮
    int v = (int)(_volume * Sound::_pSeManager->getSeMasterVolumeRate());
    if (v > GGAF_MAX_VOLUME) {
        v = GGAF_MAX_VOLUME;
    }
    int db = Sound::_a_db_volume[v];
    HRESULT hr = _pIDirectSoundBuffer->SetVolume(db);
    checkDxException(hr, DS_OK, "SetVolume("<<prm_volume<<") が失敗しました。");
}

void Se::setPan(float prm_pan) {
    _pan = prm_pan;
    //TODO: マスターパン率はまだ無い
    HRESULT hr = _pIDirectSoundBuffer->SetPan((LONG)(_pan*DSBPAN_RIGHT));
    checkDxException(hr, DS_OK, "SetPan("<<prm_pan<<") が失敗しました。");
}

void Se::setFrequencyRate(float prm_frequency_rate) {
    _frequency_rate = prm_frequency_rate;
    //TODO: マスター周波数率はまだ無い
    DWORD frequency = (DWORD)(_default_frequency*prm_frequency_rate);
    static DWORD min_frequency = Sound::_pDsCaps->dwMinSecondarySampleRate; //周波数下限
    static DWORD max_frequency = Sound::_pDsCaps->dwMaxSecondarySampleRate; //周波数上限
    if (frequency < min_frequency) {
        frequency = min_frequency;
    } else if (frequency > max_frequency) {
        frequency = max_frequency;
    }
    HRESULT hr = _pIDirectSoundBuffer->SetFrequency(frequency); //再生周波数設定
    checkDxException(hr, DS_OK, "SetFrequency("<<frequency<<") が失敗しました。");
}

int Se::restore(void) {
    std::string full_wave_file_name = getWaveFileName(_wave_file_name);
    // Waveファイルを開く
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)full_wave_file_name.c_str())) {
        return false;
    }
    if (!writeBuffer(WaveFile)) {
        return false;
    }
    return true;
}

bool Se::isPlaying() {
    DWORD dwStatus = 0;
    _pIDirectSoundBuffer->GetStatus( &dwStatus );
    if( (dwStatus & DSBSTATUS_PLAYING) != 0 ) {
        return true;
    } else {
        return false;
    }
}

Se::~Se() {
    _TRACE_("_wave_key="<<_wave_key<<" _wave_file_name="<<_wave_file_name<<" this="<<this);
    GGAF_DELETEARR_NULLABLE(_wave_key);
    GGAF_RELEASE(_pIDirectSoundBuffer);
}
