#ifndef MGRACTOR_H_
#define MGRACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace Mogera {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class MgrActor : public GgafLib::DefaultBoardActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    MgrActor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~MgrActor();
};

}
#endif /*MGRACTOR_H_*/

