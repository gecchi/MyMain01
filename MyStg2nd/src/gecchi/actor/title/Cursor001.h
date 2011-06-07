#ifndef CURSOR001_H_
#define CURSOR001_H_


namespace MyStg2nd {

/**
 * ƒJ[ƒ\ƒ‹‚»‚Ì‚P .
 * @version 1.00
 * @since 2011/04/07
 * @author Masatoshi Tsuge
 */
class Cursor001 : public GgafDx9LibStg::DefaultBoardActor {

public:
    Cursor001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void moveTo(int X, int Y);

    void moveTo(GgafDx9Core::GgafDx9GeometricActor* prm_pActor) {
        moveTo(prm_pActor->_X, prm_pActor->_Y);
    }
    virtual ~Cursor001();
};

}
#endif /*CURSOR001_H_*/

