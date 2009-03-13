#ifndef BACKGROUND01BOARD_H_
#define BACKGROUND01BOARD_H_
namespace MyStg2nd {

class BackGround01Board : public GgafDx9Core::GgafDx9TransformedActor {

    BackGroundChipBoard** _papChipBoard;

public:
    BackGround01Board(const char* prm_name, const char* prm_dummy);

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        //�Ŕw�ʁ������΂�ŏ��ɕ`��
        GgafDx9Core::GgafDx9World::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL - 1, this);
    }

    virtual void processDrawTerminate() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
        return false;
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    void processDrawMain();

    virtual ~BackGround01Board();
};

}
#endif /*BACKGROUND01BOARD_H_*/

