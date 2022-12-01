#include "MyLockonController.h"

#include "LockonCursor001_Main.h"
#include "LockonCursor001_Sub.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"

using namespace GgafLib;
using namespace VioletVreath;

int MyLockonController::lockon_num_ = 0;

MyLockonController::MyLockonController(const char* prm_name) :
        GgafCore::DestructActor(prm_name) {
    _class_name = "MyLockonController";
    pMainLockonEffect_ = NEW LockonCursor001_Main("MAIN");
    pMainLockonEffect_->inactivate();
    appendChild(pMainLockonEffect_);
    for (int i = 1; i < MAX_LOCKON_NUM; i++) {
        std::string name = "ChildLockon("+XTOS(i)+")";
        LockonCursor001_Sub* pLockonCursor_Sub = NEW LockonCursor001_Sub(name.c_str());
        pLockonCursor_Sub->inactivate();
        appendChild(pLockonCursor_Sub);
    }
}

void MyLockonController::initialize() {
}
void MyLockonController::onReset() {
    //ロックオンターゲットのリストを空にする
    listTarget_.removeAll();
    //ロックオンアクターのリセット
    LockonCursor001* pLockonCursor001;
    for (int i = 0; i < MAX_LOCKON_NUM; i++) {
        pLockonCursor001 = (LockonCursor001*)(getChild(i));
        pLockonCursor001->releaseLockon();
        pLockonCursor001->inactivate();
    }
}

void MyLockonController::onActive() {
    onReset();
}


void MyLockonController::processBehavior() {
    //ロックオンターゲット生存確認
    GgafDx::GeometricActor* pMainLockonTarget = listTarget_.getCurrent(); //メインロックオンのターゲット
    GgafDx::GeometricActor* pTarget = listTarget_.getCurrent();  //ターゲットカーソル
    GgafCore::MainActor* pLockonEffect_Active = (GgafCore::MainActor*)getChildFirst();         //ロックオンエフェクトカーソル
    int n = listTarget_.length();
    for (int i = 0; i < n; i++) {
        if (pTarget->isActiveInTheTree() && pTarget->getStatus()->get(STAT_Stamina) > 0) {
            //ターゲットが存命ならば
            //エフェクトアクターのターゲット更新、エフェクトをズルっとします
            ((LockonCursor001*)pLockonEffect_Active)->lockon(pTarget);
            if (!pLockonEffect_Active->isActiveInTheTree()) {
                pLockonEffect_Active->activate();
            }
            pLockonEffect_Active = pLockonEffect_Active->getNext(); //次回処理ロックオンエフェクトアクター次へ
            pTarget = listTarget_.next();                         //次回処理ターゲットを次へ
        } else {
            //ターゲットが死亡時
            if (pTarget == pMainLockonTarget) {
                //死亡ターゲットがメインロックオンのターゲットであった場合
                if (listTarget_.length() == 1) {
                    //死亡ターゲットがメインロックオンのターゲットでリングの最後の一つの場合
                    listTarget_.remove();                                    //ターゲット抜き出し
                    ((LockonCursor001*)pLockonEffect_Active)->releaseLockon(); //ロックオンエフェクトをリリース実行
                    pTarget = nullptr;
                    break;
                } else {
                    //死亡ターゲットがメインロックオンのターゲットでリングの最後の一つでは無い場合
                    listTarget_.remove();               //ターゲット抜き出し
                    pTarget = listTarget_.getCurrent(); //次回処理ターゲットを次へ（remove()により次のターゲットはgetCurrent()となる）
                    pMainLockonTarget = pTarget;          //メインロックオンのターゲットを更新
                    //メインロックオンエフェクトを直近ロックオンへ戻すし
                    //メインロックオンエフェクトの次のエフェクトを解放するという動作をしたい
                    ((LockonCursor001*)pLockonEffect_Active->getNext())->releaseLockon(); //「次」のロックオンエフェクトをリリース実行
                    pLockonEffect_Active->getNext()->moveLast();               //次のロックオンエフェクトを末尾へ
                    //「次回処理ロックオンエフェクトアクター次へ」の処理対象移動は不要。次に処理したいロックオンエフェクトアクターそのままであるため。
                }
            } else {
                //死亡ターゲットがサブロックオンのターゲットであった場合
                listTarget_.remove();               //ターゲット抜き出し
                pTarget = listTarget_.getCurrent(); //次回処理ターゲットを次へ（remove()により次のターゲットはgetCurrent()となる）
                ((LockonCursor001*)pLockonEffect_Active)->releaseLockon(); //ロックオンエフェクトをリリース実行
                pLockonEffect_Active = pLockonEffect_Active->getNext();    //次回処理ロックオンエフェクトアクター次へ
                pLockonEffect_Active->getPrev()->moveLast();    //今回処理ロックオンエフェクトアクターを末尾へ
            }
        }
    }
}

void MyLockonController::processJudgement() {
}

void MyLockonController::onInactive() {
    onReset();
}

