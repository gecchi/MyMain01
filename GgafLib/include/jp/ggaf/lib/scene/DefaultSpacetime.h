#ifndef GGAFLIB_DEFAULTSPACETIME_H_
#define GGAFLIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace GgafLib {

/**
 * 「この世」クラスインターフェイス.
 * GgafDxCore::GgafDxSpacetime を継承しただけのインターフェースです。<BR>
 * Ggafライブラリを利用する場合、本クラスを継承し実装したこの世クラスが必要です。<BR>
 * (旧DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultSpacetime : public GgafDxCore::GgafDxSpacetime {
    virtual void processFinal() override;

public:
    GgafCore::GgafLinearOctreeForActor* _pLinearOctree;

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::GgafLinearOctreeForActor* getLinearOctree() const {
        return _pLinearOctree;
    }
    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAFLIB_DEFAULTSPACETIME_H_*/
