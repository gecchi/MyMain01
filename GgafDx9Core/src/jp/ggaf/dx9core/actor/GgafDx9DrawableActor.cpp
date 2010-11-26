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
    _obj_class |= Obj_GgafDx9DrawableActor;
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
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->refer();
    //�G�t�F�N�g�擾
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->refer();
    //�}�e���A�����R�s�[
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;
    //�ő勗�����_
    _fBoundingSphereRadius = _pGgafDx9Model->_fBoundingSphereRadius;
    _now_drawdepth = 0;
    _specal_drawdepth = -1;
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
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(model_name);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->refer();
    //�G�t�F�N�g�擾
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(effelct_name);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->refer();
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

    _now_drawdepth = 0;
    _specal_drawdepth = -1;
    _zenable = true;
    _zwriteenable = true;
}



void GgafDx9DrawableActor::processPreDraw() {
    if (_pGgafDx9Model->_is_init_model == false) {
        onCreateModel(); //���f���쐬���̏�������
        _pGgafDx9Model->_is_init_model = true;
    }

    _pNext_TheSameDrawDepthLevel = NULL;
    //TODO:�v����
    if (isActive()) {
        if (_isTransformed) {
            _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(
                                (int)(_z * MAX_DRAW_DEPTH_LEVEL),
                                this
                             );
        } else {
            if (isOutOfView()) {
                //�`�悵�Ȃ��̂œo�^�Ȃ�
            } else {
                //��������
                //�����J�����ʒu _cameraZ_org = -47.6701�A�\���͈͉��s��  _zf �� _dep=20�̂Ƃ��A_zf = -_cameraZ_org*(_dep+1); �Ƃ����ꍇ�̗�B�B
                //�u�Q�ƁFGgafDx9Camera::GgafDx9Camera()�v
                //�\���͈�(���s��:_zf)�̋����͏����J�����̈����ʒu������21�{�Ŗ� 1000(1001.0721) �ɂȂ�i���ꂪ _zf = -_cameraZ_org*20.0 �̈Ӗ��j
                //���� MAX_DRAW_DEPTH_LEVEL (����1000)�Ƃǂ̂悤�ɑΉ������邩
                //�{���C�u������DIRECTX���W��1�͌��_�t�߂̂ŉ�ʏ��10px�����Ƃ����v�Z���s���Ă���B�����
                //���̕��͖�10px�Ԋu�����̉�����̒i�K�����_�����O�̐ݒ�ƂȂ�
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront, this);
                //   (��_fDist_VpPlnFront�͎������O�ʂ���I�u�W�F�N�g�܂ł̋����̕���)
                //
                //����́A1000 �i�K�̐[�x����ƂȂ�B
                //�܂��A
                //
                //  GgafDx9Universe::setDrawDepthLevel(-1.0*_fDist_VpPlnFront*10.0, this);
                //
                //�����1px�Ԋu�����Ŗ� 10000 �i�K�ƂȂ�B
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
                if (_specal_drawdepth < 0) { //���ʂȕ`��[�x�w�薳��

                    float dep = -_fDist_VpPlnFront; //�I�u�W�F�N�g�̎��_����̋���(DIRECTX����)
                    static float roughly_dep_point1 = (P_CAM->_zf * 0.3); //�r���Ȃ�|�C���g�P(�J���������s�� 3/10 �̒n�_)(�� 300 DIRECTX����)
                    static float roughly_dep_point2 = (P_CAM->_zf * 0.6); //�r���Ȃ�|�C���g�Q(�J���������s�� 6/10 �̒n�_)(�� 600 DIRECTX����)

                    if (dep <= roughly_dep_point1) { //dep�� �` roughly_dep_point1 �܂ł̋����̃I�u�W�F�N�g��

                        _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(dep*0.5, this); //DirectX�̋���1��0.5�{�ADirectX�̋���2���[��1�B�����20px�Ԋu
                        // MAX_DRAW_DEPTH_LEVEL �� 0 �` (int)roughly_dep_point1 �܂ŃR�R�œ��Ă͂߂��邱�ƂɂȂ�
                        // ��L�̗�ł� 1001.07 * 0.3 = 300 ���ADIRECTX���� 0�`300 �ɑ΂� 300*0.5 = 150 �ł���̂�
                        // MAX_DRAW_DEPTH_LEVEL = 0 �` 150 �����蓖�Ă���
                    } else if (dep <= roughly_dep_point2) {
                        //dep �� roughly_dep_point1(300 DIRECTX����) �` roughly_dep_point2(600 DIRECTX����) �܂ł̋����̃I�u�W�F�N�g��
                        int offset_DRAW_DEPTH_LEVEL = roughly_dep_point1*0.5; //�i�K���x���I�t�Z�b�g = 150

                        _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL + ((dep - roughly_dep_point1) * 0.2), this);  //DirectX�̋���1��0.2�{�B�܂�DirectX�̋���5���[��1�B�����50px�Ԋu�Œi�K�����_
                        // (dep - roughly_dep_point1) * 0.2 �� dep �� roughly_dep_point2 �̏ꍇ
                        // (600 - 300) * 0.2 =  60�A�ƂȂ�̂�DIRECTX���� 300�`600 �ɑ΂��� MAX_DRAW_DEPTH_LEVEL �� 150�`210 �������œ��Ă͂߂���
                    } else {
                        //dep �� roughly_dep_point2(600) �` �̋����̃I�u�W�F�N�g��
                        //��� offset_DRAW_DEPTH_LEVEL + (dep - roughly_dep_point1) * 0.2) �� dep �� roughly_dep_point2���������l���I�t�Z�b�g�ł���
                        int offset_DRAW_DEPTH_LEVEL = (roughly_dep_point1*0.5) + ((roughly_dep_point2 - roughly_dep_point1) * 0.2);

                        _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(offset_DRAW_DEPTH_LEVEL  + ((dep - roughly_dep_point2) * 0.01), this); //0.01�{�B�܂�DirectX�̋���100���[��1�B�����1000px�Ԋu�Œi�K�����_
                    }
//                    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//                        _TRACE_("setDep ["<<_now_drawdepth<<"]:dep="<<dep<<" roughly_dep_point1="<<roughly_dep_point1<<" roughly_dep_point2="<<roughly_dep_point2<<" name="<<this->getName());
//                    }
                } else { //���ʂȕ`��[�x�w��L��
                    _now_drawdepth = GgafDx9Universe::setDrawDepthLevel(_specal_drawdepth, this);
//                    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//                        _TRACE_("_specal_drawdepth ["<<_now_drawdepth<<"]: name="<<this->getName());
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
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
	_pGgafDx9EffectCon->close();
    _pGgafDx9ModelCon->close();
}
