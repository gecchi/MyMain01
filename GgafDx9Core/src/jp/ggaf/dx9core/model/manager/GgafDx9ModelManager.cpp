#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;





GgafDx9ModelManager::GgafDx9ModelManager(const char* prm_manager_name)
    : GgafResourceManager<GgafDx9Model>(prm_manager_name) {

	//�e�N�X�`���}�l�W���[
	_pTextureManager = NEW GgafDx9TextureManager("GgafDx9TextureManager");
	//�|���S����`�t�@�C���Ǎ���
	DirectXFileCreate( &_s_pIDirectXFile );
	char* paChar_SpriteModelineTemplate = GgafUtil::getFileText(GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + "ggaf_spritemodel_define.x");
	if (paChar_SpriteModelineTemplate == NULL) {
		throw_GgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] �X�v���C�g���Ǎ��݃e���v���[�g\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\" ���J���܂���B");
	}
	HRESULT hr = _s_pIDirectXFile -> RegisterTemplates(paChar_SpriteModelineTemplate, (DWORD)(strlen(paChar_SpriteModelineTemplate)));
	if(hr != DXFILE_OK) {
		throw_GgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] RegisterTemplates�Ɏ��s���܂����B\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\"���m�F���ĉ������B");
	}
	DELETE_IMPOSSIBLE_NULL(paChar_SpriteModelineTemplate);
	_id_lastdraw = -1;
	_id_max = 0;

}


GgafDx9Model* GgafDx9ModelManager::processCreateResource(char* prm_idstr) {
	//�U�蕪��
	char model_type = *prm_idstr; //���ꕶ��
	char* model_name = prm_idstr+2; //�R�����ڈȍ~
	GgafDx9Model* model;
	switch (model_type) {
		case 'M':
			//MeshModel
			model = createMeshModel(model_name, D3DXMESH_SYSTEMMEM);
			break;
		case 'm':
			//DynaMeshModel
			model = createMeshModel(model_name, D3DXMESH_DYNAMIC);
			break;
		case 'S':
			//SpriteModel
			model = createSpriteModel(model_name);
			break;
		case 'P':
			//SpriteModel
			model = createPlateModel(model_name);
			break;
		case 'C':
			//cubeModel
			model = createMeshModel("cube", D3DXMESH_SYSTEMMEM);
			break;
		case 'Q':
			//SquareModel
			model = createSquareModel(model_name);
			break;
		default :
			_TRACE_("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") ����Ȏ�ʂ͂���܂���");
			throw_GgafCriticalException("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") ����ȃ��f����ʂ͒m��܂���");
			model = NULL;
			break;
	}
	return model;
}

GgafDx9MeshModel* GgafDx9ModelManager::createMeshModel(char* prm_model_name, DWORD prm_dwOptions) {
	GgafDx9MeshModel* pMeshModel_New = NEW GgafDx9MeshModel(prm_model_name, prm_dwOptions);
	restoreMeshModel(pMeshModel_New);
	return pMeshModel_New;
}


GgafDx9SpriteModel* GgafDx9ModelManager::createSpriteModel(char* prm_model_name) {

	GgafDx9SpriteModel* pSpriteModel_New = NEW GgafDx9SpriteModel(prm_model_name);
	restoreSpriteModel(pSpriteModel_New);
	return pSpriteModel_New;
}


GgafDx9PlateModel* GgafDx9ModelManager::createPlateModel(char* prm_model_name) {
	GgafDx9PlateModel* pPlateModel_New = NEW GgafDx9PlateModel(prm_model_name);
	restorePlateModel(pPlateModel_New);
	return pPlateModel_New;
}


GgafDx9SquareModel* GgafDx9ModelManager::createSquareModel(char* prm_model_name) {
	GgafDx9SquareModel* pSquareModel_New = NEW GgafDx9SquareModel(prm_model_name);
	restoreSquareModel(pSquareModel_New);
	return pSquareModel_New;
}

