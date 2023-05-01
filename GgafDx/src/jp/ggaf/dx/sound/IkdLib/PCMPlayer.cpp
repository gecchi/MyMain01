// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムがオリジナルです。<BR>
// 一部変更して使用しています。<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

#include "jp/ggaf/dx/sound/IkdLib/PCMPlayer.h"

#include <process.h>
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/sound/IkdLib/PCMDecoder.h"
#include "jp/ggaf/dx/Caretaker.h"

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

using namespace IkdLib;

namespace {
//double playTime_g = 1; // 1 sec.
double playTime_g = 0.5; // 1 sec.
}

PCMPlayer::PCMPlayer() :
        _pDS8(nullptr), _pDSBuffer(nullptr), _pPCMDecoder(nullptr), _pWaveFormat(NEW WAVEFORMATEX), _pBufferDesc(NEW DSBUFFERDESC), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8) :
        _pDS8(prm_pDS8), _pDSBuffer(nullptr), _pPCMDecoder(nullptr), _pWaveFormat(NEW WAVEFORMATEX), _pBufferDesc(NEW DSBUFFERDESC), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8, PCMDecoder* prm_pDecoder) :
        _pDS8(prm_pDS8), _pDSBuffer(nullptr), _pPCMDecoder(nullptr), _pWaveFormat(NEW WAVEFORMATEX), _pBufferDesc(NEW DSBUFFERDESC), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
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
    GGAF_DELETE(_pWaveFormat);
    GGAF_DELETE(_pBufferDesc);

    _TRACE_("GGAF_RELEASE(_pDSBuffer);");
    GGAF_RELEASE(_pDSBuffer);
    _TRACE_("GGAF_DELETE(_pPCMDecoder);");
    GGAF_DELETE(_pPCMDecoder);
    _TRACE_("PCMPlayer::~PCMPlayer() end");
}

//! クリア
void PCMPlayer::clear() {
    terminateThread();
    memset(_pBufferDesc, 0, sizeof(DSBUFFERDESC));
    memset(_pWaveFormat, 0, sizeof(WAVEFORMATEX));
    if (_pDSBuffer) {
        GGAF_RELEASE(_pDSBuffer);
        _pDSBuffer = nullptr;
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
            //if (wait > 1) {
            if (wait > 10000) {
                _TRACE_("【警告】 PCMPlayer::terminateThread() 未完。正しくスレッドが終了することを願ってBREAK (T_T)");
                break;
            }
            DWORD flag = WaitForSingleObject(_hnd_thread, 4);
            switch (flag) {
                case WAIT_OBJECT_0:
                    // スレッドが終わった
                    end = true;
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=WAIT_OBJECT_0 OK!Done! flag="<<flag<<" wait="<<wait<<"");
                    break;
                case WAIT_TIMEOUT:
                    wait++;
                    _is_terminate = true;
                    // まだ終了していないので待機
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=WAIT_TIMEOUT... flag="<<flag<<" wait="<<wait<<"");
                    break;
                case WAIT_FAILED:
                    // 失敗しているようです
                    end = true;
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=WAIT_FAILED... flag="<<flag<<" wait="<<wait<<"");
                    break;
                default:
                    wait++;
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=?  flag="<<flag<<" wait="<<wait<<"");
                    break;
            }
            if (!end) {
                Sleep(2);
            }
        }
        _is_terminate = false;
        CloseHandle(_hnd_thread);
        _hnd_thread = 0;
    } else {
        _TRACE_(FUNC_NAME<<" 以前に既に実行済み。多分。this=" << this << "/_is_terminate=" << _is_terminate);
    }
}

//! デバイス設定
void PCMPlayer::setDevice(IDirectSound8* prm_pDS8) {
    _pDS8 = prm_pDS8;
}

