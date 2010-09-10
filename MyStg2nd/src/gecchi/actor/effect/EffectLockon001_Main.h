#ifndef EFFECTLOCKON001_MAIN_H_
#define EFFECTLOCKON001_MAIN_H_
namespace MyStg2nd {

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001_Main : public EffectLockon001 {

public:

    EffectLockon001_Main(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~EffectLockon001_Main();
};

}
#endif /*EFFECTLOCKON001_MAIN_H_*/

