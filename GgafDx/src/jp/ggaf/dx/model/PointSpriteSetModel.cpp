#include "jp/ggaf/dx/model/PointSpriteSetModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/PointSpriteSetActor.h"
#include "jp/ggaf/dx/effect/PointSpriteSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

#define POINTSPRITESETMODEL_MAX_DARW_SET_NUM 15

using namespace GgafDx;

DWORD PointSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer = nullptr;

PointSpriteSetModel::PointSpriteSetModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_PointSpriteSetModel;
    _paVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
    _size_vertices = 0;
    _size_vertex_unit= 0;
    _nVertices = 0;
    _max_draw_set_num = POINTSPRITESETMODEL_MAX_DARW_SET_NUM;
}

HRESULT PointSpriteSetModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("PointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        _TRACE_(FUNC_NAME<<" "<<_model_id<<" �̕`��Z�b�g���I�[�o�[�B_draw_set_num="<<_draw_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* pDevice = pCARETAKER->_pID3DDevice9;
    //�ΏۃA�N�^�[
    const PointSpriteSetActor* pTargetActor = (PointSpriteSetActor*)prm_pActor_target;
    //�Ώ�PointSpriteSetActor�̃G�t�F�N�g���b�p
    PointSpriteSetEffect* pPointSpriteSetEffect = (PointSpriteSetEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pPointSpriteSetEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������ł��A�Z�b�g���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetStreamSource(0, _paVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(PointSpriteSetModel::FVF);
        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("PointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            hr = pDevice->SetTexture(0, nullptr);
        }
        pDevice->SetIndices(nullptr);

        hr = pID3DXEffect->SetFloat(pPointSpriteSetEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetInt(pPointSpriteSetEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pPointSpriteSetEffect->_hInvTextureSplitRowcol, _inv_texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hInvTextureSplitRowcol) �Ɏ��s���܂����B");
    }

    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteSetEffect->_effect_name<<"("<<pPointSpriteSetEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pPointSpriteSetEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteSetEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pPointSpriteSetEffect->_effect_name);
    hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices*prm_draw_set_num);
    checkDxException(hr, D3D_OK, " pass=1 �Ɏ��s���܂����B");
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pPointSpriteSetEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void PointSpriteSetModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        std::string psprx_filepath = Model::getPointSpriteXFilePath(xdata.XFileNames[0]);
        ModelManager::PointSpriteXFileFmt xdata_pspr;
        pModelManager->obtainPointSpriteModelInfo(&xdata_pspr, psprx_filepath);
        //�}�e���A����`���P�������̂ŁA�`��̂��߂ɖ������P�}�e���A�����쐬�B
//        _num_materials = 1; ////setMaterial();�Ŏ��s�ς�
        setMaterial();
//        _pa_texture_filenames = NEW std::string[1]; ////setMaterial();�Ŏ��s�ς�
        _pa_texture_filenames[0] = std::string(xdata_pspr.TextureFile);
        //�f�o�C�X�Ƀe�N�X�`���쐬 (���ɂ��������������邪�A���̓f�o�C�X���X�g�����s)
        //���_�o�b�t�@��psize�̎Z�o�ɁA�e�N�X�`���̒������K�v�Ȃ��߁A�����ň�U���߂Ă���
        if (_papTextureConnection == nullptr) {
            _papTextureConnection = NEW TextureConnection*[1];
            _papTextureConnection[0] =
                (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
        }

        Texture* pTex = _papTextureConnection[0]->peek();
        float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
        float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)���Ɠ����ɂȂ�
        if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
            throwCriticalException("�|�C���g�X�v���C�g�p�e�N�X�`��["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")�́A�����`�ł���K�v������܂��B");
        }
        _texture_size_px = tex_width;
        _square_size_px = xdata_pspr.SquareSize;
        _texture_split_rowcol = xdata_pspr.TextureSplitRowCol;
        _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
        _nVertices = xdata_pspr.VerticesNum;
        _draw_set_num = xdata_pspr.DrawSetNum;
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("PointSpriteSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���́A�ő�� "<<_max_draw_set_num<<" �ɍĒ�`����܂����B���R�F_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("PointSpriteSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���� "<<_draw_set_num<<" �ł��B");
        }

