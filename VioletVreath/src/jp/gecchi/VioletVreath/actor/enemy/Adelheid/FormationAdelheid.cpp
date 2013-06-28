#include "stdafx.h"
#include "FormationAdelheid.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Palisana/EnemyPalisana.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adelheid/EnemyAdelheid.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


FormationAdelheid::FormationAdelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationAdelheid";

    pPalisana_start = NEW EnemyPalisana("Palisana_START");
    pPalisana_start->inactivateImmed();
    addSubGroup(pPalisana_start);

    pPalisana_goal = NEW EnemyPalisana("Palisana_GOAL");
    pPalisana_goal->inactivateImmed();
    addSubGroup(pPalisana_goal);

    //軌道計算用のダミー
    pDummy_ = NEW EnemyAdelheid("DammyEnemyAdelheid");
    pDummy_->pKurokoLeader_ = nullptr;
    pDummy_->inactivateImmed();
    addSubGroup(pDummy_);

    //編隊隊員デポジトリセット
    pConn_AdelheidDepo_ = connect_DepositoryManager("EnemyAdelheid4Formation");
    setFormationMember(pConn_AdelheidDepo_->peek());
    //編隊隊員のショットデポジトリ
    pConn_ShotDepo_ = connect_DepositoryManager("EnemyAdelheidShot");

    updateRankParameter();
    useProgress(PROG_LEAVE);
}

void FormationAdelheid::updateRankParameter() {
    RV_NumFormation_     = RF_FormationAdelheid_Num(G_RANK);    //編隊数
    RV_MvVelo_           = RF_FormationAdelheid_MvVelo(G_RANK); //速度
    RV_IntervalFrames_   = 64 / C_PX(RV_MvVelo_);
}

void FormationAdelheid::initialize() {

}

void FormationAdelheid::onActive() {
    updateRankParameter();
    _pProg->reset(PROG_INIT);
}

void FormationAdelheid::processBehavior() {
    //pPalisana_start が破壊されているかチェック
    if (pPalisana_start) {
        if (pPalisana_start->onChangeToInactive()) {
            pPalisana_start = nullptr;
        }
    }
    //pPalisana_goal が破壊されているかチェック
    if (pPalisana_goal) {
        if (pPalisana_goal->onChangeToInactive()) {
            pPalisana_goal = nullptr;
        }
    }

    switch (_pProg->get()) {
         case PROG_INIT: {
             updateRankParameter();
             //ダミー(pDummy_)を使ってメンバーのスプライン移動の開始位置と方向、終了位置と方向を予め求める
             pDummy_->config(getSplManuf()->createKurokoLeader(pDummy_->_pKurokoA), nullptr);
             pDummy_->_pKurokoA->setMvVelo(RV_MvVelo_);
             onCallUpAdelheid(pDummy_); //メンバー(Adelheid)のフォーメーション開始座標と方向を得る
             pDummy_->pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //座標計算のためスタート＆オプション指定が必要
             coord next_X, next_Y, next_Z;             //開始+1 の補完点座標
             coord end_X, end_Y, end_Z;                //最終の補完点座標
             coord end_prev_X, end_prev_Y, end_prev_Z; //最終-1 の補完点座標
             pDummy_->pKurokoLeader_->getPointCoord(1, next_X, next_Y, next_Z);//[0] or [1] を気をつけよ
             int spl_point_num = pDummy_->pKurokoLeader_->getPointNum(); //補完点の数
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-1, end_X, end_Y, end_Z);
             pDummy_->pKurokoLeader_->getPointCoord(spl_point_num-2, end_prev_X, end_prev_Y, end_prev_Z);
             //出現開始位置パリサナを配備
             pPalisana_start->positionAs(pDummy_);
             pPalisana_start->_pKurokoA->setFaceAngTwd(next_X, next_Y, next_Z); //向きセット
             pPalisana_start->acitve_open(); //ハッチオープン
             //終了位置にパリサナを配備
             pPalisana_goal->position(end_X, end_Y, end_Z);
             pPalisana_goal->_pKurokoA->setFaceAngTwd(end_prev_X, end_prev_Y, end_prev_Z);
             pPalisana_goal->acitve_open((frame)(pDummy_->pKurokoLeader_->getTotalDistance() / RV_MvVelo_)); //ハッチオープン予約

             pDummy_->sayonara(); //ありがとうダミー
             _pProg->changeNext();
             break;
         }
         //ハッチ出現＆オープン
         case PROG_ENTRY: {
             //開始ハッチが存在しているかどうか
             if (pPalisana_start) {
                 if (pPalisana_start->isOpenDone()) {
                     //ハッチオープン完了まで待つ
                     _pProg->changeNext(); //完了
                 }
             } else {
                 //開始ハッチがオープン前にやられた
                 callUpMember(0); //強制招集打ち切り
                 _pProg->changeNothing(); //本フォーメーション自体終了！
             }
             //ハッチオープン完了待ち
             break;
         }
         //ハッチから編隊メンバー出現
         case PROG_FROMATION_MOVE1: {
             if (pPalisana_start) {
                 //開始ハッチがオープンが存在中の場合
                 if (canCallUp()) {
                     //招集未完了時
                     if (_pProg->getFrameInProgress() % RV_IntervalFrames_ == 0) {
                         //機数 RV_NumFormation_ 機まで招集
                         EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(RV_NumFormation_);
                         if (pAdelheid) {
                             pAdelheid->config(getSplManuf()->createKurokoLeader(pAdelheid->_pKurokoA),
                                               pConn_ShotDepo_->peek() );
                             pAdelheid->_pKurokoA->forceMvVeloRange(RV_MvVelo_*2);
                             pAdelheid->_pKurokoA->setMvVelo(RV_MvVelo_);

                             pAdelheid->_pKurokoA->setMvAcce(0);
                             onCallUpAdelheid(pAdelheid); //下位フォーメーションクラス個別実装の処理
                         } else {
                             //招集おしまい
                         }
                     }
                 } else {
                     //招集限界時
                     pPalisana_start->close_sayonara();
                     _pProg->changeNext(); //出現終了！
                 }
             } else {
                 //開始ハッチが無い(無くなった)場合
                 callUpMember(0); //強制招集打ち切り（本フォーメションオブジェクトを解放させる条件として必要）
                 _pProg->changeNext(); //出現終了！
             }
             break;
         }

         //全メンバー減速
         case PROG_FROMATION_MOVE2: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationAdelheid::order1, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 120) {
                 _pProg->changeNext();
             }

             break;
         }

         //メンバー停滞&発射
         case PROG_FROMATION_MOVE3: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationAdelheid::order2, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 360) {
                 _pProg->changeNext(); //停滞終了！
             }
             break;
         }

         //メンバー再始動
         case PROG_FROMATION_MOVE4: {
             if (_pProg->isJustChanged()) {
                 _listFollower.executeFunc(FormationAdelheid::order3, this, nullptr);
             }
             if (_pProg->getFrameInProgress() == 120) {
                 _pProg->changeNext(); //再始動完了
             }
             break;
         }

         //待機
         case PROG_FROMATION_MOVE5: {
             if (_pProg->isJustChanged()) {
             }
             //onSayonaraAll() コールバック待ち
             break;
         }

