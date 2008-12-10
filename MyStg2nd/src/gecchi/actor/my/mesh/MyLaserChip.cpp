#include "stdafx.h"

LPDIRECT3DVERTEXBUFFER9 MyLaserChip::_pIDirect3DVertexBuffer9_MyLaserChip = NULL;
DWORD MyLaserChip::_dwVertexFormat = 0;
DWORD MyLaserChip::_dwFVFSize = 0;
DWORD MyLaserChip::_dwVertexNum = 0;
int MyLaserChip::_aVertexIndexTetrahedron_A[] = {7,13,15}; //A
int MyLaserChip::_iNum_VertexIndexTetrahedron_A = 3;
int MyLaserChip::_aVertexIndexTetrahedron_B[] = {10,19,22,26,27}; //B
int MyLaserChip::_iNum_VertexIndexTetrahedron_B = 5;
int MyLaserChip::_aVertexIndexTetrahedron_C[] = {6,16,25}; //C
int MyLaserChip::_iNum_VertexIndexTetrahedron_C = 3;
int MyLaserChip::_aVertexIndexTetrahedron_D[] = {4,14,20,28,29};
int MyLaserChip::_iNum_VertexIndexTetrahedron_D = 5;
MyLaserChip::Tetrahedron* MyLaserChip::_pTetra_EFGH = NULL;


MyLaserChip::MyLaserChip(string prm_name, string prm_model) : DefaultDynaMeshActor(prm_name, prm_model) {
	_class_name = "MyLaserChip";
	_dwFrame_switchedToPlay = 0;
}

void MyLaserChip::initialize() {
	if (_pIDirect3DVertexBuffer9_MyLaserChip == NULL) {
		D3DVECTOR* pV;
		BYTE* pByteVertexSrc;
		_dwVertexNum = _pMeshModel->_pID3DXMesh->GetNumVertices();
		_pMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip);
		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc,0);
		//頂点フォーマットとサイズを取得
		_dwVertexFormat = _pMeshModel->_pID3DXMesh->GetFVF();
		_dwFVFSize = D3DXGetFVFVertexSize( _dwVertexFormat );
		_pTetra_EFGH = NEW Tetrahedron();

		//頂点Eの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 1) + 0 );
		_pTetra_EFGH->Ex = pV->x;
		_pTetra_EFGH->Ey = pV->y;
		_pTetra_EFGH->Ez = pV->z;
		//頂点Fの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 0) + 0 );
		_pTetra_EFGH->Fx = pV->x;
		_pTetra_EFGH->Fy = pV->y;
		_pTetra_EFGH->Fz = pV->z;
		//頂点Gの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 9) + 0 );
		_pTetra_EFGH->Gx = pV->x;
		_pTetra_EFGH->Gy = pV->y;
		_pTetra_EFGH->Gz = pV->z;
		//頂点Hの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 3) + 0 );
		_pTetra_EFGH->Hx = pV->x;
		_pTetra_EFGH->Hy = pV->y;
		_pTetra_EFGH->Hz = pV->z;
		for(int i = 0; i < _dwVertexNum; i++){
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * i) + 0 );
			_TRACE_("MyLaserChip 頂点"<<(i+1)<<":("<<(pV->x)<<","<<(pV->y)<<","<<(pV->z)<<")");
		}
		_pIDirect3DVertexBuffer9_MyLaserChip->Unlock();
	}

	_pGeoMover -> setMoveVelocity(20*1000);
	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -5000, -5000, 5000, 5000);
	_pActor_Radical = NULL;

	setBumpableOnlySelf(false);
	//_SX = 10*1000; _SY=10*1000; _SZ=10*1000;
}

