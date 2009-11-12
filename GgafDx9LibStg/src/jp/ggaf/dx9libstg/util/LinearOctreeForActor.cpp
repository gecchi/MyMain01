#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


LinearOctreeForActor::LinearOctreeForActor(int prm_level) : GgafLinearOctree(prm_level) {
}


void LinearOctreeForActor::executeAllBumpChk(actorkind prm_groupA, actorkind prm_groupB) {
//    for (int i = 0; i < prm_pair_num; i++) {
//        //actorkind group_A = prm_actorkindmask_pair[i][0];
//       // actorkind group_B = prm_actorkindmask_pair[i][1];
//    }

    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    executeBumpChk(0);
}

void LinearOctreeForActor::executeBumpChk(int prm_index) {
    Space* pSpace = &(_paSpace[prm_index]);

    Elem* pElem = (ElemEx*)(pSpace->_pElemFirst);
    while(true) {
        if (pElem->_kindbit & _kind_groupA > 0) {
            _listGroupA.push(((ElemEx*)pElem)->_pActor);
        }
        if (pElem->_kindbit & _kind_groupB > 0) {
            _listGroupB.push(((ElemEx*)pElem)->_pActor);
        }

        pElem = pElem -> _pNext;
        if (pElem == pSpace->_pElemLast) {
            break;
        }
    }

    //�c���[���Ǘ����Ă�A�e��Ԃ̃��X�g�ƏՓ˔���
    executeBumpChk_RoundRobin(&_listGroupA    , &_listTreeGroupB, false);
    executeBumpChk_RoundRobin(&_listTreeGroupA, &_listGroupB    , false);

    //�����ԓ���_listGroupA x _listGroupB
    executeBumpChk_RoundRobin(&_listGroupA, &_listGroupB, true);


    int next_level_index = prm_index*8 + 1; //_papSpace[prm_index] ��Ԃ̎q��Ԃ̃��[�g�������ʒu0�Ԃ̔z��v�f�ԍ�
    if ( next_level_index > _num_space) {
        //���[�t
        return;
    } else {
        //������
        for(int i = next_level_index; i < next_level_index+8; i++) {
            if (_paSpace[i]._kindinfobit & (_kind_groupA | _kind_groupB) > 0) {
                executeBumpChk(i);
            }
        }

        return;
    }

}
void LinearOctreeForActor::executeBumpChk_RoundRobin(CollisionList* prm_pListA, CollisionList* prm_pListB, bool addTreeList) {
    GgafActor* pActor_A;
    GgafActor* pActor_B;
    while(true) {
        pActor_A = prm_pListA->pop();
        if (pActor_A == NULL) {
            break; //�I��
        } else {
            if (addTreeList) {
                _listTreeGroupA.push(pActor_A);
            }
        }
        while(true) {
            pActor_B = prm_pListB->pop();
            if (pActor_B == NULL) {
                break;
            } else {
                if (addTreeList) {
                    _listTreeGroupB.push(pActor_B);
                }
            }
            pActor_A->executeBumpChk_MeAnd(pActor_B);
        }
    }
}


LinearOctreeForActor::~LinearOctreeForActor() {
}



