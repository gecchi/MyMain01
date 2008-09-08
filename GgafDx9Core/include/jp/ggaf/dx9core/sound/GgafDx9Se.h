#ifndef GGAFDX9SE_H_
#define GGAFDX9SE_H_

class GgafDx9Se : public GgafObject {
	CC3DSoundSE* _pSoundSE;
public:
	string _wave_name;
	GgafDx9Se* _pSe_Next;
	GgafDx9Se(string prm_wave_name, int prm_iBufferCount);

	virtual void play();
	virtual void play(int prm_iVolume, int prm_iPan);

	virtual ~GgafDx9Se();
};

#endif /*GGAFDX9SE_H_*/
