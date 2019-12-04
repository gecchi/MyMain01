#ifndef ANITEST_H_
#define ANITEST_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

#include <iostream>
#include <fstream>

namespace Mogera {

/**
 * 敵機アニメっ子 .
 * @version 1.00
 * @since 2015/02/13
 * @author Masatoshi Tsuge
 */
class AniTest : public GgafLib::DefaultD3DXAniMeshActor {
public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    AniTest(const char* prm_name);

    void onCreateModel() override;

    /**
     * アニメっ子の初期処理（インスタンス生成後保証）
     */
    void initialize() override;

    /**
     * アニメっ子がアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * アニメっ子の振る舞い .
     */
    void processBehavior() override;

    /**
     * アニメっ子の振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * アニメっ子の衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~AniTest();
};

}
#endif /*ANITEST_H_*/

