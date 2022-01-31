#include "jp/ggaf/dx/model/ex/WorldBoundModel.h"

#include "jp/ggaf/dx/model/MassModel.h"

using namespace GgafDx;

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/effect/ex/WorldBoundEffect.h"
#include "jp/ggaf/dx/actor/ex/WorldBoundActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/Config.h"

WorldBoundModel::WorldBoundModel(const char* prm_model_id) : MorphMeshModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_model |= Obj_GgafDx_WorldBoundModel;
}


HRESULT WorldBoundModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("WorldBoundModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* pDevice = God::_pID3DDevice9;
    //�ΏۃA�N�^�[
    WorldBoundActor* pTargetActor = (WorldBoundActor*)prm_pActor_target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    WorldBoundEffect* pWorldBoundEffect = (WorldBoundEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pWorldBoundEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //���_�o�b�t�@�ݒ�
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //���_�t�H�[�}�b�g
        pDevice->SetStreamSource(0, _paVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //�C���f�b�N�X�o�b�t�@�ݒ�
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pWorldBoundEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        hr = pID3DXEffect->SetValue(pWorldBoundEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) &&
                i == 0) {
            if (pEffect_active) {
               _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B"<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pWorldBoundEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pWorldBoundEffect->_effect_name<<"("<<pWorldBoundEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
            //���[�t�^�[�Q�b�g�̐��ɂ�� pass ��؂�ւ��Ă���
            //�v���}�����b�V���̂�                             = pass0
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���P�� = pass1
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���Q�� = pass2
            //�ȉ��ő�X�܂�
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "BeginPass("<<_morph_target_num<<") �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pWorldBoundEffect->_begin) {
                throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pWorldBoundEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pWorldBoundEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif

    }
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pWorldBoundEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}


WorldBoundModel::~WorldBoundModel() {
}

