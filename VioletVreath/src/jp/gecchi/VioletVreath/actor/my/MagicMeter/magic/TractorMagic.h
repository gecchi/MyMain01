#ifndef TRACTORMAGIC_H_
#define TRACTORMAGIC_H_
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

namespace VioletVreath {

/**
 * 魔法「アイテム引き寄せ」 .
 * @version 1.00
 * @since 2011/02/15
 * @author Masatoshi Tsuge
 */
class TractorMagic : public Magic {
public:
    /** TractorMagic効果持続中はtrue */
    bool is_tracting_;

    TractorMagic(const char* prm_name, int* prm_pMP);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override;
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) override;
    virtual void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) override;

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override;
    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) override;
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) override;

    virtual void processEffectBegin(int prm_last_level, int prm_now_level) override;
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) override;
    virtual void processEffectFinish(int prm_justbefore_level) override;

    virtual ~TractorMagic();
};

}
#endif /*TRACTORMAGIC_H_*/
