#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WalledScene::WalledScene(const char* prm_name) : ScrolledScene(prm_name) {
    _class_name = "WalledScene";
    _pDepo_WallAAB = NULL;
    _pDepo_WallAAPrism = NULL;
    _pRingSection = NEW GgafLinkedListRing<WalledSectionScene>();
}

void WalledScene::buildWalledScene(
        int prm_wall_dep, int prm_wall_width, int prm_wall_height,
        WalledSectionScene** prm_papSection, int prm_section_num,
        GgafActorDepository* prm_pDepo_WallAAB,
        GgafActorDepository* prm_pDepo_WallAAPrism) {
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] build...");
    _pDepo_WallAAB = prm_pDepo_WallAAB;
    _pDepo_WallAAPrism = prm_pDepo_WallAAPrism;
    getDirector()->addSubGroup(_pDepo_WallAAB);
    if (_pDepo_WallAAPrism) {
        getDirector()->addSubGroup(_pDepo_WallAAPrism);
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]);
        prm_papSection[i]->config(_pDepo_WallAAB, _pDepo_WallAAPrism, prm_wall_dep, prm_wall_width, prm_wall_height);
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

    //�Z�N�V�����Ȃ��ڂ�BOX�`��̏���
    if (prm_section_num >= 2) {
        //�ŏ��A���ԁA�e�Z�N�V�����̍Ŗ����u���b�N�ʂ̑SBOX��FACE_F�`���ׂ�
        for (int i = 0; i < prm_section_num-1; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            for (int j = 0; j < pSection->_paWallInfoLen[pSection->_area_len-1]; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_F��ׂ� 0b111110
            }
        }
        //���ԁA�Ō�A�e�Z�N�V�����̍őO�u���b�N�ʂ̑SBOX��FACE_B�`���ׂ�
        for (int i = 1; i < prm_section_num; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            for (int j = 0; j < pSection->_paWallInfoLen[0]; j++) {
                pSection->_papaWallInfo[0][j]._wall_draw_face &= 47; //FACE_B��ׂ� 0b111110
            }
        }

    }
    _pRingSection->first();
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] done");
}

void WalledScene::initialize() {
    if (_pDepo_WallAAB == NULL) {
        throwGgafCriticalException("WalledScene["<<getName()<<"] �I�u�W�F�N�g���������ł��BbuildWalledScene()�����s���\�z���Ă��������B");
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
                    120 + (GgafDxUniverse::_X_goneRight - GgafDxUniverse::_X_goneLeft) / getScroolSpeed()
                 );
        }
    } else {
        if (pCurrentSection->_is_loop_end) {
            end(120 + (GgafDxUniverse::_X_goneRight - GgafDxUniverse::_X_goneLeft) / getScroolSpeed());
        }
    }

}

void WalledScene::processFinal() {
}

WalledScene::~WalledScene() {
    DELETE_IMPOSSIBLE_NULL(_pRingSection);
}
