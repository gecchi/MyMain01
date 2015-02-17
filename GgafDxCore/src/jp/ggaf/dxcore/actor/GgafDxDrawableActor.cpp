#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/scene/GgafDxScene.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxAlphaCurtain.h"
#include "jp/ggaf/core/util/GgafRgb.h"

using namespace GgafCore;
using namespace GgafDxCore;

hashval GgafDxDrawableActor::_hash_technique_last_draw = 0;

GgafDxDrawableActor::GgafDxDrawableActor(const char* prm_name,
                                         const char* prm_model,
                                         const char* prm_effect,
                                         const char* prm_technique,
                                         GgafStatus* prm_pStat,
                                         GgafDxChecker* prm_pChecker) :
  GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker),
_pModelCon((GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(
                  std::string(prm_model).c_str(),
                  this)),
_pModel((GgafDxModel*)_pModelCon->peek()),
_pEffectCon((GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(
                  std::string(prm_effect).c_str(),
                  this)),
_pEffect((GgafDxEffect*)_pEffectCon->peek()) {

    _obj_class |= Obj_GgafDxDrawableActor;
    _class_name = "GgafDxDrawableActor";

    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _hash_technique = 0;

    _temp_technique = NEW char[51];
    _hash_temp_technique = 0;

    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;
    _pNextActor_in_draw_depth_level = nullptr;
//    //���f���擾connectModelManager
//    _pModelCon = (GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(prm_model, this);
//    _pModel = (GgafDxModel*)_pModelCon->peek();
//    //�G�t�F�N�g�擾
//    _pEffectCon = (GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(prm_effect, this);
//    _pEffect = (GgafDxEffect*)_pEffectCon->peek();
    //�}�e���A�����R�s�[
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;
    //�ő勗�����_
    _now_drawdepth = 0;
    _specal_drawdepth = -1;
    _zenable = true;
    _zwriteenable = true;
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
}

GgafDxDrawableActor::GgafDxDrawableActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_model_type,
                                         const char* prm_effect_id,
                                         const char* prm_effect_type,
                                         const char* prm_technique,
                                         GgafStatus* prm_pStat,
                                         GgafDxChecker* prm_pChecker) :
  GgafDxGeometricActor(prm_name, prm_pStat, prm_pChecker),
_pModelCon((GgafDxModelConnection*)GgafDxGod::_pModelManager->connect(
                    (std::string(prm_model_type) + std::string("/") + std::string(prm_model_id)).c_str(),
                    this)),
_pModel((GgafDxModel*)_pModelCon->peek()),
_pEffectCon((GgafDxEffectConnection*)GgafDxGod::_pEffectManager->connect(
                    (std::string(prm_effect_type) + std::string("/") + std::string(prm_effect_id)).c_str(),
                    this)),
_pEffect((GgafDxEffect*)_pEffectCon->peek())
          {

    _class_name = "GgafDxDrawableActor";

    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    _hash_technique = 0;

    _temp_technique = NEW char[51];
    _hash_temp_technique = 0;

    _frame_of_behaving_temp_technique_end = 0;
    _is_temp_technique = false;

//    char* model_name = NEW char[51];
//    model_name[0] = '\0';
//    strcat(model_name, prm_model_type);
//    strcat(model_name, "/");
//    strcat(model_name, prm_model_id);
//    // prm_model_id   = "Eres"
//    // prm_model_type = "X"
//    // �̏ꍇ�Amodel_name �Ƃ���
//    // model_name     = "X/Eres"
//    // �Ƃ�����������쐬�B
//
//    char* effelct_name = NEW char[51];
//    effelct_name[0] = '\0';
//    strcat(effelct_name, prm_effect_type);
//    strcat(effelct_name, "/");
//    strcat(effelct_name, prm_effect_id);
//    // prm_effect_id   = "DefaultMeshEffect"
//    // prm_effect_type = "X"
//    // �̏ꍇ�Aeffelct_name �Ƃ���
//    // effelct_name     = "X/DefaultMeshEffect"
//    // �Ƃ�����������쐬�B

    _pNextActor_in_draw_depth_level = nullptr;

    //�}�e���A�����R�s�[
    _paMaterial = NEW D3DMATERIAL9[_pModel->_num_materials];
    for (DWORD i = 0; i < _pModel->_num_materials; i++){
        _paMaterial[i] = _pModel->_paMaterial_default[i];
    }
    _alpha = 1.0f;

//    GGAF_DELETEARR(model_name);
//    GGAF_DELETEARR(effelct_name);

    _now_drawdepth = 0;
    _specal_drawdepth = -1;
    _zenable = true;
    _zwriteenable = true;
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
}

void GgafDxDrawableActor::processPreDraw() {
    GgafDxCamera* pCam = P_GOD->getUniverse()->getCamera();
#ifdef MY_DEBUG
    if (getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxDrawableActor::processPreDraw() name="<<getName()<<"��`��o�^���悤�Ƃ��܂������A�����V�[���� name="<<getName()<<"->getPlatformScene()["<<(getPlatformScene()->getName())<<"]���AGgafDxScene �ɕϊ��s�ł��Bthis="<<this<<" \n"<<
                "getPlatformScene()->_obj_class="<<getPlatformScene()->_obj_class<< " Obj_GgafDxScene="<<Obj_GgafDxScene<<" \n"<<
                "(getPlatformScene()->_obj_class & Obj_GgafDxScene)="<<((getPlatformScene()->_obj_class) & Obj_GgafDxScene) <<" ==?? Obj_GgafDxScene("<<Obj_GgafDxScene<<")");
    }
#endif
    if (_pModel->_is_init_model == false) {
        onCreateModel(); //���f���쐬���̏�������
        _pModel->_is_init_model = true;
    }
    _pNextActor_in_draw_depth_level = nullptr;
    //TODO:�v����
    if (_alpha > 0.0f && isActiveInTheTree()) { //isActiveInTheTree() �Ŕ��肷��ƁA
        if (_is_2D) {
//            _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
//                                (int)((1.0*_z/LEN_UNIT) * MAX_DRAW_DEPTH_LEVEL),
//                                this
//                             );
            if (((GgafDxScene*)getPlatformScene())->_master_alpha <= 0.0f) {
                //�`�悵�Ȃ��̂œo�^�Ȃ�
            } else {
                if (_specal_drawdepth < 0) { //���ʂȕ`��[�x�w�薳��
                    _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(_z, this); //2D��_z�̓v���C�I���e�B�Ɏg�p�B
                } else {
                    //���ʂȕ`��[�x�w��L��
                    if (GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth] == nullptr) {
                        //����prm_draw_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
                        this->_pNextActor_in_draw_depth_level = nullptr;
                        GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth] = this;
                        GgafDxUniverse::_apLastActor_draw_depth_level[_specal_drawdepth] = this;
                    } else {
                        //�O�ɒǉ�
                        GgafDxDrawableActor* pActorTmp = GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth];
                        this->_pNextActor_in_draw_depth_level = pActorTmp;
                        GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth] = this;
                    }
                    _now_drawdepth = _specal_drawdepth;
                }

            }
        } else {
            if (((GgafDxScene*)getPlatformScene())->_pAlphaCurtain->_alpha <= 0.0f || isOutOfView()) {
                //�`�悵�Ȃ��̂œo�^�Ȃ�
            } else {
                //��������
                //�����J�����ʒu _cameraZ_org = -47.6701�A�\���͈͉��s��  _zf �� _dep=20�̂Ƃ��A_zf = -_cameraZ_org*(_dep+1); �Ƃ����ꍇ�̗�B�B
                //�u�Q�ƁFGgafDxCamera::GgafDxCamera()�v
                //�\���͈�(���s��:_zf)�̋����͏����J�����̈����ʒu������21�{�Ŗ� 1000(1001.0721) �ɂȂ�i���ꂪ _zf = -_cameraZ_org*20.0 �̈Ӗ��j
                //���� MAX_DRAW_DEPTH_LEVEL (����1000)�Ƃǂ̂悤�ɑΉ������邩
                //�{���C�u������DIRECTX���W��1�͌��_�t�߂̂ŉ�ʏ��10px�����Ƃ����v�Z���s���Ă���B�����
                //���̕��͖�10px�Ԋu�����̉�����̒i�K�����_�����O�̐ݒ�ƂȂ�
                //
                //  GgafDxUniverse::setDrawDepthLevel(-1.0*_dest_from_vppln_front, this);
                //   (��_dest_from_vppln_front�͎������O�ʂ���I�u�W�F�N�g�܂ł̋����̕���)
                //
                //����́A1000 �i�K�̐[�x����ƂȂ�B
                //�܂��A
                //
                //  GgafDxUniverse::setDrawDepthLevel(-1.0*_dest_from_vppln_front*10.0, this);
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
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera ��ʃA�X�y�N�g�F1.33333
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera FovX=1.39626 FovY=1.12341
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera �J�����̈ʒu(0,0,-47.6701)
                //   7975036 <DEBUG> GgafDxCamera::GgafDxCamera �͈� [0.01 ~ 1001.07]
                //
                // 1001.07 �܂��10000px�����̉��s����`��
                dxcoord dep = -_dest_from_vppln_front; //�I�u�W�F�N�g�̎��_����̋���(DIRECTX����)

                static const double dep_rate_point1 = 0.3;                                //�r���Ȃ�|�C���g�P�̊���(�J���������s�� 3/10 �̒n�_)
                static const double dep_rate_point2 = 0.6;                                //�r���Ȃ�|�C���g�Q�̊���(�J���������s�� 6/10 �̒n�_)
                static const dxcoord roughly_dep_point1 = (pCam->getZFar() * dep_rate_point1); //�r���Ȃ�|�C���g�P����
                static const dxcoord roughly_dep_point2 = (pCam->getZFar() * dep_rate_point2); //�r���Ȃ�|�C���g�Q����
                static const double dep_level_rate_cam_to_point1 = 0.5;                   //���_�`�r���Ȃ�|�C���g�P�܂ł́A�[�x���x�������߂邽�߂ɋ����ɏ悸�銄���B
                static const double dep_level_rate_point1_to_point2 = 0.2;                //�r���Ȃ�|�C���g�P�`�|�C���g�Q�Ԃ́A�[�x���x�������߂邽�߂ɋ����ɏ悸�銄���B
                static const double dep_level_rate_point2_to_far_away = 0.01;             //�r���Ȃ�|�C���g�Q�`�ŉ��́A�[�x���x�������߂邽�߂ɋ����ɏ悸�銄���B
                static const int roughly_dep_point1_DRAW_DEPTH_LEVEL = roughly_dep_point1*dep_level_rate_cam_to_point1;    //�r���Ȃ�|�C���g�P�[�x���x��
                static const int roughly_dep_point2_DRAW_DEPTH_LEVEL = roughly_dep_point1_DRAW_DEPTH_LEVEL +
                               ((roughly_dep_point2 - roughly_dep_point1) * dep_level_rate_point1_to_point2);        //�r���Ȃ�|�C���g�Q�[�x���x��

                if (_specal_drawdepth < 0) { //���ʂȕ`��[�x�w�薳��
                    if (dep <= roughly_dep_point1) {         //dep�� ���_ �` r�r���Ȃ�|�C���g�P �܂ł̋����̃I�u�W�F�N�g
                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
                                             dep*dep_level_rate_cam_to_point1,
                                             this); //DirectX�̋���1��0.5�{�ADirectX�̋���2���[��1�B����Ė�20px�Ԋu
                    } else if (dep <= roughly_dep_point2) {  //dep�� �r���Ȃ�|�C���g�P�`�|�C���g�Q��
                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
                                             roughly_dep_point1_DRAW_DEPTH_LEVEL +
                                               ((dep - roughly_dep_point1) * dep_level_rate_point1_to_point2),
                                             this);  //DirectX�̋���1��0.2�{�B�܂�DirectX�̋���5���[��1�B�����50px�Ԋu�Œi�K�����_
                    } else {                                 //dep�� �|�C���g�Q�ȍ~
                        _now_drawdepth = GgafDxUniverse::setDrawDepthLevel(
                                             roughly_dep_point2_DRAW_DEPTH_LEVEL +
                                               ((dep - roughly_dep_point2) * dep_level_rate_point2_to_far_away),
                                             this); //0.01�{�B�܂�DirectX�̋���100���[��1�B�����1000px�Ԋu�Œi�K�����_
                    }
                } else {
                    //���ʂȕ`��[�x�w��L��
                    if (GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth] == nullptr) {
                        //����prm_draw_depth_level�ōŏ��̃A�N�^�[�̏ꍇ
                        this->_pNextActor_in_draw_depth_level = nullptr;
                        GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth] = this;
                        GgafDxUniverse::_apLastActor_draw_depth_level[_specal_drawdepth] = this;
                    } else {
                        //�O�ɒǉ�
                        GgafDxDrawableActor* pActorTmp = GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth];
                        this->_pNextActor_in_draw_depth_level = pActorTmp;
                        GgafDxUniverse::_apFirstActor_draw_depth_level[_specal_drawdepth] = this;
                    }
                    _now_drawdepth = _specal_drawdepth;
                }

            }
        }
    }

    //�ꎞ�e�N�j�b�N���ԃ`�F�b�N
    if (_is_temp_technique) {
        if (_frame_of_behaving_temp_technique_end <= _frame_of_behaving) {
            //�ꎞ�e�N�j�b�N���Ԗ����B���ɖ߂�
            _hash_technique = _hash_temp_technique;
            strcpy(_technique, _temp_technique);
            _is_temp_technique = false;
            //����̓_���B�z��̈悪�ǂ����ɂ������߁B_temp_technique = "";
            _hash_temp_technique = 0;
        }
    }

}


