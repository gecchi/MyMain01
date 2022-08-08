#include "RankUpStage.h"

#include <stdio.h>
#include "jp/ggaf/core/actor/SceneMediator.h"
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

RankUpStage::RankUpStage(const char* prm_name) : VvScene<DefaultScene>(prm_name, NEW RankUpStage::Medietor(this)) {
    _class_name = "RankUpStage";
    _obj_class |= Obj_RankUpStage;

    pWorldBound_  = NEW WorldBoundRankUp("BG_RankUp");
    pWorldBound_->inactivate();
    bringSceneMediator()->appendGroupChild(pWorldBound_);
    pHoshiBoshi_ = NEW HoshiBoshiRankUp("HoshiBoshiRankUp");
    bringSceneMediator()->appendGroupChild( pHoshiBoshi_);
    pMessage1_ = NEW LabelGecchi16Font("RankUpMsg1");
    pMessage1_->setPosition(PX_C(400), PX_C(200));
    bringSceneMediator()->appendGroupChild(pMessage1_);
    pMessage2_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage2_->setPosition(PX_C(400), PX_C(230));
    bringSceneMediator()->appendGroupChild(pMessage2_);
    pMessage3_ = NEW LabelGecchi16Font("RankUpMsg2");
    pMessage3_->setPosition(PX_C(400), PX_C(260));
    bringSceneMediator()->appendGroupChild(pMessage3_);

    pSeConnection_all_hit_ = connectToSeManager("SE_EXPLOSION_002"); //�S�ł̍Ō�̈�@�j��SE
}

void RankUpStage::initialize() {
    getPhase()->reset(PHASE_INIT);
}
void RankUpStage::processBehavior() {
    RankUpStage::Medietor* pMedietor = bringSceneMediator();

    sprintf(buff,"HIT/ALL %d/%d", pMedietor->hit_enemy_num_, pMedietor->all_hit_num_);
    ScenePhase* pPhase = getPhase();
    pMessage3_->update(buff);
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            _TRACE_("RankUpStage::processBehavior()  "<<this<<" ��"<<NODE_INFO<<DUMP_FLGS);
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
            if (pPhase->hasArrivedFrameAt(60)) { //�X�e�[�W�J�n�I
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_PLAYING: {
            if (pPhase->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PHASE_PLAYING");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PHASE_BEGIN !");
            }

            if (pPhase->getFrame() > _paFrame_NextEvent[_event_num-1]) { //�Ō�̓G�@���o���ȍ~
                if (pMedietor->all_hit_num_ == pMedietor->hit_enemy_num_) {
                    //�S�ł������I�������ʉ�ʂ�
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] �S�ł������I");
                    pSeConnection_all_hit_->peek()->play(); //�S�Ŏ�SE!
                    pPhase->change(PHASE_RESULT);
                }
#ifdef MY_DEBUG
                if (pPhase->hasArrivedFrameAt(_paFrame_NextEvent[_event_num-1]+(10*60*60))) { //�ŏI�̃A�N�^�[�o������10���B
                    throwCriticalException(NODE_INFO<<" �����N�A�b�v�V�[�����I���Ȃ��̂ł͂Ȃ����낤���H�H");
                }
#endif
                //���̑��̏I���́A���ʎ����̊eRankUp�N���X�ɔC����B

            }

            //�S�ł����ĂȂ��ꍇ
            //���ʂ̌p�������N���X��PHASE_RESULT�փt�F�[�Y�X�V�҂�
            break;
        }
        case PHASE_RESULT: {
            if (pPhase->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PHASE_RESULT");
                pMessage2_->update("KEKKA HAPYOU!!!");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PHASE_RESULT !");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] ���� hit_enemy_num_="<<pMedietor->hit_enemy_num_<<" all_hit_num_="<<pMedietor->all_hit_num_);
            }

            //���ʕ\���H
            if (pPhase->hasArrivedFrameAt(320)) {
                getBgmConductor()->fadeoutStop(0, 120);
                if (pMedietor->all_hit_num_ <= pMedietor->hit_enemy_num_) { //�S�ł������I
                    pMessage2_->update("PERFECT!!!!");
                } else if (pMedietor->all_hit_num_/2 <= pMedietor->hit_enemy_num_) {
                    pMessage2_->update("VERY GOOD!!!!");
                } else if (pMedietor->all_hit_num_/3 <= pMedietor->hit_enemy_num_) {
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
            _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PHASE_END�ɂȂ�܂����I");
            pMessage1_->update("RANKUPSTAGE::PHASE_END");
            pMessage2_->update("BYEBYE!");
            throwEventUpperTree(EVENT_RANKUP_WAS_END); //RankUpStageController�ɏ�����C����
            pPhase->changeNothing();
            break;
        }
        default:
            break;
    }
    pMessage2_->getAlphaFader()->behave();

}

void RankUpStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

RankUpStage::~RankUpStage() {
    pSeConnection_all_hit_->close();
}
