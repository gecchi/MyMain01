#include "jp/ggaf/dx/actor/MeshActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/model/MeshModel.h"


using namespace GgafDx;

MeshActor::MeshActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     CollisionChecker* prm_pChecker) :

                         FigureActor(prm_name,
                                     prm_model,
                                     TYPE_MESH_MODEL,
                                     prm_effect_id,
                                     TYPE_MESH_EFFECT,
                                     prm_technique,
                                     prm_pChecker) ,
                         IBumpMapActor(),
_pMeshModel((MeshModel*)_pModel),
_pMeshEffect((MeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MeshActor;
    _class_name = "MeshActor";
    _far_rate = -1.0f;
    _lambert_flg = 1.0f; //1.0:Half Lambert/ -1.0:Lambert
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

MeshActor::MeshActor(const char* prm_name,
                     const char* prm_model,
                     const char prm_model_type,
                     const char* prm_effect_id,
                     const char prm_effect_type,
                     const char* prm_technique,
                     CollisionChecker* prm_pChecker) :

                         FigureActor(prm_name,
                                     prm_model,
                                     prm_model_type,
                                     prm_effect_id,
                                     prm_effect_type,
                                     prm_technique,
                                     prm_pChecker) ,
                         IBumpMapActor(),
_pMeshModel((MeshModel*)_pModel),
_pMeshEffect((MeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MeshActor;
    _class_name = "MeshActor";
    _far_rate = -1.0f;
    _lambert_flg = 1.0f; //1.0:Half Lambert/ -1.0:Lambert
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

void MeshActor::changeModel(int prm_model_index) {
    FigureActor::changeModel(prm_model_index);
    _pMeshModel = (MeshModel*)_pModel;
}

void MeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_lambert_flg, _lambert_flg );
    checkDxException(hr, D3D_OK, "SetFloat(_h_lambert_flg) に失敗しました。");
    if (_pBumpMapTextureConnection) {
        hr = pCARETAKER->_pID3DDevice9->SetTexture(2, getBumpMapTexture());
        checkDxException(hr, D3D_OK, "SetTexture() に失敗しました。");
        hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matInvWorld, getInvMatWorldRotMv() );
        checkDxException(hr, D3D_OK, "SetMatrix(_h_matInvWorld) に失敗しました。");
        //TODO:毎回逆行列をここで計算すれば良い、が、少しでもはやくするためにgetInvMatWorldRotMv()で代用。
        //getInvMatWorldRotMv() なので、拡大縮小が考慮されてない。軸ごとに拡大率が違う場合、バンプマップはちょっとおかしくなる。
    }
    _pMeshModel->MeshModel::draw(this);
}

void MeshActor::effectBumpMapping(const char* prm_cubemap_tex, frame prm_frame) {
    setBumpMapTexture(prm_cubemap_tex);
    changeEffectTechniqueMoment("BumpMapping", prm_frame);
}

MeshActor::~MeshActor() {
}
