#ifndef VVSPACETIME_H_
#define VVSPACETIME_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "actor/camera/VvCamera.h"

namespace VioletVrain {

/**
 * 「この世」の雛形 .
 * GgafLib::DefaultSpacetime を継承し「この世」クラスを作成して下さい。
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvSpacetime : public GgafLib::DefaultSpacetime {

public:
    VvWorld* pWorld_;

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

    VvCamera* getCamera() override { //共変の戻り値
        return (VvCamera*)_pCamera;
    }
    VvWorld* getWorld() {
        return pWorld_;
    }
    virtual ~VvSpacetime();
};

}
#endif /*VVSPACETIME_H_*/
