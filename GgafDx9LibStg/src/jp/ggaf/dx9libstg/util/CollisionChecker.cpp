#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

int CollisionChecker::_num_check = 0;
LinearOctreeForActor* CollisionChecker::_pLinearOctree = NULL;
CollisionChecker::CollisionChecker(GgafDx9GeometricActor* prm_pActor) : GgafDx9Checker(prm_pActor) {
    if (CollisionChecker::_pLinearOctree == NULL) {
        CollisionChecker::_pLinearOctree  = ((DefaultUniverse*)(GgafGod::_pGod->_pUniverse))->_pLinearOctree;
    }
    _pElem = NEW LinearOctreeActorElem(prm_pActor, 0);
    _need_update_aabb = true;
}

void CollisionChecker::makeCollision(int prm_nColliPart) {
    if (_pCollisionArea == NULL) {
        _pCollisionArea = NEW GgafDx9CollisionArea(prm_nColliPart);
    } else {
        throwGgafCriticalException("CollisionChecker::makeCollision ���� makeCollision ����Ă��܂��B");
    }
}

void CollisionChecker::setColliSphere(int prm_index, int x, int y, int z, int r, bool rotX, bool rotY, bool rotZ) {
#ifdef MY_DEBUG
    if (_pCollisionArea == NULL) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  �܂� makeCollision �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_nColliPart) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == NULL) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliSphere();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_SPHERE) {
        throwGgafCriticalException("CollisionChecker::setColliSphere()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��SPHERE�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliSphere* pSphere = (ColliSphere*)_pCollisionArea->_papColliPart[prm_index];
    pSphere->_shape_kind = COLLI_SPHERE;
    pSphere->_is_valid_flg = true;
    pSphere->set(x, y, z, r, rotX, rotY, rotZ);
    _need_update_aabb = true;
}


void CollisionChecker::setColliAAB(int prm_index,
                                   int x1,
                                   int y1,
                                   int z1,
                                   int x2,
                                   int y2,
                                   int z2,
                                   bool rotX,
                                   bool rotY,
                                   bool rotZ) {
#ifdef MY_DEBUG
    if (_pCollisionArea == NULL) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  �܂� makeCollision �����s���āA�v�f����錾���Ă��������B");
    }
    if (prm_index > _pCollisionArea->_nColliPart) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"�͔͈͊O�B");
    }
#endif
    if (_pCollisionArea->_papColliPart[prm_index] == NULL) {
        _pCollisionArea->_papColliPart[prm_index] = NEW ColliAAB();
    }
#ifdef MY_DEBUG
    if (_pCollisionArea->_papColliPart[prm_index]->_shape_kind != COLLI_AAB) {
        throwGgafCriticalException("CollisionChecker::setColli_AABB()["<<getTargetActor()->getName()<<"]  �v�f�C���f�b�N�X"<<prm_index<<"��AABB�łȂ��������߁A�X�V�͂ł��܂���B");
    }
#endif
    ColliAAB* pAAB = (ColliAAB*)_pCollisionArea->_papColliPart[prm_index];
    pAAB->_shape_kind = COLLI_AAB;
    pAAB->_is_valid_flg = true;
    pAAB->set(x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);
    _need_update_aabb = true;
}

void CollisionChecker::updateHitArea() {
    if (_pActor == NULL || _pCollisionArea == NULL) {
        return;
    }
    //if (_pActor->_can_hit_flg && _pActor->isActive() && _pActor->isOutOfView() == 0 ) {  //����O�͓o�^���Ȃ�
    if (_pActor->_can_hit_flg && _pActor->isActive() ) {
        GgafDx9CollisionPart* pColliPart;
        for (int i = 0; i < _pCollisionArea->_nColliPart; i++) {
#ifdef MY_DEBUG
            if (_pCollisionArea->_papColliPart[i] == NULL) {
                throwGgafCriticalException("CollisionChecker::updateHitArea()["<<getTargetActor()->getName()<<"]  _papColliPart["<<i<<"]��NULL�ł��B");
            }
#endif
            pColliPart = _pCollisionArea->_papColliPart[i];
            if (pColliPart->rotateRxRzRy(_pActor->_RX, _pActor->_RY, _pActor->_RZ)) {
                _need_update_aabb = true;
            }
        }
        if (_need_update_aabb) {
            //�ŊO���AABB�X�V
            _pCollisionArea->updateAABB();
        }

        //�W���؂ɓo�^�I
        _pElem->_kindbit = _pActor->getGroupActor()->_kind;
        _pLinearOctree->registElem(_pElem, _pActor->_X + _pCollisionArea->_AABB_X1,
                                           _pActor->_Y + _pCollisionArea->_AABB_Y1,
                                           _pActor->_Z + _pCollisionArea->_AABB_Z1,
                                           _pActor->_X + _pCollisionArea->_AABB_X2,
                                           _pActor->_Y + _pCollisionArea->_AABB_Y2,
                                           _pActor->_Z + _pCollisionArea->_AABB_Z2);

#ifdef MY_DEBUG
//        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//            _TRACE_("  CollisionChecker::updateHitArea()  registElem("<<(_pActor->getName())<<")=("<<
//                                             (_pActor->_X + _pCollisionArea->_AABB_X1)<<","<<
//                                             (_pActor->_Y + _pCollisionArea->_AABB_Y1)<<","<<
//                                             (_pActor->_Z + _pCollisionArea->_AABB_Z1)<<","<<
//                                             (_pActor->_X + _pCollisionArea->_AABB_X2)<<","<<
//                                             (_pActor->_Y + _pCollisionArea->_AABB_Y2)<<","<<
//                                             (_pActor->_Z + _pCollisionArea->_AABB_Z2)<<")");
//            //_pLinearOctree->putTree();
//
//        }
#endif
    }
}


