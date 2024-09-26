#include "jp/ggaf/dx/util/CollisionChecker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

using namespace GgafDx;

CollisionChecker::CollisionChecker(GeometricActor* prm_pColliActor) : GgafCore::Checker(prm_pColliActor),
_pColliActor(prm_pColliActor) {
    _pCollisionArea = nullptr;
}

void CollisionChecker::addCollisionArea(int prm_colli_part_num) {
    _kind = _pActor->getDefaultKind(); //TODO:�����ł����̂�

    CollisionArea* pNewCollisionArea = NEW CollisionArea(prm_colli_part_num);
    _pCollisionArea = pNewCollisionArea;
    _pCollisionArea->_need_update_aabb = true;
    _pColliActor->setHitAble(true);
    //�X�g�b�N
    _vecCollisionArea.push_back(pNewCollisionArea);
}

void CollisionChecker::changeCollisionArea(int prm_index) {
#ifdef MY_DEBUG
    if (_vecCollisionArea.size() < prm_index+1) {
        throwCriticalException("�v�f�����s���Bprm_index="<<prm_index);
    }
#endif
    _pCollisionArea = _vecCollisionArea.at(prm_index);
}

bool CollisionChecker::processHitChkLogic(GgafCore::Checker* prm_pOtherChecker) {
    if (_pActor->_can_hit_flg && prm_pOtherChecker->_pActor->_can_hit_flg) {
        //&& prm_pOtherActor->instanceOf(Obj_GgafDx_GeometricActor)) { �����蔻�肪����̂�GeometricActor�ȏ�Ɣ��f
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg �̃`�F�b�N�͔����ؓo�^�O�ɂ��`�F�b�N���Ă邪
        //�����ł�������x�`�F�b�N����ق������ǂ��B
        //�Ȃ��Ȃ�΁A���ʂȃq�b�g�`�F�b�N���s��Ȃ����߁AonHit(GgafCore::Actor*) �������� setHitAble(false) ���s���A
        //�Q�d�q�b�g�`�F�b�N�h�~���s���Ă��邩������Ȃ�����B
        return isHit((CollisionChecker*)prm_pOtherChecker);
    } else {
        return false;
    }
}

//void CollisionChecker::enable(int prm_index) {
//    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
//    if (pPart->_is_valid_flg) {
//        //���X enable
//    } else {
//        pPart->_is_valid_flg = true;
//        _pCollisionArea->_need_update_aabb = true;
//    }
//}
//
//void CollisionChecker::disable(int prm_index) {
//    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
//    if (pPart->_is_valid_flg) {
//        pPart->_is_valid_flg = false;
//        _pCollisionArea->_need_update_aabb = true;
//    } else {
//         //���X disable
//    }
//}
//
//bool CollisionChecker::isEnable(int prm_index) {
//    return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
//}

CollisionChecker::~CollisionChecker() {
    for (int i = 0; i < _vecCollisionArea.size(); i++) {
        CollisionArea* pCollisionArea = _vecCollisionArea.at(i);
        GGAF_DELETE(pCollisionArea);
    }
}
