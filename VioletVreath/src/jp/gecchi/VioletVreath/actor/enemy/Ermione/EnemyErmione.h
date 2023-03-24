#ifndef ENEMYERMIONE_H_
#define ENEMYERMIONE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArm.h"

namespace VioletVreath {

DECLARE_EVENT_VAL(EVENT_ERMIONE_SAYONARA);
DECLARE_EVENT_VAL(EVENT_ERMIONE_ENTRY_DONE);

/**
 * �G�@�G���~�I�l  .
 * �O���̐G��ɒ���b�b�I�I�I
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyErmione :
  public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {
//class EnemyErmione : public VvEnemyActor<GgafLib::CubeMapMorphMeshActor> {

public:
    class Arm {
    public:
        angle pos_Rz_;
        angle pos_Ry_;
        EnemyErmioneArm** papArmPart_;
    public:
        Arm() : pos_Rz_(0),pos_Ry_(0),papArmPart_(nullptr) {}
        ~Arm() {
            GGAF_DELETEARR(papArmPart_);
        }
    };
    int num_arm_; //�r�̐�
    int num_arm_part_;  //�r�̐ߐ��i3�ȏ�j
    Arm* paArm_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErmione(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G���~�I�l�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G���~�I�l���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G���~�I�l�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G���~�I�l�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G���~�I�l�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;
    void addArm(angle prm_rz, angle prm_ry);
    virtual ~EnemyErmione();
};

}
#endif /*ENEMYERMIONE_H_*/

