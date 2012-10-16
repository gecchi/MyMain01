#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

NameEntryScene::NameEntryScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "NameEntryScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);

    pWorldBound_ = NEW WorldBoundNameEntry("NAMEENTRY_WB");
    getDirector()->addSubGroup(pWorldBound_);

    pLabelInputedName_ = NEW SpriteLabelGecchi32Font("InputedName");
    pLabelInputedName_->locate(PX_C(100), PX_C(0), -2);
    getDirector()->addSubGroup(pLabelInputedName_);

    pLabelSelectedChar_ = NEW SpriteLabelGecchi32Font("SelectedChar");
    pLabelSelectedChar_->_pFader->beat(60, 10, 0, 0, -1); //�`�J�`�J�_��
    pLabelSelectedChar_->locateWith(pLabelInputedName_);
    getDirector()->addSubGroup(pLabelSelectedChar_);

    pNameEntryBoard_ = NEW MenuBoardNameEntry("pNameEntryBoard_");
    pNameEntryBoard_->setNameStringBoard(pLabelInputedName_, pLabelSelectedChar_);
    getDirector()->addSubGroup(pNameEntryBoard_);

    inputed_name_ = "";
    useProgress(10);
}

void NameEntryScene::onReset() {
    pLabel01_->update("");
    pLabelInputedName_->update("");
    pWorldBound_->inactivateImmed();
    _pProg->set(NameEntryScene::PROG_INIT);
}
void NameEntryScene::initialize() {
    _TRACE_("NameEntryScene::initialize()");
}

void NameEntryScene::processBehavior() {

    switch (_pProg->get()) {
        case NameEntryScene::PROG_INIT: {
            _pProg->change(NameEntryScene::PROG_PRE_DISP);
            break;
        }

        case NameEntryScene::PROG_PRE_DISP: {
            //##########  ���O��ʕ\��  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("NameEntryScene::processBehavior() Prog has Just Changed (to NameEntryScene::PROG_PRE_DISP)");
                pWorldBound_->fadein();
            }

            if(_pProg->getFrameInProgress() >= 120) {
                _pProg->change(NameEntryScene::PROG_INPUT);
            }
            break;
        }

        case NameEntryScene::PROG_INPUT: {
            //##########  �l�[���G���g���[  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("NameEntryScene::processBehavior() Prog has Just Changed (to NameEntryScene::PROG_INPUT)");
                pLabel01_->update(PX_C(62), PX_C(32), "PLEASE ENTRY YOUR NAME!!!!");
                pNameEntryBoard_->rise(PX_C(50), PX_C(10)); //�l�[���G���g���[�o��

                pLabelInputedName_->_pKurokoA->setFaceAngVelo(AXIS_X, 1700);
                pLabelInputedName_->_pKurokoA->setFaceAngVelo(AXIS_Y, 1500);
                pLabelInputedName_->_pKurokoA->setFaceAngVelo(AXIS_Z, 1000);

            }
            pLabelInputedName_->_pKurokoA->behave();
            pLabelSelectedChar_->rotateWith(pLabelInputedName_);
            pLabelSelectedChar_->_pFader->behave(); //�`�J�`�J
            //EVENT_MENU_NAMEENTRY_DONE �܂��B
            break;
        }

        case NameEntryScene::PROG_DONE_DISP: {
            //##########  �l�[���G���g���[������̉�ʕ\��  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("NameEntryScene::processBehavior() Prog has Just Changed (to NameEntryScene::PROG_DONE_DISP)");
                pNameEntryBoard_->sink(); //�l�[���G���g���[����
                pLabelSelectedChar_->inactivate(); //�I��\����������
                pLabelInputedName_->_pFader->beat(10, 5, 0, 0, -1); //���̓l�[���_��
                pLabelInputedName_->_pKurokoA->execTurnFaceAngSequence(0, 0, 8000, 0, TURN_COUNTERCLOCKWISE);//�}���Ő���p����
                pLabelInputedName_->_pKurokoA->execTurnRxSpinAngSequence(0, 8000, 0, TURN_COUNTERCLOCKWISE);
                //�����Ńn�C�X�R�A�X�V����
                inputed_name_ = std::string(pLabelInputedName_->_draw_string); //���͕���
                GameGlobal::qryRanking_.addRow(inputed_name_, _SCORE_);
                GameGlobal::qryRanking_.sort();
                GameGlobal::qryRanking_.save();

                pWorldBound_->fadeout();
            }
            if(_pProg->getFrameInProgress() >= 180) {
                _pProg->change(NameEntryScene::PROG_FINISH);
            }

            pLabelInputedName_->_pKurokoA->behave();
            pLabelSelectedChar_->rotateWith(pLabelInputedName_);
            pLabelInputedName_->_pFader->behave(); //�_�Ń`�J�`�J
            break;
        }

        case NameEntryScene::PROG_FINISH: {
            if (_pProg->hasJustChanged()) {
                _TRACE_("NameEntryScene::processBehavior() Prog has Just Changed (to NameEntryScene::PROG_FINISH)");
                _TRACE_("����肶���I");
                throwEventToUpperTree(EVENT_NAMEENTRYSCENE_FINISH);
            }
            break;
        }

        default:
            break;
     }
}

void NameEntryScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MENU_NAMEENTRY_DONE) {
        _TRACE_("NameEntryScene::onCatchEvent(EVENT_MENU_NAMEENTRY_DONE)");
        _pProg->change(PROG_DONE_DISP);
    }
}

NameEntryScene::~NameEntryScene() {
}
