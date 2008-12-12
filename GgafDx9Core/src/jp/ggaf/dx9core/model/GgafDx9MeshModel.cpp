#include "stdafx.h"

GgafDx9MeshModel::GgafDx9MeshModel(string prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9MeshModel::GgafDx9MeshModel(" <<  prm_model_name << ")");
	_pID3DXMesh      = NULL;
	_paD3DMaterial9  = NULL;
	_papID3DTexture9 = NULL;
	_dwNumMaterials  = 0L;
	_pModel_Next     = NULL;
	//��L�̃v���p�e�B�́AGgafDx9ModelManager::restoreMeshModel() ����ݒ肳��邱�ƂɂȂ�B
	_dwOptions = prm_dwOptions;
}

HRESULT GgafDx9MeshModel::draw(GgafDx9MainActor* prm_pActor_Target) {
	GgafDx9MeshActor* pMeshActor_Target = (GgafDx9MeshActor*)prm_pActor_Target;

	HRESULT hr;
	for(DWORD i = 0; i < _dwNumMaterials; i++) {

		_paD3DMaterial9[i].Ambient.a = pMeshActor_Target->_fAlpha;
		_paD3DMaterial9[i].Diffuse.a = pMeshActor_Target->_fAlpha;
        hr = GgafDx9God::_pID3DDevice9 -> SetMaterial(&(_paD3DMaterial9[i]));	//�}�e���A���̃Z�b�g
        if(hr != D3D_OK) {
        	throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw]["<<prm_pActor_Target->getName()<<"]��SetMaterial(&(paD3DMaterial9[i].MatD3D)���s model="<<_model_name, hr);
		}
		if (_papID3DTexture9[i] != NULL) {
			hr = GgafDx9God::_pID3DDevice9 -> SetTexture( 0, _papID3DTexture9[i] );	//�e�N�X�`���̃Z�b�g
 			if(hr != D3D_OK) {
 				throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]��SetTexture( 0, papID3DTexture9[i])  ���s model="<<_model_name, hr);
			}
		} else {
			hr = GgafDx9God::_pID3DDevice9 -> SetTexture(0, NULL); //������΃e�N�X�`������
 			if(hr != D3D_OK) {
 				throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]��SetTexture( 0, NULL) ���s model="<<_model_name, hr);
			}
		}
		//�`��
		if (pMeshActor_Target->_SX == LEN_UNIT &&
		    pMeshActor_Target->_SY == LEN_UNIT &&
		    pMeshActor_Target->_SZ == LEN_UNIT)
		{
			hr = _pID3DXMesh -> DrawSubset( i ); //�Ȃ�ĕ֗��ȃ��\�b�h�I
		} else {
			//�g��k�����Ȃ���Ă��邽�߁A�J������ԂɃg�����X�t�H�[�����ꂽ��Œ��_�@���̐��K������悤�ɐݒ�i���׍��j
			GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
			hr = _pID3DXMesh -> DrawSubset( i ); //�Ȃ�ĕ֗��ȃ��\�b�h�I
			GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
		}

		if(hr != D3D_OK) {
			throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]��pID3DXMesh -> DrawSubset���s model="<<_model_name, hr);
		}

	}

	//�O��`�惂�f�������f
	GgafDx9Model::_s_modelname_lastdraw = _model_name;
	GgafGod::_iNumPlayingActor++;
	return D3D_OK;
}

void GgafDx9MeshModel::restore() {
	TRACE("GgafDx9MeshModel::restore() " <<  _model_name << " start");
	GgafDx9ModelManager::restoreMeshModel(this);
	TRACE("GgafDx9MeshModel::restore() " <<  _model_name << " end");
}

void GgafDx9MeshModel::onDeviceLost() {
	_TRACE_("GgafDx9MeshModel::onDeviceLost() " <<  _model_name << " start");
	if (_pID3DXMesh == NULL) {
		throw_GgafCriticalException("[GgafDx9MeshModel::onDeviceLost] Error! �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� Release �ł��܂���I");
	}
	LPDIRECT3DTEXTURE9 pTex;
	for( DWORD i = 0; i < _dwNumMaterials; i++) {
		pTex = _papID3DTexture9[i];
		if(pTex) {
			pTex->Release();
			pTex = NULL;
		} else {
			pTex = NULL;
		}
		//RELEASE_POSSIBLE_NULL(pTex); //�e�N�X�`���������ꍇ�����邽��
	}
	DELETEARR_IMPOSSIBLE_NULL(_papID3DTexture9);
	DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
	RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);
	_TRACE_("GgafDx9MeshModel::onDeviceLost() " <<  _model_name << " end");
}

GgafDx9MeshModel::~GgafDx9MeshModel() {
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " start");
	if (_pID3DXMesh == NULL) {
		throw_GgafCriticalException("[GgafDx9MeshModel::remove] Error! �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� Release �ł��܂���I");
	}
	LPDIRECT3DTEXTURE9 pTex;
	for( DWORD i = 0; i < _dwNumMaterials; i++) {
		pTex = _papID3DTexture9[i];
		if(pTex) {
			pTex->Release();
			pTex = NULL;
		} else {
			pTex = NULL;
		}
		//RELEASE_POSSIBLE_NULL(pTex); //�e�N�X�`���������ꍇ�����邽��
	}


	DELETEARR_IMPOSSIBLE_NULL(_papID3DTexture9);
	DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
	RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " end");
}
