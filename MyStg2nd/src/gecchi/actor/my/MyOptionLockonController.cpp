#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

int MyOptionLockonController::_max_lockon_num = 9;

MyOptionLockonController::MyOptionLockonController(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "MyOptionLockonController";
    _now_lockon_num = 0;
    _pRingTarget = NEW GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor>();
    EffectLockon001_Main* _pMainLockonEffect = NEW EffectLockon001_Main("MAIN");
    _pMainLockonEffect->inactivateImmediately();
    addSubLast(_pMainLockonEffect);
    for (int i = 1; i < _max_lockon_num; i++) {
        stringstream name;
        name <<  "SUB["<<i<<"]";
        EffectLockon001_Sub* pSubLockon = NEW EffectLockon001_Sub(name.str().c_str());
        pSubLockon->inactivateImmediately();
        addSubLast(pSubLockon);
    }

    setProgress(MyOptionLockonController_PROG_NOTHING);
}

void MyOptionLockonController::initialize() {
}


void MyOptionLockonController::processBehavior() {
    //ロックオンターゲット生存確認
    GgafDx9GeometricActor* pMainLockonTarget = _pRingTarget->getCurrent();
    GgafDx9GeometricActor* pTarget = _pRingTarget->getCurrent(); //ターゲットカーソル
    GgafMainActor* pLockonEffect_Active = getSubFirst();         //ロックオンエフェクトカーソル
    int n = _pRingTarget->length();
    for (int i = 0; i < n; i++) {
//_TRACE_("<<<"<<i<<">>>");
        if (pTarget->isActive() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
//            _TRACE_("---------------------------------");
//            _TRACE_("エフェクトアクターのターゲット更新  BEFORE");
//            dumpTarget(_pRingTarget->getCurrent());
//            dump();

            //OK
            //エフェクトアクターのターゲット更新                    //エフェクトをズルっとします
            ((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
            pLockonEffect_Active = pLockonEffect_Active->getNext();//エフェクトアクター次へ
            pTarget = _pRingTarget->next(); //次へ

//            _TRACE_("エフェクトアクターのターゲット更新 AFTER");
//            dumpTarget(_pRingTarget->getCurrent());
//            dump();
        } else {

            //切れる場合
//            _TRACE_("---------------------------------");
//            _TRACE_("切れる BEFORE");
//            dumpTarget();
//            dump();
            if (pTarget == pMainLockonTarget) {
                //メインロックオン時処理
                if (_pRingTarget->length() == 1) {
                    _TRACE_("---------------------------------");
                    _TRACE_("最後の一つでメインロックオン切れる BEFORE");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();


                    //最後の一つでメインロックオン
                    _pRingTarget->remove(); //抜き出し
                    //最後の一つ
                    ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンリリース
                    pTarget = NULL;

                    _TRACE_("最後の一つでメインロックオン切れる AFTER");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();

                    break;
//                    _pMainTarget = NULL;
                } else {
                    _TRACE_("---------------------------------");
                    _TRACE_("メインロックオン切れる BEFORE");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();



                    _pRingTarget->remove(); //抜き出し
                    pTarget = _pRingTarget->getCurrent(); //Target次へ
                    pMainLockonTarget = pTarget;
                    //アクティブを次へ処理は不要、remove()したので自動的に次になっている。
//                    _pMainTarget = _pRingTarget->getCurrent();

                    //メインロックオンエフェクトを直近ロックオンへ戻す は不要、
                    //((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
                    //そのため
                    //メインロックオンエフェクトの次のエフェクトを解放
                    ((EffectLockon001*)pLockonEffect_Active->getNext())->releaseLockon();
                    pLockonEffect_Active->getNext()->moveLastImmediately(); //末尾へ

                    //pLockonEffect_Active->getNext()->releaseLockon();//inactivate(); //解放
                    //メインロックオンエフェクトアクターのターゲット更新、ズルっと戻ります
                    //((EffectLockon001*)pLockonEffect_Active)->_pTarget = _pRingTarget->getCurrent();

                    //pLockonEffect_Active = pLockonEffect_Active->getNext();//次へは
                    //次へはしなくて良い
                    //理由は次のようになるから、次は         Metis_85  であるため
//  5601092 <DEBUG> メインロックオン切れる BEFORE
//  ⇔！Metis_36[0]⇔Metis_85[1]⇔ ... avtive=Metis_36
//  5601095 <DEBUG>                                 MyOptionLockonController(08A06F18)[Lockon001]@4628/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),1(1),0000
//  5601096 <DEBUG>                                 ｜EffectLockon001_Main(08A07298)[MAIN] Target=Metis_36 @278/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(2),0000
//  5601096 <DEBUG>                                 ｜EffectLockon001_Sub(08A0C360)[SUB[8]] Target=Metis_85 @214/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(2),0000
//  5601097 <DEBUG>                                 ｜EffectLockon001_Sub(08A07D40)[SUB[1]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601097 <DEBUG>                                 ｜EffectLockon001_Sub(08A08760)[SUB[2]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601098 <DEBUG>                                 ｜EffectLockon001_Sub(08A09160)[SUB[3]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601098 <DEBUG>                                 ｜EffectLockon001_Sub(08A09B60)[SUB[4]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601099 <DEBUG>                                 ｜EffectLockon001_Sub(08A0A560)[SUB[5]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601099 <DEBUG>                                 ｜EffectLockon001_Sub(08A0AF60)[SUB[6]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601100 <DEBUG>                                 ｜EffectLockon001_Sub(08A0B960)[SUB[7]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601100 <DEBUG>                                 └─
//  5601101 <DEBUG> メインロックオン切れる AFTER
//  ⇔！Metis_85[0]⇔ ... avtive=Metis_85
//  5601103 <DEBUG>                                 MyOptionLockonController(08A06F18)[Lockon001]@4628/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),1(1),0000
//  5601103 <DEBUG>                                 ｜EffectLockon001_Main(08A07298)[MAIN] Target=Metis_85 @278/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(2),0000
//  5601104 <DEBUG>                                 ｜EffectLockon001_Sub(08A07D40)[SUB[1]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601104 <DEBUG>                                 ｜EffectLockon001_Sub(08A08760)[SUB[2]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601105 <DEBUG>                                 ｜EffectLockon001_Sub(08A09160)[SUB[3]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601105 <DEBUG>                                 ｜EffectLockon001_Sub(08A09B60)[SUB[4]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601105 <DEBUG>                                 ｜EffectLockon001_Sub(08A0A560)[SUB[5]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601106 <DEBUG>                                 ｜EffectLockon001_Sub(08A0AF60)[SUB[6]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601106 <DEBUG>                                 ｜EffectLockon001_Sub(08A0B960)[SUB[7]] Target=NULL @4628/4628/4628,1,10,0(0)0,0(0)0,0(4294967295),-3(-3),0000
//  5601107 <DEBUG>                                 ｜EffectLockon001_Sub(08A0C360)[SUB[8]] Target=NULL @214/4628/4628,1,11,0(0)0,0(0)0,0(4294967295),2(3),0000
//  5601107 <DEBUG>                                 └─


                    _TRACE_("メインロックオン切れる AFTER");
                    dumpTarget(_pRingTarget->getCurrent());
                    dump();
                }
            } else {

                _TRACE_("---------------------------------");
                _TRACE_("サブロックオン切れる BEFORE");
                dumpTarget(_pRingTarget->getCurrent());
                dump();

                //サブロックオン時処理

                _pRingTarget->remove(); //ターゲット抜き出し
                pTarget = _pRingTarget->getCurrent(); //Target次へ
                //アクティブを次へ処理は不要、remove()したので自動的に次になっている。

                ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンリリース
                pLockonEffect_Active = pLockonEffect_Active->getNext();//先に次へ
                pLockonEffect_Active->getPrev()->moveLastImmediately(); //今回releaseLockon()を末尾へ

                //pLockonEffect_Active->_pTarget は更新しなくても変化してないので不要。という設計。

                _TRACE_("切れる AFTER");
                dumpTarget(_pRingTarget->getCurrent());
                dump();

            }
//            _TRACE_("切れる AFTER");
//            dumpTarget();
//            dump();

        }
    }
//    _pMainLockOnTarget = _pRingTarget->getCurrent();
    //_TRACE_("_pRingTarget->getCurrent()="<<(_pRingTarget->getCurrent()==NULL?"NULL":_pRingTarget->getCurrent()->getName()));
}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockon(GgafDx9GeometricActor* prm_pTarget) {
    // 追加の場合エフェクトアクターは操作不要

    if (_pRingTarget->indexOf(prm_pTarget) == -1) { //ロックオン済みに無ければ

        if (_pRingTarget->length() >= _max_lockon_num) {
            _TRACE_("---------------------------------");
            _TRACE_("満帆で ズレる lockon("<<prm_pTarget->getName()<<") BEFORE");
            dumpTarget(_pRingTarget->getCurrent());
            dump();
            // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
            //
            // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
            // ⇔t6⇔t5⇔t4⇔t3⇔t2⇔   ズルっ
            // ⇔t7⇔t6⇔t5⇔t4⇔t3⇔   ズルっ
            // ⇔t8⇔t7⇔t6⇔t5⇔t4⇔   ズルっ
            // ⇔t9⇔t8⇔t7⇔t6⇔t5⇔   ズルっとします
            //ターゲットローテート
            _pRingTarget->prev();
            _pRingTarget->set(prm_pTarget);
            //_pMainTarget = prm_pTarget;

            //ロックオンエフェクトローテート
            //操作不要


            //ロックオンエフェクト ロックオン
            //フルロックオン状態であるため必要なし
            _TRACE_("満帆で ズレる lockon("<<prm_pTarget->getName()<<") AFTER");
            dumpTarget(_pRingTarget->getCurrent());
            dump();
        } else {
            _TRACE_("---------------------------------");
            _TRACE_("満帆では無い lockon("<<prm_pTarget->getName()<<") BEFORE");
            dumpTarget(_pRingTarget->getCurrent());
            dump();
            // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
            //
            // ⇔t1⇔
            // エフェクトアクター変化無し
            //
            // ⇔t2⇔t1⇔
            // ⇔Ｍ⇔S3⇔S0⇔S1⇔S2⇔
            //
            // ⇔t3⇔t2⇔t1⇔
            // ⇔Ｍ⇔S2⇔S3⇔S0⇔S1⇔
            //
            // ⇔t4⇔t3⇔t2⇔t1⇔
            // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔
            //
            // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
            // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔

            //ターゲットローテート
            _pRingTarget->addPrev(prm_pTarget, false);
            _pRingTarget->prev();
            //_pMainTarget = prm_pTarget;

            //ロックオンエフェクト
            if (_pRingTarget->length() == 1) {
                //最初の Mianロックオン追加時
                GgafMainActor* pLockonEffect = getSubFirst();
                pLockonEffect->activate();
                ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);


                _TRACE_("満帆では無い 最初の Mianロックオン追加時 lockon("<<prm_pTarget->getName()<<") AFTER");

            } else if (_pRingTarget->length() > 1) {
                //Subロックオン追加時
                if (_max_lockon_num >= 3) {
                    //特殊なローテート
                    //を切り出す
                    GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //Last
                    GgafMainActor* pLockonEffect_Next = pLockonEffect->getNext(); //Mainロックオンとなる
                    GgafMainActor* pLockonEffect_Prev = pLockonEffect->getPrev();
                    pLockonEffect_Prev->_pNext = pLockonEffect_Next;
                    pLockonEffect_Next->_pPrev = pLockonEffect_Prev;
                    pLockonEffect_Prev->_is_last_flg = true;
                    pLockonEffect->_is_last_flg = false;
                    //First->Next の間に入れる
                    GgafMainActor* pMainLockonEffect = getSubFirst();
                    GgafMainActor* pMainLockonEffect_Next = getSubFirst()->getNext();
                    pMainLockonEffect->_pNext = pLockonEffect;
                    pLockonEffect->_pPrev = pMainLockonEffect;
                    pLockonEffect->_pNext = pMainLockonEffect_Next;
                    pMainLockonEffect_Next->_pPrev = pLockonEffect;
                    pLockonEffect->activate(); //サブロックオン有効に
                    //ロックオン！
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());

                    _TRACE_("満帆では無い Subロックオン追加時 特殊なローテート lockon("<<prm_pTarget->getName()<<") AFTER");

                } else {
                    GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //２つなので結局Nextの位置
                    pLockonEffect->activate(); //サブロックオン有効に
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());

                    _TRACE_("満帆では無い Subロックオン追加時 ２つなので結局Nextの位置 lockon("<<prm_pTarget->getName()<<") AFTER");


                }

                //_pMainTarget = prm_pTarget;
            }
        }

        ((EffectLockon001*)getSubFirst())->_pTarget = prm_pTarget;
        dumpTarget(_pRingTarget->getCurrent());
        dump();
    }
