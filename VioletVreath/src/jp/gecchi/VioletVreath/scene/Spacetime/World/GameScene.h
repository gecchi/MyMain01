#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"

namespace VioletVreath {

#define P_GAME_SCENE (P_GOD->getSpacetime()->getWorld()->pGameScene_)

/**
 * ゲームシーンクラス .
 * 『この世(Spacetime)の、とある世界(World)で、ゲームが行なわれている場面(GameScene)がありました。』<BR>
 * といった概念の元に設計を行いました。<BR>
 * 本クラスは、ゲームの全体的な振る舞いを実装しています。<BR>
 * 主に、サブシーンの切り替え等を行います。<BR>
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameScene : public GgafLib::DefaultScene {

public:

    enum {
        PROG_INIT      ,
        PROG_PRE_TITLE ,
        PROG_TITLE     ,
        PROG_DEMO      ,
        PROG_BEGINNING ,
        PROG_MAIN      ,
        PROG_ENDING    ,
        PROG_GAME_OVER ,
        PROG_FINISH    ,
        PROG_BANPEI,
    };


    CommonScene* pCommonScene_;
    MyShipScene* pMyShipScene_;

    MenuBoardPause* pMenuBoardPause_;
    /** GameMain、或いは、Demoの配下へ移動される */
    StageWorld* pStageWorld_;

    /** コマ送りフラグ */
    bool is_frame_advance_;
    /** １フレーム前、GameMainSceneが一時停止状態だったかどうか */
    bool was_paused_flg_GameMainScene_prev_frame_;

public:
    GameScene(const char* prm_name);

    void onReset() override;
    void initialize() override;
    void onActive() override;

    void processBehavior() override;
    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    void pauseGame();

    virtual ~GameScene();

};

}
#endif /*GAMESCENE_H_*/
