#ifndef GGAF_DX_SE_H_
#define GGAF_DX_SE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <sstream>
#include <windows.h>
//#ifdef __GNUG__
//    #define __null
//    #define NULL    0
//    #define __in
//    #define __out
//#endif
//#include <dsound.h>  //��sal.h �� include ����
//#ifdef __GNUG__
//    #undef __null
//    #undef __in
//    #undef __out
//#endif

struct IDirectSoundBuffer;

namespace GgafDx {

/**
 * Sound Effect(Wave) �N���X .
 */
class Se : public GgafCore::Object {

    static std::string getWaveFileName(std::string prm_file);
    /**
     * �o�b�t�@��Wave�f�[�^��]�� .
     * @param WaveFile
     * @return (true:���� / false:���s)
     */
    int writeBuffer(CWaveDecorder& WaveFile);
public:
    /** [r]�T�E���h�o�b�t�@ */
    IDirectSoundBuffer* _pIDirectSoundBuffer;

    char* _wave_key;

    /** [r]wave�t�@�C���� */
    std::string _wave_file_name;
    /** [r]���̎��g�� */
    DWORD _default_frequency;
    /** [r]SE���Ō�ɔ��������A�N�^�[ */
    GeometricActor* _pActor_last_played;
    /** [r]���݂̉��ʒl(0 �` 1000) */
    int _volume;
    /** [r]���݂̃p���l(left:-1.0 �` center:0 �` right:1.0) */
    float _pan;
    /** [r]���݂̎��g���̗� */
    float _frequency_rate;

public:
    /**
     * �R���X�g���N�^
     * @param prm_wave_name ����ID (�v���p�e�B�t�@�C���̃L�[)
     * @return
     */
    explicit Se(const char* prm_wave_key);

    /**
     * SoundBuffer�̕��A .
     * @return ���� (true:���� / false:���s)
     */
    virtual int restore(void);

    /**
     * SE���Đ� .
     * @param prm_is_looping true:���[�v�Đ�
     */
    virtual void play(bool prm_is_looping = false);

    virtual void stop();

    /**
     * SE���Đ��������ׂ� .
     * @return
     */
    virtual bool isPlaying();

    /**
     * SE�{�����[����ύX .
     * �������A�����Ŏ��ۂɐݒ肳��鉹�ʂ́ABGM�}�X�^�[���ʗ����悶��ꂽ�l�ƂȂ�܂��B
     * @param prm_volume �{�����[��(0 �` 1000)
     */
    void setVolume(int prm_volume);

    /**
     * SE�{�����[�����擾 .
     * �擾����鉹�ʂ́ASE�}�X�^�[���ʗ����l�������O�̒l�B
     * �܂�A�{�N���X��setVolume(int) �Őݒ肵���l�����̂܂܎擾����܂��B
     * @return SE�̃{�����[��(0�`1000)
     */
    virtual int getVolume() {
        return _volume;
    }

    /**
     * �p����ύX .
     * play()���s��ASE���Đ����Ɏg�p���邱�Ƃ�z�� .
     * @param prm_pan �p��(left:-1.0 �` center:0 �` right:1.0)
     */
    void setPan(float prm_pan);

    virtual int getPan() {
        return _pan;
    }
//    void setLooping(bool prm_can_looping) {
//        _can_looping = prm_can_looping;
//    }

    /**
     * ���g���̗���ύX .
     * play()���s��ASE���Đ����Ɏg�p���邱�Ƃ�z�� .
     * @param prm_frequency_rate ���̎��g���ɏ悸�闦
     */
    void setFrequencyRate(float prm_frequency_rate);
    float getFrequencyRate() {
        return _frequency_rate;
    }
    virtual ~Se();
};

}
#endif /*GGAF_DX_SE_H_*/
