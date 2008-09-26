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

		//! Ogg�o�b�t�@���쐬
		bool createBuffer( const char* filePath );

		// ���S�ȃN���[�����쐬
		virtual OggVorbisResource* createClone();

		//! �N���A
		virtual void clear();

	protected:
		//! �������ǂݍ���
		static size_t read( void* buffer, size_t size, size_t maxCount, void* stream );

		//! �������V�[�N
		static int seek( void* buffer, ogg_int64_t offset, int flag );

		//! �������N���[�Y
		static int close( void* buffer );

		//! �������ʒu�ʒB
		static long tell( void* buffer );

	protected:
		char		filePath_[ 256 ];	// �t�@�C���p�X
		sp< char >	spBuffer_;			// Ogg�t�@�C���o�b�t�@
		int			size_;				// �o�b�t�@�T�C�Y
		long		curPos_;			// ���݂̈ʒu
	};
}

#endif
