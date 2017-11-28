#ifndef GAMEENDINGSCENE_H_
#define GAMEENDINGSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * エンディングシーンクラス .
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameEndingScene : public GgafLib::DefaultScene {

public:
    GameEndingScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~GameEndingScene();
};

}
#endif /*GAMEENDINGSCENE_H_*/
