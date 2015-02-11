#ifndef TEKI001_H_
#define TEKI001_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * テスト敵キャラクタ .
 * @version 1.00
 * @since 2013/08/30
 * @author Masatoshi Tsuge
 */
class Zako : public GgafLib::DefaultMeshActor {

public:

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    Zako(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~Zako();
};

}
#endif /*TEKI001_H_*/

