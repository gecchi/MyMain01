#ifndef GGAFDXSE_H_
#define GGAFDXSE_H_
#include "jp/ggaf/core/GgafObject.h"

#include <sstream>
//��#include <dsound.h> ����ɖ����ƁAout__ ��炪 sal.h �ɂ�艘������邽��
#ifdef __GNUG__
    //dsound.h ���ŁA__null �萔���g�p�����R�[�h���邽��
    #define __null
#endif
#include <dsound.h>
#ifdef __GNUG__
    #undef __null
#endif

namespace GgafDxCore {

/**
 * Sound Effect(Wave) �N���X .
 */
class GgafDxSe : public GgafCore::GgafObject {

    static std::string getWaveFileName(std::string prm_file);

public:
    /** [r]�T�E���h�o�b�t�@ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;

    char* _wave_key;

    /** [r]wave�t�@�C���� */
    std::string _wave_file_name;
    /** [r]���̎��g�� */
    DWORD _default_frequency;
    /** [r]SE���Ō�ɔ��������A�N�^�[ */
    GgafDxGeometricActor* _pActor_LastPlayed;

    bool _can_looping;
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
     * �{�����[���ƃp���Ǝ��g���̗����w�肵��SE���P��Đ� .
     * �{�����[���ɂ��āA�����Ń}�X�^�{�����[���̍l�������������̂ŁA
     * �A�v���P�[�V�������́A�{���̉��ʂ��C�ɂ����ʏ�Đ��������ꍇ�́A
     * �{�����[����100�Őݒ肷�鎖�B
     * @param prm_volume �{�����[��(0 �` 100)
     * @param prm_pan �p��(left:-1.0 �` center:0 �` right:1.0)
     * @param prm_frequency ���̎��g���ɏ悸�闦
     */
    virtual void play(int prm_volume, float prm_pan, float prm_frequency);

    /**
     * �{�����[���ƃp�����w�肵��SE��1��Đ�
     * �{�����[���ɂ��āA�����Ń}�X�^�{�����[���̍l�������������̂ŁA
     * �A�v���P�[�V�������́A�{���̉��ʂ��C�ɂ����ʏ�Đ��������ꍇ�́A
     * �{�����[����100�Őݒ肷�鎖�B
     * @param prm_volume �{�����[��(0 �` 100)
     * @param prm_pan    �p��(left:-1.0 �` center:0 �` right:1.0)
     */
    virtual void play(int prm_volume, float prm_pan) {
        play(prm_volume, prm_pan, 1.0f);
    }

    /**
     * SE��1��Đ� .
     */
    virtual void play();

    virtual void stop();

    /**
     * SE���Đ��������ׂ� .
     * @return
     */
    bool isPlaying();

    /**
     * �{�����[����ύX .
     * play()���s��ASE���Đ����ɉ��ʂ�ω�������ȂǂɎg�p���邱�Ƃ�z�� .
     * �����Ń}�X�^�{�����[���̍l�������������B
     * @param prm_volume �{�����[��(0 �` 100)
     */
    void setVolume(int prm_volume);

    /**
     * �p����ύX .
     * play()���s��ASE���Đ����Ɏg�p���邱�Ƃ�z�� .
     * @param prm_pan �p��(left:-1.0 �` center:0 �` right:1.0)
     */
    void setPan(float prm_pan);


    void setLooping(bool prm_can_looping) {
        _can_looping = prm_can_looping;
    }

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
