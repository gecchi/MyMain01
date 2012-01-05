#ifndef GAMETITLESCENE_H_
#define GAMETITLESCENE_H_

namespace MyStg2nd {

/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameTitleScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1 ,
        PROG_TITLE    ,
        PROG_SELECT   ,
        PROG_GAMESTART,
        PROG_FINISH   ,
    };

    GgafDxCore::GgafDxSeConnection* _pSeCon_exec;

    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;

    MenuBoardTitle* _pMenu;

    TitleBoard* _pTitleBoard;

    int _max_menu_item;
    int _active_item;
    frame _frame_of_noinput;

    GameTitleScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~GameTitleScene();
};

}
#endif /*GAMETITLESCENE_H_*/
