#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMeshSetActor::GgafDxCubeMapMeshSetActor(const char* prm_name,
                                                       const char* prm_model_id,
                                                       const char* prm_effect_id,
                                                       const char* prm_technique,
                                                       GgafStatus* prm_pStat,
                                                       GgafDxChecker* prm_pChecker) :
                                              GgafDxMeshSetActor(prm_name,
                                                                  prm_model_id,
                                                                  "g",
                                                                  prm_effect_id,
                                                                  "g",
                                                                  prm_technique,
                                                                  prm_pStat,
                                                                  prm_pChecker) ,
                                              GgafDxICubeMapActor() {
    _obj_class |= Obj_GgafDxCubeMapMeshSetActor;
    _class_name = "GgafDxCubeMapMeshSetActor";
    _pCubeMapMeshSetModel = (GgafDxCubeMapMeshSetModel*)_pModel;
    _pCubeMapMeshSetEffect = (GgafDxCubeMapMeshSetEffect*)_pEffect;
//    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
//    _pCubeMapTextureCon = (GgafDxTextureConnection*)(P_UNIVERSE->_pCubeMapTextureManager->connect("uffizi_cross_cubemap.dds"));
//    _pCubeMapTexture = _pCubeMapTextureCon->use()->_pIDirect3DBaseTexture9;
//    _reflectance = 0.3f;
}

void GgafDxCubeMapMeshSetActor::processDraw() {
    _draw_set_num = 0; //GgafDxCubeMapMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pCubeMapMeshSetEffect->_pID3DXEffect;
    HRESULT hr;

    hr = pID3DXEffect->SetFloat(_pCubeMapMeshSetEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "GgafDxCubeMapMeshActor::processDraw() SetFloat(_h_reflectances) �Ɏ��s���܂����B");
    GgafDxGod::_pID3DDevice9->SetTexture(1, getCubeMapTexture());

    //��{���f�����_��
    GgafDxDrawableActor* pDrawActor = this;
    GgafDxCubeMapMeshSetActor* pCubeMapMeshSetActor = NULL;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pCubeMapMeshSetModel && pDrawActor->_hash_technique == _hash_technique ) {
                pCubeMapMeshSetActor = (GgafDxCubeMapMeshSetActor*)pDrawActor;
                if (getCubeMapTexture() == pCubeMapMeshSetActor->getCubeMapTexture() && _reflectance == pCubeMapMeshSetActor->_reflectance) {
                    hr = pID3DXEffect->SetMatrix(_pCubeMapMeshSetEffect->_ah_matWorld[_draw_set_num], &(pCubeMapMeshSetActor->_matWorld));
                    checkDxException(hr, D3D_OK, "GgafDxMeshSetActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
                    hr = pID3DXEffect->SetValue(_pCubeMapMeshSetEffect->_ah_materialDiffuse[_draw_set_num], &(pCubeMapMeshSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
                    checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
                    _draw_set_num++;
                    if (_draw_set_num >= _pCubeMapMeshSetModel->_set_num) {
                        break;
                    }
                    pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
                } else {
                    break;
                }
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_DrawActive = pCubeMapMeshSetActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    _pCubeMapMeshSetModel->draw(this, _draw_set_num);
}

GgafDxCubeMapMeshSetActor::~GgafDxCubeMapMeshSetActor() {
}
