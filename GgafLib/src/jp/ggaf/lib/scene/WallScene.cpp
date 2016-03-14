#include "jp/ggaf/lib/scene/WallScene.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallScene::WallScene(const char* prm_name) : DefaultScene(prm_name) {
    _obj_class |= Obj_WallScene;
    _class_name = "WallScene";
    _pDepo_wall = nullptr;
    _pLastSectionScene = nullptr;
    _is_all_active_section_scenes = false;
    _is_finished = false;
}

void WallScene::buildWallScene(
        coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height,
        coord prm_wall_start_x,
        WallSectionScene** prm_papSection, int prm_section_num,
        GgafActorDepository* prm_pDepo_wall) {
    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] build...");
    setScrollingFunction(WallScene::scrollX); //X�������X�N���[���֐�

    _pDepo_wall = prm_pDepo_wall;
    if (_pDepo_wall->getPlatformScene()) {
        //���ɏ������Ă���Ȃ��OK
    } else {
        bringDirector()->addSubGroup(_pDepo_wall); //������ initialize() �Ŗ{����
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]); //�z���V�[���ɏ���
        prm_papSection[i]->config(_pDepo_wall,
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
            WallSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallInfoLen[pSection->_area_len-1];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_F��ׂ� 0b111110
            }
        }
        //���ԁA�Ō�A�e�Z�N�V�����̍őO�u���b�N�ʂ̑SBOX��FACE_B�`���ׂ�
        for (int i = 1; i < prm_section_num; i++) {
            WallSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallInfoLen[0];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[0][j]._wall_draw_face &= 47; //FACE_B��ׂ� 0b111110
            }
        }
    }
    _ringHoldSection.first();
    _is_all_active_section_scenes = false;
    _pLastSectionScene = prm_papSection[prm_section_num-1];
    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] done");
}

void WallScene::initialize() {
    if (_pDepo_wall == nullptr) {
        throwGgafCriticalException("WallScene["<<getName()<<"] �I�u�W�F�N�g���������ł��BbuildWallScene()�����s���\�z���Ă��������B");
    }
    //buildWallScene ���p���N���X�̃R���X�g���N�^�Ŏ��s���ꂽ�ꍇ�AbringDirector() �͐��E�V�[����Ԃ�����
    //�ǃf�|�W�g���̏����V�[���͐��E�V�[�������ɂȂ��Ă���\��������B�A
    //�X�N���[��������s�����߂ɂ��A�ǃf�|�W�g�� �� this �̔z���ɒu���K�v�����邽�߁A�ȉ��̗l��
    //�z���V�[���ɍĐݒ肷��B
    bringDirector()->addSubGroup(_pDepo_wall->extract());
}

void WallScene::onActive() {
    WallSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
    pCurrentSection->activate();
}

void WallScene::processBehavior() {

    if (!_is_finished) {
        if (!_is_all_active_section_scenes) {

            const WallSectionScene* const pCurrentSection = _ringHoldSection.getCurrent();
            if (!pCurrentSection->isLast()) {
                if (pCurrentSection->_is_loop_end) {
                    WallSectionScene* const pNewSection = _ringHoldSection.next();
                    pNewSection->activate();
                    pNewSection->_pWallLast = pCurrentSection->getLastWallParts();
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
        //MassWallActor::_pWallSectionScene ���s���|�C���^�ɂȂ�Ȃ����߂̍l���ł���B
        for (int i = 0; i < _ringLoopEndSection.length(); i++) { //_ringLoopEndSection.length()�����[�J���ϐ��ɒu�������Ă͂����܂���
            WallSectionScene* const pSection =_ringLoopEndSection.next();
            const MassWallActor* const pWallLast = pSection->_pWallLast;
            if (pWallLast->_pWallSectionScene != pSection || !pWallLast->isActive() ) {
                //��������
                //pSection->_pWallLast->_pWallSectionScene != pSection �́A
                //pSection->_pWallLast �܂�ŏI�ǂ̕R�t���Z�N�V�����͂������łȂ��A
                //�܂�A���̃Z�N�V�����V�[���� dispatchForce() ���ꂽ����OK�A�ƍl�����B
                //�܂��A!pSection->_pWallLast->isActive() ��
                //���̃Z�N�V�����V�[���� dispatchForce() ���ꂸ�ɁA�����͈͊O�ɏ���������OK�A�ƍl�����B
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] �V�[���̃Z�N�V����["<<pSection->getName()<<"]inactivate!!");
                pSection->inactivateDelay(60*60);
                _ringLoopEndSection.remove();
                if (pSection == _pLastSectionScene) {
                    //�ŏI�Z�N�V�����Ȃ�Έ�x�R�[���o�b�N���s���A������C����B
                    //�i�ȑO�͂�����sayonara()�����Ă����j
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] �ŏI�Z�N�V�����V�[������������onFinishedAllSection() �R�[���o�b�N");
                    _is_finished = true;
                    onFinishedAllSection(); //�R�[���o�b�N
                }
            }
        }
    } else {
    }
}

void WallScene::processFinal() {
}

void WallScene::scrollX(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->instanceOf(Obj_GgafDxGeometricActor)) {
        GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
        if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
            pActor->_x -= (*((coord*)p1));
        }
    }
}

WallScene::~WallScene() {
}
