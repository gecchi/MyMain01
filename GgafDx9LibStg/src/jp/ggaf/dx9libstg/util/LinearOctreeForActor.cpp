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
    TRACE5("_kind_groupA="<<_kind_groupA);
    TRACE5("_kind_groupB="<<_kind_groupB);
    if (((_paSpace[0]._kindinfobit & _kind_groupA) > 0) && ((_paSpace[0]._kindinfobit & _kind_groupB) > 0)) {
        executeBumpChk(0);//行ってらっしゃい
        _stackParentSpaceActor_GroupA.clear();
        _stackParentSpaceActor_GroupB.clear();
        //お帰りなさい。
    }
}


void LinearOctreeForActor::executeBumpChk(DWORD prm_index) {
	TRACE5("InSpaceNo="<<prm_index);



    LOFA_Elem* pElem = ((LOFA_Elem*)(_paSpace[prm_index]._pElemFirst));
    if (pElem != NULL) {
		GgafActor* pActor_ElemValue = pElem->_pActor;
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
            pElem = (LOFA_Elem*)(pElem -> _pNext);
            pActor_ElemValue = pElem->_pActor;
        }
        //現在の空間のグループAとグループB総当り
        TRACE5("1executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackCurrentSpaceActor_GroupB);");
        executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackCurrentSpaceActor_GroupB);

        //現在の空間のグループAと親空間所属のグループB総当り
        TRACE5("2executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackParentSpaceActor_GroupB );");
        executeBumpChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackParentSpaceActor_GroupB );

        //親空間所属のグループAと現在の空間のグループB総当り
        TRACE5("3executeBumpChk_RoundRobin(&_stackParentSpaceActor_GroupA , &_stackCurrentSpaceActor_GroupB);");
        executeBumpChk_RoundRobin(&_stackParentSpaceActor_GroupA , &_stackCurrentSpaceActor_GroupB);
    }


    DWORD next_level_index = prm_index*8 + 1; //_papSpace[prm_index] 空間の子空間のモートン順序位置0番の配列要素番号
    TRACE5("next_level_index="<<next_level_index);
    if ( next_level_index > _num_space-1) {
        //要素数オーバー、つまりリーフ
        TRACE5("末端Space");
        _stackCurrentSpaceActor_GroupA.clear();
        _stackCurrentSpaceActor_GroupB.clear();
        return; //親空間へ戻る
    } else {
        //もぐる。その前に、親空間アクターのスタックへ追加(現空間スタックも開放)
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

        //子空間へもぐるが良い
        for(DWORD i = next_level_index; i < next_level_index+8; i++) {
            if (((_paSpace[i]._kindinfobit & _kind_groupA) > 0) || ((_paSpace[i]._kindinfobit & _kind_groupB) > 0)) {
                executeBumpChk(i);
            }
        }

        //お帰りなさい
        for (DWORD i = 0; i < add_num_GroupA; i ++) {
            _stackParentSpaceActor_GroupA.pop();
        }
        for (DWORD i = 0; i < add_num_GroupB; i ++) {
            _stackParentSpaceActor_GroupB.pop();
        }
        return; //親空間へ戻る
    }


}

void LinearOctreeForActor::executeBumpChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {
    //TEXT5("prm_pStackA:"); prm_pStackA->dump(); TEXT5("\n");
    //TEXT5("prm_pStackB:"); prm_pStackB->dump(); TEXT5("\n");
    //両方無ければ終了
    if (prm_pStackA->_p == 0 || prm_pStackB->_p == 0) {
        return;
    }

    GgafActor* pActor_A;
    GgafActor* pActor_B;
    for (int i = 0; i < prm_pStackA->_p; i++) {
        pActor_A = prm_pStackA->_apActor[i];
        for (int j = 0; j < prm_pStackB->_p; j++) {
            pActor_B = prm_pStackB->_apActor[j];
            TRACE5("BumpChk("<<pActor_A->getName()<<" x "<<pActor_B->getName()<<")");
            pActor_A->executeBumpChk_MeAnd(pActor_B);
        }
    }
}


LinearOctreeForActor::~LinearOctreeForActor() {
}



