#ifndef GGAFDXSE_H_
#define GGAFDXSE_H_
namespace GgafDxCore {



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
class GgafDxSe : public GgafCore::GgafObject {
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
    GgafDxSe(char* prm_wave_name);

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
     * @param prm_fPan    �p��(left:-10000 right:10000)
     * @param prm_fRate_Frequency ���̎��g���ɏ悸�闦
     */
    virtual void play(int prm_iVolume, float prm_fPan, float prm_fRate_Frequency);

    /**
     * �{�����[���ƃp�����w�肵��SE��1��Đ�
     * @param prm_iVolume �{�����[��(min:0 max:100)
     * @param prm_fPan    �p��(left:-1.0 center:0 right:1.0)
     */
    virtual void play(int prm_iVolume, float prm_fPan) {
        play(prm_iVolume, prm_fPan, 1.0f);
    }

    virtual void play() {
        play(GGAF_MAX_VOLUME, 0.0f);
    }

    bool isPlaying();


    void setVolume(int prm_iVolume);

    void setPan(float prm_fPan);

    void setFrequencyRate(float prm_fRate_Frequency);

    virtual ~GgafDxSe();
};

}
#endif /*GGAFDXSE_H_*/