#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
     GgafDxMeshSetActor(prm_name,
                         string("11/" + string(prm_model)).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         NEW CollisionChecker(this) ) {
    _pMeshSetModel->_set_num = 11; //���݂̃��[�U�[�̍ő�Z�b�g����11�B
    _obj_class |= Obj_LaserChip;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDepo = NULL; //LaserChipDepository�ɒǉ�����鎞�ɐݒ肳���B�ʏ�LaserChip��LaserChipDepository�̓Z�b�g�B
    _chip_kind = 1;
    _is_regist_hitarea = false;
    _hitarea_edge_length = 0;
    _harf_hitarea_edge_length = 0;
    _can_chikei_hit = false;
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
//    _ahKind[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind012" );
//    _ahKind[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind013" );
//    _ahKind[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind014" );
//    _ahKind[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind015" );
//    _ahKind[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind016" );

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
//    _ah_matWorld_front[11]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front012" );
//    _ah_matWorld_front[12]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front013" );
//    _ah_matWorld_front[13]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front014" );
//    _ah_matWorld_front[14]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front015" );
//    _ah_matWorld_front[15]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front016" );

    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void LaserChip::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->_obj_class & Obj_WallPartsActor) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}


void LaserChip::onActive() {
    //�o����
    _chip_kind = 1;
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
}

void LaserChip::processSettlementBehavior() {
    //�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɁA���Ԃɓ����蔻��̈���ꎞ�I�ɗL����
    //���̏�����processBehavior()�ōs���Ȃ��B�Ȃ��Ȃ�΁A_pChip_front �����W�ړ��ς݂̕ۏ؂��Ȃ����߁B

    int dX, dY, dZ,cX, cY, cZ,h;
    if (_is_regist_hitarea) { //registHitAreaCube���\�b�h�ɂ���ēo�^���ꂽ�ꍇ�B
        if (_pChip_front != NULL) {
            dX = _pChip_front->_X - _X;
            dY = _pChip_front->_Y - _Y;
            dZ = _pChip_front->_Z - _Z;
            if (GgafUtil::abs(dX) >= _hitarea_edge_length*3 || GgafUtil::abs(dY) >= _hitarea_edge_length*3 || GgafUtil::abs(dZ) >= _hitarea_edge_length*3) {
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
            if (_pChip_behind->isActiveInTheTree()) {
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
//        if (_pChip_behind == NULL) {
//            sayonara();
//        }
    }
    if (isOutOfUniverse()) {
        sayonara();
    }

    GgafDxMeshSetActor::processSettlementBehavior(); //�W���ؓo�^
    //TODO:�W���ؓo�^�����Ȃ�processSettlementBehavior()���Ăяo���̂͏�������������������Ȃ��B
    //�����蔻��̈���X�V���Ă���processSettlementBehavior�łW���ؓo�^���邱�ƁB
}

void LaserChip::processPreDraw() {
    if (_chip_kind < 4) {
        //4�ȊO��\���Ώۂɂ���
        GgafDxDrawableActor::processPreDraw();
    }
}

void LaserChip::processDraw() {
    _draw_set_num = 0; //GgafDxMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //��{���f�����_��
    GgafDxDrawableActor* pDrawActor = this;
    LaserChip* pLaserChip = NULL;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pLaserChip = (LaserChip*)pDrawActor;

                //����������ւ�ňӖ��s���ȃG���[�ɂȂ�����A
                //GgafDxSpriteLaserChipActor��[MEMO]��ǂݒ����I
                if (pLaserChip->_pChip_front) {
                    //���g���[���h�ϊ��s��
                    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pLaserChip->_matWorld));
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
                    //��O���̃��[���h�ϊ��s��
                    hr = pID3DXEffect->SetMatrix(this->_ah_matWorld_front[_draw_set_num], &(pLaserChip->_pChip_front->_matWorld));
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_h_matWorld_front) �Ɏ��s���܂����B1");
                    //�`�b�v���
                    hr = pID3DXEffect->SetInt(this->_ahKind[_draw_set_num], pLaserChip->_chip_kind);
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");
                } else {
                    //��[�`�b�v�͕`��s�v
                    pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
                    continue;
                }

                _draw_set_num++;
                if (_draw_set_num >= _pMeshSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_DrawActive = pLaserChip; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    if (_draw_set_num > 0) { //�`�悳��Ȃ��\�������邽�߂��̔��肪�K�v
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_BLENDFACTOR,0x00888888);
        _pMeshSetModel->draw(this, _draw_set_num);
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_BLENDFACTOR,0x00888888);
    }
}

void LaserChip::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

void LaserChip::onInactive() {
    //������
    if (_pDepo) {
        _pDepo->_num_chip_active--;
    }
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

