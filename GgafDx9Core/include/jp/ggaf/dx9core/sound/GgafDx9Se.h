#ifndef GGAFDX9SE_H_
#define GGAFDX9SE_H_
namespace GgafDx9Core {


// �{�v���O�����́A<BR>
// �u�z�㉮Cyber�v http://www.e-cyber.org/ <BR>
// �̃����o�[�̃A���_�[���̃T���v���v���O�����𗬗p�i�ꕔ�ύX�j�����Ă��������āA�������Ă��܂��B<BR>
// �ΏۃN���X�� CWaveDecorder �ł��B
// �A���_�[�����肪�Ƃ��I
//                                            2009/01/13 Masatoshi Tsuge<BR>


/**
 * Wave(Sound Effect) �����N���X .
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
