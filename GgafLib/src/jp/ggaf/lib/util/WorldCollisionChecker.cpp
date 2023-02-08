#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/debug/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/debug/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/debug/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/debug/ColliSphereActor.h"
#endif

using namespace GgafLib;

#ifdef MY_DEBUG
unsigned int WorldCollisionChecker::_num_check = 0;
unsigned int WorldCollisionChecker::_num_check_actors = 0;
unsigned int WorldCollisionChecker::_num_otoku_check = 0;
unsigned int WorldCollisionChecker::_num_zannen_check = 0;
#endif
WorldCollisionChecker::WorldCollisionChecker(GgafDx::GeometricActor* prm_pActor) : GgafDx::CollisionChecker(prm_pActor) {
}

void WorldCollisionChecker::changeColliSphereR(int prm_index, coord r) {
    ColliSphere* pSphere = (ColliSphere*)_pActiveCollisionArea->_papColliPart[prm_index];
    pSphere->changeR(r);
    _pActiveCollisionArea->_need_update_aabb = true;
}

void WorldCollisionChecker::setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pActiveCollisionArea == nullptr) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �܂� addCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pActiveCollisionArea->_colli_part_num) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pActiveCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pActiveCollisionArea->_papColliPart[prm_index] = NEW ColliSphere();
    }
#ifdef MY_DEBUG
    if (_pActiveCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_SPHERE) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��SPHERE�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
#ifdef MY_DEBUG
    if (r < 0) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��SPHERE�̔��a�����̐��ł��Br="<<r);
    }
#endif
    ColliSphere* pSphere = (ColliSphere*)_pActiveCollisionArea->_papColliPart[prm_index];
    bool rot_before = pSphere->_rot;
    pSphere->_shape_kind = COLLI_SPHERE;
    pSphere->_is_valid_flg = true;
    pSphere->set(x, y, z, r, rot_x, rot_y, rot_z);
    _pActiveCollisionArea->_need_update_aabb = true;
    _pActiveCollisionArea->_rotate_part_num += (rot_before ? (pSphere->_rot ?  0 : -1)
                                                     : (pSphere->_rot ?  1 :  0) ) ;
//    _is_enable = true;
}

void WorldCollisionChecker::moveColliAABoxPos(int prm_index, coord cx, coord cy, coord cz) {
    ColliAABox* pAABox = (ColliAABox*)_pActiveCollisionArea->_papColliPart[prm_index];
    pAABox->movePos(cx, cy, cz);
    _pActiveCollisionArea->_need_update_aabb = true;
}

void WorldCollisionChecker::setColliAABox(int prm_index,
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
    if (_pActiveCollisionArea == nullptr) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �܂� addCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pActiveCollisionArea->_colli_part_num) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pActiveCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pActiveCollisionArea->_papColliPart[prm_index] = NEW ColliAABox();
    }
#ifdef MY_DEBUG
    if (_pActiveCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AABOX) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��AABB�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAABox* pAABox = (ColliAABox*)_pActiveCollisionArea->_papColliPart[prm_index];
    bool rot_before = pAABox->_rot;
    pAABox->_shape_kind = COLLI_AABOX;
    pAABox->_is_valid_flg = true;
    pAABox->set(x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z);
    _pActiveCollisionArea->_need_update_aabb = true;
    _pActiveCollisionArea->_rotate_part_num += (rot_before ? (pAABox->_rot ?  0 : -1)
                                                     : (pAABox->_rot ?  1 :  0) ) ;
//    _is_enable = true;
}

void WorldCollisionChecker::setColliAAPrism(int prm_index,
                                       coord x1, coord y1, coord z1,
                                       coord x2, coord y2, coord z2,
                                       pos_t pos_info,
                                       bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pActiveCollisionArea == nullptr) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �܂� addCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pActiveCollisionArea->_colli_part_num) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pActiveCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pActiveCollisionArea->_papColliPart[prm_index] = NEW ColliAAPrism();
    }
#ifdef MY_DEBUG
    if (_pActiveCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAPRISM) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��AAPRISM�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAAPrism* pAAPrism = (ColliAAPrism*)_pActiveCollisionArea->_papColliPart[prm_index];
    bool rot_before = pAAPrism->_rot;
    pAAPrism->_shape_kind = COLLI_AAPRISM;
    pAAPrism->_is_valid_flg = true;
    pAAPrism->set(x1, y1, z1, x2, y2, z2, pos_info, rot_x, rot_y, rot_z);
    _pActiveCollisionArea->_need_update_aabb = true;
    _pActiveCollisionArea->_rotate_part_num += (rot_before ? (pAAPrism->_rot ?  0 : -1)
                                                     : (pAAPrism->_rot ?  1 :  0) ) ;
//    _is_enable = true;
}

void WorldCollisionChecker::setColliAAPyramid(int prm_index,
                                         coord x1, coord y1, coord z1,
                                         coord x2, coord y2, coord z2,
                                         pos_t pos_info,
                                         bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pActiveCollisionArea == nullptr) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �܂� addCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pActiveCollisionArea->_colli_part_num) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pActiveCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pActiveCollisionArea->_papColliPart[prm_index] = NEW ColliAAPyramid();
    }
#ifdef MY_DEBUG
    if (_pActiveCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAPYRAMID) {
        throwCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��COLLI_AAPYRAMID�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAAPyramid* pAAPyramid = (ColliAAPyramid*)_pActiveCollisionArea->_papColliPart[prm_index];
    bool rot_before = pAAPyramid->_rot;
    pAAPyramid->_shape_kind = COLLI_AAPYRAMID;
    pAAPyramid->_is_valid_flg = true;
    pAAPyramid->set(x1, y1, z1, x2, y2, z2, pos_info, rot_x, rot_y, rot_z);
    _pActiveCollisionArea->_need_update_aabb = true;
    _pActiveCollisionArea->_rotate_part_num += (rot_before ? (pAAPyramid->_rot ?  0 : -1)
                                                     : (pAAPyramid->_rot ?  1 :  0) ) ;
//    _is_enable = true;
}

GgafDx::CollisionPart* WorldCollisionChecker::getLastHitCollisionPart() {
    int hit_colli_part_index = _pActiveCollisionArea->_hit_colli_part_index;
    if (hit_colli_part_index >= 0) {
        return _pActiveCollisionArea->_papColliPart[hit_colli_part_index];
    } else {
        return nullptr;
    }
}

void WorldCollisionChecker::drawHitArea(GgafDx::CollisionChecker* prm_pChecker) {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(prm_pChecker);
    ColliAAPrismActor::get()->drawHitarea(prm_pChecker);
    ColliAAPyramidActor::get()->drawHitarea(prm_pChecker);
    ColliSphereActor::get()->drawHitarea(prm_pChecker);
#endif
}

void WorldCollisionChecker::releaseHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::release();
    ColliAAPrismActor::release();
    ColliAAPyramidActor::release();
    ColliSphereActor::release();
#endif
}


WorldCollisionChecker::~WorldCollisionChecker() {
    //�����蔻��͂Ȃ���������Ȃ��B���̏ꍇ_pElem�͖��ʂȐ����Ɖ�������邱�ƂɂȂ�B�B
}
