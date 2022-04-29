#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "../World.h"
#include "jp/gecchi/VioletVreath/God.h"


namespace VioletVreath {

#define pGAME_SCENE (pGOD->getSpacetime()->getWorld()->pGameScene_)

/**
 * ゲームシーンクラス .
 * 『この世(Spacetime)の、とある世界(World)で、ゲームが行なわれている場面(GameScene)がありました。』<BR>
 * といった概念の元に設計を行いました。<BR>
 * 本クラスは、ゲームの全体的な振る舞いを実装しています。<BR>
 * 主に、子シーンの切り替え等を行います。<BR>
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameScene : public VvScene<GgafLib::DefaultScene> {

public:
    enum {
        PHASE_INIT      ,
        PHASE_PRE_TITLE ,
        PHASE_TITLE     ,
        PHASE_DEMO      ,
        PHASE_BEGINNING ,
        PHASE_MAIN      ,
        PHASE_ENDING    ,
        PHASE_GAME_OVER ,
        PHASE_FINISH    ,
        PHASE_BANPEI,
    };
    enum {
        BGM_DEMO,
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

    GgafLib::OctreeRounder* pHitCheckRounder_;
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
