#ifndef GGAF_LIB_DEFAULTSPACETIME_H_
#define GGAF_LIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/core/util/lineartree/LinearOctreeRounder.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

//typedef GgafCore::LinearOctreeRounder<GgafCore::Actor> WorldOctreeRounder;
//typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> WorldQuadtreeRounder;
//
//typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> ViewQuadtreeRounder;
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

public:
    GgafCore::LinearOctree<GgafCore::Actor>* _pWorldLinearOctree;
    GgafCore::LinearOctreeRounder<GgafCore::Actor>* _pWorldOctreeRounder;
    GgafCore::LinearQuadtree<GgafCore::Actor>* _pWorldLinearQuadtree;
    GgafCore::LinearQuadtreeRounder<GgafCore::Actor>* _pWorldQuadtreeRounder;
    GgafCore::LinearQuadtree<GgafCore::Actor>* _pViewLinearQuadtree;
    GgafCore::LinearQuadtreeRounder<GgafCore::Actor>* _pViewQuadtreeRounder;
#ifdef MY_DEBUG
    /** processPreJudgement() 実行済み判定 */
    bool _is_done_processPreJudgement;
#endif

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::LinearOctree<GgafCore::Actor>* getLinearOctree() {
#ifdef MY_DEBUG
        if (_pWorldLinearOctree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearOctree() 八分木は作成されていません。\n"
                    "IS_HIT_CHECK_3D プロパティ true にしてください。\n"
                    "現在のIS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pWorldLinearOctree;
    }

    inline GgafCore::LinearQuadtree<GgafCore::Actor>* getLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pWorldLinearQuadtree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearQuadtree() 四分木は作成されていません。 IS_HIT_CHECK_2D プロパティ true にしてください。現在のIS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pWorldLinearQuadtree;
    }
    inline GgafCore::LinearQuadtree<GgafCore::Actor>* getViewLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pViewLinearQuadtree == nullptr) {
            throwCriticalException("DefaultSpacetime::getViewLinearQuadtree() 四分木は作成されていません。");
        }
#endif
        return _pViewLinearQuadtree;
    }

    /**
     * ワールド座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
     * ３次元（８分木） or ２次元（４分木）
     * processJudgement() で呼ぶ必要あり。（processPreJudgement() で ツリーに登録している為）<BR>
     * @param prm_kind_groupA アクター種別Aグループ
     * @param prm_kind_groupB アクター種別Bグループ
     */
    virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

    /**
     * ビュー座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
     * processJudgement() で呼ぶ必要あり。（processPreJudgement() で ツリーに登録している為）<BR>
     * @param prm_kind_groupA アクター種別Aグループ
     * @param prm_kind_groupB アクター種別Bグループ
     */
    virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);


    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual void processPreJudgement() override;

    virtual void processFinal() override;

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAF_LIB_DEFAULTSPACETIME_H_*/
