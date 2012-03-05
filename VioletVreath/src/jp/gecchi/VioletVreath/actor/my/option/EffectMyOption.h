#ifndef MYOPTIONEFFECT_H_
#define EFFECTMYOPTION_H_
namespace VioletVreath {


//class EffectMyOption : public GgafLib::DefaultMorphMeshActor {
class EffectMyOption : public GgafLib::DefaultMeshSetActor {

public:
    /** 親オプション */
    MyOption* pMyOption_;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pMyOption 親のオプション
     * @return
     */
    EffectMyOption(const char* prm_name, MyOption* prm_pMyOption);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processPreDraw() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EffectMyOption();

};

}
#endif /*EFFECTMYOPTION_H_*/

