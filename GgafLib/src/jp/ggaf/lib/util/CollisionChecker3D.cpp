#include "jp/ggaf/lib/util/CollisionChecker3D.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/util/LinearOctreeActorElem.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
#ifdef MY_DEBUG
unsigned int CollisionChecker3D::_num_check = 0;
#endif
CollisionChecker3D::CollisionChecker3D(GgafDxGeometricActor* prm_pActor) : GgafDxChecker(prm_pActor) ,
        _pLinearOctree(P_GOD->getSpacetime()->getLinearOctree()),
        _pElem(NEW LinearOctreeActorElem(_pLinearOctree, prm_pActor, 0))
{
    _need_update_aabb = true;
}

void CollisionChecker3D::setColliSphere(int prm_index, coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �܂� createCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliSphere();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_SPHERE) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��SPHERE�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
#ifdef MY_DEBUG
    if (r < 0) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��SPHERE�̔��a�����̐��ł��Br="<<r);
    }
#endif
    ColliSphere* pSphere = (ColliSphere*)_pCollisionArea->_papColliPart[prm_index];
    pSphere->_shape_kind = COLLI_SPHERE;
    pSphere->_is_valid_flg = true;
    pSphere->set(x, y, z, r, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}


void CollisionChecker3D::setColliAABox(int prm_index,
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
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �܂� createCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAABox();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AABOX) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��AABB�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAABox* pAABox = (ColliAABox*)_pCollisionArea->_papColliPart[prm_index];
    pAABox->_shape_kind = COLLI_AABOX;
    pAABox->_is_valid_flg = true;
    pAABox->set(x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}

void CollisionChecker3D::setColliAAPrism(int prm_index,
                                         coord x1, coord y1, coord z1,
                                         coord x2, coord y2, coord z2,
                                         int pos_prism,
                                         bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �܂� createCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAPrism();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAPRISM) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��AAPRISM�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAAPrism* pAAPrism = (ColliAAPrism*)_pCollisionArea->_papColliPart[prm_index];
    pAAPrism->_shape_kind = COLLI_AAPRISM;
    pAAPrism->_is_valid_flg = true;
    pAAPrism->set(x1, y1, z1, x2, y2, z2, pos_prism, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}

void CollisionChecker3D::setColliAAPyramid(int prm_index,
                                           coord x1, coord y1, coord z1,
                                           coord x2, coord y2, coord z2,
                                           int pos_pyramid,
                                           bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (_pCollisionArea == nullptr) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �܂� createCollisionArea �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_colli_part_num) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == nullptr) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAPyramid();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAPYRAMID) {
        throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��COLLI_AAPYRAMID�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAAPyramid* pAAPyramid = (ColliAAPyramid*)_pCollisionArea->_papColliPart[prm_index];
    pAAPyramid->_shape_kind = COLLI_AAPYRAMID;
    pAAPyramid->_is_valid_flg = true;
    pAAPyramid->set(x1, y1, z1, x2, y2, z2, pos_pyramid, rot_x, rot_y, rot_z);
    _need_update_aabb = true;
}

