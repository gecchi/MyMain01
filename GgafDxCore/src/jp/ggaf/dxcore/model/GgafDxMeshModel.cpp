#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDxMeshModel::GgafDxMeshModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxMeshModel::GgafDxMeshModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;

    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _paIndexParam = NULL;
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreMeshModel(GgafDxMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDxMeshModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    //�ΏۃA�N�^�[
    //GgafDxMeshActor* pTargetActor = (GgafDxMeshActor*)prm_pActor_Target;
    GgafDxDrawableActor* pTargetActor = prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDxMeshEffect* pMeshEffect = (GgafDxMeshEffect*)prm_pActor_Target->_pEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertex_unit);
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxMeshModel::FVF);
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _nMaterialListGrp != 1) {
            if (_papTextureCon[material_no]) {
                //�e�N�X�`����s0���W�X�^�ɃZ�b�g
                GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->use()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxMeshModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                GgafDxGod::_pID3DDevice9->SetTexture(0, NULL);
            }
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

        if ((GgafDxEffectManager::_pEffect_Active != pMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            //�{���f���`�揉��
            if (GgafDxEffectManager::_pEffect_Active) {
                TRACE4("�O��_pEffect_Active != pMeshEffect (" <<(GgafDxEffectManager::_pEffect_Active->_effect_name)<<"!="<<(pMeshEffect->_effect_name)<<")");
                TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMeshEffect->_begin == true) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            //�O��`��Ɠ������f��
            hr = pID3DXEffect->CommitChanges(); //�}�e���A�����R�~�b�g���Ȃ���΂����Ȃ��B
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshModel::restore() {
    TRACE3("GgafDxMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMeshModel(this);
    TRACE3("GgafDxMeshModel::restore() " << _model_name << " end");
}

void GgafDxMeshModel::onDeviceLost() {
    TRACE3("GgafDxMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMeshModel::release() {
    TRACE3("GgafDxMeshModel::release() " << _model_name << " start");

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
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);


    TRACE3("GgafDxMeshModel::release() " << _model_name << " end");

}
GgafDxMeshModel::~GgafDxMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}