void MyLockonController::lockon(GgafDx::GeometricActor* prm_pTarget) {
    if (MyLockonController::lockon_num_ == 0) {
        return; //現在のロックオン可能数が0
    }

    if (listTarget_.indexOf(prm_pTarget) == -1) {
        //ロックオン済みに無いので、ロックオンする
        if (listTarget_.length() >= MyLockonController::lockon_num_) { //ターゲットリストが既に満員の場合
            //ロックオンターゲットローテート
            listTarget_.prev();           //カレントを最終要素へ
            listTarget_.replace(prm_pTarget); //最終要素だったところにメインターゲット上書き
            //ロックオンエフェクトアクターはそのまま
            //これにより、processBehavior() のターゲット存命時のしょりにより
            //ズルッとずれる。
        } else {   //まだターゲットリストに何もない、或いは余裕がある（追加可能な場合）
            //ターゲットローテート
            listTarget_.addPrev(prm_pTarget, false);
            listTarget_.prev();
            //ロックオンエフェクト
            if (listTarget_.length() == 1) {
                //最初のロックオンターゲット追加時（メインロックオンターゲット）
                GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst(); //メインロックオエフェクト
                pLockonEffect->activate();
                ((LockonCursor001*)pLockonEffect)->lockon(prm_pTarget);

                //最初のロックオンターゲット以外の追加時（サブロックオンターゲット追加時）
            } else if (listTarget_.length() > 1) {
                //Childロックオン追加時
                if (listTarget_.length() >= 3) {
                    //３個目の以降ターゲット追加時（２個目以降のサブロックオンターゲット追加時）
                    //ロックオンエフェクトの特殊なローテートを行う。（※最後のコメント＜追加の場合＞参照）
                    //Lastを切り出す
                    GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst()->getPrev(); //Last
                    GgafCore::MainActor* pLockonEffect_Next = pLockonEffect->getNext(); //Mainロックオンとなる
                    GgafCore::MainActor* pLockonEffect_Prev = pLockonEffect->getPrev();
                    pLockonEffect_Prev->_pNext = pLockonEffect_Next;
                    pLockonEffect_Next->_pPrev = pLockonEffect_Prev;
                    pLockonEffect_Prev->_is_last_flg = true;
                    pLockonEffect->_is_last_flg = false;
                    //First->Next の間に入れる
                    GgafCore::MainActor* pMainLockonEffect = (GgafCore::MainActor*)getChildFirst();
                    GgafCore::MainActor* pMainLockonEffect_Next = (GgafCore::MainActor*)getChildFirst()->getNext();
                    pMainLockonEffect->_pNext = pLockonEffect;
                    pLockonEffect->_pPrev = pMainLockonEffect;
                    pLockonEffect->_pNext = pMainLockonEffect_Next;
                    pMainLockonEffect_Next->_pPrev = pLockonEffect;
                    pLockonEffect->activate(); //サブロックオン有効に
                    //サブロックオンエフェクトロックオン！
                    ((LockonCursor001*)pLockonEffect)->lockon(listTarget_.getNext());
                } else {
                    //２個目のターゲット追加時（最初のサブロックオンターゲット追加時）
                    GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst()->getPrev(); //２つなので結局Nextの位置
                    pLockonEffect->activate(); //サブロックオン有効に
                    ((LockonCursor001*)pLockonEffect)->lockon(listTarget_.getNext());
                }
            }
        }
    } else {
        //prm_pTarget は既にロックオン済み
    }
}

void MyLockonController::releaseAllLockon() {
    if (listTarget_.length() == 0) {
        return;
    }
    listTarget_.removeAll();
    //ロックオンエフェクトをインアクティブにする
    GgafCore::MainActor* pLockonEffect = (GgafCore::MainActor*)getChildFirst();
    while (pLockonEffect) {
        ((LockonCursor001*)pLockonEffect)->releaseLockon();
        if (pLockonEffect->isLast()) {
            break;
        } else {
            pLockonEffect = pLockonEffect->getNext();
        }
    }
}

MyLockonController::~MyLockonController() {
}

void MyLockonController::dumpTarget(GgafDx::GeometricActor* pMain) {
    if (listTarget_.getFromFirst(0) == nullptr) {
        _TRACE_N_("nullptr\n");
        return;
    } else {
        _TRACE_N_("⇔");
    }
    for (int i = 0; i < listTarget_.length(); i++) {
        if (listTarget_.getFromFirst(i) == pMain) {
            _TRACE_N_("！");
        }
        _TRACE_N_(listTarget_.getFromFirst(i)->getName()<<"["<<i<<"]⇔");
    }
    _TRACE_N_(" ... avtive="<<listTarget_.getCurrent()->getName()<<"\n");
}

//【備忘録】
//「ロックオンターゲット(敵)とロックオンエフェクト(照準)の関係」(2010/09/14)
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
//          ↓            t1ロックオン
// ⇔t1⇔
// エフェクトアクター変化無し
//          ↓            t2追加ロックオン
// ⇔t2⇔t1⇔
// ⇔Ｍ⇔S3⇔S0⇔S1⇔S2⇔
//          ↓            t3追加ロックオン
// ⇔t3⇔t2⇔t1⇔
// ⇔Ｍ⇔S2⇔S3⇔S0⇔S1⇔
//          ↓            t4追加ロックオン
// ⇔t4⇔t3⇔t2⇔t1⇔
// ⇔Ｍ⇔S1⇔S2⇔S3⇔S0⇔
//          ↓            t5追加ロックオン
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
