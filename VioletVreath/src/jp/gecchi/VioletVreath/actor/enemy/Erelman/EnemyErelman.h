#ifndef ENEMYERELMAN_H_
#define ENEMYERELMAN_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�G�����}�� .
 * �g�[���X�̑т̕ґ��v��
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelman : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafDx::DriverLeader* pDriverLeader_;

    bool scatter_flg_;
    frame free_interval_;
    frame delay_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErelman(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G�����}���̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�����}�����A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�����}���̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�����}���̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G�����}���̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �U��U��ɂȂ� .
     */
    void scatter();

    /**
     * �t�H�[���[�V��������ꎞ�I�ɊJ�� .
     * @param prm_free_interval
     */
    void setFreeInterval(frame prm_free_interval) {
        free_interval_ = prm_free_interval;
    }

    virtual ~EnemyErelman();
};

}
#endif /*ENEMYERELMAN_H_*/

