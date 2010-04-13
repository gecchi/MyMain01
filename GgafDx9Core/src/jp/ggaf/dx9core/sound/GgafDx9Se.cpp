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

void GgafDx9Se::play(GgafDx9GeometricActor* prm_pActor) {
//    /** [r]視錐台上面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
//    FLOAT _fDist_VpPlnTop;
//    /** [r]視錐台下面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
//    FLOAT _fDist_VpPlnBottom;
//    /** [r]視錐台左面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
//    FLOAT _fDist_VpPlnLeft;
//    /** [r]視錐台右面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
//    FLOAT _fDist_VpPlnRight;
//    /** [r]視錐台手前面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
//    FLOAT _fDist_VpPlnFront;
//    /** [r]視錐台奥面から視野外に向かっての自身の座標までのDirectXの距離、視野内の距離は負の値になる */
//    FLOAT _fDist_VpPlnBack;
//#define DSBPAN_LEFT                 -10000
//#define DSBPAN_CENTER               0
//#define DSBPAN_RIGHT                10000
//
//#define DSBVOLUME_MIN               -10000
//#define DSBVOLUME_MAX               0
//    int GgafDx9Sound::_master_volume = 100;
//    int GgafDx9Sound::_bgm_volume = 100;
//    int GgafDx9Sound::_se_volume = 100;

//    /** カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0 */
//    float _zn;
//    /** カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn  */
//    float _zf;

//    まず、同じバッファの音が同時再生できなかった問題は、DuplicateSoundBuffer()関数を使ってバッファの外枠のみのコピーを作っておくことで解決です。例えば、これで8個作っておくと同じバッファの音が8個まで同時再生できます。
//    ただ、小さな破片は1秒間に数百個も爆発したりするので、さすがに100個くらい同時再生しようとすると音が途切れます…。
//
//    後は、再生直前に
//
//        lpDSBuf->SetVolume(LONG); //音量設定 減衰するdb 0～-10000
//        lpDSBuf->SetPan(LONG); //パン設定 -10000～+10000
//        lpDSBuf->SetFrequency(DWORD); //再生周波数設定
//
//    _dwDefaultFrequency
//    こういう設定が出来ることが分かりました。最後の再生周波数設定は、例えばサンプリングレート44.1KHzのバッファの場合はここへ44100を指定すると通常通りの再生になり、22050を指定すると半分の速度（音程も半分）で再生されるという具合です。
//    これ、敵の爆破した位置に合わせて設定してやるとすごく立体的でリアル。とくに、遠くの爆発は再生周波数下げるようにすると、爆発音がくぐもった音になってまるで映画みたい。最初は遊び心でいじってたけど、ここまで上手くハマるとは思わなかったな。
//
//    ただ、注意点もあって、バッファ初期化時にDSBUFFERDESC構造体の設定で、
//
//        DSBufferDesc.dwFlags = DSBCAPS_LOCDEFER | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;
//
//    のようなフラグを設定して、各パラメータをコントロールすることを伝えておく必要がある。MSDN見ても、SetVolume()の解説のところなんかにこのフラグの事が書いて無くて、しばらくネットを探し回ってしまった。あと、SetVolumeの値もMSDNだと正の値だと書いてあるけど、実際は負の値を入れないといけない。MSDNってどっか抜けてる…？？


}
/**
 @brief		SEを鳴らす
 @param		prm_iVolume		ボリューム(min:-9600 max:0)
 @param		prm_iPan		パン(left:-10000 right:10000)
 */
void GgafDx9Se::play(int prm_iVolume, int prm_iPan) {
    if (_pIDirectSoundBuffer == NULL) {
        _TRACE_("_pIDirectSoundBuffer==NULL;!");
    }
    DWORD dwStatus;

    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("GgafDx9Se::play() GetStatus() 失敗");
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("GgafDx9Se::play() Restore() 失敗");
        }
        if (!restore()) {
            _TRACE_("GgafDx9Se::play() restore() 失敗");
        }
    }
    //マスターボリュームTODO
    //_pIDirectSoundBuffer->SetVolume(GgafDx9Sound::_master_volume と prm_iVolumeで計算));

    _pIDirectSoundBuffer->SetVolume(prm_iVolume);
    _pIDirectSoundBuffer->SetPan(prm_iPan);
    _pIDirectSoundBuffer->SetCurrentPosition(0); //バッファ頭だし
    _pIDirectSoundBuffer->Play(0, 0, 0x00000000);

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



GgafDx9Se::~GgafDx9Se() {
    //	if (_pSoundSE != NULL) {
    //		_pSoundSE->Release();
    //		delete _pSoundSE;
    //		_pSoundSE = NULL;
    //	}
}
