#ifndef TESTACTOR_H_
#define TESTACTOR_H_
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace Mogera {

/**
 * テスト背景 .
 * @version 1.00
 * @since 2013/08/29
 * @author Masatoshi Tsuge
 */
class TestActor : public GgafLib::DefaultSpriteActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    TestActor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~TestActor();
};

}
#endif /*TESTACTOR*/

