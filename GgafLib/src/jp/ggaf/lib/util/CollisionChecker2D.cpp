#include "jp/ggaf/lib/util/CollisionChecker2D.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/util/GgafLinearQuadtree.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CollisionChecker2D::CollisionChecker2D(GgafDxGeometricActor* prm_pActor) : CollisionChecker(prm_pActor) ,
        _pLinearQuadtree(pGOD->getSpacetime()->getLinearQuadtree()),
        _pElem(NEW GgafTreeElem<2u>(_pLinearQuadtree->_paQuadrant, prm_pActor))
{
    _need_update_aabb = true;
}

void CollisionChecker2D::updateHitArea() {
    GgafDxCollisionArea* const pCollisionArea = _pCollisionArea;
    if (pCollisionArea == nullptr) {
        return;
    }
    GgafDxGeometricActor* const pActor = _pActor;
    if (pActor->isActiveInTheTree()) {
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
            _pElem->_kind = pActor->lookUpKind();
        }

        //�����؂ɓo�^�I
#ifdef MY_DEBUG
        if (_pElem->_kind == 0) {
            _TRACE_("���x���� CollisionChecker2D::updateHitArea() pActor="<<pActor->getName()<<"("<<pActor<<")�̎�ʂ�0�ɂ�������炸�A�����؂ɓo�^���悤�Ƃ��Ă��܂��B�Ȃ��ł����H�B");
        }
#endif
        _pLinearQuadtree->registerElem(_pElem, pActor->_x + pCollisionArea->_aabb_x1,
                                               pActor->_y + pCollisionArea->_aabb_y1,
                                               pActor->_x + pCollisionArea->_aabb_x2,
                                               pActor->_y + pCollisionArea->_aabb_y2);

    }
}

bool CollisionChecker2D::isHit(const GgafDxCore::GgafDxChecker* const prm_pOppChecker) {
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
        CollisionChecker::_num_check++;
#endif
        bool is_hit_bound_aabb = false;
        if (pActor->_x + pCollisionArea->_aabb_x2 >= pOppActor->_x + pOppCollisionArea->_aabb_x1) {
            if (pActor->_x + pCollisionArea->_aabb_x1 <= pOppActor->_x + pOppCollisionArea->_aabb_x2) {
                if (pActor->_y + pCollisionArea->_aabb_y2 >= pOppActor->_y + pOppCollisionArea->_aabb_y1) {
                    if (pActor->_y + pCollisionArea->_aabb_y1 <= pOppActor->_y + pOppCollisionArea->_aabb_y2) {
                        is_hit_bound_aabb = true;
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
            CollisionChecker::_num_check++;
#endif
            if (shape_kind == COLLI_AABOX) {
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAB �� AAB��
                    if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                 } else if (opp_shape_kind == COLLI_SPHERE) {
                     //��AAB �� ����
                     if (UTIL::isHit2D(pActor   , (ColliAABox*)pColliPart,
                                       pOppActor, (ColliSphere*)pOppColliPart)) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPRISM) {
                     //��AAB �� AAPrism��
                     if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                     //��AAB �� AAPyramid��
                     if (UTIL::isHit2D(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                       pActor   , (ColliAABox*)pColliPart        )) {
                         pCollisionArea->_hit_colli_part_index = i;
                         pOppCollisionArea->_hit_colli_part_index = j;
                         return true;
                     }
                 }

            } else if (shape_kind == COLLI_SPHERE) {
                if (opp_shape_kind == COLLI_AABOX) {
                    //���� �� AAB��
                    if (UTIL::isHit2D(pOppActor, (ColliAABox*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //���� �� ����
                    if (UTIL::isHit2D(pActor  , (ColliSphere*)pColliPart,
                                      pOppActor, (ColliSphere*)pOppColliPart)) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPRISM) {
                    //���� �� AAPrism��
                    if (UTIL::isHit2D(pOppActor, (ColliAAPrism*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_AAPYRAMID) {
                    //���� �� AAPyramid��
                    if (UTIL::isHit2D(pOppActor, (ColliAAPyramid*)pOppColliPart,
                                      pActor   , (ColliSphere*)pColliPart     )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                }

            } else if (shape_kind == COLLI_AAPRISM) {
                if (opp_shape_kind == COLLI_AABOX) {
                    //��AAPrism �� AAB��
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //��AAPrism �� ����
                    if (UTIL::isHit2D(pActor   , (ColliAAPrism*)pColliPart,
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
                    if (UTIL::isHit2D(pActor   , (ColliAAPyramid*)pColliPart,
                                      pOppActor, (ColliAABox*)pOppColliPart  )) {
                        pCollisionArea->_hit_colli_part_index = i;
                        pOppCollisionArea->_hit_colli_part_index = j;
                        return true;
                    }
                } else if (opp_shape_kind == COLLI_SPHERE) {
                    //��AAPyramid �� ����
                    if (UTIL::isHit2D(pActor   , (ColliAAPyramid*)pColliPart,
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


CollisionChecker2D::~CollisionChecker2D() {
    delete _pElem;
    //�����蔻��͂Ȃ���������Ȃ��B���̏ꍇ_pElem�͖��ʂȐ����Ɖ�������邱�ƂɂȂ�B�B
}
