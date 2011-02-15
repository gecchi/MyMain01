#ifndef GAMEPRETITLESCENE_H_
#define GAMEPRETITLESCENE_H_

#define GAMEPRETITLE_SCENE_PROG_INIT          1
#define GAMEPRETITLE_SCENE_PROG_EXEC     2
#define GAMEPRETITLE_SCENE_PROG_FINISH        4

namespace MyStg2nd {


/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GamePreTitleScene : public GgafDx9LibStg::DefaultScene {

public:

    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;
    TitleBoard* _pTitleBoard;

    GamePreTitleScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~GamePreTitleScene();
};

}
#endif /*GAMEPRETITLESCENE_H_*/