//	_pMainLockOnTarget = _pRingTarget->getCurrent(); //processBehavior() で更新は
}

        // ＜切れ無い場合＞ エフェクトアクターは操作不要
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t1⇔
        // ⇔t2⇔t1⇔
        // ⇔t3⇔t2⇔t1⇔
        // ⇔t4⇔t3⇔t2⇔t1⇔
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        // ⇔t6⇔t5⇔t4⇔t3⇔t2⇔   ズルっ
        // ⇔t7⇔t6⇔t5⇔t4⇔t3⇔   ズルっ
        // ⇔t8⇔t7⇔t6⇔t5⇔t4⇔   ズルっ
        // ⇔t9⇔t8⇔t7⇔t6⇔t5⇔   ズルっとします

        //＜切れる場合＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t1)
        // ⇔t5⇔t4⇔t3⇔t2⇔
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・変化無し（S3が末尾へ）移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t5⇔t4⇔t3⇔t1⇔
        // ⇔Ｍ⇔S0⇔S1⇔S3⇔S2⇔    ・・・S2が末尾へ移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t3)
        // ⇔t5⇔t4⇔t2⇔t1⇔
        // ⇔Ｍ⇔S0⇔S2⇔S3⇔S1⇔    ・・・S1が末尾へ移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t4)
        // ⇔t5⇔t3⇔t2⇔t1⇔
        // ⇔Ｍ⇔S2⇔S3⇔S1⇔S0⇔    ・・・S0が末尾へ移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t5)
        // ⇔t4⇔t3⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・ S0が末尾へ（注意）移動してlockonRelase()



        //＜切れる場合2＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t1)
        // ⇔t4⇔t3⇔t1⇔
        // ⇔Ｍ⇔S0⇔S1⇔S3⇔S2⇔    ・・・S2が末尾へ（処理省略可？）移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t4⇔t3⇔t1⇔
        // ⇔Ｍ⇔S0⇔S2⇔S3⇔S1⇔    ・・・S1が末尾へ移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t3)
        // ⇔t4⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t4)
        // ⇔t3⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ（注意）移動してlockonRelase()



        //＜切れる場合3＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t1)
        // ⇔t3⇔t2⇔
        // ⇔Ｍ⇔S0⇔S2⇔S3⇔S1⇔    ・・・S1が末尾へ（処理省略可？）移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t3⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t3)
        // ⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ移動してlockonRelase()



        //＜切れる場合4＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t2⇔t1⇔
        //          ↓    remove(t1)
        // ⇔t2⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ（処理省略可？）移動してlockonRelase()

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾ヘ移動してlockonRelase()


        //＜切れる場合5＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t1⇔
        //          ↓    remove(t1)
        //
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・変化無しでMをlockonRelase()




            // 敵  敵  敵  敵  敵  敵  敵  敵                 t2  t1  tM  t4  t3
            //     ①  Ｍ                                   ⇔○⇔○⇔●⇔○⇔○⇔
            //                                                ①  ②  Ｍ  ④  ③
            // 敵  敵  敵  敵  敵  敵  敵  敵
            //     ①  ②  Ｍ

            // ここで描画サブアクターがこうだったら
            // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター

            // ⇔ア⇔イ⇔×⇔×⇔×⇔
            //
            // ⇔新⇔ア⇔イ⇔×⇔×⇔


            //  t1  tM  t3  t2
            //⇔○⇔●⇔○⇔○⇔
            //      ↓  addPrev(☆)   ☆＝prm_pTarget
            //  t1  New tM  t3  t2
            //⇔○⇔☆⇔●⇔○⇔○⇔
            //      ↓  prev()
            //  t1  tM  t4  t3  t2
            //⇔○⇔★⇔○⇔○⇔○⇔
            //(塗り潰しはアクティブ要素)


            // 敵  敵  敵  敵  敵  敵  敵  敵                 t2  t1  tM  t4  t3
            //     ①  ②  ③  ④  Ｍ                       ⇔○⇔○⇔●⇔○⇔○⇔
            //                                                ①  ②  Ｍ  ④  ③

            // 敵  敵  敵  敵  敵  敵  敵  敵
            //         ①  ②  ③  ④  Ｍ                   ⇔○⇔★⇔○⇔○⇔○⇔
            //                                                t2  t1  tM  t4  t3
            //                                             旧 ②  ①  Ｍ  ④  ③
            //                                                ↓  ↓  ↓  ↓  ↓
            //                                             新 ①  Ｍ  ④  ③  ②

                                                           //t1  tM  t4  t3  t2
            //  ここで描画サブアクターがこうだったら
            //  ⇔Ｍ⇔ S0⇔ S1⇔ S2⇔ S3⇔    ・・・エフェクトアクター
            //    Ｍ   ①   ②   ③   ④ _pTargetを
            //    ↓   ↓   ↓   ↓   ↓
            //新=旧④ 旧Ｍ 旧① 旧② 旧③ _pTarget行のように更新されてしまう

            //理想は
            //    Ｍ   ①   ②   ③   ④ _pTargetを
            //    ↓   ↓   ↓   ↓   ↓
            //新=旧④ 旧Ｍ 旧① 旧② 旧③ _pTarget行のように更新されてしまう

            // first を moveLastで良い？




            //   t1  tM  t4  t3  t2  描画順は こうなればいい
            //tM=prm_pTarget

            //tM, t4, t3, t2, t1
            //t5, t4, t3, t2, tM
            //t5, t4, t3, tM, t6
            //t5, t4, tM, t7, t6
            //t5, tM, t8, t7, t6
            //tM, t9, t8, t7, t6

            //ロック数がMAXならば、一番古い順に上書きで消されていくだけ
            //  t2  t1  tM  t4  t3
            //⇔○⇔○⇔●⇔○⇔○⇔
            //      ↓  prev()
            //  t2  tM  t5  t4  t3
            //⇔○⇔●⇔○⇔○⇔○⇔
            //      ↓  set(☆)   ☆＝prm_pTarget
            //  t2  tM  t5  t4  t3
            //⇔○⇔★⇔○⇔○⇔○⇔


            //ロックオンエフェクトをアクティブにする

            //  t2  t1  tM  t4  t3
            //  t1  tM  t4  t3  t2

            //⇔tM⇔t1⇔t2⇔t3⇔t4⇔ こうなら

            //⇔tM⇔t2⇔t3⇔t4⇔t5⇔ こうする
            //⇔tM⇔t3⇔t4⇔t5⇔t6⇔
            //⇔tM⇔t4⇔t5⇔t6⇔t7⇔
