#ifndef BACKGROUNDSTAR001_H_
#define BACKGROUNDSTAR001_H_
namespace MyStg2nd {

/**
 * �w�i��
 */
class BackGroundStar001 : public GgafDx9Core::GgafDx9MeshActor {

private:

public:

    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g��
     */
    BackGroundStar001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void processBehavior() override;

    void processPreJudgement() override;

    void processJudgement() override;

    void processPreDraw() override;

    void processDraw() override;

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    int isOffscreen() override {
        return false;
    }

    bool isOutOfGameSpace() override {
        return false;
    }

    virtual ~BackGroundStar001();

};

}

#endif /*BACKGROUNDSTAR001_H_*/

