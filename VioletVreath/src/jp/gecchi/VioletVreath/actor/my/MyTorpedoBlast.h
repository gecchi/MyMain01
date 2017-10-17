#ifndef MYTORPEDOBLAST_H_
#define MYTORPEDOBLAST_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"


#define MyTorpedoBlast_IN_FIRE 1
#define MyTorpedoBlast_RELEASE 2
namespace VioletVreath {

/**
 * �������� .
 * @version 1.00
 * @since 2010/09/22
 * @author Masatoshi Tsuge
 */
class MyTorpedoBlast : public GgafLib::DefaultMeshSetActor {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @return
     */
    MyTorpedoBlast(const char* prm_name);

    void onCreateModel() override {
    }
    void initialize() override;

    void onReset() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyTorpedoBlast();
};

}
#endif /*MYTORPEDO*/