void MyLaserChip::processBehavior() {
	if (switchedToPlay()) {
		//出現時処理
		setBumpableOnlySelf(true);
		setGeometry(_pActor_Radical);
		_pGeoMover -> setMoveAngleRzRy(
				     _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Z],
				     _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Y]
				   );
		_X_prevFrame = _pActor_Radical->_X;
		_Y_prevFrame = _pActor_Radical->_Y;
		_Z_prevFrame = _pActor_Radical->_Z;
	}

	//座標に反映
	_pGeoMover -> behave();

	_X += (_pActor_Radical->_X - _X_prevFrame);
	_Y += (_pActor_Radical->_Y - _Y_prevFrame);
	_Z += (_pActor_Radical->_Z - _Z_prevFrame);
	_X_prevFrame = _pActor_Radical->_X;
	_Y_prevFrame = _pActor_Radical->_Y;
	_Z_prevFrame = _pActor_Radical->_Z;

}

void MyLaserChip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		declareStop();
	}
}

/**
 * ＜OverRide です＞
 */
void MyLaserChip::processDrawMain() {
	//通常時
	int index;
	D3DVECTOR* pV;
	BYTE* pByteVertexSrc;

	if (getPrev()->isPlaying() && _dwFrame_switchedToPlay-1 == getPrev()->_dwFrame_switchedToPlay) {
		//自分の正四面体頂点ABCDを、一つ前（一つ先）直近のChipの正四面体頂点EFGHに重ねる。
		MyLaserChip* pPrevChip = getPrev();
		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc, 0);
		float fOffsetX = (pPrevChip->_X - _X ) / (float)(LEN_UNIT);
		float fOffsetY = (pPrevChip->_Y - _Y ) / (float)(LEN_UNIT);
		float fOffsetZ = (pPrevChip->_Z - _Z ) / (float)(LEN_UNIT);

		for (int i = 0; i < _iNum_VertexIndexTetrahedron_A; i++) {
			index = _aVertexIndexTetrahedron_A[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = fOffsetX + _pTetra_EFGH->Ex;
			pV->y = fOffsetY + _pTetra_EFGH->Ey;
			pV->z = fOffsetZ + _pTetra_EFGH->Ez;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron_B; i++) {
			index = _aVertexIndexTetrahedron_B[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = fOffsetX + _pTetra_EFGH->Fx;
			pV->y = fOffsetY + _pTetra_EFGH->Fy;
			pV->z = fOffsetZ + _pTetra_EFGH->Fz;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron_C; i++) {
			index = _aVertexIndexTetrahedron_C[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = fOffsetX + _pTetra_EFGH->Gx;
			pV->y = fOffsetY + _pTetra_EFGH->Gy;
			pV->z = fOffsetZ + _pTetra_EFGH->Gz;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron_D; i++) {
			index = _aVertexIndexTetrahedron_D[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = fOffsetX + _pTetra_EFGH->Hx;
			pV->y = fOffsetY + _pTetra_EFGH->Hy;
			pV->z = fOffsetZ + _pTetra_EFGH->Hz;
		}
		_pIDirect3DVertexBuffer9_MyLaserChip->Unlock();

	} else {

		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc,0);
		for (int i = 0; i < _iNum_VertexIndexTetrahedron_A; i++) {
			index = _aVertexIndexTetrahedron_A[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = _pTetra_EFGH->Ex;
			pV->y = _pTetra_EFGH->Ey;
			pV->z = _pTetra_EFGH->Ez;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron_B; i++) {
			index = _aVertexIndexTetrahedron_B[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = _pTetra_EFGH->Fx;
			pV->y = _pTetra_EFGH->Fy;
			pV->z = _pTetra_EFGH->Fz;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron_C; i++) {
			index = _aVertexIndexTetrahedron_C[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = _pTetra_EFGH->Gx;
			pV->y = _pTetra_EFGH->Gy;
			pV->z = _pTetra_EFGH->Gz;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron_D; i++) {
			index = _aVertexIndexTetrahedron_D[i];
			if (_dwVertexNum < index) {
				continue;
			}
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize*index) + 0 );
			pV->x = _pTetra_EFGH->Hx;
			pV->y = _pTetra_EFGH->Hy;
			pV->z = _pTetra_EFGH->Hz;
		}
		_pIDirect3DVertexBuffer9_MyLaserChip->Unlock();
	}
	GgafDx9DynaMeshActor::processDrawMain();
}

void MyLaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareStop();
}

MyLaserChip::~MyLaserChip() {
}


