#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace Dix;

// PCMPlayer.cpp
//
//#include "GgafDxCommonHeader.h"
//#include "PCMPlayer.h"
//#include <process.h>
//#include <stdio.h>

#ifdef _MSC_VER

#else
#define NULL 0
#endif

namespace {
double playTime_g = 1; // 1 sec.
}

//namespace Dix {
PCMPlayer::PCMPlayer() :
        _pDS8(NULL), _pDSBuffer(NULL), _pPCMDecoder(NULL), _wave_format(), _buffer_desc(), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8) :
        _pDS8(prm_pDS8), _pDSBuffer(NULL), _pPCMDecoder(NULL), _wave_format(), _buffer_desc(), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8, PCMDecoder* prm_pDecoder) :
        _pDS8(prm_pDS8), _pDSBuffer(NULL), _pPCMDecoder(NULL), _wave_format(), _buffer_desc(), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
    setDecoder(prm_pDecoder);
}

PCMPlayer::~PCMPlayer() {
    //正しく解放されない場合の原因究明のため、
    //スマートポインタを外してdeleteとReleaseで解放
    _TRACE_("PCMPlayer::~PCMPlayer() begin");
    _TRACE_("terminateThread();");
    terminateThread();
    _TRACE_("RELEASE_IMPOSSIBLE_NULL(_pDSBuffer);");
    RELEASE_IMPOSSIBLE_NULL(_pDSBuffer);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pPCMDecoder);");
    DELETE_IMPOSSIBLE_NULL(_pPCMDecoder);
    _TRACE_("PCMPlayer::~PCMPlayer() end");
}

//! クリア
void PCMPlayer::clear() {
    terminateThread();
    memset(&_buffer_desc, 0, sizeof(_buffer_desc));
    memset(&_wave_format, 0, sizeof(_wave_format));
    if (_pDSBuffer) {
        RELEASE_IMPOSSIBLE_NULL(_pDSBuffer);
        _pDSBuffer = NULL;
    }
    _is_ready = false;
    _state = STATE_NONE;
}

//! 再生中のスレッドを停止
void PCMPlayer::terminateThread() {
    if (_hnd_thread != 0) {
        _is_terminate = true;
        bool end = false;
        int wait = 0;
        while (!end) {
            if (wait > 10 * 100) {
                //1秒待っても駄目な場合は警告を出して強制終了
                _TRACE_("＜警告＞ PCMPlayer::terminateThread() 失敗しました。原因不明。頻発する場合は調査が必要！！");
                break;
            }
            DWORD flag = WaitForSingleObject((HANDLE)(__int64 )_hnd_thread, 10);
            switch (flag) {
                case WAIT_OBJECT_0:
                    // スレッドが終わった
                    end = true;
                    break;
                case WAIT_TIMEOUT:
                    wait++;
                    _is_terminate = true;
                    // まだ終了していないので待機
                    break;
                case WAIT_FAILED:
                    // 失敗しているようです
                    end = true;
                    break;
            }
            //Sleep(1);
        }
        _is_terminate = false;
        _hnd_thread = 0;
    } else {
        _TRACE_("PCMPlayer::terminateThread() スレッドはありません。多分。this=" << this << "/_is_terminate=" << _is_terminate);
    }
}

//! デバイス設定
void PCMPlayer::setDevice(IDirectSound8* prm_pDS8) {
    _pDS8 = prm_pDS8;
}

