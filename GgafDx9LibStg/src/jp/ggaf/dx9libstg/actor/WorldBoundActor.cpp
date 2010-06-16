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
    _frame_offset = 0;
    _pScaler = NEW GgafDx9GeometryScaler(this);
    chengeEffectTechnique("NoLight"); //NoLight�Ńx�^�h��e�N�j�b�N
    defineWorldMatrix(GgafDx9Util::setWorldMatrix_ScMv); //�g��~���s�ړ��̂�
}

void WorldBoundActor::processPreJudgement() {
    //��ʊO���薳���ɔ��Ȃ������ȗ����B
    //���̏����𖳎����Ă��܂�
    //�E���g���{�[�����̍l��
    //�E�W���ؓo�^
    //�E�����䂩��̋����v�Z
    //GgafDx9GeometricActor::processPreJudgement() �Ɠ�������鎖�I
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    //(*_pFunc_calcWorldMatrix)(this, _matWorld); //���[���h�ϊ��s��
}
void WorldBoundActor::processPreDraw() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //���̏����𖳎����Ă��܂�
    //�E�i�K�����_�����O�̐[�x�v�Z
    //�E�ꎞ�e�N�j�b�N�l��
    //GgafDx9DrawableActor::processPreDraw() �Ɠ�������鎖�I
    GgafDx9Universe::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL - MAX_DRAW_DEPTH_LEVEL/100 ,this); //�Ő[��
}

WorldBoundActor::~WorldBoundActor() {
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
