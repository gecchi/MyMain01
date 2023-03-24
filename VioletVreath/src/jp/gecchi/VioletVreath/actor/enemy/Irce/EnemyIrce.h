#ifndef ENEMYIRCE_H_
#define ENEMYIRCE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�C���P .
 * �ŏ��ɍ�����G
 * @version 1.00
 * @since 2010/03/25
 * @author Masatoshi Tsuge
 */
class EnemyIrce : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyIrce(const char* prm_name);

    /**
     * �C���P���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * �C���P�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �C���P���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �C���P�̐U�镑�� .
     */
    void processBehavior() override;


    /**
     * �C���P�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �C���P�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyIrce();
};

}
#endif /*ENEMYIRCE_H_*/

