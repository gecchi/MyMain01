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
	// �R���X�g���N�^
	OggVorbisMemory::OggVorbisMemory() :
		size_	( 0 ),
		curPos_	( 0 )
	{
	}

	// �R���X�g���N�^
	OggVorbisMemory::OggVorbisMemory( const char* filePath ) :
		size_		( 0 ),
		curPos_		( 0 )
	{
		createBuffer( filePath );
	}

	// �f�X�g���N�^
	OggVorbisMemory::~OggVorbisMemory() {
		clear();
	}

	//! �N���A
	void OggVorbisMemory::clear() {
		size_ = 0;
		curPos_ = 0;
		spBuffer_ = 0;
		OggVorbisResource::clear();
	}

	// ���S�ȃN���[�����쐬
	sp< OggVorbisResource > OggVorbisMemory::createClone() {
		if ( isReady_ == false ) {
			return 0;
		}
		OggVorbisMemory* obj = NEW OggVorbisMemory;
		*obj = *this;
		obj->curPos_ = 0;

		// �R�[���o�b�N�o�^
		ov_callbacks callbacks = {
			&OggVorbisMemory::read,
			&OggVorbisMemory::seek,
			&OggVorbisMemory::close,
			&OggVorbisMemory::tell
		};

		// Ogg�I�[�v��
		if ( ov_open_callbacks( obj, &obj->oggVorbisFile_ , 0, 0, callbacks ) != 0 ) {
			obj->clear();
			DELETE_IMPOSSIBLE_NULL(obj);
			//delete obj;
			return 0;
		}

		sp< OggVorbisMemory > spObj( obj );

		return spObj;
	}

	//! �������ǂݍ���
	size_t OggVorbisMemory::read( void* buffer, size_t size, size_t maxCount, void* stream ) {
		if ( buffer == 0 ) {
			return 0;
		}

		// �X�g���[������I�u�W�F�N�g�̃|�C���^���擾
		OggVorbisMemory *p = (OggVorbisMemory*)stream;

		// �擾�\�J�E���g�����Z�o
		int resSize = p->size_ - p->curPos_;
		size_t count = resSize / size;
		if ( count > maxCount ) {
			count = maxCount;
		}

		memcpy( buffer, p->spBuffer_.GetPtr() + p->curPos_, size * count );

		// �|�C���^�ʒu���ړ�
		p->curPos_ += size * count;

		return count;
	};

	//! �������V�[�N
	int OggVorbisMemory::seek( void* buffer, ogg_int64_t offset, int flag ) {

		// �X�g���[������I�u�W�F�N�g�̃|�C���^���擾
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

	//! �������N���[�Y
	int OggVorbisMemory::close( void* buffer ) {
		// �f�X�g���N�^��N���A����ɏ������Ă���Ă���̂�
		// �����͉������Ȃ�
		return 0;
	}

	//! �������ʒu�ʒB
	long OggVorbisMemory::tell( void* buffer ) {
		OggVorbisMemory *p = (OggVorbisMemory*)buffer;
		return p->curPos_;
	}

	//! Ogg�o�b�t�@���쐬
	bool OggVorbisMemory::createBuffer( const char* filePath ) {

		clear();

		// �t�@�C�����o�b�t�@�ɃR�s�[
		FILE *f = fopen( filePath, "rb" );
		if ( f == 0 ) {
			return false;  // �I�[�v�����s
		}
		fseek( f, 0, SEEK_END );
		size_ = ftell( f );
		fseek( f, 0, SEEK_SET );

		spBuffer_.SetPtr( NEW char[ size_ ], true );
		size_t readSize = fread( spBuffer_.GetPtr(), size_, 1, f );
		if ( readSize != 1 ) {
			// �����ςł�
			clear();
			return false;
		}

		// �R�[���o�b�N�o�^
		ov_callbacks callbacks = {
			&OggVorbisMemory::read,
			&OggVorbisMemory::seek,
			&OggVorbisMemory::close,
			&OggVorbisMemory::tell
		};

		// Ogg�I�[�v��
		if ( ov_open_callbacks( this, &oggVorbisFile_ , 0, 0, callbacks ) != 0 ) {
			clear();
			return false;
		}

		strcpy( filePath_, filePath );

		isReady_ = true;

		return true;
	}

}
