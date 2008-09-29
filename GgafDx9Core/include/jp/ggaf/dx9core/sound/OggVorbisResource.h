// OggVorbisResource.h
//

#ifndef IKD_DIX_OGGVORBISRESOURCE_H
#define IKD_DIX_OGGVORBISRESOURCE_H

//#include "DixSmartPtr.h"
//#include "memory.h"

class OggVorbisResource {
public:
	OggVorbisResource();

	virtual ~OggVorbisResource() {
		clear();
	};

	// �N���A
	virtual void clear();

	// OggVorbis_File�\���̂��擾
	virtual OggVorbis_File& getOggVorbisFile() {
		return oggVorbisFile_;
	};

	// ���S�ȃN���[�����쐬
	virtual OggVorbisResource* createClone() = 0;

	// �����ł����H
	bool isReady() {
		return isReady_;
	};

protected:
	OggVorbis_File oggVorbisFile_; // OggVorbis_File�\����
	bool isReady_; // �����ł����H
};

#endif
