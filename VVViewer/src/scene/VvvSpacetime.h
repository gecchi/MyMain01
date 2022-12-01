#ifndef VVVSPACETIME_H_
#define VVVSPACETIME_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "actor/VvvCamera.h"

namespace VVViewer {

/**
 * VVViewerのこの世
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvSpacetime : public GgafLib::DefaultSpacetime {

public:
    VvvWorld* pWorld_;

    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    VvvSpacetime(const char* prm_name, VvvCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override;

    virtual VvvCamera* getCamera() override { //共変の戻り値
        return (VvvCamera*)_pCamera;
    }

    virtual ~VvvSpacetime();
};

}
#endif /*VVVSPACETIME_H_*/
