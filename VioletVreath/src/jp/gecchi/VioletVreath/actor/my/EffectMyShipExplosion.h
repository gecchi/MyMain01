#ifndef EFFECTMYSHIPEXPLOSION_H_
#define EFFECTMYSHIPEXPLOSION_H_
namespace VioletVreath {

/**
 * é©ã@îöî≠
 * @version 1.00
 * @since 2010/11/10
 * @author Masatoshi Tsuge
 */
class EffectMyShipExplosion : public GgafLib::DefaultSpriteSetActor {

public:
    EffectMyShipExplosion(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior() override;


    void onActive() override;

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processJudgement() override;

    virtual ~EffectMyShipExplosion();
};

}
#endif /*EFFECTMYSHIPEXPLOSION_H_*/

