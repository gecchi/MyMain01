#ifndef WORLDBOUNDSPACE002_H_
#define WORLDBOUNDSPACE002_H_
namespace MyStg2nd {

/**
 * ���E��� .
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundSpace002 : public GgafDx9LibStg::WorldBoundActor {

public:

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    WorldBoundSpace002(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;


    void processJudgement() override;


    void processFinal() override {
    }

    virtual ~WorldBoundSpace002();
};

}
#endif /*WORLDBOUNDSPACE002_H_*/
