#ifndef IKD_DIX_OGGVORBISRESOURCE_H
#define IKD_DIX_OGGVORBISRESOURCE_H
#include "jp/ggaf/GgafDxCommonHeader.h"

#define OV_EXCLUDE_STATIC_CALLBACKS

#include <string.h>
#include "vorbis/vorbisfile.h"

namespace IkdLib {

/**
 * OggVorbisResource .
 * 本プログラムは、<BR>
 * 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
 * サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
 * のサンプルプログラムがオリジナルです。<BR>
 * 変更して使用しています。<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class OggVorbisResource {
public:
    OggVorbisResource() :
            _is_ready(false) {
        memset(&_ogg_vorbis_file, 0, sizeof(OggVorbis_File));
    }

    virtual ~OggVorbisResource() {
        clear();
    }

    // クリア
    virtual void clear() {
        ov_clear(&_ogg_vorbis_file);
        memset(&_ogg_vorbis_file, 0, sizeof(OggVorbis_File));
        _is_ready = false;
    }

    // OggVorbis_File構造体を取得
    virtual OggVorbis_File& getOggVorbisFile() {
        return _ogg_vorbis_file;
    }

    // 安全なクローンを作成
    virtual OggVorbisResource* createClone() = 0;

    // 準備できた？
    bool isReady() {
        return _is_ready;
    }

protected:
    OggVorbis_File _ogg_vorbis_file; // OggVorbis_File構造体
    bool _is_ready; // 準備できた？
};
}

#endif