//! PCMデコーダを設定
bool PCMPlayer::setDecoder(PCMDecoder* prm_pPcmDecoder) {
    if (_pDS8 == NULL || prm_pPcmDecoder == NULL || prm_pPcmDecoder->isReady() == false) {
        _is_ready = false;
        return false;
    }

    _state = STATE_STOP;

    if (!prm_pPcmDecoder->getWaveFormatEx(_wave_format)) {
        return false;
    }

    _buffer_desc.dwSize = sizeof(DSBUFFERDESC);
    _buffer_desc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
    _buffer_desc.dwBufferBytes = _wave_format.nAvgBytesPerSec * playTime_g;
    _buffer_desc.dwReserved = 0;
    _buffer_desc.lpwfxFormat = &_wave_format;
    _buffer_desc.guid3DAlgorithm = GUID_NULL;

    // クローンを保存
    _pPCMDecoder = prm_pPcmDecoder->createClone();

    // セカンダリバッファがまだ無い場合は作成
    if (_pDSBuffer == NULL) {
        IDirectSoundBuffer* ptmpBuf = 0;
        if (SUCCEEDED(_pDS8->CreateSoundBuffer(&_buffer_desc, &ptmpBuf, NULL))) {
            ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&_pDSBuffer);
        } else {
            clear();
            return false;
        }
        ptmpBuf->Release();
    }

    // バッファを初期化
    //内部のpDSBuffer->Lock で極稀におちる。
    //→initializeBuffer() と再生を排他すればよさそうというような記事が○×掲示板に投稿されていた.
// ___BeginSynchronized02;
    bool r = initializeBuffer();
// ___EndSynchronized02;
    if (r == false) {
        return false;
    }

    // バッファコピースレッド生成
    if (_hnd_thread == 0) {
        _hnd_thread = (unsigned int)_beginthread(PCMPlayer::streamThread, 0, (void*)this);
    }

    _is_ready = true;

    return true;
}

//! バッファを初期化する
bool PCMPlayer::initializeBuffer() {
    if (_pPCMDecoder == NULL) {
        return false;
    }

    _pPCMDecoder->setHead(); // 頭出し
    HRESULT hr = _pDSBuffer->SetCurrentPosition(0);
    checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer()  SetCurrentPosition( 0 ) に失敗しました。");
    // バッファをロックして初期データ書き込み
    for (int i = 0; i < 10; i++) { //最大１０回試行してみる。苦肉の策。
                                   //これは DSBLOCK_ENTIREBUFFER （全体ロック)が
                                   //仕組上特定のタイミングで失敗することは避けれないと考えたため。
                                   //TODO:はたしてこんな方法でいいのだろうか。
                                   //TODO:極極稀に落ちるのはなぜか？。環境依存なのか？完全に納得していない。

        void* AP1 = 0, *AP2 = 0;
        DWORD AB1 = 0, AB2 = 0;
        hr = _pDSBuffer->Lock(0, 0, &AP1, &AB1, &AP2, &AB2, DSBLOCK_ENTIREBUFFER);
        //checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer() Lock に失敗しました。");
        //↑ロック失敗している場合がある。仕方ないのでエラーチェックはコメントにする。
        //  起こった場合、メモリリークしていた。２ヶ月ぐらい悩んだが放置。
        if (SUCCEEDED(hr)) {
            _pPCMDecoder->getSegment((char*)AP1, AB1, 0, 0);
            hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
            checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer() Unlock に失敗しました。");
            break;
        } else {
            //ロック失敗時
            if (i < 10) {
                _TRACE_("PCMPlayer::initializeBuffer() Lockに失敗 i=" << i << " ");
                _TRACE_("hr=" << hr << " " << DXGetErrorString(hr) << " " << DXGetErrorDescription(hr));
                hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                Sleep(5);
                continue; //もう一回頑張る
            } else {
                //あきらめる
                _TRACE_("PCMPlayer::initializeBuffer() もうLockをあきらめて解放します。ごめんなさい；");
                clear();
                return false;
            }
        }
    }
    return true;
}

