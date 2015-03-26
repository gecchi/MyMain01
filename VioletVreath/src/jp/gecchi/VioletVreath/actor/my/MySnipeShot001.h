#ifndef MYSNIPESHOT001_H_
#define MYSNIPESHOT001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"

namespace VioletVreath {

/**
 * ���@�X�i�C�v�V���b�g001 .
 * @version 1.00
 * @since 2014/13/06
 * @author Masatoshi Tsuge
 */
class MySnipeShot001 : public GgafLib::SingleLaser {

public:
    MySnipeShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

//    void drawHitArea() override;

    virtual ~MySnipeShot001();
};

}
#endif /*MYSNIPESHOT001_H_*/
