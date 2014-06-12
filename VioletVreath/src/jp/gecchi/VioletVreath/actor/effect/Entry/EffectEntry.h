#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
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
    frame scale_in_frames_;
    frame duration_frames_;
    frame scale_out_frames_;

    enum {
        PROG_INIT ,
        PROG_IN   ,
        PROG_STAY ,
        PROG_OUT  ,
        PROG_BANPEI,
    };
    /** �G�t�F�N�g�Ώۂ̃A�N�^�[ */
    GgafDxCore::GgafDxGeometricActor* pTarget_;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectEntry(const char* prm_name, const char* prm_model);

    virtual void onInactive() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    /**
     * �����̃A�N�^�[�Ɠ������W���p�� .
     * @param prm_pTarget
     */
    void positionFollow(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

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
     * @param prm_scale_in_frames ��L�@�̃t���[����
     * @param prm_duration_frames ��L�A�̃t���[����
     * @param prm_scale_out_frames ��L�B�̃t���[����
     */
    void config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames);

    virtual ~EffectEntry();
};

}
#endif /*EFFECTENTRY_H_*/

