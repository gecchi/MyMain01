#ifndef OPTIONMAGIC_H_
#define OPTIONMAGIC_H_
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

namespace VioletVreath {

/**
 * ���@�u�I�v�V�����v .
 * @version 1.00
 * @since 2009/05/20
 * @author Masatoshi Tsuge
 */
class OptionMagic : public Magic {

public:
    GgafDxCore::GgafDxDrawableActor** papEffect_;
//    int old_level_;
    OptionMagic(const char* prm_name, int* prm_pMP);

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

    void turnoffOptionEffect();

    virtual ~OptionMagic();
};

}
#endif /*OPTIONMAGIC_H_*/
