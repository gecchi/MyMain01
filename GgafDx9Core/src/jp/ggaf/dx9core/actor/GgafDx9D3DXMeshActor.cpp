#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


DWORD GgafDx9D3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDx9D3DXMeshActor::GgafDx9D3DXMeshActor(const char* prm_name,
                                           const char* prm_model,
                                           const char* prm_effect,
                                           const char* prm_technique,
                                           GgafDx9GeometryMover* prm_pGeoMover,
                                           GgafDx9GeometryChecker* prm_pGeoChecker) :

                                           GgafDx9UntransformedActor(prm_name,
                                                                     prm_pGeoMover,
                                                                     prm_pGeoChecker) {
    _class_name = "GgafDx9D3DXMeshActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    //���f���擾
    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pD3DXMeshModel = (GgafDx9D3DXMeshModel*)_pModelCon->view();
    //�G�t�F�N�g�擾
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pMeshEffect = (GgafDx9MeshEffect*)_pEffectCon->view();
    //�}�e���A�����R�s�[
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pD3DXMeshModel->_dwNumMaterials];
	for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++){
	    _paD3DMaterial9[i] = _pD3DXMeshModel->_paD3DMaterial9_default[i];
	}
}

void GgafDx9D3DXMeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9UntransformedActor::setAlpha(prm_fAlpha);
    //���ݒ�
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9D3DXMeshActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //WORLD�ϊ��s��
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);

    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "GgafDx9MeshActor::processDrawMain() SetTechnique("<<_technique<<") �Ɏ��s���܂����B");

    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE  );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() �Ɏ��s���܂����B");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") �Ɏ��s���܂����B");
        _pD3DXMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() �Ɏ��s���܂����B");

//    if (_pID3DXEffect == NULL) {
//        GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
//    }

//    GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
//    _pD3DXMeshModel->draw(this);
}

GgafDx9D3DXMeshActor::~GgafDx9D3DXMeshActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
