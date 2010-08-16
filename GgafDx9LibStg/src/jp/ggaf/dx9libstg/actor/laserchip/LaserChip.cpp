#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
     GgafDx9MeshSetActor(prm_name,
                         string(string("11/") + string(prm_model)).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         NEW CollisionChecker(this) ) {
    _pMeshSetModel->_set_num = 11; //���݂̃��[�U�[�̍ő�Z�b�g����11�B

    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcher�� new ���ɐݒ肳���B
    _chip_kind = 1;
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

    _ah_matWorld_front[0]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front001" );
    _ah_matWorld_front[1]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front002" );
    _ah_matWorld_front[2]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front003" );
    _ah_matWorld_front[3]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front004" );
    _ah_matWorld_front[4]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front005" );
    _ah_matWorld_front[5]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front006" );
    _ah_matWorld_front[6]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front007" );
    _ah_matWorld_front[7]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front008" );
    _ah_matWorld_front[8]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front009" );
    _ah_matWorld_front[9]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front010" );
    _ah_matWorld_front[10]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front011" );
    _ah_matWorld_front[11]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front012" );
    _ah_matWorld_front[12]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front013" );
    _ah_matWorld_front[13]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front014" );
    _ah_matWorld_front[14]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front015" );
    _ah_matWorld_front[15]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front016" );

    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

//void LaserChip::onCreateModel() {
//    _pMeshSetModel->_set_num = 11; //���݂̃��[�U�[�̍ő�Z�b�g����11�B
//    _TRACE_("LaserChip::onCreateModel() "<<_pMeshSetModel->getName()<<" �̃Z�b�g���� "<< _pMeshSetModel->_set_num<<" �ɋ�������܂����B");
//}

void LaserChip::initialize() {
    //_TRACE_("LaserChip::initialize() "<<getName()<<" bump="<<canHit());
    _pMover->setMvVelo(40000);
    _fAlpha = 0.99;
}


void LaserChip::onActive() {
    //_TRACE_("LaserChip::onActive()st "<<getName()<<" bump="<<canHit());
//    _TRACE_("LaserChip::onActive() !!"<<getName()<<"/_is_active_flg_in_next_frame="<<_is_active_flg_in_next_frame<<
//            "/_on_change_to_active_flg="<<_on_change_to_active_flg<<
//            "/_on_change_to_inactive_flg="<<_on_change_to_inactive_flg<<
//            "/_is_active_flg="<<_is_active_flg);
//    _TRACE_("LaserChip::onActive() _frame_of_behaving_from_onActive = 0;!!!"<<getName()<<"");
    //�o����
    _chip_kind = 1;
    if (_pChip_front == NULL) {
//        if (_pDispatcher->_pSeConnection) {
//            _pDispatcher->_pSeConnection->refer()->play();
//            //_TRACE_("LaserChip::onActive() _pChip_front == NULL!!");
//        }
    } else {
        //_TRACE_("LaserChip::onActive() _pChip_front == "<<(_pChip_front->getName())<<"");
    }

    _pDispatcher->_num_chip_active++;


    //_TRACE_("LaserChip::onActive()ed "<<getName()<<" bump="<<canHit());
}

void LaserChip::processBehavior() {
    //_TRACE_("LaserChip::processBehavior()ed "<<getName()<<" bump="<<canHit());
}




void LaserChip::processSettlementBehavior() {
    //�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɁA���Ԃɓ����蔻��̈���ꎞ�I�ɗL����
    //���̏�����processBehavior()�ōs���Ȃ��B�Ȃ��Ȃ�΁A_pChip_front �����W�ړ��ς݂̕ۏ؂��Ȃ����߁B

    static int dX, dY, dZ,cX, cY, cZ,h;
    //_TRACE_("LaserChip::processBehavior()st "<<getName()<<" bump="<<canHit());
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
                _pCollisionChecker->setColliAAB(
                              1,
                              cX - _harf_hitarea_edge_length,
                              cY - _harf_hitarea_edge_length,
                              cZ - _harf_hitarea_edge_length,
                              cX + _harf_hitarea_edge_length,
                              cY + _harf_hitarea_edge_length,
                              cZ + _harf_hitarea_edge_length
                              );
                _pCollisionChecker->enable(1);
            } else {
                _pCollisionChecker->disable(1);
            }
//            //�L�т�������؂��
//            if (abs(dX) >= _hitarea_edge_length*5 || abs(dY) >= _hitarea_edge_length*5 || abs(dZ) >= _hitarea_edge_length*5) {
//                sayonara();
//            }
        } else {
            _pCollisionChecker->disable(1);
        }
    }


    //���[�U�[�`�b�v��� �ݒ�B
    //�V�F�[�_�[�̃p�����[�^�ƂȂ�܂��B
    //
    //      -==========<>            ���[�U�[��
    //
    //      -= === === === <>        ����Ȃӂ��ɕ��f����Ă��܂��B
    //
    //    | -=|===|===|===|<> |     ���}�̓��[�U�[���I�u�W�F�N�g�ŋ�؂�������̐}
    //
    //    <--><--><--><--><-->^
    //    ^   ^   ^   ^   ^   |
    //    |   |   |   |   |   |
    //    |   |   |   |   |    `----- 4:��[�`�b�v(��\���ŁA���Ԑ擪�`�b�v��\�����邽�߂����ɑ���)
    //    |   |   |   |    `----- 3:���Ԑ擪�`�b�v(�\�����������̐擪)
    //    |   |   |    `----- 2:���ԃ`�b�v
    //    |   |    `----- 2:���ԃ`�b�v
    //    |    `----- 2:���ԃ`�b�v
    //     `----- 1:�����`�b�v
    //
    //�擪�Ɛ�[�Ƃ������t�ŋ�ʂ��Ă��܂��B
    setHitAble(true);
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActive()) {
                if (_pChip_front->_pChip_front) {
                    _chip_kind = 2; //���ԃe�N�X�`���`�b�v
                } else {
                    _chip_kind = 3; //�擪�e�N�X�`���`�b�v
                }
            } else {
                _chip_kind = 1; //���ˌ��̖��[�e�N�X�`���`�b�v
            }
        } else {
            _chip_kind = 1; //���ʂ̖��[�e�N�X�`��
        }
    } else {
        _chip_kind = 4; //��[�`�b�v�B�����`�悵�����Ȃ�
        setHitAble(false);
    }

    GgafDx9MeshSetActor::processSettlementBehavior(); //�W���ؓo�^
    //�����蔻��̈���X�V���Ă���processSettlementBehavior�łW���ؓo�^���邱�ƁB

}

