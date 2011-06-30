// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムがオリジナルです。<BR>
// 一部変更して使用しています。<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

#ifndef IKD_DIX_OGGDECODER_H
#define IKD_DIX_OGGDECODER_H

#include "vorbis/vorbisfile.h"

namespace Dix {
    class OggDecoder : public PCMDecoder {
    public:
        OggDecoder();
        OggDecoder(OggVorbisResource* pOggVorbisResource );
        virtual ~OggDecoder();

        //! クリア
        virtual void clear();

        //! セグメント取得
        virtual bool getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd );

        //! 頭出し
        virtual void setHead();

        //! クローンを生成
        virtual PCMDecoder* createClone();

        //! サウンドをセット
        virtual bool setResource(OggVorbisResource* pOggVorbisResource );

    protected:
        OggVorbisResource* pOggVorbisResource_;
    };
}

#endif
