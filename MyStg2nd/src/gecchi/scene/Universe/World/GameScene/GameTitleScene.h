#ifndef GAMETITLESCENE_H_
#define GAMETITLESCENE_H_

#define GAMETITLE_SCENE_PROG_INIT          1
#define GAMETITLE_SCENE_PROG_TITLE         3
#define GAMETITLE_SCENE_PROG_SELECT        4
#define GAMETITLE_SCENE_PROG_GAMESTART     5
#define GAMETITLE_SCENE_PROG_FINISH        6

#define GAMETITLE_TIMEOUT 240

namespace MyStg2nd {


/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameTitleScene : public GgafDx9LibStg::DefaultScene {

public:
    GgafDx9Core::GgafDx9SeConnection* _pSeCon_exec;

    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;

    LabelGecchi16Font** _papStringItem;
    Cursor001* _pCursor001;

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
