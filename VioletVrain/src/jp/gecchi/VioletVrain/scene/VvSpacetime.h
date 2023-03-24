#ifndef VVSPACETIME_H_
#define VVSPACETIME_H_
#include "jp/gecchi/VioletVrain/VioletVrain.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/gecchi/VioletVrain/actor/camera/VvCamera.h"

namespace VioletVrain {

/**
 * 「この世」 .
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvSpacetime : public GgafLib::DefaultSpacetime {

public:
    World* pWorld_;

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    VvSpacetime(const char* prm_name, VvCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override;

    void processHitCheck() override;

    VvCamera* getCamera() override { //共変の戻り値
        return (VvCamera*)_pCamera;
    }
    World* getWorld() {
        return pWorld_;
    }
    virtual ~VvSpacetime();
};

}
#endif /*VVSPACETIME_H_*/
