#ifndef ENEMYERELMANCORE_H_
#define ENEMYERELMANCORE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * エビウスのコア .
 * @version 1.00
 * @since 2014/11/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanCore : public GgafLib::DefaultMorphMeshActor {

public:
    EnemyErelmanController* pController_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErelmanCore(const char* prm_name, EnemyErelmanController* prm_pController);

    void onCreateModel() override;

    /**
     * エビウスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エビウスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エビウスの振る舞い .
     */
    void processBehavior() override;

    /**
     * エビウスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * エビウスの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyErelmanCore();
};

}
#endif /*ENEMYERELMANCORE_H_*/

