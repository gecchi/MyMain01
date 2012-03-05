#ifndef GAMEPAUSESCENE_H_
#define GAMEPAUSESCENE_H_

namespace VioletVreath {

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

    GgafDxCore::GgafDxSeConnection* pSeCon_exec_;

    LabelGecchi16Font* pMsgLabel01_;
    LabelGecchi16Font* pMsgLabel02_;
    LabelGecchi16Font** papMenuItemLabel_;
    Cursor001* pCursor001_;

    MenuBoardPause* pMenuBoardPause_;


    int max_menu_item_;
    int active_item_;
    frame frame_of_noinput_;

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
