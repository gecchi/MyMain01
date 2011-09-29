#ifndef MYOPTIONEFFECT_H_
#define EFFECTMYOPTION_H_
namespace MyStg2nd {


//class EffectMyOption : public GgafLib::DefaultMorphMeshActor {
class EffectMyOption : public GgafLib::DefaultMeshSetActor {

public:
    /** �e�I�v�V���� */
    MyOption* _pMyOption;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pMyOption �e�̃I�v�V����
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

    void processFinal() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EffectMyOption();

};

}
#endif /*EFFECTMYOPTION_H_*/

