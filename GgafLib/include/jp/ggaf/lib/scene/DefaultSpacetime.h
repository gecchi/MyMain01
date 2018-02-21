#ifndef GGAFLIB_DEFAULTSPACETIME_H_
#define GGAFLIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

#include "jp/ggaf/lib/GgafLibConfig.h"
#include "jp/ggaf/core/util/GgafLinearTreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

typedef GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 3> OctreeRounder;
typedef GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 2> QuadtreeRounder;

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
    OctreeRounder* _pLinearOctreeHitCheckRounder;
    GgafCore::GgafLinearQuadtree* _pLinearQuadtree;
    QuadtreeRounder* _pLinearQuadtreeHitCheckRounder;
public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::GgafLinearOctree* getLinearOctree() {
#ifdef MY_DEBUG
        if (_pLinearOctree == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::getLinearOctree() 八分木は作成されていません。\n"
                    "IS_HIT_CHECK_3D プロパティ true にしてください。\n"
                    "現在のIS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctree;
    }

    inline OctreeRounder* getLinearOctreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearOctreeHitCheckRounder == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::getLinearOctreeHitCheckRounder() 八分木は作成されていません。\n"
                    "IS_HIT_CHECK_3D プロパティ true にしてください。\n"
                    "現在のIS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctreeHitCheckRounder;
    }

    inline GgafCore::GgafLinearQuadtree* getLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pLinearQuadtree == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::getLinearQuadtree() 四分木は作成されていません。 IS_HIT_CHECK_2D プロパティ true にしてください。現在のIS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtree;
    }

    inline QuadtreeRounder* getLinearQuadtreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearQuadtreeHitCheckRounder == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::_pLinearQuadtreeHitCheckRounder() 四分木は作成されていません。 IS_HIT_CHECK_2D プロパティ true にしてください。現在のIS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtreeHitCheckRounder;
    }
    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAFLIB_DEFAULTSPACETIME_H_*/
