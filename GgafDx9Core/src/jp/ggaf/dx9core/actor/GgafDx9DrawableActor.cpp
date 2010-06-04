#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

unsigned int GgafDx9DrawableActor::_hash_technique_last_draw = 0;

GgafDx9DrawableActor::GgafDx9DrawableActor(const char* prm_name,
                                           const char* prm_model,
                                           const char* prm_effect,
                                           const char* prm_technique,
                                           GgafDx9Checker* prm_pChecker) :
  GgafDx9GeometricActor(prm_name, prm_pChecker) {
    _actor_class |= Obj_GgafDx9DrawableActor;
    _class_name = "GgafDx9DrawableActor";

    //_TRACE_("GgafDx9DrawableActor::GgafDx9DrawableActor(");
    //_TRACE_("    prm_name="<<prm_name);
    //_TRACE_("    prm_model="<<prm_model);
    //_TRACE_("    prm_effect="<<prm_effect);
    //_TRACE_("    prm_technique="<<prm_technique);
    //_TRACE_(")");

    _hash_technique = GgafUtil::easy_hash(prm_technique);
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _technique_temp = NEW char[51];
    _hash_technique = 0;
    _frame_temp_technique = 0;
    _is_temp_technique = false;

    _pNext_TheSameDrawDepthLevel = NULL;
    //���f���擾
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->connect(prm_model);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //�G�t�F�N�g�擾
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->connect(prm_effect);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //�}�e���A�����R�s�[
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;
    //�ő勗�����_
    _fBoundingSphereRadius = _pGgafDx9Model->_fBoundingSphereRadius;

    _now_drawdepth = 0;

}


GgafDx9DrawableActor::GgafDx9DrawableActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_model_type,
                                           const char* prm_effect_id,
                                           const char* prm_effect_type,
                                           const char* prm_technique,
                                           GgafDx9Checker* prm_pChecker) :
  GgafDx9GeometricActor(prm_name, prm_pChecker) {

//_TRACE_("GgafDx9DrawableActor::GgafDx9DrawableActor(");
//_TRACE_("    prm_name="<<prm_name);
//_TRACE_("    prm_model_id="<<prm_model_id);
//_TRACE_("    prm_model_type="<<prm_model_type);
//_TRACE_("    prm_effect_id="<<prm_effect_id);
//_TRACE_("    prm_effect_type="<<prm_effect_type);
//_TRACE_("    prm_technique="<<prm_technique);
//_TRACE_(")");

    _class_name = "GgafDx9DrawableActor";
    _hash_technique = GgafUtil::easy_hash(prm_technique);
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _technique_temp = NEW char[51];
    _hash_technique = 0;
    _frame_temp_technique = 0;
    _is_temp_technique = false;

    char* model_name = NEW char[51];
    model_name[0] = '\0';
    strcat(model_name, prm_model_type);
    strcat(model_name, "/");
    strcat(model_name, prm_model_id);
    // prm_model_id   = "Ceres"
    // prm_model_type = "X"
    // �̏ꍇ�Amodel_name �Ƃ���
    // model_name     = "X/Ceres"
    // �Ƃ�����������쐬�B

    char* effelct_name = NEW char[51];
    effelct_name[0] = '\0';
    strcat(effelct_name, prm_effect_type);
    strcat(effelct_name, "/");
    strcat(effelct_name, prm_effect_id);
    // prm_effect_id   = "DefaultMeshEffect"
    // prm_effect_type = "X"
    // �̏ꍇ�Aeffelct_name �Ƃ���
    // effelct_name     = "X/DefaultMeshEffect"
    // �Ƃ�����������쐬�B

    _pNext_TheSameDrawDepthLevel = NULL;
    //���f���擾
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->connect(model_name);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //�G�t�F�N�g�擾
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->connect(effelct_name);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //�}�e���A�����R�s�[
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;

    //�ő勗�����_
    _fBoundingSphereRadius = _pGgafDx9Model->_fBoundingSphereRadius;

    DELETEARR_IMPOSSIBLE_NULL(model_name);
    DELETEARR_IMPOSSIBLE_NULL(effelct_name);
}



