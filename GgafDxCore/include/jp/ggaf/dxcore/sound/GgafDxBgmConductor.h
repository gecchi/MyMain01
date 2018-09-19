#ifndef GGAFDXCORE_GGAFDXBGMCONDUCTOR_H_
#define GGAFDXCORE_GGAFDXBGMCONDUCTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <vector>

namespace GgafDxCore {

/**
 * BGM���t�w���҃N���X .
 * BGM�Ƃ���ɕR�����ʁA�p���̒l��ێ�
 * BGM�}�X�^�[�{�����[�����l��
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxBgmConductor : public GgafCore::GgafObject {

public:
//    static int _active_bgm_bpm;
    /** [r]BGM�ԍ��� */
    int _bgm_num;
    /** [r]Bgm�����ڑ� */
    std::vector<GgafDxBgmConnection*>  _vecBgmConnection;
    /** [r]BGM�̃{�����[���z��(�Y����BGM�ԍ�) */
    std::vector<double> _vec_volume;
    /** [r]BGM�̃p���l(�Y����BGM�ԍ�) */
    std::vector<float> _vec_pan;
    /** [r]�t�F�[�h�^�[�Q�b�g�{�����[���̔z��(�Y���̓`�����l��) */
    std::vector<double> _vec_target_volume;
    /** [r]�{�����[�����Z�l�̔z��(�Y���̓`�����l��) */
    std::vector<double> _vec_inc_volume;
    /** [r]���݃t�F�[�h�����ۂ��̔z��(�Y���̓`�����l��) */
    std::vector<bool> _vec_is_fade;
    /** [r]�t�F�[�h���~������̂��ǂ����̔z��(�Y���̓`�����l��) */
    std::vector<bool> _vec_is_fadeafter_stop;

public:
    GgafDxBgmConductor();

    /**
     * BGM���������� .
     * ���t�O�ɕK�����s���Ă����K�v������܂��B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_bgm_name �v���p�e�B�t�@�C��key������
     */
    virtual void ready(int prm_bgm_no, const char* prm_bgm_name);

    /**
     * BGM�����t���鏀���������Ă��邩 .
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     * @return true:���t�ł���^false:���t�ł��Ȃ�
     */
    virtual bool isReady(int prm_bgm_no);

    /**
     * �{�����[���l��ݒ肷�� .
     * BGM�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_volume �{�����[���l(0 �` 1000)
     */
    virtual void setVolume(int prm_bgm_no, double prm_volume);

    /**
     * �{�����[���l���擾���� .
     * BGM�}�X�^�[�{�����[�����l������Ă��Ȃ�setVolume()�Őݒ肳�ꂽ���ʂ��擾�B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @return �{�����[���l(0 �` 1000)
     */
    virtual int getVolume(int prm_bgm_no) {
        return _vec_volume[prm_bgm_no];
    }

    /**
     * �{�����[���l�����Z���� .
     * BGM�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_volume ���Z�{�����[���l(0 �` 1000)
     * @return
     */
    virtual void addVolume(int prm_bgm_no, double prm_volume) {
        setVolume(prm_bgm_no, _vec_volume[prm_bgm_no] + prm_volume);
    }

    /**
     * �p���l��ݒ� .
     * BGM�}�X�^�[�p���͖��쐬�̂��߁A���̂܂ܔ��f
     * @param prm_pan �p���l(left:-1.0 �` center:0 �` right:1.0)
     */
    virtual void setPan(int prm_bgm_no, float prm_pan);

    /**
     * �p���l���擾���� .
     * @param prm_bgm_no
     * @return
     */
    virtual float getPan(int prm_bgm_no) {
        return _vec_pan[prm_bgm_no];
    }

    /**
     * ���t���� .
     * �ꎞ��~���Ă����ꍇ�́A�������牉�t�����B�Ȃ̍ŏ�����Ƃ͌���Ȃ��B
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     * @param prm_is_loop  ���[�v���邩�ǂ����itrue:���[�v�Đ�����^false:���[�v�Đ����Ȃ��j
     */
    virtual void perform(int prm_bgm_no, bool prm_is_loop = true);

    /**
     * �Ȃ̍ŏ����牉�t���� .
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     * @param prm_is_loop ���[�v���邩�ǂ����itrue:���[�v�Đ�����^false:���[�v�Đ����Ȃ��j
     */
    virtual void performFromTheBegining(int prm_bgm_no, bool prm_is_loop = true);

    /**
     * BGM���~���� .
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     */
    virtual void stop(int prm_bgm_no);

    /**
     * BGM���ꎞ��~���� .
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     */
    virtual void pause(int prm_bgm_no);

    /**
     * BGM�̈ꎞ��~���������� .
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     */
    virtual void unpause(int prm_bgm_no);

    /**
     * �SBGM�ԍ���BGM���~ .
     */
    virtual void stop();

    /**
     * �SBGM�ԍ���BGM���ꎞ��~ .
     */
    virtual void pause();

    /**
     * �SBGM�ԍ���BGM�̈ꎞ��~���������� .
     */
    virtual void unpause();

    virtual bool isPerforming(int prm_bgm_no);
    /**
     * BGM�̈ꎞ��~�������f���� .
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @return true:�ꎞ��~���^false:�ꎞ��~���ł͖���
     */
    virtual bool isPause(int prm_bgm_no);

    virtual bool isStopping(int prm_bgm_no);

    virtual GgafDxBgm* getBgm(int prm_bgm_no);

    /**
     * BGM�̐U�镑�� .
     * ��Ƀ{�����[����ω������A�t�F�[�h�C���E�A�E�g���ʂ���������������B
     */
    virtual void behave();

    /**
     * ���t����BGM�Ƀt�F�[�h���ʂ����s����B
     * @param prm_bgm_no              BGM�ԍ�(0 �` )
     * @param prm_frame           �t�F�[�h�ɔ�₷�t���[������
     * @param prm_target_volume   ���B�ڕW�{�����[��(0 �` 100)
     */
    virtual void fade(int prm_bgm_no, frame prm_frame, int prm_target_volume);

    /**
     * BGM���A�t�F�[�h�C���ɂ��Đ����J�n����B
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     * @param prm_frame �t�F�[�h�C���t���[����
     */
    virtual void performFadein(int prm_bgm_no, frame prm_frame);

    /**
     * ���t����BGM�Ƀt�F�[�h�A�E�g���ʂ����s���A�t�F�[�h�A�E�g�㉉�t���~����B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_frame �t�F�[�h�A�E�g�t���[����
     */
    virtual void fadeoutStop(int prm_bgm_no, frame prm_frame);

    /**
     * �SBGM�ԍ��̉��t����BGM�Ƀt�F�[�h�A�E�g���ʂ����s���A�t�F�[�h�A�E�g�㉉�t���~����B
     * �t�F�[�h�A�E�g���Ԃ� setDefaultFadeFrames() �w��̃t���[�����B
     */
    virtual void fadeoutStopAll(frame prm_frame);


    virtual ~GgafDxBgmConductor();
};

}
#endif /*GGAFDXCORE_GGAFDXBGMCONDUCTOR_H_*/
