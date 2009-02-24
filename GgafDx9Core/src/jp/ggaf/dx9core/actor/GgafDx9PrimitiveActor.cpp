#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PrimitiveActor::GgafDx9PrimitiveActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pPrimitiveModel = (GgafDx9PrimitiveModel*)_pModelCon->view();
    _class_name = "GgafDx9PrimitiveActor";


    //##_pEffectConnection = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    //##_pID3DXEffect = _pEffectConnection->view();
    //�}�e���A�����R�s�[
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pPrimitiveModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pPrimitiveModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pPrimitiveModel->_paD3DMaterial9_default[i];
    }
    //g_matProj(�ˉe�ϊ��s��)�͑S�V�F�[�_�[���ʂ̃O���[�o���ϐ��Ƃ��邱�ƂƂ���B
	//##_pID3DXEffect->SetTechnique("DefaultTec");
    //##_pID3DXEffect->SetMatrix("g_matProj", &GgafDx9God::_vMatrixProjrction );

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
//    if (_pID3DXEffect == NULL) {
//        GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
//    }
    static D3DXMATRIX matWorld; //WORLD�ϊ��s��

    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);
    //##_pID3DXEffect->SetMatrix( "g_matWorld", &matWorld );
    //##_pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );


    
    UINT numPass;
    //##_pID3DXEffect->Begin( &numPass, 0 );

    _pPrimitiveModel->draw(this);
    
    //##_pID3DXEffect->End();
}

GgafDx9PrimitiveActor::~GgafDx9PrimitiveActor() {
    _pModelCon->close();
    //##_pEffectConnection->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
