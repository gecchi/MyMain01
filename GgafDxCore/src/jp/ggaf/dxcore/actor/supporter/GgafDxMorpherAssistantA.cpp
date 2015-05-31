#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpherAssistantA.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"


using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorpherAssistantA::GgafDxMorpherAssistantA(GgafDxMorpher* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    _target_num = prm_pMaster->_pActor->_pMorphMeshModel->_morph_target_num;

    _pa_smthMph = NEW GgafValueAccelerator<float>[_target_num+1];
    for (int i = 1; i <= _target_num; i++) {
        _pa_smthMph[i]._t_velo = _pMaster->_velo[i];
        _pa_smthMph[i]._t_acce = _pMaster->_acce[i];
    }
}

void GgafDxMorpherAssistantA::behave() {
    for (int i = 1; i <= _target_num; i++) {
        if (_pa_smthMph[i].isAccelerating()) {
            _pa_smthMph[i].behave();
            _pMaster->_velo[i] = _pa_smthMph[i]._t_velo - _pa_smthMph[i]._t_acce;
            _pMaster->_acce[i] = _pa_smthMph[i]._t_acce;
        }
    }
}

void GgafDxMorpherAssistantA::morphByDt(int prm_target_mesh_no,
                                        float prm_target_distance, int prm_target_frames,
                                        float prm_p1, float prm_p2, float prm_end_velo,
                                        bool prm_zero_acc_end_flg) {
    _pa_smthMph[prm_target_mesh_no]._t_value = 0;
    _pa_smthMph[prm_target_mesh_no]._t_velo = _pMaster->_velo[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no]._t_acce = _pMaster->_acce[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no].accelerateByDt(prm_target_distance, prm_target_frames,
                                                   prm_p1,prm_p2,prm_end_velo,
                                                   prm_zero_acc_end_flg);
}

void GgafDxMorpherAssistantA::morphByVd(int prm_target_mesh_no,
                                        float prm_top_velo, float prm_target_distance,
                                        float prm_p1, float prm_p2, float prm_end_velo,
                                        bool prm_zero_acc_end_flg) {
    _pa_smthMph[prm_target_mesh_no]._t_value = 0;
    _pa_smthMph[prm_target_mesh_no]._t_velo = _pMaster->_velo[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no]._t_acce = _pMaster->_acce[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no].accelerateByVd(prm_top_velo, prm_target_distance,
                                                   prm_p1,prm_p2,prm_end_velo,
                                                   prm_zero_acc_end_flg);
}

GgafDxMorpherAssistantA::~GgafDxMorpherAssistantA() {
    GGAF_DELETEARR(_pa_smthMph);
}
