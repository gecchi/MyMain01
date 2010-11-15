#ifndef TITLEBOARD_H_
#define TITLEBOARD_H_

#define TITLEBOARD_PROG_INIT     1
#define TITLEBOARD_PROG_ENTRANCE 2
#define TITLEBOARD_PROG_DISP     3


namespace MyStg2nd {

/**
 * ƒ^ƒCƒgƒ‹”Â .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class TitleBoard : public GgafDx9LibStg::DefaultBoardSetActor {

public:
    TitleBoard(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    virtual ~TitleBoard();
};

}
#endif /*TITLEBOARD_H_*/

