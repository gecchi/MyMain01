#ifndef ENEMYDUNA_H_
#define ENEMYDUNA_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機ドゥーナ(作成中！) .
 * 中型機にしようか。
 * ポイっと缶々をなげて、ビシっと槍弾に変化して飛んでいく。
 * @version 1.00
 * @since 2013/08/19
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
        PROG_MOVE_LARGE_UP_SEMIARC_CW  ,
        PROG_MOVE_LARGE_UP_SEMIARC_CCW,
        PROG_MOVE_LARGE_DOWN_SEMIARC_CW  ,
        PROG_MOVE_LARGE_DOWN_SEMIARC_CCW,
        PROG_MOVE_SMALL_UP_SEMIARC_CW  ,
        PROG_MOVE_SMALL_UP_SEMIARC_CCW,
        PROG_MOVE_SMALL_DOWN_SEMIARC_CW  ,
        PROG_MOVE_SMALL_DOWN_SEMIARC_CCW,
        PROG_CLOSE ,
    };
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
     * ドゥーナのがアクティブになった瞬間の処理 .
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
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyDuna();
};

}
#endif /*ENEMYDUNA_H_*/

