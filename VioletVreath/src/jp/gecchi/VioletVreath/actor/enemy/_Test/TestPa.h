#ifndef TESTPA_H_
#define TESTPA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"

namespace VioletVreath {

/**
 * パー属性テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestPa : public TestEnemy {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestPa(const char* prm_name);

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

    virtual ~TestPa();
};

}
#endif /*TESTPA_H_*/

