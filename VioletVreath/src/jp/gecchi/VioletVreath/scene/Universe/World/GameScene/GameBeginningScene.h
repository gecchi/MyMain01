#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"


namespace VioletVreath {

/**
 * ゲーム開始シーンクラス .
 * ゲームが行なわれている場面と言っても、ゲーム開始中の場面もありました。
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameBeginningScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT       ,
        PROG_SELECT_MODE,
        PROG_DECIDE     ,
        PROG_FINISH     ,
        PROG_BANPEI,
    };

    LabelGecchi16Font* pLabel01_;
    LabelGecchi16Font* pLabel02_;

    int selected_stage_;

public:
    GameBeginningScene(const char* prm_name);
    void onReset() override;
//    void ready() override;

    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    virtual ~GameBeginningScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