bool CollisionChecker::isHit(GgafDx9Core::GgafDx9Checker* prm_pOppChecker) {
    //TODO: ���񂾂��剻���Ă���
    //�������AAAB �ȊO�ɓ����蔻��v�f���������Ȃ�A
    //�����蔻��`�F�b�N���\�b�h���AGgafDx9CollisionArea �� GgafDx9CollisionPart ��
    //���U�����Ď������āA�R�R�ł͌Ăяo�������ɂ��悤�E�E�E

    //�����蔻����s������̃A�N�^�[
    GgafDx9Core::GgafDx9GeometricActor* pOppActor = prm_pOppChecker->getTargetActor();
    //����̓����蔻��̈�
    GgafDx9CollisionArea* pOppCollisionArea = ((CollisionChecker*)prm_pOppChecker)->_pCollisionArea;

//    if (_pCollisionArea == NULL || pOppCollisionArea == NULL ||
//        _pActor->isOutOfView() > 0 || pOppActor->isOutOfView() > 0 ) {  //����O�͔��肵�Ȃ�

    if (_pCollisionArea == NULL || pOppCollisionArea == NULL) {
        return false;
    } else {
        GgafDx9CollisionPart* pColliPart;     //���g�̓����蔻��v�f
        GgafDx9CollisionPart* pOppColliPart;  //����̓����蔻��v�f
        for (int i = 0; i < _pCollisionArea->_nColliPart; i++) {
            pColliPart = _pCollisionArea->_papColliPart[i];
            if (pColliPart->_is_valid_flg) {
                for (int j = 0; j < pOppCollisionArea->_nColliPart; j++) {
                    pOppColliPart = pOppCollisionArea->_papColliPart[j];
                    if (pOppColliPart->_is_valid_flg) {
                        CollisionChecker::_num_check++;

                        if (pColliPart->_shape_kind == COLLI_AAB && pOppColliPart->_shape_kind == COLLI_AAB) {
                            //��AAB �� AAB��
                            ColliAAB* pAAB = (ColliAAB*)pColliPart;
                            ColliAAB* pOppABB = (ColliAAB*)pOppColliPart;
                            //������v���Ȃ��m�����������ȏ���(Z>Y>X)�ɔ���
                            if (_pActor->_Z + pAAB->_z2 >= pOppActor->_Z + pOppABB->_z1) {
                                if (_pActor->_Z + pAAB->_z1 <= pOppActor->_Z + pOppABB->_z2) {
                                    if (_pActor->_Y + pAAB->_y2 >= pOppActor->_Y + pOppABB->_y1) {
                                        if (_pActor->_Y + pAAB->_y1 <= pOppActor->_Y + pOppABB->_y2) {
                                            if (_pActor->_X + pAAB->_x2 >= pOppActor->_X + pOppABB->_x1) {
                                                if (_pActor->_X + pAAB->_x1 <= pOppActor->_X + pOppABB->_x2) {
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                        } else if (pColliPart->_shape_kind == COLLI_SPHERE && pOppColliPart->_shape_kind == COLLI_SPHERE) {
                            //���� �� ����
                            ColliSphere* pSphere = (ColliSphere*)pColliPart;
                            ColliSphere* pOppSphere = (ColliSphere*)pOppColliPart;
                            //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
                            //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
                            //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
                            if (
                                (double)((pOppActor->_X+pOppSphere->_x) - (_pActor->_X+pSphere->_x)) * ((pOppActor->_X+pOppSphere->_x) - (_pActor->_X+pSphere->_x)) +
                                (double)((pOppActor->_Y+pOppSphere->_y) - (_pActor->_Y+pSphere->_y)) * ((pOppActor->_Y+pOppSphere->_y) - (_pActor->_Y+pSphere->_y)) +
                                (double)((pOppActor->_Z+pOppSphere->_z) - (_pActor->_Z+pSphere->_z)) * ((pOppActor->_Z+pOppSphere->_z) - (_pActor->_Z+pSphere->_z))
                                  <=
                                (double)(pOppSphere->_r + pSphere->_r) * (pOppSphere->_r + pSphere->_r)
                            ) {
                                return true;
                            }

                        } else if (pColliPart->_shape_kind == COLLI_AAB && pOppColliPart->_shape_kind == COLLI_SPHERE) {
                            //��AAB �� ����
                            ColliAAB* pAAB = (ColliAAB*)pColliPart;
                            ColliSphere* pOppSphere = (ColliSphere*)pOppColliPart;
                            int o_scx =  pOppActor->_X+pOppSphere->_cx;
                            int o_scy =  pOppActor->_Y+pOppSphere->_cy;
                            int o_scz =  pOppActor->_Z+pOppSphere->_cz;
                            int bx1 = _pActor->_X+pAAB->_x1;
                            int bx2 = _pActor->_X+pAAB->_x2;
                            int by1 = _pActor->_Y+pAAB->_y1;
                            int by2 = _pActor->_Y+pAAB->_y2;
                            int bz1 = _pActor->_Z+pAAB->_z1;
                            int bz2 = _pActor->_Z+pAAB->_z2;
                            double square_length = 0; //���̒��S��AAB�̍ŒZ�������悵���l
                            if(o_scx < bx1) {
                                square_length += (double)(o_scx - bx1) * (o_scx - bx1);
                            }
                            if(o_scx > bx2) {
                                square_length += (double)(o_scx - bx2) * (o_scx - bx2);
                            }
                            if(o_scy < by1) {
                                square_length += (double)(o_scy - by1) * (o_scy - by1);
                            }
                            if(o_scy > by2) {
                                square_length += (double)(o_scy - by2) * (o_scy - by2);
                            }
                            if(o_scz < bz1) {
                                square_length += (double)(o_scz - bz1) * (o_scz - bz1);
                            }
                            if(o_scz > bz2) {
                                square_length += (double)(o_scz - bz2) * (o_scz - bz2);
                            }
                            //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
                            if (square_length <= (double)pOppSphere->_r * pOppSphere->_r) {
                                return true;
                            }
                        } else if (pColliPart->_shape_kind == COLLI_SPHERE && pOppColliPart->_shape_kind == COLLI_AAB) {
                            //���� �� AAB��
                            ColliSphere* pSphere = (ColliSphere*)pColliPart;
                            ColliAAB* pOppABB = (ColliAAB*)pOppColliPart;
                            int scx =  _pActor->_X+pSphere->_cx;
                            int scy =  _pActor->_Y+pSphere->_cy;
                            int scz =  _pActor->_Z+pSphere->_cz;
                            int o_bx1 = pOppActor->_X+pOppABB->_x1;
                            int o_bx2 = pOppActor->_X+pOppABB->_x2;
                            int o_by1 = pOppActor->_Y+pOppABB->_y1;
                            int o_by2 = pOppActor->_Y+pOppABB->_y2;
                            int o_bz1 = pOppActor->_Z+pOppABB->_z1;
                            int o_bz2 = pOppActor->_Z+pOppABB->_z2;
                            double square_length = 0; //���̒��S��AAB�̍ŒZ�������悵���l

                            if(scx < o_bx1) {
                                square_length += (double)(scx - o_bx1) * (scx - o_bx1);
                            }
                            if(scx > o_bx2) {
                                square_length += (double)(scx - o_bx2) * (scx - o_bx2);
                            }
                            if(scy < o_by1) {
                                square_length += (double)(scy - o_by1) * (scy - o_by1);
                            }
                            if(scy > o_by2) {
                                square_length += (double)(scy - o_by2) * (scy - o_by2);
                            }
                            if(scz < o_bz1) {
                                square_length += (double)(scz - o_bz1) * (scz - o_bz1);
                            }
                            if(scz > o_bz2) {
                                square_length += (double)(scz - o_bz2) * (scz - o_bz2);
                            }
                            //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
                            if (square_length <= (double)pSphere->_r * pSphere->_r) {
                                return true;
                            }
                        }

                    }
                }
            }
        }
    }
    return false;
}



CollisionChecker::~CollisionChecker() {
    TRACE("CollisionChecker::~CollisionChecker() _pActor="<<_pActor->getName());
    DELETE_IMPOSSIBLE_NULL(_pElem);
    DELETE_POSSIBLE_NULL(_pCollisionArea);
    //�����蔻��͂Ȃ���������Ȃ��B���̏ꍇ_pElem�͖��ʂȐ����Ɖ�������邱�ƂɂȂ�B�B
}