void GgafDxDrawableActor::processAfterDraw() {
#ifdef MY_DEBUG
    //�����蔻��̈�\��
    if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        drawHitArea();
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
    }
#endif
}

void GgafDxDrawableActor::setMaterialColor(float r, float g, float b) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

void GgafDxDrawableActor::setMaterialRed(float r) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = r;
        _paMaterial[i].Diffuse.r = r;
    }
}
void GgafDxDrawableActor::setMaterialGreen(float g) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.g = g;
        _paMaterial[i].Diffuse.g = g;
    }
}
void GgafDxDrawableActor::setMaterialBlue(float b) {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.b = b;
        _paMaterial[i].Diffuse.b = b;
    }
}

void GgafDxDrawableActor::setMaterialColor(const GgafCore::GgafRgb* prm_rgb) {
    setMaterialColor(prm_rgb->_r, prm_rgb->_g, prm_rgb->_b);
}

void GgafDxDrawableActor::resetMaterialColor() {
    for (DWORD i = 0; i < _pModel->_num_materials; i++) {
        _paMaterial[i].Ambient.r = _pModel->_paMaterial_default[i].Ambient.r;
        _paMaterial[i].Diffuse.r = _pModel->_paMaterial_default[i].Diffuse.r;
        _paMaterial[i].Ambient.g = _pModel->_paMaterial_default[i].Ambient.g;
        _paMaterial[i].Diffuse.g = _pModel->_paMaterial_default[i].Diffuse.g;
        _paMaterial[i].Ambient.b = _pModel->_paMaterial_default[i].Ambient.b;
        _paMaterial[i].Diffuse.b = _pModel->_paMaterial_default[i].Diffuse.b;
    }
}

