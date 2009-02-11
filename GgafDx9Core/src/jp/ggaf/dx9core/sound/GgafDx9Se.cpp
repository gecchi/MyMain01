#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

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
        _TRACE_("DSERR_BUFFERLOST!");
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
GgafDx9Se::GgafDx9Se(char* prm_wave_name, int prm_iBufferCount) :
    GgafObject() {
    _wave_name = prm_wave_name;
    string wave_filename = GGAFDX9_PROPERTY(DIR_WAVE) + string(_wave_name) + ".wav";

    HRESULT hr;

    // Waveファイルを開く
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        _TRACE_("失敗1");
        //return false;
    }

    // セカンダリ・バッファを作成する
    // DSBUFFERDESC構造体を設定
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS
            | DSBCAPS_LOCSOFTWARE; //DSBCAPS_LOCSOFTWAREを付け足した
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    //	LPDIRECTSOUND8 lpDS = c3dSound.GetDirectSound();
    //	if (lpDS == NULL) {
    //		return false;
    //	}
    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
        _TRACE_("失敗2");
        //return false;
    }

    // バッファを作る
    //	hr = lpDS->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, NULL);
    hr = GgafDx9Sound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, NULL);
    if (hr != D3D_OK) {
        _TRACE_("失敗3");
        //return false;
    }

    //m_strFilename = lpszFileName;
    //m_lpc3dSound = &c3dSound;
    //m_uiVolumeSettingID = uiVolumeSettingID;

    if (!writeBuffer(WaveFile)) {
        _TRACE_("失敗4");
        //Release();
        //return false;
    }

    // Soundへ登録する
    //	m_lpc3dSound->RegistSoundBuffer(this);

    //return true;

    //	GgafDx9Se3D* s = new GgafDx9Se3D();
    //	s->InitDxSound(GgafDx9God::_hWnd,1,22050,16);

    //	_pSoundSE = NEW CC3DSoundSE();
    //
    //	int ret = _pSoundSE->CreateSE( /* *(GgafDx9Sound::_pC3DSound),*/ wave_filename.c_str(), prm_iBufferCount, 0);
    //	if (!ret) {
    //		throwGgafCriticalException("GgafDx9Se::GgafDx9Se() Error! " << wave_filename << " の初期化に失敗");
    //	}
}
/**
 @brief		SEを鳴らす
 @param		lVolume		ボリューム(min:-9600 max:0)
 @param		lPan		パン(left:-10000 right:10000)
 @return		true:OK/false:NG
 */
void GgafDx9Se::act() {
    if (_pIDirectSoundBuffer == NULL) {
        _TRACE_("_pIDirectSoundBuffer==NULL;!");
    }
    DWORD dwStatus;

    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("失敗5");
        //return false;
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("失敗6");
            //return false;
        }
        if (!restore()) {
            _TRACE_("失敗7");
            //return false;
        }
    }

    //	_pIDirectSoundBuffer->SetVolume(m_lpc3dSound->GetVolume(m_uiVolumeSettingID, lVolume));
    _pIDirectSoundBuffer->SetVolume(0);
    //_pIDirectSoundBuffer->SetPan(lPan);
    _pIDirectSoundBuffer->SetPan(0);
    _pIDirectSoundBuffer->SetCurrentPosition(0);
    _pIDirectSoundBuffer->Play(0, 0, 0);

    //_pSoundSE->Play(0,0);
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

void GgafDx9Se::play(int prm_iVolume, int prm_iPan) {
    //_pSoundSE->Play(prm_iVolume, prm_iPan);
}

GgafDx9Se::~GgafDx9Se() {
    //	if (_pSoundSE != NULL) {
    //		_pSoundSE->Release();
    //		delete _pSoundSE;
    //		_pSoundSE = NULL;
    //	}
}
