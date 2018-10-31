#include "jp/ggaf/dxcore/model/GgafDxRegularPolygonBoardModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/actor/GgafDxRegularPolygonBoardActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxRegularPolygonBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxRegularPolygonBoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

GgafDxRegularPolygonBoardModel::GgafDxRegularPolygonBoardModel(const char* prm_model_name) :
    GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _angle_num = 3;
    _drawing_order = 0;
    _x_center = 16;
    _y_center = 16;
    _u_center = 0.5;
    _v_center = 0.5;
    // prm_model_name �ɂ� "8,XXXX" or "8,CW,XXXX" ���A�n���Ă���B
    // "8,CW,XXXX" : ��8�p�`�Ŏ��v���`��
    // "8,XXXX"    : ��8�p�`(�f�t�H���g�̔����v���`��)
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, ",");
    if (names.size() == 1) {
        throwGgafCriticalException("���f��ID�ɏ�񂪑���܂���B[8,XXXX] or [8,CW,XXXX] �`���Ŏw�肵�ĉ������Bprm_model_name="<<prm_model_name);
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
    _obj_model |= Obj_GgafDxRegularPolygonBoardModel;
}

HRESULT GgafDxRegularPolygonBoardModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxRegularPolygonBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�Ώ�Actor
    const GgafDxRegularPolygonBoardActor* const pTargetActor = (GgafDxRegularPolygonBoardActor*)prm_pActor_target;
    //�Ώ�RegularPolygonBoardActor�̃G�t�F�N�g���b�p
    GgafDxRegularPolygonBoardEffect* const pRegularPolygonBoardEffect = (GgafDxRegularPolygonBoardEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pRegularPolygonBoardEffect->_pID3DXEffect;
    //����`���UV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxRegularPolygonBoardModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_x_center, _x_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_x_center) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_y_center, _y_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_y_center) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_u_center, _u_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_u_center) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_v_center, _v_center);
        checkDxException(hr, D3D_OK, "SetFloat(_h_v_center) �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pRegularPolygonBoardEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) �Ɏ��s���܂����B");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pRegularPolygonBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pRegularPolygonBoardEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pRegularPolygonBoardEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pRegularPolygonBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pRegularPolygonBoardEffect->_effect_name<<"("<<pRegularPolygonBoardEffect<<")");
    pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, pTargetActor->_draw_fan_num);
    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pRegularPolygonBoardEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif

    return D3D_OK;
}

void GgafDxRegularPolygonBoardModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    HRESULT hr;
    std::string model_name = std::string(_model_name); //_model_name �� "8,CW,XXXX" or "8,XXXX"
    std::vector<std::string> names = UTIL::split(model_name, ",");
    std::string filenamae = "";
    if (names.size() == 2) {
        filenamae = names[1];
    } else if (names.size() == 3) {
        filenamae = names[2];
    }

    GgafDxModelManager* pModelManager = pGOD->_pModelManager;
    std::string xfile_name = GgafDxModelManager::getSpriteFileName(filenamae, "sprx");
    GgafDxModelManager::SpriteXFileFmt xdata;
    pModelManager->obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px  = xdata.width;
    _model_height_px = xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    _papTextureConnection = NEW GgafDxTextureConnection*[1];
    _papTextureConnection[0] = (GgafDxTextureConnection*)(pModelManager->_pModelTextureManager->connect(xdata.texture_file, this));

    GgafDxRegularPolygonBoardModel::VERTEX* paVertex = NEW GgafDxRegularPolygonBoardModel::VERTEX[_angle_num+2];
    _size_vertices = sizeof(GgafDxRegularPolygonBoardModel::VERTEX)*(_angle_num+2);
    _size_vertex_unit = sizeof(GgafDxRegularPolygonBoardModel::VERTEX);
    float model_width = _model_width_px;
    float model_height = _model_height_px;
    float tu_rate = 1.0 / _col_texture_split;
    float tv_rate = 1.0 / _row_texture_split;
    _u_center = tu_rate * 0.5;
    _v_center = tv_rate * 0.5;
    _x_center =  model_width * 0.5;
    _y_center =  model_height * 0.5;
    //���S
    paVertex[0].x = _x_center;
    paVertex[0].y = _y_center;
    paVertex[0].z = 0.0f;
    paVertex[0].tu = _u_center;
    paVertex[0].tv = _v_center;

    if (_drawing_order == 0) {        //���v���
        for (int ang = 0; ang < _angle_num; ang++) {
            double rad = (PI2 * ang) / _angle_num;
            paVertex[ang+1].x = paVertex[0].x + (cos(rad) * model_width  * 0.5);
            paVertex[ang+1].y = paVertex[0].y - (sin(rad) * model_height * 0.5);
            paVertex[ang+1].z = 0.0f;
            paVertex[ang+1].tu = paVertex[0].tu + (cos(rad) * tu_rate * 0.5);
            paVertex[ang+1].tv = paVertex[0].tv - (sin(rad) * tv_rate * 0.5);
        }
        paVertex[_angle_num+1] = paVertex[1];
    } else {
        //���v���
        for (int ang = 0; ang < _angle_num; ang++) {
            double rad = PI2 - ((PI2 * ang) / _angle_num);
            paVertex[ang+1].x = paVertex[0].x + (cos(rad) * model_width  * 0.5);
            paVertex[ang+1].y = paVertex[0].y - (sin(rad) * model_height * 0.5);
            paVertex[ang+1].z = 0.0f;
            paVertex[ang+1].tu = paVertex[0].tu + (cos(rad) * tu_rate * 0.5);
            paVertex[ang+1].tv = paVertex[0].tv - (sin(rad) * tv_rate * 0.5);
        }
        paVertex[_angle_num+1] = paVertex[1];
    }

//    GgafDxRegularPolygonBoardModel::VERTEX* paVertex = NEW GgafDxRegularPolygonBoardModel::VERTEX[_angle_num+2];
//    _size_vertices = sizeof(GgafDxRegularPolygonBoardModel::VERTEX)*(_angle_num+2);
//    _size_vertex_unit = sizeof(GgafDxRegularPolygonBoardModel::VERTEX);
//
//    double du = 0.0;
//    double dv = 0.0;
//
//    //����
//    paVertex[0].x = 0.0f;
//    paVertex[0].y = 0.0f;
//    paVertex[0].z = 0.0f;
//    paVertex[0].tu = (float)du;
//    paVertex[0].tv = (float)dv;
//    //�E��
//    paVertex[1].x = xdata.width;
//    paVertex[1].y = 0.0f;
//    paVertex[1].z = 0.0f;
//    paVertex[1].tu = (float)((1.0 / xdata.col_texture_split) - du);
//    paVertex[1].tv = (float)dv;
//    //����
//    paVertex[2].x = 0.0f;
//    paVertex[2].y = xdata.height;
//    paVertex[2].z = 0.0f;
//    paVertex[2].tu = (float)du;
//    paVertex[2].tv = (float)((1.0 / xdata.row_texture_split) - dv);
//    //�E��
//    paVertex[3].x = xdata.width;
//    paVertex[3].y = xdata.height;
//    paVertex[3].z = 0.0f;
//    paVertex[3].tu = (float)((1.0 / xdata.col_texture_split) - du);
//    paVertex[3].tv = (float)((1.0 / xdata.row_texture_split) - dv);

    //�o�b�t�@�쐬
    if (_pVertexBuffer == nullptr) {

        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxRegularPolygonBoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);

    memcpy(pVertexBuffer, paVertex, _size_vertices); //pVertexBuffer �� paVertex
    _pVertexBuffer->Unlock();
    _num_materials = 1;
    D3DMATERIAL9* paMaterial;
    paMaterial = NEW D3DMATERIAL9[_num_materials];
    for ( DWORD i = 0; i < _num_materials; i++) {
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

    GGAF_DELETEARR(paVertex);
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxRegularPolygonBoardModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxRegularPolygonBoardModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

GgafDxRegularPolygonBoardModel::~GgafDxRegularPolygonBoardModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}
