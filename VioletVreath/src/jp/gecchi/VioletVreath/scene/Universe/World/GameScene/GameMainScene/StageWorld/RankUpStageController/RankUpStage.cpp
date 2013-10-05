#include "stdafx.h"
#include "RankUpStage.h"

#include <stdio.h>
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiRankUp.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpaceRankUp.h"
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

    pWorldBoundSpace_  = NEW WorldBoundSpaceRankUp("BG_RankUp");
    pWorldBoundSpace_->inactivateImmed();
    getSceneDirector()->addSubGroup(pWorldBoundSpace_);
    pHoshiBoshi_ = NEW HoshiBoshiRankUp("HoshiBoshiRankUp");
    getSceneDirector()->addSubGroup( pHoshiBoshi_);
    pMessage1_ = NEW LabelGecchi16Font("RankUpMsg1");
    pMessage1_->position(PX_C(400), PX_C(200));
    getSceneDirector()->addSubGroup(pMessage1_);
    pMessage2_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage2_->position(PX_C(400), PX_C(230));
    getSceneDirector()->addSubGroup(pMessage2_);
    pMessage3_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage3_->position(PX_C(400), PX_C(260));
    getSceneDirector()->addSubGroup(pMessage3_);


    useProgress(RankUpStage::_BANPEI_-1);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "OGG_RANKUP_THEMA");

    pSeConnection_all_hit_ = connect_SeManager("WAVE_EXPLOSION_002"); //全滅の最後の一機破壊時SE

    all_hit_num_ = 0;
    hit_enemy_num_ = 0; //MyStgUtil::calcEnemyStamina() で加算されます
}

void RankUpStage::initialize() {
    _pProg->reset(RankUpStage::PROG_INIT);
}
void RankUpStage::processBehavior() {
    sprintf(buff,"HIT/ALL %d/%d",hit_enemy_num_,all_hit_num_);
    pMessage3_->update(buff);
    switch (_pProg->get()) {
        case RankUpStage::PROG_INIT: {
            _pProg->change(RankUpStage::PROG_BEGIN);
            break;
        }
        case RankUpStage::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_BEGIN !");
                pMessage1_->update("RANKUPSTAGE::PROG_BEGIN");
                std::string m = "RUNKUP LEVEL:" + XTOS(G_RANKUP_LEVEL) ;
                pMessage2_->update(m.c_str());
                pMessage2_->_pAFader->beat(120,30,30,30,-1);
                _pBgmPerformer->play_fadein(0);
            }

            if (_pProg->getFrameInProgress() == 60) { //ステージ開始！
                _pProg->change(RankUpStage::PROG_PLAYING);
            }
            break;
        }
        case RankUpStage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PROG_PLAYING");
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_BEGIN !");
            }

            if (_pProg->getFrameInProgress() > _paFrame_NextEvent[_event_num-1]) { //最後の敵機が出現以降
                if (all_hit_num_ == hit_enemy_num_) {
                    //全滅させた！即効結果画面へ
                    _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] 全滅させた！");
                    _pProg->change(RankUpStage::PROG_RESULT);
                    pSeConnection_all_hit_->peek()->play(); //全滅時SE!
                } else if (_pProg->getFrameInProgress() == _paFrame_NextEvent[_event_num-1]+1200) {
                    //最後の敵機が出現以降最高２分で強制結果画面へ
                    _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] 強制結果画面へ！");
                    _pProg->change(RankUpStage::PROG_RESULT);
                }
            }

            //全滅させてない場合
            //下位の継承実装クラスのRankUpStage::PROG_RESULTへ進捗更新待ち
            break;
        }
        case RankUpStage::PROG_RESULT: {
            if (_pProg->isJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PROG_RESULT");
                pMessage2_->update("KEKKA HAPYOU!!!");
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_RESULT !");
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] 結果 hit_enemy_num_="<<hit_enemy_num_<<" all_hit_num_="<<all_hit_num_);
            }

            //結果表示？
            if (_pProg->getFrameInProgress() == 320) {
                _pBgmPerformer->fadeout_stop(0);
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

            if (_pProg->getFrameInProgress() == 320+300) {
                _pProg->change(RankUpStage::PROG_END);
            }
            break;
        }
        case RankUpStage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_ENDになりますた！");
                pMessage1_->update("RANKUPSTAGE::PROG_END");
                throwEventUpperTree(EVENT_RANKUP_WAS_END);
                pMessage2_->update("BYEBYE!");
            }

            break;
        }
        default:
            break;
    }
    pMessage2_->_pAFader->behave();

}

void RankUpStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

void RankUpStage::onEnd() {
    _TRACE_("RankUpStage::onEnd() ["<<getName()<<"] throwEventUpperTree EVENT_RANKUP_ON_GARBAGED！");
    throwEventUpperTree(EVENT_RANKUP_ON_GARBAGED);
}

RankUpStage::~RankUpStage() {
    pSeConnection_all_hit_->close();
}
