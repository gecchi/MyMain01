#ifndef ENEMYIDA_H_
#define ENEMYIDA_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 敵機イーダ .
 * スペハリのIDAみたいなんでいこうか。
 * 最初のFKフォーメション。
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIda : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_INIT ,
        PROG_ENTRY,
        PROG_MOVE01,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIda(const char* prm_name);

    void onCreateModel() override;

    /**
     * イーダの初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * イーダのがアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * イーダの振る舞い .
     */
    void processBehavior() override;

    /**
     * イーダの振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * イーダの衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyIda();
};

}
#endif /*ENEMYIDA_H_*/

