#ifndef ENEMYREMUS_H_
#define ENEMYREMUS_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�����X .
 * ���[�U�[�n�b�`�B
 * @version 1.00
 * @since 2012/10/22
 * @author Masatoshi Tsuge
 */
class EnemyRemus : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT       ,
        PROG_HATCH_CLOSE,
        PROG_HATCH_OPEN ,
        PROG_FIRE       ,
        PROG_NOTHING    ,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** [r]�� */
    bool is_open_hatch_;
    /** [r/w]�n�b�`���J���Ă���t���[���Ԋu */
    frame frame_of_open_interval_;
    /** [r/w]�n�b�`�����Ă��Ă���t���[���Ԋu */
    frame frame_of_close_interval_;
    /** [r/w]�n�b�`�J���� �y�сA���J �̃��[�t�A�j���[�V�����t���[���� */
    frame frame_of_morph_interval_;

    /** [r]���[�U�[�Z�b�g�̃X�g�A�[(���[�U�[�`�b�v�̃f�|�W�g���̃f�|�W�g��) */
    GgafCore::GgafActorDepositoryStore* pLaserChipDepoStore_;
    /** [r]�f�|�W�g���}�l�[�W���[�ւ̐ڑ� */
    DepositoryConnection* pConnection_LaserChipDepoStore_;
    /** [r]���[�U�[�Z�b�g(���[�U�[�`�b�v�̃f�|�W�g��) */
    GgafLib::LaserChipDepository* pLaserChipDepo_;

    bool is_firing_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyRemus(const char* prm_name);

    /**
     * �����X���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * �����X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �����X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �����X�̐U�镑�� .
     */
    void processBehavior() override;
    /**
     * �����X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �����X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyRemus();
};

}
#endif /*ENEMYREMUS_H_*/

