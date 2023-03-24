#ifndef ENEMYOZARTIA_H_
#define ENEMYOZARTIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"


namespace VioletVreath {

/**
 * 敵機オーツァルティア .
 * ちょっと賢い中型機の予定。
 * @version 1.00
 * @since 2013/10/01
 * @author Masatoshi Tsuge
 */
class EnemyOzartia : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    /** ショット関連のフェーズ */
    GgafCore::Phase* pPhase2_;

    bool is_hit_;

    GgafCore::ActorDepository* pDepo_shot01_;
    GgafLib::LaserChipDepository*  pDepo_shot02_;

    GgafDx::GeoElem posMvTarget_;

    bool faceto_ship_;

    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader01_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOzartia(const char* prm_name);

    void onCreateModel() override;

    /**
     * オーツァルティアの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * オーツァルティアがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * オーツァルティアの振る舞い .
     */
    void processBehavior() override;

    /**
     * オーツァルティアの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * オーツァルティアの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOzartia();
};

}
#endif /*ENEMYOZARTIA_H_*/

