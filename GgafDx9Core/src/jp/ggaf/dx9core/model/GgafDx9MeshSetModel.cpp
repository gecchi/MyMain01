#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9MeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
int GgafDx9MeshSetModel::_draw_set_num_LastDraw = -1;
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MeshSetModel::GgafDx9MeshSetModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9MeshSetModel::GgafDx9MeshSetModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;
    // prm_model_name �ɂ� "xxxxxx" or "8/xxxxx" ���A�n���Ă���B
    // �����`��Z�b�g����8�Ƃ����Ӗ��ł��B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c�������ȁB
    // ���f�������瓯���`��Z�b�g���w�肪����Ύ��o���B�������8
    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        _TRACE_("GgafDx9MeshSetModel("<<prm_model_name<<") �̃Z�b�g���ȗ��̂��߁A�W���̍ő��15�Z�b�g���ݒ肳��܂��B");
        _set_num = 15;
    } else {
        _set_num = num;
        if (_set_num > 15) {
            _TRACE_("GgafDx9MeshSetModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B�ő��15�Z�b�g���ł�������ȏオ�ݒ肳��Ă��܂��B�Ӑ}���Ă��܂����H _set_num="<<_set_num<<"�B");
        }
    }
    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _pa_nMaterialListGrp = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _papaIndexParam = NULL;
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̃����o�[��������
    //void GgafDx9ModelManager::restoreMeshSetModel(GgafDx9MeshSetModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDx9MeshSetModel::GgafDx9MeshSetModel(" << _model_name << ") End");
}

//�`��
HRESULT GgafDx9MeshSetModel::draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    //�ΏۃA�N�^�[
    GgafDx9MeshSetActor* pTargetActor = (GgafDx9MeshSetActor*)prm_pActor_Target;
    //�Ώ�MeshSetActor�̃G�t�F�N�g���b�p
    GgafDx9MeshSetEffect* pMeshSetEffect = (GgafDx9MeshSetEffect*)prm_pActor_Target->_pEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;

    //���f���������ł��A�Z�b�g���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    if (GgafDx9ModelManager::_pModelLastDraw  != this) {
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MeshSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }


    //�`��
    for (UINT material_grp_index = 0; material_grp_index < _pa_nMaterialListGrp[prm_draw_set_num-1]; material_grp_index++) {
        // TODO
        //���f���������ł��A�Z�b�g�����������A�}�e���A��NO���P�����Ȃ��Ȃ�΁A�e�N�X�`���ݒ���X�L�b�v�ł���
        if (GgafDx9ModelManager::_pModelLastDraw  != this      ||
            //GgafDx9MeshSetModel::_draw_set_num_LastDraw != draw_set_num ||
            _pa_nMaterialListGrp[prm_draw_set_num-1] != 1)
        {
            material_no = _papaIndexParam[prm_draw_set_num-1][material_grp_index].MaterialNo;
            if (_papTextureCon[material_no]) {
                //�e�N�X�`����s0���W�X�^�ɃZ�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->refer()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //MaterialDiffuse��GgafDx9MeshSetActor���Ń}�e���A����ݒ肷��B�}�e���A���F�͒P�F�Ƃ���B
            //���R��GgafDx9MeshSetActor�̃����yGgafDx9MeshSetActor�̃}�e���A���J���[�ɂ��āz���Q��
        }


        if (material_grp_index == 0 && (GgafDx9EffectManager::_pEffect_Active != pMeshSetEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)) {
            if (GgafDx9EffectManager::_pEffect_Active) {
                TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDx9EffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDx9MeshSetModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name<<"("<<pMeshSetEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMeshSetEffect->_begin == true) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMeshSetEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].BaseVertexIndex,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].MinIndex,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].NumVertices,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].StartIndex,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9MeshSetModel::_draw_set_num_LastDraw = prm_draw_set_num;
    GgafDx9EffectManager::_pEffect_Active = pMeshSetEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    return D3D_OK;
}

void GgafDx9MeshSetModel::restore() {
    TRACE3("GgafDx9MeshSetModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMeshSetModel(this);
    TRACE3("GgafDx9MeshSetModel::restore() " << _model_name << " end");
}

void GgafDx9MeshSetModel::onDeviceLost() {
    TRACE3("GgafDx9MeshSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9MeshSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MeshSetModel::release() {
    TRACE3("GgafDx9MeshSetModel::release() " << _model_name << " start");

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
    for (int i = 0; i < _set_num; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam);
    DELETEARR_IMPOSSIBLE_NULL(_pa_nMaterialListGrp);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);

    TRACE3("GgafDx9MeshSetModel::release() " << _model_name << " end");

}
GgafDx9MeshSetModel::~GgafDx9MeshSetModel() {
    //release();
    //��GgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) �ŌĂяo�����
}

