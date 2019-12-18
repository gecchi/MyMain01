#include "jp/ggaf/dx/model/RegularPolygonSpriteModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/RegularPolygonSpriteActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/RegularPolygonSpriteEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

DWORD RegularPolygonSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

RegularPolygonSpriteModel::RegularPolygonSpriteModel(const char* prm_model_name) : Model(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pVertexBuffer_data = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _angle_num = 3;
    _drawing_order = 0;
    _u_center = 0.5;
    _v_center = 0.5;

    // prm_model_name �ɂ� "8,XXXX" or "8,CW,XXXX" ���A�n���Ă���B
    // "8,CW,XXXX" : ��8�p�`�Ŏ��v���`��
    // "8,XXXX"    : ��8�p�`(�f�t�H���g�̔����v���`��)
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, ",");
    if (names.size() == 1) {
        throwCriticalException("���f��ID�ɏ�񂪑���܂���B[8,XXXX] or [8,CW,XXXX] �`���Ŏw�肵�ĉ������Bprm_model_name="<<prm_model_name);
    } else {
        _angle_num = STOI(names[0]);
        if (names.size() == 2) {
            _drawing_order = 0;
        } else if (names.size() == 3) {
            if (names[1] == "CW" ||  names[1] == "cw" || names[1] == "1") {
                //���v���`��
                _drawing_order = 1;
            } else {
                _drawing_order = 0;
            }
        }
    }
    _obj_model |= Obj_GgafDx_RegularPolygonSpriteModel;
}

