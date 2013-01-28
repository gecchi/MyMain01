#ifndef GGAFDXSE_H_
#define GGAFDXSE_H_
namespace GgafDxCore {

/**
 * Sound Effect(Wave) �N���X .
 */
class GgafDxSe : public GgafCore::GgafObject {

    static std::string getWaveFileName(std::string prm_file);
public:
    /** �T�E���h�o�b�t�@ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** wave�t�@�C���� */
    std::string _wave_file_name;
    /** ���̎��g�� */
    DWORD _default_frequency;
    /** [r]�Ō�ɔ��������A�N�^�[ */
    GgafDxGeometricActor* _pActor_LastPlayed;

public:
    /**
     * �R���X�g���N�^
     * @param prm_wave_name ����ID (�v���p�e�B�t�@�C���̃L�[)
     * @return
     */
    GgafDxSe(char* prm_wave_key);

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
     * @param prm_volume �{�����[��(min:0 max:100)
     * @param prm_pan �p��(left:-1.0 center:0 right:1.0)
     * @param prm_frequency ���̎��g���ɏ悸�闦
     */
    virtual void play(int prm_volume, float prm_pan, float prm_frequency);

    /**
     * �{�����[���ƃp�����w�肵��SE��1��Đ�
     * @param prm_volume �{�����[��(min:0 max:100)
     * @param prm_pan    �p��(left:-1.0 center:0 right:1.0)
     */
    virtual void play(int prm_volume, float prm_pan) {
        play(prm_volume, prm_pan, 1.0f);
    }

    /**
     * SE��1��Đ� .
     */
    virtual void play();

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
     * @param prm_pan �p��(left:-1.0 center:0 right:1.0)
     */
    void setPan(float prm_pan);

    /**
     * ���g���̗���ύX .
     * play()���s��ASE���Đ����Ɏg�p���邱�Ƃ�z�� .
     * @param prm_frequency ���̎��g���ɏ悸�闦
     */
    void setFrequencyRate(float prm_frequency);

    virtual ~GgafDxSe();
};

}
#endif /*GGAFDXSE_H_*/
