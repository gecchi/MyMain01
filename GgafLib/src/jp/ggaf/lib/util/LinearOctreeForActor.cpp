#include "jp/ggaf/lib/util/LinearOctreeForActor.h"

#include "jp/ggaf/core/actor/GgafActor.h"
#include "jp/ggaf/core/util/GgafLinearOctreeOctant.h"
#include "jp/ggaf/lib/util/LinearOctreeActorElem.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LinearOctreeForActor::LinearOctreeForActor(int prm_level) : GgafLinearOctree(prm_level) {
    _num_space_minus_one = _num_space-1;
    _kind_groupA = 0;
    _kind_groupB = 0;
}

void LinearOctreeForActor::executeAllHitChk(actorkind prm_groupA, actorkind prm_groupB) {
    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    if ( (_paOctant[0]._kindinfobit & _kind_groupA) && (_paOctant[0]._kindinfobit & _kind_groupB) ) {
        //では八分木を巡る旅へ行ってらっしゃい
        executeHitChk(0); //いってきます
        //はいお帰りなさい。
        _stackParentOctantActor_GroupA.clear();
        _stackParentOctantActor_GroupB.clear();
    }
}

void LinearOctreeForActor::executeHitChk(uint32_t prm_index) {
    GgafLinearOctreeOctant* pOctant_this_level = &(_paOctant[prm_index]);
    LinearOctreeActorElem* pElem = ((LinearOctreeActorElem*)(pOctant_this_level->_pElem_first));
    const uint32_t kind_groupA = _kind_groupA;
    const uint32_t kind_groupB = _kind_groupB;
    if (pElem) {
        GgafLinearOctreeElem* pElem_last = pOctant_this_level->_pElem_last;
        while (true) {
            if (pElem->_kindbit & kind_groupA) {
                _stackCurrentOctantActor_GroupA.push(pElem->_pActor);
            }
            if (pElem->_kindbit & kind_groupB) {
                _stackCurrentOctantActor_GroupB.push(pElem->_pActor);
            }
            if (pElem == pElem_last) {
                break;
            }
            pElem = (LinearOctreeActorElem*)(pElem->_pNext);
        }
        //現在の空間のグループAとグループB総当り
        executeHitChk_RoundRobin(&_stackCurrentOctantActor_GroupA, &_stackCurrentOctantActor_GroupB);
        //現在の空間のグループAと親空間所属のグループB総当り
        executeHitChk_RoundRobin(&_stackCurrentOctantActor_GroupA, &_stackParentOctantActor_GroupB );
        //親空間所属のグループAと現在の空間のグループB総当り
        executeHitChk_RoundRobin(&_stackParentOctantActor_GroupA , &_stackCurrentOctantActor_GroupB);
    }

    const uint32_t next_level_index = prm_index*8 + 1; //_papOctant[prm_index] 空間の子空間のモートン順序位置0番の配列要素番号
    if ( next_level_index > _num_space_minus_one) {
        //要素数オーバー、つまりリーフ
        _stackCurrentOctantActor_GroupA.clear();
        _stackCurrentOctantActor_GroupB.clear();
        return; //親空間へ戻る
    } else {

//        bool isExist_ParentGroupA = _stackParentOctantActor_GroupA.isExist();
//        bool isExist_ParentGroupB = _stackParentOctantActor_GroupB.isExist();

        //もぐる。が、その前に現空間アクターを親空間アクターのスタックへ追加。
        //もぐった空間から見た場合の親空間アクター累計を作っておいてやる。
        //(現空間スタックも開放)
        GgafCore::GgafActor** stackParentOctantActor_GroupA_papCur = _stackParentOctantActor_GroupA._papCur; //スタックポインタ保存
        GgafCore::GgafActor** stackParentOctantActor_GroupB_papCur = _stackParentOctantActor_GroupB._papCur; //スタックポインタ保存
        _stackParentOctantActor_GroupA.pop_push(&_stackCurrentOctantActor_GroupA); //_stackCurrentOctantActor_GroupAも、クリアされる。
        _stackParentOctantActor_GroupB.pop_push(&_stackCurrentOctantActor_GroupB); //_stackCurrentOctantActor_GroupBも、クリアされる。
//        //子空間へもぐるが良い
        GgafLinearOctreeOctant* pOctant = &(_paOctant[next_level_index]);
        const uint32_t next_level_index_end = next_level_index+8;
        for(uint32_t i = next_level_index; i < next_level_index_end; i++) {
            if ((pOctant->_kindinfobit & _kind_groupA) || (pOctant->_kindinfobit & _kind_groupB) ) {
                executeHitChk(i);
            }
            ++pOctant;
        }
// ↑を↓に見なおした。
//        GgafLinearOctreeOctant* pOctant_next_level = &(_paOctant[next_level_index]);
//        uint32_t octant_kindinfobit_next_level = pOctant_next_level->_kindinfobit;
        //次のレベルの空間に種別AとBが登録されていれば潜る。
        //又は、次のレベルの空間に種別Aがあり、かつ親ストックに種別Bがあれば潜る。
        //又は、次のレベルの空間に種別Bがあり、かつ親ストックに種別Aがあれば潜る。
        //それ以外は潜らない
        //if (( (octant_kindinfobit_next_level & kind_groupA) && (octant_kindinfobit_next_level & kind_groupB) ) ||
        //    ( (octant_kindinfobit_next_level & kind_groupA) && (isExist_ParentGroupB)                        ) ||
        //    (                        (isExist_ParentGroupA) && (octant_kindinfobit_next_level & kind_groupB) )
        //) {
        //    executeHitChk(next_level_index);
        //}
        //↑を↓に書き直した
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+1);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+1);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+2);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+2);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+3);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+3);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+4);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+4);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+5);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+5);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+6);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+6);
//            }
//        }
//
//        octant_kindinfobit_next_level = (++pOctant_next_level)->_kindinfobit;
//        if (octant_kindinfobit_next_level & kind_groupA) {
//            if (isExist_ParentGroupB || (octant_kindinfobit_next_level & kind_groupB)) {
//                executeHitChk(next_level_index+7);
//            }
//        } else if (octant_kindinfobit_next_level & kind_groupB) {
//            if (isExist_ParentGroupA) {
//                executeHitChk(next_level_index+7);
//            }
//        }

        //お帰りなさい
        //スタックの解放（pushした分、元に戻す）
        _stackParentOctantActor_GroupA._papCur = stackParentOctantActor_GroupA_papCur;
        _stackParentOctantActor_GroupB._papCur = stackParentOctantActor_GroupB_papCur;
        return; //親空間へ戻る
    }
}

void LinearOctreeForActor::executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB) {
    //どちらか無ければ終了
    GgafActor** papStackActor_A_Cur = prm_pStackA->_papCur;
    GgafActor** papStackActor_B_Cur = prm_pStackB->_papCur;
    GgafActor** papStackActor_A = prm_pStackA->_papFirst;
    while (papStackActor_A != papStackActor_A_Cur) {
        GgafActor** papStackActor_B = prm_pStackB->_papFirst;
        while (papStackActor_B != papStackActor_B_Cur) {
            (*papStackActor_A)->executeHitChk_MeAnd(*papStackActor_B);
            ++papStackActor_B;
        }
        ++papStackActor_A;
    }

}

LinearOctreeForActor::~LinearOctreeForActor() {
}

