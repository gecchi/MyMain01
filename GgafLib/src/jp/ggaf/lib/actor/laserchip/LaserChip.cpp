#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChip::VERTEX_instancedata LaserChip::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        GgafDxMassMeshActor(prm_name,
                         std::string(prm_model).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         UTIL::createChecker(this) ) {
//    _pMeshSetModel->_set_num = 11; //���݂̃��[�U�[�̍ő�Z�b�g����11�B
    _obj_class |= Obj_LaserChip;
    _pColliChecker = (CollisionChecker*)_pChecker;
    _class_name = "LaserChip";
    _pChip_infront = nullptr;
    _pChip_behind = nullptr;
    _pDepo = nullptr; //LaserChipDepository�ɒǉ�����鎞�ɐݒ肳���B�ʏ�LaserChip��LaserChipDepository�̓Z�b�g�B
    _chip_kind = 0;
    _hitarea_edge_length = 0;
    _hitarea_edge_length_2   = _hitarea_edge_length * 2;
    _hitarea_edge_length_3   = _hitarea_edge_length * 3;
    _hitarea_edge_length_3_2 = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6   = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6_2 = _hitarea_edge_length_6 * 2;
    _hdx = _hdy = _hdz = 0;
    _can_chikei_hit = false;

    setZEnableDraw(true);    //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setCullingDraw(false);
    _middle_colli_able = false;
    _rate_of_length = 1.0f;
    _power = 1.0f;
    _pMassMeshModel->registerCallback_VertexInstanceDataInfo(LaserChip::createVertexInstanceData);
    //���f���P�ʂŃZ�b�g����Ύ������̂����A�߂�ǂ��Ȃ̂ŁA�A�N�^�[���ɃZ�b�g
    static volatile bool is_init = LaserChip::initStatic(this); //�ÓI�����o������
}

bool LaserChip::initStatic(LaserChip* prm_pLaserChip) {
    return true;
}

