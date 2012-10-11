#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

NameEntryScene::NameEntryScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "NameEntryScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);

    pLabelInputedName_ = NEW LabelGecchi32Font("InputedName");
    //pLabelInputedName_->update("");
    pLabelInputedName_->locate(PX_C(800), PX_C(300), 2);
    getDirector()->addSubGroup(pLabelInputedName_);

    pLabelSelectedChar_ = NEW LabelGecchi32Font("SelectedChar");
    //pLabelSelectedChar_->update("");
    pLabelSelectedChar_->locateWith(pLabelInputedName_);
    pLabelSelectedChar_->_pFader->beat(60, 10, 0, 0, -1); //チカチカ点滅
    getDirector()->addSubGroup(pLabelSelectedChar_);

    pNameEntryBoard_ = NEW MenuBoardNameEntry("pNameEntryBoard_");
    pNameEntryBoard_->setNameStringBoard(pLabelInputedName_, pLabelSelectedChar_);
    getDirector()->addSubGroup(pNameEntryBoard_);

    inputed_name_ = "";
    useProgress(10);
}

void NameEntryScene::onReset() {
    pLabel01_->update("");
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
            //##########  事前画面表示  ##########
            if (_pProg->isJustChanged()) {
            }

            if(_pProg->getFrameInProgress() >= 120) {
                _pProg->change(NameEntryScene::PROG_INPUT);
            }
            break;
        }

        case NameEntryScene::PROG_INPUT: {
            //##########  ネームエントリー  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("pNameEntryBoard_->rise(PX_C(50), PX_C(10));");
                pLabel01_->update(PX_C(62), PX_C(32), "PLEASE ENTRY YOUR NAME!!!!");
                pNameEntryBoard_->rise(PX_C(50), PX_C(10)); //ネームエントリー板出現
            }
            pLabelSelectedChar_->_pFader->behave(); //チカチカ
            //EVENT_NAME_ENTRY_DONE まち。
            break;
        }

        case NameEntryScene::PROG_DONE_DISP: {
            //##########  ネームエントリー完了後の画面表示  ##########
            if (_pProg->isJustChanged()) {
                inputed_name_ = std::string(pLabelInputedName_->_draw_string); //入力文字
                pNameEntryBoard_->sink(); //ネームエントリー板消去
                pLabelSelectedChar_->inactivate(); //選択表示文字消去
                pLabelSelectedChar_->_pFader->beat(10, 5, 0, 0, -1); //速いチカチカ点滅

                //ここでハイスコア更新処理
            }
            if(_pProg->getFrameInProgress() >= 120) {
                _pProg->change(NameEntryScene::PROG_FINISH);
            }
            pLabelSelectedChar_->_pFader->behave(); //チカチカ
            break;
        }
        case NameEntryScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {

                _TRACE_("おわりじゃよ");
            }
            break;
        }

        default:
            break;
     }
}

void NameEntryScene::onCatchEvent(hashval prm_no, void* prm_pSource) {

    if (prm_no == EVENT_NAME_ENTRY_DONE) {
        _pProg->change(PROG_DONE_DISP);
    }
}
NameEntryScene::~NameEntryScene() {
}
