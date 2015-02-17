#include "jp/ggaf/dxcore/actor/GgafDxDynaD3DXMeshActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXMeshModel.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxDynaD3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDxDynaD3DXMeshActor::GgafDxDynaD3DXMeshActor(const char* prm_name,
                                                 const char* prm_model_id,
                                                 const char* prm_effect_id,
                                                 const char* prm_technique,
                                                 GgafStatus* prm_pStat,
                                                 GgafDxChecker* prm_pChecker) :

                                                     GgafDxDrawableActor(prm_name,
                                                                         prm_model_id,
                                                                         "d",
                                                                         prm_effect_id,
                                                                         "X",
                                                                         prm_technique,
                                                                         prm_pStat,
                                                                         prm_pChecker) {
    _obj_class |= Obj_GgafDxDynaD3DXMeshActor;
    _class_name = "GgafDxDynaD3DXMeshActor";

    _pD3DXMeshModel = (GgafDxD3DXMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GgafDxDynaD3DXMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxDynaD3DXMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    _pD3DXMeshModel->draw(this);
}

void GgafDxDynaD3DXMeshActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //GgafDxDynaD3DXMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pD3DXMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

void GgafDxDynaD3DXMeshActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //GgafDxDynaD3DXMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pD3DXMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

GgafDxDynaD3DXMeshActor::~GgafDxDynaD3DXMeshActor() {
}
