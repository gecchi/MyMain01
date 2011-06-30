// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムがオリジナルです。<BR>
// 一部変更して使用しています。<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>


#ifndef IKD_DIX_OGGVORBISMEMORY_H
#define IKD_DIX_OGGVORBISMEMORY_H

namespace Dix {
    class OggVorbisMemory : public OggVorbisResource {
    public:
        OggVorbisMemory();
        OggVorbisMemory( const char* filePath );
        virtual ~OggVorbisMemory();

        //! Oggバッファを作成
        bool createBuffer( const char* filePath );

        virtual OggVorbisResource* createClone();

        //! クリア
        virtual void clear();

    protected:
        //! メモリ読み込み
        static size_t read( void* buffer, size_t size, size_t maxCount, void* stream );

        //! メモリシーク
        static int seek( void* buffer, ogg_int64_t offset, int flag );

        //! メモリクローズ
        static int close( void* buffer );

        //! メモリ位置通達
        static long tell( void* buffer );

    protected:
        char		filePath_[ 256 ];	// ファイルパス
        char*       pBuffer_;          // Oggファイルバッファ
        int			size_;				// バッファサイズ
        long		curPos_;			// 現在の位置
    };
}

#endif
