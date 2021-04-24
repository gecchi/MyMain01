#include "FormationDelheid.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Alisana/EnemyAlisana.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/EnemyDelheid.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_ENTRY ,
    PROG_FROMATION_MOVE1,
    PROG_FROMATION_MOVE2,
    PROG_FROMATION_MOVE3,
    PROG_FROMATION_MOVE4,
    PROG_FROMATION_MOVE5,
    PROG_LEAVE ,
    PROG_BANPEI,
};

FormationDelheid::FormationDelheid(const char* prm_name)
   : DepositoryFormation(prm_name) {
    _class_name = "FormationDelheid";

    pAlisana_start = NEW EnemyAlisana("Alisana_START");
    pAlisana_start->inactivate(); //生成直後は非活動なので、これで onInactive() は発生しません。
    appendGroupChild(pAlisana_start);

    pAlisana_goal = NEW EnemyAlisana("Alisana_GOAL");
    pAlisana_goal->inactivate();
    appendGroupChild(pAlisana_goal);

    //軌道計算用のダミー
    pDummy_ = NEW EnemyDelheid("DammyEnemyDelheid");
    pDummy_->pDriverLeader_ = nullptr;
    pDummy_->inactivate();
    appendGroupChild(pDummy_);

    //編隊隊員デポジトリセット
    pConn_pDelheidDepo_ = connectToDepositoryManager("EnemyDelheid4Formation");
    setFormationMember(pConn_pDelheidDepo_->peek());
    //編隊隊員のショットデポジトリ
    pConn_pShotDepo_ = connectToDepositoryManager("EnemyDelheidShot");

    updateRankParameter();
}

void FormationDelheid::updateRankParameter() {
    RV_Num_           = RF_FormationDelheid_Num(G_RANK);    //編隊数
    RV_MvVelo_        = RF_FormationDelheid_MvVelo(G_RANK); //速度
    RV_LaunchInterval = 64 / C_PX(RV_MvVelo_);
}

void FormationDelheid::initialize() {

}

void FormationDelheid::onActive() {
    updateRankParameter();
    getProgress()->reset(PROG_INIT);
}

