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
    _papSplManufCon = NEW SplineManufactureConnection*[_num_formation_col];
    for (int i = 0; i < _num_formation_col; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //á"FormationEunomia001_0"
        _papSplManufCon[i] = connectSplineManufactureManager(spl_id.str().c_str());
    }

    _papapEunomia = NEW EnemyEunomia**[_num_formation_col]; //nñxN@ÌÒàðgÞ
    for (int i = 0; i < _num_formation_col; i++) {
        _papapEunomia[i] = NEW EnemyEunomia*[_num_formation_row];
        for (int j = 0; j < _num_formation_row; j++) {
            stringstream nm;
            nm << "EUNOMIA_col" << i << "_row" << j;
            _papapEunomia[i][j] = NEW EnemyEunomia(nm.str().c_str());
            SplineSequence* pSplSeq = _papSplManufCon[i]->use()->
                                            createSplineSequence(_papapEunomia[i][j]->_pKurokoA);
            _papapEunomia[i][j]->config(pSplSeq, NULL, NULL);
            _papapEunomia[i][j]->inactivateImmediately();
            addSubLast(_papapEunomia[i][j]);
        }
    }
    _pDepoCon = NULL;
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
        _papSplManufCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplManufCon);

    if (_pDepoCon) {
        _pDepoCon->close();
    }
    for (int i = 0; i < _num_formation_col; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapEunomia[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapEunomia);
}
