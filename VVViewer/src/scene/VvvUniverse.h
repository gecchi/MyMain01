#ifndef VVVUNIVERSE_H_
#define VVVUNIVERSE_H_
#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "VvvGod.h"
#include "actor/VvvCamera.h"

#ifdef P_GOD
    #undef P_UNIVERSE
    #define P_UNIVERSE ((VVViewer::VvvUniverse*)(P_GOD->_pUniverse))
    #undef P_CAM
    #define P_CAM ((VVViewer::VvvCamera*)(P_UNIVERSE->_pCamera))
#else
    #undef P_UNIVERSE
    #undef P_CAM
#endif

namespace VVViewer {

/**
 * VVViewerのこの世
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvUniverse : public GgafLib::DefaultUniverse {

public:
    VvvWorld* pWorld_;

    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    VvvUniverse(const char* prm_name, VvvCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override {}

    virtual ~VvvUniverse();
};

}
#endif /*VVVUNIVERSE_H_*/
