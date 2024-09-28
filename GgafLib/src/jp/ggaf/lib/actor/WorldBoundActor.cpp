#include "jp/ggaf/lib/actor/WorldBoundActor.h"

#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

using namespace GgafLib;

WorldBoundActor::WorldBoundActor(const char* prm_name, const char* prm_model) :
        GgafDx::WorldBoundActor(prm_name,
                              prm_model,
                              "WorldBoundEffect",
                              "WorldBoundTechnique") {

    _class_name = "WorldBoundActor";
    _offset_frames = 0;
    setHitAble(false);
    setZEnableDraw(false);   //Z�o�b�t�@�͍l������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setSpecialRenderDepthFar(0); //���ʂȍŔw�ʃ����_�����O�i��ԍŏ��ɕ`��j
    setFaceAngZero();
}

void WorldBoundActor::initialize() {
    DefaultCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
    setPositionAt(pCam);
    dxcoord world_r = pCam->getZFar(); //���E���E�����a
    dxcoord world_bound_model_r = 1.0f; //WorldBound001�̃��f���͔��aDIRECTX����1�̋��ł���
    setScaleR((world_r*0.989)/world_bound_model_r);
}


void WorldBoundActor::processSettlementBehavior() {
    DefaultCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
    //��ʊO���薳���ɔ��Ȃ������ȗ����B
    //���̏����𖳎����Ă��܂�
    //�E���g���{�[�����̍l��
    //�E�����ؓo�^
    //�E�����䂩��̋����v�Z
    //GeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    setPositionAt(pCam);
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    UTIL::setWorldMatrix_ScRxRzRyMv(this, _matWorld); //���[���h�ϊ�
}
//void WorldBoundActor::processPreDraw() {
//    //��ʊO���薳���ɔ��Ȃ������ȗ���
//    //���̏����𖳎����Ă��܂�
//    //�E�i�K�����_�����O�̐[�x�v�Z
//    //�E�ꎞ�e�N�j�b�N�l��
//    //FigureActor::processPreDraw() �Ɠ�������鎖�I
//    if (_pModel->_is_init_model == false) {
//        onCreateModel(); //���f���쐬���̏�������
//        _pModel->_is_init_model = true;
//    }
//    GgafDx::Spacetime::registerDrawActor(CONFIG::RENDER_DEPTH_INDEXS_NUM,this); //�Ő[��
//}

WorldBoundActor::~WorldBoundActor() {
}
