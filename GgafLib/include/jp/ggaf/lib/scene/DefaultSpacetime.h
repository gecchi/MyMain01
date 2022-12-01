#ifndef GGAF_LIB_DEFAULTSPACETIME_H_
#define GGAF_LIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/core/util/LinearTreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

typedef GgafCore::LinearTreeRounder<GgafCore::Actor, 3> OctreeRounder;
typedef GgafCore::LinearTreeRounder<GgafCore::Actor, 2> QuadtreeRounder;

typedef GgafCore::LinearTreeRounder<GgafCore::Actor, 2> QuadtreeRounder_b;
/**
 * 「この世」クラスインターフェイス.
 * GgafDx::Spacetime を継承しただけのインターフェースです。<BR>
 * ggaf ライブラリを利用する場合、本クラスを継承し実装したこの世クラスが必要です。<BR>
 * (旧DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultSpacetime : public GgafDx::Spacetime {
    virtual void processFinal() override;

public:
    GgafCore::LinearOctree* _pLinearOctree;
    OctreeRounder* _pLinearOctreeHitCheckRounder;
    GgafCore::LinearQuadtree* _pLinearQuadtree;
    QuadtreeRounder* _pLinearQuadtreeHitCheckRounder;

    GgafCore::LinearQuadtree* _pLinearQuadtree_b;
    QuadtreeRounder_b* _pLinearQuadtreeHitCheckRounder_b;

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::LinearOctree* getLinearOctree() {
#ifdef MY_DEBUG
        if (_pLinearOctree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearOctree() 八分木は作成されていません。\n"
                    "IS_HIT_CHECK_3D プロパティ true にしてください。\n"
                    "現在のIS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctree;
    }

    inline OctreeRounder* getLinearOctreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearOctreeHitCheckRounder == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearOctreeHitCheckRounder() 八分木は作成されていません。\n"
                    "IS_HIT_CHECK_3D プロパティ true にしてください。\n"
                    "現在のIS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctreeHitCheckRounder;
    }

    inline GgafCore::LinearQuadtree* getLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pLinearQuadtree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearQuadtree() 四分木は作成されていません。 IS_HIT_CHECK_2D プロパティ true にしてください。現在のIS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtree;
    }

    inline QuadtreeRounder* getLinearQuadtreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearQuadtreeHitCheckRounder == nullptr) {
            throwCriticalException("DefaultSpacetime::_pLinearQuadtreeHitCheckRounder() 四分木は作成されていません。 IS_HIT_CHECK_2D プロパティ true にしてください。現在のIS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtreeHitCheckRounder;
    }

    inline GgafCore::LinearQuadtree* getLinearQuadtree_b() {
#ifdef MY_DEBUG
        if (_pLinearQuadtree_b == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearQuadtree_b() 四分木は作成されていません。");
        }
#endif
        return _pLinearQuadtree_b;
    }

    inline QuadtreeRounder* getLinearQuadtreeHitCheckRounder_b() {
#ifdef MY_DEBUG
        if (_pLinearQuadtreeHitCheckRounder_b == nullptr) {
            throwCriticalException("DefaultSpacetime::_pLinearQuadtreeHitCheckRounder_b() 四分木は作成されていません。");
        }
#endif
        return _pLinearQuadtreeHitCheckRounder_b;
    }

    virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

    virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);


    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAF_LIB_DEFAULTSPACETIME_H_*/
