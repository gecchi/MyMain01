#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardActor::GgafDx9BoardActor(const char* prm_name,
                                     const char* prm_model_name,
                                     const char* prm_effect,
                                     const char* prm_technique) : GgafDx9TransformedActor(prm_name) {
    _class_name = "GgafDx9BoardActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model_name);
    _pBoardModel = (GgafDx9BoardModel*)_pModelCon->view();
    //���f���̃}�e���A�����R�s�[���ĕێ�(2009/3/10 ���݃}�e���A�����g�p�B�����g�������B)
    _paD3DMaterial9 = NEW D3DMATERIAL9[1];
    _paD3DMaterial9[0] = *(_pBoardModel->_pD3DMaterial9_default);
    _fAlpha = 1.0;
    //�G�t�F�N�g�擾
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pBoardEffect = (GgafDx9BoardEffect*)_pEffectCon->view();
    _pattno_top = 0;
    _pattno_bottom = _pBoardModel->_pattno_max;
    _patteno_now = 0;
}

void GgafDx9BoardActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetTechnique(_technique);
//    potentialDx9Exception(hr, S_OK, "GgafDx9BoardActor::processDrawMain SetTechnique("<<_technique<<") �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, _x);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedX) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, _y);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedY) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, _z);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hDepthZ) �Ɏ��s���܂����B");
    //���ݒ�
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hAlpha, _fAlpha);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hAlpha) �Ɏ��s���܂����B");

//    UINT numPass;
//    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardActor::processDrawMain Begin() �Ɏ��s���܂����B");
//    for (UINT pass = 0; pass < numPass; pass++) {
//        hr = pID3DXEffect->BeginPass(pass);
//        potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardActor::processDrawMain BeginPass(0) �Ɏ��s���܂����B");
        _pBoardModel->draw(this);
//        hr = pID3DXEffect->EndPass();
//        potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardActor::processDrawMain EndPass() �Ɏ��s���܂����B");
//    }
//    hr = pID3DXEffect->End();
//    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardActor::processDrawMain End() �Ɏ��s���܂����B");
}

void GgafDx9BoardActor::setPatternNo(int prm_pattno) {
    if (_pattno_top <= prm_pattno && prm_pattno <= _pattno_bottom) {
        _patteno_now = prm_pattno;
    } else if (prm_pattno < _pattno_top) {
        _patteno_now = _pattno_top;
    } else if (prm_pattno > _pattno_bottom) {
        _patteno_now = _pattno_bottom;
    }
}

GgafDx9BoardActor::~GgafDx9BoardActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
