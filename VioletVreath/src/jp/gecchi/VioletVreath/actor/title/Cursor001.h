#ifndef CURSOR001_H_
#define CURSOR001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"



namespace VioletVreath {

/**
 * ƒJ[ƒ\ƒ‹‚»‚Ì‚P .
 * @version 1.00
 * @since 2011/04/07
 * @author Masatoshi Tsuge
 */
class Cursor001 : public GgafLib::DefaultBoardActor {
public:

public:
    Cursor001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void moveTo(coord tx, coord ty);

    void moveTo(GgafDx::GeometricActor* prm_pActor) {
        moveTo(prm_pActor->_x, prm_pActor->_y);
    }
    virtual ~Cursor001();
};

}
#endif /*CURSOR001_H_*/

