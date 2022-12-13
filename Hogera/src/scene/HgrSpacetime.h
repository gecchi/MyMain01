#ifndef HGRSPACETIME_H_
#define HGRSPACETIME_H_
#include "Hogera.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "actor/camera/HgrCamera.h"

namespace Hogera {

/**
 * 「この世」の雛形 .
 * GgafLib::DefaultSpacetime を継承し「この世」クラスを作成して下さい。
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrSpacetime : public GgafLib::DefaultSpacetime {

public:
    HgrWorld* pWorld_;

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    HgrSpacetime(const char* prm_name, HgrCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override;

    void processJudgement() override;

    HgrCamera* getCamera() override { //共変の戻り値
        return (HgrCamera*)_pCamera;
    }
    HgrWorld* getWorld() {
        return pWorld_;
    }
    virtual ~HgrSpacetime();
};

}
#endif /*HGRSPACETIME_H_*/