void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel) {
	_TRACE_("GgafDx9ModelManager::restoreMeshModel(" << prm_pMeshModel->_model_name << ")");

	//X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDx9MeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
	//�ȉ��� string xfile_name �܂ł�GgafDx9MeshModel�����o�ݒ�̂��߂̎󂯎��ϐ��B
	LPD3DXMESH			pID3DXMesh;      //���b�V��(ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
	D3DMATERIAL9* 		paD3DMaterial9;  //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
	GgafDx9TextureLead**	papTexture;          //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
	DWORD               dwNumMaterials;
	string				xfile_name = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshModel->_model_name) + ".x";

	LPD3DXBUFFER pID3DXBuffer;	//�󂯎��p�o�b�t�@�i�}�e���A���p�j
	HRESULT hr;
	//X�t�@�C���̃t�@�C�����[�h
	hr = D3DXLoadMeshFromX(
			xfile_name.c_str(),        //[in]  LPCTSTR pFilename
			prm_pMeshModel->_dwOptions,//[in]  DWORD Options  D3DXMESH_SYSTEMMEM D3DXMESH_VB_DYNAMIC
			GgafDx9God::_pID3DDevice9, //[in]  LPDIRECT3DDEVICE9 pDevice
			NULL,                      //[out] LPD3DXBUFFER* ppAdjacency
			&pID3DXBuffer,             //[out] LPD3DXBUFFER* ppMaterials
			NULL,                      //[out] LPD3DXBUFFER* ppEffectInstances
			&dwNumMaterials,           //[out] DWORD* pNumMaterials
			&pID3DXMesh                //[out] LPD3DXMESH* pMesh
		 );
	if(hr != D3D_OK) {
		throw_GgafDx9CriticalException("[GgafDx9ModelManager::restoreMeshModel] D3DXLoadMeshFromX�ɂ�郍�[�h�����s�B�Ώ�="<<xfile_name, hr);

//		TRACE(DXGetErrorString9(HRESULT hr));
	}

	//�}�e���A�������o��
	D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
	//��2008/02/02 �̔]�݂���
	// ����Ă��邱�ƃ���
	// GetBufferPointer()�Ŏ擾�ł��� D3DXMATERIAL�\���̔z��̃����o��MatD3D (D3DMATERIAL9�\����) ���~�����B
	//�i��GgafDx9MeshModel�̃����o�[�����ɂ��������߁j�B pID3DXBuffer_tmp �̕��͂������Ɖ��(Release())���悤�Ƃ����B
	// ������������ D3DXMATERIAL�\���̔z����ǂ���������炵���i�����ɂ͏����Ȃ��H�A�����Ńn�}��G�j�B
	// �����ł������Ȃ��̂ŁApaD3DMaterial9_tmp �̍\���̂𕨗��R�s�[�����ĕێ����邱�Ƃɂ��܂���`�A���`���`���܂��傤�B
	paD3DMaterial9 = NEW D3DMATERIAL9[dwNumMaterials];
	for( DWORD i = 0; i < dwNumMaterials; i++) {
		paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
	}

	//Diffuse���˂�Ambient���˂ɃR�s�[����
	//���R�FAmbient���C�g���g�p�����������B���̂��߂ɂ͓��RAmbient���˒l���}�e���A���ɐݒ肵�Ȃ���΂����Ȃ���
	//x�t�@�C���iMatD3D�j�ɂ�Diffuse���˒l�����ݒ肳��Ă��A������Diffuse���˂̒l��
	//Ambient���˒l���p���邱�Ƃɂ���B
	//TODO:�{���ɂ���͂���̂��H�H�H�H
	for( DWORD i = 0; i < dwNumMaterials; i++) {
		paD3DMaterial9[i].Ambient = paD3DMaterial9[i].Diffuse;
	}

	//�e�N�X�`�������o��
	papTexture = NEW GgafDx9TextureLead*[dwNumMaterials];
	for( DWORD i = 0; i < dwNumMaterials; i++) {
		if (paD3DMaterial9_tmp[i].pTextureFilename != NULL && lstrlen(paD3DMaterial9_tmp[i].pTextureFilename) > 0 ) {
			papTexture[i] = (GgafDx9TextureLead*)_pTextureManager->lead(paD3DMaterial9_tmp[i].pTextureFilename);
//			string texture_filename = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(paD3DMaterial9_tmp[i].pTextureFilename);
//			hr = D3DXCreateTextureFromFileEx(
//					GgafDx9God::_pID3DDevice9,   // [in] LPDIRECT3DDEVICE9 pDevice,
//					texture_filename.c_str(),    // [in] LPCTSTR pSrcFile,
//					D3DX_DEFAULT,                // [in] UINT Width,
//					D3DX_DEFAULT,                // [in] UINT Height,
//					D3DX_DEFAULT,                // [in] UINT MipLevels,
//					0,                           // [in] DWORD Usage,
//					D3DFMT_UNKNOWN,              // [in] D3DFORMAT Format,
//					D3DPOOL_MANAGED,             // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
//					D3DX_DEFAULT,                // [in] DWORD Filter,
//					D3DX_DEFAULT,                // [in] DWORD MipFilter,
//					0,                           // [in] D3DCOLOR ColorKey,
//					NULL,                        // [in] D3DXIMAGE_INFO *pSrcInfo,
//					NULL,                        // [in] PALETTEENTRY *pPalette,
//					&papIDirect3DTexture9[i]          // [out] LPDIRECT3DTEXTURE9 *ppTexture
//				 );
//			if(hr != D3D_OK) {
//				throw_GgafDx9CriticalException("[GgafDx9MeshModelManager::load] D3DXCreateTextureFromFile���s�B�Ώ�="<<xfile_name, hr);
//			}
		} else {
			//�e�N�X�`������
			papTexture[i] = NULL;
		}
	}
	RELEASE_IMPOSSIBLE_NULL(pID3DXBuffer);//�e�N�X�`���t�@�C�����͂�������Ȃ��̂Ńo�b�t�@���

	//X�t�@�C���ɖ@�����Ȃ��ꍇ������B���̏ꍇ�@���������悤�ɂ���B
	if(pID3DXMesh -> GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
		LPD3DXMESH pID3DXMesh_tmp = NULL;
		hr = pID3DXMesh -> CloneMeshFVF(
							pID3DXMesh->GetOptions(),                // [in]  DWORD Options,
							D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1,    // [in]  DWORD FVF,
							GgafDx9God::_pID3DDevice9,               // [in]  LPDIRECT3DDEVICE9 pDevice,
							&pID3DXMesh_tmp                          // [out] LPD3DXMESH *ppCloneMesh
						 );
		if(hr != D3D_OK) {
			throw_GgafDx9CriticalException("[GgafDx9ModelManager::restoreMeshModel]  pID3DXMesh -> CloneMeshFVF()���s�B�Ώ�="<<xfile_name, hr);
		}
		D3DXComputeNormals(pID3DXMesh_tmp, NULL); //�@���v�Z
		RELEASE_IMPOSSIBLE_NULL(pID3DXMesh);
		pID3DXMesh = pID3DXMesh_tmp;
	}

	//���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������
	prm_pMeshModel -> _pID3DXMesh      = pID3DXMesh;
	prm_pMeshModel -> _paD3DMaterial9_default  = paD3DMaterial9;
	prm_pMeshModel -> _papTexture      = papTexture;
	prm_pMeshModel -> _dwNumMaterials  = dwNumMaterials;
}


