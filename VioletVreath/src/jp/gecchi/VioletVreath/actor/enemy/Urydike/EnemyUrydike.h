#ifndef ENEMYURYDIKE_H_
#define ENEMYURYDIKE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機ウリュディケ .
 * ヒルベルト帯
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class EnemyUrydike : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** 移動スプラインプログラム */
    GgafDx::VehicleLeader* pVehicleLeader_;

    bool scatter_flg_;

    frame delay_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyUrydike(const char* prm_name);

    void onCreateModel() override;

    /**
     * ウリュディケの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ウリュディケがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ウリュディケの振る舞い .
     */
    void processBehavior() override;

    /**
     * ウリュディケの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ウリュディケの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 散り散りになる .
     */
    void scatter();


    virtual ~EnemyUrydike();
};

}
#endif /*ENEMYURYDIKE_H_*/

