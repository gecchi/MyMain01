#ifndef ENEMYRATISLAVIAEYE_H_
#define ENEMYRATISLAVIAEYE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * トーラスの目玉 .
 * @version 1.00
 * @since 2012/10/16
 * @author Masatoshi Tsuge
 */
class EnemyRatislaviaEye : public GgafLib::DefaultMorphMeshActor {
    /** 弾発射前溜め効果エフェクト */
    EffectRatislaviaEye001* pEffect_;

public:
    enum {
        PROG_MOVE ,
        PROG_OPEN ,
        PROG_TURN ,
        PROG_FIRE_BEGIN,
        PROG_IN_FIRE   ,
        PROG_FIRE_END  ,
        PROG_CLOSE     ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };
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
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void wake();

    virtual ~EnemyRatislaviaEye();
};

}
#endif /*ENEMYRATISLAVIAEYE_H_*/

