#include "RankUpStage.h"

#include <stdio.h>
#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/manager/SeConnection.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "../RankUpStageController.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiRankUp.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundRankUp.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"



using namespace GgafLib;
using namespace VioletVreath;

bool RankUpStage::pause_ = false;

RankUpStage::RankUpStage(const char* prm_name) : VvScene<DefaultScene>(prm_name, NEW RankUpStage::SceneChief(this)) {
    _class_name = "RankUpStage";
    _obj_class |= Obj_RankUpStage;

    pWorldBound_  = NEW WorldBoundRankUp("BG_RankUp");
    pWorldBound_->inactivate();
    getSceneChief()->appendChild(pWorldBound_);
    pHoshiBoshi_ = NEW HoshiBoshiRankUp("HoshiBoshiRankUp");
    getSceneChief()->appendChild( pHoshiBoshi_);
    pMessage1_ = NEW LabelGecchi16Font("RankUpMsg1");
    pMessage1_->setPosition(PX_C(400), PX_C(200));
    getSceneChief()->appendChild(pMessage1_);
    pMessage2_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage2_->setPosition(PX_C(400), PX_C(230));
    getSceneChief()->appendChild(pMessage2_);
    pMessage3_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage3_->setPosition(PX_C(400), PX_C(260));
    getSceneChief()->appendChild(pMessage3_);

    pSeConnection_all_hit_ = connectToSeManager("SE_EXPLOSION_002"); //全滅の最後の一機破壊時SE
}

void RankUpStage::initialize() {
    getPhase()->reset(PHASE_INIT);
}
void RankUpStage::processBehavior() {
    RankUpStage::SceneChief* pSceneChief = getSceneChief();

    sprintf(buff,"HIT/ALL %d/%d", pSceneChief->hit_enemy_num_, pSceneChief->all_hit_num_);
    ScenePhase* pPhase = getPhase();
    pMessage3_->update(buff);
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            _TRACE_("RankUpStage::processBehavior()  "<<this<<" ★"<<NODE_INFO<< DUMP_FLGS_SCENE);
            _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PHASE_BEGIN !");
            pMessage1_->update("RANKUPSTAGE::PHASE_BEGIN");
            std::string m = "RUNKUP LEVEL:" + XTOS(G_RANKUP_LEVEL) ;
            pMessage2_->update(m.c_str());
            pMessage2_->getAlphaFader()->beat(120, 30, 30, 30, -1);
            getBgmConductor()->performFadein(0, 120);
            pPhase->changeNext();
            break;
        }
        case PHASE_BEGIN: {
            if (pPhase->hasArrivedFrameAt(60)) { //ステージ開始！
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_PLAYING: {
            if (pPhase->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PHASE_PLAYING");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PHASE_BEGIN !");
            }

            if (pPhase->getFrame() > _paFrame_NextEvent[_event_num-1]) { //最後の敵機が出現以降
                if (pSceneChief->all_hit_num_ == pSceneChief->hit_enemy_num_) {
                    //全滅させた！即効結果画面へ
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] 全滅させた！");
                    pSeConnection_all_hit_->peek()->play(); //全滅時SE!
                    pPhase->change(PHASE_RESULT);
                }
#ifdef MY_DEBUG
                if (pPhase->hasArrivedFrameAt(_paFrame_NextEvent[_event_num-1]+(SEC_F(10*60)))) { //最終のアクター出現から10分。
                    throwCriticalException(NODE_INFO<<" ランクアップシーンが終わらないのではないだろうか？？");
                }
#endif
                //その他の終了は、下位実装の各RankUpクラスに任せる。

            }

            //全滅させてない場合
            //下位の継承実装クラスのPHASE_RESULTへフェーズ更新待ち
            break;
        }
        case PHASE_RESULT: {
            if (pPhase->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PHASE_RESULT");
                pMessage2_->update("KEKKA HAPYOU!!!");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PHASE_RESULT !");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] 結果 hit_enemy_num_="<<pSceneChief->hit_enemy_num_<<" all_hit_num_="<<pSceneChief->all_hit_num_);
            }

            //結果表示？
            if (pPhase->hasArrivedFrameAt(320)) {
                getBgmConductor()->fadeoutStop(0, 120);
                if (pSceneChief->all_hit_num_ <= pSceneChief->hit_enemy_num_) { //全滅させた！
                    pMessage2_->update("PERFECT!!!!");
                } else if (pSceneChief->all_hit_num_/2 <= pSceneChief->hit_enemy_num_) {
                    pMessage2_->update("VERY GOOD!!!!");
                } else if (pSceneChief->all_hit_num_/3 <= pSceneChief->hit_enemy_num_) {
                    pMessage2_->update("GOOD!!!!");
                } else {
                    pMessage2_->update("HETAKUSO!!!!");
                }
            }
            if (pPhase->hasArrivedFrameAt(320+300)) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_END: {
            _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PHASE_ENDになりますた！");
            pMessage1_->update("RANKUPSTAGE::PHASE_END");
            pMessage2_->update("BYEBYE!");
            throwEventUpperTree(EVENT_RANKUP_WAS_END); //RankUpStageControllerに処理を任せる
            pPhase->changeNothing();
            break;
        }
        default:
            break;
    }
    pMessage2_->getAlphaFader()->behave();

}

void RankUpStage::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}

RankUpStage::~RankUpStage() {
    pSeConnection_all_hit_->close();
}
