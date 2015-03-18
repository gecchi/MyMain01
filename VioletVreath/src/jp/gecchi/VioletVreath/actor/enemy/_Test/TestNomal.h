#ifndef TESTNOMAL_H_
#define TESTNOMAL_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"

namespace VioletVreath {

/**
 * パー属性テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestNomal : public TestEnemy {

public:
      enum {
          SE_DAMAGED   ,
          SE_EXPLOSION ,
      };

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestNomal(const char* prm_name);

    /**
     * 敵のがアクティブになった瞬間の処理 .
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
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~TestNomal();
};

}
#endif /*TESTNOMAL_H_*/

