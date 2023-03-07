#include "jp/ggaf/dx/actor/MorphMeshActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/effect/MorphMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

MorphMeshActor::MorphMeshActor(const char* prm_name,
                               const char* prm_model,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               CollisionChecker* prm_pChecker) :

                                   FigureActor(prm_name,
                                               prm_model,
                                               TYPE_MORPHMESH_MODEL,
                                               prm_effect_id,
                                               TYPE_MORPHMESH_EFFECT,
                                               prm_technique,
                                               prm_pChecker),
_pMorpher(new Morpher<MorphMeshActor>(this)),
_pMorphMeshModel((MorphMeshModel*)_pModel),
_pMorphMeshEffect((MorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MorphMeshActor;
    _class_name = "MorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    //重み初期化
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMorphMeshModel->_morph_target_num;
}


MorphMeshActor::MorphMeshActor(const char* prm_name,
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
                                               prm_pChecker),
_pMorpher(new Morpher<MorphMeshActor>(this)),
_pMorphMeshModel((MorphMeshModel*)_pModel),
_pMorphMeshEffect((MorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MorphMeshActor;
    _class_name = "MorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    //重み初期化
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMorphMeshModel->_morph_target_num;
}
void MorphMeshActor::setMorphWeight(int prm_target_mesh_no, float prm_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("MorphMeshActor::setMorphWeight() name="<<getName()<<" の、prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(modelの有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
     _weight[prm_target_mesh_no] = prm_weight;
}
void MorphMeshActor::setMorphWeight(float prm_weight) {
    for (int i = 1; i <= _morph_target_num; i++) {
        _weight[i] = prm_weight;
    }
}

float MorphMeshActor::getMorphWeight(int prm_target_mesh_no) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    return _weight[prm_target_mesh_no];
}

void MorphMeshActor::addMorphWeight(int prm_target_mesh_no, float prm_add_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    _weight[prm_target_mesh_no] += prm_add_weight;
}

void MorphMeshActor::processDraw() {
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    const MorphMeshEffect* const pMorphMeshEffect = _pMorphMeshEffect;
    ID3DXEffect* const pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(pMorphMeshEffect->_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matView) に失敗しました。");
    hr = pID3DXEffect->SetInt(pMorphMeshEffect->_h_morph_target_num, _pMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "SetInt(_h_morph_target_num) に失敗しました。");
    for (int pattern = 1; pattern <= _pMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "SetFloat(_ah_weight["<<pattern<<"]) に失敗しました。");
    }
    hr = pID3DXEffect->SetMatrix(pMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
    _pMorphMeshModel->draw(this);
}

int MorphMeshActor::getMorphTergetNum() {
    return _pMorphMeshModel->_morph_target_num;
}

void MorphMeshActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pMorphMeshModel = (MorphMeshModel*)_pModel;
}

MorphMeshActor::~MorphMeshActor() {
    delete _pMorpher;
}
