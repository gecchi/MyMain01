#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

/** １オプション当たりの最大可能ロックオン数 */
int MyLockonController::max_lockon_num_ = 8;
int MyLockonController::lockon_num_ = 0;


MyLockonController::MyLockonController(const char* prm_name) :
        GgafDummyActor(prm_name, nullptr) {
    _class_name = "MyLockonController";
    pRingTarget_ = NEW GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>();
    pMainLockonEffect_ = NEW EffectLockon001_Main("MAIN");
    pMainLockonEffect_->inactivateImmed();
    addSubLast(pMainLockonEffect_);
    for (int i = 1; i < MyLockonController::max_lockon_num_; i++) {
        std::string name = "SubLockon("+ITOS(i)+")";
        EffectLockon001_Sub* pSubLockon = NEW EffectLockon001_Sub(name.c_str());
        pSubLockon->inactivateImmed();
        addSubLast(pSubLockon);
    }
}

void MyLockonController::initialize() {
}
void MyLockonController::onReset() {
    //ロックオンターゲットのリストを空にする
    int n = pRingTarget_->length();
    for (int i = 0; i < n; i++) {
        pRingTarget_->remove();
    }
    //ロックオンアクターのリセット
    EffectLockon001* pEffectLockon001;
    for (int i = 0; i < MyLockonController::max_lockon_num_; i++) {
        pEffectLockon001 = (EffectLockon001*)(getSub(i));
        pEffectLockon001->releaseLockon();
        pEffectLockon001->inactivate();
    }
}

void MyLockonController::onActive() {
    onReset();
}


void MyLockonController::processBehavior() {
    //ロックオンターゲット生存確認
    GgafDxGeometricActor* pMainLockonTarget = pRingTarget_->getCurrent(); //メインロックオンのターゲット
    GgafDxGeometricActor* pTarget = pRingTarget_->getCurrent();  //ターゲットカーソル
    GgafMainActor* pLockonEffect_Active = getSubFirst();         //ロックオンエフェクトカーソル
    int n = pRingTarget_->length();
    for (int i = 0; i < n; i++) {
        if (pTarget->isActive() && pTarget->isActiveInTheTree() && pTarget->_pStatus->get(STAT_Stamina) > 0) {
            //ターゲットが存命ならば
            //エフェクトアクターのターゲット更新、エフェクトをズルっとします
            ((EffectLockon001*)pLockonEffect_Active)->lockon(pTarget);
            if (!pLockonEffect_Active->isActiveInTheTree()) {
                pLockonEffect_Active->activate();
            }
            pLockonEffect_Active = pLockonEffect_Active->getNext(); //次回処理ロックオンエフェクトアクター次へ
            pTarget = pRingTarget_->next();                         //次回処理ターゲットを次へ
        } else {
            //ターゲットが死亡時
            if (pTarget == pMainLockonTarget) {
                //死亡ターゲットがメインロックオンのターゲットであった場合
                if (pRingTarget_->length() == 1) {
                    //死亡ターゲットがメインロックオンのターゲットでリングの最後の一つの場合
                    pRingTarget_->remove();                                    //ターゲット抜き出し
                    ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンエフェクトをリリース実行
                    pTarget = nullptr;
                    break;
                } else {
                    //死亡ターゲットがメインロックオンのターゲットでリングの最後の一つでは無い場合
                    pRingTarget_->remove();               //ターゲット抜き出し
                    pTarget = pRingTarget_->getCurrent(); //次回処理ターゲットを次へ（remove()により次のターゲットはgetCurrent()となる）
                    pMainLockonTarget = pTarget;          //メインロックオンのターゲットを更新
                    //メインロックオンエフェクトを直近ロックオンへ戻すし
                    //メインロックオンエフェクトの次のエフェクトを解放するという動作をしたい
                    ((EffectLockon001*)pLockonEffect_Active->getNext())->releaseLockon(); //次のロックオンエフェクトをリリース実行
                    pLockonEffect_Active->getNext()->moveLastImmed();               //次のロックオンエフェクトを末尾へ
                    //「次回処理ロックオンエフェクトアクター次へ」の処理対象移動は不要。次に処理したいロックオンエフェクトアクターそのままであるため。
                }
            } else {
                //死亡ターゲットがサブロックオンのターゲットであった場合
                pRingTarget_->remove();               //ターゲット抜き出し
                pTarget = pRingTarget_->getCurrent(); //次回処理ターゲットを次へ（remove()により次のターゲットはgetCurrent()となる）
                ((EffectLockon001*)pLockonEffect_Active)->releaseLockon(); //ロックオンエフェクトをリリース実行
                pLockonEffect_Active = pLockonEffect_Active->getNext();    //次回処理ロックオンエフェクトアクター次へ
                pLockonEffect_Active->getPrev()->moveLastImmed();    //今回処理ロックオンエフェクトアクターを末尾へ
            }
        }
    }
}

