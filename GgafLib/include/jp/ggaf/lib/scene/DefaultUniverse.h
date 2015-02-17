#ifndef GGAFLIB_DEFAULTUNIVERSE_H_
#define GGAFLIB_DEFAULTUNIVERSE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

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

    inline LinearOctreeForActor* getLinearOctree() {
        return _pLinearOctree;
    }
    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultUniverse();
};

}
#endif /*GGAFLIB_DEFAULTUNIVERSE_H_*/
