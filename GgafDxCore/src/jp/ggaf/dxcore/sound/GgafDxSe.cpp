#include "jp/ggaf/dxcore/sound/GgafDxSe.h"

#include <Shlwapi.h>
#include <d3d9.h>
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/CWaveDecorder.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSe::GgafDxSe(char* prm_wave_key) : GgafObject() {
    if (GgafDxSound::_pIDirectSound8 == nullptr) {
        throwGgafCriticalException("GgafDxSe::GgafDxSe("<<prm_wave_key<<") DirectSound が、まだ初期化されていません。");
    }
    _wave_key = NEW char[80];
    strcpy(_wave_key, prm_wave_key);

    _wave_file_name = (*GgafProperties::_pMapProperties)[prm_wave_key];
    std::string full_wave_file_name = getWaveFileName(_wave_file_name);

    HRESULT hr;
    // Waveファイルを開く
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)full_wave_file_name.c_str())) {
        throwGgafCriticalException("GgafDxSe::GgafDxSe("<<prm_wave_key<<") ファイル "<<full_wave_file_name<<" が開けませんでした。");
        //return false;
    }

    // セカンダリバッファ作成
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    //dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;//| DSBCAPS_GETCURRENTPOSITION2;// | DSBCAPS_LOCSOFTWARE;
    //TODO:DSBCAPS_LOCSOFTWARE or DSBCAPS_LOCDEFERかどっち？
    //TODO:GgafDxBgm と統一しなくても大丈夫？
    dsbdesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS;
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    // バッファ作成
    hr = GgafDxSound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, nullptr);
    checkDxException(hr, D3D_OK, "GgafDxSe::GgafDxSe("<<prm_wave_key<<") CreateSoundBufferに失敗しました。サウンドカードは有効ですか？");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("GgafDxSe::GgafDxSe("<<prm_wave_key<<") ＜警告＞GgafDxSe::writeBuffer()が失敗しています。");
    }
    hr = _pIDirectSoundBuffer->GetFrequency(&_default_frequency);
    checkDxException(hr, D3D_OK, "GgafDxSe::GgafDxSe("<<prm_wave_key<<") GetFrequency に失敗しました。サウンドカードは有効ですか？");

    _pActor_last_played = nullptr;
    _can_looping = false;
    _TRACE_("GgafDxSe::GgafDxSe("<<prm_wave_key<<") _wave_file_name="<<_wave_file_name<<" this="<<this<<" _id="<<getId());
}


std::string GgafDxSe::getWaveFileName(std::string prm_file) {
    std::string wave_file = PROPERTY::DIR_WAVE[2] + "/" + prm_file;
    UTIL::strReplace(wave_file, "//", "/");
    if (PathFileExists(wave_file.c_str()) ) {
        return wave_file;
    } else {
        wave_file = PROPERTY::DIR_WAVE[1] + "/" + prm_file;
        UTIL::strReplace(wave_file, "//", "/");
        if (PathFileExists(wave_file.c_str()) ) {
            return wave_file; //ユーザースキンに存在すればそれを優先
        } else {
            wave_file = PROPERTY::DIR_WAVE[0] + "/" + prm_file;
            UTIL::strReplace(wave_file, "//", "/");
            if (PathFileExists(wave_file.c_str()) ) {
                return wave_file;
            } else {
                throwGgafCriticalException("GgafDxSe::getWaveFileName waveファイルが見つかりません。wave_file="<<wave_file);
            }
        }
    }
}

int GgafDxSe::writeBuffer(CWaveDecorder& WaveFile) {
    // セカンダリ・バッファにWaveデータを書き込む
    LPVOID lpvPtr1; // 最初のブロックのポインタ
    DWORD dwBytes1; // 最初のブロックのサイズ
    LPVOID lpvPtr2; // ２番目のブロックのポインタ
    DWORD dwBytes2; // ２番目のブロックのサイズ
    HRESULT hr;

    hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

    // DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
    if (DSERR_BUFFERLOST == hr) {
        _TRACE_("GgafDxSe::writeBuffer() DSERR_BUFFERLOST が返されました。バッファ復元を試みます");
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

void GgafDxSe::play(int prm_volume, float prm_pan, float prm_frequency) {
    if (_pIDirectSoundBuffer == nullptr) {
        _TRACE_("_pIDirectSoundBuffer==nullptr;!");
    }
    DWORD dwStatus;
    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("GgafDxSe::play() GetStatus() 失敗");
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("GgafDxSe::play() Restore() 失敗");
        }
        if (!restore()) {
            _TRACE_("GgafDxSe::play() restore() 失敗");
        }
    }
    setVolume(prm_volume);
    setPan(prm_pan);
    setFrequencyRate(prm_frequency);
    HRESULT hr;
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //バッファ頭だし
    checkDxException(hr, DS_OK, "GgafDxSe::play() SetCurrentPosition(0) が失敗しました。");
    if (_can_looping) {
        hr = _pIDirectSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
        checkDxException(hr, DS_OK, "GgafDxSe::play() Play(0, 0, DSBPLAY_LOOPING) が失敗しました。");
    } else {
        hr = _pIDirectSoundBuffer->Play(0, 0, 0x00000000);
        checkDxException(hr, DS_OK, "GgafDxSe::play() Play(0, 0, 0x00000000) が失敗しました。");
    }
}

void GgafDxSe::play() {
    play(GGAF_MAX_VOLUME, 0.0f);
}

void GgafDxSe::stop() {
    HRESULT hr;
    hr = _pIDirectSoundBuffer->Stop();
    checkDxException(hr, DS_OK, "GgafDxSe::stop() Stop() が失敗しました。");
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //バッファ頭だし
    checkDxException(hr, DS_OK, "GgafDxSe::stop() SetCurrentPosition(0) が失敗しました。");
}

void GgafDxSe::setVolume(int prm_volume) {
    int db = GgafDxSound::_a_db_volume[(int)(prm_volume * GgafDxSound::_app_master_volume_rate * GgafDxSound::_se_master_volume_rate)];
    HRESULT hr = _pIDirectSoundBuffer->SetVolume(db);
    checkDxException(hr, DS_OK, "GgafDxSe::setVolume() SetVolume("<<prm_volume<<") が失敗しました。");
}

void GgafDxSe::setPan(float prm_pan) {
    HRESULT hr = _pIDirectSoundBuffer->SetPan((LONG)(prm_pan*DSBPAN_RIGHT));
    checkDxException(hr, DS_OK, "GgafDxSe::setPan() SetPan("<<prm_pan<<") が失敗しました。");
}

void GgafDxSe::setFrequencyRate(float prm_frequency) {
    HRESULT hr = _pIDirectSoundBuffer->SetFrequency((DWORD)(_default_frequency*prm_frequency)); //再生周波数設定
    checkDxException(hr, DS_OK, "GgafDxSe::setFrequencyRate() SetFrequency((DWORD)"<<(_default_frequency*prm_frequency)<<") が失敗しました。");
}

int GgafDxSe::restore(void) {
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

bool GgafDxSe::isPlaying() {
    DWORD dwStatus = 0;
    _pIDirectSoundBuffer->GetStatus( &dwStatus );
    if( (dwStatus & DSBSTATUS_PLAYING) != 0 ) {
        return true;
    } else {
        return false;
    }
}

GgafDxSe::~GgafDxSe() {
    _TRACE_("GgafDxSe::~GgafDxSe() _wave_key="<<_wave_key<<" _wave_file_name="<<_wave_file_name<<" this="<<this);
    GGAF_DELETEARR_NULLABLE(_wave_key);
    GGAF_RELEASE(_pIDirectSoundBuffer);
}