//! ストリーム再生スレッド生成
void PCMPlayer::streamThread(void* playerPtr) {
    PCMPlayer* player = (PCMPlayer*)playerPtr;
    unsigned int size = player->_buffer_desc.dwBufferBytes / 2;
    unsigned int flag = 0;
    DWORD point = 0;
    void* AP1 = 0, *AP2 = 0;
    DWORD AB1 = 0, AB2 = 0;

    DWORD finishPos = 0;
    DWORD prePlayPos = 0;

    unsigned int writeSize = 0;
    bool isEnd = false;
    bool waitFinish = false;

    while (player->_is_terminate == false) {
        switch (player->getState()) {
            case STATE_PLAY: // 再生中
                // ストリーム再生
                // 現在位置をチェック
//             ___BeginSynchronized02;
                player->_pDSBuffer->GetCurrentPosition(&point, 0);
                if (flag == 0 && point >= size) {
                    // 前半に書き込み
                    if (SUCCEEDED(player->_pDSBuffer->Lock(0, size, &AP1, &AB1, &AP2, &AB2, 0))) {
                        player->_pPCMDecoder->getSegment((char*)AP1, AB1, &writeSize, &isEnd);
                        player->_pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                        flag = 1;
                    }

                    // 最終書き込みの場合は終了位置を特定
                    if (isEnd == true && waitFinish == false) {
                        finishPos = writeSize;
                        player->_pDSBuffer->GetCurrentPosition(&prePlayPos, 0);
                        waitFinish = true;
                    }
                } else if (flag == 1 && point < size) {
                    // 後半に書き込み
                    if (SUCCEEDED(player->_pDSBuffer->Lock(size, size * 2, &AP1, &AB1, &AP2, &AB2, 0))) {
                        player->_pPCMDecoder->getSegment((char*)AP1, AB1, &writeSize, &isEnd);
                        player->_pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                        flag = 0;
                    }

                    // 最終書き込みの場合はNorifyを設定
                    if (isEnd == true && waitFinish == false) {
                        finishPos = size + writeSize;
                        player->_pDSBuffer->GetCurrentPosition(&prePlayPos, 0);
                        waitFinish = true;
                    }
                }
//             ___EndSynchronized02;
                break;

            case STATE_STOP:
                flag = 0; // 止めると前半書き込みから始まるため
                isEnd = false;
                finishPos = 0;
                prePlayPos = 0;
                break;

            case STATE_PAUSE:
                break;

            default:
                break;
        }

        // 終了位置判定チェック
        if (isEnd == true) {
            DWORD curPlayPos;
            player->_pDSBuffer->GetCurrentPosition(&curPlayPos, 0);
            if (curPlayPos < prePlayPos) {
                // バッファをループした瞬間
                //if ( prePlayPos <= finishPos ) {
                if (prePlayPos <= finishPos || finishPos <= curPlayPos) {
                    // 終了宣言
                    player->stop();
                }
            } else {
                if (prePlayPos <= finishPos && finishPos <= curPlayPos) {
                    // 終了宣言
                    player->stop();
                }
            }
            prePlayPos = curPlayPos;
        }

        Sleep(100);
    }
}

//! 再生
bool PCMPlayer::play(bool prm_is_looping) {
    if (isReady() == false) {
        return false;
    }
    _is_looping = prm_is_looping;
    _pPCMDecoder->setLooping(_is_looping);
    _pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
    _state = STATE_PLAY;
    return true;
}

//! 一時停止
void PCMPlayer::pause() {
    if (_state == STATE_PLAY) {
        // 動いていたら止める
        _pDSBuffer->Stop();
        _state = STATE_PAUSE;
    } else {
        // 止まっていたら再生
        play(_is_looping);
    }
}

//! 停止
void PCMPlayer::stop() {
    if (isReady() == false) {
        return;
    }
    _state = STATE_STOP;
    _pDSBuffer->Stop();

    // バッファの頭出し
//    ___BeginSynchronized02;
    bool r = initializeBuffer();
//    ___EndSynchronized02;
    _TRACE_("PCMPlayer::stop() initializeBuffer() = " << r);
}

//! 音量を変える
void PCMPlayer::setVolume(int volume) {
    if (isReady() == true) {
        _pDSBuffer->SetVolume(volume);
    }
}

//! パンの位置を変える
void PCMPlayer::setPan(int pan) {
    if (isReady() == true) {
        _pDSBuffer->SetPan(pan);
    }
}

//! 準備できた？
bool PCMPlayer::isReady() {
    return _is_ready;
}

//! 再生中？
bool PCMPlayer::isPlaying() {
    return (_state == STATE_PLAY);
}

//! 状態を取得
PCMPlayer::STATE PCMPlayer::getState() {
    return _state;
}

//}
