#include "stdafx.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultUniverse.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliAAB.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/util/LinearOctreeActorElem.h"
#include "jp/ggaf/lib/util/StgUtil.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

int CollisionChecker3D::_num_check = 0;
LinearOctreeForActor* CollisionChecker3D::_pLinearOctree = nullptr;
CollisionChecker3D::CollisionChecker3D(GgafDxGeometricActor* prm_pActor) : GgafDxChecker(prm_pActor) {
    if (CollisionChecker3D::_pLinearOctree == nullptr) {
        CollisionChecker3D::_pLinearOctree  = ((DefaultUniverse*)(GgafGod::_pGod->_pUniverse))->_pLinearOctree;
    }
    _pElem = NEW LinearOctreeActorElem(prm_pActor, 0);
    _need_update_aabb = true;
}


void CollisionChecker3D::setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("CollisionChecker3D::setColli_AABB()["<<getTargetActor()->getName()<<"]  �܂� makeCollision �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("CollisionChecker3D::setColli_AABB()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliSphere();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_SPHERE) {
        throwGgafCriticalException("CollisionChecker3D::setColliSphere()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��SPHERE�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
#ifdef MY_DEBUG
    if (r < 0) {
        throwGgafCriticalException("CollisionChecker3D::setColliSphere()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��SPHERE�̔��a�����̐��ł��Br="<<r);
    }
#endif
    ColliSphere* pSphere = (ColliSphere*)_pCollisionArea->_papColliPart[prm_index];
    pSphere->_shape_kind = COLLI_SPHERE;
    pSphere->_is_valid_flg = true;
    pSphere->set(x, y, z, r, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}


void CollisionChecker3D::setColliAAB(int prm_index,
                                     coord x1,
                                     coord y1,
                                     coord z1,
                                     coord x2,
                                     coord y2,
                                     coord z2,
                                     bool rot_x,
                                     bool rot_y,
                                     bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAB()["<<getTargetActor()->getName()<<"]  �܂� makeCollision �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAB()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAB();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAB) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAB()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��AABB�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAAB* pAAB = (ColliAAB*)_pCollisionArea->_papColliPart[prm_index];
    pAAB->_shape_kind = COLLI_AAB;
    pAAB->_is_valid_flg = true;
    pAAB->set(x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}

void CollisionChecker3D::setColliAAPrism(int prm_index,
                                         coord x1, coord y1, coord z1,
                                         coord x2, coord y2, coord z2,
                                         int pos_prism,
                                         bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAPrism()["<<getTargetActor()->getName()<<"]  �܂� makeCollision �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAPrism()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAPrism();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAPRISM) {
        throwGgafCriticalException("CollisionChecker3D::setColliAAPrism()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��AAPRISM�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAAPrism* pAAPrism = (ColliAAPrism*)_pCollisionArea->_papColliPart[prm_index];
    pAAPrism->_shape_kind = COLLI_AAPRISM;
    pAAPrism->_is_valid_flg = true;
    pAAPrism->set(x1, y1, z1, x2, y2, z2, pos_prism, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}


void CollisionChecker3D::updateHitArea() {
    GgafDxGeometricActor* pActor = _pActor;
    GgafDxCollisionArea* pCollisionArea = _pCollisionArea;
    if (pActor == nullptr || pCollisionArea == nullptr) {
        return;
    }
    if (pActor->isActiveInTheTree() ) {
        GgafDxCollisionPart* pColliPart;
        for (int i = 0; i < pCollisionArea->_colli_part_num; i++) {
#ifdef MY_DEBUG
            if (_pCollisionArea->_papColliPart[i] == nullptr) {
                throwGgafCriticalException("CollisionChecker3D::updateHitArea()["<<getTargetActor()->getName()<<"]  _papColliPart["<<i<<"]��nullptr�ł��B");
            }
#endif
            pColliPart = pCollisionArea->_papColliPart[i];
            if (pColliPart->_rot) {
                pColliPart->rotateRxRzRy(pActor->_rx, pActor->_ry, pActor->_rz);
                _need_update_aabb = true;
            }
        }
        if (_need_update_aabb) {
            pCollisionArea->updateAABB(); //�ŊO��̋��EAABB�X�V
            _need_update_aabb = false;
        }

        //�W���؂ɓo�^�I
        _pElem->_kindbit = pActor->getMyGroupHead()->_kind;
        _pLinearOctree->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                             pActor->_y + pCollisionArea->_aabb_y1,
                                             pActor->_z + pCollisionArea->_aabb_z1,
                                             pActor->_x + pCollisionArea->_aabb_x2,
                                             pActor->_y + pCollisionArea->_aabb_y2,
                                             pActor->_z + pCollisionArea->_aabb_z2);

    }
}


bool CollisionChecker3D::isHit(GgafDxCore::GgafDxChecker* prm_pOppChecker) {
    GgafDxCollisionArea* pCollisionArea = _pCollisionArea;
    GgafDxCollisionArea* pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //����̓����蔻��̈�
    GgafDxGeometricActor* pOppActor = prm_pOppChecker->_pActor;                //����̃A�N�^�[
    int colli_part_num = pCollisionArea->_colli_part_num;
    for (int i = 0; i < colli_part_num; i++) {
        GgafDxCollisionPart* pColliPart = pCollisionArea->_papColliPart[i];
        if (!pColliPart->_is_valid_flg) { continue; }
        int shape_kind = pColliPart->_shape_kind;
        int opp_colli_part_num = pOppCollisionArea->_colli_part_num; //����̓����蔻��v�f��
        for (int j = 0; j < opp_colli_part_num; j++) {
            GgafDxCollisionPart* pOppColliPart = pOppCollisionArea->_papColliPart[j];
            if (!pOppColliPart->_is_valid_flg) { continue; }
            int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
            CollisionChecker3D::_num_check++;
#endif
            if (shape_kind == COLLI_AAB) {
                if (opp_shape_kind == COLLI_AAB) {
                    //��AAB �� AAB��
                    if (UTIL::isHit(_pActor  , (ColliAAB*)pColliPart,
                                    pOppActor, (ColliAAB*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //��AAB �� ����
                     if (UTIL::isHit(_pActor  , (ColliAAB*)pColliPart,
                                     pOppActor, (ColliSphere*)pOppColliPart)) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //��AAB �� AAPrism��
                     if (UTIL::isHit(pOppActor, (ColliAAPrism*)pOppColliPart,
                                     _pActor  , (ColliAAB*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 }

            } else if (shape_kind == COLLI_SPHERE) {
                if (opp_shape_kind == COLLI_AAB) {
                    //���� �� AAB��
                    if (UTIL::isHit(pOppActor, (ColliAAB*)pOppColliPart,
                                    _pActor  , (ColliSphere*)pColliPart )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //���� �� ����
                    if (UTIL::isHit(_pActor  , (ColliSphere*)pColliPart,
                                    pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //���� �� AAPrism��
                    if (UTIL::isHit(pOppActor, (ColliAAPrism*)pOppColliPart,
                                    _pActor  , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }

            } else if (shape_kind == COLLI_AAPRISM) {
                if (opp_shape_kind == COLLI_AAB) {
                    //��AAPrism �� AAB��
                    if (UTIL::isHit(_pActor  , (ColliAAPrism*)pColliPart,
                                    pOppActor, (ColliAAB*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //��AAPrism �� ����
                    if (UTIL::isHit(_pActor  , (ColliAAPrism*)pColliPart,
                                    pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                   //��AAPrism �� AAPrism��
                   //TODO: �l���邾���ŏd�����Ȃ肻���A�Ƃ������߂�ǂ��������Ȋ���������G�B
                   //���Ԃ�����΍l���悤�E�E�E�B���͖��Ή��B
                   throwGgafCriticalException("AAPrism �� AAPrism�̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                                              _pActor->getName()<<" vs "<<pOppActor->getName());
                   return false;
                }
            }

        }

    }
    return false;
}



CollisionChecker3D::~CollisionChecker3D() {
    GGAF_DELETE(_pElem);
    GGAF_DELETE_NULLABLE(_pCollisionArea);
    //�����蔻��͂Ȃ���������Ȃ��B���̏ꍇ_pElem�͖��ʂȐ����Ɖ�������邱�ƂɂȂ�B�B
}