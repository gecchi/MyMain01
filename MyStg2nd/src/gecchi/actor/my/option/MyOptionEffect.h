#ifndef MYOPTIONEFFECT_H_
#define MYOPTIONEFFECT_H_
namespace MyStg2nd {


//class MyOptionEffect : public GgafDx9LibStg::DefaultMorphMeshActor {
class MyOptionEffect : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    /** 親オプション */
    MyOption* _pMyOption;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pMyOption 親のオプション
     * @return
     */
    MyOptionEffect(const char* prm_name, MyOption* prm_pMyOption);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processPreDraw() override;

    void processFinal() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOptionEffect();

};

}
#endif /*MYOPTIONEFFECT_H_*/