void GgafDx9ModelManager::restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel) {
	_TRACE_("GgafDx9ModelManager::restoreSpriteModel(" << prm_pSpriteModel->_model_name << ")");

	prm_pSpriteModel->_pTexture = NULL;
	prm_pSpriteModel->_paRectUV = NULL;

	prm_pSpriteModel->_pD3DMaterial9_default = NEW D3DMATERIAL9;
	ZeroMemory(prm_pSpriteModel->_pD3DMaterial9_default, sizeof(D3DMATERIAL9) );
	prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.r = 1.0f;
	prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.g = 1.0f;
	prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.b = 1.0f;
	prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.a = 1.0f;
	prm_pSpriteModel->_pD3DMaterial9_default->Ambient.r = 1.0f;
	prm_pSpriteModel->_pD3DMaterial9_default->Ambient.g = 1.0f;
	prm_pSpriteModel->_pD3DMaterial9_default->Ambient.b = 1.0f;
	prm_pSpriteModel->_pD3DMaterial9_default->Ambient.a = 1.0f;

	HRESULT	hr;
	string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteModel->_model_name) + ".x";

	//�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)

	IDirectXFileEnumObject* pIDirectXFileEnumObject;
	IDirectXFileData* pIDirectXFileData;
	hr = _s_pIDirectXFile -> CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
	if(hr != DXFILE_OK) {
		throw_GgafDx9CriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B", hr);
	}

	//TODO
	//const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

	char**	 ppaChar_TextureFile;
	float*   pFloat_Size_SpriteModelWidth;
	float*   pFloat_Size_SpriteModelHeight;
	int* 	 pInt_RowNum_TextureSplit;
	int* 	 pInt_ColNum_TextureSplit;

	// 1�Z�b�g�����Ǎ���
	hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
	if(hr != DXFILE_OK) {
		throw_GgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" �̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
	}
	const GUID *pGuid;
	pIDirectXFileData->GetType( &pGuid );
	//if( *pGuid == PersonID_GUID ) {
	if(true) {
		DWORD Size;
		// PersonID�e���v���[�g�f�[�^���擾
		pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
		pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_SpriteModelWidth);
		pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_SpriteModelHeight);
		pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
		pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
		prm_pSpriteModel->_fSize_SpriteModelWidthPx  = *pFloat_Size_SpriteModelWidth;
		prm_pSpriteModel->_fSize_SpriteModelHeightPx = *pFloat_Size_SpriteModelHeight;
		prm_pSpriteModel->_iRowNum_TextureSplit    = *pInt_RowNum_TextureSplit;
		prm_pSpriteModel->_iColNum_TextureSplit    = *pInt_ColNum_TextureSplit;
	} else {
		throw_GgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" ��GUID����v���܂���B");
	}

	//�e�N�X�`���擾�����f���ɕێ�������
	//string texture_filename = GGAFDX9_PROPERTY(DIR_TEXTURE_MODEL) + string(*ppaChar_TextureFile);
	GgafDx9TextureLead* pTexture = (GgafDx9TextureLead*)_pTextureManager->lead(*ppaChar_TextureFile);
