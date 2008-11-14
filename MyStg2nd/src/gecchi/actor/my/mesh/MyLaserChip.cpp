#include "stdafx.h"

LPDIRECT3DVERTEXBUFFER9 MyLaserChip::_pIDirect3DVertexBuffer9_MyLaserChip = NULL;
DWORD MyLaserChip::_dwVertexFormat = 0;
DWORD MyLaserChip::_dwFVFSize = 0;
DWORD MyLaserChip::_dwVertexNum = 0;
int MyLaserChip::_aVertexIndexTetrahedron01_head[] = {0};
int MyLaserChip::_aVertexIndexTetrahedron02_head[] = {0};
int MyLaserChip::_aVertexIndexTetrahedron03_head[] = {0};
int MyLaserChip::_aVertexIndexTetrahedron04_head[] = {0};
int MyLaserChip::_aVertexIndexTetrahedron01_tail[] = {0};
int MyLaserChip::_aVertexIndexTetrahedron02_tail[] = {0};
int MyLaserChip::_aVertexIndexTetrahedron03_tail[] = {0};
int MyLaserChip::_aVertexIndexTetrahedron04_tail[] = {0};


MyLaserChip::MyLaserChip(string prm_name, string prm_model) : DefaultMeshActor(prm_name, prm_model) {

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
	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);

	if (_pIDirect3DVertexBuffer9_MyLaserChip == NULL) {
		BYTE* pByteVertexSrc;
		_dwVertexNum = _pMeshModel->_pID3DXMesh->GetNumVertices();
		_pMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip);
		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc,0);
		//頂点フォーマットとサイズを取得
		_dwVertexFormat = _pMeshModel->_pID3DXMesh->GetFVF();
		_dwFVFSize = D3DXGetFVFVertexSize( _dwVertexFormat );

		D3DVECTOR* pV;
		int index = _aVertexIndexTetrahedron01_tail[0];
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
		_tet_tail.x1 = pV->x;
		_tet_tail.y1 = pV->y;
		_tet_tail.z1 = pV->z;

		index = _aVertexIndexTetrahedron02_tail[0];
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
		_tet_tail.x2 = pV->x;
		_tet_tail.y2 = pV->y;
		_tet_tail.z2 = pV->z;

		index = _aVertexIndexTetrahedron03_tail[0];
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
		_tet_tail.x3 = pV->x;
		_tet_tail.y3 = pV->y;
		_tet_tail.z3 = pV->z;

		index = _aVertexIndexTetrahedron04_tail[0];
		pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
		_tet_tail.x4 = pV->x;
		_tet_tail.y4 = pV->y;
		_tet_tail.z4 = pV->z;

	}
    _pIDirect3DVertexBuffer9_MyLaserChip->Unlock();

}

void MyLaserChip::processBehavior() {


	if (getNext()->isPlaying()) {
		BYTE* pByteVertexSrc;
		MyLaserChip* pNextChip = (MyLaserChip*)getNext();

		_pIDirect3DVertexBuffer9_MyLaserChip->Lock(0, 0, (void**)&pByteVertexSrc,0);

		int index;
		D3DVECTOR* pV;
		float fOffsetX = (pNextChip->_X - _X ) / LEN_UNIT;
		float fOffsetY = (pNextChip->_Y - _Y ) / LEN_UNIT;
		float fOffsetZ = (pNextChip->_Z - _Z ) / LEN_UNIT;

		for (int i = 0; i < 9999; i++) {
			index = _aVertexIndexTetrahedron01_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + pNextChip->_tet_tail.x1;
			pV -> y = fOffsetY + pNextChip->_tet_tail.y1;
			pV -> z = fOffsetZ + pNextChip->_tet_tail.z1;
		}

		for (int i = 0; i < 9999; i++) {
			index = _aVertexIndexTetrahedron02_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + pNextChip->_tet_tail.x2;
			pV -> y = fOffsetY + pNextChip->_tet_tail.y2;
			pV -> z = fOffsetZ + pNextChip->_tet_tail.z2;
		}

		for (int i = 0; i < 9999; i++) {
			index = _aVertexIndexTetrahedron03_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + pNextChip->_tet_tail.x3;
			pV -> y = fOffsetY + pNextChip->_tet_tail.y3;
			pV -> z = fOffsetZ + pNextChip->_tet_tail.z3;
		}

		for (int i = 0; i < 9999; i++) {
			index = _aVertexIndexTetrahedron04_head[i];
			pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * index) + 0 );
			pV -> x = fOffsetX + pNextChip->_tet_tail.x4;
			pV -> y = fOffsetY + pNextChip->_tet_tail.y4;
			pV -> z = fOffsetZ + pNextChip->_tet_tail.z4;
		}


		_pIDirect3DVertexBuffer9_MyLaserChip->Unlock();


	}


	//座標に反映
	_pGeoMover -> behave();
}




void MyLaserChip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}


void MyLaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}



MyLaserChip::~MyLaserChip() {

}


