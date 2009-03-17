#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

LPDIRECT3DVERTEXBUFFER9 MyLaserChip2::_pIDirect3DVertexBuffer9_MyLaserChip2 = NULL;
DWORD MyLaserChip2::_dwVertexFormat = 0;
DWORD MyLaserChip2::_dwFVFSize = 0;
DWORD MyLaserChip2::_dwVertexNum = 0;
int MyLaserChip2::_aVertexIndexTetrahedron_A[] = {7, 13, 15}; //A
int MyLaserChip2::_iNum_VertexIndexTetrahedron_A = 3;
int MyLaserChip2::_aVertexIndexTetrahedron_B[] = {10, 19, 22, 26, 27}; //B
int MyLaserChip2::_iNum_VertexIndexTetrahedron_B = 5;
int MyLaserChip2::_aVertexIndexTetrahedron_C[] = {6, 16, 25}; //C
int MyLaserChip2::_iNum_VertexIndexTetrahedron_C = 3;
int MyLaserChip2::_aVertexIndexTetrahedron_D[] = {4, 14, 20, 28, 29};
int MyLaserChip2::_iNum_VertexIndexTetrahedron_D = 5;
MyLaserChip2::Vertex* MyLaserChip2::_paLaserChipVertex = NULL;
MyLaserChip2::Tetrahedron* MyLaserChip2::_pTetra_EFGH = NULL;

MyLaserChip2::MyLaserChip2(const char* prm_name) : DefaultDynaD3DXMeshActor(prm_name, "m/laserchip9") {
    _class_name = "MyLaserChip2";
    //_dwFrame_switchedToActFlg = 0;
}

/*
 頂点1	0	F
 頂点2	1	E
 頂点3	2	E
 頂点4	3	H
 頂点5	4	D
 頂点6	5	G
 頂点7	6	C
 頂点8	7	A
 頂点9	8	E
 頂点10	9	G
 頂点11	10	B
 頂点12	11	F
 頂点13	12	H
 頂点14	13	A
 頂点15	14	D
 頂点16	15	A
 頂点17	16	C
 頂点18	17	G
 頂点19	18	F
 頂点20	19	B
 */

void MyLaserChip2::initialize() {
    if (MyLaserChip2::_paLaserChipVertex == NULL) {
        D3DVECTOR* pV;
        BYTE* pByteVertexSrc;
        _dwVertexNum = _pD3DXMeshModel->_pID3DXMesh->GetNumVertices();
        if (_dwVertexNum != 20) {
            _TRACE_("MyLaserChip2::initialize 想定外のレーザーチップ");
        }
        _pD3DXMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip2);
        _pIDirect3DVertexBuffer9_MyLaserChip2->Lock(0, 0, (void**)&pByteVertexSrc, 0);
        //頂点フォーマットとサイズを取得
        _dwVertexFormat = _pD3DXMeshModel->_pID3DXMesh->GetFVF();
        _dwFVFSize = D3DXGetFVFVertexSize(_dwVertexFormat);
        _pTetra_EFGH = NEW Tetrahedron();

        //頂点Eの内の一つ
        pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * 1) + 0);
        _pTetra_EFGH->Ex = pV->x;
        _pTetra_EFGH->Ey = pV->y;
        _pTetra_EFGH->Ez = pV->z;
        //頂点Fの内の一つ
        pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * 0) + 0);
        _pTetra_EFGH->Fx = pV->x;
        _pTetra_EFGH->Fy = pV->y;
        _pTetra_EFGH->Fz = pV->z;
        //頂点Gの内の一つ
        pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * 9) + 0);
        _pTetra_EFGH->Gx = pV->x;
        _pTetra_EFGH->Gy = pV->y;
        _pTetra_EFGH->Gz = pV->z;
        //頂点Hの内の一つ
        pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * 3) + 0);
        _pTetra_EFGH->Hx = pV->x;
        _pTetra_EFGH->Hy = pV->y;
        _pTetra_EFGH->Hz = pV->z;

        _paLaserChipVertex = NEW Vertex[20];
		for(DWORD i = 0; i < _dwVertexNum; i++){
            pV = (D3DVECTOR*)( pByteVertexSrc + (_dwFVFSize * i) + 0 );
            _paLaserChipVertex[i].x = pV->x;
            _paLaserChipVertex[i].y = pV->y;
            _paLaserChipVertex[i].z = pV->z;
            _TRACE_("MyLaserChip2 頂点"<<(i+1)<<":("<<(pV->x)<<","<<(pV->y)<<","<<(pV->z)<<")");
        }
        _pIDirect3DVertexBuffer9_MyLaserChip2->Unlock();
    //_pIDirect3DVertexBuffer9_MyLaserChip2 = NULL;
    }

    _pGeoMover->setMoveVelocity(64*1000);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -1000, -1000, -1000, 1000, 1000, 1000);
    //	_pChecker->setHitAreaBox(1, -1000, -1000, -1000, 1000, 1000, 1000);
    _pActor_Radical = NULL;

    setBumpableAlone(false);
    //_SX = 10*1000; _SY=10*1000; _SZ=10*1000;
}

