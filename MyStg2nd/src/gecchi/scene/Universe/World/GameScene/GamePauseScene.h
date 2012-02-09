#ifndef GAMEPAUSESCENE_H_
#define GAMEPAUSESCENE_H_

namespace MyStg2nd {

/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GamePauseScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1 ,
        PROG_SELECT   ,
        PROG_CONFIRM  ,
        PROG_FINISH   ,
    };

    GgafDxCore::GgafDxSeConnection* _pSeCon_exec;

    LabelGecchi16Font* _pMsgLabel01;
    LabelGecchi16Font* _pMsgLabel02;
    LabelGecchi16Font** _papMenuItemLabel;
    Cursor001* _pCursor001;

    MenuBoardPause* _pMenuBoardPause;


    int _max_menu_item;
    int _active_item;
    frame _frame_of_noinput;

    GamePauseScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void onInactive() override;
    virtual ~GamePauseScene();
};

}
#endif /*GAMETITLESCENE_H_*/
