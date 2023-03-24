#ifndef IKD_DIX_OGGVORBISFILE_H
#define IKD_DIX_OGGVORBISFILE_H
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/sound/IkdLib/OggVorbisResource.h"

namespace IkdLib {

/**
 * OggVorbisFile .
 * 本プログラムは、<BR>
 * 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
 * サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
 * のサンプルプログラムがオリジナルです。<BR>
 * 変更して使用しています。<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class OggVorbisFile : public OggVorbisResource {
public:
    OggVorbisFile();
    OggVorbisFile(const char* filePath);

    virtual ~OggVorbisFile();

    //! クリア
    virtual void clear();

    //! 安全なクローンを作成
    virtual OggVorbisResource* createClone();

    //! Oggファイルオープン
    bool open(const char* filePath);

protected:
    char _filepath[1024];	// ファイル名
};

}

#endif
