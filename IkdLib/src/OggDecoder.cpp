// OggDecoder.cpp
//

#pragma comment ( lib, "ogg_static.lib" )
#pragma comment ( lib, "vorbis_static.lib" )
#pragma comment ( lib, "vorbisfile_static.lib" )

#include "OggDecoder.h"
#include <memory.h>
//#include <crtdbg.h>

namespace {
	const unsigned int requestSize_g = 4096;	// �ǂݍ��ݒP��
}

namespace Dix {
	//! �R���X�g���N�^
	OggDecoder::OggDecoder() {
	}

	OggDecoder::OggDecoder( sp< OggVorbisResource > oggVorbisResource ) {
		setResource( oggVorbisResource );
	}

	//! �f�X�g���N�^
	OggDecoder::~OggDecoder() {
		clear();
	}

	//! �N���A
	void OggDecoder::clear() {
		PCMDecoder::clear();
	}

	//! �Z�O�����g�擾
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
			isAdjust = true;	// �����i�K
		}

		while( 1 ) {
			readSize = ov_read( &ovf_, (char*)( buffer + comSize ), requestSize, 0, 2, 1, &bitstream );
			if ( readSize == 0 ) {
				// �t�@�C���G���h�ɒB����
				if ( isLoop() == true ) {
					// ���[�v����ꍇ�ǂݍ��݈ʒu���ŏ��ɖ߂�
					ov_time_seek( &ovf_, 0.0 );
				}
				else {
					// ���[�v���Ȃ��ꍇ�t�@�C���G���h�ɒB������I��
					if ( isEnd ) *isEnd = true;
					if ( writeSize )
						*writeSize = comSize;
					return true;
				}
			}

			comSize += readSize;

//			if (comSize <= size) {
//				_TRACE_("�o�b�t�@�I�[�o�[");
//			}
			//_ASSERT( comSize <= size );	// �o�b�t�@�I�[�o�[

			if ( comSize  >= size ) {
				// �o�b�t�@�𖄂ߐs�������̂ŏI��
				if ( writeSize ) *writeSize = comSize;
				return true;
			}

			if ( size - comSize < requestSize_g ) {
				isAdjust = true;	// �����i�K
				requestSize = size - comSize;
			}
		}

		if ( writeSize ) *writeSize = 0;
		return false;	// �ǂ��킩��Ȃ��G���[
	}

	//! ���o��
	void OggDecoder::setHead() {
		if ( isReady() == true ) {
			ov_time_seek( &oggVorbisResource_->getOggVorbisFile(), 0.0 );
		}
	}

	//! ���S�ȃN���[���𐶐�
	sp< PCMDecoder > OggDecoder::createClone() {
		sp< OggDecoder > spObj( new OggDecoder );
		if ( oggVorbisResource_->isReady() == false ) {
			return spObj;  // ���Ԃ�
		}

		spObj->setResource( oggVorbisResource_ );

		return spObj;
	}

	//! �T�E���h���Z�b�g
	bool OggDecoder::setResource( sp< OggVorbisResource > oggVorbisResource ) {

		clear();

		if ( oggVorbisResource.GetPtr() == 0 || oggVorbisResource->isReady() == false ) {
			return false;
		}

		oggVorbisResource_ = oggVorbisResource->createClone();
		if ( oggVorbisResource_.GetPtr() == 0 ) {
			// �N���[���쐬���s
			return false;
		}

		// Ogg�����{�����i�[
		vorbis_info *info = ov_info( &oggVorbisResource_->getOggVorbisFile(), -1 );
		setChannelNum( info->channels );
		setBitRate( 16 );
		setSamplingRate( info->rate );

		setReady( true );

		return true;
	}
}
