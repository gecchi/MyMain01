#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSe::GgafDxSe(char* prm_wave_name) : GgafObject() {
    if (GgafDxSound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDxSe::GgafDxSe("<<prm_wave_name<<") DirectSound が、まだ初期化されていません。");
    }

    _wave_name = NEW char[128];
    strcpy(_wave_name, prm_wave_name);
    string wave_filename = GGAF_PROPERTY(DIR_WAVE) + string(_wave_name) + ".wav";

    HRESULT hr;
    // Waveファイルを開く
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        throwGgafCriticalException("GgafDxSe::GgafDxSe("<<prm_wave_name<<") ファイル "<<wave_filename<<" が開けませんでした。");
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
    hr = GgafDxSound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, NULL);
    checkDxException(hr, D3D_OK, "GgafDxSe::GgafDxSe("<<prm_wave_name<<") CreateSoundBufferに失敗しました。サウンドカードは有効ですか？");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("GgafDxSe::GgafDxSe("<<prm_wave_name<<") ＜警告＞GgafDxSe::writeBuffer()が失敗しています。");
    }
    hr = _pIDirectSoundBuffer->GetFrequency(&_dwDefaultFrequency);
    checkDxException(hr, D3D_OK, "GgafDxSe::GgafDxSe("<<prm_wave_name<<") GetFrequency に失敗しました。サウンドカードは有効ですか？");

	_TRACE_("GgafDxSe::GgafDxSe() _wave_name="<<_wave_name<<" this="<<this<<" _id="<<_id);
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

void GgafDxSe::play(int prm_iVolume, float prm_fPan, float prm_fRate_Frequency) {
    if (_pIDirectSoundBuffer == NULL) {
        _TRACE_("_pIDirectSoundBuffer==NULL;!");
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
    setVolume(prm_iVolume);
    setPan(prm_fPan);
    setFrequencyRate(prm_fRate_Frequency);
    HRESULT hr;
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //バッファ頭だし
    checkDxException(hr, DS_OK, "GgafDxSe::play() SetCurrentPosition(0) が失敗しました。");
    hr = _pIDirectSoundBuffer->Play(0, 0, 0x00000000);
    checkDxException(hr, DS_OK, "GgafDxSe::play() Play(0, 0, 0x00000000) が失敗しました。");
}

void GgafDxSe::setVolume(int prm_iVolume) {
    int db = GgafDxSound::aDbVolume[(LONG)(prm_iVolume * GgafDxSound::_master_volume_rate * GgafDxSound::_se_volume_rate)];
    HRESULT hr = _pIDirectSoundBuffer->SetVolume(db);
    checkDxException(hr, DS_OK, "GgafDxSe::setVolume() SetVolume("<<prm_iVolume<<") が失敗しました。");
}

void GgafDxSe::setPan(float prm_fPan) {
    HRESULT hr = _pIDirectSoundBuffer->SetPan(prm_fPan*DSBPAN_RIGHT);
    checkDxException(hr, DS_OK, "GgafDxSe::setPan() SetPan("<<prm_fPan<<") が失敗しました。");
}

void GgafDxSe::setFrequencyRate(float prm_fRate_Frequency) {
    HRESULT hr = _pIDirectSoundBuffer->SetFrequency((DWORD)(_dwDefaultFrequency*prm_fRate_Frequency)); //再生周波数設定
    checkDxException(hr, DS_OK, "GgafDxSe::setFrequencyRate() SetFrequency((DWORD)"<<(_dwDefaultFrequency*prm_fRate_Frequency)<<") が失敗しました。");
}

int GgafDxSe::restore(void) {
    string wave_filename = GGAF_PROPERTY(DIR_WAVE) + _wave_name + ".wav";
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
    _TRACE_("GgafDxSe::~GgafDxSe() _wave_name="<<_wave_name<<" this="<<this<<" _id="<<_id);
    DELETEARR_IMPOSSIBLE_NULL(_wave_name);
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSoundBuffer);
}
