#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafTreeFormation::GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafTreeFormation";
}

void GgafTreeFormation::addSubLast(GgafActor* prm_pSub) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        throwGgafCriticalException("GgafTreeFormation::addSubLast("<<prm_pSub->getName()<<") 既に死にゆく定めのFormationです。サブに追加することはおかしいでしょう。this="<<getName());
    }
    _num_sub++;
    prm_pSub->_pFormation = this; //メンバーへフォーメーションを設定
//        _listFllower.addLast((GgafActor*)prm_pSub, false); //フォーメーションメンバーとして内部保持
    GgafActor::addSubLast(prm_pSub);
}


void GgafTreeFormation::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        if (getSubFirst() == NULL) {          //配下がない場合、フォーメーションはなかったことになり、自身を終了
            sayonara(_offset_frames_end);
        }
    }

}
void GgafTreeFormation::onGarbaged() {
    GgafActor::onGarbaged();
}


GgafTreeFormation::~GgafTreeFormation() {

}
