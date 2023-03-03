#include "jp/ggaf/dx/actor/ex/CubeMapMeshActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMeshEffect.h"
#include "jp/ggaf/dx/model/ex/CubeMapMeshModel.h"


using namespace GgafDx;


CubeMapMeshActor::CubeMapMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   CollisionChecker* prm_pChecker) :
                                           MeshActor(prm_name,
                                                     prm_model,
                                                     TYPE_CUBEMAPMESH_MODEL,
                                                     prm_effect_id,
                                                     TYPE_CUBEMAPMESH_EFFECT,
                                                     prm_technique,
                                                     prm_pChecker) ,
                                           ICubeMapActor() {
    _obj_class |= Obj_GgafDx_CubeMapMeshActor;
    _class_name = "CubeMapMeshActor";
    _pCubeMapMeshModel = (CubeMapMeshModel*)_pModel;
    _pCubeMapMeshEffect = (CubeMapMeshEffect*)_pEffect;
}

void CubeMapMeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pCubeMapMeshEffect->_h_reflectance, getCubeMapReflectance());
    checkDxException(hr, D3D_OK, "SetFloat(_h_reflectances) に失敗しました。");
    pCARETAKER->_pID3DDevice9->SetTexture(1, getCubeMapTexture());
    if (_pBumpMapTextureConnection) {
        hr = pCARETAKER->_pID3DDevice9->SetTexture(2, getBumpMapTexture());
        checkDxException(hr, D3D_OK, "SetTexture() に失敗しました。");
        hr = pID3DXEffect->SetMatrix(_pCubeMapMeshEffect->_h_matInvWorld, getInvMatWorldRotMv() );
        checkDxException(hr, D3D_OK, "SetMatrix(_h_matInvWorld) に失敗しました。");
        //TODO:毎回逆行列をここで計算すれば良い、が、少しでもはやくするためにgetInvMatWorldRotMv()で代用。
        //getInvMatWorldRotMv() なので、拡大縮小が考慮されてない。軸ごとに拡大率が違う場合、バンプマップはちょっとおかしくなる。
    }
    ((MeshModel*)_pCubeMapMeshModel)->MeshModel::draw(this);
}

void CubeMapMeshActor::changeModel(int prm_model_index) {
    MeshActor::changeModel(prm_model_index);
    _pCubeMapMeshModel = (CubeMapMeshModel*)_pModel;
}

CubeMapMeshActor::~CubeMapMeshActor() {
}
