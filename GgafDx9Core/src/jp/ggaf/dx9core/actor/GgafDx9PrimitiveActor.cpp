#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PrimitiveActor::GgafDx9PrimitiveActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_technique,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pPrimitiveModel = (GgafDx9PrimitiveModel*)_pModelCon->view();
    _class_name = "GgafDx9PrimitiveActor";

    //�G�t�F�N�g�擾
    _pEffectConnection = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection("GgafDx9MashEffect");
    _pMeshEffect = (GgafDx9MeshEffect*)_pEffectConnection->view();
    _pID3DXEffect = _pMeshEffect->_pID3DXEffect;

    //���f���̃I���W�i���}�e���A�����R�s�[���ĕۑ�
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pPrimitiveModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pPrimitiveModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pPrimitiveModel->_paD3DMaterial9_default[i];
    }
}

void GgafDx9PrimitiveActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //���ݒ�
    for (DWORD i = 0; i < _pPrimitiveModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9PrimitiveActor::processDrawMain() {
	HRESULT hr;
	hr = _pID3DXEffect->SetTechnique(_technique);
    whetherGgafDx9CriticalException(hr, S_OK, "GgafDx9PrimitiveActor::GgafDx9PrimitiveActor SetTechnique() �Ɏ��s���܂����B");

    static D3DXMATRIX matWorld; //WORLD�ϊ��s��
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
    hr = _pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    UINT numPass;
    hr = _pID3DXEffect->Begin( &numPass, 0 );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain Begin() �Ɏ��s���܂����B");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = _pID3DXEffect->BeginPass(pass);
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw BeginPass(0) �Ɏ��s���܂����B");
        _pPrimitiveModel->draw(this);
        hr = _pID3DXEffect->EndPass();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw EndPass() �Ɏ��s���܂����B");
    }
    hr = _pID3DXEffect->End();
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain End() �Ɏ��s���܂����B");

}

GgafDx9PrimitiveActor::~GgafDx9PrimitiveActor() {
    _pModelCon->close();
    _pEffectConnection->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
