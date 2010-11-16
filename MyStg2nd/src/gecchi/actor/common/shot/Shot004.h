#ifndef SHOT004_H_
#define SHOT004_H_
namespace MyStg2nd {

/**
 * 汎用弾004(小) .
 * 破壊不可能で等速直線移動の小さなレーザー片<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot004 : public GgafDx9LibStg::SingleLaser {
public:

    Shot004(const char* prm_name);


    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void drawHitArea() override;

    virtual ~Shot004();
};

}
#endif /*SHOT004_H_*/

