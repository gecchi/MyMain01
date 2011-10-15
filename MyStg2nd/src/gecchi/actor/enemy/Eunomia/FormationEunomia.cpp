#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEunomia";
    _num_formation_col = 7;   //編隊列数
    _num_formation_row = 1;  //１列の編隊数
    _interval_frames   = R_FormationEunomia001_LaunchInterval;  //エウノミアの間隔(frame)
    _mv_velo           = 10; //速度
    _n = 0;

    //エウノミア編隊作成
    _pDepoCon_Eunomia = connectDepositoryManager("DpCon_EnemyEunomia4Formation", this);
    setFormationAbleActorDepository(_pDepoCon_Eunomia->use());


    //スプライン定義ファイルを読み込む
    _papSplManufCon = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationEunomia001_0"
        _papSplManufCon[i] = connectSplineManufactureManager(spl_id.str().c_str());
    }
    _pDepoCon_shot = NULL;
}

void FormationEunomia::initialize() {
    _n = 0;
}


void FormationEunomia::processBehavior() {

    if (_n < _num_formation_row && getActivePartFrame() % _interval_frames == 0) {
        _num_formation_col = R_FormationEunomia001_Col;   //編隊列数
        _num_formation_row = R_FormationEunomia001_Num;  //１列の編隊数
        _interval_frames   = R_FormationEunomia001_LaunchInterval;   //エウノミアの間隔(frame)
        _mv_velo           = R_FormationEunomia001_MvVelo; //速度
        for (int i = 0; i < _num_formation_col; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUpUntil(_num_formation_col*_num_formation_row);
            if (pEunomia) {
                SplineSequence* pSplSeq = _papSplManufCon[i]->use()->
                                              createSplineSequence(pEunomia->_pKurokoA);
                pEunomia->config(pSplSeq, NULL, NULL);
                pEunomia->_pKurokoA->setMvVelo(_mv_velo);
    //            _papapEunomia[i][_n]->activate();
                processOnActiveEunomia(pEunomia, i); //フォーメーション個別実装の処理
            }
        }
        _n++;
    }
}

FormationEunomia::~FormationEunomia() {
    _pDepoCon_Eunomia->close();

    for (int i = 0; i < 7; i++) {
        _papSplManufCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplManufCon);

    if (_pDepoCon_shot) {
        _pDepoCon_shot->close();
    }
}
