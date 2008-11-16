#include "stdafx.h"

LPDIRECT3DVERTEXBUFFER9 MyLaserChip::_pIDirect3DVertexBuffer9_MyLaserChip = NULL;
DWORD MyLaserChip::_dwVertexFormat = 0;
DWORD MyLaserChip::_dwFVFSize = 0;
DWORD MyLaserChip::_dwVertexNum = 0;
int MyLaserChip::_aVertexIndexTetrahedron01_head[] = {7,13,15}; //A
int MyLaserChip::_iNum_VertexIndexTetrahedron01_head = 3;
int MyLaserChip::_aVertexIndexTetrahedron02_head[] = {10,19,22,26,27}; //B
int MyLaserChip::_iNum_VertexIndexTetrahedron02_head = 5;
int MyLaserChip::_aVertexIndexTetrahedron03_head[] = {6,16,25}; //C
int MyLaserChip::_iNum_VertexIndexTetrahedron03_head = 3;
int MyLaserChip::_aVertexIndexTetrahedron04_head[] = {4,14,20,28,29};
int MyLaserChip::_iNum_VertexIndexTetrahedron04_head = 5;
MyLaserChip::Tetrahedron* MyLaserChip::_pTetra_tail = NULL;


MyLaserChip::MyLaserChip(string prm_name, string prm_model) : DefaultDynaMeshActor(prm_name, prm_model) {

//	if (_pTetra_tail == NULL) {
//		//資料「レーザーチップ」参照
//		//A
//		_pTetra_tail->x1 = 0.612293;
//		_pTetra_tail->y1 = 0.000029;
//		_pTetra_tail->z1 = 0.0000286102;
//		//B
//		_pTetra_tail->x2 = -0.162006;
//		_pTetra_tail->y2 = 0.000011;
//		_pTetra_tail->z2 = 0.577404;
//		//C
//		_pTetra_tail->x3 = -0.16188;
//		_pTetra_tail->y3 = 0.500019;
//		_pTetra_tail->z3 = -0.288506;
//		//D
//		_pTetra_tail->x4 = -0.161881;
//		_pTetra_tail->y4 = -0.49998;
//		_pTetra_tail->z4 = -0.288506;
//	}

}

//A	-35	-10	0
//B	22	-10	0
//C	22	5	8
//D	-35	5	8
//E	36	0	0
//F	-22	0	0
//G	-35	5	-9
//H	22	5	-9


void MyLaserChip::initialize() {

	if (_pIDirect3DVertexBuffer9_MyLaserChip == NULL) {
		BYTE* pByteVertexSrc;
		_dwVertexNum = _pMeshModel->_pID3DXMesh->GetNumVertices();
		_pMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip);
		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc,0);
		//頂点フォーマットとサイズを取得
		_dwVertexFormat = _pMeshModel->_pID3DXMesh->GetFVF();
		_dwFVFSize = D3DXGetFVFVertexSize( _dwVertexFormat );

		_pTetra_tail = NEW Tetrahedron();
		D3DVECTOR* pV;
		//頂点Eの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 1) + 0 );
		_pTetra_tail->x1 = pV->x;
		_pTetra_tail->y1 = pV->y;
		_pTetra_tail->z1 = pV->z;

		_TRACE_("_pTetra_tail E ("<<_pTetra_tail->x1<<","<<_pTetra_tail->y1<<","<<_pTetra_tail->z1<<")");



		//頂点Fの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 0) + 0 );
		_pTetra_tail->x2 = pV->x;
		_pTetra_tail->y2 = pV->y;
		_pTetra_tail->z2 = pV->z;
		_TRACE_("_pTetra_tail F ("<<_pTetra_tail->x2<<","<<_pTetra_tail->y2<<","<<_pTetra_tail->z2<<")");

		//頂点Gの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 9) + 0 );
		_pTetra_tail->x3 = pV->x;
		_pTetra_tail->y3 = pV->y;
		_pTetra_tail->z3 = pV->z;
		_TRACE_("_pTetra_tail G ("<<_pTetra_tail->x3<<","<<_pTetra_tail->y3<<","<<_pTetra_tail->z3<<")");

		//頂点Hの内の一つ
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * 3) + 0 );
		_pTetra_tail->x4 = pV->x;
		_pTetra_tail->y4 = pV->y;
		_pTetra_tail->z4 = pV->z;
		_TRACE_("_pTetra_tail H ("<<_pTetra_tail->x4<<","<<_pTetra_tail->y4<<","<<_pTetra_tail->z4<<")");

	}
    _pIDirect3DVertexBuffer9_MyLaserChip->Unlock();


	_pGeoMover -> setMoveVelocity(50*1000);
	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -5000, -5000, 5000, 5000);
	_pActor_Radical = NULL;

	setBumpableOnlySelf(true);

}

