#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


LinearOctreeForActor::LinearOctreeForActor(int prm_level) : GgafLinearOctree(prm_level) {
}


void LinearOctreeForActor::executeAllHitChk(actorkind prm_groupA, actorkind prm_groupB) {
    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    TRACE5("_kind_groupA="<<_kind_groupA);
    TRACE5("_kind_groupB="<<_kind_groupB);
    if (((_paSpace[0]._kindinfobit & _kind_groupA) > 0) && ((_paSpace[0]._kindinfobit & _kind_groupB) > 0)) {
        //�ł͔����؂����闷�֍s���Ă�����Ⴂ
        executeHitChk(0); //���[�g��Ԃ̃`�F�b�N
        //���A��Ȃ����B
        _stackParentSpaceActor_GroupA.clear();
        _stackParentSpaceActor_GroupB.clear();
    }
}


void LinearOctreeForActor::executeHitChk(UINT32 prm_index) {
    TRACE5("InSpaceNo="<<prm_index);
    LinearOctreeActorElem* pElem = ((LinearOctreeActorElem*)(_paSpace[prm_index]._pElemFirst));
    if (pElem != NULL) {
        GgafActor* pActor_ElemValue = pElem->_pActor;
        TRACE5("pActor_ElemValue="<<pActor_ElemValue->getName());
        while(true) {
            if ((pElem->_kindbit & _kind_groupA) > 0) {
                _stackCurrentSpaceActor_GroupA.push(pActor_ElemValue);
            }
            if ((pElem->_kindbit & _kind_groupB) > 0) {
                _stackCurrentSpaceActor_GroupB.push(pActor_ElemValue);
            }
            if (pElem == _paSpace[prm_index]._pElemLast) {
                break;
            }
            pElem = (LinearOctreeActorElem*)(pElem -> _pNext);
            pActor_ElemValue = pElem->_pActor;
        }
        //���݂̋�Ԃ̃O���[�vA�ƃO���[�vB������
        executeHitChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackCurrentSpaceActor_GroupB);

        //���݂̋�Ԃ̃O���[�vA�Ɛe��ԏ����̃O���[�vB������
        executeHitChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackParentSpaceActor_GroupB );

        //�e��ԏ����̃O���[�vA�ƌ��݂̋�Ԃ̃O���[�vB������
        executeHitChk_RoundRobin(&_stackParentSpaceActor_GroupA , &_stackCurrentSpaceActor_GroupB);
    }

    UINT32 next_level_index = prm_index*8 + 1; //_papSpace[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
    TRACE5("next_level_index="<<next_level_index);
    if ( next_level_index > _num_space-1) {
        //�v�f���I�[�o�[�A�܂胊�[�t
        TRACE5("���[Space");
        _stackCurrentSpaceActor_GroupA.clear();
        _stackCurrentSpaceActor_GroupB.clear();
        return; //�e��Ԃ֖߂�
    } else {
        //������B���̑O�ɁA�e��ԃA�N�^�[�̃X�^�b�N�֒ǉ�(����ԃX�^�b�N���J��)
        int add_num_GroupA, add_num_GroupB;
        add_num_GroupA = add_num_GroupB = 0;
        GgafActor* pActor;
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupA.pop();
            if (pActor == NULL) {
                break;
            } else {
                _stackParentSpaceActor_GroupA.push(pActor);
                add_num_GroupA++;
            }
        }
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupB.pop();
            if (pActor == NULL) {
                break;
            } else {
                _stackParentSpaceActor_GroupB.push(pActor);
                add_num_GroupB++;
            }
        }

        //�q��Ԃւ����邪�ǂ�
        for(UINT32 i = next_level_index; i < next_level_index+8; i++) {
            if (((_paSpace[i]._kindinfobit & _kind_groupA) > 0) || ((_paSpace[i]._kindinfobit & _kind_groupB) > 0)) {
                executeHitChk(i);
            }
        }

        //���A��Ȃ���
        for (int i = 0; i < add_num_GroupA; i ++) {
            _stackParentSpaceActor_GroupA.pop();
        }
        for (int i = 0; i < add_num_GroupB; i ++) {
            _stackParentSpaceActor_GroupB.pop();
        }
        return; //�e��Ԃ֖߂�
    }


}

void LinearOctreeForActor::executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {
    //TEXT5("prm_pStackA:"); prm_pStackA->dump(); TEXT5("\n");
    //TEXT5("prm_pStackB:"); prm_pStackB->dump(); TEXT5("\n");
    //����������ΏI��
    if (prm_pStackA->_p == 0 || prm_pStackB->_p == 0) {
        return;
    }
    GgafActor* pActor_A;
    GgafActor* pActor_B;
    for (UINT32 i = 0; i < prm_pStackA->_p; i++) {
        pActor_A = prm_pStackA->_apActor[i];
        for (UINT32 j = 0; j < prm_pStackB->_p; j++) {
            pActor_B = prm_pStackB->_apActor[j];
#ifdef MY_DEBUG
//        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//            _TRACE_("HitChk("<<pActor_A->getName()<<" x "<<pActor_B->getName()<<")");
//        }
#endif

            pActor_A->executeHitChk_MeAnd(pActor_B);
        }
    }
}


LinearOctreeForActor::~LinearOctreeForActor() {
}



