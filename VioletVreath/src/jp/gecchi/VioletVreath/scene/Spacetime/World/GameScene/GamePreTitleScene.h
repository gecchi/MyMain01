#ifndef GAMEPRETITLESCENE_H_
#define GAMEPRETITLESCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GamePreTitleScene : public VvScene<GgafLib::DefaultScene> {

public:
    LabelGecchi16Font* pLabel01_;
    LabelGecchi16Font* pLabel02_;
    TitleBoard* pTitleBoard_;

//    SpriteLabelTest** papSpriteLabel_;

public:
    GamePreTitleScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    virtual ~GamePreTitleScene();
};

}
#endif /*GAMEPRETITLESCENE_H_*/