//
//
//
//
//        } else {
//            //tM=prm_pTarget
//
//            //tM
//            //tM, t1
//            //tM, t2, t1
//            //tM, t3, t2, t1
//            //tM, t4, t3, t2, t1
//
//
//            //t1, tM, t2
//            //t1, tM, t3, t2
//
//            //  t1  tM  t3  t2
//            //⇔○⇔●⇔○⇔○⇔
//            //      ↓  addPrev(☆)   ☆＝prm_pTarget
//            //  t1  New tM  t3  t2
//            //⇔○⇔☆⇔●⇔○⇔○⇔
//            //      ↓  prev()
//            //  t1  tM  t4  t3  t2
//            //⇔○⇔★⇔○⇔○⇔○⇔
//            //(塗り潰しはアクティブ要素)
//
//            _pRingTarget->addPrev(prm_pTarget, false);
//            _pRingTarget->prev();
//            _pMainTarget = prm_pTarget;
//
//
//
//            //ロックオンエフェクトをアクティブにする
//                //tM⇔ x⇔ x⇔ x⇔ x⇔ x   (xはinactive)
//                //tM⇔t1⇔ x⇔ x⇔ x⇔ x   (xはinactive)
//                //tM⇔t1⇔t2⇔ x⇔ x⇔ x   (xはinactive)
//                //tM⇔t1⇔t2⇔t3⇔ x⇔ x   (xはinactive)
//                //tM⇔t1⇔t2⇔t3⇔t4⇔ x   (xはinactive)
//                //tM⇔t1⇔t2⇔t3⇔t4⇔t5
//
//            GgafMainActor* pLockonEffect = getSubFirst();
//            for (int i = 0; i < _pRingTarget->length()-1; i++) {
//                pLockonEffect = pLockonEffect->getNext();
//            }
//            pLockonEffect->activate();
//            ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);
//
//        }
//
//    }



