#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9CubeMapMorphMeshModel::GgafDx9CubeMapMorphMeshModel(char* prm_model_name) : GgafDx9MorphMeshModel(prm_model_name) {
    TRACE3("GgafDx9CubeMapMorphMeshModel::GgafDx9CubeMapMorphMeshModel(" << _model_name << ")");
}


HRESULT GgafDx9CubeMapMorphMeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDx9CubeMapMorphMeshModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //�ΏۃA�N�^�[
    GgafDx9CubeMapMorphMeshActor* pTargetActor = (GgafDx9CubeMapMorphMeshActor*)prm_pActor_Target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    GgafDx9CubeMapMorphMeshEffect* pCubeMapMorphMeshEffect = (GgafDx9CubeMapMorphMeshEffect*)prm_pActor_Target->_pGgafDx9Effect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pCubeMapMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //���_�o�b�t�@�ݒ�
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        GgafDx9God::_pID3DDevice9->SetVertexDeclaration( _pIDirect3DVertexDeclaration9); //���_�t�H�[�}�b�g
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            GgafDx9God::_pID3DDevice9->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //�C���f�b�N�X�o�b�t�@�ݒ�
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }
    if ( pTargetActor->_pCubeMapTextureCon) {
        GgafDx9God::_pID3DDevice9->SetTexture(1, pTargetActor->_pCubeMapTextureCon->refer()->_pIDirect3DBaseTexture9);
    } else {
        throwGgafCriticalException("GgafDx9CubeMapMorphMeshModel::draw ���}�b�v�e�N�X�`��������܂��� pTargetActor="<<pTargetActor->getName());
    }


    //�`��
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDx9ModelManager::_pModelLastDraw != this || _nMaterialListGrp != 1) {
            if (_papTextureCon[material_no]) {
                //�e�N�X�`����s0���W�X�^�ɃZ�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->refer()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDx9CubeMapMorphMeshModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
        }
        hr = pID3DXEffect->SetValue(pCubeMapMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw()SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

        if ((GgafDx9EffectManager::_pEffect_Active != pCubeMapMorphMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active) {
               TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDx9EffectManager::_pEffect_Active->_begin = false;
                }
#endif

             }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDx9CubeMapMorphMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");


            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name<<"("<<pCubeMapMorphMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() Begin() �Ɏ��s���܂����B");
            //���[�t�^�[�Q�b�g�̐��ɂ�� pass ��؂�ւ��Ă���
            //�v���}�����b�V���̂�                             = pass0
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���P�� = pass1
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���Q�� = pass2
            //�ȉ��ő�X�܂�
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw() BeginPass("<<_morph_target_num<<") �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pCubeMapMorphMeshEffect->_begin == true) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pCubeMapMorphMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDx9CubeMapMorphMeshModel::draw()CommitChanges() �Ɏ��s���܂����B");
        }

        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name);
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pCubeMapMorphMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;

    return D3D_OK;
}


GgafDx9CubeMapMorphMeshModel::~GgafDx9CubeMapMorphMeshModel() {
}

