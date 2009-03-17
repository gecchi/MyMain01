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
 ���_1	0	F
 ���_2	1	E
 ���_3	2	E
 ���_4	3	H
 ���_5	4	D
 ���_6	5	G
 ���_7	6	C
 ���_8	7	A
 ���_9	8	E
 ���_10	9	G
 ���_11	10	B
 ���_12	11	F
 ���_13	12	H
 ���_14	13	A
 ���_15	14	D
 ���_16	15	A
 ���_17	16	C
 ���_18	17	G
 ���_19	18	F
 ���_20	19	B
 */

void MyLaserChip2::initialize() {
    if (MyLaserChip2::_paLaserChipVertex == NULL) {
        D3DVECTOR* pV;
        BYTE* pByteVertexSrc;
        _dwVertexNum = _pD3DXMeshModel->_pID3DXMesh->GetNumVertices();
        if (_dwVertexNum != 20) {
            _TRACE_("MyLaserChip2::initialize �z��O�̃��[�U�[�`�b�v");
        }
        _pD3DXMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip2);
        _pIDirect3DVertexBuffer9_MyLaserChip2->Lock(0, 0, (void**)&pByteVertexSrc, 0);
        //���_�t�H�[�}�b�g�ƃT�C�Y���擾
        _dwVertexFormat = _pD3DXMeshModel->_pID3DXMesh->GetFVF();
        _dwFVFSize = D3DXGetFVFVertexSize(_dwVertexFormat);
        _pTetra_EFGH = NEW Tetrahedron();

        //���_E�̓��̈��
        pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * 1) + 0);
        _pTetra_EFGH->Ex = pV->x;
        _pTetra_EFGH->Ey = pV->y;
        _pTetra_EFGH->Ez = pV->z;
        //���_F�̓��̈��
        pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * 0) + 0);
        _pTetra_EFGH->Fx = pV->x;
        _pTetra_EFGH->Fy = pV->y;
        _pTetra_EFGH->Fz = pV->z;
        //���_G�̓��̈��
        pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * 9) + 0);
        _pTetra_EFGH->Gx = pV->x;
        _pTetra_EFGH->Gy = pV->y;
        _pTetra_EFGH->Gz = pV->z;
        //���_H�̓��̈��
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
            _TRACE_("MyLaserChip2 ���_"<<(i+1)<<":("<<(pV->x)<<","<<(pV->y)<<","<<(pV->z)<<")");
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
        //�o��������
        setBumpableAlone(true);
        setGeometry(_pActor_Radical);
        _pGeoMover->setRzRyMoveAngle(_pActor_Radical->_pGeoMover->_angRot[AXIS_Z],
                                     _pActor_Radical->_pGeoMover->_angRot[AXIS_Y]);
        _X_prevFrame = _pActor_Radical->_X;
        _Y_prevFrame = _pActor_Radical->_Y;
        _Z_prevFrame = _pActor_Radical->_Z;
        return;
    }

    //���W�ɔ��f
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
    //�ʏ펞
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
        //�A�����Ă��邩
        if (pPrevChip->isPlaying()) {
            //�A�����Ă���̂ŁAPrev�i��O���j�����̐��l�ʑ̒��_ABCD���APrev�i��O���j��Chip�̐��l�ʑ̒��_EFGH�ɏd�˂�B


            //		_pD3DXMeshModel->_pID3DXMesh->GetVertexBuffer(&_pIDirect3DVertexBuffer9_MyLaserChip2);
            _pIDirect3DVertexBuffer9_MyLaserChip2->Lock(0, 0, (void**)&pByteVertexSrc, D3DLOCK_DISCARD); //D3DLOCK_DISCARD �ɂ������̂�

            //���_F
            index = 0;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_E
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_E
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_H
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_D
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Hx;
            pV->y = fOffsetY + _pTetra_EFGH->Hy;
            pV->z = fOffsetZ + _pTetra_EFGH->Hz;

            //���_G
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_C
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Gx;
            pV->y = fOffsetY + _pTetra_EFGH->Gy;
            pV->z = fOffsetZ + _pTetra_EFGH->Gz;

            //���_A
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Ex;
            pV->y = fOffsetY + _pTetra_EFGH->Ey;
            pV->z = fOffsetZ + _pTetra_EFGH->Ez;

            //���_E
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_G
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_B
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Fx;
            pV->y = fOffsetY + _pTetra_EFGH->Fy;
            pV->z = fOffsetZ + _pTetra_EFGH->Fz;

            //���_F
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_H
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_A
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Ex;
            pV->y = fOffsetY + _pTetra_EFGH->Ey;
            pV->z = fOffsetZ + _pTetra_EFGH->Ez;

            //���_D
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Hx;
            pV->y = fOffsetY + _pTetra_EFGH->Hy;
            pV->z = fOffsetZ + _pTetra_EFGH->Hz;

            //���_A
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Ex;
            pV->y = fOffsetY + _pTetra_EFGH->Ey;
            pV->z = fOffsetZ + _pTetra_EFGH->Ez;

            //���_C
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Gx;
            pV->y = fOffsetY + _pTetra_EFGH->Gy;
            pV->z = fOffsetZ + _pTetra_EFGH->Gz;

            //���_G
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_F
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = _paLaserChipVertex[index].x;
            pV->y = _paLaserChipVertex[index].y;
            pV->z = _paLaserChipVertex[index].z;

            //���_B
            index++;
            pV = (D3DVECTOR*)(pByteVertexSrc + (_dwFVFSize * index) + 0);
            pV->x = fOffsetX + _pTetra_EFGH->Fx;
            pV->y = fOffsetY + _pTetra_EFGH->Fy;
            pV->z = fOffsetZ + _pTetra_EFGH->Fz;

            _pIDirect3DVertexBuffer9_MyLaserChip2->Unlock();

        } else {
            //		//�A�����ĂȂ��̂ŁA������܂肵�Ƃ��B
            _pIDirect3DVertexBuffer9_MyLaserChip2->Lock(0, 0, (void**)&pByteVertexSrc, D3DLOCK_DISCARD); //D3DLOCK_DISCARD �ɂ������̂�
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
    //				   ); //���Ԃ̓����蔻��
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
//    //�o����
//    ((MyLaserChipRotationActor*)getParent())->_iNumActiveChip++;
//}
void MyLaserChip2::onInact() {
    //������
    ((MyLaserChipRotationActor*)getParent())->_iNumActiveChip--;
}


MyLaserChip2::~MyLaserChip2() {
    //RELEASE_POSSIBLE_NULL(_pIDirect3DVertexBuffer9_MyLaserChip2);//���f������RELEASE�����̂ŕs�v
    DELETEARR_POSSIBLE_NULL(_paLaserChipVertex);
    DELETE_POSSIBLE_NULL(_pTetra_EFGH);
}

