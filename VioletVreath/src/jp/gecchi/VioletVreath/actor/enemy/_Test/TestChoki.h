#ifndef TESTCHOKI_H_
#define TESTCHOKI_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"

namespace VioletVreath {

/**
 * チョキ属性テスト .
 * @version 1.00
 * @since 2012/08/27
 * @author Masatoshi Tsuge
 */
class TestChoki : public TestEnemy {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestChoki(const char* prm_name);

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

    virtual ~TestChoki();
};

}
#endif /*TESTCHOKI_H_*/

