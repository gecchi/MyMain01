#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9MeshActor::GgafDx9MeshActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   GgafDx9Checker* prm_pChecker) :

                                       GgafDx9DrawableActor(prm_name,
                                                            prm_model_id,
                                                            "X",
                                                            prm_effect_id,
                                                            "X",
                                                            prm_technique,
                                                            prm_pChecker) {
    _class_name = "GgafDx9MeshActor";
    _pMeshModel = (GgafDx9MeshModel*)_pGgafDx9Model;
    _pMeshEffect = (GgafDx9MeshEffect*)_pGgafDx9Effect;
}


void GgafDx9MeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9MeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}


void GgafDx9MeshActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &pCAM->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

    // Z�o�b�t�@��L����
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    _pMeshModel->draw(this);

    // Z�o�b�t�@�𖳌���
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );


}

GgafDx9MeshActor::~GgafDx9MeshActor() {
}
