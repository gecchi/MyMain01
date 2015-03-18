#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �o��G�t�F�N�g��� .
 * @version 1.00
 * @since 2013/06/28
 * @author Masatoshi Tsuge
 */
class EffectEntry : public GgafLib::DefaultMeshSetActor {

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
    EffectEntry(const char* prm_name, const char* prm_model);

    virtual void onInactive() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    /**
     * �G�t�F�N�g�̍��W�������̃A�N�^�[�Ɠ������W�Ɍp�������� .
     * @param prm_pTarget �G�t�F�N�g�̍��W�ɂȂ�A�N�^�[
     */
    void positionFollow(const GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    /**
     * �G�t�F�N�g�̔����A�����A���ł̎��Ԃ�ݒ�B.
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
     * Top �X�P�[��,Bottom �X�P�[���� pScaler_->forceRange(TOP,BOTTOM) �ŏ㏑���ݒ�\�B
     * @param prm_scale_in_frames ��L�@�̃t���[���� (1�`)
     * @param prm_duration_frames ��L�A�̃t���[���� (0�`)
     * @param prm_scale_out_frames ��L�B�̃t���[���� (1�`)
     */
    void config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames);

    virtual ~EffectEntry();
};

}
#endif /*EFFECTENTRY_H_*/

