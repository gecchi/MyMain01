#include "jp/ggaf/core/util/GgafLinearOctreeForActor.h"

#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearOctreeOctant.h"
#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"
#include "jp/ggaf/core/actor/GgafActor.h"

using namespace GgafCore;

GgafLinearOctreeForActor::GgafLinearOctreeForActor(GgafLinearOctree* prm_pTargetLinearOctree, void (GgafActor::*prm_pFunc)(GgafActor*)) : GgafObject() {
    _pTargetLinearOctree = prm_pTargetLinearOctree;
    _paTargetLinearOctant = _pTargetLinearOctree->_paLinearOctant;
    _num_space_minus_one = _pTargetLinearOctree->_num_space-1;
    _pFunc = prm_pFunc;
    _kind_groupA = 0;
    _kind_groupB = 0;
}

void GgafLinearOctreeForActor::executeAll(actorkind prm_groupA, actorkind prm_groupB) {
    _kind_groupA = prm_groupA;
    _kind_groupB = prm_groupB;
    if ( (_paTargetLinearOctant[0]._kindinfobit & prm_groupA) && (_paTargetLinearOctant[0]._kindinfobit & prm_groupB) ) {
        //では八分木を巡る旅へ行ってらっしゃい
        execute(0); //いってきます
        //はいお帰りなさい。
        _stackGroupA.clear();
        _stackGroupB.clear();
    }
}

void GgafLinearOctreeForActor::execute(uint32_t prm_index) {
    GgafLinearOctreeOctant* pOctant_this_level = &(_paTargetLinearOctant[prm_index]);
    GgafLinearOctreeElem* pElem = pOctant_this_level->_pElem_first;
    const uint32_t kind_groupA = _kind_groupA;
    const uint32_t kind_groupB = _kind_groupB;
    if (pElem) {
        GgafLinearOctreeElem* pElem_last = pOctant_this_level->_pElem_last;
        while (true) {
            if (pElem->_kindbit & kind_groupA) {
                _stackGroupA_Current.push((GgafActor*)(pElem->_pObject));
            }
            if (pElem->_kindbit & kind_groupB) {
                _stackGroupB_Current.push((GgafActor*)(pElem->_pObject));
            }
            if (pElem == pElem_last) {
                break;
            }
            pElem = pElem->_pNext;
        }
        //現在の空間のグループAとグループB総当り
        executeRoundRobin(&_stackGroupA_Current, &_stackGroupB_Current);
        //現在の空間のグループAと親空間所属のグループB総当り
        executeRoundRobin(&_stackGroupA_Current, &_stackGroupB );
        //親空間所属のグループAと現在の空間のグループB総当り
        executeRoundRobin(&_stackGroupA , &_stackGroupB_Current);
    }

    const uint32_t lower_level_index = prm_index*8 + 1; //_papOctant[prm_index] 空間の子空間のモートン順序位置0番の配列要素番号
    if ( lower_level_index > _num_space_minus_one) {
        //要素数オーバー、つまりリーフ
        _stackGroupA_Current.clear();
        _stackGroupB_Current.clear();
        return; //親空間へ戻る
    } else {

        //もぐる。が、その前に現空間アクターを親空間アクターのスタックへ追加。
        //もぐった空間から見た場合の親空間アクター累計を作っておいてやる。
        //(同時に現空間スタックも開放)
        GgafActor** temp_stackGroupA = _stackGroupA._papCur; //スタックポインタ保存(潜った後のリセットに使用)
        GgafActor** temp_stackGroupB = _stackGroupB._papCur; //スタックポインタ保存(潜った後のリセットに使用)
        _stackGroupA.popush(&_stackGroupA_Current); //Current を Parent に追加。同時にCurrentはクリアされる。
        _stackGroupB.popush(&_stackGroupB_Current); //Current を Parent に追加。同時にCurrentはクリアされる。
        bool isExistGroupA = _stackGroupA.isExist();
        bool isExistGroupB = _stackGroupB.isExist();

        //ヒットチェックを行いに、子空間(８個)へ潜りに行こう～。
        //次のレベルの空間に種別AとBが登録されていれば潜る。
        //又は、次のレベルの空間に種別Aがあり、かつストックに種別Bがあれば潜る。
        //又は、次のレベルの空間に種別Bがあり、かつストックに種別Aがあれば潜る。
        //それ以外は潜らない
        GgafLinearOctreeOctant* pOctant_lower_level = &(_paTargetLinearOctant[lower_level_index]);
        uint32_t kindinfobit_lower_level = pOctant_lower_level->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+1);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+1);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+2);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+2);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+3);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+3);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+4);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+4);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+5);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+5);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+6);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+6);
            }
        }

        kindinfobit_lower_level = (++pOctant_lower_level)->_kindinfobit;
        if (kindinfobit_lower_level & kind_groupA) {
            if (isExistGroupB || (kindinfobit_lower_level & kind_groupB)) {
                execute(lower_level_index+7);
            }
        } else if (kindinfobit_lower_level & kind_groupB) {
            if (isExistGroupA) {
                execute(lower_level_index+7);
            }
        }

//        //お帰りなさい
//        //スタックの解放（pushした分、元に戻す）
        _stackGroupA._papCur = temp_stackGroupA;
        _stackGroupB._papCur = temp_stackGroupB;
        return; //親空間へ戻る
    }
}

void GgafLinearOctreeForActor::executeRoundRobin(ActorStack* prm_pStackA, ActorStack* prm_pStackB) {
    //GgafLinearOctreeForActorでは、要素の指す(GgafObject*)インスタンスは GgafActorが前提
    if (prm_pStackA->isExist() && prm_pStackB->isExist()) {
        void (GgafActor::*pFunc)(GgafActor*) = _pFunc;
        GgafActor** papStackActor_A_Cur = prm_pStackA->_papCur;
        GgafActor** papStackActor_B_Cur = prm_pStackB->_papCur;
        GgafActor** papStackActor_A = prm_pStackA->_papFirst;
        while (papStackActor_A != papStackActor_A_Cur) {
            GgafActor** papStackActor_B = prm_pStackB->_papFirst;
            while (papStackActor_B != papStackActor_B_Cur) {
//                ((GgafActor*)(*papStackActor_A))->executeHitChk_MeAnd((GgafActor*)(*papStackActor_B));
                ((*papStackActor_A)->*pFunc)(*papStackActor_B);
                ++papStackActor_B;
            }
            ++papStackActor_A;
        }
    }
}

GgafLinearOctreeForActor::~GgafLinearOctreeForActor() {
}

