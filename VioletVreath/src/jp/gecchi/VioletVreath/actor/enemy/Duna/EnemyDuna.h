#ifndef ENEMYDUNA_H_
#define ENEMYDUNA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機ドゥーナ(作成中！) .
 * ムーンクレスタのコールドアイのような動きに挑戦ッ！！。
 * @version 1.00
 * @since 2013/08/22
 * @author Masatoshi Tsuge
 */
class EnemyDuna : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    GgafDx::GeoElem next_pos_;
    int step_;
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
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyDuna();
};

}
#endif /*ENEMYDUNA_H_*/

