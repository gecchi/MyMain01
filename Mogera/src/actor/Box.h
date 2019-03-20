#ifndef BOX_H_
#define BOX_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace Mogera {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class Box : public GgafLib::DefaultMassMeshActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    Box(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~Box();
};

}
#endif /*BOX_H_*/

