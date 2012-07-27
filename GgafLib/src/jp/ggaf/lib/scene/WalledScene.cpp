#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WalledScene::WalledScene(const char* prm_name) : ScrolledScene(prm_name) {
    _class_name = "WalledScene";
    _pDepo_WallAAB = NULL;
    _pDepo_WallAAPrism = NULL;
    _pLastSectionScene = NULL;
    _is_all_active_section_scenes = false;
}

void WalledScene::buildWalledScene(
        coord prm_wall_dep, int prm_wall_width, int prm_wall_height,
        WalledSectionScene** prm_papSection, int prm_section_num,
        GgafActorDepository* prm_pDepo_WallAAB,
        GgafActorDepository* prm_pDepo_WallAAPrism) {
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] build...");
    _pDepo_WallAAB = prm_pDepo_WallAAB;
    _pDepo_WallAAPrism = prm_pDepo_WallAAPrism;
    if (_pDepo_WallAAB->getPlatformScene()) {
        //���ɏ������Ă���Ȃ��OK
    } else {
        getDirector()->addSubGroup(_pDepo_WallAAB); //������ initialize() �Ŗ{����
    }
    if (_pDepo_WallAAPrism) {
        if (_pDepo_WallAAPrism->getPlatformScene()) {
            //���ɏ������Ă���Ȃ��OK
        } else {
            getDirector()->addSubGroup(_pDepo_WallAAPrism); //������ initialize() �Ŗ{����
        }
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]); //�z���V�[���ɏ���
        prm_papSection[i]->config(_pDepo_WallAAB, _pDepo_WallAAPrism, prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivateImmed();
        _ringHoldSection.addLast(prm_papSection[i], false);
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
    _ringHoldSection.first();
    _is_all_active_section_scenes = false;
    _pLastSectionScene = prm_papSection[prm_section_num-1];
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] done");
}

void WalledScene::initialize() {
    if (_pDepo_WallAAB == NULL) {
        throwGgafCriticalException("WalledScene["<<getName()<<"] �I�u�W�F�N�g���������ł��BbuildWalledScene()�����s���\�z���Ă��������B");
    }
    //buildWalledScene ���p���N���X�̃R���X�g���N�^�Ŏ��s���ꂽ�ꍇ�AgetDirector() �͐��E�V�[����Ԃ�����
    //�ǃf�|�W�g���̏����V�[���͐��E�V�[�������ɂȂ��Ă���\��������B�A
    //�X�N���[��������s�����߂ɂ��A�ǃf�|�W�g�� �� this �̔z���ɒu���K�v�����邽�߁A�ȉ��̗l��
    //�z���V�[���ɍĐݒ肷��B
    getDirector()->addSubGroup(_pDepo_WallAAB->extract());
    if (_pDepo_WallAAPrism) {
        getDirector()->addSubGroup(_pDepo_WallAAPrism->extract());
    }
}

void WalledScene::onActive() {
    WalledSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
    pCurrentSection->activate();
}

void WalledScene::processBehavior() {
    if (!_is_all_active_section_scenes) {

        WalledSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
        if (!pCurrentSection->isLast()) {
            if (pCurrentSection->_is_loop_end) {
                WalledSectionScene* pNewSection = _ringHoldSection.next();
                pNewSection->activate();
                pNewSection->_pWallPartsLast = pCurrentSection->getLastWallParts();
                _ringLoopEndSection.addLast(pCurrentSection, false);
            }
        } else {
            if (pCurrentSection->_is_loop_end) {
                _ringLoopEndSection.addLast(pCurrentSection, false);
                _is_all_active_section_scenes = true;
            }
        }
    }
    ScrolledScene::processBehavior();

    //_ringLoopEndSection�`�F�b�N
    //WallPartsActor::_pWalledSectionScene ���s���|�C���^�ɂȂ�Ȃ����߂̍l���ł���B
    for (int i = 0; i < _ringLoopEndSection.length(); i++) {
        WalledSectionScene* pSection =_ringLoopEndSection.next();
        if (pSection->_pWallPartsLast->_pWalledSectionScene != pSection || !pSection->_pWallPartsLast->isActive() ) {
            //��������
            //pSection->_pWallPartsLast->_pWalledSectionScene != pSection �́A
            //pSection->_pWallPartsLast �܂�ŏI�ǂ̕R�t���Z�N�V�����͂������łȂ��A
            //�܂�A���̃Z�N�V�����V�[���� dispatchForce() ���ꂽ����OK�A�ƍl�����B
            //�܂��A!pSection->_pWallPartsLast->isActive() ��
            //���̃Z�N�V�����V�[���� dispatchForce() ���ꂸ�ɁA�����͈͊O�ɏ���������OK�A�ƍl�����B
            pSection->end(60*10); //����I
            _TRACE_("WalledScene::processBehavior() ["<<getName()<<"]�V�[���̃Z�N�V����["<<pSection->getName()<<"]��end!!");
            _ringLoopEndSection.remove();
            if (pSection == _pLastSectionScene) {
                //�ŏI�Z�N�V�����Ȃ�Ύ��g�̃V�[�������
                end(60*20);
                _TRACE_("WalledScene::processBehavior() �ŏI�Z�N�V�����V�[�����������߁B["<<getName()<<"]�V�[�����g��end!!");
            }
        }
    }

}

void WalledScene::processFinal() {
}

WalledScene::~WalledScene() {
}
