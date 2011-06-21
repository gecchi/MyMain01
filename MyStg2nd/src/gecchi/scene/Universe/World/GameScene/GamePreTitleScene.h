#ifndef GAMEPRETITLESCENE_H_
#define GAMEPRETITLESCENE_H_

#define GAMEPRETITLESCENE_PROG_INIT     1
#define GAMEPRETITLESCENE_PROG_EXEC     2
#define GAMEPRETITLESCENE_PROG_FINISH   3

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