//	hr = D3DXCreateTextureFromFileEx(
//			GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
//			texture_filename.c_str(),  // [in] LPCTSTR pSrcFile,
//			D3DX_DEFAULT,              // [in] UINT Width,
//			D3DX_DEFAULT,              // [in] UINT Height,
//			D3DX_DEFAULT,              // [in] UINT MipLevels,
//			0,                         // [in] DWORD Usage,
//			D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
//			D3DPOOL_MANAGED,           // [in] D3DPOOL Pool,
//			D3DX_DEFAULT,              // [in] DWORD Filter,
//			D3DX_DEFAULT,              // [in] DWORD MipFilter,
//			D3DCOLOR_ARGB(255, 0, 0, 0),  // [in] D3DCOLOR ColorKey,
//			NULL,                      // [in] D3DXIMAGE_INFO *pSrcInfo,
//			NULL,                      // [in] PALETTEENTRY *pPalette,
//			&pIDirect3DTexture9             // [out] LPDIRECT3DTEXTURE9 *ppTexture
//		 );
//	if(hr != D3D_OK) {
//		throw_GgafDx9CriticalException("[GgafDx9ModelManager::restoreSpriteModel] �e�N�X�`���t�@�C���Ǎ��݂Ɏ��s���܂����B�Ώ�="<<texture_filename, hr);
//	}
	//�e�N�X�`���̎Q�Ƃ�ێ�������B
 	prm_pSpriteModel->_pTexture = pTexture;


	GgafDx9SpriteModel::VERTEX* paVertex = NEW GgafDx9SpriteModel::VERTEX[4];
	prm_pSpriteModel->_iSize_Vertecs = sizeof(GgafDx9SpriteModel::VERTEX)*4;
	prm_pSpriteModel->_iSize_Vertec_unit = sizeof(GgafDx9SpriteModel::VERTEX);

	//���_�z��������f���ɕێ�������
	paVertex[0].x     = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
	paVertex[0].y     = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
	paVertex[0].z     = 0.0f;
	paVertex[0].nx    = 0.0f;
	paVertex[0].ny    = 0.0f;
	paVertex[0].nz    = -1.0f;
	paVertex[0].color = D3DCOLOR_ARGB(255,255,255,255);
	paVertex[0].tu    = 0.0f;
	paVertex[0].tv    = 0.0f;

	paVertex[1].x     = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
	paVertex[1].y     = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
	paVertex[1].z     = 0.0f;
	paVertex[1].nx    = 0.0f;
	paVertex[1].ny    = 0.0f;
	paVertex[1].nz    = -1.0f;
	paVertex[1].color = D3DCOLOR_ARGB(255,255,255,255);
	paVertex[1].tu    = 1.0f;
	paVertex[1].tv    = 0.0f;

	paVertex[2].x     = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
	paVertex[2].y     = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
	paVertex[2].z     = 0.0f;
	paVertex[2].nx    = 0.0f;
	paVertex[2].ny    = 0.0f;
	paVertex[2].nz    = -1.0f;
	paVertex[2].color = D3DCOLOR_ARGB(255,255,255,255);
	paVertex[2].tu    = 0.0f;
	paVertex[2].tv    = 1.0f;

	paVertex[3].x     = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
	paVertex[3].y     = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
	paVertex[3].z     = 0.0f;
	paVertex[3].nx    = 0.0f;
	paVertex[3].ny    = 0.0f;
	paVertex[3].nz    = -1.0f;
	paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
	paVertex[3].tu    = 1.0f;
	paVertex[3].tv    = 1.0f;


	//�o�b�t�@�쐬
	if (prm_pSpriteModel->_pIDirect3DVertexBuffer9 == NULL) {

		hr = GgafDx9God::_pID3DDevice9 -> CreateVertexBuffer(
											 prm_pSpriteModel->_iSize_Vertecs,
											 D3DUSAGE_WRITEONLY,
											 GgafDx9SpriteModel::FVF,
											 D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
											 &(prm_pSpriteModel->_pIDirect3DVertexBuffer9),
											 NULL);
		if(hr != D3D_OK) {
			throw_GgafDx9CriticalException("[GgafDx9ModelManager::restoreSpriteModel] _pID3DDevice9 -> CreateVertexBuffer ���s model="<<(prm_pSpriteModel->_model_name), hr);
		}
	}
	//���_�o�b�t�@�쐬
	//���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
	void *pVertexBuffer;
	hr = prm_pSpriteModel->_pIDirect3DVertexBuffer9 -> Lock(0, prm_pSpriteModel->_iSize_Vertecs, (void**)&pVertexBuffer, 0);
	if(hr != D3D_OK) {
		throw_GgafDx9CriticalException("[GgafDx9ModelManager::restoreSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSpriteModel->_model_name, hr);
	}
	memcpy(pVertexBuffer, paVertex, prm_pSpriteModel->_iSize_Vertecs); //pVertexBuffer �� paVertex
	prm_pSpriteModel->_pIDirect3DVertexBuffer9 -> Unlock();

	//�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
	int iAnimationPatternNum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
	GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[iAnimationPatternNum];
	for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
		for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
			int iAnimationPatternNo = row*(*pInt_ColNum_TextureSplit)+col;
			paRectUV[iAnimationPatternNo]._aUV[0].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
			paRectUV[iAnimationPatternNo]._aUV[0].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

			paRectUV[iAnimationPatternNo]._aUV[1].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
			paRectUV[iAnimationPatternNo]._aUV[1].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

			paRectUV[iAnimationPatternNo]._aUV[2].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
			paRectUV[iAnimationPatternNo]._aUV[2].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));

			paRectUV[iAnimationPatternNo]._aUV[3].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
			paRectUV[iAnimationPatternNo]._aUV[3].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));
		}
	}
	prm_pSpriteModel->_paRectUV = paRectUV;
	prm_pSpriteModel->_iAnimationPatternNo_Max=iAnimationPatternNum-1;

	//��n��

	DELETEARR_IMPOSSIBLE_NULL(paVertex);
	RELEASE_IMPOSSIBLE_NULL(pIDirectXFileData);
	RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restorePlateModel(GgafDx9PlateModel* prm_pPlateModel) {
	_TRACE_("GgafDx9ModelManager::restorePlateModel(" << prm_pPlateModel->_model_name << ")");

	HRESULT	hr;
	string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pPlateModel->_model_name) + ".x";

