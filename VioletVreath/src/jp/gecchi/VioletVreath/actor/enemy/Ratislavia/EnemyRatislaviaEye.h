#ifndef ENEMYRATISLAVIAEYE_H_
#define ENEMYRATISLAVIAEYE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * トーラスの目玉 .
 * @version 1.00
 * @since 2012/10/16
 * @author Masatoshi Tsuge
 */
class EnemyRatislaviaEye : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {
    /** 弾発射前溜め効果エフェクト */
    EffectRatislaviaEye001* pEffect_;

public:
    bool is_wake_;
    EnemyRatislavia* pRatislavia_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyRatislaviaEye(const char* prm_name, EnemyRatislavia* prm_pRatislavia);

    void onCreateModel() override;

    /**
     * トーラスアイの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * トーラスアイがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * トーラスアイの振る舞い .
     */
    void processBehavior() override;

    /**
     * トーラスアイの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * トーラスアイの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    void wake();

    virtual ~EnemyRatislaviaEye();
};

}
#endif /*ENEMYRATISLAVIAEYE_H_*/

