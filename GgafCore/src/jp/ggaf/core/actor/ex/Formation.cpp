#include "jp/ggaf/core/actor/ex/Formation.h"

using namespace GgafCore;

Formation::Formation(const char* prm_name, frame prm_offset_frames_end) :
        MainActor(prm_name)
{
    _obj_class |= Obj_ggaf_Formation;
    _class_name = "Formation";
    _offset_frames_end = prm_offset_frames_end > 0 ? prm_offset_frames_end : 1;
    _num_formation_member = 0;
    setHitAble(false);
    _num_destory = 0;
    _num_summon = 0;
    _was_all_destroyed = false;
    _was_all_sayonara = false;
    _can_summon = true;
    _pLastDestroyedActor = nullptr;
}

void Formation::onDestroyMember(Actor* prm_pActor_destroyed) {
    _num_destory++;
    _pLastDestroyedActor = prm_pActor_destroyed;
    if (_num_formation_member == _num_destory) {
        _was_all_destroyed = true;
        onDestroyAll(prm_pActor_destroyed);
    }
}
void Formation::onEnd() {
    Actor::onEnd();
}


Formation::~Formation() {

}