void FormationDelheid::processBehavior() {
    //pAlisana_start が破壊されているかチェック
    if (pAlisana_start) {
        if (pAlisana_start->hasJustChangedToInactive()) {
            pAlisana_start = nullptr;
        }
    }
    //pAlisana_goal が破壊されているかチェック
    if (pAlisana_goal) {
        if (pAlisana_goal->hasJustChangedToInactive()) {
            pAlisana_goal = nullptr;
        }
    }
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             updateRankParameter();
             //ダミー(pDummy_)を使ってメンバーのスプライン移動の開始位置と方向、終了位置と方向を予め求める
             pDummy_->config(getSplManuf()->createVecDriverLeader(pDummy_->getVecDriver()), nullptr);
             pDummy_->getVecDriver()->setMvVelo(RV_MvVelo_);
             pDummy_->setPositionAt(&geoLocate_);
             pDummy_->setFaceAngAs(&geoLocate_);
             pDummy_->getVecDriver()->setRzRyMvAng(geoLocate_.rz, geoLocate_.ry);
             onCallUpDelheid(pDummy_);
             pDummy_->pDriverLeader_->start(RELATIVE_COORD_DIRECTION); //座標計算のためスタート＆オプション指定が必要
             coord next_x, next_y, next_z;             //開始+1 の補完点座標
             coord end_x, end_y, end_z;                //最終の補完点座標
             coord end_prev_x, end_prev_y, end_prev_z; //最終-1 の補完点座標
             pDummy_->pDriverLeader_->getPointCoord(1, next_x, next_y, next_z);//[0] or [1] を気をつけよ
             int ldr_point_num = pDummy_->pDriverLeader_->getPointNum(); //補完点の数
             pDummy_->pDriverLeader_->getPointCoord(ldr_point_num-1, end_x, end_y, end_z);
             pDummy_->pDriverLeader_->getPointCoord(ldr_point_num-2, end_prev_x, end_prev_y, end_prev_z);
             //出現開始位置アリサナを配備
             pAlisana_start->setPositionAt(pDummy_);
             pAlisana_start->setFaceAngTwd(next_x, next_y, next_z); //向きセット
             pAlisana_start->acitve_open(); //ハッチオープン
             //終了位置にアリサナを配備
             pAlisana_goal->setPosition(end_x, end_y, end_z);
             pAlisana_goal->setFaceAngTwd(end_prev_x, end_prev_y, end_prev_z);
             pAlisana_goal->acitve_open((frame)(pDummy_->pDriverLeader_->getTotalDistance() / RV_MvVelo_)); //ハッチオープン予約

             pDummy_->sayonara(); //ありがとうダミー
             pProg->changeNext();
             break;
         }
         //ハッチ出現＆オープン
         case PROG_ENTRY: {
             //開始ハッチが存在しているかどうか
             if (pAlisana_start) {
                 if (pAlisana_start->isOpenDone()) {
                     //ハッチオープン完了まで待つ
                     pProg->changeNext(); //完了
                 }
             } else {
                 //開始ハッチがオープン前にやられた
                 callUpMember(0); //強制招集打ち切り
                 pProg->changeNothing(); //本フォーメーション自体終了！
             }
             //ハッチオープン完了待ち
             break;
         }
         //ハッチから編隊メンバー出現
         case PROG_FROMATION_MOVE1: {
             if (pAlisana_start) {
                 //開始ハッチがオープンが存在中の場合
                 if (canCallUp()) {
                     //招集未完了時
                     if (pProg->getFrame() % RV_LaunchInterval == 0) {
                         //機数 RV_Num_ 機まで招集
                         EnemyDelheid* pDelheid = (EnemyDelheid*)callUpMember(RV_Num_);
                         if (pDelheid) {
                             pDelheid->config(getSplManuf()->createVecDriverLeader(pDelheid->getVecDriver()),
                                              pConn_pShotDepo_->peek() );
                             pDelheid->getVecDriver()->forceMvVeloRange(RV_MvVelo_*2);
                             pDelheid->getVecDriver()->setMvVelo(RV_MvVelo_);

                             pDelheid->getVecDriver()->setMvAcce(0);
                             pDelheid->setPositionAt(&geoLocate_);
                             pDelheid->setFaceAngAs(&geoLocate_);
                             pDelheid->getVecDriver()->setRzRyMvAng(geoLocate_.rz, geoLocate_.ry);
                             pDelheid->pDriverLeader_->setStartAngle(geoLocate_.rx, geoLocate_.ry, geoLocate_.rz);
//                             pDelheid->pDriverLeader_->setLoopAngleByMvAng();
                             onCallUpDelheid(pDelheid); //下位フォーメーションクラス個別実装の処理
                         } else {
                             //招集おしまい
                         }
                     }
                 } else {
                     //招集限界時
                     pAlisana_start->close_sayonara();
                     pProg->changeNext(); //出現終了！
                 }
             } else {
                 //開始ハッチが無い(無くなった)場合
                 callUpMember(0); //強制招集打ち切り（本フォーメションオブジェクトを解放させる条件として必要）
                 pProg->changeNext(); //出現終了！
             }
             break;
         }

         //全メンバー減速
         case PROG_FROMATION_MOVE2: {
             if (pProg->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order1, this, nullptr, nullptr);
             }
             if (pProg->hasArrivedAt(120)) {
                 pProg->changeNext();
             }

             break;
         }

         //メンバー停滞&発射
         case PROG_FROMATION_MOVE3: {
             if (pProg->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order2, this, nullptr, nullptr);
             }
             if (pProg->hasArrivedAt(360)) {
                 pProg->changeNext(); //停滞終了！
             }
             break;
         }

         //メンバー再始動
         case PROG_FROMATION_MOVE4: {
             if (pProg->hasJustChanged()) {
                 _listFollower.executeFunc(FormationDelheid::order3, this, nullptr, nullptr);
             }
             if (pProg->hasArrivedAt(120)) {
                 pProg->changeNext(); //再始動完了
             }
             break;
         }

         //待機
         case PROG_FROMATION_MOVE5: {
             if (pProg->hasJustChanged()) {
             }
             //onSayonaraAll() コールバック待ち
             break;
         }

//----------------------------------------------
         //編隊メンバー全機非活動時(onSayonaraAll()時)
         case PROG_LEAVE: {
             if (pProg->hasJustChanged()) {
                  if (pAlisana_goal) {
                      pAlisana_goal->close_sayonara();
                  }
             }
             break;
         }

         default: {
             break;
         }
     }
}

void FormationDelheid::order1(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //各メンバー減速
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecDriver()->setMvAcceByT(120, -(pFormation->RV_MvVelo_/8));
}

void FormationDelheid::order2(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //各メンバー停滞&発射
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecDriver()->setMvAcce(0);
    pMember->open_shot(); //ショット発射！
}

void FormationDelheid::order3(GgafCore::Actor* prm_pDelheid, void* prm1, void* prm2, void* prm3) {
    //各メンバー再始動
    EnemyDelheid* pMember = (EnemyDelheid*)prm_pDelheid;
    FormationDelheid* pFormation = (FormationDelheid*)prm1;
    pMember->getVecDriver()->setMvAcceByT(120, pFormation->RV_MvVelo_);
}

void FormationDelheid::onSayonaraAll() {
    //このコールバックが呼び出された時点で、余命は FORMATION_END_DELAY フレームのはず
    _TRACE_(FUNC_NAME<<" です");
    getProgress()->change(PROG_LEAVE);
    //解放を待つ
}

void FormationDelheid::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationDelheid::~FormationDelheid() {
    pConn_pShotDepo_->close();
    pConn_pDelheidDepo_->close();
}

