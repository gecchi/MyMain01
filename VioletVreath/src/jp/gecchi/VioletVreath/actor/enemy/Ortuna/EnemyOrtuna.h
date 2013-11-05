#ifndef ENEMYORTUNA_H_
#define ENEMYORTUNA_H_
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
        PROG_MOVE03 ,
        PROG_BANPEI,
    };
    /** [r]出現座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]折り返し座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem hanging_pos_;

    frame hanging_pos_frames_;
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOrtuna(const char* prm_name);

    void onCreateModel() override;

    /**
     * アッポーの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アッポーのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アッポーの振る舞い .
     */
    void processBehavior() override;

    /**
     * アッポーの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アッポーの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOrtuna();
};

}
#endif /*ENEMYAPPHO_H_*/

