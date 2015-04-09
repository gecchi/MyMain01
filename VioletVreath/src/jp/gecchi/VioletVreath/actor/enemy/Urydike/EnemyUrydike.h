#ifndef ENEMYURYDIKE_H_
#define ENEMYURYDIKE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"


namespace VioletVreath {

/**
 * 敵機ウリュディケ .
 * ヒルベルト帯
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class EnemyUrydike : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE_BEGIN ,
        PROG_SPLINE ,
        PROG_SCATTER ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** 移動スプラインプログラム */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;

    bool scatter_flg_;

    frame delay_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyUrydike(const char* prm_name);

    void onCreateModel() override;

    /**
     * ウリュディケの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ウリュディケのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ウリュディケの振る舞い .
     */
    void processBehavior() override;

    /**
     * ウリュディケの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ウリュディケの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * 散り散りになる .
     */
    void scatter();


    virtual ~EnemyUrydike();
};

}
#endif /*ENEMYURYDIKE_H_*/

