#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


MyOptionLockonController::MyOptionLockonController(const char* prm_name) :
        GgafDummyActor(prm_name, NULL) {
    _class_name = "MyOptionLockonController";
    _pRingTarget = NEW GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>();
    _pMainLockonEffect = NEW EffectLockon001_Main("MAIN");
    _pMainLockonEffect->inactivateImmediately();
    addSubLast(_pMainLockonEffect);
    for (int i = 1; i < MyOption::_max_lockon_num; i++) {
        stringstream name;
        name <<  "SUB["<<i<<"]";
        EffectLockon001_Sub* pSubLockon = NEW EffectLockon001_Sub(name.str().c_str());
        pSubLockon->inactivateImmediately();
        addSubLast(pSubLockon);
    }
}

void MyOptionLockonController::initialize() {
}
void MyOptionLockonController::onReset() {
    GgafMainActor* pLockonEffect_Active = getSubFirst();
    int n = _pRingTarget->length();
    for (int i = 0; i < n; i++) {
        _pRingTarget->remove();
        ((EffectLockon001*)pLockonEffect_Active)->releaseLockon();
        pLockonEffect_Active->getPrev()->moveLastImmediately();
    }
}

void MyOptionLockonController::processBehavior() {
    //ロックオンターゲット生存確認
    GgafDxGeometricActor* pMainLockonTarget = _pRingTarget->getCurrent(); //メインロックオンのターゲット
    GgafDxGeometricActor* pTarget = _pRingTarget->getCurrent(); //ターゲットカーソル
    GgafMainActor* pLockonEffect_Active = getSubFirst();         //ロックオンエフェクトカーソル
    int n = _pRingTarget->length();
    for (int i = 0; i < n; i++) {
        if (pTarget->isActiveInTheTree() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
            //ターゲットが存命ならば
            //エフェクトアクターのターゲット更新、エフェクトをズルっとします
            ((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
            if (!pLockonEffect_Active->isActiveInTheTree()) {
                pLockonEffect_Active->activate();
            }
            pLockonEffect_Active = pLockonEffect_Active->getNext(); //次回処理ロックオンエフェクトアクター次へ
            pTarget = _pRingTarget->next();                         //次回処理ターゲットを次へ
        } else {
            //ターゲットが死亡時
            if (pTarget == pMainLockonTarget) {
                //死亡ターゲットがメインロックオンのターゲットであった場合
                if (_pRingTarget->length() == 1) {
                    //死亡ターゲットがメインロックオンのターゲットでリングの最後の一つの場合
                    _pRingTarget->remove();                                    //ターゲット抜き出し
                    ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンエフェクトをリリース実行
                    pTarget = NULL;
                    break;
                } else {
                    //死亡ターゲットがメインロックオンのターゲットでリングの最後の一つでは無い場合
                    _pRingTarget->remove();               //ターゲット抜き出し
                    pTarget = _pRingTarget->getCurrent(); //次回処理ターゲットを次へ（remove()により次のターゲットはgetCurrent()となる）
                    pMainLockonTarget = pTarget;          //メインロックオンのターゲットを更新
                    //メインロックオンエフェクトを直近ロックオンへ戻すし
                    //メインロックオンエフェクトの次のエフェクトを解放するという動作をしたい
                    ((EffectLockon001*)pLockonEffect_Active->getNext())->releaseLockon(); //次のロックオンエフェクトをリリース実行
                    pLockonEffect_Active->getNext()->moveLastImmediately();               //次のロックオンエフェクトを末尾へ
                    //「次回処理ロックオンエフェクトアクター次へ」の処理対象移動は不要。次に処理したいロックオンエフェクトアクターそのままであるため。
                }
            } else {
                //死亡ターゲットがサブロックオンのターゲットであった場合
                _pRingTarget->remove();               //ターゲット抜き出し
                pTarget = _pRingTarget->getCurrent(); //次回処理ターゲットを次へ（remove()により次のターゲットはgetCurrent()となる）
                ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンエフェクトをリリース実行
                pLockonEffect_Active = pLockonEffect_Active->getNext();    //次回処理ロックオンエフェクトアクター次へ
                pLockonEffect_Active->getPrev()->moveLastImmediately();    //今回処理ロックオンエフェクトアクターを末尾へ
            }
        }
    }

    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
        dumpTarget(_pRingTarget->getCurrent());
        dump();
    }


}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockon(GgafDxGeometricActor* prm_pTarget) {
    if (_pRingTarget->indexOf(prm_pTarget) == -1) { //ロックオン済みに無ければ

        if (_pRingTarget->length() >= MyOption::_lockon_num) {
            //ターゲットのリストが既に満員の場合
            //ロックオンターゲットローテート
            _pRingTarget->prev();
            _pRingTarget->set(prm_pTarget);
            //ロックオンエフェクトアクターはそのまま
            //これにより、processBehavior() のターゲット存命時のしょりにより
            //ズルッとずれる。
        } else {
            //ターゲットのリストが既に満員では無い（追加可能な場合）
            //ターゲットローテート
            _pRingTarget->addPrev(prm_pTarget, false);
            _pRingTarget->prev();
            //ロックオンエフェクト
            if (_pRingTarget->length() == 1) {
                //最初のロックオンターゲット追加時（メインロックオンターゲット）
                GgafMainActor* pLockonEffect = getSubFirst(); //メインロックオエフェクト
                pLockonEffect->activate();
                ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);
                //最初のロックオンターゲット以外の追加時（サブロックオンターゲット追加時）
            } else if (_pRingTarget->length() > 1) {
                //Subロックオン追加時
                if (_pRingTarget->length() >= 3) {
                    //３個目の以降ターゲット追加時（２個目以降のサブロックオンターゲット追加時）
                    //ロックオンエフェクトの特殊なローテートを行う。（※最後のコメント＜追加の場合＞参照）
                    //Lastを切り出す
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
                    //サブロックオンエフェクトロックオン！
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());
                } else {
                    //２個目のターゲット追加時（最初のサブロックオンターゲット追加時）
                    GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //２つなので結局Nextの位置
                    pLockonEffect->activate(); //サブロックオン有効に
                    ((EffectLockon001*)pLockonEffect)->lockon(_pRingTarget->getNext());
                }
            }
        }
    }
}

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


