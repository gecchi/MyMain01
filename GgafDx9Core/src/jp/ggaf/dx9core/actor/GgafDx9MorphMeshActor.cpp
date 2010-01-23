#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MorphMeshActor::GgafDx9MorphMeshActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafDx9Checker* prm_pChecker) :

                                                 GgafDx9DrawableActor(prm_name,
                                                                       prm_model_id,
                                                                       "M",
                                                                       prm_effect_id,
                                                                       "M",
                                                                       prm_technique,
                                                                       prm_pChecker) {
    _class_name = "GgafDx9MorphMeshActor";
    _pMorphMeshModel = (GgafDx9MorphMeshModel*)_pGgafDx9Model;
    _pMorphMeshEffect = (GgafDx9MorphMeshEffect*)_pGgafDx9Effect;
    //�d�ݏ�����
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
}



void GgafDx9MorphMeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9MorphMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pMorphMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MorphMeshActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");
    GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetInt(_pMorphMeshEffect->_hMorphTargetnum, _pMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::processDraw() SetInt(_hMorphTargetnum) �Ɏ��s���܂����B");
    for (int pattern = 1; pattern <= _pMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pMorphMeshEffect->_hWeight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::processDraw() SetFloat(_hWeight["<<pattern<<"]) �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_hMatWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

    // Z�o�b�t�@��L����
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    _pMorphMeshModel->draw(this);

    // Z�o�b�t�@�𖳌���
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

}

int GgafDx9MorphMeshActor::getMorphTergetNum() {
    return _pMorphMeshModel->_morph_target_num;
}

GgafDx9MorphMeshActor::~GgafDx9MorphMeshActor() {
}