void MyLaserChip2::processBehavior() {
    if (switchedToAct()) {
        //出現時処理
        setBumpableAlone(true);
        setGeometry(_pActor_Radical);
        _pGeoMover->setRzRyMoveAngle(_pActor_Radical->_pGeoMover->_angRot[AXIS_Z],
                                     _pActor_Radical->_pGeoMover->_angRot[AXIS_Y]);
        _X_prevFrame = _pActor_Radical->_X;
        _Y_prevFrame = _pActor_Radical->_Y;
        _Z_prevFrame = _pActor_Radical->_Z;
        return;
    }

    //座標に反映
    _pGeoMover->behave();

    _X += (_pActor_Radical->_X - _X_prevFrame);
    _Y += (_pActor_Radical->_Y - _Y_prevFrame);
    _Z += (_pActor_Radical->_Z - _Z_prevFrame);
    _X_prevFrame = _pActor_Radical->_X;
    _Y_prevFrame = _pActor_Radical->_Y;
    _Z_prevFrame = _pActor_Radical->_Z;

}

void MyLaserChip2::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (isOffScreen()) {
        inact();
    }
}

void MyLaserChip2::processDrawMain() {
    //通常時
    static int index;
    static D3DVECTOR* pV;
    static BYTE* pByteVertexSrc;
    static float fOffsetX, fOffsetY, fOffsetZ;
    static MyLaserChip2* pNextChip;
    static MyLaserChip2* pPrevChip;
    pNextChip = getNext();
    pPrevChip = getPrev();

    fOffsetX = (pPrevChip->_X - _X) / (float)(LEN_UNIT);
    fOffsetY = (pPrevChip->_Y - _Y) / (float)(LEN_UNIT);
    fOffsetZ = (pPrevChip->_Z - _Z) / (float)(LEN_UNIT);

    if (_pIDirect3DVertexBuffer9_MyLaserChip2 != NULL) {
        //連続しているか
        if (pPrevChip->isPlaying()) {
            //連続しているので、Prev（一つ前方）自分の正四面体頂点ABCDを、Prev（一つ前方）のChipの正四面体頂点EFGHに重ねる。


            //		_pD3DXMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip2);
            _pIDirect3DVertexBuffer9_MyLaserChip2->Lock(0, 0, (void**)&pByteVertexSrc, D3DLOCK_DISCARD); //D3DLOCK_DISCARD にしたいのぉ

            //頂点F
            index = 0;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点E
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点E
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点H
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点D
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Hx;
            pV->y = fOffsetY + _pTetra_EFGH->Hy;
            pV->z = fOffsetZ + _pTetra_EFGH->Hz;

            //頂点G
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点C
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Gx;
            pV->y = fOffsetY + _pTetra_EFGH->Gy;
            pV->z = fOffsetZ + _pTetra_EFGH->Gz;

            //頂点A
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Ex;
            pV->y = fOffsetY + _pTetra_EFGH->Ey;
            pV->z = fOffsetZ + _pTetra_EFGH->Ez;

            //頂点E
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点G
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点B
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Fx;
            pV->y = fOffsetY + _pTetra_EFGH->Fy;
            pV->z = fOffsetZ + _pTetra_EFGH->Fz;

            //頂点F
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点H
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点A
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Ex;
            pV->y = fOffsetY + _pTetra_EFGH->Ey;
            pV->z = fOffsetZ + _pTetra_EFGH->Ez;

            //頂点D
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Hx;
            pV->y = fOffsetY + _pTetra_EFGH->Hy;
            pV->z = fOffsetZ + _pTetra_EFGH->Hz;

            //頂点A
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Ex;
            pV->y = fOffsetY + _pTetra_EFGH->Ey;
            pV->z = fOffsetZ + _pTetra_EFGH->Ez;

            //頂点C
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Gx;
            pV->y = fOffsetY + _pTetra_EFGH->Gy;
            pV->z = fOffsetZ + _pTetra_EFGH->Gz;

            //頂点G
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点F
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //頂点B
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Fx;
            pV->y = fOffsetY + _pTetra_EFGH->Fy;
            pV->z = fOffsetZ + _pTetra_EFGH->Fz;

            _pIDirect3DVertexBuffer9_MyLaserChip2->Unlock();

        } else {
            //		//連続してないので、こじんまりしとく。
            _pIDirect3DVertexBuffer9_MyLaserChip2->Lock(0, 0, (void**)&pByteVertexSrc, D3DLOCK_DISCARD); //D3DLOCK_DISCARD にしたいのぉ
            for (int i = 0; i < 20; i++) {
                pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * i) + 0);
                pV->x = _paLaserChipVertex[i].x;
                pV->y = _paLaserChipVertex[i].y;
                pV->z = _paLaserChipVertex[i].z;

            }
            _pIDirect3DVertexBuffer9_MyLaserChip2->Unlock();
        }
    }

    //	static int centerX, centerY, centerZ;
    //	if (pNextChip->isPlaying() && _dwFrame_switchedToActFlg+1 == pNextChip->_dwFrame_switchedToActFlg) {
    //		centerX = (_X - pNextChip->_X) / 2;
    //		centerY = (_Y - pNextChip->_Y) / 2;
    //		centerZ = (_Z - pNextChip->_Z) / 2;
    //		_pChecker->setHitAreaBox(
    //						1,
    //						centerX - 10000,
    //						centerY - 10000,
    //						centerZ - 10000,
    //						centerX + 10000,
    //						centerY + 10000,
    //						centerZ + 10000
    //				   ); //中間の当たり判定
    //		_pChecker->getHitAreaBoxs()->enable(1);
    //	} else {
    //		_pChecker->getHitAreaBoxs()->disable(1);
    //	}

    GgafDx9DynaD3DXMeshActor::processDrawMain();
}

