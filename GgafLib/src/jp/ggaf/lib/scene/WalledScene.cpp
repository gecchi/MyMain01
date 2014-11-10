#include "jp/ggaf/lib/scene/WalledScene.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"
#include "jp/ggaf/lib/actor/WallPartsActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WalledScene::WalledScene(const char* prm_name) : DefaultScene(prm_name) {
    _obj_class |= Obj_WalledScene;
    _class_name = "WalledScene";
    _pDepo_wall = nullptr;
    _pDepo_prism = nullptr;
    _pLastSectionScene = nullptr;
    _is_all_active_section_scenes = false;
    _is_finished = false;
}

void WalledScene::buildWalledScene(
        coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height,
        coord prm_wall_start_x,
        WalledSectionScene** prm_papSection, int prm_section_num,
        GgafActorDepository* prm_pDepo_wall,
        GgafActorDepository* prm_pDepo_prism) {
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] build...");
    setScrollingFunction(WalledScene::scrollX);

    _pDepo_wall = prm_pDepo_wall;
    _pDepo_prism = prm_pDepo_prism;
    if (_pDepo_wall->getPlatformScene()) {
        //���ɏ������Ă���Ȃ��OK
    } else {
        getSceneDirector()->addSubGroup(_pDepo_wall); //������ initialize() �Ŗ{����
    }
    if (_pDepo_prism) {
        if (_pDepo_prism->getPlatformScene()) {
            //���ɏ������Ă���Ȃ��OK
        } else {
            getSceneDirector()->addSubGroup(_pDepo_prism); //������ initialize() �Ŗ{����
        }
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]); //�z���V�[���ɏ���
        prm_papSection[i]->config(_pDepo_wall, _pDepo_prism,
                                  prm_wall_start_x,
                                  prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivate();
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
            int len = pSection->_paWallInfoLen[pSection->_area_len-1];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_F��ׂ� 0b111110
            }
        }
        //���ԁA�Ō�A�e�Z�N�V�����̍őO�u���b�N�ʂ̑SBOX��FACE_B�`���ׂ�
        for (int i = 1; i < prm_section_num; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallInfoLen[0];
            for (int j = 0; j < len; j++) {
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
    if (_pDepo_wall == nullptr) {
        throwGgafCriticalException("WalledScene["<<getName()<<"] �I�u�W�F�N�g���������ł��BbuildWalledScene()�����s���\�z���Ă��������B");
    }
    //buildWalledScene ���p���N���X�̃R���X�g���N�^�Ŏ��s���ꂽ�ꍇ�AgetSceneDirector() �͐��E�V�[����Ԃ�����
    //�ǃf�|�W�g���̏����V�[���͐��E�V�[�������ɂȂ��Ă���\��������B�A
    //�X�N���[��������s�����߂ɂ��A�ǃf�|�W�g�� �� this �̔z���ɒu���K�v�����邽�߁A�ȉ��̗l��
    //�z���V�[���ɍĐݒ肷��B
    getSceneDirector()->addSubGroup(_pDepo_wall->extract());
    if (_pDepo_prism) {
        getSceneDirector()->addSubGroup(_pDepo_prism->extract());
    }
}

void WalledScene::onActive() {
    WalledSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
    pCurrentSection->activate();
}

void WalledScene::processBehavior() {

    if (!_is_finished) {
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

        //_ringLoopEndSection�`�F�b�N
        //WallPartsActor::_pWalledSectionScene ���s���|�C���^�ɂȂ�Ȃ����߂̍l���ł���B
        for (int i = 0; i < _ringLoopEndSection.length(); i++) { //_ringLoopEndSection.length()�����[�J���ϐ��ɒu�������Ă͂����܂���
            WalledSectionScene* pSection =_ringLoopEndSection.next();
            if (pSection->_pWallPartsLast->_pWalledSectionScene != pSection || !pSection->_pWallPartsLast->isActive() ) {
                //��������
                //pSection->_pWallPartsLast->_pWalledSectionScene != pSection �́A
                //pSection->_pWallPartsLast �܂�ŏI�ǂ̕R�t���Z�N�V�����͂������łȂ��A
                //�܂�A���̃Z�N�V�����V�[���� dispatchForce() ���ꂽ����OK�A�ƍl�����B
                //�܂��A!pSection->_pWallPartsLast->isActive() ��
                //���̃Z�N�V�����V�[���� dispatchForce() ���ꂸ�ɁA�����͈͊O�ɏ���������OK�A�ƍl�����B
                _TRACE_("WalledScene::processBehavior() ["<<getName()<<"] �V�[���̃Z�N�V����["<<pSection->getName()<<"]inactivate!!");
                pSection->inactivateDelay(60*60);
                _ringLoopEndSection.remove();
                if (pSection == _pLastSectionScene) {
                    //�ŏI�Z�N�V�����Ȃ�Έ�x�R�[���o�b�N���s���A������C����B
                    //�i�ȑO�͂�����sayonara()�����Ă����j
                    _TRACE_("WalledScene::processBehavior() ["<<getName()<<"] �ŏI�Z�N�V�����V�[������������onFinishedAllSection() �R�[���o�b�N");
                    _is_finished = true;
                    onFinishedAllSection(); //�R�[���o�b�N
                }
            }
        }
    } else {
    }

}

void WalledScene::processFinal() {
}

void WalledScene::scrollX(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->instanceOf(Obj_GgafDxGeometricActor)) {
        GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
        if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
            pActor->_x -= (*((coord*)p1));
        }
    }
}

WalledScene::~WalledScene() {
}
