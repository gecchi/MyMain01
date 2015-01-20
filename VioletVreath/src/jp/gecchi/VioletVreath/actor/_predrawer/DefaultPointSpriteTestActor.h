#ifndef DEFAULTPOINTSPRITEEFFECTACTOR_H_
#define DEFAULTPOINTSPRITEEFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultPointSpriteTestActor : public GgafLib::DefaultPointSpriteActor {

public:

    DefaultPointSpriteTestActor(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

//    void processPreDraw() override;

    int isOutOfView() override;

    bool isOutOfUniverse() const override;

    virtual ~DefaultPointSpriteTestActor();
};

}
#endif /*DEFAULTPOINTSPRITEEFFECTACTOR_H_*/

