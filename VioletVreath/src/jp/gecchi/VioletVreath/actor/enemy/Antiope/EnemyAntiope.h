#ifndef ENEMYANTIOPE_H_
#define ENEMYANTIOPE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機アンティオペ .
 * 物質と反物質の瞬きのようなイメージの動き
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class EnemyAntiope :
    public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** 平行移動速度ベクトル */
    GgafDx::GeoElem mv_velo_twd_;
    /** 相方 */
    EnemyAntiope* pP_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAntiope(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

    void onCreateModel() override;

    /**
     * アンティオペの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アンティオペがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アンティオペの振る舞い .
     */
    void processBehavior() override;

    /**
     * アンティオペの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アンティオペの衝突時処理 .
     */
    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    void onInactive() override;

    virtual ~EnemyAntiope();
};

}
#endif /*ENEMYANTIOPE_H_*/

