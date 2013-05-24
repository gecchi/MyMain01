#ifndef SMPACTOR_H_
#define SMPACTOR_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace SimpleSample {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpActor : public GgafLib::DefaultMeshActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    SmpActor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~SmpActor();
};

}
#endif /*SMPACTOR_H_*/

