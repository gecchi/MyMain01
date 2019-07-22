#ifndef ENEMYHALIA_H_
#define ENEMYHALIA_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

namespace VioletVreath {

/**
 * 敵機ハリア .
 * スペハリのトモスもどき？
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
class EnemyHalia : public VvEnemyActor<GgafLib::DefaultMassMorphMeshActor> {
public:
    velo veloTopMv_;
    /** 移動スプラインプログラム */
    GgafLib::SplineLeader* pRikishaLeader_;
    /** 原点から初期カメラZ位置の距離 */
    coord dZ_camera_init_;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyHalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * ハリアの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ハリアがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ハリアの振る舞い .
     */
    void processBehavior() override;

    /**
     * ハリアの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ハリアの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * スプライン移動設定 .
     * initialize() までに設定して下さい。
     * @param prm_pRikishaLeader
     */
    void setSplineRikishaLeader(GgafLib::SplineLeader* prm_pRikishaLeader) {
        pRikishaLeader_ = prm_pRikishaLeader;
    }

    virtual ~EnemyHalia();
};

}
#endif /*ENEMYHALIA_H_*/

