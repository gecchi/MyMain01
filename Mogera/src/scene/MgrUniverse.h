#ifndef MGRUNIVERSE_H_
#define MGRUNIVERSE_H_
#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "actor/MgrCamera.h"
#ifdef P_GOD
    #undef P_UNIVERSE
    #define P_UNIVERSE ((Mogera::MgrUniverse*)(P_GOD->_pUniverse))
    #ifdef P_CAM
        #undef P_CAM
    #endif
    #define P_CAM ((Mogera::MgrCamera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
#endif

namespace Mogera {

/**
 * 「この世」の雛形 .
 * GgafLib::DefaultUniverse を継承し「この世」クラスを作成して下さい。
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrUniverse : public GgafLib::DefaultUniverse {

public:
    MgrWorld* pWorld_;

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    MgrUniverse(const char* prm_name, MgrCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~MgrUniverse();
};

}
#endif /*MGRUNIVERSE_H_*/