void MyLaserChip::processBehavior() {
	if (switchedToPlay()) {
		//出現時処理
		setBumpableOnlySelf(true);
		setGeometry(_pActor_Radical);
		_pGeoMover -> setAxisRotAngle(AXIS_Z, _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Z]);
		_pGeoMover -> setAxisRotAngle(AXIS_Y, _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Y]);
		_pGeoMover -> setMoveAngleRzRy(
				     _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Z],
				     _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Y]
				   );
		_X_prevFrame = _pActor_Radical->_X;
		_Y_prevFrame = _pActor_Radical->_Y;
		_Z_prevFrame = _pActor_Radical->_Z;

	} else {

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
	if (getNext()->isPlaying()) {
		BYTE* pByteVertexSrc;
		MyLaserChip* pNextChip = (MyLaserChip*)getNext();

		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc,0);

		int index;
		D3DVECTOR* pV;

		float fOffsetX = ((float)(pNextChip->_X - _X )) / LEN_UNIT / PX_UNIT;
		float fOffsetY = ((float)(pNextChip->_Y - _Y )) / LEN_UNIT / PX_UNIT;
		float fOffsetZ = ((float)(pNextChip->_Z - _Z )) / LEN_UNIT / PX_UNIT;
/*
		_TRACE_("XYZ ["<<getName()<<"] ("<<_X<<","<<_Y <<","<<_Z<<")");
		_TRACE_("nextXYZ ["<<pNextChip->getName()<<"] ("<<pNextChip->_X<<","<<pNextChip->_Y <<","<<pNextChip->_Z<<")");
		_TRACE_("fOffset ("<<fOffsetX<<","<<fOffsetY<<","<<fOffsetZ<<")");
*/



		for (int i = 0; i < _iNum_VertexIndexTetrahedron01_head; i++) {
			index = _aVertexIndexTetrahedron01_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + _pTetra_tail->x1;
			pV -> y = fOffsetY + _pTetra_tail->y1;
			pV -> z = fOffsetZ + _pTetra_tail->z1;
		}

		for (int i = 0; i < _iNum_VertexIndexTetrahedron02_head; i++) {
			index = _aVertexIndexTetrahedron02_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + _pTetra_tail->x2;
			pV -> y = fOffsetY + _pTetra_tail->y2;
			pV -> z = fOffsetZ + _pTetra_tail->z2;
		}

		for (int i = 0; i < _iNum_VertexIndexTetrahedron03_head; i++) {
			index = _aVertexIndexTetrahedron03_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + _pTetra_tail->x3;
			pV -> y = fOffsetY + _pTetra_tail->y3;
			pV -> z = fOffsetZ + _pTetra_tail->z3;
		}

		for (int i = 0; i < _iNum_VertexIndexTetrahedron04_head; i++) {
			index = _aVertexIndexTetrahedron04_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + _pTetra_tail->x4;
			pV -> y = fOffsetY + _pTetra_tail->y4;
			pV -> z = fOffsetZ + _pTetra_tail->z4;
		}
		_pIDirect3DVertexBuffer9_MyLaserChip->Unlock();
	} else {
		BYTE* pByteVertexSrc;
		int index;
		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc,0);
		D3DVECTOR* pV;
		for (int i = 0; i < _iNum_VertexIndexTetrahedron01_head; i++) {
			index = _aVertexIndexTetrahedron01_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = _pTetra_tail->x1;
			pV -> y = _pTetra_tail->y1;
			pV -> z = _pTetra_tail->z1;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron02_head; i++) {
			index = _aVertexIndexTetrahedron02_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = _pTetra_tail->x2;
			pV -> y = _pTetra_tail->y2;
			pV -> z = _pTetra_tail->z2;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron03_head; i++) {
			index = _aVertexIndexTetrahedron03_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = _pTetra_tail->x3;
			pV -> y = _pTetra_tail->y3;
			pV -> z = _pTetra_tail->z3;
		}
		for (int i = 0; i < _iNum_VertexIndexTetrahedron04_head; i++) {
			index = _aVertexIndexTetrahedron04_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = _pTetra_tail->x4;
			pV -> y = _pTetra_tail->y4;
			pV -> z = _pTetra_tail->z4;
		}
		_pIDirect3DVertexBuffer9_MyLaserChip->Unlock();

	}

	GgafDx9DynaMeshActor::processDrawMain();

}


void MyLaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}



MyLaserChip::~MyLaserChip() {

}


