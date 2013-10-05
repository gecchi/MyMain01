#ifndef GAMETITLESCENE_H_
#define GAMETITLESCENE_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"


namespace VioletVreath {

/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameTitleScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT     ,
        PROG_TITLE    ,
        PROG_SELECT   ,
        PROG_GAMESTART,
        PROG_FINISH   ,
        _BANPEI_,
    };

    GgafDxCore::GgafDxSeConnection* pSeConnection_exec_;

    LabelGecchi16Font* pLabel01_;
    LabelGecchi16Font* pLabel02_;

    MenuBoardTitle* pMenu_;

    TitleBoard* pTitleBoard_;

    WorldBoundTitle* pWorldBound_;
    HoshiBoshiTitle* pHoshiBoshi_;
    int active_item_;
    frame frame_of_noinput_;

public:
   GameTitleScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    virtual ~GameTitleScene();
};

}
#endif /*GAMETITLESCENE_H_*/
