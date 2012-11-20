#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxWorldBoundModel::GgafDxWorldBoundModel(char* prm_model_name) : GgafDxMorphMeshModel(prm_model_name) {
    TRACE3("GgafDxWorldBoundModel::GgafDxWorldBoundModel(" << _model_name << ")");
    _obj_model |= Obj_GgafDxWorldBoundModel;
}


HRESULT GgafDxWorldBoundModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxWorldBoundModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //�ΏۃA�N�^�[
    GgafDxWorldBoundActor* pTargetActor = (GgafDxWorldBoundActor*)prm_pActor_Target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    GgafDxWorldBoundEffect* pWorldBoundEffect = (GgafDxWorldBoundEffect*)prm_pActor_Target->_pEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pWorldBoundEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //���_�o�b�t�@�ݒ�
    if (GgafDxModelManager::_pModelLastDraw != this) {
        GgafDxGod::_pID3DDevice9->SetVertexDeclaration( _pIDirect3DVertexDeclaration9); //���_�t�H�[�}�b�g
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            GgafDxGod::_pID3DDevice9->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //�C���f�b�N�X�o�b�t�@�ݒ�
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        hr = pID3DXEffect->SetValue(pWorldBoundEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw()SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

        if ((GgafDxEffectManager::_pEffect_Active != pWorldBoundEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) &&
                i == 0) {
            if (GgafDxEffectManager::_pEffect_Active) {
               TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() EndPass() �Ɏ��s���܂����B"<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxWorldBoundModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");


            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name<<"("<<pWorldBoundEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() Begin() �Ɏ��s���܂����B");
            //���[�t�^�[�Q�b�g�̐��ɂ�� pass ��؂�ւ��Ă���
            //�v���}�����b�V���̂�                             = pass0
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���P�� = pass1
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���Q�� = pass2
            //�ȉ��ő�X�܂�
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw() BeginPass("<<_morph_target_num<<") �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pWorldBoundEffect->_begin == true) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pWorldBoundEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxWorldBoundModel::draw()CommitChanges() �Ɏ��s���܂����B");
        }

        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pWorldBoundEffect->_effect_name);
        GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pWorldBoundEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;

    return D3D_OK;
}


GgafDxWorldBoundModel::~GgafDxWorldBoundModel() {
}

