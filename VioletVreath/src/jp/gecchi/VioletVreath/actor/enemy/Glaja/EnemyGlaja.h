#ifndef ENEMYGLAJA_H_
#define ENEMYGLAJA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機グラヤ .
 * 中型機にしようか。
 * ポイっと缶々をなげて、ビシっと槍弾に変化して飛んでいく。
 * @version 1.00
 * @since 2013/08/19
 * @author Masatoshi Tsuge
 */
class EnemyGlaja : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    DepositoryConnection* pConn_pShot_;
    GgafDx::GeoElem next_pos_;
    int num_fire_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyGlaja(const char* prm_name);

    void onCreateModel() override;

    /**
     * グラヤの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * グラヤがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * グラヤの振る舞い .
     */
    void processBehavior() override;

    /**
     * グラヤの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * グラヤの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyGlaja();
};

}
#endif /*ENEMYGLAJA_H_*/

