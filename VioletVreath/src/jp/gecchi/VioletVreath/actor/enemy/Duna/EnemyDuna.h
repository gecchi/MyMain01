#ifndef ENEMYDUNA_H_
#define ENEMYDUNA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機ドゥーナ(作成中！) .
 * ムーンクレスタのコールドアイのような動きに挑戦ッ！！。
 * @version 1.00
 * @since 2013/08/22
 * @author Masatoshi Tsuge
 */
class EnemyDuna : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        MPH_OPEN = 1,
    };

    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY_EFFECT,
        PROG_ENTRY_MOVE01,
        PROG_ENTRY_MOVE02,
        PROG_MOVE_ORDER_LARGE_SEMIARC_CW,
        PROG_MOVE_ORDER_LARGE_SEMIARC_CCW,
        PROG_MOVE_REV_LARGE_SEMIARC_CW,
        PROG_MOVE_REV_LARGE_SEMIARC_CCW,
        PROG_MOVE_ORDER_SMALL_SEMIARC_CW,
        PROG_MOVE_ORDER_SMALL_SEMIARC_CCW,
        PROG_MOVE_REV_SMALL_SEMIARC_CW,
        PROG_MOVE_REV_SMALL_SEMIARC_CCW,
        PROG_CLOSE ,
        PROG_BANPEI,
    };

    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    GgafDxCore::GgafDxGeoElem next_pos_;
    int num_fire_;
    int nprog_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyDuna(const char* prm_name);

    void onCreateModel() override;

    /**
     * ドゥーナの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * ドゥーナがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * ドゥーナの振る舞い .
     */
    void processBehavior() override;

    /**
     * ドゥーナの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * ドゥーナの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyDuna();
};

}
#endif /*ENEMYDUNA_H_*/

