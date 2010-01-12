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

    void initialize();

    void processBehavior();

    void processPreJudgement();

    void processJudgement();

    void processPreDraw();

    void processDraw();

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    int isOffscreen() {
        return false;
    }

    int isOutOfGameSpace() {
        return false;
    }

    virtual ~BackGroundStar001();

};

}

#endif /*BACKGROUNDSTAR001_H_*/

