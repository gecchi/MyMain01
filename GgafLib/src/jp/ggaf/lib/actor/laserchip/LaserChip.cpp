#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
      GgafDxMeshSetActor(prm_name,
                         std::string("11/" + std::string(prm_model)).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         NEW CollisionChecker3D(this) ) {
    _pMeshSetModel->_set_num = 11; //���݂̃��[�U�[�̍ő�Z�b�g����11�B
    _obj_class |= Obj_LaserChip;
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _class_name = "LaserChip";
    _pChip_front = nullptr;
    _pChip_behind = nullptr;
    _pDepo = nullptr; //LaserChipDepository�ɒǉ�����鎞�ɐݒ肳���B�ʏ�LaserChip��LaserChipDepository�̓Z�b�g�B
    _chip_kind = 1;
    _hitarea_edge_length = 0;
    _harf_hitarea_edge_length = 0;
    _can_chikei_hit = false;
    _ah_kind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind001" );
    _ah_kind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind002" );
    _ah_kind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind003" );
    _ah_kind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind004" );
    _ah_kind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind005" );
    _ah_kind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind006" );
    _ah_kind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind007" );
    _ah_kind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind008" );
    _ah_kind[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind009" );
    _ah_kind[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind010" );
    _ah_kind[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_kind011" );

    _ah_force_alpha[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha001" );
    _ah_force_alpha[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha002" );
    _ah_force_alpha[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha003" );
    _ah_force_alpha[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha004" );
    _ah_force_alpha[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha005" );
    _ah_force_alpha[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha006" );
    _ah_force_alpha[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha007" );
    _ah_force_alpha[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha008" );
    _ah_force_alpha[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha009" );
    _ah_force_alpha[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha010" );
    _ah_force_alpha[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha011" );

    _ah_matWorld_front[0]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front001" );
    _ah_matWorld_front[1]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front002" );
    _ah_matWorld_front[2]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front003" );
    _ah_matWorld_front[3]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front004" );
    _ah_matWorld_front[4]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front005" );
    _ah_matWorld_front[5]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front006" );
    _ah_matWorld_front[6]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front007" );
    _ah_matWorld_front[7]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front008" );
    _ah_matWorld_front[8]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front009" );
    _ah_matWorld_front[9]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front010" );
    _ah_matWorld_front[10]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front011" );

    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setAlpha(0.99);
    _middle_colli_able = false;
}

void LaserChip::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->instanceOf(Obj_WallPartsActor)) {
        if (_chip_kind == 3 || _can_chikei_hit) {  //3:���Ԑ擪�`�b�v ���A1/8�̒n�`�����蔻��L��`�b�v
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
    _force_alpha = 1.00; //�ŏ��͉��ł��n�b�L���f��B
    if (_middle_colli_able) {
        getCollisionChecker()->disable(1);
    }
}

void LaserChip::processSettlementBehavior() {
    LaserChip* pChip_front = _pChip_front;
    CollisionChecker3D* pChecker = getCollisionChecker();

    //���[�U�[�`�b�v��� �ݒ�B
    //�V�F�[�_�[�̃p�����[�^�ƂȂ�܂��B
    //
    //      -==========<>            ���[�U�[��
    //
    //      -= === === === <>        ����Ȃӂ��ɕ��f����Ă��܂��B
    //                               �c�ɋ�؂��Ă�����̉ӏ��� LaserChip �I�u�W�F�N�g�ł��B
    //    | -=|===|===|===|<> |      ���}�̓��[�U�[���I�u�W�F�N�g�ŋ�؂�������̐}
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
    if (pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActiveInTheTree()) {
                if (pChip_front->_pChip_front) {
                    _chip_kind = 2; //���ԃe�N�X�`���`�b�v
                    _pLeader = pChip_front->_pLeader;
                } else {
                    _chip_kind = 3; //�擪�e�N�X�`���`�b�v
                    _pLeader = pChip_front->_pLeader;
                }
            } else {
                _chip_kind = 1; //���ˌ��̖��[�e�N�X�`���`�b�v
                _pLeader = pChip_front->_pLeader;
            }
        } else {
            _chip_kind = 1; //���ʂ̖��[�e�N�X�`��
            _pLeader = pChip_front->_pLeader;
        }
    } else {
        _chip_kind = 4; //��[�`�b�v�B�����`�悵�����Ȃ�
        _pLeader = this;
        if (getActiveFrame() > 1 && _pChip_behind == nullptr) {
            sayonara();
        }
        setHitAble(false);
    }

    //���̏�����processBehavior()�ōs���Ȃ��B�Ȃ��Ȃ�΁A_pChip_front �����W�ړ��ς݂̕ۏ؂��Ȃ����߁B
    if (_middle_colli_able) { //�����炭���T�����[�U�[�`�b�v�̏ꍇ
        if (_chip_kind != 4) {
            coord dX = pChip_front->_x - _x;
            coord dY = pChip_front->_y - _y;
            coord dZ = pChip_front->_z - _z;
            coord abs_dx = ABS(dX);
            coord abs_dy = ABS(dY);
            coord abs_dz = ABS(dZ);

            if (abs_dx < _hitarea_edge_length &&
                abs_dy < _hitarea_edge_length &&
                abs_dz < _hitarea_edge_length) {
                //�O���`�b�v�Ƃ������������ꍇ�ɁA����̈���ꎞ�I�ɖ�����
                setHitAble(false);
            } else {
                setHitAble(true);
                if (abs_dx >= _hitarea_edge_length_3 ||
                    abs_dy >= _hitarea_edge_length_3 ||
                    abs_dz >= _hitarea_edge_length_3) {
                    //�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɁA���Ԃɓ����蔻��̈���ꎞ�I�ɗL����
                    //���g�ƑO���`�b�v�̒��Ԃɓ����蔻������o��
                    int cX = dX / 2;
                    int cY = dY / 2;
                    int cZ = dZ / 2;
                    pChecker->setColliAAB(
                                  1,
                                  cX - _harf_hitarea_edge_length,
                                  cY - _harf_hitarea_edge_length,
                                  cZ - _harf_hitarea_edge_length,
                                  cX + _harf_hitarea_edge_length,
                                  cY + _harf_hitarea_edge_length,
                                  cZ + _harf_hitarea_edge_length
                                  );
                    pChecker->enable(1);
                } else {
                    pChecker->disable(1);
                }
            }
        } else {
            pChecker->disable(1);
        }
    }


    if (isOutOfUniverse()) {
        sayonara();
    }

    //�ŏ��͉��ł��n�b�L���f��B��
    //1�b��͋����Ɋ���Ĕ��܂�d�l
    if (getActiveFrame() > 60 && _force_alpha > 0) {
        _force_alpha -= 0.01;
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
    int draw_set_num = 0; //GgafDxMeshSetActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //��{���f�����_��
    GgafDxDrawableActor* pDrawActor = this;
    LaserChip* pLaserChip = nullptr;
    int model_set_num = _pMeshSetModel->_set_num;

    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pLaserChip = (LaserChip*)pDrawActor;
            //����������ւ�ňӖ��s���ȃG���[�ɂȂ�����A
            //GgafDxSpriteLaserChipActor��[MEMO]��ǂݒ����I
            if (pLaserChip->_pChip_front) {
                //���g���[���h�ϊ��s��
                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pLaserChip->_matWorld));
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
                //��O���̃��[���h�ϊ��s��
                hr = pID3DXEffect->SetMatrix(this->_ah_matWorld_front[draw_set_num], &(pLaserChip->_pChip_front->_matWorld));
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_h_matWorld_front) �Ɏ��s���܂����B1");
                //�`�b�v���
                hr = pID3DXEffect->SetInt(this->_ah_kind[draw_set_num], pLaserChip->_chip_kind);
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) �Ɏ��s���܂����B2");

                hr = pID3DXEffect->SetFloat(this->_ah_force_alpha[draw_set_num], pLaserChip->_force_alpha);
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetFloat(_ah_force_alpha) �Ɏ��s���܂����B2");

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                    break;
                }

            } else {
                //��[�`�b�v�͕`��s�v
            }
            pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_DrawActive = pLaserChip; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
    if (draw_set_num > 0) { //�`�悳��Ȃ��\�������邽�߂��̔��肪�K�v
        _pMeshSetModel->GgafDxMeshSetModel::draw(this, draw_set_num);
    }
}

void LaserChip::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

void LaserChip::onInactive() {
    //������
    if (_pDepo) {
        _pDepo->_num_chip_active--;
        if (_pDepo->_num_chip_active < 0) {
            _pDepo->_num_chip_active = 0;
            //GgafActorDepository::onReset() �ɂ�� onInactive() ������̂ŁA���ɂȂ鎞��Ƃ�Ȃ�
        }
    }
    //�O��̌q�����ؒf
    if (_pChip_front) {
        _pChip_front->_pChip_behind = nullptr;
    }
    _pChip_front = nullptr;
    if (_pChip_behind) {
        _pChip_behind->_pChip_front = nullptr;
    }
    _pChip_behind = nullptr;
    _pLeader = nullptr;
}

void LaserChip::registerHitAreaCube_AutoGenMidColli(int prm_edge_length) {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _middle_colli_able = true;
    _hitarea_edge_length = prm_edge_length;
    _hitarea_edge_length_3 = _hitarea_edge_length*3;
    _harf_hitarea_edge_length = _hitarea_edge_length / 2;
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(2);
    pChecker->setColliAAB_Cube(0, prm_edge_length);
    pChecker->setColliAAB_Cube(1, prm_edge_length);
    pChecker->disable(1);
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
    GGAF_DELETE(_pColliChecker);
}

