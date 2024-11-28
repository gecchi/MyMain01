#ifndef ENEMYTHAGORAS_H_
#define ENEMYTHAGORAS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機タゴラス .
 * トランジットレベル１
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class EnemyThagoras : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** 移動スプラインプログラム */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** 鼓動(スケール)を同期させる為のダミーアクター */
    GgafLib::DefaultGeometricActor* pActor4Sc_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyThagoras(const char* prm_name);

    void onCreateModel() override;

    /**
     * タゴラスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * タゴラスがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * タゴラスの振る舞い .
     */
    void processBehavior() override;

    /**
     * タゴラスの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    void onInactive() override;


    virtual ~EnemyThagoras();
};

}
#endif /*ENEMYTHAGORAS_H_*/

