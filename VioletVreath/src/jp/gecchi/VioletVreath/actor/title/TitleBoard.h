#ifndef TITLEBOARD_H_
#define TITLEBOARD_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassBoardActor.h"


namespace VioletVreath {

/**
 * ƒ^ƒCƒgƒ‹”Â .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class TitleBoard : public GgafLib::DefaultMassBoardActor {

protected:
    VERTEX_instancedata aInstancedata_title_[2];

public:
    TitleBoard(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processDraw() override;

    virtual ~TitleBoard();
};

}
#endif /*TITLEBOARD_H_*/

