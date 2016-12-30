#include "jp/ggaf/dxcore/model/GgafDxPointSpriteSetModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteSetActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteSetEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxPointSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxPointSpriteSetModel::GgafDxPointSpriteSetModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _set_num = 0;
    _pVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _size_vertex_unit= 0;
    _nVertices = 0;
    _obj_model |= Obj_GgafDxPointSpriteSetModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̃����o�[��������
    //void GgafDxModelManager::restorePointSpriteSetModel(GgafDxPointSpriteSetModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _TRACE_("GgafDxPointSpriteSetModel::GgafDxPointSpriteSetModel(" << _model_name << ") End");
}

//�`��
HRESULT GgafDxPointSpriteSetModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxPointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_(FUNC_NAME<<" "<<_model_name<<" �̕`��Z�b�g���I�[�o�[�B_set_num="<<_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //�ΏۃA�N�^�[
    const GgafDxPointSpriteSetActor* pTargetActor = (GgafDxPointSpriteSetActor*)prm_pActor_target;
    //�Ώ�PointSpriteSetActor�̃G�t�F�N�g���b�p
    GgafDxPointSpriteSetEffect* pPointSpriteSetEffect = (GgafDxPointSpriteSetEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pPointSpriteSetEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������ł��A�Z�b�g���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxPointSpriteSetModel::FVF);
        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxPointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            hr = pDevice->SetTexture(0, nullptr);
        }
        pDevice->SetIndices(nullptr);

        hr = pID3DXEffect->SetFloat(pPointSpriteSetEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetInt(pPointSpriteSetEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) �Ɏ��s���܂����B");
    }

    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteSetEffect->_effect_name<<"("<<pPointSpriteSetEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pPointSpriteSetEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteSetEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteSetEffect->_effect_name);
    hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices*prm_draw_set_num);
    checkDxException(hr, D3D_OK, " pass=1 �Ɏ��s���܂����B");
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif

    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pPointSpriteSetEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxPointSpriteSetModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    HRESULT hr;
    if (!_paVtxBuffer_data) {

        //�ÓI�ȏ��ݒ�
        std::vector<std::string> names = UTIL::split(std::string(_model_name), "/");
        std::string xfile_name = ""; //�ǂݍ���X�t�@�C����
        if (names.size() == 1) {
            _TRACE_(FUNC_NAME<<" "<<_model_name<<" �̍ő哯���`��I�u�W�F�N�g���́A�f�t�H���g��15���ݒ肳��܂����B");
            _set_num = 15;
            xfile_name = GgafDxModelManager::getPointSpriteFileName(names[0]);
        } else if (names.size() == 2) {
            _set_num = STOI(names[0]);
            xfile_name = GgafDxModelManager::getPointSpriteFileName(names[1]);
        } else {
            throwGgafCriticalException("_model_name �ɂ� \"xxxxxx\" or \"8/xxxxx\" �`�����w�肵�Ă��������B \n"<<
                    "���ۂ́A_model_name="<<_model_name<<" �ł����B");
        }
//        if (_set_num < 1 || _set_num > GGAFDXMASS_MAX_INSTANCE_NUM) {
//            throwGgafCriticalException(_model_name<<"�̍ő哯���`��I�u�W�F�N�g�����s���B�͈͂� 1�`"<<GGAFDXMASS_MAX_INSTANCE_NUM<<"�Z�b�g�ł��B_set_num="<<_set_num);
//        }
//        if (xfile_name == "") {
//            throwGgafCriticalException("�|�C���g�X�v���C�g��`�t�@�C��(*.psprx)��������܂���Bmodel_name="<<(_model_name));
//        }
        GgafDxModelManager::PointSpriteXFileFmt xdata;
        GgafDxModelManager::obtainPointSpriteInfo(&xdata, xfile_name);

        //�}�e���A����`���P�������̂ŁA�`��̂��߂ɖ������P�}�e���A�����쐬�B
        setMaterial();
        _pa_texture_filenames[0] = std::string(xdata.TextureFile);

        //�f�o�C�X�Ƀe�N�X�`���쐬 (���ɂ��������������邪�A���̓f�o�C�X���X�g�����s)
        //���_�o�b�t�@��psize�̎Z�o�ɁA�e�N�X�`���̒������K�v�Ȃ��߁A�����ň�U���߂Ă���
        if (!_papTextureConnection) {
            _papTextureConnection = NEW GgafDxTextureConnection*[1];
            _papTextureConnection[0] =
                (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
            GgafDxTexture* pTex = _papTextureConnection[0]->peek();
            float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
            float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)���Ɠ����ɂȂ�
            if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
                throwGgafCriticalException("�|�C���g�X�v���C�g�p�e�N�X�`��["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")�́A�����`�ł���K�v������܂��B");
            }
            _texture_size_px = tex_width;
        }
        _square_size_px = xdata.SquareSize;
        _texture_split_rowcol = xdata.TextureSplitRowCol;

        _nVertices = xdata.VerticesNum;
        if (_nVertices*_set_num > 65535) {
            throwGgafCriticalException("���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  _nVertices*_set_num:"<<_nVertices*_set_num);
        }
