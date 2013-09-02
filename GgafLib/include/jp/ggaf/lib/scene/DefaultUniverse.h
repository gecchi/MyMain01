#ifndef GGAFLIB_DEFAULTUNIVERSE_H_
#define GGAFLIB_DEFAULTUNIVERSE_H_
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

#ifdef P_GOD
    #undef P_UNIVERSE
    #define P_UNIVERSE ((GgafLib::DefaultUniverse*)(P_GOD->_pUniverse))
    #undef P_CAM
    #define P_CAM ((GgafLib::DefaultCamera*)(P_UNIVERSE->_pCamera))
#else
    #undef P_UNIVERSE
    #undef P_CAM
#endif

namespace GgafLib {

/**
 * 「この世」クラスインターフェイス.
 * GgafDxCore::GgafDxUniverse を継承しただけのインターフェースです。<BR>
 * Ggafライブラリを利用する場合、本クラスを継承し実装したこの世クラスが必要です。<BR>
 * (旧DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultUniverse : public GgafDxCore::GgafDxUniverse {
    virtual void processFinal() override;

public:
    LinearOctreeForActor* _pLinearOctree;

public:
    DefaultUniverse(const char* prm_name, DefaultCamera* prm_pCamera);

    virtual ~DefaultUniverse();
};

}
#endif /*GGAFLIB_DEFAULTUNIVERSE_H_*/