HRESULT RegularPolygonSpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    _TRACE4_("RegularPolygonSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    //�Ώ�Actor
    const RegularPolygonSpriteActor* const pTargetActor = (RegularPolygonSpriteActor*)prm_pActor_target;
    //�Ώ�SpriteActor�̃G�t�F�N�g���b�p
    RegularPolygonSpriteEffect* const pSpriteEffect = (RegularPolygonSpriteEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pSpriteEffect->_pID3DXEffect;

    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(RegularPolygonSpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");

        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_u_center, _u_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_u_center) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_v_center, _v_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_v_center) �Ɏ��s���܂����B");
    }
    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name<<"("<<pSpriteEffect<<")");
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pSpriteEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, pTargetActor->_draw_fan_num);
    if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"�p�X�� BeginPass("<<pass<<") �Ɏ��s���܂����B");
            pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, pTargetActor->_draw_fan_num);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "�P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }

    //�O��`�惂�f���ێ�
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pSpriteEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void RegularPolygonSpriteModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    if (_pVertexBuffer_data == nullptr) {
        ModelManager* pModelManager = pGOD->_pModelManager;
        HRESULT hr;
        std::string model_name = std::string(_model_name); //_model_name �� "8,CW,XXXX" or "8,XXXX"
        std::vector<std::string> names = UTIL::split(model_name, ",");
        std::string filenamae = "";
        if (names.size() == 2) {
            filenamae = names[1];
        } else if (names.size() == 3) {
            filenamae = names[2];
        }
        std::string xfile_name = ModelManager::getSpriteFileName(filenamae, "sprx");
        ModelManager::SpriteXFileFmt xdata;
        pModelManager->obtainSpriteInfo(&xdata, xfile_name);
        _model_width_px = xdata.width;
        _model_height_px =  xdata.height;
        _row_texture_split = xdata.row_texture_split;
        _col_texture_split = xdata.col_texture_split;
        _pa_texture_filenames = NEW std::string[1];
        _pa_texture_filenames[0] = std::string(xdata.texture_file);
        _pVertexBuffer_data = NEW RegularPolygonSpriteModel::VERTEX[_angle_num+2];
        _size_vertices = sizeof(RegularPolygonSpriteModel::VERTEX)*(_angle_num+2);
        _size_vertex_unit = sizeof(RegularPolygonSpriteModel::VERTEX);
        dxcoord model_width = PX_DX(_model_width_px);
        dxcoord model_height = PX_DX(_model_height_px);
        float tu_rate = 1.0 / _col_texture_split;
        float tv_rate = 1.0 / _row_texture_split;
        _u_center = tu_rate * 0.5;
        _v_center = tv_rate * 0.5;
        //���S
        _pVertexBuffer_data[0].x = 0.0f;
        _pVertexBuffer_data[0].y = 0.0f;
        _pVertexBuffer_data[0].z = 0.0f;
        _pVertexBuffer_data[0].nx = 0.0f;
        _pVertexBuffer_data[0].ny = 0.0f;
        _pVertexBuffer_data[0].nz = 1.0f;
        _pVertexBuffer_data[0].color = D3DCOLOR_ARGB(255,255,255,255);
        _pVertexBuffer_data[0].tu = _u_center;
        _pVertexBuffer_data[0].tv = _v_center;

        if (_drawing_order == 0) {        //���v���
            for (int ang = 0; ang < _angle_num; ang++) {
                double rad = (PI2 * ang) / _angle_num;
                _pVertexBuffer_data[ang+1].x = (float)(cos(rad) * model_width * 0.5);
                _pVertexBuffer_data[ang+1].y = (float)(sin(rad) * model_height * 0.5);
                _pVertexBuffer_data[ang+1].z = 0.0f;
                _pVertexBuffer_data[ang+1].nx = 0.0f;
                _pVertexBuffer_data[ang+1].ny = 0.0f;
                _pVertexBuffer_data[ang+1].nz = 1.0f;
                _pVertexBuffer_data[ang+1].color = D3DCOLOR_ARGB(255,255,255,255);
                _pVertexBuffer_data[ang+1].tu = _pVertexBuffer_data[0].tu + (cos(rad) * tu_rate * 0.5);
                _pVertexBuffer_data[ang+1].tv = _pVertexBuffer_data[0].tv - (sin(rad) * tv_rate * 0.5);
            }
            _pVertexBuffer_data[_angle_num+1] = _pVertexBuffer_data[1];
        } else {
            //���v���
            for (int ang = 0; ang < _angle_num; ang++) {
                double rad = PI2 - ((PI2 * ang) / _angle_num);
                _pVertexBuffer_data[ang+1].x = (float)(cos(rad) * model_width * 0.5);
                _pVertexBuffer_data[ang+1].y = (float)(sin(rad) * model_height * 0.5);
                _pVertexBuffer_data[ang+1].z = 0.0f;
                _pVertexBuffer_data[ang+1].nx = 0.0f;
                _pVertexBuffer_data[ang+1].ny = 0.0f;
                _pVertexBuffer_data[ang+1].nz = 1.0f;
                _pVertexBuffer_data[ang+1].color = D3DCOLOR_ARGB(255,255,255,255);
                _pVertexBuffer_data[ang+1].tu = _pVertexBuffer_data[0].tu + (cos(rad) * tu_rate * 0.5);
                _pVertexBuffer_data[ang+1].tv = _pVertexBuffer_data[0].tv - (sin(rad) * tv_rate * 0.5);
            }
            _pVertexBuffer_data[_angle_num+1] = _pVertexBuffer_data[1];
        }

        //����
        _bounding_sphere_radius = _pVertexBuffer_data[1].x;

        _num_materials = 1;
        D3DMATERIAL9* paMaterial;
        paMaterial = NEW D3DMATERIAL9[_num_materials];
        for ( DWORD i = 0; i < _num_materials; i++) {
            //paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
            paMaterial[i].Diffuse.r = 1.0f;
            paMaterial[i].Diffuse.g = 1.0f;
            paMaterial[i].Diffuse.b = 1.0f;
            paMaterial[i].Diffuse.a = 1.0f;
            paMaterial[i].Ambient.r = 1.0f;
            paMaterial[i].Ambient.g = 1.0f;
            paMaterial[i].Ambient.b = 1.0f;
            paMaterial[i].Ambient.a = 1.0f;
        }
        _paMaterial_default = paMaterial;
    }
    //�o�b�t�@�쐬
    if (_pVertexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                RegularPolygonSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);

        memcpy(pVertexBuffer, _pVertexBuffer_data, _size_vertices); //pVertexBuffer �� _pVertexBuffer_data
        _pVertexBuffer->Unlock();
    }

    if (_papTextureConnection == nullptr) {
        //�e�N�X�`���擾�����f���ɕێ�������
        ModelManager* pModelManager = pGOD->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }

    _TRACE3_("_model_name=" << _model_name << " end");
}

void RegularPolygonSpriteModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void RegularPolygonSpriteModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    _TRACE3_("_model_name=" << _model_name << " end");
}

RegularPolygonSpriteModel::~RegularPolygonSpriteModel() {
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_DELETEARR(_pVertexBuffer_data);
}

