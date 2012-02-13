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
    MyOptionTorpedoController* _pMyOptionTorpedoController;
    /** [r]魚雷の移動軌跡エフェクトの数 */
    int _length_TailEffect;
    /** [r]魚雷の移動軌跡エフェクトのデポジトリ */
    GgafLib::LaserChipDepository* _pTailEffectDepository;
    /** [r]魚雷発射時の座標 */
    int _begin_X,_begin_Y,_begin_Z;
    /** [r]到達目標のアクター。NULLの場合は自機前方のゲーム領域境界点を目標とする仕組み */
    GgafDxCore::GgafDxGeometricActor* _pTarget;

    int _move_section;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pMyOptionTorpedoController 親アクターとなる魚雷コンローラー .
     * @return
     */
    MyTorpedo(const char* prm_name, MyOptionTorpedoController* prm_pMyOptionTorpedoController);

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

