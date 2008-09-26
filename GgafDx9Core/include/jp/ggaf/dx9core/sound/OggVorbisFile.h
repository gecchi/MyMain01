// OggVorbisFile.h
//

#ifndef IKD_DIX_OGGVORBISFILE_H
#define IKD_DIX_OGGVORBISFILE_H


//#include "OggVorbisResource.h"
//#include "DixSmartPtr.h"
//#include "memory.h"

	class OggVorbisFile : public OggVorbisResource {
	public:
		OggVorbisFile();
		OggVorbisFile( const char* filePath );

		virtual ~OggVorbisFile();

		//! クリア
		virtual void clear();

		//! 安全なクローンを作成
		virtual OggVorbisResource* createClone();

		//! Oggファイルオープン
		bool open( const char* filePath );

	protected:
		char filePath_[ 256 ];	// ファイル名
	};

#endif