//	prm_pPlateModel->_pD3DMaterial9 = NEW D3DMATERIAL9;
//	ZeroMemory( prm_pPlateModel->_pD3DMaterial9, sizeof(D3DMATERIAL9) );
//	prm_pPlateModel->_pD3DMaterial9->Diffuse.r = 1.0f;
//	prm_pPlateModel->_pD3DMaterial9->Diffuse.g = 1.0f;
//	prm_pPlateModel->_pD3DMaterial9->Diffuse.b = 1.0f;
//	prm_pPlateModel->_pD3DMaterial9->Diffuse.a = 0.2f;
//	prm_pPlateModel->_pD3DMaterial9->Ambient = prm_pPlateModel->_pD3DMaterial9->Diffuse;



	IDirectXFileEnumObject* pIDirectXFileEnumObject;
	IDirectXFileData* pIDirectXFileData;
	hr = _s_pIDirectXFile -> CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
	if(hr != DXFILE_OK) {
		throw_GgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");
	}

	//TODO
	//const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

	char**	 ppaChar_TextureFile;
	float*   pFloat_Size_PlateModelWidth;
	float*   pFloat_Size_PlateModelHeight;
	int* 	 pInt_RowNum_TextureSplit;
	int* 	 pInt_ColNum_TextureSplit;

	// 1�Z�b�g�����Ǎ���
	hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
	if(hr != DXFILE_OK) {
		throw_GgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"�̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
	}

	const GUID *pGuid;
	pIDirectXFileData->GetType( &pGuid );
	//if( *pGuid == PersonID_GUID ) {

	if(true) {
		DWORD Size;
		// PersonID�e���v���[�g�f�[�^���擾
		pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
		pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_PlateModelWidth);
		pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_PlateModelHeight);
		pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
		pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
		//�f�[�^�̓R�s�[���Ȃ���΂����܂���B
		prm_pPlateModel->_fSize_PlateModelWidth  = *pFloat_Size_PlateModelWidth;
		prm_pPlateModel->_fSize_PlateModelHeight = *pFloat_Size_PlateModelHeight;
		prm_pPlateModel->_iRowNum_TextureSplit    = *pInt_RowNum_TextureSplit;
		prm_pPlateModel->_iColNum_TextureSplit    = *pInt_ColNum_TextureSplit;
	} else {
		throw_GgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"��GUID����v���܂���B");
	}

	//���_�z��������f���ɕێ�������
	//string texture_filename = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(*ppaChar_TextureFile);
	GgafDx9TextureLead* pTexture = (GgafDx9TextureLead*)_pTextureManager->lead(*ppaChar_TextureFile);