//! PCMデコーダを設定
bool PCMPlayer::setDecoder(PCMDecoder* prm_pPcmDecoder) {
    if (_pDS8 == nullptr || prm_pPcmDecoder == nullptr || prm_pPcmDecoder->isReady() == false) {
        _is_ready = false;
        return false;
    }

    _state = STATE_STOP;

    if (!prm_pPcmDecoder->getWaveFormatEx(_pWaveFormat)) {
        return false;
    }
    _pBufferDesc->dwSize = sizeof(DSBUFFERDESC);
    _pBufferDesc->dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
    _pBufferDesc->dwBufferBytes = _pWaveFormat->nAvgBytesPerSec * playTime_g;
    _pBufferDesc->dwReserved = 0;
    _pBufferDesc->lpwfxFormat = _pWaveFormat;
    _pBufferDesc->guid3DAlgorithm = GUID_NULL;

    // クローンを保存
    _pPCMDecoder = prm_pPcmDecoder->createClone();

    // セカンダリバッファがまだ無い場合は作成
    if (_pDSBuffer == nullptr) {
        IDirectSoundBuffer* ptmpBuf = 0;
        if (SUCCEEDED(_pDS8->CreateSoundBuffer(_pBufferDesc, &ptmpBuf, nullptr))) {
            ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&_pDSBuffer);
        } else {
            clear();
            return false;
        }
        ptmpBuf->Release();
    }

    // バッファを初期化
    //内部のpDSBuffer->Lock で極稀におちる。
    //→initializeBuffer() と再生を排他すればよさそう
    bool r = initializeBuffer();
    if (r == false) {
        return false;
    }

    // バッファコピースレッド生成
    if (_hnd_thread == 0) {
        //_hnd_thread = (uintptr_t)_beginthread(PCMPlayer::streamThread, 0, (void*)this);
        _hnd_thread = (HANDLE)_beginthreadex(nullptr, 0, IkdLib::PCMPlayer::streamThread, (void*)this, 0, nullptr);
    }

    _is_ready = true;

    return true;
}

//! バッファを初期化する
bool PCMPlayer::initializeBuffer() {
    if (_pPCMDecoder == nullptr) {
        return false;
    }
    BEGIN_SYNCHRONIZED2; //これが効いてる
    _pPCMDecoder->setHead(); // 頭出し
    HRESULT hr = _pDSBuffer->SetCurrentPosition(0);
    checkDxException(hr, DS_OK, " SetCurrentPosition( 0 ) に失敗しました。");
    // バッファをロックして初期データ書き込み
    for (int i = 0; i < 10; i++) { //最大１０回試行してみる。苦肉の策。
                                   //これは DSBLOCK_ENTIREBUFFER （全体ロック)が
                                   //仕組上特定のタイミングで失敗することは避けれないと考えたため。
                                   //TODO:はたしてこんな方法でいいのだろうか。


        void* AP1 = 0, *AP2 = 0;
        DWORD AB1 = 0, AB2 = 0;
        hr = _pDSBuffer->Lock(0, 0, &AP1, &AB1, &AP2, &AB2, DSBLOCK_ENTIREBUFFER);
        //checkDxException(hr, DS_OK, "Lock に失敗しました。");
        //↑TODO:ロック失敗している場合がある。仕方ないのでエラーチェックはコメントにする。
        //  起こった場合、メモリリークしているっぽい。長い期間悩んだが放置・・。
        //クリティカルセクション   BEGIN_SYNCHRONIZED2 ～    END_SYNCHRONIZED2 で挟むようにしてみた。
        //追記：クリティカルセクションで囲むように修正してから、長い期間安定している。

        if (SUCCEEDED(hr)) {
            _pPCMDecoder->getSegment((char*)AP1, AB1, 0, 0); //← ココでも極稀に落ちる！昔は。（今は長い期間安定している）
            hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
            checkDxException(hr, DS_OK, "Unlock に失敗しました。");
            break;
        } else {
            //ロック失敗時
            if (i < 10) {
                _TRACE_(FUNC_NAME<<" Lockに失敗 i=" << i << " ");
//                _TRACE_("hr=" << hr << " " << DXGetErrorString(hr) << " " << DXGetErrorDescription(hr));
                _TRACE_("HRESULT="<<hr);
                hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                Sleep(5);
                continue; //もう一回頑張る
            } else {
                //あきらめる
                _TRACE_(FUNC_NAME<<" もうLockをあきらめて解放します。いいんかそれで");
                clear();
                END_SYNCHRONIZED2;
                return false;
            }
        }
    }
    END_SYNCHRONIZED2;
    return true;
}

