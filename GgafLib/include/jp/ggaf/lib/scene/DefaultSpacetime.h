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
    GgafCore::GgafLinearOctree* _pLinearOctree;
    GgafCore::GgafLinearOctreeForActor* _pLinearOctreeForActor;
    GgafCore::GgafLinearQuadtree* _pLinearQuadtree;
    GgafCore::GgafLinearQuadtreeForActor* _pLinearQuadtreeForActor;
public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::GgafLinearOctree* getLinearOctree() {
        return _pLinearOctree;
    }
    inline GgafCore::GgafLinearOctreeForActor* getLinearOctreeForActor() {
        return _pLinearOctreeForActor;
    }
    inline GgafCore::GgafLinearQuadtree* getLinearQuadtree() {
        return _pLinearQuadtree;
    }

    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAFLIB_DEFAULTSPACETIME_H_*/
