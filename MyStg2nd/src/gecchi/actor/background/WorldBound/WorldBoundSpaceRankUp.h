#ifndef WORLDBOUNDSPACERANKUP_H_
#define WORLDBOUNDSPACERANKUP_H_
namespace MyStg2nd {

/**
 * �ʉ߃X�e�[�W�̐��E��� .
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class WorldBoundSpaceRankUp : public GgafLib::WorldBoundActor {

public:

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    WorldBoundSpaceRankUp(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;


    void processJudgement() override;


    void processFinal() override {
    }

    virtual ~WorldBoundSpaceRankUp();
};

}
#endif /*WORLDBOUNDSPACERANKUP_H_*/
