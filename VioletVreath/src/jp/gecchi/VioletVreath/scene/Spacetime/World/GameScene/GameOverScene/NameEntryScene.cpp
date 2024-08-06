#include "NameEntryScene.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundNameEntry.h"
#include "jp/gecchi/VioletVreath/actor/menu/name_entry/MenuBoardNameEntry.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/util/RankingTable.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT     ,
    PHASE_PRE_DISP ,
    PHASE_INPUT    ,
    PHASE_DONE_DISP,
    PHASE_FINISH   ,
    PHASE_BANPEI,
};

NameEntryScene::NameEntryScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "NameEntryScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getSceneChief()->appendGroupChild(pLabel01_);

    pWorldBound_ = NEW WorldBoundNameEntry("NAMEENTRY_WB");
    getSceneChief()->appendGroupChild(pWorldBound_);

    pLabelInputedName_ = NEW SpriteLabelGecchi32Font("InputedName");
    pLabelInputedName_->setPosition(PX_C(100), PX_C(0), -2);
    getSceneChief()->appendGroupChild(pLabelInputedName_);

    pLabelSelectedChar_ = NEW SpriteLabelGecchi32Font("SelectedChar");
    pLabelSelectedChar_->getAlphaFader()->beat(60, 10, 0, 50, -1); //�`�J�`�J�_��
    pLabelSelectedChar_->setPositionAt(pLabelInputedName_);
    getSceneChief()->appendGroupChild(pLabelSelectedChar_);

    pNameEntryBoard_ = NEW MenuBoardNameEntry("pNameEntryBoard_");
    pNameEntryBoard_->setNameFontBoard(pLabelInputedName_, pLabelSelectedChar_);
    getSceneChief()->appendGroupChild(pNameEntryBoard_);

    inputed_name_ = "";
}

void NameEntryScene::onReset() {
    pLabel01_->update("");
    pLabelInputedName_->update("");
    pWorldBound_->inactivate();
    getPhase()->reset(PHASE_INIT);
}
void NameEntryScene::initialize() {
    _TRACE_(FUNC_NAME<<"");
}

void NameEntryScene::processBehavior() {
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_PRE_DISP);
            break;
        }

        case PHASE_PRE_DISP: {
            //##########  ���O��ʕ\��  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_PRE_DISP)");
                pWorldBound_->fadein();
            }

            if(pPhase->getFrame() >= 120) {
                pPhase->change(PHASE_INPUT);
            }
            break;
        }

        case PHASE_INPUT: {
            //##########  �l�[���G���g���[  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_INPUT)");
                pLabel01_->update(PX_C(62), PX_C(32), "PLEASE ENTRY YOUR NAME!!!!");
                pNameEntryBoard_->rise(PX_C(50), PX_C(10)); //�l�[���G���g���[�o��
                pLabelInputedName_->getLocusVehicle()->setRollPitchYawFaceAngVelo(1700, 1500, 1000);
            }
            pLabelInputedName_->getLocusVehicle()->behave();
            pLabelSelectedChar_->setFaceAngAs(pLabelInputedName_);
            pLabelSelectedChar_->getAlphaFader()->behave(); //�`�J�`�J
            //EVENT_MENU_NAMEENTRY_DONE �܂��B
            break;
        }

        case PHASE_DONE_DISP: {
            //##########  �l�[���G���g���[������̉�ʕ\��  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_DONE_DISP)");
                pNameEntryBoard_->sinkMe(); //�l�[���G���g���[����
                pLabelSelectedChar_->inactivate(); //�I��\����������
                pLabelInputedName_->getAlphaFader()->beat(10, 5, 0, 5, -1); //���̓l�[���_��
                pLabelInputedName_->getLocusVehicle()->turnRzRyFaceAngTo(D0ANG, D0ANG,
                                                                   8000, 0,
                                                                   TURN_COUNTERCLOCKWISE, false);//�}���Ő���p����
                pLabelInputedName_->getLocusVehicle()->rollFaceAngTo(D0ANG, 8000, 0, TURN_COUNTERCLOCKWISE);
                //�����Ńn�C�X�R�A�X�V����
                char* cstr = NEW char[pLabelInputedName_->_len + 1];
                for (int i = 0; i < pLabelInputedName_->_len; i++) {
                    cstr[i] = pLabelInputedName_->_draw_string[i];
                };
                cstr[pLabelInputedName_->_len] = '\0';

                inputed_name_ = std::string(cstr); //���͕���
                GGAF_DELETEARR(cstr);
                G_RANKING_TABLE.addRow(inputed_name_, G_SCORE);
                G_RANKING_TABLE.sort();
                G_RANKING_TABLE.save();

                pWorldBound_->fadeout();
            }
            if(pPhase->getFrame() >= 180) {
                pPhase->change(PHASE_FINISH);
            }

            pLabelInputedName_->getLocusVehicle()->behave();
            pLabelSelectedChar_->setFaceAngAs(pLabelInputedName_);
            pLabelInputedName_->getAlphaFader()->behave(); //�_�Ń`�J�`�J
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_FINISH)");
                _TRACE_("����肶���I");
                throwEventUpperTree(EVENT_NAMEENTRYSCENE_FINISH);
            }
            break;
        }

        default: {
            break;
        }
     }
}

void NameEntryScene::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    GgafCore::Phase* pPhase = getPhase();
    if (prm_event_val == EVENT_MENU_NAMEENTRY_DONE) {
        _TRACE_("NameEntryScene::onCatchEvent(EVENT_MENU_NAMEENTRY_DONE)");
        pPhase->change(PHASE_DONE_DISP);
    }
}

NameEntryScene::~NameEntryScene() {
}
