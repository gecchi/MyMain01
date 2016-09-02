#include "RankUpStage.h"

#include <stdio.h>
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "../RankUpStageController.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiRankUp.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundRankUp.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool RankUpStage::pause_ = false;

RankUpStage::RankUpStage(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpStage";
    _obj_class |= Obj_RankUpStage;

    pWorldBound_  = NEW WorldBoundRankUp("BG_RankUp");
    pWorldBound_->inactivate();
    bringDirector()->addSubGroup(pWorldBound_);
    pHoshiBoshi_ = NEW HoshiBoshiRankUp("HoshiBoshiRankUp");
    bringDirector()->addSubGroup( pHoshiBoshi_);
    pMessage1_ = NEW LabelGecchi16Font("RankUpMsg1");
    pMessage1_->place(PX_C(400), PX_C(200));
    bringDirector()->addSubGroup(pMessage1_);
    pMessage2_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage2_->place(PX_C(400), PX_C(230));
    bringDirector()->addSubGroup(pMessage2_);
    pMessage3_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage3_->place(PX_C(400), PX_C(260));
    bringDirector()->addSubGroup(pMessage3_);


    useProgress(PROG_BANPEI);

    pSeConnection_all_hit_ = connectToSeManager("WAVE_EXPLOSION_002"); //全滅の最後の一機破壊時SE

    all_hit_num_ = 0;
    hit_enemy_num_ = 0; //MyStgUtil::calcEnemyStamina() で加算されます
}

void RankUpStage::initialize() {
    getProgress()->reset(PROG_INIT);
}
void RankUpStage::processBehavior() {
    sprintf(buff,"HIT/ALL %d/%d",hit_enemy_num_,all_hit_num_);
    SceneProgress* pProg = getProgress();
    pMessage3_->update(buff);
    switch (pProg->get()) {
        case PROG_INIT: {
            _TRACE_("RankUpStage::processBehavior()  "<<this<<" ★"<<NODE_INFO<<DUMP_FLGS);
            _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PROG_BEGIN !");
            pMessage1_->update("RANKUPSTAGE::PROG_BEGIN");
            std::string m = "RUNKUP LEVEL:" + XTOS(G_RANKUP_LEVEL) ;
            pMessage2_->update(m.c_str());
            pMessage2_->pAFader_->beat(120, 30, 30, 30, -1);
            getBGMer()->play_fadein(0);
            pProg->changeNext();
            break;
        }
        case PROG_BEGIN: {
            if (pProg->hasArrivedAt(60)) { //ステージ開始！
                pProg->changeNext();
            }
            break;
        }
        case PROG_PLAYING: {
            if (pProg->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PROG_PLAYING");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PROG_BEGIN !");
            }

            if (pProg->getFrame() > _paFrame_NextEvent[_event_num-1]) { //最後の敵機が出現以降
                if (all_hit_num_ == hit_enemy_num_) {
                    //全滅させた！即効結果画面へ
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] 全滅させた！");
                    pSeConnection_all_hit_->peek()->play(); //全滅時SE!
                    pProg->change(PROG_RESULT);
                }
#ifdef MY_DEBUG
                if (pProg->hasArrivedAt(_paFrame_NextEvent[_event_num-1]+(10*60*60))) { //最終のアクター出現から10分。
                    throwGgafCriticalException(NODE_INFO<<" ランクアップシーンが終わらないのではないだろうか？？");
                }
#endif
                //その他の終了は、下位実装の各RankUpクラスに任せる。

            }

            //全滅させてない場合
            //下位の継承実装クラスのPROG_RESULTへ進捗更新待ち
            break;
        }
        case PROG_RESULT: {
            if (pProg->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PROG_RESULT");
                pMessage2_->update("KEKKA HAPYOU!!!");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PROG_RESULT !");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] 結果 hit_enemy_num_="<<hit_enemy_num_<<" all_hit_num_="<<all_hit_num_);
            }

            //結果表示？
            if (pProg->hasArrivedAt(320)) {
                getBGMer()->fadeout_stop(0);
                if (all_hit_num_ <= hit_enemy_num_) { //全滅させた！
                    pMessage2_->update("PERFECT!!!!");
                } else if (all_hit_num_/2 <= hit_enemy_num_) {
                    pMessage2_->update("VERY GOOD!!!!");
                } else if (all_hit_num_/3 <= hit_enemy_num_) {
                    pMessage2_->update("GOOD!!!!");
                } else {
                    pMessage2_->update("HETAKUSO!!!!");
                }
            }
            if (pProg->hasArrivedAt(320+300)) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_END: {
            _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PROG_ENDになりますた！");
            pMessage1_->update("RANKUPSTAGE::PROG_END");
            pMessage2_->update("BYEBYE!");
            throwEventUpperTree(EVENT_RANKUP_WAS_END); //RankUpStageControllerに処理を任せる
            pProg->changeNothing();
            break;
        }
        default:
            break;
    }
    pMessage2_->pAFader_->behave();

}

void RankUpStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

void RankUpStage::onEnd() {
    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] ");
}

RankUpStage::~RankUpStage() {
    pSeConnection_all_hit_->close();
}
