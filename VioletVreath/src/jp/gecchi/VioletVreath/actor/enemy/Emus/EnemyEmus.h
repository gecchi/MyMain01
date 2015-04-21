#ifndef ENEMYEMUS_H_
#define ENEMYEMUS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�G���X .
 * ���[�U�[�n�b�`�B
 * @version 1.00
 * @since 2012/10/22
 * @author Masatoshi Tsuge
 */
class EnemyEmus : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT       ,
        PROG_HATCH_CLOSE,
        PROG_HATCH_OPEN ,
        PROG_FIRE       ,
        PROG_NOTHING    ,
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

//    /** [r]���[�U�[�Z�b�g�̃X�g�A�[(���[�U�[�`�b�v�̃f�|�W�g���̃f�|�W�g��) */
//    GgafCore::GgafActorDepositoryStore* pDepoStore_laser_set;
//    /** [r]�f�|�W�g���}�l�[�W���[�ւ̐ڑ� */
//    DepositoryConnection* pConn_pDepoStore_laser_set;
    /** [r]���[�U�[�Z�b�g(���[�U�[�`�b�v�̃f�|�W�g��) */
    GgafCore::GgafActorDepository* pDepo_;

    bool is_firing_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyEmus(const char* prm_name);

    /**
     * �G���X���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * �G���X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G���X���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G���X�̐U�镑�� .
     */
    void processBehavior() override;
    void processChangeGeoFinal() override;
    /**
     * �G���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyEmus();
};

}
#endif /*ENEMYEMUS_H_*/

