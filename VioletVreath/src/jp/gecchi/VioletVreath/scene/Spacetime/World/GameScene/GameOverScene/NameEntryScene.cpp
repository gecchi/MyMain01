#include "NameEntryScene.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundNameEntry.h"
#include "jp/gecchi/VioletVreath/actor/menu/name_entry/MenuBoardNameEntry.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/util/RankingTable.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT     ,
    PROG_PRE_DISP ,
    PROG_INPUT    ,
    PROG_DONE_DISP,
    PROG_FINISH   ,
    PROG_BANPEI,
};

NameEntryScene::NameEntryScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "NameEntryScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    bringSceneMediator()->appendGroupChild(pLabel01_);

    pWorldBound_ = NEW WorldBoundNameEntry("NAMEENTRY_WB");
    bringSceneMediator()->appendGroupChild(pWorldBound_);

    pLabelInputedName_ = NEW SpriteLabelGecchi32Font("InputedName");
    pLabelInputedName_->setPosition(PX_C(100), PX_C(0), -2);
    bringSceneMediator()->appendGroupChild(pLabelInputedName_);

    pLabelSelectedChar_ = NEW SpriteLabelGecchi32Font("SelectedChar");
    pLabelSelectedChar_->getAlphaFader()->beat(60, 10, 0, 50, -1); //�`�J�`�J�_��
    pLabelSelectedChar_->setPositionAt(pLabelInputedName_);
    bringSceneMediator()->appendGroupChild(pLabelSelectedChar_);

    pNameEntryBoard_ = NEW MenuBoardNameEntry("pNameEntryBoard_");
    pNameEntryBoard_->setNameFontBoard(pLabelInputedName_, pLabelSelectedChar_);
    bringSceneMediator()->appendGroupChild(pNameEntryBoard_);

    inputed_name_ = "";
    useProgress(PROG_BANPEI);
}

void NameEntryScene::onReset() {
    pLabel01_->update("");
    pLabelInputedName_->update("");
    pWorldBound_->inactivate();
    getProgress()->reset(PROG_INIT);
}
void NameEntryScene::initialize() {
    _TRACE_(FUNC_NAME<<"");
}

void NameEntryScene::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_PRE_DISP);
            break;
        }

        case PROG_PRE_DISP: {
            //##########  ���O��ʕ\��  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_PRE_DISP)");
                pWorldBound_->fadein();
            }

            if(pProg->getFrame() >= 120) {
                pProg->change(PROG_INPUT);
            }
            break;
        }

        case PROG_INPUT: {
            //##########  �l�[���G���g���[  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_INPUT)");
                pLabel01_->update(PX_C(62), PX_C(32), "PLEASE ENTRY YOUR NAME!!!!");
                pNameEntryBoard_->rise(PX_C(50), PX_C(10)); //�l�[���G���g���[�o��
                pLabelInputedName_->getKuroko()->setRollPitchYawFaceAngVelo(1700, 1500, 1000);
            }
            pLabelInputedName_->getKuroko()->behave();
            pLabelSelectedChar_->setFaceAngAs(pLabelInputedName_);
            pLabelSelectedChar_->getAlphaFader()->behave(); //�`�J�`�J
            //EVENT_MENU_NAMEENTRY_DONE �܂��B
            break;
        }

        case PROG_DONE_DISP: {
            //##########  �l�[���G���g���[������̉�ʕ\��  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_DONE_DISP)");
                pNameEntryBoard_->sinkMe(); //�l�[���G���g���[����
                pLabelSelectedChar_->inactivate(); //�I��\����������
                pLabelInputedName_->getAlphaFader()->beat(10, 5, 0, 5, -1); //���̓l�[���_��
                pLabelInputedName_->getKuroko()->turnRzRyFaceAngTo(D0ANG, D0ANG,
                                                                   8000, 0,
                                                                   TURN_COUNTERCLOCKWISE, false);//�}���Ő���p����
                pLabelInputedName_->getKuroko()->rollFaceAngTo(D0ANG, 8000, 0, TURN_COUNTERCLOCKWISE);
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
            if(pProg->getFrame() >= 180) {
                pProg->change(PROG_FINISH);
            }

            pLabelInputedName_->getKuroko()->behave();
            pLabelSelectedChar_->setFaceAngAs(pLabelInputedName_);
            pLabelInputedName_->getAlphaFader()->behave(); //�_�Ń`�J�`�J
            break;
        }

        case PROG_FINISH: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_FINISH)");
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

void NameEntryScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
    GgafProgress* const pProg = getProgress();
    if (prm_no == EVENT_MENU_NAMEENTRY_DONE) {
        _TRACE_("NameEntryScene::onCatchEvent(EVENT_MENU_NAMEENTRY_DONE)");
        pProg->change(PROG_DONE_DISP);
    }
}

NameEntryScene::~NameEntryScene() {
}