//        _nFaces = 0; //_nFaces�͎g�p���Ȃ�
        _paVtxBuffer_data = NEW GgafDxPointSpriteSetModel::VERTEX[_nVertices*_set_num];
        _size_vertex_unit = sizeof(GgafDxPointSpriteSetModel::VERTEX);
        _size_vertices = sizeof(GgafDxPointSpriteSetModel::VERTEX) * _nVertices*_set_num;

        FLOAT model_bounding_sphere_radius;


        for (int i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data[i].x = xdata.paD3DVECTOR_Vertices[i].x;
            _paVtxBuffer_data[i].y = xdata.paD3DVECTOR_Vertices[i].y;
            _paVtxBuffer_data[i].z = xdata.paD3DVECTOR_Vertices[i].z;

            _paVtxBuffer_data[i].psize = (_square_size_px*_texture_split_rowcol / _texture_size_px) * xdata.paFLOAT_InitScale[i]; //PSIZE�ɂ̓s�N�Z���T�C�Y�ł͂Ȃ��{���𖄂ߍ��ށB
            //�V�F�[�_�[�Ŋg��k���s�N�Z�����v�Z
            _paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(xdata.paD3DVECTOR_VertexColors[i].r,
                                                                   xdata.paD3DVECTOR_VertexColors[i].g,
                                                                   xdata.paD3DVECTOR_VertexColors[i].b,
                                                                   xdata.paD3DVECTOR_VertexColors[i].a );
            _paVtxBuffer_data[i].ini_ptn_no = (float)(xdata.paInt_InitUvPtnNo[i]); //���_�X�v���C�g��UV�p�^�[���ԍ�
            _paVtxBuffer_data[i].index = 0; //���_�ԍ��i�ނ��薄�ߍ��݁j

            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data[i].x * _paVtxBuffer_data[i].x +
                                                        _paVtxBuffer_data[i].y * _paVtxBuffer_data[i].y +
                                                        _paVtxBuffer_data[i].z * _paVtxBuffer_data[i].z  )
                                                   + (((_square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                                                 );

            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        for (int n = 1; n < _set_num; n++) {
            int os = n*_nVertices;
            for (int i = 0; i < _nVertices; i++) {
                _paVtxBuffer_data[os+i].x = _paVtxBuffer_data[i].x;
                _paVtxBuffer_data[os+i].y = _paVtxBuffer_data[i].y;
                _paVtxBuffer_data[os+i].z = _paVtxBuffer_data[i].z;
                _paVtxBuffer_data[os+i].psize = _paVtxBuffer_data[i].psize;
                _paVtxBuffer_data[os+i].color = _paVtxBuffer_data[i].color;
                _paVtxBuffer_data[os+i].ini_ptn_no = _paVtxBuffer_data[i].ini_ptn_no;
                _paVtxBuffer_data[os+i].index = n; //���_�ԍ��i�ނ��薄�ߍ��݁j
            }
        }

    }

    //�f�o�C�X�ɒ��_�o�b�t�@�쐬(���f��)
    if (_pVertexBuffer == nullptr) {

        //���_�o�b�t�@�쐬
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS,
                GgafDxPointSpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void* pDeviceMemory = 0;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
        memcpy(pDeviceMemory, _paVtxBuffer_data, _size_vertices);
        hr = _pVertexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃A�����b�N�擾�Ɏ��s model="<<_model_name);
    }

    //�f�o�C�X�Ƀe�N�X�`���쐬
    if (!_papTextureConnection) {
        _num_materials = 1;
        _papTextureConnection = NEW GgafDxTextureConnection*[1];
        _papTextureConnection[0] =
            (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
        GgafDxTexture* pTex = _papTextureConnection[0]->peek();
        float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
        float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)���Ɠ����ɂȂ�
        if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
            throwGgafCriticalException("�|�C���g�X�v���C�g�p�e�N�X�`��["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")�́A�����`�ł���K�v������܂��B");
        }
        _texture_size_px = tex_width;
    }

//    //�C���f�b�N�X�o�b�t�@�͎g��Ȃ�
//    _pIndexBuffer = nullptr;

    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxPointSpriteSetModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxPointSpriteSetModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");

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
    GGAF_DELETEARR(_paVtxBuffer_data);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");

}
GgafDxPointSpriteSetModel::~GgafDxPointSpriteSetModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

