#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Se::GgafDx9Se(char* prm_wave_name) : GgafObject() {
    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") DirectSound が、まだ初期化されていません。");
    }

    _wave_name = prm_wave_name;
    string wave_filename = GGAFDX9_PROPERTY(DIR_WAVE) + string(_wave_name) + ".wav";

    HRESULT hr;
    // Waveファイルを開く
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        _TRACE_("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") ファイル "<<wave_filename<<" が開けませんでした。");
        //return false;
    }

    // セカンダリバッファ作成
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE; //TODO:DSBCAPS_LOCSOFTWARE or DSBCAPS_LOCDEFERかどっち？
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    // バッファ作成
    hr = GgafDx9Sound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, NULL);
    checkDxException(hr, D3D_OK, "GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") CreateSoundBufferに失敗しました。サウンドカードは有効ですか？");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") ＜警告＞GgafDx9Se::writeBuffer()が失敗しています。");
    }
    hr = _pIDirectSoundBuffer->GetFrequency(&_dwDefaultFrequency);
    checkDxException(hr, D3D_OK, "GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") GetFrequency に失敗しました。サウンドカードは有効ですか？");

}



int GgafDx9Se::writeBuffer(CWaveDecorder& WaveFile) {
    // セカンダリ・バッファにWaveデータを書き込む
    LPVOID lpvPtr1; // 最初のブロックのポインタ
    DWORD dwBytes1; // 最初のブロックのサイズ
    LPVOID lpvPtr2; // ２番目のブロックのポインタ
    DWORD dwBytes2; // ２番目のブロックのサイズ

    HRESULT hr;

    hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

    // DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
    if (DSERR_BUFFERLOST == hr) {
        _TRACE_("GgafDx9Se::writeBuffer() DSERR_BUFFERLOST が返されました。バッファ復元を試みます");
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

void GgafDx9Se::play(int prm_iVolume, int prm_iPan, float prm_fRate_Frequency) {
_TRACE_(" 1");
    if (_pIDirectSoundBuffer == NULL) {
        _TRACE_("_pIDirectSoundBuffer==NULL;!");
    }
_TRACE_(" 2");
    DWORD dwStatus;
    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("GgafDx9Se::play() GetStatus() 失敗");
    }
    _TRACE_(" 3");
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("GgafDx9Se::play() Restore() 失敗");
        }
        _TRACE_(" 4");
        if (!restore()) {
            _TRACE_("GgafDx9Se::play() restore() 失敗");
        }
        _TRACE_(" 5");
    }
    _TRACE_(" 6");
    setVolume(prm_iVolume);
    setPan(prm_iPan);
    setFrequencyRate(prm_fRate_Frequency);
    HRESULT hr;
    _TRACE_(" 7");
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //バッファ頭だし
    _TRACE_(" 8");
    checkDxException(hr, DS_OK, "GgafDx9Se::play() SetCurrentPosition(0) が失敗しました。");
    hr = _pIDirectSoundBuffer->Play(0, 0, 0x00000000);
    _TRACE_(" 9");
    checkDxException(hr, DS_OK, "GgafDx9Se::play() Play(0, 0, 0x00000000) が失敗しました。");
}

void GgafDx9Se::setVolume(int prm_iVolume) {
    HRESULT hr = _pIDirectSoundBuffer->SetVolume(
                    DSBVOLUME_MIN + ((prm_iVolume - DSBVOLUME_MIN) * GgafDx9Sound::_master_volume_rate * GgafDx9Sound::_se_volume_rate)
                  );
    checkDxException(hr, DS_OK, "GgafDx9Se::setVolume() SetVolume("<<prm_iVolume<<") が失敗しました。");
}

void GgafDx9Se::setPan(int prm_iPan) {
    HRESULT hr = _pIDirectSoundBuffer->SetPan(prm_iPan);
    checkDxException(hr, DS_OK, "GgafDx9Se::setPan() SetPan("<<prm_iPan<<") が失敗しました。");
}

void GgafDx9Se::setFrequencyRate(float prm_fRate_Frequency) {
    HRESULT hr = _pIDirectSoundBuffer->SetFrequency((DWORD)(_dwDefaultFrequency*prm_fRate_Frequency)); //再生周波数設定
    checkDxException(hr, DS_OK, "GgafDx9Se::setFrequencyRate() SetFrequency((DWORD)"<<(_dwDefaultFrequency*prm_fRate_Frequency)<<") が失敗しました。");
}

int GgafDx9Se::restore(void) {
    string wave_filename = GGAFDX9_PROPERTY(DIR_WAVE) + _wave_name + ".wav";
    // Waveファイルを開く
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        return false;
    }

    if (!writeBuffer(WaveFile)) {
        return false;
    }
    return true;
}



GgafDx9Se::~GgafDx9Se() {
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSoundBuffer);
}
