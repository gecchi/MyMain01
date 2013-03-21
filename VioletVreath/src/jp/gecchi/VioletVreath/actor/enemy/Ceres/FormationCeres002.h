#ifndef FORMATIONCERES002_H_
#define FORMATIONCERES002_H_
namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 */
class FormationCeres002 : public GgafLib::TreeFormation {

public:
    FormationCeres002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationCeres002();
};

}
#endif /*FORMATIONCERES002_H_*/
