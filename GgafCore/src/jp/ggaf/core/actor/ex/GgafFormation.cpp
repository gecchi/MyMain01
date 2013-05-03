#include "stdafx.h"
using namespace GgafCore;

GgafFormation::GgafFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafMainActor(prm_name, nullptr)
{
    _obj_class |= Obj_GgafFormation;
    _class_name = "GgafFormation";
    _offset_frames_end = prm_offset_frames_end > 0 ? prm_offset_frames_end : 1;
    _num_formation_member = 0;
    setHitAble(false);
    _num_destory = 0;
    _was_all_destroyed = false;
    _was_all_sayonara = false;
}

void GgafFormation::destroyedFollower(GgafActor* prm_pActor_destroyed) {
    _num_destory++;
    if (_num_formation_member == _num_destory) {
        _was_all_destroyed = true;
        onDestroyAll(prm_pActor_destroyed);
    }
}
void GgafFormation::onEnd() {
    GgafActor::onEnd();
}


GgafFormation::~GgafFormation() {

}
