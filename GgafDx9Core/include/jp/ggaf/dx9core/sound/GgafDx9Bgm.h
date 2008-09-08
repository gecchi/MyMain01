#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_

class GgafDx9Bgm : public GgafObject {
public:
	CC3DSoundBGM* _pSoundBgm;
	string _ogg_name;
	GgafDx9Bgm* _pBgm_Next;

	GgafDx9Bgm(string prm_wave_name);

	//virtual void behave();�t�F�[�h�C���t�F�[�h�A�E�g���������邼�I

	virtual void play();

	virtual void play(int prm_iVolume, int prm_iPan);
	virtual void stop();

	virtual ~GgafDx9Bgm();
};

#endif /*GGAFDX9BGM_H_*/