void MyOptionLockonController::releaseAllLockon() {
    while (_pRingTarget->length() > 0) {
        _pRingTarget->remove();
    }

    //ロックオンエフェクトをインアクティブにする
    GgafMainActor* pLockonEffect = getSubFirst();
    while (true) {
        ((EffectLockon001*)pLockonEffect)->releaseLockon();
        if (pLockonEffect->isLast()) {
            break;
        } else {
            pLockonEffect = pLockonEffect->getNext();
        }
    }
}


MyOptionLockonController::~MyOptionLockonController() {
    DELETE_IMPOSSIBLE_NULL(_pRingTarget);
}




void MyOptionLockonController::dumpTarget(GgafDx9GeometricActor* pMain) {

    if (_pRingTarget->getNextFromFirst(0) == NULL) {
        _TEXT_("NULL\n");
        return;
    } else {
        _TEXT_("⇔");
    }
    for (int i = 0; i < _pRingTarget->length(); i++) {
        if (_pRingTarget->getNextFromFirst(i) == pMain) {
            _TEXT_("！");
        }
        _TEXT_(_pRingTarget->getNextFromFirst(i)->getName()<<"["<<i<<"]⇔");
    }
    _TEXT_(" ... avtive="<<_pRingTarget->getCurrent()->getName()<<"\n");
}


