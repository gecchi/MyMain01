#ifndef GGAFDX9SE_H_
#define GGAFDX9SE_H_
namespace GgafDx9Core {


// 本プログラムは、<BR>
// 「越後屋Cyber」 http://www.e-cyber.org/ <BR>
// のメンバーのアンダー氏のサンプルプログラムを流用（一部変更）させていただいて、実装しています。<BR>
// 対象クラスは CWaveDecorder です。
// アンダー氏ありがとう！
//                                            2009/01/13 Masatoshi Tsuge<BR>


/**
 * Wave(Sound Effect) 活動クラス .
 */
class GgafDx9Se : public GgafCore::GgafObject {

	static const int _DS_MINVOLUME_ = -9600;
	static const int _DS_PAN_LEFT_ = -10000;
	static const int _DS_PAN_RIGHT_ = 10000;


	//CC3DSoundSE* _pSoundSE;
public:
	LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
	char* _wave_name;
	GgafDx9Se(char* prm_wave_name, int prm_iBufferCount);
	int writeBuffer(CWaveDecorder& WaveFile);
	int restore(void);
	virtual void act();
	virtual void play(int prm_iVolume, int prm_iPan);

	virtual ~GgafDx9Se();
};


}
#endif /*GGAFDX9SE_H_*/
