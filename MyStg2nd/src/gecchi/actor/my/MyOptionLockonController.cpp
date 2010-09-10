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
    _pMainTarget = NULL;

    EffectLockon001_Main* _pMainLockonEffect = NEW EffectLockon001_Main("LOCKON_MARK");
    _pMainLockonEffect->inactivateImmediately();
    addSubLast(_pMainLockonEffect);
    for (int i = 1; i < _max_lockon_num; i++) {
        EffectLockon001_Sub* pSubLockon = NEW EffectLockon001_Sub("SUB_LOCKON_MARK");
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
    _pMainTarget = pTarget;

    GgafMainActor* pLockonEffect = getSubFirst();

    for (int i = 0; i < _pRingTarget->length(); i++) {

        if (pTarget->isActive() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
            //OK
            pTarget = _pRingTarget->next(); //次へ
        } else {
            //切れる場合
            if (i == 0) {
                //メインロックオン時処理
                pTarget = _pRingTarget->remove(); //抜き出し
                //エフェクトをズルっとします
                GgafMainActor* pLockonEffect = getSubFirst()->getNext();
                pLockonEffect->moveLastImmediately(); //末尾へ
                ((EffectLockon001*)pLockonEffect)->releaseLockon();

                pTarget = _pRingTarget->getCurrent(); //次へ（remove()したので自動的に次になっている)
                _pMainTarget = pTarget;
            } else {
                //サブロックオン時処理

                //ターゲット抜き出し
                pTarget = _pRingTarget->remove();
                //対応エフェクトを末尾へ
                GgafMainActor* pLockonEffect = getSubFirst();
                for (int j = 0; j < i; j++) {
                    pLockonEffect = pLockonEffect->getNext();
                }
                pLockonEffect->moveLastImmediately(); //末尾へ
                ((EffectLockon001*)pLockonEffect)->releaseLockon();

                pTarget = _pRingTarget->getCurrent(); //次へ（remove()したので自動的に次になっている)
            }



        }
    }

}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockon(GgafDx9GeometricActor* prm_pTarget) {
    // 追加の場合エフェクトアクターは操作不要

    if (_pRingTarget->indexOf(prm_pTarget) == -1) { //ロックオン済みに無ければ
        if (_pRingTarget->length() > _max_lockon_num) {

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


            //ロックオンエフェクトローテート
            //操作不要


            //ロックオンエフェクト ロックオン
            //フルロックオン状態であるため必要なし

        } else {

            // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
            //
            // ⇔t1⇔
            // ⇔t2⇔t1⇔
            // ⇔t3⇔t2⇔t1⇔
            // ⇔t4⇔t3⇔t2⇔t1⇔
            // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔

            //ターゲットローテート
            _pRingTarget->addPrev(prm_pTarget, false);
            _pRingTarget->prev();
            _pMainTarget = prm_pTarget;

            //ロックオンエフェクトローテート
            //操作不要

            //ロックオンエフェクト ロックオン
            GgafMainActor* pLockonEffect = getSubFirst();
            for (int i = 0; i < _pRingTarget->length()-1; i++) {
                pLockonEffect = pLockonEffect->getNext();
            }
            pLockonEffect->activate();
            ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);

            _pMainTarget = prm_pTarget;
        }
    }
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
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・変化無し（S3が末尾へ）

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t5⇔t4⇔t3⇔t1⇔
        // ⇔Ｍ⇔S0⇔S1⇔S3⇔S2⇔    ・・・S2が末尾へ

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t3)
        // ⇔t5⇔t4⇔t2⇔t1⇔
        // ⇔Ｍ⇔S0⇔S2⇔S3⇔S1⇔    ・・・S1が末尾へ

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t4)
        // ⇔t5⇔t3⇔t2⇔t1⇔
        // ⇔Ｍ⇔S2⇔S3⇔S1⇔S0⇔    ・・・S0が末尾へ

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t5)
        // ⇔t4⇔t3⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・ S0が末尾へ（注意）



        //＜切れる場合2＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t1)
        // ⇔t4⇔t3⇔t1⇔
        // ⇔Ｍ⇔S0⇔S1⇔S3⇔S2⇔    ・・・S2が末尾へ（処理省略可？）

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t4⇔t3⇔t1⇔
        // ⇔Ｍ⇔S0⇔S2⇔S3⇔S1⇔    ・・・S1が末尾へ

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t3)
        // ⇔t4⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t4⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t4)
        // ⇔t3⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ（注意）



        //＜切れる場合3＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t1)
        // ⇔t3⇔t2⇔
        // ⇔Ｍ⇔S0⇔S2⇔S3⇔S1⇔    ・・・S1が末尾へ（処理省略可？）

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t3⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t3⇔t2⇔t1⇔
        //          ↓    remove(t3)
        // ⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ



        //＜切れる場合4＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t2⇔t1⇔
        //          ↓    remove(t1)
        // ⇔t2⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ（処理省略可？）

        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t2⇔t1⇔
        //          ↓    remove(t2)
        // ⇔t2⇔t1⇔
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・S0が末尾へ


        //＜切れる場合5＞
        // ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
        // ⇔t1⇔
        //          ↓    remove(t1)
        //
        // ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔    ・・・変化無し




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
