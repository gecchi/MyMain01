#include "stdafx.h"


GgafDx9Bgm::GgafDx9Bgm(string prm_ogg_name) : GgafObject() {
	_TRACE_("GgafDx9Bgm::GgafDx9Bgm "+prm_ogg_name);
	_ogg_name = prm_ogg_name;
	string ogg_filename = GGAFDX9_PROPERTY(DIR_OGG) + prm_ogg_name+".ogg";


	// Oggオブジェクト作成
	//Dix::sp< Dix::OggVorbisMemory > spOggResource( new Dix::OggVorbisMemory( "test.ogg" ) );
	spOggResource.SetPtr( NEW Dix::OggVorbisFile( ogg_filename.c_str() ) );
	spOggDecoder.SetPtr( NEW Dix::OggDecoder( spOggResource ) );
	pPcmPlayer = NEW Dix::PCMPlayer(GgafDx9Sound::_pIDirectSound8 , spOggDecoder);
//	_TRACE_("1");
//	player.setDevice( GgafDx9Sound::_pIDirectSound8 );
//	_TRACE_("2");
//	player.setDecoder( spOggDecoder );
//	_TRACE_("3");
//	_pPcmPlayer = NEW Dix::PCMPlayer(cpDS8, spOggDecoder);
//
//
//	_pOggResource = NEW Dix::OggVorbisFile(ogg_filename.c_str());
//	_pOggDecoder = NEW Dix::OggDecoder(_pOggResource);
//	_pPcmPlayer = NEW Dix::PCMPlayer(GgafDx9Sound::_pIDirectSound8, _pOggDecoder);
//

//	_pOggResource = NEW OggVorbisFile(ogg_filename.c_str());
//	_pOggDecoder = NEW OggDecoder(_pOggResource);
//	_pPcmPlayer = NEW PCMPlayer(GgafDx9Sound::_pIDirectSound8, _pOggDecoder);

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
	pPcmPlayer->play( prm_isLoop );

	//_pSoundBgm -> Play(0,0);
}

void GgafDx9Bgm::pause() {
	pPcmPlayer->pause();

	//_pSoundBgm -> Play(prm_iVolume, prm_iPan);
}

void GgafDx9Bgm::stop() {
	pPcmPlayer->stop();
	//_pSoundBgm -> Stop();
}
void GgafDx9Bgm::setVolume( int prm_volume ) {
	pPcmPlayer->setVolume(prm_volume);
}

//! パンの位置を変える
void GgafDx9Bgm::setPan( int prm_pan ) {
	pPcmPlayer->setPan(prm_pan);
}

//! クリア
void GgafDx9Bgm::clear() {
	pPcmPlayer->clear();
}

bool GgafDx9Bgm::isPlaying() {
	if (pPcmPlayer->getState() == Dix::PCMPlayer::STATE_PLAY) {
		return true;
	} else {
		return false;
	}
}


GgafDx9Bgm::~GgafDx9Bgm() {
	_TRACE_("GgafDx9Bgm::~GgafDx9Bgm() begin");
	pPcmPlayer->clear();
	delete pPcmPlayer;
	_TRACE_("GgafDx9Bgm::~GgafDx9Bgm() end");
//	DELETE_IMPOSSIBLE_NULL(_pPcmPlayer);
//	DELETE_IMPOSSIBLE_NULL(_pOggDecoder);
//	DELETE_IMPOSSIBLE_NULL(_pOggResource);
}
