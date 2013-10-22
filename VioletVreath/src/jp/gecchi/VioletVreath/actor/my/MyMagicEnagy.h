#ifndef MYMAGICENAGY_H_
#define MYMAGICENAGY_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * MPÉGÉlÉãÉMÅ[ .
 * @version 1.00
 * @since 2013/10/22
 * @author Masatoshi Tsuge
 */
class MyMagicEnagy : public GgafLib::DefaultMeshActor {

public:
   MyMagicEnagy(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~MyMagicEnagy();
};

}
#endif /*MYMAGICENAGY_H_*/

