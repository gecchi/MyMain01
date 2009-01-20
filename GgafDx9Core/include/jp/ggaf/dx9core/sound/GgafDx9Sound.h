#ifndef GGAFDX9SOUND_H_
#define GGAFDX9SOUND_H_
namespace GgafDx9Core {


class GgafDx9Sound  {
public:
	/** IDirectSound8インターフェイス */
	static IDirectSound8* _pIDirectSound8;
	static DSCAPS _dsCaps;
	//static CC3DSound* _pC3DSound;
	static void init();
	static void release();
	static GgafDx9Se*  createSe(std::string prm_wave_name);
	static GgafDx9Bgm* createBgm(std::string prm_ogg_name);
};


}
#endif /*GGAFDX9SOUND_H_*/
