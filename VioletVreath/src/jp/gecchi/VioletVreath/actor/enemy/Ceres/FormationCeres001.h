#ifndef FORMATIONCERES001_H_
#define FORMATIONCERES001_H_
namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 */
class FormationCeres001 : public GgafLib::TreeFormation {

public:
    FormationCeres001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationCeres001();
};

}
#endif /*FORMATIONCERES001_H_*/
