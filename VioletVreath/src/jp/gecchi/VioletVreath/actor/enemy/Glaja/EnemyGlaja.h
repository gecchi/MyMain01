#ifndef ENEMYGLAJA_H_
#define ENEMYGLAJA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機グラヤ .
 * 中型機にしようか。
 * ポイっと缶々をなげて、ビシっと槍弾に変化して飛んでいく。
 * @version 1.00
 * @since 2013/08/19
 * @author Masatoshi Tsuge
 */
class EnemyGlaja : public GgafLib::DefaultMorphMeshActor {

public:

    enum {
        MPH_OPEN = 1,
    };

    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_MOVE02 ,
        PROG_OPEN ,
        PROG_FIRE ,
        PROG_CLOSE ,
        PROG_BANPEI,
    };

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    DepositoryConnection* pConn_pShot_;
    GgafDxCore::GgafDxGeoElem next_pos_;
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
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyGlaja();
};

}
#endif /*ENEMYGLAJA_H_*/