//	hr = D3DXCreateTextureFromFileEx(
//			GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
//			texture_filename.c_str(),  // [in] LPCTSTR pSrcFile,
//			D3DX_DEFAULT,              // [in] UINT Width,
//			D3DX_DEFAULT,              // [in] UINT Height,
//			D3DX_DEFAULT,              // [in] UINT MipLevels,
//			0,                         // [in] DWORD Usage,
//			D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
//			D3DPOOL_MANAGED,           // [in] D3DPOOL Pool,
//			D3DX_DEFAULT,              // [in] DWORD Filter,
//			D3DX_DEFAULT,              // [in] DWORD MipFilter,
//			0,                         // [in] D3DCOLOR ColorKey,
//			NULL,                      // [in] D3DXIMAGE_INFO *pSrcInfo,
//			NULL,                      // [in] PALETTEENTRY *pPalette,
//			&pIDirect3DTexture9             // [out] LPDIRECT3DTEXTURE9 *ppTexture
//		 );
//	if(hr != D3D_OK) {
//		throw_GgafDx9CriticalException("[GgafDx9ModelManager::restorePlateModel] �e�N�X�`���t�@�C���Ǎ��݂Ɏ��s���܂����B�Ώ�="<<texture_filename, hr);
//	}
	prm_pPlateModel->_pTexture = pTexture;

	// �e�N�X�`���[�̃T�C�Y���擾����
	/*
	D3DSURFACE_DESC d3dsurface_desc;
	pIDirect3DTexture9->GetLevelDesc(0, &d3dsurface_desc);
	UINT ulTextureWidth  = d3dsurface_desc.Width;  //���i�e�N�Z���j
	UINT ulTextureHeight = d3dsurface_desc.Height; //�e�N�X�`�������i�s�N�Z���j
	*/

	//�S�p�^�[����UV�������W�����߂ĕێ�
	int iPatternNum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
	GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[iPatternNum];
	for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
		for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
			int iPatternNo = row*(*pInt_ColNum_TextureSplit)+col;

			paRectUV[iPatternNo]._aUV[0].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
			paRectUV[iPatternNo]._aUV[0].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

			paRectUV[iPatternNo]._aUV[1].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
			paRectUV[iPatternNo]._aUV[1].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

			paRectUV[iPatternNo]._aUV[2].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
			paRectUV[iPatternNo]._aUV[2].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));

			paRectUV[iPatternNo]._aUV[3].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
			paRectUV[iPatternNo]._aUV[3].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));
		}
	}
	prm_pPlateModel->_paRectUV = paRectUV;
	prm_pPlateModel->_iPatternNo_Max=iPatternNum-1;

	//��n��
	RELEASE_IMPOSSIBLE_NULL(pIDirectXFileData);
	RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}