void CollisionChecker3D::updateHitArea() {
    GgafDxGeometricActor* const pActor = _pActor;
    GgafDxCollisionArea* const pCollisionArea = _pCollisionArea;
    if (pActor == nullptr || pCollisionArea == nullptr) {
        return;
    }
    if (pActor->isActiveInTheTree() && pActor->isActive()) {
        GgafDxCollisionPart* pColliPart;
        for (int i = 0; i < pCollisionArea->_colli_part_num; i++) {
#ifdef MY_DEBUG
            if (_pCollisionArea->_papColliPart[i] == nullptr) {
                throwGgafCriticalException("["<<getTargetActor()->getName()<<"]  _papColliPart["<<i<<"]��nullptr�ł��B");
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

        //�����؂ɓo�^�I
        _pElem->_kindbit = pActor->getMyGroupHead()->_kind;
#ifdef MY_DEBUG
        if (_pElem->_kindbit == 0) {
            _TRACE_("���x���� CollisionChecker3D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")�̎�ʂ�0�ɂ�������炸�A�����؂ɓo�^���悤�Ƃ��Ă��܂��B�Ȃ��ł����H�B");
        }
#endif
        _pLinearOctree->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                             pActor->_y + pCollisionArea->_aabb_y1,
                                             pActor->_z + pCollisionArea->_aabb_z1,
                                             pActor->_x + pCollisionArea->_aabb_x2,
                                             pActor->_y + pCollisionArea->_aabb_y2,
                                             pActor->_z + pCollisionArea->_aabb_z2);

    }
}


bool CollisionChecker3D::isHit(const GgafDxCore::GgafDxChecker* const prm_pOppChecker) {
    GgafDxCollisionArea* const pCollisionArea = _pCollisionArea;
    GgafDxCollisionArea* const pOppCollisionArea = prm_pOppChecker->_pCollisionArea; //����̓����蔻��̈�
    const GgafDxGeometricActor* const pActor = _pActor;                //����̃A�N�^�[
    const GgafDxGeometricActor* const pOppActor = prm_pOppChecker->_pActor;                //����̃A�N�^�[
    const int colli_part_num = pCollisionArea->_colli_part_num;
    const int opp_colli_part_num = pOppCollisionArea->_colli_part_num; //����̓����蔻��v�f��

    //�����̓����蔻��v�f�����A�N�^�[���m�̏ꍇ�A
    //�܂��ŊO���EAABox�œ����蔻����s���āA�q�b�g����Ό����ɓ����蔻����s���B
    if (colli_part_num > 1 && opp_colli_part_num > 1) {
#ifdef MY_DEBUG
        CollisionChecker3D::_num_check++;
#endif
        bool is_hit_bound_aabb = false;
        if (pActor->_x + pCollisionArea->_aabb_x2 >= pOppActor->_x + pOppCollisionArea->_aabb_x1) {
            if (pActor->_x + pCollisionArea->_aabb_x1 <= pOppActor->_x + pOppCollisionArea->_aabb_x2) {
                if (pActor->_z + pCollisionArea->_aabb_z2 >= pOppActor->_z + pOppCollisionArea->_aabb_z1) {
                    if (pActor->_z + pCollisionArea->_aabb_z1 <= pOppActor->_z + pOppCollisionArea->_aabb_z2) {
                        if (pActor->_y + pCollisionArea->_aabb_y2 >= pOppActor->_y + pOppCollisionArea->_aabb_y1) {
                            if (pActor->_y + pCollisionArea->_aabb_y1 <= pOppActor->_y + pOppCollisionArea->_aabb_y2) {
                                is_hit_bound_aabb = true;
                            }
                        }
                    }
                }
            }
        }
        if (!is_hit_bound_aabb) {
            //�ŊO���EAABox�Ńq�b�g���Ă��Ȃ�
            return false;
        }
    }

    for (int i = 0; i < colli_part_num; i++) {
        const GgafDxCollisionPart* const pColliPart = pCollisionArea->_papColliPart[i];
        if (!pColliPart->_is_valid_flg) { continue; }
        const int shape_kind = pColliPart->_shape_kind;
        for (int j = 0; j < opp_colli_part_num; j++) {
            const GgafDxCollisionPart* const pOppColliPart = pOppCollisionArea->_papColliPart[j];
            if (!pOppColliPart->_is_valid_flg) { continue; }
            const int opp_shape_kind = pOppColliPart->_shape_kind;
#ifdef MY_DEBUG
            CollisionChecker3D::_num_check++;
#endif
            if (shape_kind == COLLI_AABOX) {
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAB �� AAB��
                    if (UTIL::isHit(pActor   , (ColliAABox*)pColliPart,
                                    pOppActor, (ColliAABox*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //��AAB �� ����
                     if (UTIL::isHit(pActor   , (ColliAABox*)pColliPart,
                                     pOppActor, (ColliSphere*)pOppColliPart)) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //��AAB �� AAPrism��
                     if (UTIL::isHit(pOppActor, (ColliAAPrism*)pOppColliPart,
                                     pActor   , (ColliAABox*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                     //��AAB �� AAPyramid��
                     if (UTIL::isHit(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                     pActor   , (ColliAABox*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 }

            } else if (shape_kind == COLLI_SPHERE) {
                if (opp_shape_kind == COLLI_AABOX) {
                    //���� �� AAB��
                    if (UTIL::isHit(pOppActor, (ColliAABox*)pOppColliPart,
                                    pActor   , (ColliSphere*)pColliPart )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //���� �� ����
                    if (UTIL::isHit(pActor  , (ColliSphere*)pColliPart,
                                    pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //���� �� AAPrism��
                    if (UTIL::isHit(pOppActor, (ColliAAPrism*)pOppColliPart,
                                    pActor   , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //���� �� AAPyramid��
                    if (UTIL::isHit(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                    pActor   , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }

            } else if (shape_kind == COLLI_AAPRISM) {
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAPrism �� AAB��
                    if (UTIL::isHit(pActor   , (ColliAAPrism*)pColliPart,
                                    pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //��AAPrism �� ����
                    if (UTIL::isHit(pActor   , (ColliAAPrism*)pColliPart,
                                    pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }  else if (opp_shape_kind == COLLI_AAPRISM) {
                    //��AAPrism �� AAPrism��
                    //TODO: �l���邾���ŏd�����Ȃ肻���A�Ƃ������߂�ǂ��������Ȋ���������G�B
                    //���Ԃ�����΍l���悤�E�E�E�B���͖��Ή��B
                    throwGgafCriticalException("AAPrism �� AAPrism �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                   return false;
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //��AAPrism �� AAPyramid��
                    //TODO: ���͖��Ή��B
                    throwGgafCriticalException("AAPrism �� AAPyramid �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                 }
            } else if (shape_kind == COLLI_AAPYRAMID) {
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAPyramid �� AAB��
                    if (UTIL::isHit(pActor  , (ColliAAPyramid*)pColliPart,
                                    pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //��AAPyramid �� ����
                    if (UTIL::isHit(pActor  , (ColliAAPyramid*)pColliPart,
                                    pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //��AAPyramid �� AAPrism��
                    //TODO: ���͖��Ή��B
                    throwGgafCriticalException("AAPyramid �� AAPrism �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<_pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //��AAPyramid �� AAPyramid��
                    //TODO: ���͖��Ή��B
                    throwGgafCriticalException("AAPyramid �� AAPyramid �̓����蔻�菈�������݂��܂��B����ȏ����͖�������Ă܂���B "<<
                            pActor <<"["<<_pActor->getName()<<"] vs "<<pOppActor<<"["<<pOppActor->getName()<<"]");
                    return false;
                }
            }
        }

    }
    return false;
}


CollisionChecker3D::~CollisionChecker3D() {
    delete _pElem;
    GGAF_DELETE_NULLABLE(_pCollisionArea);
    //�����蔻��͂Ȃ���������Ȃ��B���̏ꍇ_pElem�͖��ʂȐ����Ɖ�������邱�ƂɂȂ�B�B
}