void GgafDx9DrawableActor::processPreDraw() {
    _pNext_TheSameDrawDepthLevel = NULL;
    //TODO:�v����
    if (_is_active_flg && _can_live_flg) {
        if (_isTransformed) {
            _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(
                                (int)(_z * MAX_DRAW_DEPTH_LEVEL),
                                this
                             );
        } else {
            if (isOffscreen()) {
                //�`�悵�Ȃ��̂œo�^�Ȃ�
            } else {
                //��������
                //�����J�����ʒu _cameraZ_org = -47.6701�A�\���͈͉��s���́A_zf = -_cameraZ_org*20.0; �Ƃ����ꍇ�̗�B
                //�u�Q�ƁFGgafDx9Camera::GgafDx9Camera()�v
                //�\���͈�(���s��:_zf)�̋����͏����J�����̈����ʒu������10�{�Ŗ� 571.0 �ɂȂ�i���ꂪ _zf = -_cameraZ_org*10.0 �̈Ӗ��j
                //���� MAX_DRAW_DEPTH_LEVEL (����1000)�Ƃǂ̂悤�ɑΉ������邩
                //�{���C�u������DIRECTX���W��1�͌��_�t�߂̂ŉ�ʏ��10px�����Ƃ����v�Z���s���Ă���B�����
                //���̕��͖�10px�Ԋu�����̉�����̒i�K�����_�����O�̐ݒ�ƂȂ�
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront, this);
                //   (��_fDist_VpPlnFront�͎������O�ʂ���I�u�W�F�N�g�܂ł̋����̕���)
                //
                //����́A571 �i�K�̐[�x����ƂȂ�B
                //�܂��A
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront*10.0, this);
                //
                //�����1px�Ԋu�����Ŗ� 5710 �i�K�ƂȂ邪�AMAX_DRAW_DEPTH_LEVEL��1000�Ȃ��
                //4710�`5710�i�K�ڂ͑S�čŐ[�̂Ƃ��ē���[�x�ň����Ă��܂��B
                //MAX_DRAW_DEPTH_LEVEL�𑝂₹�Ζ��Ȃ����A600�i�K���炢�������̖��p�t�H�[�}���X�I�ɂ��傤�ǂ悳���ł���B
                //�Ȃ�Ƃ�600�i�K���炢�őΉ��i�K�����_�����O���悤�ƍl�����B
                //
                //�͂邩�����I�u�W�F�N�g�B���ׂ����i�K�`�悵�Ă����܂����Ȃ��ƍl�����B
                //�J�����ɋ߂��قǐ����ɁA�����قǃA�o�E�g�ɒi�K�����_�����O�������ƍl�����B
                //
                //  <o   |-+-+-+-+-+-+-+-+-+-+-+-+-+--+---+----+-----+------+------+-------+-----
                //              ------> ��         ^            ------> ��                        ^
                // �J����                   �A�o�E�g�Ԋu�J�n�[�x                                 �Ő[��
                //
                //��}�̂悤�ȃC���[�W�i�K�I�ɍr�����Ă������I
                //�y�Q�l�z
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera ��ʃA�X�y�N�g�F1.33333
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera FovX=1.39626 FovY=1.12341
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera �J�����̈ʒu(0,0,-47.6701)
                //   7975036 <DEBUG> GgafDx9Camera::GgafDx9Camera �͈� [0.01 ~ 1001.07]
                //
                // 1001.07 �܂��10000px�����̉��s����`��

                float dep = -_fDist_VpPlnFront; //�I�u�W�F�N�g�̎��_����̋���(DIRECTX����)
                static float roughly_dep_point1 = ((pCAM->_zf) * (5.0/10.0)); //�r���Ȃ�|�C���g�P(�J���������s�� 5/10 �̒n�_)( 500.535 DIRECTX����)
                static float roughly_dep_point2 = ((pCAM->_zf) * (8.0/10.0)); //�r���Ȃ�|�C���g�Q(�J���������s�� 8/10 �̒n�_)( 800.856 DIRECTX����)

                if (dep <= roughly_dep_point1) { //dep�� �` roughly_dep_point1 �܂ł̋����̃I�u�W�F�N�g��

                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(dep, this); //DirectX�̋���1���[��1�B�����10px�Ԋu
                    // MAX_DRAW_DEPTH_LEVEL �� 0 �` (int)roughly_dep_point1 �܂ŃR�R�œ��Ă͂߂��邱�ƂɂȂ�
                    // ��L�̗�ł� 1001.07 * (5.0/10.0) = 500.535
                    // MAX_DRAW_DEPTH_LEVEL = 0 �` 500 ���g�p�����
//                    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//                        _TRACE_(GgafGod::_pGod->_godframe<<"\t"<<getName()<<"\t"<<dep<<"\t"<<_now_drawdepth<<"\t1\tinfo\tOffset=0\t"<<pCAM->_zf<<"\t"<<roughly_dep_point1<<"\t"<<roughly_dep_point2<<"\t");
//                    }
                } else if (dep <= roughly_dep_point2) {
                    //dep �� roughly_dep_point1(500.535) �` roughly_dep_point2(800.856) �܂ł̋����̃I�u�W�F�N�g��
                    int offset_DRAW_DEPTH_LEVEL = roughly_dep_point1; //�I�t�Z�b�g

                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL + ((dep - roughly_dep_point1) * 0.2), this);  //0.2�{�B�܂�DirectX�̋���5���[��1�B�����50px�Ԋu�Œi�K�����_
                    // (dep - roughly_dep_point1) * 0.2 �� dep �� roughly_dep_point2 �̏ꍇ
                    // (800.856 - 500.535) * 0.2 =  550.5885 �ƂȂ�̂�
                    // MAX_DRAW_DEPTH_LEVEL �� 500 �`  550 �������œ��Ă͂߂���
//                    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//                        _TRACE_(GgafGod::_pGod->_godframe<<"\t"<<getName()<<"\t"<<dep<<"\t"<<_now_drawdepth<<"\t2\tinfo\tOffset="<<offset_DRAW_DEPTH_LEVEL<<"\t"<<pCAM->_zf<<"\t"<<roughly_dep_point1<<"\t"<<roughly_dep_point2<<"\t");
//                    }
                } else {
                    //dep �� roughly_dep_point2(800.856) �` �܂ł̋����̃I�u�W�F�N�g��
                    //��� offset_DRAW_DEPTH_LEVEL + (dep - roughly_dep_point1) * 0.2) �� dep �� roughly_dep_point2���������l���I�t�Z�b�g�ł���
                    int offset_DRAW_DEPTH_LEVEL = roughly_dep_point1 + ((roughly_dep_point2 - roughly_dep_point1) * 0.2);

                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL  + ((dep - roughly_dep_point2) * 0.04), this); //0.04�{�B�܂�DirectX�̋���25���[��1�B�����250px�Ԋu�Œi�K�����_
//                    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//                        _TRACE_(GgafGod::_pGod->_godframe<<"\t"<<getName()<<"\t"<<dep<<"\t"<<_now_drawdepth<<"\t3\tinfo\tOffset="<<offset_DRAW_DEPTH_LEVEL<<"\t"<<pCAM->_zf<<"\t"<<roughly_dep_point1<<"\t"<<roughly_dep_point2<<"\t");
//                    }
                }


            }
        }
    }

    //�ꎞ�e�N�j�b�N���ԃ`�F�b�N
    if (_is_temp_technique) {
        if (_frame_temp_technique <= _frame_of_behaving) {
            //�ꎞ�e�N�j�b�N���Ԗ����B���ɖ߂�
            _hash_technique = _hash_technique_temp;
            strcpy(_technique, _technique_temp);
            _is_temp_technique = false;
            //����̓_���B�z��̈悪�ǂ����ɂ������߁B_technique_temp = "";
            _hash_technique_temp = 0;
        }
    }

}


