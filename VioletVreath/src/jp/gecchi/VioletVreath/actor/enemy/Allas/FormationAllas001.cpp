#include "FormationAllas001.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/EnemyAllas.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001::FormationAllas001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAllas001";
    num_Allas_      = RF_FormationAllas001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationAllas001_LaunchInterval(G_RANK);  //アラスの間隔(frame)
    velo_mv_         = RF_FormationAllas001_MvVelo(G_RANK); //速度
    //アラス編隊作成
    pConn_pSplManuf_ = getConnection_SplineManufactureManager("Allas01");
    pConn_depo_ = nullptr;
    for (int i = 0; i < num_Allas_; i++) {
        EnemyAllas* pAllas= NEW EnemyAllas("Allas01");
        SplineKurokoLeader* pKurokoLeader = pConn_pSplManuf_->peek()->createKurokoLeader(pAllas->getKuroko());
        pAllas->config(pKurokoLeader, nullptr, nullptr);
        addFormationMember(pAllas);
    }
}

void FormationAllas001::initialize() {
}

void FormationAllas001::onActive() {
    for (int n = 0; canCallUp(); n++) {
        EnemyAllas* pAllas = (EnemyAllas*)callUpMember();
        if (pAllas) {
            onCallUpAllas(pAllas); //コールバック
            pAllas->activateDelay(n*interval_frames_ + 1); //活動予定フレーム上書き
            n++;
        }
    }
    //FormationTableScene に追加する編隊の場合、
    //編隊が途中でちょん切れる事を防ぐために、このように
    //onActive()内で、一気に全ての編隊要員を callUpMember() することにした。
}

void FormationAllas001::processBehavior() {
}

void FormationAllas001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

FormationAllas001::~FormationAllas001() {
    pConn_pSplManuf_->close();
    if (pConn_depo_) {
        pConn_depo_->close();
    }
}
