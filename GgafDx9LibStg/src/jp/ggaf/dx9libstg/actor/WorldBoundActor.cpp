#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WorldBoundActor::WorldBoundActor(const char* prm_name, const char* prm_model) :
        GgafDx9SpriteMeshActor(prm_name,
                               prm_model,
                               NULL) {

    _class_name = "WorldBoundActor";
    _offset_frames = 0;
    _pScaler = NEW GgafDx9Scaler(this);
    changeEffectTechnique("NoLight"); //NoLight�Ńx�^�h��e�N�j�b�N
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_ScMv); //�g��~���s�ړ��̂�
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL);
}

void WorldBoundActor::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ����B
    //���̏����𖳎����Ă��܂�
    //�E���g���{�[�����̍l��
    //�E�W���ؓo�^
    //�E�����䂩��̋����v�Z
    //GgafDx9GeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    locateAs(P_CAM);
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //���[���h�ϊ�
}
//void WorldBoundActor::processPreDraw() {
//    //��ʊO���薳���ɔ��Ȃ������ȗ���
//    //���̏����𖳎����Ă��܂�
//    //�E�i�K�����_�����O�̐[�x�v�Z
//    //�E�ꎞ�e�N�j�b�N�l��
//    //GgafDx9DrawableActor::processPreDraw() �Ɠ�������鎖�I
//    if (_pGgafDx9Model->_is_init_model == false) {
//        onCreateModel(); //���f���쐬���̏�������
//        _pGgafDx9Model->_is_init_model = true;
//    }
//    GgafDx9Universe::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL,this); //�Ő[��
//}

WorldBoundActor::~WorldBoundActor() {
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
