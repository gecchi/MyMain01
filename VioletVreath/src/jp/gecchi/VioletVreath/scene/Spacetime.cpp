#include "Spacetime.h"


#include "jp/ggaf/core/util/LinearQuadtree.h"
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"

using namespace GgafLib;
using namespace VioletVreath;

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : DefaultSpacetime(prm_name, prm_pCamera) {
    _class_name = "Spacetime";
    pWorld_ = nullptr;
    _TRACE_(FUNC_NAME<<"");
    pCameraWorkerChanger_ = NEW VVCameraWorkerChanger("CameraWorkerChanger", prm_pCamera);
    bringSceneMediator()->appendGroupChild(pCameraWorkerChanger_);
    //�y�߂��z
    //������Actor��Scene��NEW�����Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void Spacetime::initialize() {
    pWorld_ = desireScene(VioletVreath::World);
    appendChild(pWorld_);
    _TRACE_(FUNC_NAME<<"");
}

void Spacetime::processBehavior() {
    DefaultSpacetime::processBehavior();
}

void Spacetime::processJudgement() {
    DefaultSpacetime::processJudgement();

    if (getBehaveingFrame() >= 120) {
#ifdef MY_DEBUG
        WorldCollisionChecker::_num_check = 0;
#endif
        //�{�V�[���̏����V�[���̏����A�N�^�[�S�Ăɂ��ē����蔻��`�F�b�N���s���B
        //��ԕ���(������)�A���S���Y���ɂ��A�`�F�b�N�񐔂̍œK�����s���Ă��܂��B
        //�ڍׂ� �u��ʑ��֒�`�R�s�y�c�[��.xls�v �� �u��ʑ��ցv �V�[�g�Q��
#ifdef MY_DEBUG
        if (GgafDx::Input::isPushedDownKey(DIK_I)) {
           getLinearOctree()->putTree();
        }
#endif
        //�����؃A���S���Y���Ńq�b�g�`�F�b�N
        executeWorldHitCheck(KIND_CHIKEI, KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT);
        executeWorldHitCheck(KIND_ITEM, KIND_MY_BODY_CHIKEI_HIT);
        executeWorldHitCheck(KIND_MY, KIND_ENEMY_BODY);
        executeWorldHitCheck(KIND_ENEMY_SHOT, KIND_MY_BODY);

#ifdef MY_DEBUG
        if (GgafDx::Input::isPushedDownKey(DIK_J)) {
            _TRACE_("Board�p�l���� -->");
            _pLinearQuadtree_b->putTree();
            _TRACE_("<--Board�p�l����");
        }
#endif
        executeViewHitCheck(KIND_2DFIX_MOUSE_POINTER, KIND_2DFIX_MENU_ITEM);
    }
}

Spacetime::~Spacetime() {
}
