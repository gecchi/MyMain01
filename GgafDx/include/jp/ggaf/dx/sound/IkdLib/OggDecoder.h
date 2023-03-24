#ifndef IKD_DIX_OGGDECODER_H
#define IKD_DIX_OGGDECODER_H
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/sound/IkdLib/PCMDecoder.h"

#define OV_EXCLUDE_STATIC_CALLBACKS
#include "vorbis/vorbisfile.h"

namespace IkdLib {

/**
 * OggDecoder .
 * 本プログラムは、<BR>
 * 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
 * サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
 * のサンプルプログラムがオリジナルです。<BR>
 * 変更して使用しています。<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class OggDecoder : public PCMDecoder {

public:
    OggDecoder();
    OggDecoder(OggVorbisResource* prm_pOggVorbisResource);
    virtual ~OggDecoder();

    //! クリア
    virtual void clear();
    //! セグメント取得
    virtual bool getSegment(char* prm_buffer, unsigned int prm_size, unsigned int* pUInt_write_size, bool* pBool_is_end);
    //! 頭出し
    virtual void setHead();
    //! クローンを生成
    virtual PCMDecoder* createClone();
    //! サウンドをセット
    virtual bool setResource(OggVorbisResource* pOggVorbisResource);

protected:
    OggVorbisResource* _pOggVorbisResource;
};

}

#endif
