#include "stdafx.h"
#include "FormationPallas001.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/EnemyPallas.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001::FormationPallas001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationPallas001";
    num_Pallas_      = RF_FormationPallas001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationPallas001_LaunchInterval(G_RANK);  //パラスの間隔(frame)
    velo_mv_         = RF_FormationPallas001_MvVelo(G_RANK); //速度
    //パラス編隊作成
    pSplManufConnection_ = connectToSplineManufactureManager("Pallas01");
    pDepoConnection_ = nullptr;
    for (int i = 0; i < num_Pallas_; i++) {
        EnemyPallas* pPallas= NEW EnemyPallas("Pallas01");
        SplineKurokoLeader* pKurokoLeader = pSplManufConnection_->peek()->createKurokoLeader(pPallas->_pKurokoA);
        pPallas->config(pKurokoLeader, nullptr, nullptr);
        addFormationMember(pPallas);
    }
}

void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    for (int n = 0; canCallUp(); n++) {
        EnemyPallas* pPallas = (EnemyPallas*)callUpMember();
        if (pPallas) {
            onCallUpPallas(pPallas); //コールバック
            pPallas->activateDelay(n*interval_frames_ + 1); //活動予定フレーム上書き
            n++;
        }
    }
    //FormationTableScene に追加する編隊の場合、
    //編隊が途中でちょん切れる事を防ぐために、このように
    //onActive()内で、一気に全ての編隊要員を callUpMember() することにした。
}

void FormationPallas001::processBehavior() {
}

void FormationPallas001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationPallas001::~FormationPallas001() {
    pSplManufConnection_->close();
    if (pDepoConnection_) {
        pDepoConnection_->close();
    }
}
