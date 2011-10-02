#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FormationActor::FormationActor(const char* prm_name, frame prm_offset_frames_end) :
    GgafDxGeometricActor(prm_name, NULL, NULL)
{
    _obj_class |= Obj_FormationActor;
    _class_name = "FormationActor";
    _offset_frames_end = prm_offset_frames_end;
    _num_sub = 0;
    setHitAble(false);
    _is_init = false;
    _pDepo = NULL;
    _num_destory = 0;
//    _num_inactive = 0;
    _is_called_up = false;
    _was_all_destroyed = false;
}
void FormationActor::setActorDepository(GgafActorDepository* prm_pDepo) {
    _pDepo = prm_pDepo;
}

void FormationActor::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        throwGgafCriticalException("FormationActor::addSubLast("<<prm_pSub->getName()<<") 既に死にゆく定めのFormationです。サブに追加することはおかしいでしょう。this="<<getName());
    }
    if (_pDepo) {
        _TRACE_("＜警告＞ FormationActor::addSubLast("<<prm_pSub->getName()<<") Depository指定モード時に addSubLast すると全滅判定は出来ません。意図的ですか？callUp()は不要ですか？ this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    if (_pSubFirst == NULL) {
        //種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));

    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("FormationActor::addSubLast 異なる種別のアクターを登録しようとしています。this="<<getName()<<"("<<this<<") \n"<<
                                       "想定kind="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" _pSubFirst="<<_pSubFirst->getName()<<" \n"<<
                                       "引数kind="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" prm_pSub="<<prm_pSub->getName()<<"("<<prm_pSub<<")");
        }
    }
    if (prm_pSub->_obj_class & Obj_GgafDxGeometricActor) {
        _num_sub++;
        IFormationAble* p = dynamic_cast<IFormationAble*>(prm_pSub);
#ifdef MY_DEBUG
        if (p == NULL) {
            throwGgafCriticalException("FormationActor::addSubLast IFormationAble*へクロスキャスト失敗。prm_pSub="<<prm_pSub->getName()<<" のクラスから IFormationAble が見えません。public 継承して下さい。 this="<<getName()<<" _num_sub="<<_num_sub);
        }
#endif
        p->_pFormation = this;
        _listFllower.addLast((GgafMainActor*)prm_pSub, false);
    } else {
        _TRACE_("＜警告＞ FormationActor::addSubLast("<<prm_pSub->getName()<<") Obj_GgafDxGeometricActor 以外のアクターが追加されます。FormationActor使用意図は正しいですか？。this="<<getName()<<" _num_sub="<<_num_sub);
    }
    GgafDxGeometricActor::addSubLast(prm_pSub);
}

GgafDxGeometricActor* FormationActor::callUp() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("FormationActor::callUp "<<getName()<<"は、Depositoryが指定されてません。setActorDepositoryが必要です。this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    GgafMainActor* pActor = _pDepo->dispatch();
    if (pActor) {
#ifdef MY_DEBUG
        if (pActor->_obj_class & Obj_GgafDxGeometricActor) {
            //OK
        } else {
            throwGgafCriticalException("FormationActor::callUp() Obj_GgafDxGeometricActor 以外のアクターが取り出されました。this="<<getName()<<" pActor="<<pActor->getName()<<" _num_sub="<<_num_sub);
        }
#endif
        _num_sub++;
        IFormationAble* p = dynamic_cast<IFormationAble*>(pActor);
#ifdef MY_DEBUG
        if (p == NULL) {
            throwGgafCriticalException("FormationActor::callUp() IFormationAble*へクロスキャスト失敗。pActor="<<pActor->getName()<<" のクラスから IFormationAble が見えません。public 継承して下さい。 this="<<getName()<<" _num_sub="<<_num_sub);
        }
#endif
		p->_pFormation = this;
        _listFllower.addLast(pActor, false);
    }
    _is_called_up = true;
    return (GgafDxGeometricActor*)pActor;
}

