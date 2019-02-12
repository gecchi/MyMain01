#ifndef MYBUNSHINSHOT001_H_
#define MYBUNSHINSHOT001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * ���g�̃V���b�g001 .
 * @version 1.00
 * @since 2015/04/21
 * @author Masatoshi Tsuge
 */
class MyBunshinShot001 : public GgafLib::SingleLaser {

public:
    MyBunshinShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

//    void drawHitArea() override;

    virtual ~MyBunshinShot001();
};

}
#endif /*MYBUNSHINSHOT001_H_*/