#ifdef MY_DEBUG

void GgafDx9DrawableActor::processAfterDraw() {
    //�����蔻��̈�\��
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        drawHitArea();
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void GgafDx9DrawableActor::processAfterDraw() {}

#endif



void GgafDx9DrawableActor::setMaterialColor(float r, float g, float b) {
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.r = r;
        _paD3DMaterial9[i].Diffuse.r = r;
        _paD3DMaterial9[i].Ambient.g = g;
        _paD3DMaterial9[i].Diffuse.g = g;
        _paD3DMaterial9[i].Ambient.b = b;
        _paD3DMaterial9[i].Diffuse.b = b;
    }
}

void GgafDx9DrawableActor::resetMaterialColor() {
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.r = _pGgafDx9Model->_paD3DMaterial9_default[i].Ambient.r;
        _paD3DMaterial9[i].Diffuse.r = _pGgafDx9Model->_paD3DMaterial9_default[i].Diffuse.r;
        _paD3DMaterial9[i].Ambient.g = _pGgafDx9Model->_paD3DMaterial9_default[i].Ambient.g;
        _paD3DMaterial9[i].Diffuse.g = _pGgafDx9Model->_paD3DMaterial9_default[i].Diffuse.g;
        _paD3DMaterial9[i].Ambient.b = _pGgafDx9Model->_paD3DMaterial9_default[i].Ambient.b;
        _paD3DMaterial9[i].Diffuse.b = _pGgafDx9Model->_paD3DMaterial9_default[i].Diffuse.b;
    }
}


GgafDx9DrawableActor::~GgafDx9DrawableActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    DELETEARR_IMPOSSIBLE_NULL(_technique_temp);
    _pGgafDx9ModelCon->close();
    _pGgafDx9EffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
