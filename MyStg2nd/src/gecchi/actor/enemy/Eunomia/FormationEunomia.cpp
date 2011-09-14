#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia::FormationEunomia(const char* prm_name, int prm_col,
                                                         int prm_row,
                                                         frame prm_interval_frames,
                                                         velo prm_mv_velo,
                                                         const char* prm_spl_id) : FormationActor(prm_name, 20*60) {
    _class_name = "FormationEunomia";
    _num_formation_col = prm_col > 7 ? 7 : prm_col;   //編隊列数
    _num_formation_row = prm_row;  //１列の編隊数
    _interval_frames    = prm_interval_frames;   //エウノミアの間隔(frame)
    _mv_velo           = prm_mv_velo; //速度
    _n = 0;

    //エウノミア編隊作成
    _pDepoCon_Eunomia = connectDepositoryManager("DpCon_EnemyEunomia4Formation", this);
    setActorDepository(_pDepoCon_Eunomia->use());


    //スプライン定義ファイルを読み込む
    _papSplManufCon = NEW SplineManufactureConnection*[_num_formation_col];
    for (int i = 0; i < _num_formation_col; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationEunomia001_0"
        _papSplManufCon[i] = connectSplineManufactureManager(spl_id.str().c_str());
    }

//    _papapEunomia = NEW EnemyEunomia**[_num_formation_col]; //n列xN機の編隊を組む
//    for (int i = 0; i < _num_formation_col; i++) {
//        _papapEunomia[i] = NEW EnemyEunomia*[_num_formation_row];
//        for (int j = 0; j < _num_formation_row; j++) {
//            stringstream nm;
//            nm << "EUNOMIA_col" << i << "_row" << j;
//            _papapEunomia[i][j] = NEW EnemyEunomia(nm.str().c_str());
//            SplineSequence* pSplSeq = _papSplManufCon[i]->use()->
//                                            createSplineSequence(_papapEunomia[i][j]->_pKurokoA);
//            _papapEunomia[i][j]->config(this, pSplSeq, NULL, NULL);
//            _papapEunomia[i][j]->inactivateImmediately();
//            addSubLast(_papapEunomia[i][j]);
//        }
//    }
    _pDepoCon_shot = NULL;
}

void FormationEunomia::initialize() {
    _n = 0;
}


void FormationEunomia::processBehavior() {
    if (_n < _num_formation_row && getActivePartFrame() % _interval_frames == 0) {
        for (int i = 0; i < _num_formation_col; i++) {
            EnemyEunomia* e = (EnemyEunomia*)callUp();
            if (e) {
                SplineSequence* pSplSeq = _papSplManufCon[i]->use()->
                                              createSplineSequence(e->_pKurokoA);
                e->config(this, pSplSeq, NULL, NULL);
    //            _papapEunomia[i][_n]->activate();
                processOnActiveEunomia(e, i); //個別実装の処理
            }
        }
        _n++;
    }
}

FormationEunomia::~FormationEunomia() {
    _pDepoCon_Eunomia->close();

    for (int i = 0; i < _num_formation_col; i++) {
        _papSplManufCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplManufCon);

    if (_pDepoCon_shot) {
        _pDepoCon_shot->close();
    }
//    for (int i = 0; i < _num_formation_col; i++) {
//        DELETEARR_IMPOSSIBLE_NULL(_papapEunomia[i]);
//    }
//    DELETEARR_IMPOSSIBLE_NULL(_papapEunomia);
}
