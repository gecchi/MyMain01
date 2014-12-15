#ifndef VECEYEACTOR_H_
#define VECEYEACTOR_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VVViewer {

/**
 * テスト敵キャラクタ .
 * @version 1.00
 * @since 2014/12/15
 * @author Masatoshi Tsuge
 */
class VecEyeActor : public GgafLib::DefaultMeshActor {

public:
    int _hx;
    int _hy;
    int _hz;

    int _hx_prev;
    int _hy_prev;
    int _hz_prev;

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    VecEyeActor(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~VecEyeActor();
};

}
#endif /*VECEYEACTOR_H_*/