void MyOptionLockonController::dumpTarget(GgafDxGeometricActor* pMain) {

    if (_pRingTarget->getFromFirst(0) == NULL) {
        _TEXT_("NULL\n");
        return;
    } else {
        _TEXT_("⇔");
    }
    for (int i = 0; i < _pRingTarget->length(); i++) {
        if (_pRingTarget->getFromFirst(i) == pMain) {
            _TEXT_("！");
        }
        _TEXT_(_pRingTarget->getFromFirst(i)->getName()<<"["<<i<<"]⇔");
    }
    _TEXT_(" ... avtive="<<_pRingTarget->getCurrent()->getName()<<"\n");
}

//【備忘録】
//「ロックオンターゲットとロックオンエフェクトの関係」(2010/09/14)
//
//ロックオン時、ロックオンリリース時の
//ロックオンターゲットとロックオンエフェクトの関係をメモとして残す。
//
//Ｍ      … メインロックオンエフェクト
//S0～S3  … サブロックオンエフェクト
//t1～t5  … ロックオンターゲット
//
//メインロックオンエフェクト(Ｍ)の場所に位置するロックオンターゲットを
//「メインロックオンターゲット」
//サブロックオンエフェクト(S0～S3)の場所に位置するロックオンターゲットを
//「サブロックオンターゲット」
//と呼ぶことにする。

//＜追加の場合＞
// ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクター
//          ↓            t1追加
// ⇔t1⇔
// エフェクトアクター変化無し
//          ↓            t2追加
// ⇔t2⇔t1⇔
// ⇔Ｍ⇔S3⇔S0⇔S1⇔S2⇔
//          ↓            t3追加
// ⇔t3⇔t2⇔t1⇔
// ⇔Ｍ⇔S2⇔S3⇔S0⇔S1⇔
//          ↓            t4追加
// ⇔t4⇔t3⇔t2⇔t1⇔
// ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔
//          ↓            t5追加
// ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
// ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔

// ＜満員で追加の場合＞
// ⇔Ｍ⇔S0⇔S1⇔S2⇔S3⇔    ・・・エフェクトアクターは操作不要
//
// ⇔t5⇔t4⇔t3⇔t2⇔t1⇔
// ⇔t6⇔t5⇔t4⇔t3⇔t2⇔   ズルっ
// ⇔t7⇔t6⇔t5⇔t4⇔t3⇔   ズルっ
// ⇔t8⇔t7⇔t6⇔t5⇔t4⇔   ズルっ
// ⇔t9⇔t8⇔t7⇔t6⇔t5⇔   ズルっとします

//＜死亡の場合＞
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