void GgafDxDrawableActor::setSpecialDrawDepth(int prm_drawdepth) {
    if (prm_drawdepth > MAX_DRAW_DEPTH_LEVEL) {
        _specal_drawdepth = MAX_DRAW_DEPTH_LEVEL;
    } else {
        _specal_drawdepth = prm_drawdepth;
    }
}

void GgafDxDrawableActor::changeEffectTechnique(const char* prm_technique) {
    _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
    strcpy(_technique, prm_technique);
}
void GgafDxDrawableActor::changeEffectTechniqueInterim(const char* prm_technique, frame prm_frame) {
    if (_is_temp_technique == false) { //���łɈꎞ�e�N�j�b�N�g�p���͖���
        //���X�̃e�N�j�b�N��ޔ�
        _hash_temp_technique = _hash_technique;
        strcpy(_temp_technique, _technique);
        //�e�N�j�b�N�ύX
        if (prm_frame == MAX_FRAME) {
            _frame_of_behaving_temp_technique_end = MAX_FRAME;
        } else {
            _frame_of_behaving_temp_technique_end = _frame_of_behaving + prm_frame; //�ύX�����t���[��
        }
        _hash_technique = UTIL::easy_hash(prm_technique) + UTIL::easy_hash(_pModel->getName());
        strcpy(_technique, prm_technique);
        _is_temp_technique = true;
    }
}