//! ストリーム再生スレッド生成
unsigned __stdcall PCMPlayer::streamThread(void* playerPtr) {
    PCMPlayer* player = (PCMPlayer*)playerPtr;
    unsigned int size = player->_pBufferDesc->dwBufferBytes / 2;
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
        if (pCARETAKER->_sync_frame_time || pCARETAKER->_is_device_lost_flg) {
            _TRACE_("PCMPlayer::streamThread() 演奏停止中・・・");
            Sleep(100);
            continue;
        }

        BEGIN_SYNCHRONIZED2;
        switch (player->getState()) {
            case STATE_PLAY: // 再生中
                // ストリーム再生
                // 現在位置をチェック
                player->_pDSBuffer->GetCurrentPosition(&point, 0);
                if (flag == 0 && point >= size) {
                    // 前半に書き込み
                    if (SUCCEEDED(player->_pDSBuffer->Lock(0, size, &AP1, &AB1, &AP2, &AB2, 0))) {
                        player->_pPCMDecoder->getSegment((char*)AP1, AB1, &writeSize, &isEnd);
                        player->_pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                        flag = 1;
                    }

                    // 最終書き込みの場合は終了位置を特定
                    if (isEnd && waitFinish == false) {
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
                    if (isEnd && waitFinish == false) {
                        finishPos = size + writeSize;
                        player->_pDSBuffer->GetCurrentPosition(&prePlayPos, 0);
                        waitFinish = true;
                    }
                }
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
        END_SYNCHRONIZED2;

        // 終了位置判定チェック
        if (isEnd) {
            DWORD curPlayPos;
            HRESULT hr = player->_pDSBuffer->GetCurrentPosition(&curPlayPos, 0);
            checkDxException(hr, DS_OK, "GetCurrentPosition に失敗しました。");
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

    return 0;
}

//! 再生
bool PCMPlayer::play(bool prm_is_looping) {
    if (isReady() == false) {
        return false;
    }
    _is_looping = prm_is_looping;
    _pPCMDecoder->setLooping(_is_looping);
    HRESULT hr = _pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
    checkDxException(hr, DS_OK, "失敗しました。 prm_is_looping="<<prm_is_looping);
    _state = STATE_PLAY;
    return true;
}

//! 一時停止
void PCMPlayer::pause() {
    if (_state == STATE_PLAY) {
        // 動いていたら止める
        HRESULT hr = _pDSBuffer->Stop();
        checkDxException(hr, DS_OK, "失敗しました。");
        _state = STATE_PAUSE;
    } else if (_state == STATE_PAUSE) {
        //PAUSE中にpause()しても無視
    } else if (_state == STATE_STOP) {
        //停止中にpause()しても無視
    }
}
void PCMPlayer::unpause() {
    if (_state == STATE_PLAY) {
        //演奏中に unpause() しても無視
    } else if (_state == STATE_PAUSE) {
        // PAUSE中なら再生
        _state = STATE_PLAY;
        play(_is_looping);
    } else if (_state == STATE_STOP) {
        //停止中にunpause()しても無視
    }
}

//! 停止
void PCMPlayer::stop() {
    if (isReady() == false) {
        return;
    }
    _state = STATE_STOP;
    HRESULT hr = _pDSBuffer->Stop();
    checkDxException(hr, DS_OK, "失敗しました。");
    // バッファの頭出し
    bool r = initializeBuffer();
    _TRACE_(FUNC_NAME<<" initializeBuffer() = " << r);
}

//! 音量を変える
void PCMPlayer::setVolume(int db) {
    if (isReady()) {
        HRESULT hr = _pDSBuffer->SetVolume(db);
        checkDxException(hr, DS_OK, "失敗しました。 db="<<db);
    }
}

//! パンの位置を変える
void PCMPlayer::setPan(int pan) {
    if (isReady()) {
        HRESULT hr = _pDSBuffer->SetPan(pan);
        checkDxException(hr, DS_OK, "失敗しました。pan="<<pan);
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
