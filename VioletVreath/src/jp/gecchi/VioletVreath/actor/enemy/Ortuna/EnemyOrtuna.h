#ifndef ENEMYORTUNA_H_
#define ENEMYORTUNA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機オルトゥナ .
 * ビューポイント２面水面からワラワラ出る魚雑魚みたいなんに
 * @version 1.00
 * @since 2013/08/05
 * @author Masatoshi Tsuge
 */
class EnemyOrtuna : public GgafLib::DefaultMorphMeshActor {

public:
    /** [r]出現座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]折り返し座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem stagnating_pos_;

    frame stagnating_pos_frames_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOrtuna(const char* prm_name);

    void onCreateModel() override;

    /**
     * オルトゥナの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * オルトゥナがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * オルトゥナの振る舞い .
     */
    void processBehavior() override;

    /**
     * オルトゥナの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * オルトゥナの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOrtuna();
};

}
#endif /*ENEMYAPPHO_H_*/

