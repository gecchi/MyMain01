#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafTreeFormation::GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafTreeFormation";
}

void GgafTreeFormation::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        throwGgafCriticalException("GgafTreeFormation::addSubLast("<<prm_pSub->getName()<<") 既に死にゆく定めのFormationです。サブに追加することはおかしいでしょう。this="<<getName());
    }
#endif
    _num_sub++;
    if (_pSubFirst == NULL) {
        //団長に種別を正しく伝えるために種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafTreeFormation::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pFormation = this; //メンバーへフォーメーションを設定
//        _listFllower.addLast((GgafActor*)prm_pSub, false); //フォーメーションメンバーとして内部保持
    GgafFormation::addSubLast(prm_pSub);
}


void GgafTreeFormation::processFinal() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        if (getSubFirst() == NULL) {          //配下がない場合、フォーメーションはなかったことになり、自身を終了
            sayonara(_offset_frames_end);
        }
    }

}
void GgafTreeFormation::onEnded() {
    GgafFormation::onEnded();
}


GgafTreeFormation::~GgafTreeFormation() {

}
