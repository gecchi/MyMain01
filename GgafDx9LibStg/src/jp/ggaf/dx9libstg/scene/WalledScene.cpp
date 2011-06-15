#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WalledScene::WalledScene(const char* prm_name) : ScrolledScene(prm_name) {
    _class_name = "WalledScene";
    _pDispatcher_WallAAB = NULL;
    _pDispatcher_WallAAPrism = NULL;
    _pRingSection = NEW GgafLinkedListRing<WalledSectionScene>();
}

void WalledScene::buildWalledScene(
        int prm_wall_dep, int prm_wall_width, int prm_wall_height,
        WalledSectionScene** prm_papSection, int prm_section_num,
        GgafActorDispatcher* prm_pDispatcher_WallAAB,
        GgafActorDispatcher* prm_pDispatcher_WallAAPrism) {
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] build...");
    _pDispatcher_WallAAB = prm_pDispatcher_WallAAB;
    _pDispatcher_WallAAPrism = prm_pDispatcher_WallAAPrism;
    getLordActor()->addSubGroup(_pDispatcher_WallAAB);
    if (_pDispatcher_WallAAPrism) {
        getLordActor()->addSubGroup(_pDispatcher_WallAAPrism);
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]);
        prm_papSection[i]->config(_pDispatcher_WallAAB, _pDispatcher_WallAAPrism, prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivateImmediately();
        _pRingSection->addLast(prm_papSection[i], false);
    }
    // 0b 00abcdef
    //
    //    c
    // a b d f
    //      e
    //
    //    FACE_A_BIT = 0b100000
    //    FACE_B_BIT = 0b010000
    //    FACE_C_BIT = 0b001000
    //    FACE_D_BIT = 0b000100
    //    FACE_E_BIT = 0b000010
    //    FACE_F_BIT = 0b000001
    //    A          = 0b111110 = 62
    //    A          = 0b101111 = 47

    //セクションつなぎ目のBOX描画の処理
    if (prm_section_num >= 2) {
        //最初、中間、各セクションの最末尾ブロック面の全BOXのFACE_F描画を潰す
        for (int i = 0; i < prm_section_num-1; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            for (int j = 0; j < pSection->_paWallInfoLen[pSection->_area_len-1]; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_Fを潰す 0b111110
            }
        }
        //中間、最後、各セクションの最前ブロック面の全BOXのFACE_B描画を潰す
        for (int i = 1; i < prm_section_num; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            for (int j = 0; j < pSection->_paWallInfoLen[0]; j++) {
                pSection->_papaWallInfo[0][j]._wall_draw_face &= 47; //FACE_Bを潰す 0b111110
            }
        }

    }
    _pRingSection->first();
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] done");
}

void WalledScene::initialize() {
    if (_pDispatcher_WallAAB == NULL) {
        throwGgafCriticalException("WalledScene["<<getName()<<"] オブジェクトが未完成です。buildWalledScene()を実行し構築してください。");
    }
}

void WalledScene::onActive() {
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    pCurrentSection->activate();
}

void WalledScene::processBehavior() {
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    if (!pCurrentSection->isLast()) {
        if (pCurrentSection->_is_loop_end) {
            WalledSectionScene* pNewSection = _pRingSection->next();
            pNewSection->activate();
            pNewSection->_pWallPartsLast = pCurrentSection->getLastWallParts();
            pCurrentSection->end(
                    120 + (GgafDx9Universe::_X_goneRight - GgafDx9Universe::_X_goneLeft) / getScroolSpeed()
                 );
        }
    } else {
        if (pCurrentSection->_is_loop_end) {
            end(120 + (GgafDx9Universe::_X_goneRight - GgafDx9Universe::_X_goneLeft) / getScroolSpeed());
        }
    }

}

void WalledScene::processFinal() {
}

WalledScene::~WalledScene() {
    DELETE_IMPOSSIBLE_NULL(_pRingSection);
}
