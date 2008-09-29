#include "stdafx.h"

GgafDx9Bgm::GgafDx9Bgm(string prm_ogg_name) : GgafObject() {
	_ogg_name = prm_ogg_name;
	string ogg_filename = GGAFDX9_PROPERTY(DIR_OGG) + prm_ogg_name+".ogg";

	_pOggResource = NEW OggVorbisFile(ogg_filename.c_str());
	_pOggDecoder = NEW OggDecoder(_pOggResource);
	_pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8, _pOggDecoder);

	//GgafDx9Sound::_pIDirectSound8, _pOggResource

	_pBgm_Next = NULL;
/*
	_pSoundBgm = NEW CC3DSoundBGM();
	int ret = _pSoundBgm -> CreateBGM( *GgafDx9Sound::_pC3DSound, ogg_filename.c_str());
	if (!ret) {
		throw_GgafCriticalException("GgafDx9Bgm::GgafDx9Bgm() Error! " << ogg_filename << " の初期化に失敗");
	}
	*/
}

void GgafDx9Bgm::play(bool prm_isLoop) {
	_pPcmPlayer->play( prm_isLoop );

	//_pSoundBgm -> Play(0,0);
}

void GgafDx9Bgm::pause() {
	_pPcmPlayer->pause();

	//_pSoundBgm -> Play(prm_iVolume, prm_iPan);
}

void GgafDx9Bgm::stop() {
	_pPcmPlayer->stop();
	//_pSoundBgm -> Stop();
}
void GgafDx9Bgm::setVolume( int prm_volume ) {
	_pPcmPlayer->setVolume(prm_volume);
}

//! パンの位置を変える
void GgafDx9Bgm::setPan( int prm_pan ) {
	_pPcmPlayer->setPan(prm_pan);
}

//! クリア
void GgafDx9Bgm::clear() {
	_pPcmPlayer->clear();
}


GgafDx9Bgm::~GgafDx9Bgm() {
	delete _pPcmPlayer;
	delete _pOggDecoder;
	delete _pOggResource;
//
//	if (_pOggResource != NULL) {
//		delete _pOggResource;
//		_pOggResource = NULL;
//	}
}
