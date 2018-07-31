#ifndef ENEMYOZARTIA_H_
#define ENEMYOZARTIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"


namespace VioletVreath {

/**
 * 敵機オーツァルティア .
 * ちょっと賢い中型機の予定。
 * @version 1.00
 * @since 2013/10/01
 * @author Masatoshi Tsuge
 */
class EnemyOzartia : public GgafLib::DefaultMorphMeshActor {

public:
    /** ショット関連の進捗状態 */
    GgafCore::GgafProgress* pProg2_;

    bool is_hit_;

    GgafCore::GgafActorDepository* pDepo_shot01_;
    GgafLib::LaserChipDepository*  pDepo_shot02_;

    GgafDxCore::GgafDxGeoElem posMvTarget_;

    bool faceto_ship_;

    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineLeader* pKurokoLeader01_;

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
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOzartia();
};

}
#endif /*ENEMYOZARTIA_H_*/

