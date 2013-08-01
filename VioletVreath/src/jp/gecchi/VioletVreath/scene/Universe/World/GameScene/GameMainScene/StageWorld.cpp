#include "stdafx.h"
#include "StageWorld.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

StageWorld::StageWorld(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageWorld";
    can_rank_up_ = true;
    pStageCtrler_ = NEW StageController("StageController");
    addSubLast(pStageCtrler_);
    pRankUpStageCtrler_ = NEW RankUpStageController("RankUpStageController");
    addSubLast(pRankUpStageCtrler_);
}

void StageWorld::onReset() {
    _TRACE_("StageWorld::onReset() ");
    _TRACE_("MyShipScene を、スローの影響を与えないために一つ上に引き上げます addSubLast(P_MYSHIP_SCENE->extract()); ");
    P_MYSHIP_SCENE->resetTree();
    P_MYSHIP_SCENE->activateImmed();
    addSubLast(P_MYSHIP_SCENE->extract()); //スローの影響を与えないために一つ上
    pStageCtrler_->setRunFrameOnce(1); //スローなしに
}

void StageWorld::initialize() {
}

void StageWorld::processBehavior() {

    //debug ---->
//#ifdef MY_DEBUG
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_P)) {
        G_RANK += (1.0/G_RANK_R);
        _TRACE_("StageWorld::processBehavior() G_RANK="<<G_RANK<<"/G_RANK_DISP="<<G_RANK_DISP<<"");
    }
//#endif
    //<---- debug
    //ランクアップシーン差し込み
    if (GameGlobal::updateRankUpLebel()) {
        _TRACE_("G_RANKUP_LEVEL アップしました！！→"<<G_RANKUP_LEVEL<<" (G_RANK="<<G_RANK<<"/G_RANK_DISP="<<G_RANK_DISP<<")");
        if (can_rank_up_) {
            _TRACE_("ランクアップシーン差し込みします！");
            pRankUpStageCtrler_->startRunkUpStage(G_RANKUP_LEVEL);
            _TRACE_("P_STAGE_CTRLER をスロー");
            pStageCtrler_->addRunFrameOnce(3); //スロー開始
        } else {
            //スルー
        }
    } else {
        //can_rank_up_ = false;
    }
}
void StageWorld::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_RANKUP_WAS_END) {
        _TRACE_("StageWorld::onCatchEvent EVENT_RANKUP_WAS_END");
        //スロー回復
        _TRACE_("P_STAGE_CTRLER をスロー回復");
        pStageCtrler_->addRunFrameOnce(-3); //スロー開始
    }
}

StageWorld::~StageWorld() {
    _TRACE_("StageWorld::~StageWorld() ");
}
