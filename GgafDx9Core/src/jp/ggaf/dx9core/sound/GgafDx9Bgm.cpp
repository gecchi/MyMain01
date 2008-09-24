#include "stdafx.h"

GgafDx9Bgm::GgafDx9Bgm(string prm_ogg_name) : GgafObject() {
	_ogg_name = prm_ogg_name;
	string ogg_filename = GGAFDX9_PROPERTY(DIR_OGG) + prm_ogg_name+".ogg";
	_pBgm_Next = NULL;
	_pSoundBgm = NEW CC3DSoundBGM();
	int ret = _pSoundBgm -> CreateBGM( *GgafDx9Sound::_pC3DSound, ogg_filename.c_str());
	if (!ret) {
		throw_GgafCriticalException("GgafDx9Bgm::GgafDx9Bgm() Error! " << ogg_filename << " ‚Ì‰Šú‰»‚ÉŽ¸”s");
	}
}

void GgafDx9Bgm::play() {
	_pSoundBgm -> Play(0,0);
}

void GgafDx9Bgm::play(int prm_iVolume, int prm_iPan) {
	_pSoundBgm -> Play(prm_iVolume, prm_iPan);
}

void GgafDx9Bgm::stop() {
	_pSoundBgm -> Stop();
}


GgafDx9Bgm::~GgafDx9Bgm() {
	if (_pSoundBgm != NULL) {
		_pSoundBgm -> Release();
		delete _pSoundBgm;
		_pSoundBgm = NULL;
	}
}
