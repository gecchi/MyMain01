#ifndef ENEMYOEBIUS_H_
#define ENEMYOEBIUS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス .
 * メビウスの帯の編隊要因
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class EnemyOebius : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

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
    EnemyOebius(const char* prm_name);

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

    void onInactive() override;

    /**
     * 散り散りになる .
     */
    void scatter();


    virtual ~EnemyOebius();
};

}
#endif /*ENEMYOEBIUS_H_*/

