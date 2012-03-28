#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_

namespace VioletVreath {

/**
 * ゲーム開始シーンクラス .
 * ゲームが行なわれている場面と言っても、ゲーム開始中の場面もありました。
 */
class GameBeginningScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1   ,
        PROG_SELECT_MODE,
        PROG_DECIDE     ,
        PROG_FINISH     ,
    };

    LabelGecchi16Font* pLabel01_;
    LabelGecchi16Font* pLabel02_;

    int selected_stage_;

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
