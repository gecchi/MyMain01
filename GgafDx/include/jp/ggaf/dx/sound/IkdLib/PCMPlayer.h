#ifndef IKD_DIX_PCMPLAYER_H
#define IKD_DIX_PCMPLAYER_H
#include "jp/ggaf/GgafDxCommonHeader.h"
#include <sstream>

//#ifdef __GNUG__
//    #define __null
//    #define NULL    0
//    #define __in
//    #define __out
//#endif
//#include <dsound.h>  //←sal.h を include する
//#ifdef __GNUG__
//    #undef __null
//    #undef __in
//    #undef __out
//#endif

struct IDirectSound8;
struct IDirectSoundBuffer8;
typedef struct tWAVEFORMATEX WAVEFORMATEX;
typedef struct _DSBUFFERDESC DSBUFFERDESC;
typedef void *HANDLE;

namespace IkdLib {

/**
 * PCMPlayer .
 * 本プログラムは、<BR>
 * 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
 * サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
 * のサンプルプログラムがオリジナルです。<BR>
 * 変更して使用しています。<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class PCMPlayer {
public:
    // 再生状態
    enum STATE {
        STATE_NONE, STATE_PLAY, STATE_PAUSE, STATE_STOP
    };

public:
    PCMPlayer();
    PCMPlayer(IDirectSound8* prm_pDS8);
    PCMPlayer(IDirectSound8* prm_pDS8, PCMDecoder* prm_pDecoder);

    virtual ~PCMPlayer(); //virtual 追加

    //! デバイス設定
    void setDevice(IDirectSound8* prm_pDS8);

    //! PCMデコーダを設定
    bool setDecoder(PCMDecoder* prm_pPcmDecoder);
    //! 再生
    bool play(bool prm_is_looping);

    //! 一時停止
    void pause();
    void unpause();
    //! 停止
    void stop();

    //! 音量を変える(デシベル)
    void setVolume(int db);

    //! パンの位置を変える
    void setPan(int pan);

    //! クリア
    void clear();

    //! 状態取得
    STATE getState();

public:
    //! 再生中のスレッドを停止
    void terminateThread();

    //! 再生中のスレッドを停止
    void terminateThreadWait();

    //! バッファを初期化する
    bool initializeBuffer();

    //! バッファコピースレッド生成
//    static void __cdecl streamThread(void* player);
    static unsigned __stdcall streamThread(void* player);
    //! 準備できた？
    bool isReady();

    //! 再生中？
    bool isPlaying();

public:
    IDirectSound8* _pDS8; //!< サウンドデバイス
    IDirectSoundBuffer8* _pDSBuffer; //!< セカンダリバッファ
    PCMDecoder* _pPCMDecoder;
    WAVEFORMATEX* _pWaveFormat; //!< WAVEFORMATEX構造体
    DSBUFFERDESC* _pBufferDesc; //!< DSBUFFERDESC構造体
    bool _is_ready; //!< 準備できた？
    HANDLE _hnd_thread; //!< ストリーム再生スレッドハンドル
    bool _is_terminate; //!< スレッド停止
    bool _is_looping; //!< ループする？
    STATE _state; //!< 再生状態
};
}

#endif
