#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

int MyOptionLockonController::_max_lockon_num = 5;

MyOptionLockonController::MyOptionLockonController(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "MyOptionLockonController";
    _now_lockon_num = 0;


    _pRingTarget = NEW GgafLinkedListRing<GgafDx9Core::GgafDx9GeometricActor>();
    _pMainLockOnTarget = NULL;

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
    GgafDx9GeometricActor* pTarget = _pRingTarget->getCurrent();
//    _pMainTarget = pTarget;

    GgafMainActor* pLockonEffect_Active = getSubFirst();
    int n = _pRingTarget->length();
    for (int i = 0; i < n; i++) {

        if (pTarget->isActive() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
            //OK
            //エフェクトアクターのターゲット更新                    //エフェクトをズルっとします
            ((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
            pLockonEffect_Active = pLockonEffect_Active->getNext();//エフェクトアクター次へ
            pTarget = _pRingTarget->next(); //次へ

        } else {

            //切れる場合
//            _TRACE_("---------------------------------");
//            _TRACE_("切れる BEFORE");
//            dumpTarget();
//            dump();
            if (pTarget == _pRingTarget->getCurrent()) {
                //メインロックオン時処理
                if (_pRingTarget->length() == 0) {
                    _pRingTarget->remove(); //抜き出し
					pTarget = _pRingTarget->getCurrent(); //Target次へ
                    //最後の一つ
                    ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンリリース
//                    _pMainTarget = NULL;
                } else {
                    _pRingTarget->remove(); //抜き出し
					pTarget = _pRingTarget->getCurrent(); //Target次へ
                    //アクティブを次へ処理は不要、remove()したので自動的に次になっている。
//                    _pMainTarget = _pRingTarget->getCurrent();

                    //メインロックオンエフェクトを直近ロックオンへ戻す
					((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
                    //そのため
                    //メインロックオンエフェクトの次のエフェクトを解放
                    ((EffectLockon001*)pLockonEffect_Active->getNext())->releaseLockon();
                    pLockonEffect_Active->getNext()->moveLastImmediately(); //末尾へ

                    //pLockonEffect_Active->getNext()->releaseLockon();//inactivate(); //解放
                    //メインロックオンエフェクトアクターのターゲット更新、ズルっと戻ります
                    //((EffectLockon001*)pLockonEffect_Active)->_pTarget = _pRingTarget->getCurrent();

                    pLockonEffect_Active = pLockonEffect_Active->getNext();//次へ

                }
            } else {
                //サブロックオン時処理

                _pRingTarget->remove(); //ターゲット抜き出し
				pTarget = _pRingTarget->getCurrent(); //Target次へ
                //アクティブを次へ処理は不要、remove()したので自動的に次になっている。

                ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンリリース
                pLockonEffect_Active = pLockonEffect_Active->getNext();//先に次へ
                pLockonEffect_Active->getPrev()->moveLastImmediately(); //今回releaseLockon()を末尾へ

                //pLockonEffect_Active->_pTarget は更新しなくても変化してないので不要。という設計。
            }
//            _TRACE_("切れる AFTER");
//            dumpTarget();
//            dump();

        }
    }
    _pMainLockOnTarget = _pRingTarget->getCurrent();
    //_TRACE_("_pRingTarget->getCurrent()="<<(_pRingTarget->getCurrent()==NULL?"NULL":_pRingTarget->getCurrent()->getName()));
}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockon(GgafDx9GeometricActor* prm_pTarget) {
    // 追加の場合エフェクトアクターは操作不要

    if (_pRingTarget->indexOf(prm_pTarget) == -1) { //ロックオン済みに無ければ
//        _TRACE_("---------------------------------");
//        _TRACE_("_pRingTarget->indexOf("<<prm_pTarget->getName()<<") = "<<_pRingTarget->indexOf(prm_pTarget));
//        _TRACE_("lockon("<<prm_pTarget->getName()<<") BEFORE");
//        dumpTarget();
//        dump();

        if (_pRingTarget->length() >= _max_lockon_num) {

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

        } else {

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
				} else {
					GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //２つなので結局Nextの位置
					pLockonEffect->activate(); //サブロックオン有効に
					((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());
				}

                //_pMainTarget = prm_pTarget;
            }
        }

        ((EffectLockon001*)getSubFirst())->_pTarget = prm_pTarget;

//        _TRACE_("lockon("<<prm_pTarget->getName()<<") AFTER");
//        dumpTarget();
//        dump();
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
}




void MyOptionLockonController::dumpTarget() {

    GgafMainActor* pActor = _pRingTarget->getCurrent();
	if (pActor == NULL) {
		_TEXT_("NULL\n");
		return;
	} else {
	    _TEXT_("⇔");
	}
    for (int i = 0; i < _pRingTarget->length(); i++) {
        if (pActor == _pRingTarget->getCurrent()) {
            _TEXT_("！");
        }
        _TEXT_(_pRingTarget->getNext(i)->getName()<<"["<<i<<"]⇔");
    }
    _TEXT_(" ... avtive="<<_pRingTarget->getCurrent()->getName()<<"\n");
}


