#ifndef ENEMYERELMAN_H_
#define ENEMYERELMAN_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機エレルマン .
 * トーラスの帯の編隊要因
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelman : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    /** 移動スプラインプログラム */
    GgafDx::VehicleLeader* pVehicleLeader_;

    bool scatter_flg_;
    frame free_interval_;
    frame delay_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErelman(const char* prm_name);

    void onCreateModel() override;

    /**
     * エレルマンの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エレルマンがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * エレルマンの振る舞い .
     */
    void processBehavior() override;

    /**
     * エレルマンの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    void onInactive() override;

    /**
     * 散り散りになる .
     */
    void scatter();

    /**
     * フォーメーションから一時的に開放 .
     * @param prm_free_interval
     */
    void setFreeInterval(frame prm_free_interval) {
        free_interval_ = prm_free_interval;
    }

    virtual ~EnemyErelman();
};

}
#endif /*ENEMYERELMAN_H_*/

