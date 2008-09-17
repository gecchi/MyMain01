#ifndef GGAFDX9SOUND_H_
#define GGAFDX9SOUND_H_

class GgafDx9Sound  {
public:
	static CC3DSound* _pC3DSound;
	static bool ENABLE;
	static void init();
	static void release();
	static GgafDx9Se*  createSe(string prm_wave_name);
	static GgafDx9Bgm* createBgm(string prm_ogg_name);
};

#endif /*GGAFDX9SOUND_H_*/
