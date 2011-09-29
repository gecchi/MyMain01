#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_

namespace MyStg2nd {

/**
 * ゲーム開始シーンクラス .
 * ゲームが行なわれている場面と言っても、ゲーム開始中の場面もありました。
 */
class GameBeginningScene : public GgafLib::DefaultScene {

public:
    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;

    int _selected_stage;

    GameBeginningScene(const char* prm_name);
    void onReset() override;
//    void ready() override;

    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~GameBeginningScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
