#ifndef MYTORPEDO_H_
#define MYTORPEDO_H_

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
class MyTorpedo : public GgafLib::DefaultMeshSetActor {

public:
    /** [r]親アクターとなる魚雷コンローラー */
    MyTorpedoController* pOptionTorpedoCtrler_;
    /** [r]魚雷の移動軌跡エフェクトの数 */
    int length_TailEffect_;
    /** [r]魚雷の移動軌跡エフェクトのデポジトリ */
    GgafLib::LaserChipDepository* pTailEffectDepository_;
    /** [r]魚雷発射時の座標 */
    int begin_X_,begin_Y_,begin_Z_;
    /** [r]到達目標のアクター。nullptrの場合は自機前方のゲーム領域境界点を目標とする仕組み */
    GgafDxCore::GgafDxGeometricActor* pTarget_;

    int move_section_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pOptionTorpedoController 親アクターとなる魚雷コンローラー .
     * @return
     */
    MyTorpedo(const char* prm_name, MyTorpedoController* prm_pOptionTorpedoController);

    void onCreateModel() override {
    }

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyTorpedo();
};

}
#endif /*MYTORPEDO*/

