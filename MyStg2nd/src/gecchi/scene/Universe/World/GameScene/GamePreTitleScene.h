#ifndef GAMEPRETITLESCENE_H_
#define GAMEPRETITLESCENE_H_
namespace MyStg2nd {

/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GamePreTitleScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_EXEC    ,
        PROG_FINISH  ,
    };


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
