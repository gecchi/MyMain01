#ifndef LASERMAGIC_H_
#define LASERMAGIC_H_
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

namespace VioletVreath {

/**
 * 魔法「レーザー」 .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class LaserMagic : public Magic {

public:
    EffectLaserMagic* pEffect_;

public:
    LaserMagic(const char* prm_name, int* prm_pMP);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override;
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) override;
    virtual void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) override;

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override;
    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) override;
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) override;

    virtual void processEffectBegin(int prm_last_level, int prm_now_level) override;
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) override;
    virtual void processEffectFinish(int prm_justbefore_level) override;

    virtual ~LaserMagic();
};

}
#endif /*LASERMAGIC_H_*/
