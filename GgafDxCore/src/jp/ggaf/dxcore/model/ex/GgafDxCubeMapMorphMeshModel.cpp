#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMorphMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMorphMeshEffect.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMorphMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMorphMeshModel::GgafDxCubeMapMorphMeshModel(const char* prm_model_name) : GgafDxMorphMeshModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _obj_model |= Obj_GgafDxCubeMapMorphMeshModel;
}


HRESULT GgafDxCubeMapMorphMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxCubeMapMorphMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //�ΏۃA�N�^�[
    GgafDxCubeMapMorphMeshActor* pTargetActor = (GgafDxCubeMapMorphMeshActor*)prm_pActor_target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    GgafDxCubeMapMorphMeshEffect* pCubeMapMorphMeshEffect = (GgafDxCubeMapMorphMeshEffect*)(prm_pActor_target->getEffect());
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pCubeMapMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //���_�o�b�t�@�ݒ�
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //���_�t�H�[�}�b�g
        pDevice->SetStreamSource(0, _pVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //�C���f�b�N�X�o�b�t�@�ݒ�
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pCubeMapMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //�}�e���A��0�Ԃ́A���ʂɋK��̃e�N�X�`����ݒ肷��d�l
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("GgafDxCubeMapMorphMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pCubeMapMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((pEffect_active != pCubeMapMorphMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
               _TRACE4_("EndPass("<< pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B"<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");


            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name<<"("<<pCubeMapMorphMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "�Ɏ��s���܂����B");
            //���[�t�^�[�Q�b�g�̐��ɂ�� pass ��؂�ւ��Ă���
            //�v���}�����b�V���̂�                             = pass0
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���P�� = pass1
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���Q�� = pass2
            //�ȉ��ő�X�܂�
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "BeginPass("<<_morph_target_num<<") �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pCubeMapMorphMeshEffect->_begin) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pCubeMapMorphMeshEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pCubeMapMorphMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pCubeMapMorphMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}


GgafDxCubeMapMorphMeshModel::~GgafDxCubeMapMorphMeshModel() {
}