void LaserChip::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
     if (prm_pOtherActor->instanceOf(Obj_MassWallActor)) {   //���肪�n�`�u���b�N
        if (_pChip_infront == nullptr || _can_chikei_hit) {  //��[�`�b�v ���A1/16�̒n�`�����蔻��L��`�b�v
            GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void LaserChip::onActive() {
    CollisionChecker* pChecker = getCollisionChecker();

    //�o����
    _chip_kind = 0; //�����s��
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
    _force_alpha = 1.00; //�ŏ��͉��ł��n�b�L���f��B

    GgafDxCollisionArea* pArea = pChecker->getArea();
    if (pArea) {
        if (_middle_colli_able) {
            pChecker->disable(1);
        }

        GgafDxCollisionPart* p = pArea->_papColliPart[0];
        _hdx = p->_hdx;
        _hdy = p->_hdy;
        _hdz = p->_hdz;
        pChecker->setColliAABox(
                0,
                -_hdx,
                -_hdy,
                -_hdz,
                +_hdx,
                +_hdy,
                +_hdz
                );
    }
}

void LaserChip::processSettlementBehavior() {
    CollisionChecker* pChecker = getCollisionChecker();
    const LaserChip* pChip_infront = _pChip_infront;
    const LaserChip* pChip_behind = _pChip_behind;

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
    if (pChip_infront) {
        if (pChip_infront->isActive()) {
            if (pChip_behind) {
                if (pChip_behind->isActive()) {
                    if (pChip_infront->_pChip_infront) {
                        _chip_kind = 2; //���ԃe�N�X�`���`�b�v
                        setHitAble(true);
                    } else {
                        _chip_kind = 3; //���Ԑ擪�e�N�X�`���`�b�v
                        setHitAble(true);
                    }
                } else {
                    _chip_kind = 1; //���ˌ��̖��[�e�N�X�`���`�b�v
                    setHitAble(true);
                }
            } else {
                _chip_kind = 1; //���ʂ̖��[�e�N�X�`��
                if (getActiveFrame() > 2 && pChip_infront->_pChip_infront == nullptr) {
                    _chip_kind = 0;
                    sayonara();
                    setHitAble(false);
                } else {
                    setHitAble(true);
                }
            }
        } else {
            _chip_kind = 4; //��[�`�b�v�B�����`�悵�����Ȃ�
            if (getActiveFrame() > 1 && pChip_behind == nullptr) {
                sayonara();
                setHitAble(false);
            } else {
                setHitAble(true);
            }
        }
    } else {
        _chip_kind = 4; //��[�`�b�v�B�����`�悵�����Ȃ�
        if (getActiveFrame() > 1 && pChip_behind == nullptr) {
            sayonara();
            setHitAble(false);
        } else {
            setHitAble(true);
        }
    }

    if (pChecker->getArea()) {
        if (_chip_kind == 4) {
            //��[�`�b�v�̓����蔻����A���`�b�v�Ƃ̒��Ԃ̈ʒu�ɉ��܂���B
            if (pChip_behind) {
                coord dX =  pChip_behind->_x - _x;
                coord dY =  pChip_behind->_y - _y;
                coord dZ =  pChip_behind->_z - _z;
                int cX = dX / 2;
                int cY = dY / 2;
                int cZ = dZ / 2;
                pChecker->setColliAABox(
                          0,
                          cX - _hdx,
                          cY - _hdy,
                          cZ - _hdz,
                          cX + _hdx,
                          cY + _hdy,
                          cZ + _hdz
                          );
                setHitAble(true);
            } else {
                setHitAble(false);
            }
        }


        //���̏�����processBehavior()�ōs���Ȃ��B�Ȃ��Ȃ�΁A_pChip_infront �����W�ړ��ς݂̕ۏ؂��Ȃ����߁B
        if (_middle_colli_able) { //�����炭���T�����[�U�[�`�b�v�̏ꍇ
            if (_chip_kind == 1 || _chip_kind == 2) {
                coord dX = pChip_infront->_x - _x;
                coord dY = pChip_infront->_y - _y;
                coord dZ = pChip_infront->_z - _z;
//                coord abs_dx = ABS(dX);
//                coord abs_dy = ABS(dY);
//                coord abs_dz = ABS(dZ);

                if ((ucoord)(dX+_hitarea_edge_length) < _hitarea_edge_length_2 &&
                    (ucoord)(dY+_hitarea_edge_length) < _hitarea_edge_length_2 &&
                    (ucoord)(dZ+_hitarea_edge_length) < _hitarea_edge_length_2)
                {
                    //�O���`�b�v�Ƃ������������ꍇ�ɁA����̈���ꎞ�I�ɖ�����
                    setHitAble(false);
                } else {
                    setHitAble(true);
                    if ((ucoord)(dX+_hitarea_edge_length_3) < _hitarea_edge_length_3_2 &&
                        (ucoord)(dY+_hitarea_edge_length_3) < _hitarea_edge_length_3_2 &&
                        (ucoord)(dZ+_hitarea_edge_length_3) < _hitarea_edge_length_3_2)
                    {
                        //�O���`�b�v�Ɨ��ꂷ�����ꍇ�ɁA���Ԃɓ����蔻��̈���ꎞ�I�ɗL����
                        //���g�ƑO���`�b�v�̒��Ԃɓ����蔻������o��
                        coord cX = dX / 2;
                        coord cY = dY / 2;
                        coord cZ = dZ / 2;
                        pChecker->setColliAABox(
                                      2,
                                      cX - _hdx,
                                      cY - _hdy,
                                      cZ - _hdz,
                                      cX + _hdx,
                                      cY + _hdy,
                                      cZ + _hdz
                                      );
                        if ((ucoord)(dX+_hitarea_edge_length_6) < _hitarea_edge_length_6_2 &&
                            (ucoord)(dY+_hitarea_edge_length_6) < _hitarea_edge_length_6_2 &&
                            (ucoord)(dZ+_hitarea_edge_length_6) < _hitarea_edge_length_6_2)
                        {
                            coord cX2 = cX / 2;
                            coord cY2 = cY / 2;
                            coord cZ2 = cZ / 2;
                            pChecker->setColliAABox(
                                          1,
                                          cX2 - _hdx,
                                          cY2 - _hdy,
                                          cZ2 - _hdz,
                                          cX2 + _hdx,
                                          cY2 + _hdy,
                                          cZ2 + _hdz
                                          );
                            coord cX3 = cX2 + cX;
                            coord cY3 = cY2 + cY;
                            coord cZ3 = cZ2 + cZ;
                            pChecker->setColliAABox(
                                          3,
                                          cX3 - _hdx,
                                          cY3 - _hdy,
                                          cZ3 - _hdz,
                                          cX3 + _hdx,
                                          cY3 + _hdy,
                                          cZ3 + _hdz
                                          );
                            _rate_of_length = 16.0f;
                        } else {
                            pChecker->disable(1);
                            pChecker->disable(3);
                            _rate_of_length = 8.0f;
                        }
                    } else {
                        pChecker->disable(1);
                        pChecker->disable(2);
                        pChecker->disable(3);
                        _rate_of_length = 4.0f;
                    }
                }
            } else {
                pChecker->disable(1);
                pChecker->disable(2);
                pChecker->disable(3);
                _rate_of_length = 4.0f;
            }
        }
    }

    //�ŏ��͉��ł��n�b�L���f��B��
    //1�b��͋����Ɋ���Ĕ��܂�d�l
    if (getActiveFrame() > 60 && _force_alpha > 0) {
        _force_alpha -= 0.01;
    }
    GgafDxMassMeshActor::processSettlementBehavior(); //�����ؓo�^
    //TODO:�����ؓo�^�����Ȃ�processSettlementBehavior()���Ăяo���̂͏�������������������Ȃ��B
    //�����蔻��̈���X�V���Ă���processSettlementBehavior�Ŕ����ؓo�^���邱�ƁB
}

void LaserChip::processPreDraw() {
    if (0 < _chip_kind && _chip_kind < 4) {
        //1~3��\���Ώۂɂ���
        GgafDxFigureActor::processPreDraw();
    }
}

void LaserChip::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
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
    if (_pChip_infront) {
        _pChip_infront->_pChip_behind = nullptr;
    }
    _pChip_infront = nullptr;
    if (_pChip_behind) {
        _pChip_behind->_pChip_infront = nullptr;
    }
    _pChip_behind = nullptr;
}

int LaserChip::isOutOfView() {
    if (_offscreen_kind == -1) {
        const dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*_rate_of_length*2.0f;//�|����2�͋��E����傫�����āA��ʋ��E�̃`���c�L��}����
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
                            if (_dest_from_vppln_back < bound) {
                                //Viewport�͈͓�
                                _offscreen_kind = 0;
                            } else {
                                //�����ʂ�艜�Ŕ͈͊O
                                _offscreen_kind = 6;
                            }
                        } else {
                            //��O���ʂ���O�Ŕ͈͊O
                            _offscreen_kind = 5;
                        }
                    } else {
                        //�E���ʂ��E�Ŕ͈͊O
                        _offscreen_kind = 4;
                    }
                } else {
                    //�����ʂ�荶�Ŕ͈͊O
                    _offscreen_kind = 3;
                }
            } else {
                //�����ʂ�艺�Ŕ͈͊O
                _offscreen_kind = 2;
            }
        } else {
            //�㕽�ʂ���Ŕ͈͊O
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}

