#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                     prm_model,
                     "LaserChipEffect",
                     "LaserChipTechnique",
                     NEW StgChecker(this) ) {
    _pStgChecker = (StgChecker*)_pChecker;


    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcher�� new ���ɐݒ肳���B
    _chip_kind = 1;
    _rev_pos_Z = 0;
    _div_pos_Z = 0;
    _ahKind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ahKind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ahKind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ahKind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ahKind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ahKind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ahKind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ahKind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
    _ahMatWorld_front[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front001" );
    _ahMatWorld_front[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front002" );
    _ahMatWorld_front[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front003" );
    _ahMatWorld_front[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front004" );
    _ahMatWorld_front[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front005" );
    _ahMatWorld_front[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front006" );
    _ahMatWorld_front[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front007" );
    _ahMatWorld_front[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front008" );
}

void LaserChip::initialize() {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _pMover->setMoveVelocity(40000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}


void LaserChip::onActive() {
    //�o����
    _chip_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
        }
    }

    _pDispatcher->_num_chip_active++;
    //���[�U�[�́A�^��������Ԃ����Ȃ̂ŁA�R�R�ōs�������v�Z�񐔂�ߖ�B
    //���dx,dy,dz�����X�V����B
    GgafDx9GeometricActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);


    if (_pChip_front != NULL) {
        processPreJudgement();

    } else {
        _rev_pos_Z = 0;
    }

}

void LaserChip::onInactive() {
    //������
    _pDispatcher->_num_chip_active--;
    //�O��̌q�����ؒf
    if (_pChip_front) {
        _pChip_front->_pChip_behind = NULL;
    }
    _pChip_front = NULL;
    if (_pChip_behind) {
        _pChip_behind->_pChip_front = NULL;
    }
    _pChip_behind = NULL;

}


void LaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivate();
    }

    //���[�U�[���  1:���� 2:���� 3:�擪 �i�������擪�͖������D��j
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActive()) {
                if (_pChip_front->_pChip_front) {
                    _chip_kind = 2; //���ԃe�N�X�`��
                } else {
                    _chip_kind = 3; //�擪�e�N�X�`��
                }
            } else {
                _chip_kind = 1; //���ˌ��̖����e�N�X�`��
            }
        } else {
            _chip_kind = 1; //�����e�N�X�`��
        }
    } else {
        _chip_kind = 4; //�����`�悵�����Ȃ�
    }

    if ((0 <= _RZ && _RZ < ANGLE90) ||
        (ANGLE270 <= _RZ && _RZ < ANGLE360) ) {
        _RX = 0;
    } else {
        _RX = ANGLE180;
    }

//    //�y���Ӂz4/15 ����
//    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
//    //processBehavior,processJudgement�� _pChip_front ���K����Ɏ��s�����B
//    //�`�掞��_pChip_front���g�p���邽�߂����Őݒ肵�Ƃ��K�v������B
//    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

void LaserChip::processDraw() {
    _draw_set_num = 1; //����`��[�x�ɁAGgafDx9MeshSetActor�̓������f�����A�����Ă���J�E���g��
    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > 8) {
                    _draw_set_num = 8;
                    break;
                }
                _pNextDrawActor= _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW�ϊ��s��
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_hMatView) �Ɏ��s���܂����B");
//    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
//    mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetInt(_h_nVertexs) �Ɏ��s���܂����B2");

    LaserChip *pDrawLaserChipActor;
    pDrawLaserChipActor = this;

    //float DBackFrom;
    //float DBackTo;
    //float DFrontFrom;
    static float DFrontTo;
    static float DLeftFrom;  //distance left from
    static float DLeftTo;    //distance left to
    static float DRightFrom; //distance right from
    static float DRightTo;   //distance right to
    static float DTopFrom;   //distance top from
    static float DTopTo;     //distance top to
    static float DBtmFrom;   //distance bottom from
    static float DBtmTo;     //distance bottom to

    static float LeftIncRate;
    static float RightIncRate;
    static float TopIncRate;
    static float BtmIncRate;
    static int kind;
    for (int i = 0; i < _draw_set_num; i++) {
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawLaserChipActor->_matWorld));
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");


        if (pDrawLaserChipActor->_pChip_front != NULL) {

             //DBackFrom = -1.0 * pDrawLaserChipActor->_fDistance_plnBack;
             //DBackTo = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnBack;
             //DFrontFrom = -1.0 * pDrawLaserChipActor->_fDistance_plnFront;
             DFrontTo   = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnFront;
             DLeftFrom  = -1.0 * pDrawLaserChipActor->_fDistance_plnLeft;
             DLeftTo    = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnLeft;
             DRightFrom = -1.0 * pDrawLaserChipActor->_fDistance_plnRight;
             DRightTo   = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnRight;
             DTopFrom   = -1.0 * pDrawLaserChipActor->_fDistance_plnTop;
             DTopTo     = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnTop;
             DBtmFrom   = -1.0 * pDrawLaserChipActor->_fDistance_plnBottom;
             DBtmTo     = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnBottom;

             LeftIncRate = DLeftFrom / DLeftTo;
             RightIncRate = DRightFrom / DRightTo;

             TopIncRate = DTopFrom / DTopTo;
             BtmIncRate = DBtmFrom / DBtmTo;

             if (LeftIncRate < RightIncRate) {
                 //��O�����Ȃ王����E���ʂɂԂ���
                 //�������Ȃ�召�t�ɂȂ��ēs���悵
                 if (DFrontTo < 0 || DLeftTo < 0 || DRightTo < 0 || DTopTo < 0 || DBtmTo < 0) {

                 } else {
                     pDrawLaserChipActor->_rev_pos_Z = 0;
                     if (RightIncRate > TopIncRate && RightIncRate > BtmIncRate) {
                         pDrawLaserChipActor->_div_pos_Z = 1;
                     } else {
                         pDrawLaserChipActor->_div_pos_Z = 0;
                     }
                 }

             } else if (LeftIncRate  > RightIncRate) {
                 //��O�����Ȃ王���䍶���ʂɂԂ���
                 //�������Ȃ�召�t�ɂȂ��ēs���悵
                 if (DFrontTo < 0 || DLeftTo < 0 || DRightTo < 0 || DTopTo < 0 || DBtmTo < 0) {

                 } else {
                     pDrawLaserChipActor->_rev_pos_Z = 1;
                     if (LeftIncRate > TopIncRate && LeftIncRate > BtmIncRate) {
                         pDrawLaserChipActor->_div_pos_Z = 1;
                     } else {
                         pDrawLaserChipActor->_div_pos_Z = 0;
                     }
                 }

             } else {
                 pDrawLaserChipActor->_rev_pos_Z = 0;
                 pDrawLaserChipActor->_div_pos_Z = 0;
             }

             kind = (pDrawLaserChipActor->_chip_kind) +
                    (pDrawLaserChipActor->_rev_pos_Z*10) +
                    (pDrawLaserChipActor->_div_pos_Z*100);
             //�e�N�X�`�����̃`�b�v�̎��
             hr = pID3DXEffect->SetInt(_ahKind[i], kind);
             mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");

             hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_pChip_front->_matWorld));
             mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B1");

        } else {
            //�e�N�X�`�����
            hr = pID3DXEffect->SetInt(_ahKind[i], pDrawLaserChipActor->_chip_kind);
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");

            hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_matWorld) ); //�擪���Ȃ��̂Ŏ��M��_matWorld
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B2");
        }
        pDrawLaserChipActor = (LaserChip*)(pDrawLaserChipActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }

    _pMeshSetModel->draw(this);
}

void LaserChip::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);

}

