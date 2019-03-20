#include "jp/ggaf/dx/actor/MeshSetActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

MeshSetActor::MeshSetActor(const char* prm_name,
                           const char* prm_model_id,
                           const char* prm_effect_id,
                           const char* prm_technique,
                           Checker* prm_pChecker) :

                               FigureActor(prm_name,
                                           prm_model_id,
                                           TYPE_MESHSET_MODEL,
                                           prm_effect_id,
                                           TYPE_MESHSET_EFFECT,
                                           prm_technique,
                                           prm_pChecker),
_pMeshSetModel((MeshSetModel*)_pModel),
_pMeshSetEffect((MeshSetEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MeshSetActor;
    _class_name = "MeshSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
}

MeshSetActor::MeshSetActor(const char* prm_name,
                           const char* prm_model_id,
                           const char prm_model_type,
                           const char* prm_effect_id,
                           const char prm_effect_type,
                           const char* prm_technique,
                           Checker* prm_pChecker) :

                               FigureActor(prm_name,
                                           prm_model_id,
                                           prm_model_type,
                                           prm_effect_id,
                                           prm_effect_type,
                                           prm_technique,
                                           prm_pChecker),
_pMeshSetModel((MeshSetModel*)_pModel),
_pMeshSetEffect((MeshSetEffect*)_pEffect) {

    _obj_class |= Obj_GgafDx_MeshSetActor;
    _class_name = "MeshSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
}

void MeshSetActor::processDraw() {
    int draw_set_num = 0; //MeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    MeshSetActor* pMeshSetActor = nullptr;
    const int model_set_num = _pMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pMeshSetActor = (MeshSetActor*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pMeshSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            //�yMeshSetActor�̃}�e���A���J���[�ɂ��čl�����z���Y�^����
            //�{���̓}�e���A���P�I�u�W�F�N�g�ɕ����ێ����A�}�e���A�����X�g�̃O���[�v���ɐݒ肷����̂����A���s���x�œK���Ǝg�p���W�X�^���팸(�s�N�Z���V�F�[�_�[2.0)�ׁ̈A
            //�e�Z�b�g��[0]�̃}�e���A����S�̂̃}�e���A���Ƃ���B
            //����������MeshSetActor�̓}�e���A���F�͂P�F�����s�\�B
            //���ꂼ��̂P�F���A�}�e���A���F�Ƃ��ăI�u�W�F�N�g�ʂɂ邽�ߒ��_�J���[�Ŏ������Ă���B
            //���Ƃ��Ɩ{�N���X�́A���ꃂ�f�������I�u�W�F�N�g���A�����Ɉ��ŕ`�悵�X�s�[�h�A�b�v��}�邱�Ƃ�ړI�Ƃ����N���X�ŁA��������}�e���A���O���[�v������I�u�W�F�N�g�ɂ͕s���Ƃ��������Ӗ��ł���B
            //�P���e�N�X�`���Ŋ撣��Ζ��Ȃ��E�E�E�Ƃ������j�B�}�e���A���F�ŐF�����������ꍇ�� MeshActor ���g�������Ȃ��B
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    Spacetime::_pActor_draw_active = pMeshSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    ((MeshSetModel*)_pMeshSetModel)->MeshSetModel::draw(this, draw_set_num);
}

MeshSetActor::~MeshSetActor() {
}
