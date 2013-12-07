#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpherAsstA.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/util/GgafDxAccelerator.hpp"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"


using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorpherAsstA::GgafDxMorpherAsstA(GgafDxMorpher* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    _target_num = prm_pMaster->_pActor->_pMorphMeshModel->_morph_target_num;

    _pa_smthMph = NEW GgafDxAccelerator<float>[_target_num+1];
    for (int i = 1; i <= _target_num; i++) {
        _pa_smthMph[i]._velo = _pMaster->_velo_weight[i];
        _pa_smthMph[i]._acce = _pMaster->_acce_weight[i];
    }
}

void GgafDxMorpherAsstA::behave() {
    for (int i = 1; i <= _target_num; i++) {
        bool flg = _pa_smthMph[i]._prm._flg;
        _pa_smthMph[i].behave();
        if (flg) {
            _pMaster->_velo_weight[i] = _pa_smthMph[i]._velo - _pa_smthMph[i]._acce;
            _pMaster->_acce_weight[i] = _pa_smthMph[i]._acce;
        }
    }
}

void GgafDxMorpherAsstA::morphByDt(int prm_target_mesh_no,
                                      float prm_target_distance, int prm_target_frames,
                                      float prm_p1, float prm_p2, float prm_end_velo,
                                      bool prm_endacc_flg) {
    _pa_smthMph[prm_target_mesh_no]._value = 0;
    _pa_smthMph[prm_target_mesh_no]._velo = _pMaster->_velo_weight[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no]._acce = _pMaster->_acce_weight[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no].accelerateByDt(prm_target_distance, prm_target_frames,
                                                   prm_p1,prm_p2,prm_end_velo,
                                                   prm_endacc_flg);
}

void GgafDxMorpherAsstA::morphByVd(int prm_target_mesh_no,
                                      float prm_top_velo, float prm_target_distance,
                                      float prm_p1, float prm_p2, float prm_end_velo,
                                      bool prm_endacc_flg) {
    _pa_smthMph[prm_target_mesh_no]._value = 0;
    _pa_smthMph[prm_target_mesh_no]._velo = _pMaster->_velo_weight[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no]._acce = _pMaster->_acce_weight[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no].accelerateByVd(prm_top_velo, prm_target_distance,
                                                   prm_p1,prm_p2,prm_end_velo,
                                                   prm_endacc_flg);
}

GgafDxMorpherAsstA::~GgafDxMorpherAsstA() {
    GGAF_DELETEARR(_pa_smthMph);
}


