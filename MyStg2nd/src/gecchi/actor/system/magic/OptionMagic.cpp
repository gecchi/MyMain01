#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

OptionMagic::OptionMagic(const char* prm_name, MagicMeter* prm_pMagicMeter) : Magic(prm_name, prm_pMagicMeter,
                                                          8,          //max_level
                                                          4*1000,     //cost_base
                                                          5*60*60,    //time_of_casting_base
                                                          3600*60 //1*60*60     //time_of_invoking èàóùÇ≈invokingäÆóπÇ≥ÇπÇÈ
                                                    ) {
//    |  0,   1,   2,   3 |
//    |  4,   5,   6,   7 |
//    |  8,   9,  10,  11 |
//    | 12,  13,  14,  15 |
//    | 16,  17,  18,  19 |
//    | 20,  21,  22,  23 |
//    | 24,  25,  26,  27 |
//    | 28,  29,  30,  31 |
//    | 32,  33,  34,  35 |
//    | 36,  37,  38,  39 |
//    | 40,  41,  42,  43 |
//    | 44,  45,  46,  47 |
//    | 48,  49,  50,  51 |
//    | 52,  53,  54,  55 |
//    | 56,  57,  58,  59 |
//    | 60,  61,  62,  63 |
    _lvinfo[0]._pno = 3;
    _lvinfo[1]._pno = 61;
    _lvinfo[2]._pno = 57;
    _lvinfo[3]._pno = 53;
    _lvinfo[4]._pno = 49;
    _lvinfo[5]._pno = 45;
    _lvinfo[6]._pno = 49;
    _lvinfo[7]._pno = 45;
    _lvinfo[8]._pno = 41;

    _lvinfo[0]._time_of_abandon = 300*60*60;
    _lvinfo[1]._time_of_abandon = 300*60*60;
    _lvinfo[2]._time_of_abandon = 300*60*60;
    _lvinfo[3]._time_of_abandon = 300*60*60;
    _lvinfo[4]._time_of_abandon = 300*60*60;
    _lvinfo[5]._time_of_abandon = 300*60*60;
    _lvinfo[6]._time_of_abandon = 300*60*60;
    _lvinfo[7]._time_of_abandon = 300*60*60;
    _lvinfo[8]._time_of_abandon = 300*60*60;
    _papEffect = NEW GgafDx9DrawableActor*[8];
    for (int i = 0; i < 8; i++) {
        _papEffect[i] = NEW EffectMagic001("EF");
        _papEffect[i]->inactivateImmediately();
        _pMagicMeter->addSubGroup(_papEffect[i]);
    }
}
void OptionMagic::processCastBegin() {
    _cast_speed = 60;
    if (_new_level > _level) {
        _cost = _cost_base * (_new_level - _level) * 0.8 ; //ÇQäÑà¯
    } else {
        _cost = -1.0f * _cost_base * (_level - _new_level) * 0.5;
		P_MYOPTIONCON->setNumOption(_new_level);
		commit();

    }

    _old_level = _level;
    angle* paAngWay = NEW angle[_level-_old_level];
    GgafDx9Util::getRadialAngle2D(0, _level-_old_level, paAngWay);
    for (int i = _old_level; i < _new_level; i++) {
        _papEffect[i]->setCoordinateBy(P_MYSHIP);
        _papEffect[i]->_pKuroko->setRzRyMvAng(ANGLE45, paAngWay[i]);
        _papEffect[i]->_pKuroko->setMvVelo(200000 / (_time_of_casting/_cast_speed));
        _papEffect[i]->_pKuroko->setMvAcce(0);
        _papEffect[i]->activate();
        _papEffect[i]->setAlpha(0.9);
        _papEffect[i]->setScaleRate(2.0f);
    }
	DELETEARR_IMPOSSIBLE_NULL(paAngWay);
    _r_effect = 1;

}

void OptionMagic::processCastingBehavior() {
    _r_effect += 0.02;
    for (int i = _old_level; i < _new_level; i++) {
        _papEffect[i]->setScaleRate(_r_effect);
    }
}

