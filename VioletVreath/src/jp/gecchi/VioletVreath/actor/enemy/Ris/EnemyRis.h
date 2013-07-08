#ifndef ENEMYRIS_H_
#define ENEMYRIS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@���X .
 * �t���[����e�Ƃ��ďo���B
 * @version 1.00
 * @since 2009/12/22
 * @author Masatoshi Tsuge
 */
class EnemyRis : public GgafLib::DefaultMeshSetActor {

//    /** �t�H�[���[�V����(��t�H�[���[�V��������nullptr) */
//    GgafLib::TreeFormation* pFormation_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

public:
    enum {
        SE_EXPLOSION,
    };

    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyRis(const char* prm_name);

    void onCreateModel() override;

    /**
     * ���X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * ���X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * ���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * ���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * ���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_Shot,
            GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
            ) {
        pKurokoLeader_ = prm_pKurokoLeader;
        pDepo_Shot_ = prm_pDepo_Shot;
        pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
    }

    virtual ~EnemyRis();
};

}
#endif /*ENEMYRIS_H_*/

