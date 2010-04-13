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
     * �{�����[���ƃp�����A�N�^�[�̈ʒu�Ōv�Z����SE���Đ�
     * @param prm_pActor SE�������A�N�^�[
     */
    virtual void play(GgafDx9GeometricActor* prm_pActor);

    /**
     * �ꎞ�I�Ƀ{�����[���ƃp�����w�肵��SE���Đ�
     * @param prm_iVolume
     * @param prm_iPan
     */
    virtual void play(int prm_iVolume, int prm_iPan);

    virtual void play() {
        play(DSBPAN_CENTER, DSBPAN_CENTER);
    }


    virtual ~GgafDx9Se();
};

}
#endif /*GGAFDX9SE_H_*/
