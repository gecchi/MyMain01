#ifndef GAMETITLESCENE_H_
#define GAMETITLESCENE_H_

namespace VioletVreath {

/**
 * �^�C�g���V�[���N���X .
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

    GgafDxCore::GgafDxSeConnection* pSeCon_exec_;

    LabelGecchi16Font* pStringBoard01_;
    LabelGecchi16Font* pStringBoard02_;

    MenuBoardTitle* pMenu_;

    TitleBoard* pTitleBoard_;

    WorldBoundTitle* pWorldBound_;
    HoshiBoshiTitle* pHoshiBoshi_;
    int max_menu_item_;
    int active_item_;
    frame frame_of_noinput_;

    GameTitleScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    virtual ~GameTitleScene();
};

}
#endif /*GAMETITLESCENE_H_*/