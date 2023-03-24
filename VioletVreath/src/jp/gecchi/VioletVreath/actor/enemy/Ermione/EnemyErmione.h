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
 * 敵機エルミオネ  .
 * グラの触手に挑戦ッッ！！！
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
    int num_arm_; //腕の数
    int num_arm_part_;  //腕の節数（3以上）
    Arm* paArm_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErmione(const char* prm_name);

    void onCreateModel() override;

    /**
     * エルミオネの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エルミオネがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エルミオネの振る舞い .
     */
    void processBehavior() override;

    /**
     * エルミオネの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エルミオネの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;
    void addArm(angle prm_rz, angle prm_ry);
    virtual ~EnemyErmione();
};

}
#endif /*ENEMYERMIONE_H_*/

