#ifndef EFFECTWORMHOLE001_H_
#define EFFECTWORMHOLE001_H_
namespace MyStg2nd {

/**
 * ÉèÅ[ÉÄÉzÅ[ÉãÇªÇÃÇP.
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class EffectWormhole001 : public EffectWormhole {

public:
    EffectWormhole001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectWormhole001();
};

}
#endif /*EFFECTWORMHOLE001_H_*/

