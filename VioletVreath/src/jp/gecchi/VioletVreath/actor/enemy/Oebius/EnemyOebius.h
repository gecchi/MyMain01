#ifndef ENEMYOEBIUS_H_
#define ENEMYOEBIUS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス .
 * メビウスの帯の編隊要因
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class EnemyOebius : public GgafLib::DefaultMeshSetActor {

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
    EnemyOebius(const char* prm_name);

    void onCreateModel() override;

    /**
     * エビウスの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * エビウスのがアクティブになった瞬間の処理 .
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

    /**
     * 散り散りになる .
     */
    void scatter();


    virtual ~EnemyOebius();
};

}
#endif /*ENEMYOEBIUS_H_*/

