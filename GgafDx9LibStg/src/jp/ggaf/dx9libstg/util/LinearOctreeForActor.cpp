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
        //では八分木を巡る旅へ行ってらっしゃい
        executeHitChk(0); //いってきます
        //はいお帰りなさい。
        _stackParentSpaceActor_GroupA.clear();
        _stackParentSpaceActor_GroupB.clear();
    }
}


void LinearOctreeForActor::executeHitChk(UINT32 prm_index) {
    TRACE5("InSpaceNo="<<prm_index);
    LinearOctreeActorElem* pElem = ((LinearOctreeActorElem*)(_paSpace[prm_index]._pElemFirst));
    if (pElem) {
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
        //現在の空間のグループAとグループB総当り
        executeHitChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackCurrentSpaceActor_GroupB);
        //現在の空間のグループAと親空間所属のグループB総当り
        executeHitChk_RoundRobin(&_stackCurrentSpaceActor_GroupA, &_stackParentSpaceActor_GroupB );
        //親空間所属のグループAと現在の空間のグループB総当り
        executeHitChk_RoundRobin(&_stackParentSpaceActor_GroupA , &_stackCurrentSpaceActor_GroupB);
    }

    UINT32 next_level_index = prm_index*8 + 1; //_papSpace[prm_index] 空間の子空間のモートン順序位置0番の配列要素番号
    TRACE5("next_level_index="<<next_level_index);
    if ( next_level_index > _num_space-1) {
        //要素数オーバー、つまりリーフ
        TRACE5("末端Space");
        _stackCurrentSpaceActor_GroupA.clear();
        _stackCurrentSpaceActor_GroupB.clear();
        return; //親空間へ戻る
    } else {
        //もぐる。が、その前に現空間アクターを親空間アクターのスタックへ追加。
        //もぐった空間から見た場合の親空間アクター累計を作っておいてやる。
        //(現空間スタックも開放)
        int _stackParentSpaceActor_GroupA_p = _stackCurrentSpaceActor_GroupA._p; //スタックポインタ保存
        int _stackParentSpaceActor_GroupB_p = _stackCurrentSpaceActor_GroupB._p;
        GgafActor* pActor;
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupA.pop();
            if (pActor) {
                _stackParentSpaceActor_GroupA.push(pActor);
            } else {
                break;
            }
        }
        while (true) {
            pActor = _stackCurrentSpaceActor_GroupB.pop();
            if (pActor) {
                _stackParentSpaceActor_GroupB.push(pActor);
            } else {
                break;
            }
        }

        //子空間へもぐるが良い
        for(UINT32 i = next_level_index; i < next_level_index+8; i++) {
            if (((_paSpace[i]._kindinfobit & _kind_groupA) > 0) || ((_paSpace[i]._kindinfobit & _kind_groupB) > 0)) {
                executeHitChk(i);
            }
        }

        //お帰りなさい
        //スタックの解放（pushした分、元に戻す）
        _stackParentSpaceActor_GroupA._p = _stackParentSpaceActor_GroupA_p;
        _stackParentSpaceActor_GroupB._p = _stackParentSpaceActor_GroupB_p;

        return; //親空間へ戻る
    }


}

void LinearOctreeForActor::executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {
    //TEXT5("prm_pStackA:"); prm_pStackA->dump(); TEXT5("\n");
    //TEXT5("prm_pStackB:"); prm_pStackB->dump(); TEXT5("\n");
    //どちらか無ければ終了
    UINT32 num_stackA = prm_pStackA->_p;
//    if (num_stackA == 0) {
//        return;
//    }
    UINT32 num_stackB = prm_pStackB->_p;
//    if (num_stackB == 0) {
//        return;
//    }
    GgafActor** papStackActor_A = prm_pStackA->_apActor;
    GgafActor** papStackActor_B = prm_pStackB->_apActor;
    GgafActor* pActor_A;
//    GgafActor* pActor_B;
    for (UINT32 i = 0; i < num_stackA; i++) {
        pActor_A = papStackActor_A[i];
        for (UINT32 j = 0; j < num_stackB; j++) {
//            pActor_B = prm_pStackB->_apActor[j];
            pActor_A->executeHitChk_MeAnd(papStackActor_B[j]);
        }
    }
}


LinearOctreeForActor::~LinearOctreeForActor() {
}



