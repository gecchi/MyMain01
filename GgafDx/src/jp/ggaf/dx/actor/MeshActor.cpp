#include "jp/ggaf/dx/actor/MeshActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/model/MeshModel.h"


using namespace GgafDx;

MeshActor::MeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     Checker* prm_pChecker) :

                         FigureActor(prm_name,
                                     prm_model_id,
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
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
}

MeshActor::MeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char prm_model_type,
                     const char* prm_effect_id,
                     const char prm_effect_type,
                     const char* prm_technique,
                     Checker* prm_pChecker) :

                         FigureActor(prm_name,
                                     prm_model_id,
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
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
}


void MeshActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) �Ɏ��s���܂����B");
    if (_pBumpMapTextureConnection) {
        hr = God::_pID3DDevice9->SetTexture(2, getBumpMapTexture());
        checkDxException(hr, D3D_OK, "SetTexture() �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matInvWorld, getInvMatWorldRotMv() );
        checkDxException(hr, D3D_OK, "SetMatrix(_h_matInvWorld) �Ɏ��s���܂����B");
        //TODO:����t�s��������Ōv�Z����Ηǂ��A���A�����ł��͂₭���邽�߂�getInvMatWorldRotMv()�ő�p�B
        //getInvMatWorldRotMv() �Ȃ̂ŁA�g��k�����l������ĂȂ��B�����ƂɊg�嗦���Ⴄ�ꍇ�A�o���v�}�b�v�͂�����Ƃ��������Ȃ�B
    }
    _pMeshModel->MeshModel::draw(this);
}

void MeshActor::effectBumpMapping(const char* prm_cubemap_tex, frame prm_frame) {
    setBumpMapTexture(prm_cubemap_tex);
    changeEffectTechniqueMoment("BumpMapping", prm_frame);
}

MeshActor::~MeshActor() {
}
