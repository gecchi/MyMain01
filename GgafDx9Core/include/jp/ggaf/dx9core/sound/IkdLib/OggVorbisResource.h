// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムのがオリジナルです。<BR>
// 一部変更して使用しています。<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

// OggVorbisResource.h
//

#ifndef IKD_DIX_OGGVORBISRESOURCE_H
#define IKD_DIX_OGGVORBISRESOURCE_H

#include "vorbis/vorbisfile.h"

namespace Dix {
    class OggVorbisResource {
    public:
        OggVorbisResource() : isReady_( false ){
            memset( &oggVorbisFile_, 0, sizeof( OggVorbis_File ) );
        }

        virtual ~OggVorbisResource(){
            clear();
        }

        // クリア
        virtual void clear() {
            ov_clear( &oggVorbisFile_ );
            memset( &oggVorbisFile_, 0, sizeof( OggVorbis_File ) );
            isReady_ = false;
        }

        // OggVorbis_File構造体を取得
        virtual OggVorbis_File& getOggVorbisFile() {
            return oggVorbisFile_;
        }

        // 安全なクローンを作成
        virtual OggVorbisResource* createClone() = 0;

        // 準備できた？
        bool isReady() {
            return isReady_;
        }

    protected:
        OggVorbis_File	oggVorbisFile_;	// OggVorbis_File構造体
        bool			isReady_;		// 準備できた？
    };
}

#endif
