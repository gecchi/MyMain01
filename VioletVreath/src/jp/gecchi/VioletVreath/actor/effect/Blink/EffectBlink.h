#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �܂������G�t�F�N�g��� .
 * ���ޏꎞ�̃G�t�F�N�g�Ȃǂ�z��B
 * @version 1.00
 * @since 2013/06/28
 * @author Masatoshi Tsuge
 */
class EffectBlink : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT ,
        PROG_IN   ,
        PROG_STAY ,
        PROG_OUT  ,
        PROG_BANPEI,
    };

    /** [r]�G�t�F�N�g�����`�ő�̑傫���܂Ŋg��A�܂ł̃t���[���� */
    frame scale_in_frames_;
    /** [r]�G�t�F�N�g�����t���[���� */
    frame duration_frames_;
    /** [r]�G�t�F�N�g���������`���ł܂ł̃t���[���� */
    frame scale_out_frames_;
    /** [r]�G�t�F�N�g�Ώۂ̃A�N�^�[ */
    const GgafDxCore::GgafDxGeometricActor* pTarget_;
    /** [r]�g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ���ʖ�
     * @param prm_model ���f��ID
     */
    EffectBlink(const char* prm_name, const char* prm_model);

    virtual void onInactive() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    /**
     * �܂��������� .
     * �G�t�F�N�g�̔����A�����A���ł��s���B
     * </PRE>
     *       �Q�Q�Q�Q               �� Top �X�P�[��
     *      /:      :�_
     *     / :      :  �_
     *    /  :      :    �_
     *   /   :      :      �_
     *  /    :      :        �_
     * /     :      :          �_   �� Bottom �X�P�[��
     * ----------------------------------------------->���ԁi�t���[���j
     * ���@��|���A��|���� �B ����|
     *
     * </PRE>
     * Top �X�P�[��,Bottom �X�P�[���� pScaler_->setRange(TOP,BOTTOM) �ŏ㏑���ݒ�\�B
     * @param prm_scale_in_frames �������ԁA��L�@�̃t���[���� (1�`)
     * @param prm_duration_frames �������ԁA��L�A�̃t���[���� (0�`)
     * @param prm_scale_out_frames ���Ŏ��ԁA��L�B�̃t���[���� (1�`)
     * @param prm_pFollowTarget �G�t�F�N�g���W�������̃A�N�^�[�Ɠ������W�ɓ������Ƃ�(�Ǐ]������)�B �s�v�̏ꍇ�� nullptr .
     */
    void blink(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
               const GgafDxCore::GgafDxGeometricActor* prm_pFollowTarget);

    /**
     * �܂������t���[�������擾 .
     */
    frame getBlinkFrames() {
        return (scale_in_frames_+duration_frames_+scale_out_frames_);
    }

    /**
     * ����G�t�F�N�g�Ƃ��Ďg�p�����ꍇ�́A�A�N�^�[�̓���J�n�t���[�����擾 .
     * @return ����J�n�t���[��
     */
    frame getFrameOfSummonsBegin() {
        return (scale_in_frames_/2);
    }

    /**
     * ����G�t�F�N�g�Ƃ��Ďg�p�����ꍇ�́A����ɔ�₷�t���[�������擾 .
     * @return ����ɔ�₷�t���[����
     */
    frame getSummoningFrames() {
        return ( (scale_in_frames_/2) + duration_frames_ + (scale_out_frames_/2) );
    }

    virtual ~EffectBlink();
};

}
#endif /*EFFECTENTRY_H_*/

