#ifndef MIKATA001_H_
#define MIKATA001_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * テスト味方キャラクタ .
 * @version 1.00
 * @since 2013/08/30
 * @author Masatoshi Tsuge
 */
class Mikata001 : public GgafLib::DefaultMeshActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    Mikata001(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    void onActive() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    void onInactive() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Mikata001();
};

}
#endif /*MIKATA001_H_*/

