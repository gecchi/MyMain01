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
    _pMover = NEW GgafDx9GeometryMover(this);


    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcher�� new ���ɐݒ肳���B
    _chiptex_kind = 1;
    _ahKind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ahKind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ahKind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ahKind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ahKind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ahKind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ahKind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ahKind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
    _ahRevPosZ[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ001" );
    _ahRevPosZ[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ002" );
    _ahRevPosZ[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ003" );
    _ahRevPosZ[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ004" );
    _ahRevPosZ[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ005" );
    _ahRevPosZ[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ006" );
    _ahRevPosZ[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ007" );
    _ahRevPosZ[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ008" );
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
    _chiptex_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
        }
    }

    _pDispatcher->_num_chip_active++;
    //���[�U�[�́A�^��������Ԃ����Ȃ̂ŁA�R�R�ōs�������v�Z�񐔂�ߖ�B
    //���dx,dy,dz�����X�V����B
    GgafDx9GeometricActor::getWorldMatrix_ScRzRyMv(this, _matWorld);
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

void LaserChip::processBehavior() {

    //���W�ɔ��f
    _pMover->behave();
/*
    //���Ԓn�_�ɂ������蔻��
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pStgChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //���Ԃ̓����蔻��
      _pStgChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pStgChecker->getHitAreaBoxs()->disable(1);

    }
*/

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
                    _chiptex_kind = 2; //���ԃe�N�X�`��
                } else {
                    _chiptex_kind = 3; //�擪�e�N�X�`��
                }
            } else {
                _chiptex_kind = 1; //���ˌ��̖����e�N�X�`��
            }
        } else {
            _chiptex_kind = 1; //�����e�N�X�`��
        }
    } else {
        _chiptex_kind = 4; //�����`�悵�����Ȃ�
    }

    //�y���Ӂz4/15 ����
    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
    //processBehavior,processJudgement�� _pChip_front ���K����Ɏ��s�����B
    //�`�掞��_pChip_front���g�p���邽�߂����Őݒ肵�Ƃ��K�v������B
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

void LaserChip::processDraw() {
    _draw_set_num = 1; //����`��[�x�ɁAGgafDx9MeshSetActor�̓������f�����A�����Ă���J�E���g��
    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            GgafDx9Model* pGgafDx9Model =  _pNextDrawActor->_pGgafDx9Model;
            if (pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
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
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetInt(_h_nVertexs) �Ɏ��s���܂����B2");

    LaserChip *pDrawLaserChipActor;
    pDrawLaserChipActor = this;

    int rev_pos_Z; //true = ���_��Z��-1���悸��Bfalse = �������Ȃ�
    float DBF;
    float DBT;
    float DLF; //distance left from
    float DLT; //distance left to
    float DRF; //distance right from
    float DRT; //distance right to

    float DTF; //distance top from
    float DTT; //distance top to
    float DBoF; //distance bottom from
    float DBoT; //distance bottom to





    for (int i = 0; i < _draw_set_num; i++) {
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawLaserChipActor->_matWorld));
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

        //�e�N�X�`�����
        hr = pID3DXEffect->SetInt(_ahKind[i], pDrawLaserChipActor->_chiptex_kind);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");

        if (pDrawLaserChipActor->_pChip_front != NULL) {
            hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_pChip_front->_matWorld));
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B1");

            //��O�Ȍ����ȃ`�b�v���A�������ȃ`�b�v��
            //���g�̍��W �` �����䉜�� �̋���(D1)�A�O���`�b�v���W �` �����䉜�� �̋���(D2) ���r����
            //D1 > D2 �Ȃ�Ύ�O�Ȍ����ȃ`�b�v�B
            //D1 < D2 �Ȃ�Ή������ȃ`�b�v�B
            //D1 = D2 �Ȃ�ΐ^��

            DBF = -1.0 * pDrawLaserChipActor->_fDistance_plnBack;
            DBT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnBack;

            DLF = -1.0 * pDrawLaserChipActor->_fDistance_plnLeft;
            DLT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnLeft;
            DRF = -1.0 * pDrawLaserChipActor->_fDistance_plnRight;
            DRT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnRight;
            DTF = -1.0 * pDrawLaserChipActor->_fDistance_plnTop;
            DTT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnTop;

            DBoF = -1.0 * pDrawLaserChipActor->_fDistance_plnBottom;
            DBoT = -1.0 * pDrawLaserChipActor->_pChip_front->_fDistance_plnBottom;

//            if (GgafDx9Util::abs(DTT - DTF) >  GgafDx9Util::abs(DLT - DLF)) {
//                //���Ă�
//                rev_pos_Z = true;
//            } else {
//                rev_pos_Z = false;
//            }

            //  DLF / DLT  = DRF / DRT �ƂȂ����ꍇ�A
            // ���_��ʂ�̂���Ȃ��̂��H
            //  DLF / DLT  < DRF / DRT �ƂȂ����ꍇ�A
            // ���̕ǂɂԂ���̂���Ȃ��̂��H
            //  DLF / DLT  < DRF / DRT �ƂȂ����ꍇ�A
            // �E�̕ǂɂԂ���̂���Ȃ��̂��H
            float DLr = DLF / DLT;
            float DRr = DRF / DRT;

            float DTr = DTF / DTT;
            float DBor = DBoF / DBoT;

//            _TRACE_("DLF="<<DLF<<",DLT="<<DLT<<",   DL="<<DL<<"");
//            _TRACE_("DRF="<<DRF<<",DRT="<<DRT<<",   DR="<<DR<<"");
//            if (DL < 0) {
//                DL = 0;
//            }
//            if (DR < 0) {
//                DR = 0;
//            }




            if (DLr < DRr) {
                //��O�����Ȃ王����E���ʂɂԂ���
                //�������Ȃ�召�t�ɂȂ��ēs���悵
                rev_pos_Z = 0;
                //_TRACE_("DL < DR  "<<DL<<">"<<DR<<"   rev_pos_Z = false;");
                if (DLT < 0 || DRT < 0) {
                    rev_pos_Z = !rev_pos_Z;
                }

                if (DRr > DTr && DRr > DBor) {
                    rev_pos_Z += 100;
                }
            } else if (DLr  > DRr) {
                //��O�����Ȃ王���䍶���ʂɂԂ���
                //�������Ȃ�召�t�ɂȂ��ēs���悵
                rev_pos_Z = 1;
                if (DLT < 0 || DRT < 0) {
                    rev_pos_Z = !rev_pos_Z;
                }

                //_TRACE_("DL > DR  "<<DL<<">"<<DR<<"   rev_pos_Z = true;");
                if (DLr > DTr && DLr > DBor) {
                    rev_pos_Z += 100;
                }
            } else {
                rev_pos_Z = 0;
            }


//            //�������l����
//            if (GgafDx9Util::abs(DTT - DTF) >  GgafDx9Util::abs(DLT - DLF)) {
//                //���Ă�
//                rev_pos_Z += 100;
//            } else {
//                rev_pos_Z += 0;
//            }





            hr = pID3DXEffect->SetInt(_ahRevPosZ[i], rev_pos_Z);
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetBool(_hRevPosZ) �Ɏ��s���܂����B1");

        } else {
            hr = pID3DXEffect->SetMatrix(_ahMatWorld_front[i], &(pDrawLaserChipActor->_matWorld) ); //�擪���Ȃ��̂Ŏ��M��_matWorld
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B2");
            hr = pID3DXEffect->SetInt(_ahRevPosZ[i], 0);
            mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetBool(_hRevPosZ) �Ɏ��s���܂����B2");
        }
        pDrawLaserChipActor = (LaserChip*)(pDrawLaserChipActor -> _pNext_TheSameDrawDepthLevel);
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }

    _pMeshSetModel->draw(this);
}

#ifdef OREDEBUG

void LaserChip::processAfterDraw() {
    //�����蔻��̈�\��
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pStgChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void LaserChip::processAfterDraw() {}

#endif

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pMover);

}

