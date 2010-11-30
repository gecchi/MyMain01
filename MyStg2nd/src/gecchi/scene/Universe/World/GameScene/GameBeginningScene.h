#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_


#define GAMEBEGINNING_SCENE_PROG_INIT   1
#define GAMEBEGINNING_SCENE_PROG_SELECT_MODE  2
#define GAMEBEGINNING_SCENE_PROG_DECIDE 3
#define GAMEBEGINNING_SCENE_PROG_FINISH 4

namespace MyStg2nd {

/**
 * ゲーム開始シーンクラス .
 * ゲームが行なわれている場面と言っても、ゲーム開始中の場面もありました。
 */
class GameBeginningScene : public GgafDx9LibStg::DefaultScene {

public:
    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;

    int _selected_stage;

    GameBeginningScene(const char* prm_name);
    void processReset() override;
//    void ready() override;

    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~GameBeginningScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
