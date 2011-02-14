#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia::FormationEunomia(const char* prm_name, int prm_col,
                                                         int prm_row,
                                                         frame prm_frame_interval,
                                                         velo prm_mv_velo,
                                                         const char* prm_spl_id) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationEunomia";
    _num_formation_col = prm_col;   //編隊列数
    _num_formation_row = prm_row;  //１列の編隊数
    _frame_interval    = prm_frame_interval;   //エウノミアの間隔(frame)
    _mv_velo           = prm_mv_velo; //速度
    _n = 0;
    //エウノミア編隊作成
    //スプライン定義ファイルを読み込む
    _papSplineCon = NEW SplineConnection*[_num_formation_col];
    for (int i = 0; i < _num_formation_col; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationEunomia001_0"
        _papSplineCon[i] = (SplineConnection*)(P_GOD->_pSplineManager->getConnection(spl_id.str().c_str()));
    }

    _papapEunomia = NEW EnemyEunomia**[_num_formation_col]; //n列xN機の編隊を組む
    for (int i = 0; i < _num_formation_col; i++) {
        _papapEunomia[i] = NEW EnemyEunomia*[_num_formation_row];
        for (int j = 0; j < _num_formation_row; j++) {
            _papapEunomia[i][j] = NEW EnemyEunomia("EUNOMIA");
            _papapEunomia[i][j]->config(_papSplineCon[i]->refer()->makeSplineProgram(_papapEunomia[i][j]), NULL, NULL);
            _papapEunomia[i][j]->inactivateImmediately();
            addSubLast(_papapEunomia[i][j]);
        }
    }
    _pDispatcherCon = NULL;
}
void FormationEunomia::initialize() {
    _n = 0;
}


void FormationEunomia::processBehavior() {
    if (_n < _num_formation_row && getActivePartFrame() % _frame_interval == 0) {
        for (int i = 0; i < _num_formation_col; i++) {
            _papapEunomia[i][_n]->activate();
            processOnActiveEunomia(_papapEunomia[i][_n], i); //個別実装の処理
        }
        _n++;
    }
}

FormationEunomia::~FormationEunomia() {
    for (int i = 0; i < _num_formation_col; i++) {
        _papSplineCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplineCon);

    if (_pDispatcherCon) {
        _pDispatcherCon->close();
    }
    for (int i = 0; i < _num_formation_col; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapEunomia[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapEunomia);
}
