#ifndef DEFAULTBOARDSETEFFECTACTOR_H_
#define DEFAULTBOARDSETEFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultBoardSetTestActor : public GgafLib::DefaultBoardSetActor {

public:
    DefaultBoardSetTestActor(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    virtual ~DefaultBoardSetTestActor();
};

}
#endif /*DEFAULTBOARDSETEFFECTACTOR_H_*/

