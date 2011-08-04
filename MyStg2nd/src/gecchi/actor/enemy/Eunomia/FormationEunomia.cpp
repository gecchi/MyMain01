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
    _num_formation_col = prm_col > 7 ? 7 : prm_col;   //Òàñ
    _num_formation_row = prm_row;  //PñÌÒà
    _interval_frames    = prm_interval_frames;   //GEm~AÌÔu(frame)
    _mv_velo           = prm_mv_velo; //¬x
    _n = 0;
    //GEm~AÒàì¬
    //XvCè`t@CðÇÝÞ
    _papSplineCon = NEW SplineConnection*[_num_formation_col];
    for (int i = 0; i < _num_formation_col; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //á"FormationEunomia001_0"
        _papSplineCon[i] = (SplineConnection*)(P_GOD->_pSplineManager->getConnection(spl_id.str().c_str())); //"FormationEunomia001_0.spl"
    }

    _papapEunomia = NEW EnemyEunomia**[_num_formation_col]; //nñxN@ÌÒàðgÞ
    SplineProgram* pSplinProg;
    for (int i = 0; i < _num_formation_col; i++) {
        _papapEunomia[i] = NEW EnemyEunomia*[_num_formation_row];
        for (int j = 0; j < _num_formation_row; j++) {
            _papapEunomia[i][j] = NEW EnemyEunomia("EUNOMIA");
            pSplinProg = _papSplineCon[i]->refer()->makeSplineProgram(_papapEunomia[i][j]);
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
            processOnActiveEunomia(_papapEunomia[i][_n], i); //ÂÊÀÌ
        }
        _n++;
    }
}

FormationEunomia::~FormationEunomia() {
    for (int i = 0; i < _num_formation_col; i++) {
        _papSplineCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplineCon);

    if (_pStoreCon) {
        _pStoreCon->close();
    }
    for (int i = 0; i < _num_formation_col; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapEunomia[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapEunomia);
}
