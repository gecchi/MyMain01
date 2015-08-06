#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMeshSetActor::GgafDxMeshSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       GgafStatus* prm_pStat,
                                       GgafDxChecker* prm_pChecker) :

                                           GgafDxFigureActor(prm_name,
                                                               prm_model_id,
                                                               "x",
                                                               prm_effect_id,
                                                               "x",
                                                               prm_technique,
                                                               prm_pStat,
                                                               prm_pChecker),
_pMeshSetModel((GgafDxMeshSetModel*)_pModel),
_pMeshSetEffect((GgafDxMeshSetEffect*)_pEffect) {
    _obj_class |= Obj_GgafDxMeshSetActor;
    _class_name = "GgafDxMeshSetActor";
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

GgafDxMeshSetActor::GgafDxMeshSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_model_type,
                                       const char* prm_effect_id,
                                       const char* prm_effect_type,
                                       const char* prm_technique,
                                       GgafStatus* prm_pStat,
                                       GgafDxChecker* prm_pChecker) :

                                           GgafDxFigureActor(prm_name,
                                                               prm_model_id,
                                                               prm_model_type,
                                                               prm_effect_id,
                                                               prm_effect_type,
                                                               prm_technique,
                                                               prm_pStat,
                                                               prm_pChecker),
_pMeshSetModel((GgafDxMeshSetModel*)_pModel),
_pMeshSetEffect((GgafDxMeshSetEffect*)_pEffect) {

    _obj_class |= Obj_GgafDxMeshSetActor;
    _class_name = "GgafDxMeshSetActor";
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GgafDxMeshSetActor::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxFigureActor* pDrawActor = this;
    GgafDxMeshSetActor* pMeshSetActor = nullptr;
    const int model_set_num = _pMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pMeshSetActor = (GgafDxMeshSetActor*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pMeshSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            //�yGgafDxMeshSetActor�̃}�e���A���J���[�ɂ��čl�����z���Y�^����
            //�{���̓}�e���A���P�I�u�W�F�N�g�ɕ����ێ����A�}�e���A�����X�g�̃O���[�v���ɐݒ肷����̂����A���s���x�œK���Ǝg�p���W�X�^���팸(�s�N�Z���V�F�[�_�[2.0)�ׁ̈A
            //�e�Z�b�g��[0]�̃}�e���A����S�̂̃}�e���A���Ƃ���B
            //����������GgafDxMeshSetActor�̓}�e���A���F�͂P�F�����s�\�B
            //���ꂼ��̂P�F���A�}�e���A���F�Ƃ��ăI�u�W�F�N�g�ʂɂ邽�ߒ��_�J���[�Ŏ������Ă���B
            //���Ƃ��Ɩ{�N���X�́A���ꃂ�f�������I�u�W�F�N�g���A�����Ɉ��ŕ`�悵�X�s�[�h�A�b�v��}�邱�Ƃ�ړI�Ƃ����N���X�ŁA��������}�e���A���O���[�v������I�u�W�F�N�g�ɂ͕s���Ƃ��������Ӗ��ł���B
            //�P���e�N�X�`���Ŋ撣��Ζ��Ȃ��E�E�E�Ƃ������j�B�}�e���A���F�ŐF�����������ꍇ�� GgafDxMeshActor ���g�������Ȃ��B
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextActor_in_render_depth;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pMeshSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    ((GgafDxMeshSetModel*)_pMeshSetModel)->GgafDxMeshSetModel::draw(this, draw_set_num);
}

GgafDxMeshSetActor::~GgafDxMeshSetActor() {
}
