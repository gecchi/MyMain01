#ifndef PARALLELCURVETESTSCENE_H_
#define PARALLELCURVETESTSCENE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace Mogera {

DECLARE_EVENT_VAL(EVENT_START_MOVING);

class ParallelCurveTestScene : public GgafLib::DefaultScene {

public:
    PointSpriteTest* pTest_;
    GgafCore::ActorDepository* pDepoBox_;
    EnemyIdaBase* pActor_;
public:
    ParallelCurveTestScene(const char* prm_name);
    void pset(coord x, coord y, coord z);
    void psetAs(GgafDx::GeometricActor* pActor);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~ParallelCurveTestScene();
};

}
#endif /*PARALLELCURVETESTSCENE_H_*/