void LaserChip::registerHitAreaCube_AutoGenMidColli(int prm_edge_length) {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _middle_colli_able = true;
    _hitarea_edge_length = prm_edge_length;
    _hitarea_edge_length_2   = _hitarea_edge_length * 2;
    _hitarea_edge_length_3   = _hitarea_edge_length * 3;
    _hitarea_edge_length_3_2 = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6   = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6_2 = _hitarea_edge_length_6 * 2;
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(4);
    pChecker->setColliAACube(0, prm_edge_length);
    pChecker->setColliAACube(1, prm_edge_length);
    pChecker->setColliAACube(2, prm_edge_length);
    pChecker->setColliAACube(3, prm_edge_length);
    pChecker->enable(0);
    pChecker->disable(1);
    pChecker->disable(2);
    pChecker->disable(3);
    setHitAble(true);
}


void LaserChip::createVertexInstanceData(void* prm, GgafDxMassMeshModel::VertexInstanceDataInfo* out_info) {
    out_info->paElement = NEW D3DVERTEXELEMENT9[9];
    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
    out_info->paElement[0].Stream = 1;
    out_info->paElement[0].Offset = st1_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*4;
    //float _21, _22, _23, _24;  // : TEXCOORD2  World�ϊ��s��A�Q�s��
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*4;
    //float _31, _32, _33, _34;  // : TEXCOORD3  World�ϊ��s��A�R�s��
    out_info->paElement[2].Stream = 1;
    out_info->paElement[2].Offset = st1_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 3;
    st1_offset_next += sizeof(float)*4;
    //float _41, _42, _43, _44;  // : TEXCOORD4  World�ϊ��s��A�S�s��
    out_info->paElement[3].Stream = 1;
    out_info->paElement[3].Offset = st1_offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 4;
    st1_offset_next += sizeof(float)*4;

    //float _f_11, _f_12, _f_13, _14;   // : TEXCOORD5  �O���`�b�vWorld�ϊ��s��A�P�s��
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*4;
    //float _f_21, _f_22, _f_23, _24;   // : TEXCOORD6  �O���`�b�vWorld�ϊ��s��A�Q�s��
    out_info->paElement[5].Stream = 1;
    out_info->paElement[5].Offset = st1_offset_next;
    out_info->paElement[5].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[5].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[5].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[5].UsageIndex = 6;
    st1_offset_next += sizeof(float)*4;
    //float _f_31, _f_32, _f_33, _34;   // : TEXCOORD7  �O���`�b�vWorld�ϊ��s��A�R�s��
    out_info->paElement[6].Stream = 1;
    out_info->paElement[6].Offset = st1_offset_next;
    out_info->paElement[6].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[6].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[6].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[6].UsageIndex = 7;
    st1_offset_next += sizeof(float)*4;
    //float _f_41, _f_42, _f_43, _44;   // : TEXCOORD8  �O���`�b�vWorld�ϊ��s��A�S�s��
    out_info->paElement[7].Stream = 1;
    out_info->paElement[7].Offset = st1_offset_next;
    out_info->paElement[7].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[7].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[7].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[7].UsageIndex = 8;
    st1_offset_next += sizeof(float)*4;

    //float _chip_kind, _force_alpha, _power;   // : TEXCOORD9  �`�b�v��ʁA�������A�Η͗�
    out_info->paElement[8].Stream = 1;
    out_info->paElement[8].Offset = st1_offset_next;
    out_info->paElement[8].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[8].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[8].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[8].UsageIndex = 9;
    st1_offset_next += sizeof(float)*3;
    // <---- Stream = 1

    out_info->element_num = 9;
    out_info->size_vertex_unit_instancedata = sizeof(LaserChip::VERTEX_instancedata);
    out_info->pInstancedata = LaserChip::_aInstancedata;
}

