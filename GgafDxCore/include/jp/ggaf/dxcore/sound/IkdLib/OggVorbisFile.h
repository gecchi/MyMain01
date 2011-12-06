// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムがオリジナルです。<BR>
// 一部変更して使用しています。<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

#ifndef IKD_DIX_OGGVORBISFILE_H
#define IKD_DIX_OGGVORBISFILE_H

namespace Dix {

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
    char _filepath[256];	// ファイル名
};

}

#endif
