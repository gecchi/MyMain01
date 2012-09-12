#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
     GgafDxMeshSetActor(prm_name,
                         std::string("11/" + std::string(prm_model)).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         NEW CollisionChecker(this) ) {
    _pMeshSetModel->_set_num = 11; //���݂̃��[�U�[�̍ő�Z�b�g����11�B
    _obj_class |= Obj_LaserChip;
    _pColliChecker = (CollisionChecker*)_pChecker;
    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDepo = NULL; //LaserChipDepository�ɒǉ�����鎞�ɐݒ肳���B�ʏ�LaserChip��LaserChipDepository�̓Z�b�g�B
    _chip_kind = 1;
    _is_regist_hitarea = false;
    _hitarea_edge_length = 0;
    _harf_hitarea_edge_length = 0;
    _can_chikei_hit = false;
    _ah_kind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ah_kind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ah_kind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ah_kind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ah_kind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ah_kind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ah_kind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ah_kind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
    _ah_kind[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind009" );
    _ah_kind[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind010" );
    _ah_kind[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind011" );

    _ah_alpha[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha001" );
    _ah_alpha[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha002" );
    _ah_alpha[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha003" );
    _ah_alpha[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha004" );
    _ah_alpha[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha005" );
    _ah_alpha[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha006" );
    _ah_alpha[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha007" );
    _ah_alpha[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha008" );
    _ah_alpha[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha009" );
    _ah_alpha[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha010" );
    _ah_alpha[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha011" );

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
    _alpha = 0.99; //�ŏ��͉��ł��n�b�L���f��B
}

void LaserChip::processSettlementBehavior() {
    //�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɁA���Ԃɓ����蔻��̈���ꎞ�I�ɗL����
    //���̏�����processBehavior()�ōs���Ȃ��B�Ȃ��Ȃ�΁A_pChip_front �����W�ړ��ς݂̕ۏ؂��Ȃ����߁B
    if (_is_regist_hitarea) { //registHitAreaCube���\�b�h�ɂ���ēo�^���ꂽ�ꍇ�B
        if (_pChip_front != NULL) {
            int dX = _pChip_front->_X - _X;
            int dY = _pChip_front->_Y - _Y;
            int dZ = _pChip_front->_Z - _Z;
            if (ABS(dX) >= _hitarea_edge_length_3 ||
                ABS(dY) >= _hitarea_edge_length_3 ||
                ABS(dZ) >= _hitarea_edge_length_3) {
                //���g�ƑO���`�b�v�̒��Ԃɓ����蔻������o��
                int cX = dX / 2;
                int cY = dY / 2;
                int cZ = dZ / 2;
                _pColliChecker->setColliAAB(
                              1,
                              cX - _harf_hitarea_edge_length,
                              cY - _harf_hitarea_edge_length,
                              cZ - _harf_hitarea_edge_length,
                              cX + _harf_hitarea_edge_length,
                              cY + _harf_hitarea_edge_length,
                              cZ + _harf_hitarea_edge_length
                              );
                _pColliChecker->enable(1);
            } else {
                _pColliChecker->disable(1);
            }
//            //�L�т�������؂��
//            if (ABS(dX) >= _hitarea_edge_length*5 || ABS(dY) >= _hitarea_edge_length*5 || ABS(dZ) >= _hitarea_edge_length*5) {
//                sayonara();
//            }
        } else {
            _pColliChecker->disable(1);
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
                    _pLeader = _pChip_front->_pLeader;
                } else {
                    _chip_kind = 3; //�擪�e�N�X�`���`�b�v
                    _pLeader = _pChip_front->_pLeader;
                }
            } else {
                _chip_kind = 1; //���ˌ��̖��[�e�N�X�`���`�b�v
                _pLeader = _pChip_front->_pLeader;
            }
        } else {
            _chip_kind = 1; //���ʂ̖��[�e�N�X�`��
            _pLeader = _pChip_front->_pLeader;
        }
    } else {
        _chip_kind = 4; //��[�`�b�v�B�����`�悵�����Ȃ�
        _pLeader = this;
        if (getActivePartFrame() > 1 && _pChip_behind == NULL) {
            sayonara();
        }
        setHitAble(false);
    }
    if (isOutOfUniverse()) {
        sayonara();
    }

    //�ŏ��͉��ł��n�b�L���f��B��
    //1�b��͋����Ɋ���Ĕ��܂�d�l
    if (getActivePartFrame() > 60 && _alpha > 0) {
        _alpha -= 0.01;
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
                    hr = pID3DXEffect->SetInt(this->_ah_kind[_draw_set_num], pLaserChip->_chip_kind);
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");

                    hr = pID3DXEffect->SetFloat(this->_ah_alpha[_draw_set_num], pLaserChip->getAlpha());
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetFloat(_ah_alpha) �Ɏ��s���܂����B2");
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
        _pMeshSetModel->draw(this, _draw_set_num);
    }
}

void LaserChip::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
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
    _pLeader = NULL;
}

void LaserChip::registHitAreaCube(int prm_edge_length) {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _is_regist_hitarea = true;
    _hitarea_edge_length = prm_edge_length;
    _hitarea_edge_length_3 = _hitarea_edge_length*3;
    _harf_hitarea_edge_length = _hitarea_edge_length / 2;
    _pColliChecker->makeCollision(2);
    _pColliChecker->setColliAAB_Cube(0, prm_edge_length);
    _pColliChecker->setColliAAB_Cube(1, prm_edge_length);
    _pColliChecker->disable(1);
    setHitAble(true);
}

void LaserChip::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //���ݒ�A���[�U�[�`�b�v�́A����_paMaterial�͎g�p���Ȃ�
}

void LaserChip::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //���ݒ�A���[�U�[�`�b�v�́A����_paMaterial�͎g�p���Ȃ�
}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
}

