#ifndef ENEMYTAMAGO01_H_
#define ENEMYTAMAGO01_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

namespace VioletVreath {

/**
 * テスト用 .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyTamago01 : public GgafLib::SpriteMeshSetActor {

public:
    /** 行動パターン番号 */
    int iMovePatternNo_;
    /** 移動スプラインプログラム */
    GgafLib::SplineLeader* pProgram_Tamago01Move_;
    /** 弾ストック */
    GgafCore::GgafActorDepository* pDepo_shot_;
    /** 弾発射効果エフェクト */
    GgafCore::GgafActorDepository* pDepo_effect_;

    DepositoryConnection* pConn_depo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyTamago01(const char* prm_name);

    /**
     * たまごモデルが生成された際に１回だけ実行される処理
     */
    void onCreateModel() override;
    /**
     * たまごの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * たまごがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * たまごの振る舞い .
     */
    void processBehavior() override;

    /**
     * たまごの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * たまごの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 発射弾設定 .
     * @param prm_pDepo (GgafDxFigureActor*)にキャスト可能なアクターを子に持つデポジトリのポインタ
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_shot_ = prm_pDepo;
    }

    /**
     * 効果エフェクト設定 .
     * @param prm_pDepo (GgafDxFigureActor*)にキャスト可能なアクターを子に持つデポジトリのポインタ
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_effect_ = prm_pDepo;
    }

    virtual ~EnemyTamago01();
};

}
#endif /*ENEMYTAMAGO01_H_*/

