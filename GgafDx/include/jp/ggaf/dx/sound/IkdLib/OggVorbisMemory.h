#ifndef IKD_DIX_OGGVORBISMEMORY_H
#define IKD_DIX_OGGVORBISMEMORY_H
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/sound/IkdLib/OggVorbisResource.h"

namespace IkdLib {

/**
 * OggVorbisMemory .
 * 本プログラムは、<BR>
 * 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
 * サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
 * のサンプルプログラムがオリジナルです。<BR>
 * 変更して使用しています。<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class OggVorbisMemory : public OggVorbisResource {
public:
    OggVorbisMemory();
    OggVorbisMemory(const char* prm_filepath);
    virtual ~OggVorbisMemory();

    //! Oggバッファを作成
    bool createBuffer(const char* prm_filepath);

    virtual OggVorbisResource* createClone();

    //! クリア
    virtual void clear();

protected:
    //! メモリ読み込み
    static size_t read(void* prm_buffer, size_t prm_size, size_t prm_max_count, void* prm_stream);

    //! メモリシーク
    static int seek(void* prm_buffer, ogg_int64_t offset, int flag);

    //! メモリクローズ
    static int close(void* prm_buffer);

    //! メモリ位置通達
    static long tell(void* prm_buffer);

protected:
    char _filepath[256]; // ファイルパス
    char* _buffer; // Oggファイルバッファ
    int _size; // バッファサイズ
    long _pos_current; // 現在の位置
};

}

#endif
