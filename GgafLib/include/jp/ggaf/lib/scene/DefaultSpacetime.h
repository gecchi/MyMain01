#ifndef GGAF_LIB_DEFAULTSPACETIME_H_
#define GGAF_LIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/core/util/lineartree/LinearOctreeRounder.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

typedef GgafCore::LinearOctree<GgafCore::Actor> WorldOctree;
typedef GgafCore::LinearOctreeRounder<GgafCore::Actor> WorldOctreeRounder;
typedef GgafCore::LinearQuadtree<GgafCore::Actor> WorldQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> WorldQuadtreeRounder;

typedef GgafCore::LinearQuadtree<GgafCore::Actor> ViewQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Actor> ViewQuadtreeRounder;

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
    static WorldOctree* _pWorldOctree;
    static WorldOctreeRounder* _pWorldOctreeRounder;
    static WorldQuadtree* _pWorldQuadtree;
    static WorldQuadtreeRounder* _pWorldQuadtreeRounder;

    static ViewQuadtree* _pViewQuadtree;
    static ViewQuadtreeRounder* _pViewQuadtreeRounder;
#ifdef MY_DEBUG
    /** processSettlementBehavior() 実行済み判定 */
    bool _is_done_processSettlementBehavior;
#endif

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    /**
     * ワールド座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
     * ３次元（８分木） or ２次元（４分木）
     * processJudgement() で呼ぶ必要あり。（processSettlementBehavior() で ツリーに登録している為）<BR>
     * @param prm_kind_groupA アクター種別Aグループ
     * @param prm_kind_groupB アクター種別Bグループ
     */
    virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

    /**
     * ビュー座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
     * processJudgement() で呼ぶ必要あり。（processSettlementBehavior() で ツリーに登録している為）<BR>
     * @param prm_kind_groupA アクター種別Aグループ
     * @param prm_kind_groupB アクター種別Bグループ
     */
    virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);


    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processFinal() override;

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAF_LIB_DEFAULTSPACETIME_H_*/
