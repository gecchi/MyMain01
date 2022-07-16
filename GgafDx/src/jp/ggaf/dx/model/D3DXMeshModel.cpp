#include "jp/ggaf/dx/model/D3DXMeshModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/D3DXMeshActor.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

D3DXMeshModel::D3DXMeshModel(const char* prm_model_id, DWORD prm_dwOptions) : Model(prm_model_id) {
    _obj_model |= Obj_GgafDx_D3DXMeshModel;
    _pID3DXMesh = nullptr;
    _num_materials = 0L;
    _dwOptions = prm_dwOptions;
    _max_draw_set_num = 1;
}

HRESULT D3DXMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("D3DXMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = pGOD->_pID3DDevice9;
    //�ΏۃA�N�^�[
    const D3DXMeshActor* const pTargetActor = (D3DXMeshActor*)prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    MeshEffect* const pMeshEffect = (MeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMeshEffect->_pID3DXEffect;

    pDevice->SetFVF(D3DXMeshActor::FVF);
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
    }
    for (DWORD i = 0; i < _num_materials; i++) {
        if (ModelManager::_pModelLastDraw != this || _num_materials != 1) {
            if (_papTextureConnection[i]) {
                if (i == 0) {
                    //�}�e���A��0�Ԃ́A���ʂɋK��̃e�N�X�`����ݒ肷��d�l
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[i]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("D3DXMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
            //�}�e���A���̃Z�b�g
            hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[i].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
            checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
            checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
            checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
            checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
        }

        //�`��
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
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
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
        }
        _TRACE4_("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
        hr = _pID3DXMesh->DrawSubset(i);  //�Ȃ�ĕ֗��ȃ��\�b�h�B
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    }
    //�O��`�惂�f�������f
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}

//�V�F�[�_�[�����O
//        if (pTargetActor->_sx == LEN_UNIT &&
//            pTargetActor->_sy == LEN_UNIT &&
//            pTargetActor->_sz == LEN_UNIT)
//        {
//            hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
//        } else {
//            //�g��k�����Ȃ���Ă��邽�߁A�J������ԂɃg�����X�t�H�[�����ꂽ��Œ��_�@���̐��K������悤�ɐݒ�i���׍��j
//            pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
//            pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


void D3DXMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    ModelManager* pModelManager = pGOD->_pModelManager;
    //�yrestoreD3DXMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)D3DXMeshModel�̃����o�ɃZ�b�g

    ModelManager::MeshXFileFmt xdata;
    std::string model_def_file = std::string(_model_id) + ".meshx";
    std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
    pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
    _matBaseTransformMatrix = xdata.BaseTransformMatrix; //TODO:����͎g���Ă��Ȃ��B�ǂ�����ēK�p���悤���E�E�E
    _draw_set_num = xdata.DrawSetNum;
    if (_draw_set_num != 1) {
        _TRACE_("D3DXMeshModel::restore() �{���f���� "<<_model_id<<" �̓����`��Z�b�g���� 1 �ɏ㏑������܂����B�i_draw_set_num="<<_draw_set_num<<" �͖�������܂����B�j");
        _draw_set_num = 1;
    }
    std::string xfilepath = Model::getXFilePath(xdata.XFileNames[0]);

    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��D3DXMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
    LPD3DXMESH pID3DXMesh; //���b�V��(ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* paMaterial; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    TextureConnection** papTextureConnection; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
    DWORD num_materials;

//    std::string xfile_name = Model::getModelDefineFilePath(_model_id, "meshx");
//    if (xfile_name == "") {
//         throwCriticalException("���b�V���t�@�C��(*.x)��������܂���Bmodel_id="<<(_model_id));
//    }

    LPD3DXBUFFER pID3DXBuffer; //�󂯎��p�o�b�t�@�i�}�e���A���p�j
    HRESULT hr;
    //X�t�@�C���̃t�@�C�����[�h
    hr = D3DXLoadMeshFromX(
            xfilepath.c_str(),             //[in]  LPCTSTR pFilename
            _dwOptions, //[in]  DWORD Options  D3DXMESH_SYSTEMMEM D3DXMESH_VB_DYNAMIC
            pGOD->_pID3DDevice9,       //[in]  LPDIRECT3DDEVICE9 pDevice
            nullptr,                        //[out] LPD3DXBUFFER* ppAdjacency
            &pID3DXBuffer,                  //[out] LPD3DXBUFFER* ppMaterials
            nullptr,                        //[out] LPD3DXBUFFER* ppEffectInstances
            &num_materials,                //[out] DWORD* pNumMaterials
            &pID3DXMesh                     //[out] LPD3DXMESH* pMesh
         );
    checkDxException(hr, D3D_OK, "D3DXLoadMeshFromX�ɂ�郍�[�h�����s�B�Ώ�="<<xfilepath);

    IDirect3DVertexBuffer9* pVb_load;
    pID3DXMesh->GetVertexBuffer(&pVb_load);
    DWORD size_vertex_unit = pID3DXMesh->GetNumBytesPerVertex(); // 1�̒��_�̃T�C�Y
    void* paVertexBuffer;
    int nVertices = (int)(pID3DXMesh->GetNumVertices()); //���b�V���R���e�i�̒��_��
    pVb_load->Lock(0, nVertices*size_vertex_unit, (void**)&paVertexBuffer, 0);
//    for (int vi = 0; vi < nVertices; vi++) {
//        Model::VERTEX_POS* pVtx = (Model::VERTEX_POS*)pVb_load + (size_vertex_unit*vi);  //�ǂݍ���1���_�̊J�n�A�h���X
//    }
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        //X�t�@�C���ɖ@�����Ȃ��ꍇ
        transformPosVtx(paVertexBuffer, size_vertex_unit, nVertices);
    } else {
        transformPosNomalVtx(paVertexBuffer, size_vertex_unit, nVertices);
    }
    pVb_load->Unlock();
    pVb_load->Release();

    //�œK��
    DWORD *pAdjacency = NEW DWORD [ pID3DXMesh->GetNumFaces() * 3 ];
    hr = pID3DXMesh->GenerateAdjacency( 1e-6f, pAdjacency );
    checkDxException(hr, D3D_OK, "GenerateAdjacency������܂���B�Ώ�="<<xfilepath);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT, pAdjacency, nullptr, nullptr, nullptr );
    checkDxException(hr, D3D_OK, "D3DXMESHOPT_ATTRSORT�ł��܂���B�Ώ�="<<xfilepath);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE, pAdjacency, nullptr, nullptr, nullptr );
    checkDxException(hr, D3D_OK, "D3DXMESHOPT_VERTEXCACHE�ł��܂���B�Ώ�="<<xfilepath);
    GGAF_DELETEARR(pAdjacency);

    //�}�e���A�������o��
    D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
    //��2008/02/02 �̔]�݂���
    // ����Ă��邱�ƃ���
    // GetBufferPointer()�Ŏ擾�ł��� D3DXMATERIAL�\���̔z��̃����o��MatD3D (D3DMATERIAL9�\����) ���~�����B
    //�\���̂𕨗��R�s�[�����ĕۑ����邱�Ƃɂ��܂���`�A�Ƃ肠�������`���܂��傤�B
    paMaterial = NEW D3DMATERIAL9[num_materials];
    for ( DWORD i = 0; i < num_materials; i++) {
        paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
    }

    //�}�e���A����Diffuse���˂�Ambient���˂ɃR�s�[����
    //���R�FAmbient���C�g���g�p�����������B���̂��߂ɂ͓��RAmbient���˒l���}�e���A���ɐݒ肵�Ȃ���΂����Ȃ���
    //�G�N�X�|�[�g���ꂽx�t�@�C���̃}�e���A����Ambient���˒l���ݒ肳��ĂȂ��i�����c�[���̂����H�j�B
    //�܂��قƂ��Diffuse=Ambient�Ŗ��Ȃ��n�Y�ƍl�����B
    //�����Ńf�t�H���g�ŁADiffuse���˒l��Ambient���˒l��ݒ肷�邱�Ƃɂ���A�Ƃ肠�����B
    //��2009/3/13��
    //�Œ�p�C�v���C���͂����g��Ȃ��Ȃ����B����ɔ����}�e���A��Diffuse�̓V�F�[�_�[�̃p�����[�^�݂̂ŗ��p���Ă���B
    //TODO:���݃}�e���A��Ambient�͎Q�Ƃ���Ȃ��B�������������H
    for ( DWORD i = 0; i < num_materials; i++) {
        paMaterial[i].Ambient = paMaterial[i].Diffuse;
    }

    //�e�N�X�`�������o��
    papTextureConnection = NEW TextureConnection*[num_materials];
    char* texture_filename;
    for ( DWORD i = 0; i < num_materials; i++) {
        texture_filename = paD3DMaterial9_tmp[i].pTextureFilename;
        if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
            papTextureConnection[i] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(texture_filename, this));
        } else {
            //�e�N�X�`������
            papTextureConnection[i] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(CONFIG::WHITE_TEXTURE.c_str(), this));
        }
    }
    GGAF_RELEASE(pID3DXBuffer);//�e�N�X�`���t�@�C�����͂�������Ȃ��̂Ńo�b�t�@���

    //X�t�@�C���ɖ@�����Ȃ��ꍇ�AFVF�ɖ@����ǉ����A�@�����v�Z���Ă�ݒ�B
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        LPD3DXMESH pID3DXMesh_tmp = nullptr;
        hr = pID3DXMesh->CloneMeshFVF(
                           pID3DXMesh->GetOptions(),             // [in]  DWORD Options,
                           D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1, // [in]  DWORD FVF,
                           pGOD->_pID3DDevice9,             // [in]  LPDIRECT3DDEVICE9 pDevice,
                           &pID3DXMesh_tmp                       // [out] LPD3DXMESH *ppCloneMesh
                         );
        checkDxException(hr, D3D_OK, " pID3DXMesh->CloneMeshFVF()���s�B�Ώ�="<<xfilepath);
        D3DXComputeNormals(pID3DXMesh_tmp, nullptr); //�@���v�Z�iFace�̕\���ǂ����ɖ@�������邩�A�ǂ�����Ĕ��肵�Ă���̂��낤���E�E�E�j
        GGAF_RELEASE(pID3DXMesh);
        pID3DXMesh = pID3DXMesh_tmp;
    }

    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������
    _pID3DXMesh             = pID3DXMesh;
    _paMaterial_default     = paMaterial;
    _papTextureConnection   = papTextureConnection;
    _num_materials          = num_materials;
    _bounding_sphere_radius = 10.0f; //TODO:���E�����a�傫���Ƃ肠����100px
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_pID3DXMesh == nullptr) {
        _TRACE_("�y�x���z [D3DXMeshModel::release()]  "<<_model_id<<" �� _pID3DXMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
    }
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
    GGAF_RELEASE(_pID3DXMesh);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_id=" << _model_id << " end");
}

D3DXMeshModel::~D3DXMeshModel() {
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}
