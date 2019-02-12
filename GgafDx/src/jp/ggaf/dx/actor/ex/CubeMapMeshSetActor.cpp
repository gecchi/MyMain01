#include "jp/ggaf/dx/actor/ex/CubeMapMeshSetActor.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMeshSetEffect.h"
#include "jp/ggaf/dx/model/ex/CubeMapMeshSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

CubeMapMeshSetActor::CubeMapMeshSetActor(const char* prm_name,
                                                     const char* prm_model_id,
                                                     const char* prm_effect_id,
                                                     const char* prm_technique,
                                                     GgafCore::Status* prm_pStat,
                                                     Checker* prm_pChecker) :
                                              MeshSetActor(prm_name,
                                                                 prm_model_id,
                                                                 TYPE_CUBEMAPMESHSET_MODEL,
                                                                 prm_effect_id,
                                                                 TYPE_CUBEMAPMESHSET_EFFECT,
                                                                 prm_technique,
                                                                 prm_pStat,
                                                                 prm_pChecker) ,
                                              ICubeMapActor() {
    _obj_class |= Obj_GgafDx_CubeMapMeshSetActor;
    _class_name = "CubeMapMeshSetActor";
    _pCubeMapMeshSetModel = (CubeMapMeshSetModel*)_pModel;
    _pCubeMapMeshSetEffect = (CubeMapMeshSetEffect*)_pEffect;
}

void CubeMapMeshSetActor::processDraw() {
    int draw_set_num = 0; //CubeMapMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* const pID3DXEffect = _pCubeMapMeshSetEffect->_pID3DXEffect;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pCubeMapMeshSetEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) �Ɏ��s���܂����B");
    God::_pID3DDevice9->SetTexture(1, getCubeMapTexture());

    //��{���f�����_��
    FigureActor* pDrawActor = this;
    CubeMapMeshSetActor* pCubeMapMeshSetActor = nullptr;
    int model_set_num = _pCubeMapMeshSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pCubeMapMeshSetModel && pDrawActor->_hash_technique == _hash_technique ) {
            pCubeMapMeshSetActor = (CubeMapMeshSetActor*)pDrawActor;
            if (getCubeMapTexture() == pCubeMapMeshSetActor->getCubeMapTexture() &&
                  (_reflectance-0.00001f < pCubeMapMeshSetActor->_reflectance && pCubeMapMeshSetActor->_reflectance < _reflectance+0.00001f)) {
                hr = pID3DXEffect->SetMatrix(_pCubeMapMeshSetEffect->_ah_matWorld[draw_set_num], &(pCubeMapMeshSetActor->_matWorld));
                checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) �Ɏ��s���܂����B");
                hr = pID3DXEffect->SetValue(_pCubeMapMeshSetEffect->_ah_materialDiffuse[draw_set_num], &(pCubeMapMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNextRenderActor;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    Spacetime::_pActor_draw_active = pCubeMapMeshSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    ((MeshSetModel*)_pCubeMapMeshSetModel)->MeshSetModel::draw(this, draw_set_num);
}

CubeMapMeshSetActor::~CubeMapMeshSetActor() {
}
