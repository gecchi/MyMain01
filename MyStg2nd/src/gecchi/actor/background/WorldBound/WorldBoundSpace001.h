#ifndef WorldBoundSpace001_H_
#define WorldBoundSpace001_H_
namespace MyStg2nd {

/**
 * 世界空間 .
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundSpace001 : public GgafDx9LibStg::WorldBoundActor {

public:

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBoundSpace001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;


    void processJudgement() override;


    void processFinal() override {
    }

    virtual ~WorldBoundSpace001();
};

}
#endif /*WorldBoundSpace001_H_*/

