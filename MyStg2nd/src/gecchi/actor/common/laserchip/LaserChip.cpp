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
    _dwActiveFrame = 0;
    _is_regist_hitarea = false;
    _hitarea_edge_length = 0;
    _harf_hitarea_edge_length = 0;

    _ahKind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ahKind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ahKind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ahKind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ahKind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ahKind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ahKind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ahKind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
    _ahKind[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind009" );
    _ahKind[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind010" );
    _ahKind[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind011" );
    _ahKind[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind012" );
    _ahKind[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind013" );
    _ahKind[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind014" );
    _ahKind[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind015" );
    _ahKind[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind016" );

    _ahMatWorld_front[0]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front001" );
    _ahMatWorld_front[1]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front002" );
    _ahMatWorld_front[2]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front003" );
    _ahMatWorld_front[3]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front004" );
    _ahMatWorld_front[4]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front005" );
    _ahMatWorld_front[5]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front006" );
    _ahMatWorld_front[6]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front007" );
    _ahMatWorld_front[7]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front008" );
    _ahMatWorld_front[8]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front009" );
    _ahMatWorld_front[9]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front010" );
    _ahMatWorld_front[10]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front011" );
    _ahMatWorld_front[11]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front012" );
    _ahMatWorld_front[12]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front013" );
    _ahMatWorld_front[13]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front014" );
    _ahMatWorld_front[14]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front015" );
    _ahMatWorld_front[15]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front016" );

}

void LaserChip::initialize() {
    //_TRACE_("LaserChip::initialize() "<<getName()<<" bump="<<canBump());
    _pMover->setMoveVelocity(40000);
    _fAlpha = 0.99;
}


void LaserChip::onActive() {
    //_TRACE_("LaserChip::onActive()st "<<getName()<<" bump="<<canBump());
//    _TRACE_("LaserChip::onActive() !!"<<getName()<<"/_is_active_flg_in_next_frame="<<_is_active_flg_in_next_frame<<
//            "/_on_change_to_active_flg="<<_on_change_to_active_flg<<
//            "/_on_change_to_inactive_flg="<<_on_change_to_inactive_flg<<
//            "/_is_active_flg="<<_is_active_flg);
//    _TRACE_("LaserChip::onActive() _dwActiveFrame = 0;!!!"<<getName()<<"");
    _dwActiveFrame = 0;
    //�o����
    _chip_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
            //_TRACE_("LaserChip::onActive() _pChip_front == NULL!!");
        }
    } else {
        //_TRACE_("LaserChip::onActive() _pChip_front == "<<(_pChip_front->getName())<<"");
    }

    _pDispatcher->_num_chip_active++;
    //���[�U�[�́A�^��������Ԃ����Ȃ̂ŁA�R�R�ōs���������dx,dy,dz�����X�V����B
    //�v�Z�񐔂�ߖ�B
    GgafDx9GeometricActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);
    //??
    //TODO: ���ł����ǉ������񂾂����H�E�E�E���ׂ�
    if (_pChip_front != NULL) {
        processPreJudgement();
    } else {

    }

    //_TRACE_("LaserChip::onActive()ed "<<getName()<<" bump="<<canBump());
}

void LaserChip::processBehavior() {
    //_TRACE_("LaserChip::processBehavior()ed "<<getName()<<" bump="<<canBump());
}




void LaserChip::processPreJudgement() {
    //�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɁA���Ԃɓ����蔻��̈���ꎞ�I�ɗL����
    //���̏�����processBehavior()�ōs���Ȃ��B�Ȃ��Ȃ�΁A_pChip_front �����W�ړ��ς݂̕ۏ؂��Ȃ����߁B

    static int dX, dY, dZ,cX, cY, cZ,h;
    //_TRACE_("LaserChip::processBehavior()st "<<getName()<<" bump="<<canBump());
    if (_is_regist_hitarea) { //registHitAreaCube���\�b�h�ɂ���ēo�^���ꂽ�ꍇ�B
        if (_pChip_front != NULL && _pChip_front->_pChip_front != NULL) {
            dX = _pChip_front->_X - _X;
            dY = _pChip_front->_Y - _Y;
            dZ = _pChip_front->_Z - _Z;
            if (abs(dX) >= _hitarea_edge_length*3 || abs(dY) >= _hitarea_edge_length*3 || abs(dZ) >= _hitarea_edge_length*3) {
                //���g�ƑO���`�b�v�̒��Ԃɓ����蔻������o��
                cX = dX / 2;
                cY = dY / 2;
                cZ = dZ / 2;
                h = _hitarea_edge_length / 2;
                _pStgChecker->setHitAreaBox(
                              1,
                              cX - _harf_hitarea_edge_length,
                              cY - _harf_hitarea_edge_length,
                              cZ - _harf_hitarea_edge_length,
                              cX + _harf_hitarea_edge_length,
                              cY + _harf_hitarea_edge_length,
                              cZ + _harf_hitarea_edge_length
                              );
                _pStgChecker->enable(1);
            } else {
                _pStgChecker->disable(1);
            }
        } else {
            _pStgChecker->disable(1);
        }
    }

    GgafDx9MeshSetActor::processPreJudgement(); //�W���ؓo�^
    //�����蔻��̈���X�V���Ă���processPreJudgement�łW���ؓo�^���邱�ƁB

}

void LaserChip::processJudgement() {
    //_TRACE_("LaserChip::processJudgement()st "<<getName()<<" bump="<<canBump());
    if (isOutOfGameSpace()) {
        inactivate();
    }
    //���[�U�[���  1:���� 2:���� 3:�擪 �i�������擪�͖������D��j
    setBumpable(true);
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
        setBumpable(false);
    }

//    if ((0 <= _RZ && _RZ < ANGLE90) ||
//        (ANGLE270 <= _RZ && _RZ < ANGLE360) ) {
//        _RX = 0;
//    } else {
//        _RX = ANGLE180;
//    }

//    //�y���Ӂz4/15 ����
//    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
//    //processBehavior,processJudgement�ł� _pChip_front ���K����Ɏ��s�����i�����������c���[�\���Ɉˑ����邽�߁j�B
//    //�`�掞��_pChip_front���g�p���邽�߂����Őݒ肵�Ƃ��K�v������B
//    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
    //_TRACE_("LaserChip::processJudgement()ed "<<getName()<<" bump="<<canBump());
}


void LaserChip::processDraw() {
    //_TRACE_("LaserChip::processDraw()st "<<getName()<<" bump="<<canBump());
    _draw_set_num = 1; //����`��[�x�ɁAGgafDx9MeshSetActor�̓������f�����A�����Ă���J�E���g��
    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > _pMeshSetModel->_set_num) {
                    _draw_set_num = _pMeshSetModel->_set_num;
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

    LaserChip *pDrawLaserChipActor;
    pDrawLaserChipActor = this;

    for (int i = 0; i < _draw_set_num; i++) {
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawLaserChipActor->_matWorld));
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

        if (pDrawLaserChipActor->_pChip_front != NULL) {
            //�e�N�X�`�����
            hr = pID3DXEffect->SetInt(_ahKind[i], pDrawLaserChipActor->_chip_kind);
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

    // Z�o�b�t�@�𖳌���
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    _pMeshSetModel->draw(this);

    // Z�o�b�t�@��L����
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //_TRACE_("LaserChip::processDraw()ed "<<getName()<<" bump="<<canBump());
}

void LaserChip::drawHitArea() {
    //_TRACE_("LaserChip::drawHitArea()st "<<getName()<<" bump="<<canBump());
    CubeEx::get()->drawHitarea(_pStgChecker);
    //_TRACE_("LaserChip::drawHitArea()ed "<<getName()<<" bump="<<canBump());
}

void LaserChip::processOnHit(GgafActor* prm_pOtherActor) {
}

void LaserChip::onInactive() {
    //_TRACE_("LaserChip::onInactive()st "<<getName()<<" bump="<<canBump());
//    _TRACE_("LaserChip::onInactive() !!"<<getName()<<"/_is_active_flg_in_next_frame="<<_is_active_flg_in_next_frame<<
//            "/_on_change_to_active_flg="<<_on_change_to_active_flg<<
//            "/_on_change_to_inactive_flg="<<_on_change_to_inactive_flg<<
//            "/_is_active_flg="<<_is_active_flg);
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
    //_TRACE_("LaserChip::onInactive()ed "<<getName()<<" bump="<<canBump());
}

void LaserChip::registHitAreaCube(int prm_edge_length) {
    //_TRACE_("LaserChip::registHitAreaCube()st "<<getName()<<" bump="<<canBump());
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _is_regist_hitarea = true;
    _hitarea_edge_length = prm_edge_length;
    _harf_hitarea_edge_length = _hitarea_edge_length / 2;
    _pStgChecker->useHitAreaBoxNum(2);
    _pStgChecker->setHitAreaBox_Cube(0, prm_edge_length);
    _pStgChecker->setHitAreaBox_Cube(1, prm_edge_length);
    _pStgChecker->disable(1);
    setBumpable(true);
    //_TRACE_("LaserChip::registHitAreaCube()ed "<<getName()<<" bump="<<canBump());

}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);

}

