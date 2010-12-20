#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9MeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MeshModel::GgafDx9MeshModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9MeshModel::GgafDx9MeshModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;

    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _paIndexParam = NULL;
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDx9MeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    //�ΏۃA�N�^�[
    static GgafDx9MeshActor* pTargetActor;
    pTargetActor = (GgafDx9MeshActor*)prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    static GgafDx9MeshEffect* pMeshEffect;
    pMeshEffect = pTargetActor->_pMeshEffect;
    TRACE4("GgafDx9MeshModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName()<<" pTargetActor->_pMeshEffect="<<(pTargetActor->_pMeshEffect->_effect_name));
    //�ΏۃG�t�F�N�g
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MeshModel::FVF);
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDx9ModelManager::_pModelLastDraw != this || _nMaterialListGrp != 1) {
            if (_papTextureCon[material_no] != NULL) {
                //�e�N�X�`����s0���W�X�^�ɃZ�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->refer()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDx9MeshModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

        if ((GgafDx9EffectManager::_pEffect_Active != pMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            //�{���f���`�揉��
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("�O��_pEffect_Active != pMeshEffect (" <<(GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"!="<<(pMeshEffect->_effect_name)<<")");
                TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDx9EffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDx9MeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMeshEffect->_begin == true) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            //�O��`��Ɠ������f��
            hr = pID3DXEffect->CommitChanges(); //�}�e���A�����R�~�b�g���Ȃ���΂����Ȃ��B
            checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
    }
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9MeshModel::restore() {
    TRACE3("GgafDx9MeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMeshModel(this);
    TRACE3("GgafDx9MeshModel::restore() " << _model_name << " end");
}

void GgafDx9MeshModel::onDeviceLost() {
    TRACE3("GgafDx9MeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9MeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MeshModel::release() {
    TRACE3("GgafDx9MeshModel::release() " << _model_name << " start");

    _TRACE_("GgafDx9MeshModel::release() " << _model_name << " start");
    //�e�N�X�`�������
    if (_papTextureCon) {
        for (int i = 0; i < (int)_dwNumMaterials; i++) {
            if (_papTextureCon[i]) {
                TRACE3("close() _papTextureCon["<<i<<"]->"<<(_papTextureCon[i]->getIdStr()));
                _papTextureCon[i]->close();
            }
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //�e�N�X�`���̔z��

    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);

    DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paIdxBuffer_org);
    DELETE_IMPOSSIBLE_NULL(_pModel3D);
    //_pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
    _pMeshesFront = NULL;
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);


    TRACE3("GgafDx9MeshModel::release() " << _model_name << " end");

}
GgafDx9MeshModel::~GgafDx9MeshModel() {
    //release();
    //��GgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) �ŌĂяo�����
}

