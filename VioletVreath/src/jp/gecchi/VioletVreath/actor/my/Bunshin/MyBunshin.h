#ifndef MYBUNSHIN_H_
#define MYBUNSHIN_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"


namespace VioletVreath {

//class MyBunshin : public GgafLib::DefaultMorphMeshActor {
class MyBunshin : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_FIRE_LASER  ,
        SE_FIRE_SHOT   ,
        SE_FIRE_TORPEDO,
    };

    /** [r]ショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepo_MyBunshinShot_;
    /** [r]スナイプショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepo_MySnipeBunshinShot_;

public:
    MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processChangeGeoFinal() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyBunshin();

    void adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame);

};

}
#endif /*MYBUNSHIN_H_*/