void LaserChip::processJudgement() {
    //_TRACE_("LaserChip::processJudgement()st "<<getName()<<" bump="<<canHit());
    if (isOutOfGameSpace()) {
        sayonara();
    }
}


void LaserChip::processDraw() {
    //_TRACE_("LaserChip::processDraw()st "<<getName()<<" bump="<<canHit());
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
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_h_matView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_h_matView) �Ɏ��s���܂����B");

    LaserChip *pDrawLaserChipActor;
    pDrawLaserChipActor = this;

    for (int i = 0; i < _draw_set_num; i++) {
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[i], &(pDrawLaserChipActor->_matWorld));
        checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

        if (pDrawLaserChipActor->_pChip_front != NULL) {
            //�e�N�X�`�����
            hr = pID3DXEffect->SetInt(this->_ahKind[i], pDrawLaserChipActor->_chip_kind);
            checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");
            hr = pID3DXEffect->SetMatrix(this->_ah_matWorld_front[i], &(pDrawLaserChipActor->_pChip_front->_matWorld));
            checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_h_matWorld_front) �Ɏ��s���܂����B1");
        } else {
            //�e�N�X�`�����
            hr = pID3DXEffect->SetInt(this->_ahKind[i], pDrawLaserChipActor->_chip_kind);
            checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");
            hr = pID3DXEffect->SetMatrix(this->_ah_matWorld_front[i], &(pDrawLaserChipActor->_matWorld) ); //�擪���Ȃ��̂Ŏ��M��_matWorld
            checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_h_matWorld_front) �Ɏ��s���܂����B2");
        }
        //���̃L���X�g�͊댯�ł���
        pDrawLaserChipActor = (LaserChip*)(pDrawLaserChipActor -> _pNext_TheSameDrawDepthLevel);
        //����������ւ�ňӖ��s���ȃG���[�ɂȂ�����A
        //GgafDx9SpriteMeshSetActor��[MEMO]��ǂݒ����I

        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }

    //Z�o�b�t�@�͍l�����ĕ`�悷�邪�AZ�o�b�t�@�͏������܂Ȃ��B
    // Z�o�b�t�@�𖳌���
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    _pMeshSetModel->draw(this);

    // Z�o�b�t�@��L����
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //_TRACE_("LaserChip::processDraw()ed "<<getName()<<" bump="<<canHit());
}

void LaserChip::drawHitArea() {
    //_TRACE_("LaserChip::drawHitArea()st "<<getName()<<" bump="<<canHit());
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
    //_TRACE_("LaserChip::drawHitArea()ed "<<getName()<<" bump="<<canHit());
}

void LaserChip::onHit(GgafActor* prm_pOtherActor) {
}

void LaserChip::onInactive() {
    //_TRACE_("LaserChip::onInactive()st "<<getName()<<" bump="<<canHit());
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
    //_TRACE_("LaserChip::onInactive()ed "<<getName()<<" bump="<<canHit());
}

void LaserChip::registHitAreaCube(int prm_edge_length) {
    //_TRACE_("LaserChip::registHitAreaCube()st "<<getName()<<" bump="<<canHit());
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _is_regist_hitarea = true;
    _hitarea_edge_length = prm_edge_length;
    _harf_hitarea_edge_length = _hitarea_edge_length / 2;
    _pCollisionChecker->makeCollision(2);
    _pCollisionChecker->setColliAAB_Cube(0, prm_edge_length);
    _pCollisionChecker->setColliAAB_Cube(1, prm_edge_length);
    _pCollisionChecker->disable(1);
    setHitAble(true);
    //_TRACE_("LaserChip::registHitAreaCube()ed "<<getName()<<" bump="<<canHit());

}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);

}

