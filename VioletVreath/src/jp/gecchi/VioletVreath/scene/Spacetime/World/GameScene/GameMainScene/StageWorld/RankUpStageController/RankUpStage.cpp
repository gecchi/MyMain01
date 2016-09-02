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

    pSeConnection_all_hit_ = connectToSeManager("WAVE_EXPLOSION_002"); //�S�ł̍Ō�̈�@�j��SE

    all_hit_num_ = 0;
    hit_enemy_num_ = 0; //MyStgUtil::calcEnemyStamina() �ŉ��Z����܂�
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
            _TRACE_("RankUpStage::processBehavior()  "<<this<<" ��"<<NODE_INFO<<DUMP_FLGS);
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
            if (pProg->hasArrivedAt(60)) { //�X�e�[�W�J�n�I
                pProg->changeNext();
            }
            break;
        }
        case PROG_PLAYING: {
            if (pProg->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PROG_PLAYING");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PROG_BEGIN !");
            }

            if (pProg->getFrame() > _paFrame_NextEvent[_event_num-1]) { //�Ō�̓G�@���o���ȍ~
                if (all_hit_num_ == hit_enemy_num_) {
                    //�S�ł������I�������ʉ�ʂ�
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] �S�ł������I");
                    pSeConnection_all_hit_->peek()->play(); //�S�Ŏ�SE!
                    pProg->change(PROG_RESULT);
                }
#ifdef MY_DEBUG
                if (pProg->hasArrivedAt(_paFrame_NextEvent[_event_num-1]+(10*60*60))) { //�ŏI�̃A�N�^�[�o������10���B
                    throwGgafCriticalException(NODE_INFO<<" �����N�A�b�v�V�[�����I���Ȃ��̂ł͂Ȃ����낤���H�H");
                }
#endif
                //���̑��̏I���́A���ʎ����̊eRankUp�N���X�ɔC����B

            }

            //�S�ł����ĂȂ��ꍇ
            //���ʂ̌p�������N���X��PROG_RESULT�֐i���X�V�҂�
            break;
        }
        case PROG_RESULT: {
            if (pProg->hasJustChanged()) {
                pMessage1_->update("RANKUPSTAGE::PROG_RESULT");
                pMessage2_->update("KEKKA HAPYOU!!!");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PROG_RESULT !");
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] ���� hit_enemy_num_="<<hit_enemy_num_<<" all_hit_num_="<<all_hit_num_);
            }

            //���ʕ\���H
            if (pProg->hasArrivedAt(320)) {
                getBGMer()->fadeout_stop(0);
                if (all_hit_num_ <= hit_enemy_num_) { //�S�ł������I
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
            _TRACE_(FUNC_NAME<<" ["<<getName()<<"] PROG_END�ɂȂ�܂����I");
            pMessage1_->update("RANKUPSTAGE::PROG_END");
            pMessage2_->update("BYEBYE!");
            throwEventUpperTree(EVENT_RANKUP_WAS_END); //RankUpStageController�ɏ�����C����
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
