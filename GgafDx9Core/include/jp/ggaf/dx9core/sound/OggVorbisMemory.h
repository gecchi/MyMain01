// OggVorbisMemory.h
//

#ifndef IKD_DIX_OGGVORBISMEMORY_H
#define IKD_DIX_OGGVORBISMEMORY_H

//#include "OggVorbisResource.h"

namespace Dix {
	class OggVorbisMemory : public OggVorbisResource {
	public:
		OggVorbisMemory();
		OggVorbisMemory( const char* filePath );
		virtual ~OggVorbisMemory();

		//! Oggバッファを作成
		bool createBuffer( const char* filePath );

		// 安全なクローンを作成
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
		sp< char >	spBuffer_;			// Oggファイルバッファ
		int			size_;				// バッファサイズ
		long		curPos_;			// 現在の位置
	};
}

#endif
