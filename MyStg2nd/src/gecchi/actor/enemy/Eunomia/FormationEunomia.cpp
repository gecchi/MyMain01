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
                                                         const char* prm_spl_id) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationEunomia";
    _num_formation_col = prm_col > 7 ? 7 : prm_col;   //編隊列数
    _num_formation_row = prm_row;  //１列の編隊数
    _interval_frames    = prm_interval_frames;   //エウノミアの間隔(frame)
    _mv_velo           = prm_mv_velo; //速度
    _n = 0;

    //エウノミア編隊作成
    //スプライン定義ファイルを読み込む
    _papSplineManufactureCon = NEW SplineManufactureConnection*[_num_formation_col];
    for (int i = 0; i < _num_formation_col; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationEunomia001_0"
        _papSplineManufactureCon[i] = (SplineManufactureConnection*)((P_GOD)->_pSplineManufactureManager->getConnection(spl_id.str().c_str()));
    }


    _papapEunomia = NEW EnemyEunomia**[_num_formation_col]; //n列xN機の編隊を組む
    SplineProgram* pSplinProg;
    for (int i = 0; i < _num_formation_col; i++) {
        _papapEunomia[i] = NEW EnemyEunomia*[_num_formation_row];
        for (int j = 0; j < _num_formation_row; j++) {
            stringstream nm;
            nm << "EUNOMIA_col" << i << "_row" << j;
            _papapEunomia[i][j] = NEW EnemyEunomia(nm.str().c_str());
            pSplinProg = _papSplineManufactureCon[i]->refer()->createSplineProgram(_papapEunomia[i][j]);
            _papapEunomia[i][j]->config(pSplinProg, NULL, NULL);
            _papapEunomia[i][j]->inactivateImmediately();
            addSubLast(_papapEunomia[i][j]);
        }
    }
    _pStoreCon = NULL;
}
void FormationEunomia::initialize() {
    _n = 0;
}


void FormationEunomia::processBehavior() {
    if (_n < _num_formation_row && getActivePartFrame() % _interval_frames == 0) {
        for (int i = 0; i < _num_formation_col; i++) {
            _papapEunomia[i][_n]->activate();
            processOnActiveEunomia(_papapEunomia[i][_n], i); //個別実装の処理
        }
        _n++;
    }
}

FormationEunomia::~FormationEunomia() {
    for (int i = 0; i < _num_formation_col; i++) {
        _papSplineManufactureCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplineManufactureCon);

    if (_pStoreCon) {
        _pStoreCon->close();
    }
    for (int i = 0; i < _num_formation_col; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapEunomia[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapEunomia);
}
