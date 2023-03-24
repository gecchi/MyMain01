#ifndef IKD_DIX_PCMDECODER_H
#define IKD_DIX_PCMDECODER_H
#include "jp/ggaf/GgafDxCommonHeader.h"
#include <windows.h>

namespace IkdLib {

/**
 * PCMDecoder .
 * 本プログラムは、<BR>
 * 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
 * サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
 * のサンプルプログラムがオリジナルです。<BR>
 * 変更して使用しています。<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class PCMDecoder {
public:
    //! コンストラクタ
    PCMDecoder();

    //! デストラクタ
    virtual ~PCMDecoder();

    //! セグメント取得
    virtual bool getSegment(char* prm_buffer,
                            unsigned int prm_size,
                            unsigned int* pUInt_write_size,
                            bool* pBool_is_end) = 0;

    //! 頭出し
    virtual void setHead() = 0;

    //! 安全なクローンを生成
    virtual PCMDecoder* createClone() = 0;

public:
    //! クリア
    virtual void clear();

    //! ループフラグ取得
    bool isLooping();

    //! 準備できた？
    bool isReady();

    //! ループを設定
    void setLooping(bool prm_is_looping);

    //! WAVEFORMATEX構造体を取得
    bool getWaveFormatEx(WAVEFORMATEX* out_waveFormatEx);

protected:
    //! 準備フラグ設定
    void setReady(bool prm_is_ready);

    //! チャンネル数設定
    void setChannelNum(unsigned int prm_num_channel);

    //! サンプリングレートを設定
    void setSamplingRate(unsigned int prm_sampling_rate);

    //! ビットレートを設定
    void setBitRate(unsigned int prm_bit_rate);

protected:
    bool _is_looping; //!< ループする？
    bool _is_ready; //!< 準備できた？
    unsigned int _num_channel; //!< チャンネル数
    unsigned int _sampling_rate; //!< サンプリングレート
    unsigned int _bit_rate; //!< ビットレート
};
}

#endif
