#include "StageWorld.h"

#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

StageWorld::StageWorld(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "StageWorld";
    can_rank_up_ = true;
    pStageCtrler_ = NEW StageController("StageController");
    appendChild(pStageCtrler_);
    pRankUpStageCtrler_ = NEW RankUpStageController("RankUpStageController");
    appendChild(pRankUpStageCtrler_);
}

void StageWorld::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<" CARETAKER="<<pCARETAKER->_frame_of_Caretaker);
    _TRACE_("MyShipScene を、スローの影響を与えないために一つ上に引き上げます appendChild(pMYSHIP_SCENE->extract()); ");
    pMYSHIP_SCENE->resetTree();
    pMYSHIP_SCENE->activateImmed();
    appendChild(pMYSHIP_SCENE->extract()); //スローの影響を与えないために一つ上
    pStageCtrler_->setRunFrameOnce(1); //スローなしに
}

void StageWorld::initialize() {
}

void StageWorld::processBehavior() {

    //debug ---->
//#ifdef MY_DEBUG
    if (GgafDx::Input::isPushedDownKey(DIK_P)) {
        G_RANK += (1.0/G_RANK_R);
        _TRACE_(FUNC_NAME<<" G_RANK="<<G_RANK<<"/G_RANK_DISP="<<G_RANK_DISP<<"");
    }
//#endif
    //<---- debug
    //ランクアップシーン差し込み
    if (GameGlobal::updateRankUpLebel()) {
        _TRACE_("G_RANKUP_LEVEL アップしました！！→"<<G_RANKUP_LEVEL<<" (G_RANK="<<G_RANK<<"/G_RANK_DISP="<<G_RANK_DISP<<")");
        if (can_rank_up_) {
            _TRACE_("ランクアップシーン差し込みします！");
            pRankUpStageCtrler_->startRunkUpStage(G_RANKUP_LEVEL);
            _TRACE_("pSTAGE_CTRLER をスロー");
            pStageCtrler_->addRunFrameOnce(SLOW_FRAME_RANKUP); //スロー開始
        } else {
            //スルー
        }
    } else {
        //can_rank_up_ = false;
    }
}
void StageWorld::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    if (prm_event_val == EVENT_RANKUP_WAS_END) {
        _TRACE_(FUNC_NAME<<" EVENT_RANKUP_WAS_END");
        //スロー回復
        _TRACE_("pSTAGE_CTRLER をスロー回復");
        pStageCtrler_->addRunFrameOnce(-SLOW_FRAME_RANKUP); //スロー開始
    }
}

StageWorld::~StageWorld() {
    _TRACE_("StageWorld::~StageWorld() ");
}