void GgafDx9ModelManager::restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel) {
	_TRACE_("GgafDx9ModelManager::restoreSquareModel(" << prm_pSquareModel->_model_name << ")");

		//���_�����ݒ肵�����B


	prm_pSquareModel->_pD3DMaterial9 = NEW D3DMATERIAL9;
	ZeroMemory(prm_pSquareModel->_pD3DMaterial9, sizeof(D3DMATERIAL9) );
	prm_pSquareModel->_pD3DMaterial9->Diffuse.r = prm_pSquareModel->_pD3DMaterial9->Ambient.r = 1.0f;
	prm_pSquareModel->_pD3DMaterial9->Diffuse.g = prm_pSquareModel->_pD3DMaterial9->Ambient.g = 0.0f;
	prm_pSquareModel->_pD3DMaterial9->Diffuse.b = prm_pSquareModel->_pD3DMaterial9->Ambient.b = 0.0f;
	prm_pSquareModel->_pD3DMaterial9->Diffuse.a = prm_pSquareModel->_pD3DMaterial9->Ambient.a = 1.0f;



	GgafDx9SquareModel::VERTEX* paVertex = NEW GgafDx9SquareModel::VERTEX[12];
	prm_pSquareModel->_iSize_Vertecs = sizeof(GgafDx9SquareModel::VERTEX)*4;
	prm_pSquareModel->_iSize_Vertec_unit = sizeof(GgafDx9SquareModel::VERTEX);
	paVertex[0].color = D3DCOLOR_ARGB(255,255,0,0);
	paVertex[1].color = D3DCOLOR_ARGB(255,255,0,0);
	paVertex[2].color = D3DCOLOR_ARGB(255,255,0,0);
	paVertex[3].color = D3DCOLOR_ARGB(255,255,0,0);


	//���_�z��������f���ɕێ�������
	paVertex[0].x     = -0.5/PX_UNIT;
	paVertex[0].y     = 0.5/PX_UNIT;
	paVertex[0].z     = 0.0f;
	paVertex[0].nx    = 0.0f;
	paVertex[0].ny    = 0.0f;
	paVertex[0].nz    = -1.0f;
	paVertex[0].color = D3DCOLOR_ARGB(255,255,0,0);

	paVertex[1].x     = 0.5/PX_UNIT;
	paVertex[1].y     = 0.5/PX_UNIT;
	paVertex[1].z     = 0.0f;
	paVertex[1].nx    = 0.0f;
	paVertex[1].ny    = 0.0f;
	paVertex[1].nz    = -1.0f;
	paVertex[1].color = D3DCOLOR_ARGB(255,255,0,0);

	paVertex[2].x     = -0.5/PX_UNIT;
	paVertex[2].y     = -0.5/PX_UNIT;
	paVertex[2].z     = 0.0f;
	paVertex[2].nx    = 0.0f;
	paVertex[2].ny    = 0.0f;
	paVertex[2].nz    = -1.0f;
	paVertex[2].color = D3DCOLOR_ARGB(255,255,0,0);

	paVertex[3].x     = 0.5/PX_UNIT;
	paVertex[3].y     = -0.5/PX_UNIT;
	paVertex[3].z     = 0.0f;
	paVertex[3].nx    = 0.0f;
	paVertex[3].ny    = 0.0f;
	paVertex[3].nz    = -1.0f;
	paVertex[3].color = D3DCOLOR_ARGB(255,255,0,0);

	HRESULT	hr;
	//���_�o�b�t�@�쐬
	if (prm_pSquareModel->_pIDirect3DVertexBuffer9 == NULL) {
		hr = GgafDx9God::_pID3DDevice9 -> CreateVertexBuffer(
											 prm_pSquareModel->_iSize_Vertecs,
											 D3DUSAGE_WRITEONLY,
											 GgafDx9SquareModel::FVF,
											 D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
											 &(prm_pSquareModel->_pIDirect3DVertexBuffer9),
											 NULL);
		if(hr != D3D_OK) {
			throw_GgafDx9CriticalException("[GgafDx9SquareModelManager::restoreSquareModel] _pID3DDevice9 -> CreateVertexBuffer ���s model="<<prm_pSquareModel->_model_name, hr);
		}
	}

	//���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
	void *pVertexBuffer;
	hr = prm_pSquareModel->_pIDirect3DVertexBuffer9 -> Lock(0, prm_pSquareModel->_iSize_Vertecs, (void**)&pVertexBuffer, 0);
	if(hr != D3D_OK) {
		throw_GgafDx9CriticalException("[GgafDx9SquareModelManager::restoreSquareModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSquareModel->_model_name, hr);
	}
	memcpy(pVertexBuffer, paVertex, prm_pSquareModel->_iSize_Vertecs);
	prm_pSquareModel->_pIDirect3DVertexBuffer9 -> Unlock();

	//��n��
	DELETEARR_IMPOSSIBLE_NULL(paVertex);
}

GgafResourceLead<GgafDx9Model>* GgafDx9ModelManager::processCreateLead(char* prm_idstr, GgafDx9Model* prm_pResource) {
	_TRACE_(" GgafDx9ModelManager::processCreateLead "<<prm_idstr<<" �𐶐��J�n�B");
	GgafDx9ModelLead* p = NEW GgafDx9ModelLead(prm_idstr, prm_pResource);
	_TRACE_(" GgafDx9ModelManager::processCreateLead "<<prm_idstr<<" �𐶐��I���B");
	return p;
}


GgafDx9ModelManager::~GgafDx9ModelManager() {
	_TRACE_("GgafDx9ModelManager::~GgafDx9ModelManager() start-->");
	RELEASE_IMPOSSIBLE_NULL(_s_pIDirectXFile);
	_pTextureManager->dump();
	DELETE_IMPOSSIBLE_NULL(_pTextureManager);
	_TRACE_("GgafDx9ModelManager::releaseAll() ���邯�ǂ��A�����ł͊��ɉ����J��������̂��Ȃ��͂��ł�");
	releaseAll();
	_TRACE_("GgafDx9ModelManager::~GgafDx9ModelManager() end<--");

}

void GgafDx9ModelManager::restoreAll() {
	_TRACE_("GgafDx9ModelManager::restoreAll() start-->");
	GgafResourceLead<GgafDx9Model>* pCurrent = _pTop;
	_TRACE_("restoreAll pCurrent="<<pCurrent);
	while (pCurrent != NULL) {
		pCurrent->getResource()->restore();
		pCurrent = pCurrent -> _pNext;
	}
	_TRACE_("GgafDx9ModelManager::restoreAll() end<--");
}

void GgafDx9ModelManager::onDeviceLostAll() {
	_TRACE_("GgafDx9ModelManager::onDeviceLostAll() start-->");
	GgafResourceLead<GgafDx9Model>* pCurrent = _pTop;
	_TRACE_("onDeviceLostAll pCurrent="<<pCurrent);
	while (pCurrent != NULL) {
		pCurrent->getResource()->onDeviceLost();
		pCurrent = pCurrent -> _pNext;
	}
	TRACE("GgafDx9ModelManager::onDeviceLostAll() end<--");
}

void GgafDx9ModelManager::releaseAll() {
	_TRACE_("GgafDx9ModelManager::releaseAll() start-->");
	GgafResourceLead<GgafDx9Model>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		pCurrent->getResource()->release();
		pCurrent = pCurrent -> _pNext;
	}
	_TRACE_("GgafDx9ModelManager::releaseAll() end<--");
}


























