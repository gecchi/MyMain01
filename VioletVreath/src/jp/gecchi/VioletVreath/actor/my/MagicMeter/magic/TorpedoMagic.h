#ifndef TORPEDOMAGIC_H_
#define TORPEDOMAGIC_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

namespace VioletVreath {

/**
 * ñÇñ@ÅuãõóãÅv .
 * @version 1.00
 * @since 2011/01/16
 * @author Masatoshi Tsuge
 */
class TorpedoMagic : public Magic {

public:
    EffectTorpedoMagic* pEffect_;

public:
    TorpedoMagic(const char* prm_name, int* prm_pMP);

    void onReset() override;

    void processCastBegin(int prm_now_level, int prm_new_level) override;
    void processCastingBehavior(int prm_now_level, int prm_new_level) override;
    void processCastingCancel(int prm_now_level) override;
    void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) override;

    void processInvokeBegin(int prm_now_level, int prm_new_level) override;
    void processInvokingBehavior(int prm_now_level, int prm_new_level) override;
    void processInvokingCancel(int prm_now_level) override;
    void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) override;

    void processEffectBegin(int prm_last_level, int prm_now_level) override;
    void processEffectingBehavior(int prm_last_level, int prm_now_level) override;

    virtual ~TorpedoMagic();
};

}
#endif /*LASERMAGIC_H_*/
