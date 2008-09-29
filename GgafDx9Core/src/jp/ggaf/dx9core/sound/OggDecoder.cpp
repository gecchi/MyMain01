#include "stdafx.h"

// OggDecoder.cpp
//

//#pragma comment ( lib, "ogg_static.lib" )
//#pragma comment ( lib, "vorbis_static.lib" )
//#pragma comment ( lib, "vorbisfile_static.lib" )

//#include "OggDecoder.h"
//#include <memory.h>

namespace {
	const unsigned int requestSize_g = 4096;	// 読み込み単位
}

	//! コンストラクタ
	OggDecoder::OggDecoder() {
	}

	OggDecoder::OggDecoder( OggVorbisResource* oggVorbisResource ) {
		setResource( oggVorbisResource );
	}

	//! デストラクタ
	OggDecoder::~OggDecoder() {
		clear();

		if (oggVorbisResource_ != NULL) {
			delete oggVorbisResource_;
		}
	}

	//! クリア
	void OggDecoder::clear() {
		PCMDecoder::clear();
	}

	//! セグメント取得
	bool OggDecoder::getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd ) {
		if ( isReady() == false ) {
			return false;
		}

		if ( buffer == 0 ) {
			if ( isEnd ) *isEnd = true;
			if ( writeSize ) *writeSize = 0;
			return false;
		}

		OggVorbis_File& ovf_ = oggVorbisResource_->getOggVorbisFile();

		if ( isEnd ) *isEnd = false;

		memset( buffer, 0, size );
		unsigned int requestSize = requestSize_g;
		int bitstream = 0;
		int readSize = 0;
		unsigned int comSize = 0;
		bool isAdjust = false;

		if ( size < requestSize ) {
			requestSize = size;
			isAdjust = true;	// 調整段階
		}

		while( 1 ) {
			readSize = ov_read( &ovf_, (char*)( buffer + comSize ), requestSize, 0, 2, 1, &bitstream );
			if ( readSize == 0 ) {
				// ファイルエンドに達した
				if ( isLoop() == true ) {
					// ループする場合読み込み位置を最初に戻す
					ov_time_seek( &ovf_, 0.0 );
				}
				else {
					// ループしない場合ファイルエンドに達したら終了
					if ( isEnd ) *isEnd = true;
					if ( writeSize ) *writeSize = comSize;
					return true;
				}
			}

			comSize += readSize;

			//TODO _ASSERT( comSize <= size );	// バッファオーバー

			if ( comSize  >= size ) {
				// バッファを埋め尽くしたので終了
				if ( writeSize ) *writeSize = comSize;
				return true;
			}

			if ( size - comSize < requestSize_g ) {
				isAdjust = true;	// 調整段階
				requestSize = size - comSize;
			}
		}

		if ( writeSize ) *writeSize = 0;
		return false;	// 良くわからないエラー
	}

	//! 頭出し
	void OggDecoder::setHead() {
		if ( isReady() == true ) {
			ov_time_seek( &oggVorbisResource_->getOggVorbisFile(), 0.0 );
		}
	}

	//! サウンドをセット
	bool OggDecoder::setResource( OggVorbisResource* oggVorbisResource ) {

		clear();

		if ( oggVorbisResource == 0 || oggVorbisResource->isReady() == false ) {
			return false;
		}

		oggVorbisResource_ = oggVorbisResource->createClone();

		// Oggから基本情報を格納
		vorbis_info *info = ov_info( &oggVorbisResource_->getOggVorbisFile(), -1 );
		setChannelNum( info->channels );
		setBitRate( 16 );
		setSamplingRate( info->rate );

		setReady( true );

		return true;
	}
