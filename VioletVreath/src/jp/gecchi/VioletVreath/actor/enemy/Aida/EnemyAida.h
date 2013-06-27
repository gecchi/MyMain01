#ifndef ENEMYAIDA_H_
#define ENEMYAIDA_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機アイーダ .
 * スペハリのIDAみたいなんで。
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyAida : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT ,
        PROG_ENTRY,
        PROG_MOVE01,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** [r]入場エフェクト */
    GgafDxCore::GgafDxDrawableActor* pEntryEffect_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAida(const char* prm_name);

    void onCreateModel() override;

    /**
     * アイーダの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アイーダのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アイーダの振る舞い .
     */
    void processBehavior() override;

    /**
     * アイーダの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アイーダの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAida();
};

}
#endif /*ENEMYAIDA_H_*/