void LaserChip::processDraw() {
    int draw_set_num = 0; //GgafDxMassMeshActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDxMassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_set_num = pMassMeshModel->_set_num;
    const hashval hash_technique = _hash_technique;
    VERTEX_instancedata* paInstancedata = LaserChip::_aInstancedata;
    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    GgafDxFigureActor* pDrawActor = this;
    LaserChip* pChip = nullptr;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == hash_technique) {
            pChip = (LaserChip*)pDrawActor;
            if (pChip->_pChip_infront) {
                memcpy(paInstancedata, &(pChip->_matWorld), size_of_D3DXMATRIX);
                memcpy(&(paInstancedata->_f_11), &(pChip->_pChip_infront->_matWorld), size_of_D3DXMATRIX);
                paInstancedata->_chip_kind = pChip->_chip_kind;
                paInstancedata->_force_alpha = pChip->_force_alpha;
                paInstancedata->_power = pChip->_power;
                ++paInstancedata;
                draw_set_num++;
            }
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g
            if (draw_set_num >= model_max_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }
    ((GgafDxMassMeshModel*)_pMassMeshModel)->GgafDxMassMeshModel::draw(this, draw_set_num);
}


LaserChip::~LaserChip() {
    GGAF_DELETE(_pColliChecker);
}

