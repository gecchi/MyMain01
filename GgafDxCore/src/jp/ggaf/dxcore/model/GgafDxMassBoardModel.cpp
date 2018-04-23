#include "jp/ggaf/dxcore/model/GgafDxMassBoardModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassBoardActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassBoardModel::GgafDxMassBoardModel(const char* prm_model_name) : GgafDxMassModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _paVtxBuffer_data_model = nullptr;
    _paIndexBuffer_data = nullptr;

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _model_half_width_px = _model_width_px/2;
    _model_half_height_px = _model_height_px/2;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _papTextureConnection = nullptr;
    _obj_model |= Obj_GgafDxMassBoardModel;

    registerCallback_VertexModelInfo(GgafDxMassBoardModel::createVertexModel); //���_���C�A�E�g���쐬�R�[���o�b�N�֐�
}

void GgafDxMassBoardModel::createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info) {
    int element_num = 3;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    WORD  st0_offset_next = 0;
    //float x, y, z;    // :POSITION0 ���_���W
    out_info->paElement[0].Stream = 0;
    out_info->paElement[0].Offset = st0_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_POSITION;
    out_info->paElement[0].UsageIndex = 0;
    st0_offset_next += sizeof(float)*3;
    //float nx, ny, nz; // :NORMAL0 �@��
    out_info->paElement[1].Stream = 0;
    out_info->paElement[1].Offset = st0_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_NORMAL;
    out_info->paElement[1].UsageIndex = 0;
    st0_offset_next += sizeof(float)*3;
    //float tu, tv;    // : TEXCOORD0  �e�N�X�`�����W
    out_info->paElement[2].Stream = 0;
    out_info->paElement[2].Offset = st0_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 0;
    //st0_offset_next += sizeof(float)*2;
    out_info->element_num = element_num;
}


//�`��
HRESULT GgafDxMassBoardModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxMassBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    if (_pVertexBuffer_instancedata == nullptr) {
        createVertexElements(); //�f�o�C�X���X�g���A���ɌĂяo�����
    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException(FUNC_NAME<<" "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�Ώ�Actor
    const GgafDxMassBoardActor* const pTargetActor = (GgafDxMassBoardActor*)prm_pActor_target;
    //�Ώ�MassBoardActor�̃G�t�F�N�g���b�p
    GgafDxMassBoardEffect* const pMassBoardEffect = (GgafDxMassBoardEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMassBoardEffect->_pID3DXEffect;

    HRESULT hr;
    //���_�o�b�t�@(�C���X�^���X�f�[�^)��������
    UINT update_vertex_instancedata_size = _size_vertex_unit_instancedata * prm_draw_set_num;
    void* pInstancedata = prm_pPrm ? prm_pPrm : this->_pInstancedata; //prm_pPrm �͗Վ��̃e���|�����C���X�^���X�f�[�^
    void* pDeviceMemory = 0;
    hr = _pVertexBuffer_instancedata->Lock(0, update_vertex_instancedata_size, (void**)&pDeviceMemory, D3DLOCK_DISCARD);
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
    memcpy(pDeviceMemory, pInstancedata, update_vertex_instancedata_size);
    hr = _pVertexBuffer_instancedata->Unlock();
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_name);

    //���f���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq 1 �Ɏ��s���܂����B");
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //���_�t�H�[�}�b�g
        checkDxException(hr, D3D_OK, "SetVertexDeclaration �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 �Ɏ��s���܂����B");
        hr = pDevice->SetStreamSource(1, _pVertexBuffer_instancedata, 0, _size_vertex_unit_instancedata);
        checkDxException(hr, D3D_OK, "SetStreamSource 1 �Ɏ��s���܂����B");
        hr = pDevice->SetIndices(_pIndexBuffer);
        checkDxException(hr, D3D_OK, "SetIndices �Ɏ��s���܂����B");

        hr = pID3DXEffect->SetFloat(pMassBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMassBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");

        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxMassBoardActor::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            pDevice->SetTexture(0, nullptr);
        }
    }
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "SetStreamSourceFreq 0 �Ɏ��s���܂����Bprm_draw_set_num="<<prm_draw_set_num);
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
           _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassBoardEffect->_effect_name<<"("<<pMassBoardEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pMassBoardEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassBoardEffect->_effect_name);
    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                       0,
                                       0,
                                       _nVertices,
                                       0,
                                       _nFaces);
    if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"�p�X�� BeginPass("<<pass<<") �Ɏ��s���܂����B");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                               0,
                                               0,
                                               _nVertices,
                                               0,
                                               _nFaces);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "�P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }
    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassBoardEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif
    return D3D_OK;
}

void GgafDxMassBoardModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GgafDxModelManager* pModelManager = pGOD->_pModelManager;
    HRESULT hr;
    if (!_paVtxBuffer_data_model) {
        //�ÓI�ȏ��ݒ�
        std::vector<std::string> names = UTIL::split(std::string(_model_name), "/");
        std::string xfile_name = ""; //�ǂݍ���X�t�@�C����
        if (names.size() == 1) {
            _TRACE_(FUNC_NAME<<" "<<_model_name<<" �̍ő哯���`��I�u�W�F�N�g���́A�f�t�H���g��"<<GGAFDXMASS_MAX_INSTANCE_NUM<<" ���ݒ肳��܂����B");
            _set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
            xfile_name = GgafDxModelManager::getSpriteFileName(names[0]);
        } else if (names.size() == 2) {
            _set_num = STOI(names[0]);
            xfile_name = GgafDxModelManager::getSpriteFileName(names[1]);
        } else {
            throwGgafCriticalException("_model_name �ɂ� \"xxxxxx\" or \"8/xxxxx\" �`�����w�肵�Ă��������B \n"
                    "���ۂ́A_model_name="<<_model_name<<" �ł����B");
        }
        if (_set_num < 1 || _set_num > GGAFDXMASS_MAX_INSTANCE_NUM) {
            throwGgafCriticalException(_model_name<<"�̍ő哯���`��I�u�W�F�N�g�����s���B�͈͂� 1�`"<<GGAFDXMASS_MAX_INSTANCE_NUM<<"�Z�b�g�ł��B_set_num="<<_set_num);
        }
        if (xfile_name == "") {
            throwGgafCriticalException("�X�v���C�g��`�t�@�C��(*.sprx)��������܂���Bmodel_name="<<(_model_name));
        }
        GgafDxModelManager::SpriteXFileFmt xdata;
        pModelManager->obtainSpriteInfo(&xdata, xfile_name);
        _model_width_px  = xdata.width;
        _model_height_px = xdata.height;
        _model_half_width_px = _model_width_px/2;
        _model_half_height_px = _model_height_px/2;
        _row_texture_split = xdata.row_texture_split;
        _col_texture_split = xdata.col_texture_split;
        _nVertices = 4;
        _nFaces = 2;
        _paVtxBuffer_data_model = NEW GgafDxMassBoardModel::VERTEX_model[_nVertices];
        _size_vertex_unit_model = sizeof(GgafDxMassBoardModel::VERTEX_model);
        _size_vertices_model = sizeof(GgafDxMassBoardModel::VERTEX_model) * _nVertices;

        float du = 0.0f; //1.0 / tex_width  / 100000.0; //�e�N�X�`���̕�1px��10000����1px
        float dv = 0.0f; //1.0 / tex_height / 100000.0; //�e�N�X�`���̍���1px��10000����1px

        //����
        _paVtxBuffer_data_model[0].x = 0.0f;
        _paVtxBuffer_data_model[0].y = 0.0f;
        _paVtxBuffer_data_model[0].z = 0.0f;
        _paVtxBuffer_data_model[0].nx = 0.0f;   //���ݖ@���̓V�F�[�_�[�Ŗ��g�p
        _paVtxBuffer_data_model[0].ny = 0.0f;
        _paVtxBuffer_data_model[0].nz = -1.0f;
        _paVtxBuffer_data_model[0].tu = du;
        _paVtxBuffer_data_model[0].tv = dv;
        //�E��
        _paVtxBuffer_data_model[1].x = xdata.width;
        _paVtxBuffer_data_model[1].y = 0.0f;
        _paVtxBuffer_data_model[1].z = 0.0f;
        _paVtxBuffer_data_model[1].nx = 0.0f;
        _paVtxBuffer_data_model[1].ny = 0.0f;
        _paVtxBuffer_data_model[1].nz = -1.0f;
        _paVtxBuffer_data_model[1].tu = (1.0 / xdata.col_texture_split) - du;
        _paVtxBuffer_data_model[1].tv = dv;
        //����
        _paVtxBuffer_data_model[2].x = 0.0f;
        _paVtxBuffer_data_model[2].y = xdata.height;
        _paVtxBuffer_data_model[2].z = 0.0f;
        _paVtxBuffer_data_model[2].nx = 0.0f;
        _paVtxBuffer_data_model[2].ny = 0.0f;
        _paVtxBuffer_data_model[2].nz = -1.0f;
        _paVtxBuffer_data_model[2].tu = du;
        _paVtxBuffer_data_model[2].tv = (1.0 / xdata.row_texture_split) - dv;
        //�E��
        _paVtxBuffer_data_model[3].x = xdata.width;
        _paVtxBuffer_data_model[3].y = xdata.height;
        _paVtxBuffer_data_model[3].z = 0.0f;
        _paVtxBuffer_data_model[3].nx = 0.0f;
        _paVtxBuffer_data_model[3].ny = 0.0f;
        _paVtxBuffer_data_model[3].nz = -1.0f;
        _paVtxBuffer_data_model[3].tu = (1.0 / xdata.col_texture_split) - du;
        _paVtxBuffer_data_model[3].tv = (1.0 / xdata.row_texture_split) - dv;

        _paIndexBuffer_data = NEW WORD[(_nFaces*3)];
        _paIndexBuffer_data[0] = 0;
        _paIndexBuffer_data[1] = 1;
        _paIndexBuffer_data[2] = 2;

        _paIndexBuffer_data[3] = 1;
        _paIndexBuffer_data[4] = 3;
        _paIndexBuffer_data[5] = 2;
        //����(Board�Ȃ̂ŁA���ۂ͎g��Ȃ�)
        FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[0].x * _paVtxBuffer_data_model[0].x +
                                                          _paVtxBuffer_data_model[0].y * _paVtxBuffer_data_model[0].y +
                                                          _paVtxBuffer_data_model[0].z * _paVtxBuffer_data_model[0].z));
        _bounding_sphere_radius = model_bounding_sphere_radius;

        setMaterial();
        _pa_texture_filenames[0] = std::string(xdata.texture_file);
    }
    //�f�o�C�X�ɒ��_�o�b�t�@�쐬(���f��)
    if (_pVertexBuffer_model == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices_model,
                D3DUSAGE_WRITEONLY,
                0,
                D3DPOOL_DEFAULT,
                &(_pVertexBuffer_model),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void* pDeviceMemory = 0;
        hr = _pVertexBuffer_model->Lock(0, _size_vertices_model, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
        memcpy(pDeviceMemory, _paVtxBuffer_data_model, _size_vertices_model);
        hr = _pVertexBuffer_model->Unlock();
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_name);
    }
    //�f�o�C�X�ɃC���f�b�N�X�o�b�t�@�쐬
    if (_pIndexBuffer == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * _nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<_model_name);
        void* pDeviceMemory = 0;
        hr = _pIndexBuffer->Lock(0, 0, (void**)&pDeviceMemory,0);
        checkDxException(hr, D3D_OK, "�C���f�b�N�X�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
        memcpy(pDeviceMemory, _paIndexBuffer_data, sizeof(WORD)*_nFaces*3);
        hr = _pIndexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "�C���f�b�N�X�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_name);
    }
    //�f�o�C�X�Ƀe�N�X�`���쐬
    if (!_papTextureConnection) {
        _papTextureConnection = NEW GgafDxTextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (GgafDxTextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }
}

GgafDxMassBoardModel::~GgafDxMassBoardModel() {
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR(_paIndexBuffer_data);
}

