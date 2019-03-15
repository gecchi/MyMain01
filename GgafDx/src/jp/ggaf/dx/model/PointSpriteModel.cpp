#include "jp/ggaf/dx/model/PointSpriteModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/PointSpriteActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/PointSpriteEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

DWORD PointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

PointSpriteModel::PointSpriteModel(const char* prm_model_name) : Model(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _pVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _vertices_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
    _obj_model |= Obj_GgafDx_PointSpriteModel;
}

HRESULT PointSpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    _TRACE4_("PointSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //�Ώ�Actor
    const PointSpriteActor* const pTargetActor = (PointSpriteActor*)prm_pActor_target;
    //�Ώ�PointSpriteActor�̃G�t�F�N�g���b�p
    PointSpriteEffect* const pPointSpriteEffect = (PointSpriteEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //����`���UV
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(PointSpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hInvTextureSplitRowcol, _inv_texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hInvTextureSplitRowcol) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetValue(pPointSpriteEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name<<"("<<pPointSpriteEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pPointSpriteEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);

    //�O��`�惂�f���ێ�
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pPointSpriteEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void PointSpriteModel::restore() {
    _TRACE3_("_model_name="<<_model_name);
    ModelManager* pModelManager = pGOD->_pModelManager;
    _papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name = ModelManager::getSpriteFileName(_model_name, "psprx");
    ModelManager::PointSpriteXFileFmt pointsprite_info;
    pModelManager->obtainPointSpriteInfo(&pointsprite_info, xfile_name);
    //�ޔ�
    float square_size_px = pointsprite_info.SquareSize;
    int texture_split_rowcol = pointsprite_info.TextureSplitRowCol;
    int vertices_num = pointsprite_info.VerticesNum;
    _TRACE3_("vertices_num="<<vertices_num);
    UINT size_vertices = sizeof(PointSpriteModel::VERTEX)*vertices_num;
    UINT size_vertex_unit = sizeof(PointSpriteModel::VERTEX);

    //�e�N�X�`���擾�����f���ɕێ�������
    TextureConnection** papTextureConnection = NEW TextureConnection*[1];
    papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(pointsprite_info.TextureFile , this));
    Texture* pTex = papTextureConnection[0]->peek();

    float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
    float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)���Ɠ����ɂȂ�
    if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
        throwCriticalException("�|�C���g�X�v���C�g�p�e�N�X�`��["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")�́A�����`�ł���K�v������܂��B");
    }
    FLOAT bounding_sphere_radius = 0;

    //���_�o�b�t�@�쐬
    PointSpriteModel::VERTEX* paVtxBuffer_data = NEW PointSpriteModel::VERTEX[vertices_num];

    float dis;
    for (int i = 0; i < vertices_num; i++) {
        paVtxBuffer_data[i].x = pointsprite_info.paD3DVECTOR_Vertices[i].x;
        paVtxBuffer_data[i].y = pointsprite_info.paD3DVECTOR_Vertices[i].y;
        paVtxBuffer_data[i].z = pointsprite_info.paD3DVECTOR_Vertices[i].z;
        paVtxBuffer_data[i].psize = (square_size_px*texture_split_rowcol / tex_width) * pointsprite_info.paFLOAT_InitScale[i]; //PSIZE�ɂ̓s�N�Z���T�C�Y�ł͂Ȃ��{���𖄂ߍ��ށB
                                                                                                //�V�F�[�_�[�Ŋg��k���s�N�Z�����v�Z
        paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(pointsprite_info.paD3DVECTOR_VertexColors[i].r,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].g,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].b,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].a );
        paVtxBuffer_data[i].tu = (float)(pointsprite_info.paInt_InitUvPtnNo[i]);
        paVtxBuffer_data[i].tv = 0;

        dis = (FLOAT)(sqrt(paVtxBuffer_data[i].x * paVtxBuffer_data[i].x +
                           paVtxBuffer_data[i].y * paVtxBuffer_data[i].y +
                           paVtxBuffer_data[i].z * paVtxBuffer_data[i].z  )
                       + (((square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                     );

         if (bounding_sphere_radius < dis) {
             bounding_sphere_radius = dis;
         }
    }

    D3DMATERIAL9*   paMaterial = nullptr;
    if (_pVertexBuffer == nullptr) {

        //���_�o�b�t�@�쐬
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                size_vertices,
                D3DUSAGE_WRITEONLY,
                PointSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
        memcpy(pVertexBuffer, paVtxBuffer_data, size_vertices); //pVertexBuffer �� paVertex
        _pVertexBuffer->Unlock();
    }

    paMaterial = NEW D3DMATERIAL9[1];
    paMaterial[0].Diffuse.r = 1.0f;
    paMaterial[0].Diffuse.g = 1.0f;
    paMaterial[0].Diffuse.b = 1.0f;
    paMaterial[0].Diffuse.a = 1.0f;

    //���f���ɕێ�������
    _paMaterial_default     = paMaterial;
    _papTextureConnection   = papTextureConnection;
    _num_materials          = 1;
    _square_size_px         = square_size_px;
    _texture_size_px        = tex_width;
    _texture_split_rowcol   = texture_split_rowcol;
    _vertices_num           = vertices_num;
    _size_vertices          = size_vertices;
    _size_vertex_unit       = size_vertex_unit;
    _paVtxBuffer_data        = paVtxBuffer_data;
    _bounding_sphere_radius = bounding_sphere_radius;
    _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
    _TRACE3_("_model_name=" << _model_name << " end");
}

void PointSpriteModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void PointSpriteModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_DELETEARR(_paVtxBuffer_data);
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

PointSpriteModel::~PointSpriteModel() {
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}
