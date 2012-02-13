#ifndef WORLDBOUNDSPACE001_H_
#define WORLDBOUNDSPACE001_H_
namespace VioletVreath {

/**
 * 世界空間 .
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundSpace001 : public GgafLib::WorldBoundActor {

public:

//    float _base_u;
//    float _base_v;
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBoundSpace001(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~WorldBoundSpace001();
};

}
#endif /*WORLDBOUNDSPACE001_H_*/

