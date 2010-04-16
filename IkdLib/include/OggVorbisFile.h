// OggVorbisFile.h
//

#ifndef IKD_DIX_OGGVORBISFILE_H
#define IKD_DIX_OGGVORBISFILE_H

#include "OggVorbisResource.h"
#include "DixSmartPtr.hpp"
#include "memory.h"

namespace Dix {
	class OggVorbisFile : public OggVorbisResource {
	public:
		OggVorbisFile();
		OggVorbisFile( const char* filePath );

		virtual ~OggVorbisFile();

		//! クリア
		virtual void clear();

		//! 安全なクローンを作成
		virtual sp< OggVorbisResource > createClone();

		//! Oggファイルオープン
		bool open( const char* filePath );

	protected:
		char filePath_[ 256 ];	// ファイル名
	};
}

#endif