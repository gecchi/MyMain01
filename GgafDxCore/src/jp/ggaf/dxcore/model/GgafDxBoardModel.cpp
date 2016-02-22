#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxBoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

GgafDxBoardModel::GgafDxBoardModel(const char* prm_model_name) :
    GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxBoardModel::GgafDxBoardModel(" << _model_name << ")");
    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxBoardModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreBoardModel(GgafDxBoardModel*)
    //�ōs���Ă���B
}

HRESULT GgafDxBoardModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�Ώ�Actor
    const GgafDxBoardActor* const pTargetActor = (GgafDxBoardActor*)prm_pActor_target;
    //�Ώ�BoardActor�̃G�t�F�N�g���b�p
    GgafDxBoardEffect* const pBoardEffect = (GgafDxBoardEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pBoardEffect->_pID3DXEffect;
    //����`���UV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxBoardModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->SetFloat(pBoardEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_offset_u) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_offset_v) �Ɏ��s���܂����B");
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pBoardEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
            _TRACE4_("GgafDxBoardModel::draw() EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() End() �Ɏ��s���܂����B");
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
        _TRACE4_("GgafDxBoardModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxBoardModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("GgafDxBoardModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pBoardEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name<<"("<<pBoardEffect<<")");
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pBoardEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_drawing++;
    return D3D_OK;
}

void GgafDxBoardModel::restore() {
    _TRACE3_("GgafDxBoardModel::restore() " << _model_name << " start");
    _papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name = GgafDxModelManager::getSpriteFileName(_model_name);

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData;
    hr = GgafDxGod::_pModelManager->_pID3DXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "[GgafDxModelManager::restoreBoardModel] '"<<xfile_name<<"' ��CreateEnumObject�Ɏ��s���܂����B�t�@�C���̑��݂��m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for(SIZE_T childCount = 0; childCount < nChildren; ++childCount) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }

    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException("[GgafDxModelManager::restoreBoardModel] "<<xfile_name<<" �̃t�H�[�}�b�g�G���[�B");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    SpriteXFileFmt xdata;
    pXData = obtainSpriteFmtX(&xdata, pXData);
    _model_width_px  = xdata.width;
    _model_height_px = xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)(GgafDxGod::_pModelManager->_pModelTextureManager->connect(xdata.texture_file, this));
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    _papTextureConnection = NEW GgafDxTextureConnection*[1];
    _papTextureConnection[0] = model_pTextureConnection;

    GgafDxBoardModel::VERTEX* paVertex = NEW GgafDxBoardModel::VERTEX[4];
    _size_vertices = sizeof(GgafDxBoardModel::VERTEX)*4;
    _size_vertex_unit = sizeof(GgafDxBoardModel::VERTEX);

    //1px�������uv�̑傫�������߂�
//    float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
//    float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
    double du = 0.0;//1.0 / tex_width  / 100000.0; //�e�N�X�`���̕�1px��10000����1px
    double dv = 0.0;//1.0 / tex_height / 100000.0; //�e�N�X�`���̍���1px��10000����1px

    //����
    paVertex[0].x = 0.0f;
    paVertex[0].y = 0.0f;
    paVertex[0].z = 0.0f;
    paVertex[0].tu = du;
    paVertex[0].tv = dv;
    //�E��
    paVertex[1].x = xdata.width;
    paVertex[1].y = 0.0f;
    paVertex[1].z = 0.0f;
    paVertex[1].tu = (1.0 / xdata.col_texture_split) - du;
    paVertex[1].tv = dv;
    //����
    paVertex[2].x = 0.0f;
    paVertex[2].y = xdata.height;
    paVertex[2].z = 0.0f;
    paVertex[2].tu = du;
    paVertex[2].tv = (1.0 / xdata.row_texture_split) - dv;
    //�E��
    paVertex[3].x = xdata.width;
    paVertex[3].y = xdata.height;
    paVertex[3].z = 0.0f;
    paVertex[3].tu = (1.0 / xdata.col_texture_split) - du;
    paVertex[3].tv = (1.0 / xdata.row_texture_split) - dv;

    //�o�b�t�@�쐬
    if (_pVertexBuffer == nullptr) {

        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxBoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);

    memcpy(pVertexBuffer, paVertex, _size_vertices); //pVertexBuffer �� paVertex
    _pVertexBuffer->Unlock();
    _num_materials = 1;
    D3DMATERIAL9* paMaterial;
    paMaterial = NEW D3DMATERIAL9[_num_materials];
    for( DWORD i = 0; i < _num_materials; i++){
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
    pID3DXFileData->Unlock();
    GGAF_DELETEARR(paVertex);
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
    _TRACE3_("GgafDxBoardModel::restore() " << _model_name << " end");
}

void GgafDxBoardModel::release() {
    _TRACE3_("GgafDxBoardModel::release() " << _model_name << " start");
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
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    _TRACE3_("GgafDxBoardModel::release() " << _model_name << " end");
}

void GgafDxBoardModel::onDeviceLost() {
    _TRACE3_("GgafDxBoardModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxBoardModel::onDeviceLost() " << _model_name << " end");
}

GgafDxBoardModel::~GgafDxBoardModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}
