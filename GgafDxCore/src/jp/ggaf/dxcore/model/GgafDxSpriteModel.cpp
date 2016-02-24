#include "jp/ggaf/dxcore/model/GgafDxSpriteModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxSpriteActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDxSpriteModel::GgafDxSpriteModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxSpriteModel::GgafDxSpriteModel(" << _model_name << ")");

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxSpriteModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreSpriteModel(GgafDxSpriteModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDxSpriteModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    _TRACE4_("GgafDxSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    //�Ώ�Actor
    const GgafDxSpriteActor* const pTargetActor = (GgafDxSpriteActor*)prm_pActor_target;
    //�Ώ�SpriteActor�̃G�t�F�N�g���b�p
    GgafDxSpriteEffect* const pSpriteEffect = (GgafDxSpriteEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pSpriteEffect->_pID3DXEffect;

    //����`���UV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxSpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxSpriteActor::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxSpriteActor::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_h_offset_u) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() SetFloat(_h_offset_v) �Ɏ��s���܂����B");
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pSpriteEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
            _TRACE4_("GgafDxSpriteModel::draw() EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteActor::draw() EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxSpriteActor::draw() End() �Ɏ��s���܂����B");
            if (pEffect_active->_obj_effect & Obj_GgafDxMassMeshEffect) {
                pDevice->SetStreamSourceFreq( 0, 1 );
                pDevice->SetStreamSourceFreq( 1, 1 );
            }
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("GgafDxSpriteModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxSpriteActor::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("GgafDxSpriteModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name<<"("<<pSpriteEffect<<")");
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxSpriteActor::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteActor::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pSpriteEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() �P�p�X�� EndPass() �Ɏ��s���܂����B");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() "<<pass+1<<"�p�X�� BeginPass("<<pass<<") �Ɏ��s���܂����B");
            pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() "<<pass+1<<"�p�X�� EndPass() �Ɏ��s���܂����B");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteModel::draw() �P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }

    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pSpriteEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_drawing++;
    return D3D_OK;
}

void GgafDxSpriteModel::restore() {
    _TRACE3_("GgafDxSpriteModel::restore() " << _model_name << " start");
    _papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name = GgafDxModelManager::getSpriteFileName(_model_name);
    GgafDxModelManager::SpriteXFileFmt xdata;
    GgafDxModelManager::obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px = xdata.width;
    _model_height_px =  xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(xdata.texture_file, this));

    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    _papTextureConnection = NEW GgafDxTextureConnection*[1];
    _papTextureConnection[0] = model_pTextureConnection;

    GgafDxSpriteModel::VERTEX* paVertex = NEW GgafDxSpriteModel::VERTEX[4];
    _size_vertices = sizeof(GgafDxSpriteModel::VERTEX)*4;
    _size_vertex_unit = sizeof(GgafDxSpriteModel::VERTEX);

    //���_�z��������f���ɕێ�������
    //UV�͍���̂P���i�A�j���p�^�[���O�j���f�t�H���g�Őݒ肷��B
    //�V�F�[�_�[���`�掞�ɃA�j���p�^�[���ԍ����݂�UV���W�����炷�d�l�Ƃ�����ƁB
    //x,y �� ��2 �Ƃ́A���f�����S�����[�J�����W�̌��_���S�Ƃ���������
    float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
    float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
    double du = 1.0 / tex_width  / 100000.0; //�e�N�X�`���̕�1px��10000����1px
    double dv = 1.0 / tex_height / 100000.0; //�e�N�X�`���̍���1px��10000����1px
    double rev = 1.0;//0.99609308; //99609309�Ŋ���
    //����
    paVertex[0].x = (PX_DX(xdata.width)  / -2.0)*rev;
    paVertex[0].y = (PX_DX(xdata.height) /  2.0)*rev;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[0].tu = du;
    paVertex[0].tv = dv;
    //�E��
    paVertex[1].x = (PX_DX(xdata.width)  /  2.0)*rev;
    paVertex[1].y = (PX_DX(xdata.height) /  2.0)*rev;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[1].tu = (1.0 / xdata.col_texture_split) - du;
    paVertex[1].tv = dv;
    //����
    paVertex[2].x = (PX_DX(xdata.width)  / -2.0)*rev;
    paVertex[2].y = (PX_DX(xdata.height) / -2.0)*rev;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[2].tu = du;
    paVertex[2].tv = (1.0 / xdata.row_texture_split) - dv;

    //�E��
    paVertex[3].x = (PX_DX(xdata.width)  / 2.0 )*rev;
    paVertex[3].y = (PX_DX(xdata.height) / -2.0)*rev;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[3].tu = (1.0 / xdata.col_texture_split) - du;
    paVertex[3].tv = (1.0 / xdata.row_texture_split) - dv;

    //����
    FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(paVertex[0].x * paVertex[0].x +
                                                      paVertex[0].y * paVertex[0].y +
                                                      paVertex[0].z * paVertex[0].z));
    _bounding_sphere_radius = model_bounding_sphere_radius;


    //�o�b�t�@�쐬
    if (_pVertexBuffer == nullptr) {

        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreSpriteModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);

    memcpy(pVertexBuffer, paVertex, _size_vertices); //pVertexBuffer �� paVertex
    _pVertexBuffer->Unlock();

    _num_materials = 1;
    D3DMATERIAL9* paMaterial;
    paMaterial = NEW D3DMATERIAL9[_num_materials];
    for( DWORD i = 0; i < _num_materials; i++){
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
    //��n��
    GGAF_DELETEARR(paVertex);
    _TRACE3_("GgafDxSpriteModel::restore() " << _model_name << " end");
}

void GgafDxSpriteModel::onDeviceLost() {
    _TRACE3_("GgafDxSpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxSpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxSpriteModel::release() {
    _TRACE3_("GgafDxSpriteModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR(_pa_texture_filenames);
    _TRACE3_("GgafDxSpriteModel::release() " << _model_name << " end");
}

GgafDxSpriteModel::~GgafDxSpriteModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