void FormationActor::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        if (_pDepo) {
//            _TRACE_("FormationActor::processJudgement() this="<<getName()<<" _is_called_up="<<_is_called_up<<" _num_sub="<<_num_sub<<" _num_inactive="<<_num_inactive);
            if (_is_called_up && _num_sub == 0) { //デポジトリモード時、いきなり借りれない場合、フォーメーションはなかったことになり、自身を終了
//                _TRACE_("FormationActor::processJudgement()  this="<<getName()<<" sayonara("<<_offset_frames_end<<");");
                sayonara(_offset_frames_end);
            }
        } else {
            if (getSubFirst() == NULL) {          //配下がない場合、フォーメーションはなかったことになり、自身を終了
                sayonara(_offset_frames_end);
            }
        }
    }

    if (_listFllower.length() == 0) {
        if (_num_sub > 0) {
            sayonara(_offset_frames_end);
        } else {
            return;
        }
    } else {
        GgafMainActor* pFllower = _listFllower.getCurrent();
        int num_follwer = _listFllower.length();
        for (int i = 0; i < num_follwer; i++) {
            if (pFllower->_can_live_flg && (pFllower->_is_active_flg || pFllower->_will_activate_after_flg)) {
                pFllower = _listFllower.next();
            } else {
                _TRACE_("FormationActor::sayonaraFollwer _listFllowerの"<<_listFllower.getCurrent()->getName()<<"をsayonaraします。");
                _listFllower.remove();
            }
        }
    }


}
void FormationActor::onGarbaged() {
    sayonaraFollwer();
}

//void FormationActor::wasDestroyedFollower(GgafDxGeometricActor* prm_pActor) {
//    _num_destory++;
//    if (_num_sub == _num_destory) {
//        _was_all_destroyed = true;
//        onDestroyedFormation(prm_pActor);
//    }
//}

//void FormationActor::wasInactiveFollower(GgafDxGeometricActor* prm_pActor) {
////    _TRACE_("FormationActor::wasInactiveFollower() this="<<getName()<<" _num_sub="<<_num_sub<<" _num_inactive="<<_num_inactive);
//    int idx = _listFllower.indexOf(prm_pActor);
//    if (idx >= 0) {
//        _listFllower.current(idx);
//        _listFllower.remove();
//    } else {
//#ifdef MY_DEBUG
//        throwGgafCriticalException("FormationActor::wasInactiveFollower prm_pActor="<<prm_pActor<<" を所属させた覚えはありません\n"<<
//                                   "this="<<getName()<<" _num_sub="<<_num_sub<<" _num_inactive="<<_num_inactive);
//#endif
//    }
//    if (_pDepo) {
//        _num_inactive++;
//        if (_num_sub == _num_inactive) {
//            sayonara(_offset_frames_end);
//        }
////        _TRACE_("FormationActor::wasInactiveFollower() this="<<getName()<<" _num_sub="<<_num_sub<<" _num_inactive++ _num_inactive="<<_num_inactive);
//    }
//}
void FormationActor::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
#ifdef MY_DEBUG
    if (_pDepo) {
        _TRACE_("FormationActor::sayonaraFollwer 所属を残したまま、FormationActor の方が先に消されています。wasInactiveFollower() コール漏れはありませんか？ "<<
                "this="<<getName()<<" _num_sub="<<_num_sub<<" _listFllower.length()="<<_listFllower.length());
    }
#endif
    while (_listFllower.length() > 0) {

        IFormationAble* p = dynamic_cast<IFormationAble*>(_listFllower.getCurrent());
#ifdef MY_DEBUG
        if (p == NULL) {
            throwGgafCriticalException("FormationActor::sayonaraFollwer IFormationAble*へクロスキャスト失敗。_listFllower.getCurrent()="<<_listFllower.getCurrent()->getName()<<" のクラスから IFormationAble が見えません。public 継承して下さい。 this="<<getName()<<" _num_sub="<<_num_sub);
        }
#endif
        if (p->_pFormation == this) {
            _TRACE_("FormationActor::sayonaraFollwer _listFllowerの"<<_listFllower.getCurrent()->getName()<<"をsayonaraします。");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

FormationActor::~FormationActor() {

}
