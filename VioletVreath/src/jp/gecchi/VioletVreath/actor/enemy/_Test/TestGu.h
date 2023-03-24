#ifndef TESTGU_H_
#define TESTGU_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"

namespace VioletVreath {

/**
 * グー属性テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestGu : public TestEnemy {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestGu(const char* prm_name);

    /**
     * 敵がアクティブになった瞬間の処理 .
     */
    void onActive() override;

    /**
     * 敵の振る舞い .
     */
    void processBehavior() override;

    /**
     * 敵の振る舞い後の判定処理 .
     */
    void processJudgement() override;

    /**
     * 敵の衝突時処理 .
     * @param prm_pOtherActor 衝突対象
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    virtual ~TestGu();
};

}
#endif /*TESTGU_H_*/

