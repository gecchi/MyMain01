#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorphMeshModel::GgafDxMorphMeshModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ")");
    _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ") Begin");
    // ���ʎ����N���X���w�肷�郂�f������"M/4/xxxxx"�Ƃ����`���ŁAGgafDxModelManager��
    // "M"����GgafDxMorphMeshModel�Ɣ��f���A"M"����菜����"4/XXXX"�����f�����Ƃ��Ĉ����B
    // prm_model_name �ɂ� "4/XXXX" ���A�n���Ă���B
    // �v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c����
    // ���f��������t�^�[�Q�b�g�����擾
    _TRACE_("GgafDxMorphMeshModel prm_model_name="<<prm_model_name);
    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, nullptr, 10);
    pT = strtok(nullptr, "/");
    if (pT == nullptr) {
        throwGgafCriticalException("GgafDxMorphMeshModel::GgafDxMorphMeshModel ���f��ID�Ƀ��[�t�^�[�Q�b�g�����w�肳��Ă܂���Bprm_model_name="<<prm_model_name);
    } else {
        _morph_target_num = num;
        _TRACE_("GgafDxMorphMeshModel ���[�t�^�[�Q�b�g���͎w�肠��A_morph_target_num="<<_morph_target_num);
    }
    //_morph_target_num = (int)(*prm_model_name - '0'); //���ꕶ���̔��p���������𐔒l��
    if (_morph_target_num > 6) {
        _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel ���[�t�^�[�Q�b�g�����ő�6�ȏ�w�肳��Ă܂��B�Ӑ}���Ă��܂����H _morph_target_num="<<_morph_target_num<<"/_model_name="<<_model_name);
    }
    _papModel3D = nullptr;
    _papMeshesFront = nullptr;

    _pIDirect3DVertexDeclaration9 = nullptr;
    _pVertexBuffer_primary = nullptr;
    _paIDirect3DVertexBuffer9_morph = nullptr;
    _pIndexBuffer = nullptr;
    _paVtxBuffer_org_primary = nullptr;
    _papaVtxBuffer_org_morph = nullptr;
    _paIdxBuffer_org = nullptr;
    _paIndexParam = nullptr;
    _material_list_grp_num = 0;
    _size_vertices_primary = 0;
    _size_vertex_unit_primary = 0;
    _size_vertices_morph = 0;
    _size_vertex_unit_morph = 0;
    _obj_model |= Obj_GgafDxMorphMeshModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreMorphMeshModel(GgafDxMorphMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ") End");
}

HRESULT GgafDxMorphMeshModel::draw(GgafDxDrawableActor* prm_pActor_target, int prm_draw_set_num) {
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    TRACE4("GgafDxMorphMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //�ΏۃA�N�^�[
    GgafDxMorphMeshActor* pTargetActor = (GgafDxMorphMeshActor*)prm_pActor_target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    GgafDxMorphMeshEffect* pMorphMeshEffect = (GgafDxMorphMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //���_�o�b�t�@�ݒ�
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetVertexDeclaration( _pIDirect3DVertexDeclaration9); //���_�t�H�[�}�b�g
        pDevice->SetStreamSource(0, _pVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //�C���f�b�N�X�o�b�t�@�ݒ�
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                //�e�N�X�`����s0���W�X�^�ɃZ�b�g
                pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxMorphMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw()SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

        if ((GgafDxEffectManager::_pEffect_active != pMorphMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (GgafDxEffectManager::_pEffect_active) {
               TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_active->_begin = false;
                }
#endif

             }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMorphMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");


            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name<<"("<<pMorphMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() Begin() �Ɏ��s���܂����B");
            //���[�t�^�[�Q�b�g�̐��ɂ�� pass ��؂�ւ��Ă���
            //�v���}�����b�V���̂�                             = pass0
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���P�� = pass1
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���Q�� = pass2
            //�ȉ��ő�X�܂�
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() BeginPass("<<_morph_target_num<<") �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMorphMeshEffect->_begin) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMorphMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw()CommitChanges() �Ɏ��s���܂����B");
        }

        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMorphMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}

void GgafDxMorphMeshModel::restore() {
    TRACE3("GgafDxMorphMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMorphMeshModel(this);
    TRACE3("GgafDxMorphMeshModel::restore() " << _model_name << " end");
}

void GgafDxMorphMeshModel::onDeviceLost() {
    TRACE3("GgafDxMorphMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxMorphMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMorphMeshModel::release() {
    TRACE3("GgafDxMorphMeshModel::release() " << _model_name << " start");

    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (DWORD i = 0; i < _num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��

    for (int pattern = 0; pattern <= _morph_target_num; pattern++) {
        if (pattern == 0) {
            GGAF_RELEASE(_pVertexBuffer_primary);
            GGAF_DELETEARR(_paVtxBuffer_org_primary);
        } else {
            GGAF_RELEASE(_paIDirect3DVertexBuffer9_morph[pattern-1]);
            GGAF_DELETEARR(_papaVtxBuffer_org_morph[pattern-1]);
        }
        Frm::Model3D* p = _papModel3D[pattern];
        GGAF_DELETE(p);
    }

    GGAF_DELETEARR(_paIDirect3DVertexBuffer9_morph);
    GGAF_DELETEARR(_papaVtxBuffer_org_morph);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pIDirect3DVertexDeclaration9);

    GGAF_DELETEARR(_papModel3D);
    //_papMeshesFront[0],_papMeshesFront[1] �� _papModel3D ��DELETE���Ă���̂ł���K�v�͖���
    GGAF_DELETEARR(_papMeshesFront);
    _papMeshesFront = nullptr;
    GGAF_DELETEARR(_paIdxBuffer_org);
    GGAF_DELETEARR(_paIndexParam);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    TRACE3("GgafDxMorphMeshModel::release() " << _model_name << " end");

}
GgafDxMorphMeshModel::~GgafDxMorphMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

