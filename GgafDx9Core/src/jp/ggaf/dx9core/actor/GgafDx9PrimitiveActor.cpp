#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PrimitiveActor::GgafDx9PrimitiveActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_technique,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pPrimitiveModel = (GgafDx9PrimitiveModel*)_pModelCon->view();
    _class_name = "GgafDx9PrimitiveActor";

    //�G�t�F�N�g�擾
    _pEffectConnection = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection("GgafDx9MashEffect");
    _pID3DXEffect = _pEffectConnection->view();
    //���f���̃I���W�i���}�e���A�����R�s�[���ĕۑ�
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pPrimitiveModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pPrimitiveModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pPrimitiveModel->_paD3DMaterial9_default[i];
    }
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
	HRESULT hr;
	hr = _pID3DXEffect->SetTechnique(prm_technique);
    whetherGgafDx9CriticalException(hr, S_OK, "GgafDx9PrimitiveActor::GgafDx9PrimitiveActor SetTechnique() �Ɏ��s���܂����B");
    //VIEW�ϊ��s��
    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::processDrawMain SetMatrix(g_matView) �Ɏ��s���܂����B");
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9God::_vMatrixProjrction );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveActor::GgafDx9PrimitiveActor SetMatrix() �Ɏ��s���܂����B");
    //���C�g����
    hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw SetValue(g_LightDirection) �Ɏ��s���܂����B");
    //Diffuse����
    hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw SetValue(g_LightDiffuse) �Ɏ��s���܂����B");
    //Ambient����
    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::draw SetValue(g_LightAmbient) �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse" );
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
    static D3DXMATRIX matWorld; //WORLD�ϊ��s��
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
    hr = _pID3DXEffect->SetMatrix(_hMatWorld, &matWorld );
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
