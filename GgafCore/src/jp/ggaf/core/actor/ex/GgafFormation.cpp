#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafFormation::GgafFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafMainActor(prm_name, NULL)
{
    _obj_class |= Obj_GgafFormation;
    _class_name = "GgafFormation";
    _offset_frames_end = prm_offset_frames_end;
    _num_sub = 0;
    setHitAble(false);
    _is_init = false;
    _num_destory = 0;
    _was_all_destroyed = false;
}

void GgafFormation::destroyedFollower(GgafActor* prm_pActor_Destroyed) {
    _num_destory++;
    if (_num_sub == _num_destory) {
        _was_all_destroyed = true;
        onDestroyedAll(prm_pActor_Destroyed);
    }
}
void GgafFormation::onEnded() {
    GgafActor::onEnded();
}


GgafFormation::~GgafFormation() {

}
