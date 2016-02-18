#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMassMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxMassMeshModel::GgafDxMassMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    // prm_model_name �ɂ� "xxxxxx" or "8/xxxxx" ���A�n���Ă���B
    // �����`��Z�b�g����8�Ƃ����Ӗ��ł��B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c�������ȁB
    // ���f�������瓯���`��Z�b�g���w�肪����Ύ��o���B�������8
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("GgafDxMassMeshModel::GgafDxMassMeshModel "<<
                "prm_model_name �ɂ� \"xxxxxx\" or \"8/xxxxx\" �`�����w�肵�Ă��������B \n"<<
                "���ۂ̈����́Aprm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > MAX_INSTACE) {
            _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") �̓����`��Z�b�g���I�[�o�[�B�ő��"<<MAX_INSTACE<<"�Z�b�g���ł�������ȏオ�ݒ肳��Ă��܂��B�Ӑ}���Ă��܂����H _set_num="<<_set_num<<"�B");
        }
    } else {
        _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") �̃Z�b�g���ȗ��̂��߁A�W���̍ő��"<<MAX_INSTACE<<"�Z�b�g���ݒ肳��܂��B");
        _set_num = MAX_INSTACE;
    }
    _pVertexBuffer_model = nullptr;
    _pVertexBuffer_instacedata = nullptr;
    _pIndexBuffer = nullptr;
    _pIDirect3DVertexDeclaration9 = nullptr;
    _paUint_material_list_grp_num = nullptr;
    _paVtxBuffer_org_model = nullptr;
    _paIdxBuffer_org = nullptr;
    _size_vertex_unit_instacedata = 0;
    _size_vertex_unit_model = 0;
    _size_vertices_model = 0;
    _nVertices = 0;
    _nFaces= 0;

    _obj_model |= Obj_GgafDxMassMeshModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̃����o�[��������
    //void GgafDxModelManager::restoreMassMeshModel(GgafDxMassMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ") End");
}

//�`��
HRESULT GgafDxMassMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxMassMeshModel::draw() "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�ΏۃA�N�^�[
    const GgafDxMassMeshActor* const pTargetActor = (GgafDxMassMeshActor*)prm_pActor_target;
    //�Ώ�MassMeshActor�̃G�t�F�N�g���b�p
    GgafDxMassMeshEffect* const pMassMeshEffect = (GgafDxMassMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMassMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //���_�o�b�t�@(�C���X�^���X�f�[�^)��������
    UINT update_vertex_instacedata_size = _size_vertex_unit_instacedata * prm_draw_set_num;
    void* pVertexBuffer_instacedata;
    hr = _pVertexBuffer_instacedata->Lock(
                                  0,
                                  update_vertex_instacedata_size,
                                  (void**)&pVertexBuffer_instacedata,
                                  D3DLOCK_DISCARD
                                );
    checkDxException(hr, D3D_OK, "[GgafDxMassMeshModel::draw] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
    memcpy(
      pVertexBuffer_instacedata,
      _aInstancedata,
      update_vertex_instacedata_size
    );
    _pVertexBuffer_instacedata->Unlock();

    //���f���������ł��A�Z�b�g���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 0 �Ɏ��s���܂����Bprm_draw_set_num="<<prm_draw_set_num);

    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 1 �Ɏ��s���܂����B");
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        hr = pDevice->SetVertexDeclaration(_pIDirect3DVertexDeclaration9); //���_�t�H�[�}�b�g
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetVertexDeclaration �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 0 �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(1, _pVertexBuffer_instacedata, 0, _size_vertex_unit_instacedata);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 1 �Ɏ��s���܂����B");
        hr = pDevice->SetIndices(_pIndexBuffer);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetIndices �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            pDevice->SetTexture(0, nullptr);
        }
    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pMassMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxMassMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name<<"("<<pMassMeshEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pMassMeshEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMeshEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);

    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  0,
                                  0,
                                  _nVertices,
                                  0,
                                  _nFaces);
    //checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass=1 �Ɏ��s���܂����B");
    if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() �P�p�X�� EndPass() �Ɏ��s���܂����B");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"�p�X�� BeginPass("<<i<<") �Ɏ��s���܂����B");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                          0,
                                          0,
                                          _nVertices,
                                          0,
                                          _nFaces);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass="<<(i+1)<<" �Ɏ��s���܂����B");
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"�p�X�� EndPass() �Ɏ��s���܂����B");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() �P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }

//    pDevice->SetStreamSourceFreq( 0, 1 );
//    pDevice->SetStreamSourceFreq( 1, 1 );

    GgafGod::_num_drawing++;
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMassMeshModel::restore() {
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMassMeshModel(this);
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " end");
}

void GgafDxMassMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMassMeshModel::release() {
    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " start");

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
    GGAF_RELEASE(_pVertexBuffer_instacedata);
    GGAF_RELEASE(_pVertexBuffer_model);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pIDirect3DVertexDeclaration9);

    GGAF_DELETEARR(_paVtxBuffer_org_model);
    GGAF_DELETEARR(_paIdxBuffer_org);

    GGAF_DELETE(_pModel3D);
    //_pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
    _pMeshesFront = nullptr;
    GGAF_DELETEARR(_paUint_material_list_grp_num);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);

    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " end");

}
GgafDxMassMeshModel::~GgafDxMassMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

