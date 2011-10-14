#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

RankUp001::RankUp001(const char* prm_name) : RankUpScene(prm_name) {
    _class_name = "RankUp001";
    _pWorldBoundSpace  = NEW WorldBoundSpace001("BG_SPACE");
    getDirector()->addSubGroup(_pWorldBoundSpace);
    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    getDirector()->addSubGroup( _pHoshiBoshi);
    _pMessage = NEW LabelGecchi16Font("RankUp001Msg");
    getDirector()->addSubGroup(_pMessage);
}

void RankUp001::initialize() {
    RankUpScene::initialize();
}

void RankUp001::processBehavior() {
    RankUpScene::processBehavior();

    switch (_pProg->get()) {
        case RANKUPSCENE_PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp001::processBehavior() RANKUPSCENE_PROG_PLAYING Ç…Ç»ÇËÇ‹Ç∑ÇΩÅI");
            }

            if (_pProg->getFrameInProgress() == 300) {
                _TRACE_("RankUp001::processBehavior() RANKUPSCENE_PROG_PLAYING Ç®ÇÌÇ¡ÇΩ");
                _pProg->change(RANKUPSCENE_PROG_RESULT); //ÇØÇ¡Ç©ÇÕÇ“ÇÂÅ[Ç÷
            }
            break;
        }
    }

}

void RankUp001::processJudgement() {
}


void RankUp001::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}


RankUp001::~RankUp001() {

}