//
//
//
//
//
//
//
//
//GgafDx9SpriteModel* GgafDx9ModelManager::obtainSpriteModel(string prm_model_name) {
//	GgafDx9Model* pModel = GgafDx9ModelManager::find(prm_model_name);
//	if (pModel == NULL) {
//		GgafDx9SpriteModel* pSpriteModel_New = createSpriteModel(prm_model_name);
//		GgafDx9ModelManager::add((GgafDx9Model*)pSpriteModel_New);
//		return pSpriteModel_New;
//	} else {
//		return (GgafDx9SpriteModel*)pModel;
//	}
//}
//
//GgafDx9SquareModel* GgafDx9ModelManager::obtainSquareModel(string prm_model_name) {
//	GgafDx9Model* pModel = GgafDx9ModelManager::find(prm_model_name);
//	if (pModel == NULL) {
//		GgafDx9SquareModel* pSquareModel_New = createSquareModel(prm_model_name);
//		GgafDx9ModelManager::add((GgafDx9Model*)pSquareModel_New);
//		return pSquareModel_New;
//	} else {
//		return (GgafDx9SquareModel*)pModel;
//	}
//}
//
//
//GgafDx9MeshModel* GgafDx9ModelManager::obtainMeshModel(string prm_model_name, DWORD prm_dwOptions) {
//	GgafDx9Model* pModel = GgafDx9ModelManager::find(prm_model_name);
//	if (pModel == NULL) {
//		GgafDx9MeshModel* pMeshModel_New = createMeshModel(prm_model_name, prm_dwOptions);
//		GgafDx9ModelManager::add((GgafDx9Model*)pMeshModel_New);
//		return pMeshModel_New;
//	} else {
//		return (GgafDx9MeshModel*)pModel;
//	}
//}
//
//GgafDx9PlateModel* GgafDx9ModelManager::obtainPlateModel(string prm_model_name) {
//	GgafDx9Model* pModel = GgafDx9ModelManager::find(prm_model_name);
//	if (pModel == NULL) {
//		GgafDx9PlateModel* pPlateModel_New = createPlateModel(prm_model_name);
//		GgafDx9ModelManager::add((GgafDx9Model*)pPlateModel_New);
//		return pPlateModel_New;
//	} else {
//		return (GgafDx9PlateModel*)pModel;
//	}
//}


