#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_
#include <dsound.h>
#include <tchar.h>
#include "OggDecoder.h"
#include "OggVorbisMemory.h"
#include "OggVorbisFile.h"
#include "PCMPlayer.h"
#include "DixSmartPtr.h"
#include "DixComPtr.h"

class GgafDx9Bgm : public GgafObject {
public:
	//CC3DSoundBGM* _pSoundBgm;
	string _ogg_name;
	GgafDx9Bgm* _pBgm_Next;

//	Dix::OggDecoder* _pOggDecoder;
//	Dix::OggVorbisFile* _pOggResource;
	Dix::PCMPlayer* pPcmPlayer;

	Dix::sp< Dix::OggVorbisFile > spOggResource;
	Dix::sp< Dix::OggDecoder > spOggDecoder;

//	Dix::PCMPlayer* _pPcmPlayer;

	GgafDx9Bgm(string prm_wave_name);

	//virtual void behave();�t�F�[�h�C���t�F�[�h�A�E�g���������邼�I

	//! �Đ�
	void play( bool isLoop );

	//! �ꎞ��~
	void pause();

	//! ��~
	void stop();

	//! ���ʂ�ς���
	void setVolume( int volume );

	//! �p���̈ʒu��ς���
	void setPan( int pan );
	//! ��~
	void clear();

	bool isPlaying();

	virtual ~GgafDx9Bgm();
};

#endif /*GGAFDX9BGM_H_*/
