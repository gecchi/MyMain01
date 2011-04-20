#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeMapMorphMeshEffect::GgafDx9CubeMapMorphMeshEffect(char* prm_effect_name) : GgafDx9MorphMeshEffect(prm_effect_name) {
    _h_pos_camera = _pID3DXEffect->GetParameterByName( NULL, "pos_camera" );
}

void GgafDx9CubeMapMorphMeshEffect::setParamPerFrame() {
    GgafDx9MorphMeshEffect::setParamPerFrame();
    HRESULT hr = _pID3DXEffect->SetValue(_h_pos_camera, P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_pos_camera) に失敗しました。");
}

GgafDx9CubeMapMorphMeshEffect::~GgafDx9CubeMapMorphMeshEffect() {
}

