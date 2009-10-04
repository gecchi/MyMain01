#ifndef BACKGROUNDSTAR001_H_
#define BACKGROUNDSTAR001_H_
namespace MyStg2nd {

/**
 * 背景星
 */
class BackGroundStar001 : public GgafDx9Core::GgafDx9MeshActor {

private:

public:

    /**
     * コンストラクタ
     * @param prm_name オブジェクト名
     * @param prm_model モデル名
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

    int wasGone() {
        return false;
    }

    virtual ~BackGroundStar001();

};

}

#endif /*BACKGROUNDSTAR001_H_*/

