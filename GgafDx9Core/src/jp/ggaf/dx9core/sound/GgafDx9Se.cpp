#include "stdafx.h"

GgafDx9Se::GgafDx9Se(string prm_wave_name, int prm_iBufferCount) : GgafObject() {
	_wave_name = prm_wave_name;
	string wave_filename = GGAFDX9_PROPERTY(DIR_WAVE) + prm_wave_name + ".wav";
	_pSe_Next = NULL;
	_pSoundSE = NEW CC3DSoundSE();

	int ret = _pSoundSE -> CreateSE( *GgafDx9Sound::_pC3DSound, wave_filename.c_str(), prm_iBufferCount, 0);
	if (!ret) {
		throw_GgafCriticalException("GgafDx9Se::GgafDx9Se() Error! " << wave_filename << " ‚Ì‰Šú‰»‚ÉŽ¸”s");
	}
}

void GgafDx9Se::play() {
	_pSoundSE -> Play(0,0);
}

void GgafDx9Se::play(int prm_iVolume, int prm_iPan) {
	_pSoundSE -> Play(prm_iVolume, prm_iPan);
}

GgafDx9Se::~GgafDx9Se() {
	if (_pSoundSE != NULL) {
		_pSoundSE -> Release();
		delete _pSoundSE;
		_pSoundSE = NULL;
	}
}