void GgafDxDrawableActor::effectFlush(frame prm_frame) {
    changeEffectTechniqueInterim("Flush", prm_frame); //�t���b�V��
}

void GgafDxDrawableActor::effectBlendOne(frame prm_frame) {
    changeEffectTechniqueInterim("DestBlendOne", prm_frame);
}

void GgafDxDrawableActor::effectDefault() {
    if (_is_temp_technique) {
        _hash_technique = _hash_temp_technique;
        strcpy(_technique, _temp_technique);
        _is_temp_technique = false;
        _hash_temp_technique = 0;
    }
}
int GgafDxDrawableActor::isOutOfView() {
    //_TRACE_("name="<<getName()<<" _bounding_sphere_radius="<<_bounding_sphere_radius);
    if (_offscreen_kind == -1) {
        dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*2;//�|����2�͋��E����傫�����āA��ʋ��E�̃`���c�L��}����
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_front < bound) {
                            if (_dest_from_vppln_back < bound) {
                                //Viewport�͈͓�
                                _offscreen_kind = 0;
                            } else {
                                //�����ʂ�艜�Ŕ͈͊O
                                _offscreen_kind = 6;
                            }
                        } else {
                            //��O���ʂ���O�Ŕ͈͊O
                            _offscreen_kind = 5;
                        }
                    } else {
                        //�E���ʂ��E�Ŕ͈͊O
                        _offscreen_kind = 4;
                    }
                } else {
                    //�����ʂ�荶�Ŕ͈͊O
                    _offscreen_kind = 3;
                }
            } else {
                //�����ʂ�艺�Ŕ͈͊O
                _offscreen_kind = 2;
            }
        } else {
            //�㕽�ʂ���Ŕ͈͊O
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}
GgafDxDrawableActor::~GgafDxDrawableActor() {
    GGAF_DELETEARR(_technique);
    GGAF_DELETEARR(_temp_technique);
    GGAF_DELETEARR(_paMaterial);

    _pEffectCon->close();
    _pModelCon->close();
}