void MyLaserChip2::processHappen(int prm_no) {
    switch (prm_no) {

        case GGAF_EVENT_ON_DEVICE_LOST:
            RELEASE_POSSIBLE_NULL(_pIDirect3DVertexBuffer9_MyLaserChip2);
            break;
        case GGAF_EVENT_DEVICE_LOST_RESTORE:
            if (_pIDirect3DVertexBuffer9_MyLaserChip2 == NULL) {
                _pD3DXMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip2);
            }
            break;
        default:
            break;
    }

}

void MyLaserChip2::processOnHit(GgafActor* prm_pActor_Opponent) {
    inact();
}

//void MyLaserChip2::onAct() {
//    //出現時
//    ((MyLaserChipRotationActor*)getParent())->_iNumActiveChip++;
//}
void MyLaserChip2::onInact() {
    //消失時
    ((MyLaserChipRotationActor*)getParent())->_iNumActiveChip--;
}


MyLaserChip2::~MyLaserChip2() {
    //RELEASE_POSSIBLE_NULL(_pIDirect3DVertexBuffer9_MyLaserChip2);//モデル側でRELEASEされるので不要
    DELETEARR_POSSIBLE_NULL(_paLaserChipVertex);
    DELETE_POSSIBLE_NULL(_pTetra_EFGH);
}

