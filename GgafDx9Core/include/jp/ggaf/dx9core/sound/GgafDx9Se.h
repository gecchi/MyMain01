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
 * Sound Effect(Wave) �N���X .
 */
class GgafDx9Se : public GgafCore::GgafObject {

    static const int _DS_MINVOLUME_ = -9600;
    static const int _DS_PAN_LEFT_ = -10000;
    static const int _DS_PAN_RIGHT_ = 10000;

    static int _master_volume;

    //CC3DSoundSE* _pSoundSE;
public:
    /** �T�E���h�o�b�t�@ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** �{�����[��(min:-9600 max:0)�A�f�t�H���g=0 */
    int _iVolume;
    /** �p�� (left:-10000 right:10000)�A�f�t�H���g=0 */
    int _iPan;
    /** wave�t�@�C���� */
    char* _wave_name;

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
     * �ꎞ�I�Ƀ{�����[���ƃp�����w�肵��SE���Đ�
     * @param prm_iVolume
     * @param prm_iPan
     */
    virtual void play(int prm_iVolume, int prm_iPan);


    /**
     * �ꎞ�I�Ƀ{�����[�����w�肵��SE���Đ�
     */
    void play(int prm_iVolume) {
        play(prm_iVolume, _iPan);
    }

    /**
     * SE���Đ�
     */
    void play() {
        play(_iVolume, _iPan);
    }

    /**
     * �{�����[���ݒ�
     * @param prm_iVolume �{�����[��(min:-9600 max:0)
     */
    void setVolume(int prm_iVolume) {
        _iVolume = prm_iVolume;
    }

    /**
     * �p���ݒ�
     * @param prm_iPan �p��(left:-10000 right:10000)
     */
    void setPan(int prm_iPan) {
        _iPan = prm_iPan;
    }

    /**
     * �}�X�^�{�����[���ݒ�(���ݖ�����).
     * TODO:�}�X�^�[�{�����[������������I
     * @param prm_master_volume
     */
    static void setMasterVolume(int prm_master_volume) {
        GgafDx9Se::_master_volume = prm_master_volume;
    }

    virtual ~GgafDx9Se();
};

}
#endif /*GGAFDX9SE_H_*/
