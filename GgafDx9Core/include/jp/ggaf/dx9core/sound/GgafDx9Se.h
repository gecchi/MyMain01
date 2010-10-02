#ifndef GGAFDX9SE_H_
#define GGAFDX9SE_H_
namespace GgafDx9Core {



// �{�v���O�����́A<BR>
// �u�z�㉮Cyber�v http://www.e-cyber.org/ <BR>
// �̃����o�[�̃A���_�[���̃T���v���v���O�����̃N���X���g�p���������Ă��܂��B<BR>
// �A���_�[�����肪�Ƃ��I
//
// �ΏہF CWaveDecorder �N���X
//                                            2009/01/13 Masatoshi Tsuge<BR>

/**
 * Sound Effect(Wave) �N���X .
 */
class GgafDx9Se : public GgafCore::GgafObject {
public:
    /** �T�E���h�o�b�t�@ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** wave�t�@�C���� */
    char* _wave_name;

    DWORD _dwDefaultFrequency;
    /**
     * �R���X�g���N�^
     * @param prm_wave_name
     * @return
     */
    GgafDx9Se(char* prm_wave_name);

    /**
     * �o�b�t�@��Wave�f�[�^��]�� .
     * @param WaveFile
     * @return (true:���� / false:���s)
     */
    int writeBuffer(CWaveDecorder& WaveFile);

    /**
     * SoundBuffer�̕��A .
     * @return ���� (true:���� / false:���s)
     */
    int restore(void);

    /**
     * �{�����[���ƃp���Ǝ��g���̗����w�肵��SE���P��Đ�
     * @param prm_iVolume �{�����[��(min:-9600 max:0)
     * @param prm_iPan    �p��(left:-10000 right:10000)
     * @param prm_fRate_Frequency ���̎��g���ɏ悸�闦
     */
    virtual void play(int prm_iVolume, int prm_iPan, float prm_fRate_Frequency);

    /**
     * �{�����[���ƃp�����w�肵��SE��1��Đ�
     * @param prm_iVolume �{�����[��(min:-9600 max:0)
     * @param prm_iPan    �p��(left:-10000 right:10000)
     */
    virtual void play(int prm_iVolume, int prm_iPan) {
        play(prm_iVolume, prm_iPan, 1.0);
    }

    virtual void play() {
        play(DSBVOLUME_MAX, DSBPAN_CENTER);
    }

    void setVolume(int prm_iVolume);

    void setPan(int prm_iPan);

    void setFrequencyRate(float prm_fRate_Frequency);

    virtual ~GgafDx9Se();
};

}
#endif /*GGAFDX9SE_H_*/
