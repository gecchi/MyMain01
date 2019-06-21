#ifndef ENEMYURYDIKE_H_
#define ENEMYURYDIKE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�E�����f�B�P .
 * �q���x���g��
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class EnemyUrydike : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineLeader* pRikishaLeader_;

    bool scatter_flg_;

    frame delay_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyUrydike(const char* prm_name);

    void onCreateModel() override;

    /**
     * �E�����f�B�P�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �E�����f�B�P���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �E�����f�B�P�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �E�����f�B�P�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �E�����f�B�P�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �U��U��ɂȂ� .
     */
    void scatter();


    virtual ~EnemyUrydike();
};

}
#endif /*ENEMYURYDIKE_H_*/

