#ifndef MYTORPEDO_H_
#define MYTORPEDO_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#define MyTorpedo_IN_FIRE 1
#define MyTorpedo_RELEASE 2
namespace VioletVreath {

/**
 * 魚雷 .
 * オプションが保持しているロックオンの敵めがけて飛んでゆきます。
 * @version 1.00
 * @since 2010/09/21
 * @author Masatoshi Tsuge
 */
class MyTorpedo : public VvMyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** [r]親アクターとなる魚雷コンローラー */
    MyTorpedoController* pTorpedoCtrler_;
    /** [r]魚雷の移動軌跡エフェクトの数 */
    int length_TailEffect_;
    /** [r]魚雷の移動軌跡エフェクトのデポジトリ */
    GgafLib::LaserChipDepository* pTailEffectDepository_;
    /** [r]魚雷発射時の座標 */
    int begin_x_,begin_y_,begin_z_;
    /** [r]到達目標のアクター。nullptrの場合は自機前方のゲーム領域境界点を目標とする仕組み */
    GgafDx::GeometricActor* pTarget_;

    int move_section_;

    angle trz_,try_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pTorpedoController 親アクターとなる魚雷コンローラー .
     * @return
     */
    MyTorpedo(const char* prm_name, MyTorpedoController* prm_pTorpedoController);

    void onCreateModel() override {
    }

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    virtual ~MyTorpedo();
};

}
#endif /*MYTORPEDO*/