void OptionMagic::processInvokeBegin() {

    for (int i = _old_level; i < _new_level; i++) {
        _papEffect[i]->_pKuroko->setMvVelo(1000);
        _papEffect[i]->_pKuroko->setMvAcce(100);
        _papEffect[i]->_pKuroko->execTagettingMvAngSequence(P_MYOPTIONCON->_X + P_MYOPTIONCON->_papMyOption[i]->_Xorg,
                                                           P_MYOPTIONCON->_Y + P_MYOPTIONCON->_papMyOption[i]->_Yorg,
                                                           P_MYOPTIONCON->_Z + P_MYOPTIONCON->_papMyOption[i]->_Zorg,
                                                           3000,
                                                           0,TURN_CLOSE_TO,true);



        _papEffect[i]->_pKuroko->forceMvVeloRange(P_MYOPTIONCON->_papMyOption[i]->_veloMv*5.0);
//                                SmoothMvVeloSequence2(2000, 0, _time_of_casting, true);
    }

}

void OptionMagic::processInvokeingBehavior()  {
    if ((_time_of_invoking - _left_time_to_expire) < (ANGLE180/3000)) {
        return;
    }
    int targetX,targetY,targetZ;
    int ok = 0;
    for (int i = _old_level; i < _new_level; i++) {
        targetX = P_MYOPTIONCON->_X + P_MYOPTIONCON->_papMyOption[i]->_Xorg;
        targetY = P_MYOPTIONCON->_Y + P_MYOPTIONCON->_papMyOption[i]->_Yorg;
        targetZ = P_MYOPTIONCON->_Z + P_MYOPTIONCON->_papMyOption[i]->_Zorg;
        if (GgafUtil::abs(_papEffect[i]->_X - targetX) + GgafUtil::abs(_papEffect[i]->_Y - targetY) + GgafUtil::abs(_papEffect[i]->_Z - targetZ)/3  < GgafUtil::abs(P_MYOPTIONCON->_papMyOption[i]->_veloMv)*5) {
            ok++;
            _papEffect[i]->_pKuroko->setMvVelo(500);
        }
        _papEffect[i]->_pKuroko->execTagettingMvAngSequence(targetX,
                                                           targetY,
                                                           targetZ,
                                                           40000,
                                                           0,TURN_CLOSE_TO,true);
    }
    if (ok == (_new_level - _old_level)) {
        expire();
    }
}

void OptionMagic::processExpireBegin()  {
    P_MYOPTIONCON->setNumOption(_new_level);
    P_MYOPTIONCON->adjustDefaltAngPosition(60);
	_r_effect = 1.0f;
    for (int i = _old_level; i < _new_level; i++) {
        _papEffect[i]->setAlpha(_r_effect);
        _papEffect[i]->setCoordinateBy(P_MYOPTIONCON->_papMyOption[i]);
        P_MYOPTIONCON->_papMyOption[i]->setAlpha(0.0);
    }

}

void OptionMagic::processExpiringBehavior() {
    _r_effect -= 0.01f;
    for (int i = _old_level; i < _new_level; i++) {
        _papEffect[i]->setAlpha(_r_effect);
		_papEffect[i]->setScaleRate(3.0f+(1.0f-_r_effect)*4.0);
        _papEffect[i]->setCoordinateBy(P_MYOPTIONCON->_papMyOption[i]);
        P_MYOPTIONCON->_papMyOption[i]->setAlpha(1.0f-_r_effect);
    }
    if (_r_effect < 0) {
        for (int i = _old_level; i < _new_level; i++) {
            _papEffect[i]->inactivate();
            P_MYOPTIONCON->_papMyOption[i]->setAlpha(1.0);
        }
        commit();
    }
}

void OptionMagic::processOnAbandon(int prm_last_level) {
    P_MYOPTIONCON->setNumOption(_new_level);
    commit();
}

OptionMagic::~OptionMagic() {
    DELETEARR_IMPOSSIBLE_NULL(_papEffect);

}
