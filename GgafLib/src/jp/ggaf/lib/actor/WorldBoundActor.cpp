#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WorldBoundActor::WorldBoundActor(const char* prm_name, const char* prm_model) :
        GgafDxWorldBoundActor(prm_name,
                               prm_model,
                               "WorldBoundEffect",
                               "WorldBoundTechnique",
                               NULL,
                               NULL) {

    _class_name = "WorldBoundActor";
    _offset_frames = 0;
    _pScaler = NEW GgafDxScaler(this);
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND);

    setZEnable(false);        //Z�o�b�t�@�͍l������
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}
void WorldBoundActor::initialize() {
    dxcoord dxworld_r = P_CAM->_zf-P_CAM->_zn; //���E���E�����a
    dxcoord dxmodel_r = 1.0f; //WorldBoundActor�̃��f���͔��aDIRECTX����1�̋��ł��鎖�O��
    _SX = _SY = _SZ = R_SC(dxworld_r/dxmodel_r)*0.989;
}


void WorldBoundActor::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ����B
    //���̏����𖳎����Ă��܂�
    //�E���g���{�[�����̍l��
    //�E�W���ؓo�^
    //�E�����䂩��̋����v�Z
    //GgafDxGeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    locateWith(P_CAM);
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    UTIL::setWorldMatrix_ScRxRzRyMv(this, _matWorld); //���[���h�ϊ�
}
//void WorldBoundActor::processPreDraw() {
//    //��ʊO���薳���ɔ��Ȃ������ȗ���
//    //���̏����𖳎����Ă��܂�
//    //�E�i�K�����_�����O�̐[�x�v�Z
//    //�E�ꎞ�e�N�j�b�N�l��
//    //GgafDxDrawableActor::processPreDraw() �Ɠ�������鎖�I
//    if (_pModel->_is_init_model == false) {
//        onCreateModel(); //���f���쐬���̏�������
//        _pModel->_is_init_model = true;
//    }
//    GgafDxUniverse::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL,this); //�Ő[��
//}

WorldBoundActor::~WorldBoundActor() {
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
