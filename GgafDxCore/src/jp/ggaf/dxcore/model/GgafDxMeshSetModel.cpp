#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxMeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxMeshSetModel::GgafDxMeshSetModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMeshSetModel::GgafDxMeshSetModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    // prm_model_name �ɂ� "xxxxxx" or "8/xxxxx" ���A�n���Ă���B
    // �����`��Z�b�g����8�Ƃ����Ӗ��ł��B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c�������ȁB
    // ���f�������瓯���`��Z�b�g���w�肪����Ύ��o���B�������8
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("GgafDxMeshSetModel::GgafDxMeshSetModel "<<
                "prm_model_name �ɂ� \"xxxxxx\" or \"8/xxxxx\" �`�����w�肵�Ă��������B \n"<<
                "���ۂ̈����́Aprm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > 15) {
            _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B�ő��15�Z�b�g���ł�������ȏオ�ݒ肳��Ă��܂��B�Ӑ}���Ă��܂����H _set_num="<<_set_num<<"�B");
        }
    } else {
        _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") �̃Z�b�g���ȗ��̂��߁A�W���̍ő��15�Z�b�g���ݒ肳��܂��B");
        _set_num = 15;
    }
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paUint_material_list_grp_num = nullptr;
    _paVtxBuffer_org = nullptr;
    _paIdxBuffer_org = nullptr;
    _papaIndexParam = nullptr;
    _size_vertex_unit= 0;
    _size_vertices = 0;
    _nVertices = 0;
    _nFaces= 0;

    _obj_model |= Obj_GgafDxMeshSetModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̃����o�[��������
    //void GgafDxModelManager::restoreMeshSetModel(GgafDxMeshSetModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDxMeshSetModel::GgafDxMeshSetModel(" << _model_name << ") End");
}

//�`��
HRESULT GgafDxMeshSetModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxMeshSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxMeshSetModel::draw() "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�ΏۃA�N�^�[
    const GgafDxMeshSetActor* const pTargetActor = (GgafDxMeshSetActor*)prm_pActor_target;
    //�Ώ�MeshSetActor�̃G�t�F�N�g���b�p
    GgafDxMeshSetEffect* const pMeshSetEffect = (GgafDxMeshSetEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������ł��A�Z�b�g���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    if (GgafDxModelManager::_pModelLastDraw  != this) {
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxMeshSetModel::FVF);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    const UINT material_list_grp_num = _paUint_material_list_grp_num[prm_draw_set_num-1];
    for (UINT material_grp_index = 0; material_grp_index < material_list_grp_num; material_grp_index++) {
        const INDEXPARAM& idxparam = _papaIndexParam[prm_draw_set_num-1][material_grp_index];
        //���f���������ł��A�Z�b�g�����������A�}�e���A��NO���P�����Ȃ��Ȃ�΁A�e�N�X�`���ݒ���X�L�b�v�ł���
        if (GgafDxModelManager::_pModelLastDraw  != this || material_list_grp_num != 1) {
            const UINT material_no = idxparam.MaterialNo;
            if (_papTextureConnection[material_no]) {
                //�e�N�X�`����s0���W�X�^�ɃZ�b�g
                pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxMeshSetModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
            //MaterialDiffuse��GgafDxMeshSetActor���Ń}�e���A����ݒ肷��B�}�e���A���F�͒P�F�Ƃ���B
            //���R��GgafDxMeshSetActor�̃����yGgafDxMeshSetActor�̃}�e���A���J���[�ɂ��āz���Q��
        }

        if (material_grp_index == 0 && (GgafDxEffectManager::_pEffect_active != pMeshSetEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)) {
            if (GgafDxEffectManager::_pEffect_active) {
                _TRACE4_("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMeshSetModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name<<"("<<pMeshSetEffect<<")");
            //UINT numPass;
            hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMeshSetEffect->_begin) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshSetEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);

        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
        if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() �P�p�X�� EndPass() �Ɏ��s���܂����B");
            for (UINT i = 1; i < _num_pass; i++) {
                hr = pID3DXEffect->BeginPass(i);
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() "<<i+1<<"�p�X�� BeginPass("<<i<<") �Ɏ��s���܂����B");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() "<<i+1<<"�p�X�� EndPass() �Ɏ��s���܂����B");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() �P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
        }
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMeshSetEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshSetModel::restore() {
    _TRACE3_("GgafDxMeshSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMeshSetModel(this);
    _TRACE3_("GgafDxMeshSetModel::restore() " << _model_name << " end");
}

void GgafDxMeshSetModel::onDeviceLost() {
    _TRACE3_("GgafDxMeshSetModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMeshSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMeshSetModel::release() {
    _TRACE3_("GgafDxMeshSetModel::release() " << _model_name << " start");

    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);

    GGAF_DELETEARR(_paVtxBuffer_org);
    GGAF_DELETEARR(_paIdxBuffer_org);

    GGAF_DELETE(_pModel3D);
    //_pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
    _pMeshesFront = nullptr;
    if (_papaIndexParam) {
        for (int i = 0; i < _set_num; i++) {
            GGAF_DELETEARR(_papaIndexParam[i]);
        }
    }
    GGAF_DELETEARR(_papaIndexParam);
    GGAF_DELETEARR(_paUint_material_list_grp_num);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);

    _TRACE3_("GgafDxMeshSetModel::release() " << _model_name << " end");

}
GgafDxMeshSetModel::~GgafDxMeshSetModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

