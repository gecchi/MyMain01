#ifndef ENEMYAPPHO_H_
#define ENEMYAPPHO_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機アッポー .
 * 超連射６８Kの雑魚のように、
 * 現れて、目の前にスーっと来て、
 * ちょっとウロウロして、スーっと逃げる。
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class EnemyAppho : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** [r]出現座標(フォーメーションオブジェクトが設定) */
    GgafDx::GeoElem entry_pos_;
    /** [r]ウロウロする座標(フォーメーションオブジェクトが設定) */
    GgafDx::GeoElem stagnating_pos_;
    /** [r]退出座標(フォーメーションオブジェクトが設定) */
    GgafDx::GeoElem leave_pos_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAppho(const char* prm_name);

    void onCreateModel() override;

    /**
     * アッポーの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アッポーがアクティブになった瞬間の処理 .
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
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyAppho();
};

}
#endif /*ENEMYAPPHO_H_*/

