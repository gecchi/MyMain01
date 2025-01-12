#ifndef GGAF_LIB_DEFAULTSPACETIME_H_
#define GGAF_LIB_DEFAULTSPACETIME_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/core/util/lineartree/LinearOctreeRounder.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace GgafLib {

typedef GgafCore::LinearOctree<GgafCore::Checker> WorldOctree;
typedef GgafCore::LinearOctreeRounder<GgafCore::Checker> WorldOctreeRounder;
typedef GgafCore::LinearQuadtree<GgafCore::Checker> WorldQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Checker> WorldQuadtreeRounder;

typedef GgafCore::LinearQuadtree<GgafCore::Checker> ViewQuadtree;
typedef GgafCore::LinearQuadtreeRounder<GgafCore::Checker> ViewQuadtreeRounder;

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

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);


    virtual DefaultCamera* getCamera() override { //共変の戻り値
        return (DefaultCamera*)_pCamera;
    }

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override {
    }
//実装させる
//    virtual void processHitCheck() override {
//    }

    virtual void processFinal() override;


    /**
      * ワールド座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
      * ３次元（８分木） or ２次元（４分木）
      * processHitCheck() で呼ぶ必要あり。<BR>
      * @param prm_kind_groupA アクター種別Aグループ
      * @param prm_kind_groupB アクター種別Bグループ
      */
     virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

     /**
      * ビュー座標上のアクターの「種別Aグループ 対 種別Bグループ」の ヒットチェック を行う  .
      * processHitCheck() で呼ぶ必要あり。<BR>
      * @param prm_kind_groupA アクター種別Aグループ
      * @param prm_kind_groupB アクター種別Bグループ
      */
     virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAF_LIB_DEFAULTSPACETIME_H_*/
