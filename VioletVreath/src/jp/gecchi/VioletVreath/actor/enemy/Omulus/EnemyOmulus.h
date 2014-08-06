#ifndef ENEMYOMULUS_H_
#define ENEMYOMULUS_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�I�����X .
 * �X�N�����u���n�b�`�B
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyOmulus : public GgafLib::DefaultMorphMeshActor {
private:
//    /** [r]����n�b�`���J���t���[��(�����v�Z�p) */
//    frame frame_of_moment_nextopen_;
//    /** [r]����n�b�`������t���[��(�����v�Z�p) */
//    frame frame_of_moment_nextclose_;
public:
    enum {
        PROG_INIT       ,
        PROG_HATCH_CLOSE,
        PROG_HATCH_OPEN ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** [r]�� */
    bool is_open_hatch_;
    /** [r/w]�n�b�`���J���Ă���t���[���Ԋu */
    frame frame_of_open_interval_;
    /** [r/w]�n�b�`�����Ă��Ă���t���[���Ԋu */
    frame frame_of_close_interval_;
    /** [r/w]�n�b�`�J���� �y�сA���J �̃��[�t�A�j���[�V�����t���[���� */
    frame frame_of_morph_interval_;

    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_Fired_;
    DepositoryConnection* pConn_depo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOmulus(const char* prm_name);

    /**
     * �I�����X���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * �I�����X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �I�����X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �I�����X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �I�����X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �I�����X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyOmulus();
};

}
#endif /*ENEMYOMULUS_H_*/

