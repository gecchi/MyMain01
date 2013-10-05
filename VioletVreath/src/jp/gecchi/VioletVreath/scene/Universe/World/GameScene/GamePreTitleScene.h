#ifndef GAMEPRETITLESCENE_H_
#define GAMEPRETITLESCENE_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * �^�C�g���V�[���N���X .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GamePreTitleScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT   ,
        PROG_EXEC   ,
        PROG_FINISH ,
        _BANPEI_,
    };


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