//----------------------------------------------
         //編隊メンバー全機非活動時(onSayonaraAll()時)
         case PROG_LEAVE: {
             if (_pProg->isJustChanged()) {
                  if (pPalisana_goal) {
                      pPalisana_goal->close_sayonara();
                  }
             }
             break;
         }

         default:
             break;
     }
}

void FormationAdelheid::order1(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2) {
    //各メンバー減速
    EnemyAdelheid* pMember = (EnemyAdelheid*)prm_pAdelheid;
    FormationAdelheid* pFormation = (FormationAdelheid*)prm1;
    pMember->_pKurokoA->setMvAcceByT(120, -(pFormation->RV_MvVelo_/8));
}

void FormationAdelheid::order2(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2) {
    //各メンバー停滞&発射
    EnemyAdelheid* pMember = (EnemyAdelheid*)prm_pAdelheid;
    FormationAdelheid* pFormation = (FormationAdelheid*)prm1;
    pMember->_pKurokoA->setMvAcce(0);
    pMember->open_shot(); //ショット発射！
}

void FormationAdelheid::order3(GgafCore::GgafActor* prm_pAdelheid, void* prm1, void* prm2) {
    //各メンバー再始動
    EnemyAdelheid* pMember = (EnemyAdelheid*)prm_pAdelheid;
    FormationAdelheid* pFormation = (FormationAdelheid*)prm1;
    pMember->_pKurokoA->setMvAcceByT(120, pFormation->RV_MvVelo_);
}

void FormationAdelheid::onSayonaraAll() {
    //このコールバックが呼び出された時点で、余命は FORMATION_END_DELAY フレームのはず
    _TRACE_("FormationAdelheid::onSayonaraAll() です");
    _pProg->change(PROG_LEAVE);
    //解放を待つ
}

void FormationAdelheid::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationAdelheid::~FormationAdelheid() {
    pConn_ShotDepo_->close();
    pConn_AdelheidDepo_->close();
}

