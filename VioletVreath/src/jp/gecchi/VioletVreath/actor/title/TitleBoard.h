#ifndef TITLEBOARD_H_
#define TITLEBOARD_H_
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"


namespace VioletVreath {

/**
 * �^�C�g���� .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class TitleBoard : public GgafLib::DefaultBoardSetActor {

public:
    TitleBoard(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processDraw() override;

    virtual ~TitleBoard();
};

}
#endif /*TITLEBOARD_H_*/