void MyLockonController::processJudgement() {
}
void MyLockonController::onInactive() {
    onReset();
}

void MyLockonController::lockon(GgafDxGeometricActor* prm_pTarget) {
    if (MyLockonController::lockon_num_ == 0) {
        return; //現在のロックオン可能数が0
    }

    if (pRingTarget_->indexOf(prm_pTarget) == -1) {
        //ロックオン済みに無いので、ロックオンする
        if (pRingTarget_->length() >= MyLockonController::lockon_num_) { //ターゲットリストが既に満員の場合
            //ロックオンターゲットローテート
            pRingTarget_->prev();           //カレントを最終要素へ
            pRingTarget_->set(prm_pTarget, false); //最終要素だったところにメインターゲット上書き
            //ロックオンエフェクトアクターはそのまま
            //これにより、processBehavior() のターゲット存命時のしょりにより
            //ズルッとずれる。
        } else {   //まだターゲットリストに何もない、或いは余裕がある（追加可能な場合）
            //ターゲットローテート
            pRingTarget_->addPrev(prm_pTarget, false);
            pRingTarget_->prev();
            //ロックオンエフェクト
            if (pRingTarget_->length() == 1) {
                //最初のロックオンターゲット追加時（メインロックオンターゲット）
                GgafMainActor* pLockonEffect = getSubFirst(); //メインロックオエフェクト
                pLockonEffect->activate();
                ((EffectLockon001*)pLockonEffect)->lockon(prm_pTarget);

                //最初のロックオンターゲット以外の追加時（サブロックオンターゲット追加時）
            } else if (pRingTarget_->length() > 1) {
                //Subロックオン追加時
                if (pRingTarget_->length() >= 3) {
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
                    ((EffectLockon001*)pLockonEffect)->lockon(pRingTarget_->getNext());
                } else {
                    //２個目のターゲット追加時（最初のサブロックオンターゲット追加時）
                    GgafMainActor* pLockonEffect = getSubFirst()->getPrev(); //２つなので結局Nextの位置
                    pLockonEffect->activate(); //サブロックオン有効に
                    ((EffectLockon001*)pLockonEffect)->lockon(pRingTarget_->getNext());
                }
            }
        }
    } else {
        //prm_pTarget は既にロックオン済み
    }
}

void MyLockonController::releaseAllLockon() {
    if (pRingTarget_->length() == 0) {
        return;
    }
    pRingTarget_->removeAll();
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

MyLockonController::~MyLockonController() {
    DELETE_IMPOSSIBLE_NULL(pRingTarget_);
}

void MyLockonController::dumpTarget(GgafDxGeometricActor* pMain) {
    if (pRingTarget_->getFromFirst(0) == nullptr) {
        _TEXT_("nullptr\n");
        return;
    } else {
        _TEXT_("⇔");
    }
    for (int i = 0; i < pRingTarget_->length(); i++) {
        if (pRingTarget_->getFromFirst(i) == pMain) {
            _TEXT_("！");
        }
        _TEXT_(pRingTarget_->getFromFirst(i)->getName()<<"["<<i<<"]⇔");
    }
    _TEXT_(" ... avtive="<<pRingTarget_->getCurrent()->getName()<<"\n");
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
