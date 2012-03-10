#ifndef GGAFDXSE_H_
#define GGAFDXSE_H_
namespace GgafDxCore {

/**
 * Sound Effect(Wave) �N���X .
 */
class GgafDxSe : public GgafCore::GgafObject {
public:
    /** �T�E���h�o�b�t�@ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** wave�t�@�C���� */
    char* _wave_name;
    /** ���̎��g�� */
    DWORD _dwDefaultFrequency;

    /**
     * �R���X�g���N�^
     * @param prm_wave_name ����ID (����ID + ".wav"�œǂݍ��ރt�@�C�����ɂȂ�)
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
     * @param prm_volume �{�����[��(min:-9600 max:0)
     * @param prm_fPan    �p��(left:-10000 right:10000)
     * @param prm_fRate_Frequency ���̎��g���ɏ悸�闦
     */
    virtual void play(int prm_volume, float prm_fPan, float prm_fRate_Frequency);

    /**
     * �{�����[���ƃp�����w�肵��SE��1��Đ�
     * @param prm_volume �{�����[��(min:0 max:100)
     * @param prm_fPan    �p��(left:-1.0 center:0 right:1.0)
     */
    virtual void play(int prm_volume, float prm_fPan) {
        play(prm_volume, prm_fPan, 1.0f);
    }

    /**
     * SE��1��Đ� .
     */
    virtual void play() {
        play(GGAF_MAX_VOLUME, 0.0f);
    }

    /**
     * SE���Đ��������ׂ� .
     * @return
     */
    bool isPlaying();

    /**
     * �{�����[����ύX .
     * play()���s��ASE���Đ����Ɏg�p���邱�Ƃ�z�� .
     * @param prm_volume �{�����[��(min:0 max:100)
     */
    void setVolume(int prm_volume);

    /**
     * �p����ύX .
     * play()���s��ASE���Đ����Ɏg�p���邱�Ƃ�z�� .
     * @param prm_fPan �p��(left:-1.0 center:0 right:1.0)
     */
    void setPan(float prm_fPan);

    /**
     * ���g���̗���ύX .
     * play()���s��ASE���Đ����Ɏg�p���邱�Ƃ�z�� .
     * @param prm_fRate_Frequency ���̎��g���ɏ悸�闦
     */
    void setFrequencyRate(float prm_fRate_Frequency);

    virtual ~GgafDxSe();
};

}
#endif /*GGAFDXSE_H_*/
