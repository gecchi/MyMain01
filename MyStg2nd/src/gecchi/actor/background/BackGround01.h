#ifndef BACKGROUND01_H_
#define BACKGROUND01_H_
namespace MyStg2nd {

class BackGround01 : public GgafDx9Core::GgafDx9GeometricActor {

    BackGroundChipBoard*** _papapChipBoard;
//    BackGroundStar001** _papBackGroundStar001;

public:

    float _chip_width;
    float _chip_height;

    float _base_x[4];
    float _base_y[4];
    BackGround01(const char* prm_name, const char* prm_dummy);



    virtual void processPreDraw();



    virtual void processHappen(int prm_no) {
    }


    virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
        return false;
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize();

    void processJudgement() {
    }

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processDraw() {
    }

    void processAfterDraw() {
    }

    virtual void processFinal() {
    }

    virtual ~BackGround01();
};

}
#endif /*BACKGROUND01BOARD_H_*/