//        if (_nVertices*_draw_set_num > 65535) {
//            throwCriticalException("PointSpriteSetModel::restore() ���_�C���f�b�N�X�� 65535 �𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  _nVertices*_draw_set_num:"<<_nVertices*_draw_set_num);
//        }
//        _nFaces = 0; //_nFaces�͎g�p���Ȃ�
        _paVtxBuffer_data = NEW PointSpriteSetModel::VERTEX[_nVertices*_draw_set_num];
        _size_vertex_unit = sizeof(PointSpriteSetModel::VERTEX);
        _size_vertices = sizeof(PointSpriteSetModel::VERTEX) * _nVertices*_draw_set_num;

        for (UINT i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data[i].x = xdata_pspr.paD3DVECTOR_Vertices[i].x;
            _paVtxBuffer_data[i].y = xdata_pspr.paD3DVECTOR_Vertices[i].y;
            _paVtxBuffer_data[i].z = xdata_pspr.paD3DVECTOR_Vertices[i].z;

            _paVtxBuffer_data[i].psize = (_square_size_px*_texture_split_rowcol / _texture_size_px) * xdata_pspr.paFLOAT_InitScale[i]; //PSIZE�ɂ̓s�N�Z���T�C�Y�ł͂Ȃ��{���𖄂ߍ��ށB
            //�V�F�[�_�[�Ŋg��k���s�N�Z�����v�Z
            _paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(xdata_pspr.paD3DVECTOR_VertexColors[i].r,
                                                             xdata_pspr.paD3DVECTOR_VertexColors[i].g,
                                                             xdata_pspr.paD3DVECTOR_VertexColors[i].b,
                                                             xdata_pspr.paD3DVECTOR_VertexColors[i].a );
            _paVtxBuffer_data[i].ini_ptn_no = (float)(xdata_pspr.paInt_InitUvPtnNo[i]); //���_�X�v���C�g��UV�p�^�[���ԍ�
            _paVtxBuffer_data[i].index = 0; //���_�ԍ��i�ނ��薄�ߍ��݁j
        }
        transformPosVtx(_paVtxBuffer_data, _size_vertex_unit, _nVertices);

        //����
        FLOAT model_bounding_sphere_radius;
        for (UINT i = 0; i < _nVertices; i++) {
            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data[i].x * _paVtxBuffer_data[i].x +
                                                        _paVtxBuffer_data[i].y * _paVtxBuffer_data[i].y +
                                                        _paVtxBuffer_data[i].z * _paVtxBuffer_data[i].z  )
                                                   + (((_square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                                                 );
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }
        //set���J��Ԃ��}��
        for (int n = 1; n < _draw_set_num; n++) {
            int os = n*_nVertices;
            for (UINT i = 0; i < _nVertices; i++) {
                _paVtxBuffer_data[os+i].x = _paVtxBuffer_data[i].x;
                _paVtxBuffer_data[os+i].y = _paVtxBuffer_data[i].y;
                _paVtxBuffer_data[os+i].z = _paVtxBuffer_data[i].z;
                _paVtxBuffer_data[os+i].psize = _paVtxBuffer_data[i].psize;
                _paVtxBuffer_data[os+i].color = _paVtxBuffer_data[i].color;
                _paVtxBuffer_data[os+i].ini_ptn_no = _paVtxBuffer_data[i].ini_ptn_no;
                _paVtxBuffer_data[os+i].index = n; //���_�ԍ��i�ނ��薄�ߍ��݁j
            }
        }

        transformPosVtx(_paVtxBuffer_data, _size_vertex_unit, _nVertices*_draw_set_num);

    }

    //�f�o�C�X�ɒ��_�o�b�t�@�쐬(���f��)
    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //���_�o�b�t�@�쐬
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS,
                PointSpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_id));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void* pDeviceMemory = 0;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);
        memcpy(pDeviceMemory, _paVtxBuffer_data, _size_vertices);
        hr = _paVertexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_id);
    }

    //�f�o�C�X�Ƀe�N�X�`���쐬
    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] =
            (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }

//    //�C���f�b�N�X�o�b�t�@�͎g��Ȃ�
//    _paIndexBuffer = nullptr;

    _TRACE3_("_model_id=" << _model_id << " end");
}

void PointSpriteSetModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void PointSpriteSetModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");

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
    GGAF_RELEASE(_paVertexBuffer);
    _TRACE3_("_model_id=" << _model_id << " end");

}
PointSpriteSetModel::~PointSpriteSetModel() {
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
}

