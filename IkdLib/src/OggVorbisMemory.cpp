// OggVorbisMemory.cpp
//

#pragma warning ( disable : 4267 )
#pragma warning ( disable : 4244 )
#pragma warning ( disable : 4996 )
#include "GgafCommonHeader.h"
#include "OggVorbisMemory.h"
#include <stdio.h>
#include <string.h>

namespace Dix {
	// コンストラクタ
	OggVorbisMemory::OggVorbisMemory() :
		size_	( 0 ),
		curPos_	( 0 )
	{
	}

	// コンストラクタ
	OggVorbisMemory::OggVorbisMemory( const char* filePath ) :
		size_		( 0 ),
		curPos_		( 0 )
	{
		createBuffer( filePath );
	}

	// デストラクタ
	OggVorbisMemory::~OggVorbisMemory() {
		clear();
	}

	//! クリア
	void OggVorbisMemory::clear() {
		size_ = 0;
		curPos_ = 0;
		spBuffer_ = 0;
		OggVorbisResource::clear();
	}

	// 安全なクローンを作成
	sp< OggVorbisResource > OggVorbisMemory::createClone() {
		if ( isReady_ == false ) {
			return 0;
		}
		OggVorbisMemory* obj = NEW OggVorbisMemory;
		*obj = *this;
		obj->curPos_ = 0;

		// コールバック登録
		ov_callbacks callbacks = {
			&OggVorbisMemory::read,
			&OggVorbisMemory::seek,
			&OggVorbisMemory::close,
			&OggVorbisMemory::tell
		};

		// Oggオープン
		if ( ov_open_callbacks( obj, &obj->oggVorbisFile_ , 0, 0, callbacks ) != 0 ) {
			obj->clear();
			DELETE_IMPOSSIBLE_NULL(obj);
			//delete obj;
			return 0;
		}

		sp< OggVorbisMemory > spObj( obj );

		return spObj;
	}

	//! メモリ読み込み
	size_t OggVorbisMemory::read( void* buffer, size_t size, size_t maxCount, void* stream ) {
		if ( buffer == 0 ) {
			return 0;
		}

		// ストリームからオブジェクトのポインタを取得
		OggVorbisMemory *p = (OggVorbisMemory*)stream;

		// 取得可能カウント数を算出
		int resSize = p->size_ - p->curPos_;
		size_t count = resSize / size;
		if ( count > maxCount ) {
			count = maxCount;
		}

		memcpy( buffer, p->spBuffer_.GetPtr() + p->curPos_, size * count );

		// ポインタ位置を移動
		p->curPos_ += size * count;

		return count;
	};

	//! メモリシーク
	int OggVorbisMemory::seek( void* buffer, ogg_int64_t offset, int flag ) {

		// ストリームからオブジェクトのポインタを取得
		OggVorbisMemory *p = (OggVorbisMemory*)buffer;

		switch( flag ) {
		case SEEK_CUR:
			p->curPos_ += offset;
			break;

		case SEEK_END:
			p->curPos_ = p->size_ + offset;
			break;

		case SEEK_SET:
			p->curPos_ = offset;
			break;

		default:
			return -1;
		}

		if ( p->curPos_ > p->size_ ) {
			p->curPos_ = p->size_;
			return -1;
		} else if ( p->curPos_ < 0 ) {
			p->curPos_ = 0;
			return -1;
		}

		return 0;
	}

	//! メモリクローズ
	int OggVorbisMemory::close( void* buffer ) {
		// デストラクタやクリアが先に処理してくれているので
		// ここは何もしない
		return 0;
	}

	//! メモリ位置通達
	long OggVorbisMemory::tell( void* buffer ) {
		OggVorbisMemory *p = (OggVorbisMemory*)buffer;
		return p->curPos_;
	}

	//! Oggバッファを作成
	bool OggVorbisMemory::createBuffer( const char* filePath ) {

		clear();

		// ファイルをバッファにコピー
		FILE *f = fopen( filePath, "rb" );
		if ( f == 0 ) {
			return false;  // オープン失敗
		}
		fseek( f, 0, SEEK_END );
		size_ = ftell( f );
		fseek( f, 0, SEEK_SET );

		spBuffer_.SetPtr( NEW char[ size_ ], true );
		size_t readSize = fread( spBuffer_.GetPtr(), size_, 1, f );
		if ( readSize != 1 ) {
			// 何か変です
			clear();
			return false;
		}

		// コールバック登録
		ov_callbacks callbacks = {
			&OggVorbisMemory::read,
			&OggVorbisMemory::seek,
			&OggVorbisMemory::close,
			&OggVorbisMemory::tell
		};

		// Oggオープン
		if ( ov_open_callbacks( this, &oggVorbisFile_ , 0, 0, callbacks ) != 0 ) {
			clear();
			return false;
		}

		strcpy( filePath_, filePath );

		isReady_ = true;

		return true;
	}

}
