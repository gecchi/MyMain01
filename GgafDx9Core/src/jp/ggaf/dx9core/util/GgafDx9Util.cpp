#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

bool GgafDx9Util::_was_inited_flg = false;
int GgafDx9Util::COS_UNITLEN[S_ANG360];
int GgafDx9Util::SIN_UNITLEN[S_ANG360];
int GgafDx9Util::TAN_UNITLEN[S_ANG360];
int GgafDx9Util::RAD_UNITLEN[S_ANG360];
float GgafDx9Util::PARABORA[S_ANG360];
float GgafDx9Util::COS[S_ANG360];
float GgafDx9Util::SIN[S_ANG360];
float GgafDx9Util::RAD[S_ANG360];

int GgafDx9Util::SLANT_ANG_0[1000 + 1];
int GgafDx9Util::SLANT_ANG_1[10000 + 1];
int GgafDx9Util::SLANT_ANG_2[1100 + 1];

GgafDx9SphereRadiusVectors GgafDx9Util::_srv = GgafDx9SphereRadiusVectors();

void GgafDx9Util::init() {
    if (_was_inited_flg) {
        return;
    } else {
        for (s_ang ang = 0; ang < S_ANG360; ang++) {
            double rad = (PI * 2.0f * ang) / S_ANG360;
            COS_UNITLEN[ang] = (int)(cos(rad) * LEN_UNIT);
            SIN_UNITLEN[ang] = (int)(sin(rad) * LEN_UNIT);
            TAN_UNITLEN[ang] = (int)(tan(rad) * LEN_UNIT);
            RAD_UNITLEN[ang] = (int)(rad * LEN_UNIT);

            COS[ang] = (float)(cos(rad));
            SIN[ang] = (float)(sin(rad));
            RAD[ang] = (float)rad;
            PARABORA[ang] = (float)((double)((ang-(S_ANG360/2))*(ang-(S_ANG360/2))) /  (double)(-1.0*(S_ANG360/2)*(S_ANG360/2)) + 1.0);
            //PARABORA[0] = 0 , PARABORA[S_ANG180] = 1,  PARABORA[S_ANG360-1] = 0 Ç≈ y = -x^2  ï˙ï®ê¸ÇÃílÇÇ∆ÇÈ
        }

        COS_UNITLEN[0] = 1 * LEN_UNIT;
        COS_UNITLEN[S_ANG90] = 0;
        COS_UNITLEN[S_ANG180] = -1 * LEN_UNIT;
        COS_UNITLEN[S_ANG270] = 0;

        SIN_UNITLEN[0] = 0;
        SIN_UNITLEN[S_ANG90] = 1 * LEN_UNIT;
        SIN_UNITLEN[S_ANG180] = 0;
        SIN_UNITLEN[S_ANG270] = -1 * LEN_UNIT;

        TAN_UNITLEN[0] = 0;
        TAN_UNITLEN[S_ANG90] = LONG_MAX;
        TAN_UNITLEN[S_ANG180] = 0;
        TAN_UNITLEN[S_ANG270] = -1 * LONG_MAX;
        //TAN_UNITLEN[ANGLE360] = 0;

        COS[0] = 1;
        COS[S_ANG90] = 0;
        COS[S_ANG180] = -1;
        COS[S_ANG270] = 0;

        SIN[0] = 0;
        SIN[S_ANG90] = 1;
        SIN[S_ANG180] = 0;
        SIN[S_ANG270] = -1;

        //RAD_SLANT
        double rad;
        double vx;
        double vy;
		float slant;
        int index_slant;
        int index_slant_prev = -1;


        //åXÇ´ 0.0 Å` 1.0 ÇÃ äpìxÇãÅÇﬂîzóÒÇ…é˚ÇﬂÇÈÅBé˚ÇﬂÇÈäpìxÇÕ1000î{ÇÃêÆêîÅB
        //óvëfî‘çÜÇÕÅAåXÇ´*1000

        //ang=0 slant=0 index_slant=0 vx,vy=1,0
        //ang=1 slant=0.00174533 vx,vy=0.999998,0.00174533
        //ang=2 slant=0.00349067 vx,vy=0.999994,0.00349065
        //ang=3 slant=0.00523604 vx,vy=0.999986,0.00523596
        //ang=4 slant=0.00698143 vx,vy=0.999976,0.00698126
        //ang=5 slant=0.00872687 vx,vy=0.999962,0.00872654

        // SLANT_ANG_0[0]      = 0
        // SLANT_ANG_0[1]Å`[3] = 1000
        // SLANT_ANG_0[4]Å`[5] = 2000
        // SLANT_ANG_0[6]     s= 4000
        // SLANT_ANG_0[7]Å`[8] = 5000 Ç∆Ç¢Ç¡ÇΩãÔçá


        //ang=446 slant=0.986134 vx,vy=0.712026,0.7021
        //ang=447 slant=0.989582 vx,vy=0.710799,0.7033
        //ang=448 slant=0.993043 vx,vy=0.709571,0.7046
        //ang=449 slant=0.996515 vx,vy=0.70834,0.70587
        //ang=450 slant=1        vx,vy=0.707107,0.707107
        //--- Ç≥Ç©Ç¢Çﬂ
        //ang=450 slant=1       vx,vy=0.707107,0.707107
        //ang=451 slant=1.0035  vx,vy=0.705872,0.70834
        //ang=452 slant=1.00701 vx,vy=0.704634,0.709571
        //ang=453 slant=1.01053 vx,vy=0.703395,0.710799
        //ang=454 slant=1.01406 vx,vy=0.702153,0.712026

        //ang=450(45.0ìx)à»ç~ÇÕéüÇÃîzóÒÇ…é˚ÇﬂÇÈÅB
        //ç≈ëÂóvëfINDEXÇÕ 1000 Ç∆Ç»ÇÈÅB

        for (s_ang ang = 0; ang <= S_ANG45; ang++) {
            rad = (PI * 2.0f * ang) / S_ANG360;
            vx = cos(rad);
            vy = sin(rad);
            if (vx == 0) {
                slant = 0;
            } else {
                slant = vy / vx;
            }
            index_slant = slant * 1000;
            for (int i = index_slant_prev+1; i <= index_slant; i++) {
                if (i > 1000) {
                    _TRACE_("ÅÉåxçêÅÑëzíËîÕàÕà»è„ÇÃåXÇ´îzóÒINDEXÇê›íËÅBÉÅÉÇÉäÇ™îjâÛÇ≥ÇÍÇ‹Ç∑ÅBSLANT_ANG_0["<<i<<"]<="<<(ang*100));
                }
                SLANT_ANG_0[i] = ang*100;
            }
			index_slant_prev = index_slant;
//			_TRACE_("ang="<<ang<<" slant="<<slant<<" index_slant="<<index_slant<<" vx,vy="<<vx<<","<<vy);
        }
        for (int i = index_slant_prev+1; i <= 1000; i++) {
            if (i > 1000) {
                _TRACE_("ÅÉåxçêÅÑëzíËîÕàÕà»è„ÇÃåXÇ´îzóÒINDEXÇê›íËÅBÉÅÉÇÉäÇ™îjâÛÇ≥ÇÍÇ‹Ç∑ÅBSLANT_ANG_0["<<i<<"]<="<<(S_ANG45*100));
            }
            SLANT_ANG_0[i] = S_ANG45*100;
        }

        //åXÇ´ 1.0 Å` 10.0187 ÇÃ äpìxÇãÅÇﬂîzóÒÇ…é˚ÇﬂÇÈÅB
        //óvëfî‘çÜÇÕÅAåXÇ´*1000 - 1000

        //ang=450 slant=1       vx,vy=0.707107,0.707107
        //ang=451 slant=1.0035  vx,vy=0.705872,0.70834
        //ang=452 slant=1.00701 vx,vy=0.704634,0.709571
        //ang=453 slant=1.01053 vx,vy=0.703395,0.710799

        // SLANT_ANG_1[0]      = 450000
        // SLANT_ANG_1[1]Å`[3] = 451000
        // SLANT_ANG_1[4]Å`[7] = 452000
        // SLANT_ANG_1[8]Å`[10] = 453000 Ç∆Ç¢Ç¡ÇΩãÔçá

        //åXÇ´Ç∆äpìxÇÃä÷åWÅiñ{ÉtÉ@ÉCÉãÇÃç≈å„ÇÃÉRÉÅÉìÉgéQè∆)ÇÊÇË

        //ang=838 slant=9.20516 vx,vy=0.107999,0.994151
        //ang=839 slant=9.35724 vx,vy=0.106264,0.994338
        //ang=840 slant=9.51436 vx,vy=0.104528,0.994522
        //ang=841 slant=9.6768  vx,vy=0.102793,0.994703
        //ang=842 slant=9.84482 vx,vy=0.101056,0.994881
        //ang=843 slant=10.0187 vx,vy=0.0993197,0.995056 <--Ç≥Ç©Ç¢Çﬂ
        //---
        //ang=843 slant=10.0187 vx,vy=0.0993197,0.995056 <--Ç≥Ç©Ç¢Çﬂ
        //ang=844 slant=10.1988 vx,vy=0.0975829,0.995227
        //ang=845 slant=10.3854 vx,vy=0.0958458,0.995396
        //ang=846 slant=10.5789 vx,vy=0.0941083,0.995562

        //ang=842(84.2ìx)à»ç~ÇÕéüÇÃîzóÒÇ…é˚ÇﬂÇÈÅBÇµÇΩÇ™Ç¡ÇƒÇ±ÇÃîzóÒÇÃÉTÉ|Å[ÉgÇÕslant=9.84482Ç‹Ç≈Ç∆ÇµÇÊÇ§
        //ç≈ëÂóvëfINDEXÇÕ 10.0187*1000 - 1000 = 10018 - 1000 = 9018 Ç∆Ç»ÇÈÅBÅiÇªÇ§Ç∑ÇÍÇŒóvëfêîÇ™10000Ç≈é˚Ç‹ÇÈÇµÅj
        index_slant_prev = -1;
        for (s_ang ang = S_ANG45; ang <= 843; ang++) {
            rad = (PI * 2.0f * ang) / S_ANG360;
            vx = cos(rad);
            vy = sin(rad);
            if (vx == 0) {
                slant = 0;
            } else {
                slant = vy / vx;
            }
            index_slant = slant*1000.0 - 1000.0;
            for (int i = index_slant_prev+1; i <= index_slant; i++) {
                if (i > 9018) {
                    _TRACE_("ÅÉåxçêÅÑëzíËîÕàÕà»è„ÇÃåXÇ´îzóÒINDEXÇê›íËÅBÉÅÉÇÉäÇ™îjâÛÇ≥ÇÍÇ‹Ç∑ÅBSLANT_ANG_1["<<i<<"]<="<<(ang*100));
                }
                SLANT_ANG_1[i] = ang*100;
            }
            index_slant_prev = index_slant;
//            _TRACE_("ang="<<ang<<" slant="<<slant<<" index_slant="<<index_slant<<" vx,vy="<<vx<<","<<vy);
        }
        for (int i = index_slant_prev+1; i <= 9018; i++) {
            if (i > 9018) {
                _TRACE_("ÅÉåxçêÅÑëzíËîÕàÕà»è„ÇÃåXÇ´îzóÒINDEXÇê›íËÅBÉÅÉÇÉäÇ™îjâÛÇ≥ÇÍÇ‹Ç∑ÅBSLANT_ANG_1["<<i<<"]<=843000");
            }
            SLANT_ANG_1[i] = 843000;
        }

        //åXÇ´ 10.0187 Å` 95.4895 ÇÃ äpìxÇãÅÇﬂîzóÒÇ…é˚ÇﬂÇÈÅB
        //óvëfî‘çÜÇÕÅAåXÇ´*10 - 100

        //ang=843 slant=10.0187 vx,vy=0.0993197,0.995056
        //ang=844 slant=10.1988 vx,vy=0.0975829,0.995227
        //ang=845 slant=10.3854 vx,vy=0.0958458,0.995396
        //ang=846 slant=10.5789 vx,vy=0.0941083,0.995562

        // SLANT_ANG_2[0]      = 843000
        // SLANT_ANG_2[1]      = 844000
        // SLANT_ANG_2[2]Å`[3] = 845000
        // SLANT_ANG_2[4]Å`[5] = 846000 Ç∆Ç¢Ç¡ÇΩãÔçá

        //åXÇ´Ç∆äpìxÇÃä÷åWÅiñ{ÉtÉ@ÉCÉãÇÃç≈å„ÇÃÉRÉÅÉìÉgéQè∆)ÇÊÇË

        //ang=890 slant=57.29 vx,vy=0.0174524,0.999848
        //ang=891 slant=63.6567 vx,vy=0.0157073,0.999877
        //ang=892 slant=71.6151 vx,vy=0.0139622,0.999903
        //ang=893 slant=81.847 vx,vy=0.012217,0.999925
        //ang=894 slant=95.4895 vx,vy=0.0104718,0.999945
        //ang=895 slant=114.589 vx,vy=0.00872654,0.999962
        //---Ç≥Ç©Ç¢Çﬂ
        //ang=895 slant=114.589 vx,vy=0.00872654,0.999962
        //ang=896 slant=143.237 vx,vy=0.00698126,0.999976
        //ang=897 slant=190.984 vx,vy=0.00523596,0.999986
        //ang=898 slant=286.478 vx,vy=0.00349065,0.999994
        //ang=899 slant=572.957 vx,vy=0.00174533,0.999998

        //ang=895(89.5ìx)à»ç~ÇÕÅAÇ‡Ç§ÅEÅEÅEifï∂Ç≈èÍçáÇÌÇØÇ∑ÇÈ
        //ç≈ëÂóvëfINDEXÇÕ 114.589 * 10 - 100 = 1145 - 100 = 1045 Ç∆Ç»ÇÈÅB
        index_slant_prev = -1;
        for (s_ang ang = 843; ang <= 895; ang++) {
            rad = (PI * 2.0f * ang) / S_ANG360;
            vx = cos(rad);
            vy = sin(rad);
            if (vx == 0) {
                slant = 0;
            } else {
                slant = vy / vx;
            }
            index_slant = slant*10.0 - 100.0;
            for (int i = index_slant_prev+1; i <= index_slant; i++) {
                if (i > 1045) {
                    _TRACE_("ÅÉåxçêÅÑëzíËîÕàÕà»è„ÇÃåXÇ´îzóÒINDEXÇê›íËÅBÉÅÉÇÉäÇ™îjâÛÇ≥ÇÍÇ‹Ç∑ÅBSLANT_ANG_2["<<i<<"]<="<<(ang*100));
                }
                SLANT_ANG_2[i] = ang*100;
            }
            index_slant_prev = index_slant;
//            _TRACE_("ang="<<ang<<" slant="<<slant<<" index_slant="<<index_slant<<" vx,vy="<<vx<<","<<vy);
        }
        for (int i = index_slant_prev+1; i <= 1045; i++) {
            if (i > 1045) {
                _TRACE_("ÅÉåxçêÅÑëzíËîÕàÕà»è„ÇÃåXÇ´îzóÒINDEXÇê›íËÅBÉÅÉÇÉäÇ™îjâÛÇ≥ÇÍÇ‹Ç∑ÅBSLANT_ANG_2["<<i<<"]<=894000");
            }
            SLANT_ANG_2[i] = 894000;
        }

//        for (int s = 0; s <= 1000; s++) {
//            _TRACE_("SLANT_ANG_0["<<s<<"]="<<SLANT_ANG_0[s]<<" åXÇ´"<<(s/1000.0)<<"=äpìx"<<(SLANT_ANG_0[s]/1000.0));
//        }
//        for (int s = 0; s <= 9018; s++) {
//            _TRACE_("SLANT_ANG_1["<<s<<"]="<<SLANT_ANG_1[s]<<" åXÇ´"<<((s+1000)/1000.0)<<"=äpìx"<<(SLANT_ANG_1[s]/1000.0));
//        }
//        for (int s = 0; s <= 854; s++) {
//            _TRACE_("SLANT_ANG_2["<<s<<"]="<<SLANT_ANG_2[s]<<" åXÇ´"<<((s+100)/10.0)<<"=äpìx"<<(SLANT_ANG_2[s]/1000.0));
//        }

    }
}

angle GgafDx9Util::getAngle2D(int prm_vx, int prm_vy) {
    if (prm_vy == 0) {
        if (prm_vx > 0) {
            return 0;
        } else if (prm_vx < 0) {
            return ANGLE180;
        } else {
            //(0,0)ÇÃÉxÉNÉgÉãï˚å¸ÇÕñ≥Ç¢
            //ÇµÇ©ÇΩÇ»Ç¢ÇÃÇ≈ 0
            return 0;
        }
    } else if (prm_vx == 0) {
        if (prm_vy > 0) {
            return ANGLE90;
        } else if (prm_vy < 0) {
            return ANGLE270;
        } else {
            //(0,0)ÇÃÉxÉNÉgÉãï˚å¸ÇÕñ≥Ç¢
            //ÇµÇ©ÇΩÇ»Ç¢ÇÃÇ≈ 0
            return 0;
        }
    } else {

        //ÉoÉCÉiÉäÅ[ÉTÅ[É`Ç≈íºãﬂÇíTÇ∑
        static s_ang left, right, middle;
        if (prm_vx > 0 && prm_vy > 0) { //ëÊ1è€å¿
            left = 1;
            right = S_ANG90 - 1;
        } else if (prm_vx < 0 && prm_vy > 0) { //ëÊ2è€å¿
            left = S_ANG90 + 1;
            right = S_ANG180 - 1;
        } else if (prm_vx < 0 && prm_vy < 0) { //ëÊ3è€å¿
            left = S_ANG180 + 1;
            right = S_ANG270 - 1;
        } else if (prm_vx > 0 && prm_vy < 0) { //ëÊ4è€å¿
            left = S_ANG270 + 1;
            right = S_ANG360 - 1;
        } else {
            //Ç“Ç¡ÇΩÇËèdÇ»Ç¡ÇƒÇ¢ÇÈèÍçá
            return 0; //édï˚Ç»Ç¢ÇÃÇ≈0
        }
        s_ang middle_prev = -1;
        int lTerget = (int)(LEN_UNIT * ((1.0f * prm_vy) / (1.0f * prm_vx)));
        while (true) {
            middle = (left + right) / 2;
            if (TAN_UNITLEN[middle] < lTerget) {

                left = middle;
            } else {
                right = middle;
            }
            if (middle_prev == middle) {
                break;
            } else {
                middle_prev = middle;
            }
        }
        return left * ANGLE_RATE;
    }
}

void GgafDx9Util::getWayAngle2D(int prm_vx_Center,
                                int prm_vy_Center,
                                int prm_way,
                                angle prm_angClearance,
                                angle* out_paAngle) {
    return getWayAngle2D(getAngle2D(prm_vx_Center, prm_vy_Center), prm_way, prm_angClearance, out_paAngle);
}

void GgafDx9Util::getWayAngle2D(angle prm_angCenter, int prm_way, angle prm_angClearance, angle* out_paAngle) {
    int angstart = addAngle(prm_angCenter, ((prm_way - 1) * prm_angClearance) / -2);

    for (int i = 0; i < prm_way; i++) {
        out_paAngle[i] = addAngle(angstart, prm_angClearance * i);
    }
}
void GgafDx9Util::getRadiationAngle2D(angle prm_angStart, int prm_way, angle* out_paAngle) {
    for (int i = 0; i < prm_way; i++) {
        out_paAngle[i] = addAngle(prm_angStart, (1.0f * ANGLE360 / prm_way * i));
    }
}

//void GgafDx9Util::getMoveRzRyWayShot3D_XZ(int prm_way, angle prm_angClearance, int prm_tX, int prm_tY, int prm_tZ,
//                                          angle& out_angRotZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    getRotAngleZY(prm_tX, prm_tY, prm_tZ, tRy, tRy);
//
//    angle angStart = addAngle(tRy, ((prm_way - 1) * prm_angClearance) / -2);
//    for (int i = 0; i < prm_way; i++) {
//        out_paAngRotY[i] = addAngle(angstart, prm_angClearance * i);
//    }
//}

angle GgafDx9Util::addAngle(angle prm_angNow, angle prm_angOffset) {
    static angle angAdd;
    angAdd = prm_angNow + prm_angOffset;
    while (angAdd >= ANGLE360) {
        angAdd -= ANGLE360;
    }
    while (angAdd < 0) {
        angAdd += ANGLE360;
    }
    return angAdd;
}

void GgafDx9Util::rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y) {
    out_X = (int)(floor((prm_X * GgafDx9Util::COS[prm_ang / ANGLE_RATE]) - (prm_Y * GgafDx9Util::SIN[prm_ang
            / ANGLE_RATE])));
    out_Y = (int)(floor((prm_X * GgafDx9Util::SIN[prm_ang / ANGLE_RATE]) + (prm_Y * GgafDx9Util::COS[prm_ang
            / ANGLE_RATE])));
}

// ê¸ï™ÇÃìñÇΩÇËîªíË (x11,y11)-(x12,y12) Å~ (x21,y21)-(x22,y22)
bool GgafDx9Util::chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {

    //xç¿ïWÇ…ÇÊÇÈÉ`ÉFÉbÉN
    if (x11 >= x12) {
        if ((x11 < x21 && x11 < x22) || (x12 > x21 && x12 > x22)) {
            return false;
        }
    } else {
        if ((x12 < x21 && x12 < x22) || (x11 > x21 && x11 > x22)) {
            return false;
        }
    }
    //yç¿ïWÇ…ÇÊÇÈÉ`ÉFÉbÉN
    if (y11 >= y12) {
        if ((y11 < y21 && y11 < y22) || (y12 > y21 && y12 > y22)) {
            return false;
        }
    } else {
        if ((y12 < y21 && y12 < y22) || (y11 > y21 && y11 > y22)) {
            return false;
        }
    }
    if (((x11 - x12) * (y21 - y11) + (y11 - y12) * (x11 - x21)) * ((x11 - x12) * (y22 - y11) + (y11 - y12)
            * (x11 - x22)) > 0) {
        return false;
    }
    if (((x21 - x22) * (y11 - y21) + (y21 - y22) * (x21 - x11)) * ((x21 - x22) * (y12 - y21) + (y21 - y22)
            * (x21 - x12)) > 0) {
        return false;
    }
    return true;
}

int GgafDx9Util::getDistance(int x1, int y1, int x2, int y2) {
    return sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}


void GgafDx9Util::getRotAngleZY(int x,
                                int y,
                                int z,
                                float& out_nvx,
                                float& out_nvy,
                                float& out_nvz,
                                angle& out_angRotZ,
                                angle& out_angRotY ) {
    static float vx, vy, vz, t;
    vx = ((float)x) / LEN_UNIT;
    vy = ((float)y) / LEN_UNIT;
    vz = ((float)z) / LEN_UNIT;
    //vx,vy,vz Çê≥ãKâªÇ∑ÇÈÅB
    //ãÅÇﬂÇÈíPà ÉxÉNÉgÉãÇ (X,Y,Z) Ç∆Ç∑ÇÈÇ∆ (X,Y,Z) = t(vx,vy,vz)
    //ä÷åWéÆ   X=t*vx; Y=t*vy; Z=t*vz; ••• (1) ÇìæÇÈ
    //íPà ãÖÇÕ X^2 + Y^2 + Z^2 = 1 •••(2)
    //(1)(2)ÇòAóßÇ≥ÇπÇƒÅAt Ç…Ç¬Ç¢ÇƒâÇ≠ÅB
    //t = 1 / sqrt(vx^2 + vy^2 + vz^2)
    t = 1 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    //ãÅÇﬂÇΩ t Ç (1) Ç…ë„ì¸Çµ (X,Y,Z) ÇãÅÇﬂÇÈÅB
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;

    //GgafDx9SphereRadiusVectors ÇégÇ¡ÇƒíPà ÉxÉNÉgÉãÇ©ÇÁâÒì]äpÇÇ‡Ç∆ÇﬂÇÈ
    //íAÇµ GgafDx9SphereRadiusVectors ÇÃÉxÉNÉgÉãê∏ìxÇÕ 10000ÇèÊÇ∂ÇΩêÆêîÇ≈Ç†ÇÈÅB(LEN_UNIT*10)
    //Ç≥ÇÁÇ…ÅAà¯êîÇÃÉxÉNÉgÉãóvëfÇÕëSÇƒê≥ÇÃílÅi1/8 ÇÃãÖï™ÅjÇæÇØÇ»ÇÃÇ≈Ç∑ÅBÇÊÇ¡ÇƒÅAÇ¢ÇÎÇ¢ÇÎèÍçáÇÌÇØÇ∑ÇÈÅB

    static s_ang rZ, rY;
    _srv.getRotAngleClosely(
            (unsigned __int16) abs(out_nvx*10000),
            (unsigned __int16) abs(out_nvy*10000),
            (unsigned __int16) abs(out_nvz*10000),
            rZ,
            rY
    );

    //x > 0; y > 0; z > 0 ÇÃóÃàÊÇëÊàÍè€å¿Ç∆Ç∑ÇÈ
    //x < 0; y > 0; z > 0 ÇÃóÃàÊÇëÊìÒè€å¿Ç∆Ç∑ÇÈ
    //x < 0; y < 0; z > 0 ÇÃóÃàÊÇëÊéOè€å¿Ç∆Ç∑ÇÈ
    //x > 0; y < 0; z > 0 ÇÃóÃàÊÇëÊélè€å¿Ç∆Ç∑ÇÈ
    //x > 0; y > 0; z < 0 ÇÃóÃàÊÇëÊå‹è€å¿Ç∆Ç∑ÇÈ
    //x < 0; y > 0; z < 0 ÇÃóÃàÊÇëÊòZè€å¿Ç∆Ç∑ÇÈ
    //x < 0; y < 0; z < 0 ÇÃóÃàÊÇëÊéµè€å¿Ç∆Ç∑ÇÈ
    //x > 0; y < 0; z < 0 ÇÃóÃàÊÇëÊî™è€å¿Ç∆Ç∑ÇÈ
    //è€å¿Ç…ÇÊÇ¡ÇƒâÒì]äpÇï‚ê≥
    if (vx >= 0 && vy >= 0 && vz >= 0) { //ëÊàÍè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //ëÊìÒè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //ëÊéOè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //ëÊélè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //ëÊå‹è€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //ëÊòZè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //ëÊéµè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //ëÊî™è€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else {
        _TRACE_("Ç®Ç©ÇµÇ¢Ç≈Ç∑Ç∫");
    }

    //_TRACE_("(x,y,z)=("<<x<<","<<y<<","<<z<<") (out_nvx,nvy,nvz)=("<<out_nvx<<","<<out_nvy<<","<<out_nvz<<") RZ="<<out_angRotZ<<" RY="<<out_angRotY);
}

void GgafDx9Util::getRotAngleZY(int x, int y, int z, angle& out_angRotZ, angle& out_angRotY) {
    static float vx, vy, vz, t;
    vx = ((float)x) / LEN_UNIT;
    vy = ((float)y) / LEN_UNIT;
    vz = ((float)z) / LEN_UNIT;
    t = 1 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    static s_ang rZ, rY;

    _srv.getRotAngleClosely(
            (unsigned __int16) abs(t*vx*10000),
            (unsigned __int16) abs(t*vy*10000),
            (unsigned __int16) abs(t*vz*10000),
            rZ,
            rY
    );
    if (vx >= 0 && vy >= 0 && vz >= 0) { //ëÊàÍè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //ëÊìÒè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //ëÊéOè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //ëÊélè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //ëÊå‹è€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //ëÊòZè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //ëÊéµè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //ëÊî™è€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else {
        _TRACE_("Ç®Ç©ÇµÇ¢Ç≈Ç∑Ç∫");
    }
}

void GgafDx9Util::getRotAngleZY(float vx, float vy, float vz, angle& out_angRotZ, angle& out_angRotY) {
    static s_ang rZ, rY;
    _srv.getRotAngleClosely(
            (unsigned __int16) abs(vx*10000),
            (unsigned __int16) abs(vy*10000),
            (unsigned __int16) abs(vz*10000),
            rZ,
            rY
    );
    if (vx >= 0 && vy >= 0 && vz >= 0) { //ëÊàÍè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //ëÊìÒè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //ëÊéOè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //ëÊélè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //ëÊå‹è€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //ëÊòZè€å¿
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //ëÊéµè€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //ëÊî™è€å¿
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else {
        _TRACE_("Ç®Ç©ÇµÇ¢Ç≈Ç∑Ç∫");
    }
}

void GgafDx9Util::getNormalizeVector(int x,
                                     int y,
                                     int z,
                                     float& out_nvx,
                                     float& out_nvy,
                                     float& out_nvz) {
    static float vx, vy, vz, t;
    vx = ((float)x) / LEN_UNIT;
    vy = ((float)y) / LEN_UNIT;
    vz = ((float)z) / LEN_UNIT;
    t = 1 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;

}
















void GgafDx9Util::getNormalizeVectorZY(angle prm_angRotZ,
                                       angle prm_angRotY,
                                       float& out_nvx,
                                       float& out_nvy,
                                       float& out_nvz) {
    //void GgafDx9SphereRadiusVectors::getVectorClosely(int out_angRotY, int prm_angRotZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z) {
    //âÒì]äpÇ…ÇÊÇ¡Çƒè€å¿Ççló∂ÇµÅAgetVectorCloselyÇÃÉpÉâÉÅÅ[É^äp(< 900)ÇèoÇ∑
    static int Xsign, Ysign, Zsign;
    static s_ang rZ, rY;

    if (0 <= prm_angRotZ && prm_angRotZ < ANGLE90) {
        rZ = (prm_angRotZ - ANGLE0) / ANGLE_RATE;
        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //ëÊå‹è€å¿
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //ëÊòZè€å¿
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //ëÊìÒè€å¿
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //ëÊàÍè€å¿
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        }
    } else if (ANGLE90 <= prm_angRotZ && prm_angRotZ < ANGLE180) {
        rZ = (ANGLE180 - prm_angRotZ) / ANGLE_RATE;

        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //ëÊìÒè€å¿
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //ëÊàÍè€å¿
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //ëÊå‹è€å¿
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //ëÊòZè€å¿
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        }

    } else if (ANGLE180 <= prm_angRotZ && prm_angRotZ < ANGLE270) {
        rZ = (prm_angRotZ - ANGLE180) / ANGLE_RATE;
        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //ëÊéOè€å¿
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //ëÊélè€å¿
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //ëÊî™è€å¿
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //ëÊéµè€å¿
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        }
    } else if (ANGLE270 <= prm_angRotZ && prm_angRotZ < ANGLE360) {
        rZ = (ANGLE360 - prm_angRotZ) / ANGLE_RATE;
        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //ëÊî™è€å¿
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //ëÊéµè€å¿
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //ëÊéOè€å¿
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //ëÊélè€å¿
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        }
    } else {
        _TRACE_("getNormalizeVectorZY: Ç»ÇÒÇ©Ç®Ç©ÇµÇ¢Ç≈Ç∑Ç∫");
    }
    static unsigned __int16 vx, vy, vz;
    //	_TRACE_("prm_angRotZ="<<prm_angRotZ<<"/prm_angRotY="<<prm_angRotY<<" rY="<<rY<<"/rZ="<<rZ<<")");
    //	_TRACE_("("<<Xsign<<","<<Ysign<<","<<Zsign<<")");
    _srv.getVectorClosely(rY, rZ, vx, vy, vz);
    out_nvx = Xsign * vx / 10000.0f;
    out_nvy = Ysign * vy / 10000.0f;
    out_nvz = Zsign * vz / 10000.0f;
}

//DWORD GgafDx9Util::max3(DWORD a, DWORD b, DWORD c) {
//	if (a > b) {
//		if (a > c) {
//			return a;
//		} else {
//			return c;
//		}
//	} else {
//		if (b > c) {
//			return b;
//		} else {
//			return c;
//		}
//	}
//}


//åXÇ´Ç∆äpìxÇÃä÷åW
//ang=0 slant=0 vx,vy=1,0
//ang=1 slant=0.00174533 vx,vy=0.999998,0.00174533
//ang=2 slant=0.00349067 vx,vy=0.999994,0.00349065
//ang=3 slant=0.00523604 vx,vy=0.999986,0.00523596
//ang=4 slant=0.00698143 vx,vy=0.999976,0.00698126
//ang=5 slant=0.00872687 vx,vy=0.999962,0.00872654
//ang=6 slant=0.0104724 vx,vy=0.999945,0.0104718
//ang=7 slant=0.0122179 vx,vy=0.999925,0.012217
//ang=8 slant=0.0139635 vx,vy=0.999903,0.0139622
//ang=9 slant=0.0157093 vx,vy=0.999877,0.0157073
//ang=10 slant=0.0174551 vx,vy=0.999848,0.0174524
//ang=11 slant=0.019201 vx,vy=0.999816,0.0191974
//ang=12 slant=0.020947 vx,vy=0.999781,0.0209424
//ang=13 slant=0.0226932 vx,vy=0.999743,0.0226873
//ang=14 slant=0.0244395 vx,vy=0.999701,0.0244322
//ang=15 slant=0.0261859 vx,vy=0.999657,0.0261769
//ang=16 slant=0.0279325 vx,vy=0.99961,0.0279216
//ang=17 slant=0.0296793 vx,vy=0.99956,0.0296662
//ang=18 slant=0.0314263 vx,vy=0.999507,0.0314108
//ang=19 slant=0.0331734 vx,vy=0.99945,0.0331552
//ang=20 slant=0.0349208 vx,vy=0.999391,0.0348995
//ang=21 slant=0.0366683 vx,vy=0.999328,0.0366437
//ang=22 slant=0.0384161 vx,vy=0.999263,0.0383878
//ang=23 slant=0.0401641 vx,vy=0.999194,0.0401318
//ang=24 slant=0.0419124 vx,vy=0.999123,0.0418757
//ang=25 slant=0.0436609 vx,vy=0.999048,0.0436194
//ang=26 slant=0.0454097 vx,vy=0.998971,0.045363
//ang=27 slant=0.0471588 vx,vy=0.99889,0.0471065
//ang=28 slant=0.0489082 vx,vy=0.998806,0.0488498
//ang=29 slant=0.0506578 vx,vy=0.998719,0.0505929
//ang=30 slant=0.0524078 vx,vy=0.99863,0.052336
//ang=31 slant=0.0541581 vx,vy=0.998537,0.0540788
//ang=32 slant=0.0559087 vx,vy=0.998441,0.0558215
//ang=33 slant=0.0576596 vx,vy=0.998342,0.057564
//ang=34 slant=0.0594109 vx,vy=0.99824,0.0593064
//ang=35 slant=0.0611626 vx,vy=0.998135,0.0610485
//ang=36 slant=0.0629147 vx,vy=0.998027,0.0627905
//ang=37 slant=0.0646671 vx,vy=0.997916,0.0645323
//ang=38 slant=0.0664199 vx,vy=0.997801,0.0662739
//ang=39 slant=0.0681732 vx,vy=0.997684,0.0680153
//ang=40 slant=0.0699268 vx,vy=0.997564,0.0697565
//ang=41 slant=0.0716809 vx,vy=0.997441,0.0714974
//ang=42 slant=0.0734354 vx,vy=0.997314,0.0732382
//ang=43 slant=0.0751904 vx,vy=0.997185,0.0749787
//ang=44 slant=0.0769458 vx,vy=0.997053,0.076719
//ang=45 slant=0.0787017 vx,vy=0.996917,0.0784591
//ang=46 slant=0.0804581 vx,vy=0.996779,0.0801989
//ang=47 slant=0.082215 vx,vy=0.996637,0.0819385
//ang=48 slant=0.0839723 vx,vy=0.996493,0.0836778
//ang=49 slant=0.0857302 vx,vy=0.996345,0.0854169
//ang=50 slant=0.0874887 vx,vy=0.996195,0.0871557
//ang=51 slant=0.0892476 vx,vy=0.996041,0.0888943
//ang=52 slant=0.0910071 vx,vy=0.995884,0.0906326
//ang=53 slant=0.0927672 vx,vy=0.995725,0.0923706
//ang=54 slant=0.0945278 vx,vy=0.995562,0.0941083
//ang=55 slant=0.096289 vx,vy=0.995396,0.0958458
//ang=56 slant=0.0980509 vx,vy=0.995227,0.0975829
//ang=57 slant=0.0998133 vx,vy=0.995056,0.0993197
//ang=58 slant=0.101576 vx,vy=0.994881,0.101056
//ang=59 slant=0.10334 vx,vy=0.994703,0.102793
//ang=60 slant=0.105104 vx,vy=0.994522,0.104528
//ang=61 slant=0.106869 vx,vy=0.994338,0.106264
//ang=62 slant=0.108635 vx,vy=0.994151,0.107999
//ang=63 slant=0.110401 vx,vy=0.993961,0.109734
//ang=64 slant=0.112168 vx,vy=0.993768,0.111469
//ang=65 slant=0.113936 vx,vy=0.993572,0.113203
//ang=66 slant=0.115704 vx,vy=0.993373,0.114937
//ang=67 slant=0.117473 vx,vy=0.993171,0.116671
//ang=68 slant=0.119243 vx,vy=0.992966,0.118404
//ang=69 slant=0.121013 vx,vy=0.992757,0.120137
//ang=70 slant=0.122785 vx,vy=0.992546,0.121869
//ang=71 slant=0.124557 vx,vy=0.992332,0.123601
//ang=72 slant=0.126329 vx,vy=0.992115,0.125333
//ang=73 slant=0.128103 vx,vy=0.991894,0.127065
//ang=74 slant=0.129877 vx,vy=0.991671,0.128796
//ang=75 slant=0.131652 vx,vy=0.991445,0.130526
//ang=76 slant=0.133428 vx,vy=0.991216,0.132256
//ang=77 slant=0.135205 vx,vy=0.990983,0.133986
//ang=78 slant=0.136983 vx,vy=0.990748,0.135716
//ang=79 slant=0.138761 vx,vy=0.990509,0.137445
//ang=80 slant=0.140541 vx,vy=0.990268,0.139173
//ang=81 slant=0.142321 vx,vy=0.990024,0.140901
//ang=82 slant=0.144102 vx,vy=0.989776,0.142629
//ang=83 slant=0.145884 vx,vy=0.989526,0.144356
//ang=84 slant=0.147667 vx,vy=0.989272,0.146083
//ang=85 slant=0.149451 vx,vy=0.989016,0.147809
//ang=86 slant=0.151236 vx,vy=0.988756,0.149535
//ang=87 slant=0.153022 vx,vy=0.988494,0.151261
//ang=88 slant=0.154808 vx,vy=0.988228,0.152986
//ang=89 slant=0.156596 vx,vy=0.98796,0.15471
//ang=90 slant=0.158384 vx,vy=0.987688,0.156434
//ang=91 slant=0.160174 vx,vy=0.987414,0.158158
//ang=92 slant=0.161965 vx,vy=0.987136,0.159881
//ang=93 slant=0.163756 vx,vy=0.986856,0.161604
//ang=94 slant=0.165549 vx,vy=0.986572,0.163326
//ang=95 slant=0.167343 vx,vy=0.986286,0.165048
//ang=96 slant=0.169137 vx,vy=0.985996,0.166769
//ang=97 slant=0.170933 vx,vy=0.985703,0.168489
//ang=98 slant=0.17273 vx,vy=0.985408,0.170209
//ang=99 slant=0.174528 vx,vy=0.985109,0.171929
//ang=100 slant=0.176327 vx,vy=0.984808,0.173648
//ang=101 slant=0.178127 vx,vy=0.984503,0.175367
//ang=102 slant=0.179928 vx,vy=0.984196,0.177085
//ang=103 slant=0.181731 vx,vy=0.983885,0.178802
//ang=104 slant=0.183534 vx,vy=0.983571,0.180519
//ang=105 slant=0.185339 vx,vy=0.983255,0.182236
//ang=106 slant=0.187145 vx,vy=0.982935,0.183951
//ang=107 slant=0.188952 vx,vy=0.982613,0.185667
//ang=108 slant=0.19076 vx,vy=0.982287,0.187381
//ang=109 slant=0.19257 vx,vy=0.981959,0.189095
//ang=110 slant=0.19438 vx,vy=0.981627,0.190809
//ang=111 slant=0.196192 vx,vy=0.981293,0.192522
//ang=112 slant=0.198005 vx,vy=0.980955,0.194234
//ang=113 slant=0.19982 vx,vy=0.980615,0.195946
//ang=114 slant=0.201635 vx,vy=0.980271,0.197657
//ang=115 slant=0.203452 vx,vy=0.979925,0.199368
//ang=116 slant=0.205271 vx,vy=0.979575,0.201078
//ang=117 slant=0.20709 vx,vy=0.979223,0.202787
//ang=118 slant=0.208911 vx,vy=0.978867,0.204496
//ang=119 slant=0.210733 vx,vy=0.978509,0.206204
//ang=120 slant=0.212557 vx,vy=0.978148,0.207912
//ang=121 slant=0.214381 vx,vy=0.977783,0.209619
//ang=122 slant=0.216208 vx,vy=0.977416,0.211325
//ang=123 slant=0.218035 vx,vy=0.977046,0.21303
//ang=124 slant=0.219864 vx,vy=0.976672,0.214735
//ang=125 slant=0.221695 vx,vy=0.976296,0.21644
//ang=126 slant=0.223526 vx,vy=0.975917,0.218143
//ang=127 slant=0.22536 vx,vy=0.975535,0.219846
//ang=128 slant=0.227194 vx,vy=0.975149,0.221548
//ang=129 slant=0.229031 vx,vy=0.974761,0.22325
//ang=130 slant=0.230868 vx,vy=0.97437,0.224951
//ang=131 slant=0.232707 vx,vy=0.973976,0.226651
//ang=132 slant=0.234548 vx,vy=0.973579,0.228351
//ang=133 slant=0.23639 vx,vy=0.973179,0.23005
//ang=134 slant=0.238234 vx,vy=0.972776,0.231748
//ang=135 slant=0.240079 vx,vy=0.97237,0.233445
//ang=136 slant=0.241925 vx,vy=0.971961,0.235142
//ang=137 slant=0.243774 vx,vy=0.971549,0.236838
//ang=138 slant=0.245624 vx,vy=0.971134,0.238533
//ang=139 slant=0.247475 vx,vy=0.970716,0.240228
//ang=140 slant=0.249328 vx,vy=0.970296,0.241922
//ang=141 slant=0.251183 vx,vy=0.969872,0.243615
//ang=142 slant=0.253039 vx,vy=0.969445,0.245307
//ang=143 slant=0.254897 vx,vy=0.969016,0.246999
//ang=144 slant=0.256756 vx,vy=0.968583,0.24869
//ang=145 slant=0.258618 vx,vy=0.968148,0.25038
//ang=146 slant=0.26048 vx,vy=0.967709,0.252069
//ang=147 slant=0.262345 vx,vy=0.967268,0.253758
//ang=148 slant=0.264211 vx,vy=0.966823,0.255446
//ang=149 slant=0.266079 vx,vy=0.966376,0.257133
//ang=150 slant=0.267949 vx,vy=0.965926,0.258819
//ang=151 slant=0.269821 vx,vy=0.965473,0.260505
//ang=152 slant=0.271694 vx,vy=0.965016,0.262189
//ang=153 slant=0.273569 vx,vy=0.964557,0.263873
//ang=154 slant=0.275446 vx,vy=0.964095,0.265556
//ang=155 slant=0.277325 vx,vy=0.96363,0.267238
//ang=156 slant=0.279205 vx,vy=0.963163,0.26892
//ang=157 slant=0.281087 vx,vy=0.962692,0.2706
//ang=158 slant=0.282971 vx,vy=0.962218,0.27228
//ang=159 slant=0.284857 vx,vy=0.961741,0.273959
//ang=160 slant=0.286745 vx,vy=0.961262,0.275637
//ang=161 slant=0.288635 vx,vy=0.960779,0.277315
//ang=162 slant=0.290527 vx,vy=0.960294,0.278991
//ang=163 slant=0.29242 vx,vy=0.959805,0.280667
//ang=164 slant=0.294316 vx,vy=0.959314,0.282341
//ang=165 slant=0.296213 vx,vy=0.95882,0.284015
//ang=166 slant=0.298113 vx,vy=0.958323,0.285688
//ang=167 slant=0.300014 vx,vy=0.957822,0.287361
//ang=168 slant=0.301918 vx,vy=0.957319,0.289032
//ang=169 slant=0.303823 vx,vy=0.956814,0.290702
//ang=170 slant=0.305731 vx,vy=0.956305,0.292372
//ang=171 slant=0.30764 vx,vy=0.955793,0.29404
//ang=172 slant=0.309552 vx,vy=0.955278,0.295708
//ang=173 slant=0.311465 vx,vy=0.954761,0.297375
//ang=174 slant=0.313381 vx,vy=0.95424,0.299041
//ang=175 slant=0.315299 vx,vy=0.953717,0.300706
//ang=176 slant=0.317219 vx,vy=0.953191,0.30237
//ang=177 slant=0.319141 vx,vy=0.952661,0.304033
//ang=178 slant=0.321065 vx,vy=0.952129,0.305695
//ang=179 slant=0.322991 vx,vy=0.951594,0.307357
//ang=180 slant=0.32492 vx,vy=0.951057,0.309017
//ang=181 slant=0.32685 vx,vy=0.950516,0.310676
//ang=182 slant=0.328783 vx,vy=0.949972,0.312335
//ang=183 slant=0.330718 vx,vy=0.949425,0.313992
//ang=184 slant=0.332656 vx,vy=0.948876,0.315649
//ang=185 slant=0.334595 vx,vy=0.948324,0.317305
//ang=186 slant=0.336537 vx,vy=0.947768,0.318959
//ang=187 slant=0.338481 vx,vy=0.94721,0.320613
//ang=188 slant=0.340428 vx,vy=0.946649,0.322266
//ang=189 slant=0.342377 vx,vy=0.946085,0.323917
//ang=190 slant=0.344328 vx,vy=0.945519,0.325568
//ang=191 slant=0.346281 vx,vy=0.944949,0.327218
//ang=192 slant=0.348237 vx,vy=0.944376,0.328867
//ang=193 slant=0.350195 vx,vy=0.943801,0.330514
//ang=194 slant=0.352156 vx,vy=0.943223,0.332161
//ang=195 slant=0.354119 vx,vy=0.942641,0.333807
//ang=196 slant=0.356084 vx,vy=0.942057,0.335452
//ang=197 slant=0.358052 vx,vy=0.941471,0.337095
//ang=198 slant=0.360022 vx,vy=0.940881,0.338738
//ang=199 slant=0.361995 vx,vy=0.940288,0.34038
//ang=200 slant=0.36397 vx,vy=0.939693,0.34202
//ang=201 slant=0.365948 vx,vy=0.939094,0.34366
//ang=202 slant=0.367928 vx,vy=0.938493,0.345298
//ang=203 slant=0.369911 vx,vy=0.937889,0.346936
//ang=204 slant=0.371897 vx,vy=0.937282,0.348572
//ang=205 slant=0.373885 vx,vy=0.936672,0.350207
//ang=206 slant=0.375875 vx,vy=0.93606,0.351842
//ang=207 slant=0.377869 vx,vy=0.935444,0.353475
//ang=208 slant=0.379864 vx,vy=0.934826,0.355107
//ang=209 slant=0.381863 vx,vy=0.934204,0.356738
//ang=210 slant=0.383864 vx,vy=0.93358,0.358368
//ang=211 slant=0.385868 vx,vy=0.932954,0.359997
//ang=212 slant=0.387874 vx,vy=0.932324,0.361625
//ang=213 slant=0.389884 vx,vy=0.931691,0.363251
//ang=214 slant=0.391896 vx,vy=0.931056,0.364877
//ang=215 slant=0.39391 vx,vy=0.930418,0.366501
//ang=216 slant=0.395928 vx,vy=0.929776,0.368125
//ang=217 slant=0.397948 vx,vy=0.929133,0.369747
//ang=218 slant=0.399971 vx,vy=0.928486,0.371368
//ang=219 slant=0.401997 vx,vy=0.927836,0.372988
//ang=220 slant=0.404026 vx,vy=0.927184,0.374607
//ang=221 slant=0.406058 vx,vy=0.926529,0.376224
//ang=222 slant=0.408092 vx,vy=0.925871,0.377841
//ang=223 slant=0.41013 vx,vy=0.92521,0.379456
//ang=224 slant=0.41217 vx,vy=0.924546,0.38107
//ang=225 slant=0.414214 vx,vy=0.92388,0.382683
//ang=226 slant=0.41626 vx,vy=0.92321,0.384295
//ang=227 slant=0.418309 vx,vy=0.922538,0.385906
//ang=228 slant=0.420361 vx,vy=0.921863,0.387516
//ang=229 slant=0.422417 vx,vy=0.921185,0.389124
//ang=230 slant=0.424475 vx,vy=0.920505,0.390731
//ang=231 slant=0.426536 vx,vy=0.919821,0.392337
//ang=232 slant=0.428601 vx,vy=0.919135,0.393942
//ang=233 slant=0.430668 vx,vy=0.918446,0.395546
//ang=234 slant=0.432739 vx,vy=0.917755,0.397148
//ang=235 slant=0.434812 vx,vy=0.91706,0.398749
//ang=236 slant=0.436889 vx,vy=0.916363,0.400349
//ang=237 slant=0.438969 vx,vy=0.915663,0.401948
//ang=238 slant=0.441053 vx,vy=0.91496,0.403545
//ang=239 slant=0.443139 vx,vy=0.914254,0.405142
//ang=240 slant=0.445229 vx,vy=0.913545,0.406737
//ang=241 slant=0.447322 vx,vy=0.912834,0.40833
//ang=242 slant=0.449418 vx,vy=0.91212,0.409923
//ang=243 slant=0.451517 vx,vy=0.911403,0.411514
//ang=244 slant=0.45362 vx,vy=0.910684,0.413104
//ang=245 slant=0.455726 vx,vy=0.909961,0.414693
//ang=246 slant=0.457836 vx,vy=0.909236,0.416281
//ang=247 slant=0.459949 vx,vy=0.908508,0.417867
//ang=248 slant=0.462065 vx,vy=0.907777,0.419452
//ang=249 slant=0.464185 vx,vy=0.907044,0.421036
//ang=250 slant=0.466308 vx,vy=0.906308,0.422618
//ang=251 slant=0.468434 vx,vy=0.905569,0.424199
//ang=252 slant=0.470564 vx,vy=0.904827,0.425779
//ang=253 slant=0.472698 vx,vy=0.904083,0.427358
//ang=254 slant=0.474835 vx,vy=0.903335,0.428935
//ang=255 slant=0.476976 vx,vy=0.902585,0.430511
//ang=256 slant=0.47912 vx,vy=0.901833,0.432086
//ang=257 slant=0.481267 vx,vy=0.901077,0.433659
//ang=258 slant=0.483419 vx,vy=0.900319,0.435231
//ang=259 slant=0.485574 vx,vy=0.899558,0.436802
//ang=260 slant=0.487733 vx,vy=0.898794,0.438371
//ang=261 slant=0.489895 vx,vy=0.898028,0.439939
//ang=262 slant=0.492061 vx,vy=0.897258,0.441506
//ang=263 slant=0.494231 vx,vy=0.896486,0.443071
//ang=264 slant=0.496404 vx,vy=0.895712,0.444635
//ang=265 slant=0.498582 vx,vy=0.894934,0.446198
//ang=266 slant=0.500763 vx,vy=0.894154,0.447759
//ang=267 slant=0.502948 vx,vy=0.893371,0.449319
//ang=268 slant=0.505136 vx,vy=0.892586,0.450878
//ang=269 slant=0.507329 vx,vy=0.891798,0.452435
//ang=270 slant=0.509525 vx,vy=0.891007,0.45399
//ang=271 slant=0.511726 vx,vy=0.890213,0.455545
//ang=272 slant=0.51393 vx,vy=0.889416,0.457098
//ang=273 slant=0.516138 vx,vy=0.888617,0.45865
//ang=274 slant=0.518351 vx,vy=0.887815,0.4602
//ang=275 slant=0.520567 vx,vy=0.887011,0.461749
//ang=276 slant=0.522787 vx,vy=0.886204,0.463296
//ang=277 slant=0.525012 vx,vy=0.885394,0.464842
//ang=278 slant=0.52724 vx,vy=0.884581,0.466387
//ang=279 slant=0.529473 vx,vy=0.883766,0.46793
//ang=280 slant=0.531709 vx,vy=0.882948,0.469472
//ang=281 slant=0.53395 vx,vy=0.882127,0.471012
//ang=282 slant=0.536195 vx,vy=0.881303,0.472551
//ang=283 slant=0.538445 vx,vy=0.880477,0.474088
//ang=284 slant=0.540698 vx,vy=0.879649,0.475624
//ang=285 slant=0.542956 vx,vy=0.878817,0.477159
//ang=286 slant=0.545218 vx,vy=0.877983,0.478692
//ang=287 slant=0.547484 vx,vy=0.877146,0.480223
//ang=288 slant=0.549755 vx,vy=0.876307,0.481754
//ang=289 slant=0.55203 vx,vy=0.875465,0.483282
//ang=290 slant=0.554309 vx,vy=0.87462,0.48481
//ang=291 slant=0.556593 vx,vy=0.873772,0.486335
//ang=292 slant=0.558881 vx,vy=0.872922,0.48786
//ang=293 slant=0.561174 vx,vy=0.872069,0.489382
//ang=294 slant=0.563471 vx,vy=0.871214,0.490904
//ang=295 slant=0.565773 vx,vy=0.870356,0.492424
//ang=296 slant=0.568079 vx,vy=0.869495,0.493942
//ang=297 slant=0.57039 vx,vy=0.868632,0.495459
//ang=298 slant=0.572705 vx,vy=0.867765,0.496974
//ang=299 slant=0.575026 vx,vy=0.866897,0.498488
//ang=300 slant=0.57735 vx,vy=0.866025,0.5
//ang=301 slant=0.57968 vx,vy=0.865151,0.501511
//ang=302 slant=0.582014 vx,vy=0.864275,0.50302
//ang=303 slant=0.584353 vx,vy=0.863396,0.504528
//ang=304 slant=0.586697 vx,vy=0.862514,0.506034
//ang=305 slant=0.589045 vx,vy=0.861629,0.507538
//ang=306 slant=0.591398 vx,vy=0.860742,0.509041
//ang=307 slant=0.593757 vx,vy=0.859852,0.510543
//ang=308 slant=0.59612 vx,vy=0.85896,0.512043
//ang=309 slant=0.598488 vx,vy=0.858065,0.513541
//ang=310 slant=0.600861 vx,vy=0.857167,0.515038
//ang=311 slant=0.603239 vx,vy=0.856267,0.516533
//ang=312 slant=0.605622 vx,vy=0.855364,0.518027
//ang=313 slant=0.60801 vx,vy=0.854459,0.519519
//ang=314 slant=0.610403 vx,vy=0.853551,0.52101
//ang=315 slant=0.612801 vx,vy=0.85264,0.522499
//ang=316 slant=0.615204 vx,vy=0.851727,0.523986
//ang=317 slant=0.617613 vx,vy=0.850811,0.525472
//ang=318 slant=0.620026 vx,vy=0.849893,0.526956
//ang=319 slant=0.622445 vx,vy=0.848972,0.528438
//ang=320 slant=0.624869 vx,vy=0.848048,0.529919
//ang=321 slant=0.627299 vx,vy=0.847122,0.531399
//ang=322 slant=0.629734 vx,vy=0.846193,0.532876
//ang=323 slant=0.632174 vx,vy=0.845262,0.534352
//ang=324 slant=0.634619 vx,vy=0.844328,0.535827
//ang=325 slant=0.63707 vx,vy=0.843391,0.5373
//ang=326 slant=0.639527 vx,vy=0.842452,0.538771
//ang=327 slant=0.641989 vx,vy=0.841511,0.54024
//ang=328 slant=0.644456 vx,vy=0.840567,0.541708
//ang=329 slant=0.646929 vx,vy=0.83962,0.543174
//ang=330 slant=0.649408 vx,vy=0.838671,0.544639
//ang=331 slant=0.651892 vx,vy=0.837719,0.546102
//ang=332 slant=0.654382 vx,vy=0.836764,0.547563
//ang=333 slant=0.656877 vx,vy=0.835807,0.549023
//ang=334 slant=0.659379 vx,vy=0.834848,0.550481
//ang=335 slant=0.661886 vx,vy=0.833886,0.551937
//ang=336 slant=0.664398 vx,vy=0.832921,0.553392
//ang=337 slant=0.666917 vx,vy=0.831954,0.554844
//ang=338 slant=0.669442 vx,vy=0.830984,0.556296
//ang=339 slant=0.671972 vx,vy=0.830012,0.557745
//ang=340 slant=0.674509 vx,vy=0.829038,0.559193
//ang=341 slant=0.677051 vx,vy=0.82806,0.560639
//ang=342 slant=0.679599 vx,vy=0.827081,0.562083
//ang=343 slant=0.682154 vx,vy=0.826098,0.563526
//ang=344 slant=0.684714 vx,vy=0.825113,0.564967
//ang=345 slant=0.687281 vx,vy=0.824126,0.566406
//ang=346 slant=0.689854 vx,vy=0.823136,0.567844
//ang=347 slant=0.692433 vx,vy=0.822144,0.56928
//ang=348 slant=0.695018 vx,vy=0.821149,0.570714
//ang=349 slant=0.69761 vx,vy=0.820152,0.572146
//ang=350 slant=0.700208 vx,vy=0.819152,0.573576
//ang=351 slant=0.702812 vx,vy=0.81815,0.575005
//ang=352 slant=0.705422 vx,vy=0.817145,0.576432
//ang=353 slant=0.708039 vx,vy=0.816138,0.577858
//ang=354 slant=0.710663 vx,vy=0.815128,0.579281
//ang=355 slant=0.713293 vx,vy=0.814116,0.580703
//ang=356 slant=0.71593 vx,vy=0.813101,0.582123
//ang=357 slant=0.718573 vx,vy=0.812084,0.583541
//ang=358 slant=0.721223 vx,vy=0.811064,0.584958
//ang=359 slant=0.723879 vx,vy=0.810042,0.586372
//ang=360 slant=0.726543 vx,vy=0.809017,0.587785
//ang=361 slant=0.729213 vx,vy=0.80799,0.589196
//ang=362 slant=0.731889 vx,vy=0.80696,0.590606
//ang=363 slant=0.734573 vx,vy=0.805928,0.592013
//ang=364 slant=0.737264 vx,vy=0.804894,0.593419
//ang=365 slant=0.739961 vx,vy=0.803857,0.594823
//ang=366 slant=0.742666 vx,vy=0.802817,0.596225
//ang=367 slant=0.745377 vx,vy=0.801776,0.597625
//ang=368 slant=0.748096 vx,vy=0.800731,0.599024
//ang=369 slant=0.750821 vx,vy=0.799685,0.60042
//ang=370 slant=0.753554 vx,vy=0.798636,0.601815
//ang=371 slant=0.756294 vx,vy=0.797584,0.603208
//ang=372 slant=0.759041 vx,vy=0.79653,0.604599
//ang=373 slant=0.761796 vx,vy=0.795473,0.605988
//ang=374 slant=0.764558 vx,vy=0.794415,0.607376
//ang=375 slant=0.767327 vx,vy=0.793353,0.608761
//ang=376 slant=0.770104 vx,vy=0.79229,0.610145
//ang=377 slant=0.772888 vx,vy=0.791224,0.611527
//ang=378 slant=0.77568 vx,vy=0.790155,0.612907
//ang=379 slant=0.778479 vx,vy=0.789084,0.614285
//ang=380 slant=0.781286 vx,vy=0.788011,0.615661
//ang=381 slant=0.7841 vx,vy=0.786935,0.617036
//ang=382 slant=0.786922 vx,vy=0.785857,0.618408
//ang=383 slant=0.789752 vx,vy=0.784776,0.619779
//ang=384 slant=0.79259 vx,vy=0.783693,0.621148
//ang=385 slant=0.795436 vx,vy=0.782608,0.622515
//ang=386 slant=0.79829 vx,vy=0.78152,0.62388
//ang=387 slant=0.801151 vx,vy=0.78043,0.625243
//ang=388 slant=0.804021 vx,vy=0.779338,0.626604
//ang=389 slant=0.806898 vx,vy=0.778243,0.627963
//ang=390 slant=0.809784 vx,vy=0.777146,0.62932
//ang=391 slant=0.812678 vx,vy=0.776046,0.630676
//ang=392 slant=0.81558 vx,vy=0.774944,0.632029
//ang=393 slant=0.818491 vx,vy=0.77384,0.633381
//ang=394 slant=0.821409 vx,vy=0.772734,0.634731
//ang=395 slant=0.824336 vx,vy=0.771625,0.636078
//ang=396 slant=0.827272 vx,vy=0.770513,0.637424
//ang=397 slant=0.830216 vx,vy=0.7694,0.638768
//ang=398 slant=0.833169 vx,vy=0.768284,0.64011
//ang=399 slant=0.83613 vx,vy=0.767165,0.64145
//ang=400 slant=0.8391 vx,vy=0.766044,0.642788
//ang=401 slant=0.842078 vx,vy=0.764921,0.644124
//ang=402 slant=0.845066 vx,vy=0.763796,0.645458
//ang=403 slant=0.848062 vx,vy=0.762668,0.64679
//ang=404 slant=0.851067 vx,vy=0.761538,0.64812
//ang=405 slant=0.854081 vx,vy=0.760406,0.649448
//ang=406 slant=0.857104 vx,vy=0.759271,0.650774
//ang=407 slant=0.860136 vx,vy=0.758134,0.652098
//ang=408 slant=0.863177 vx,vy=0.756995,0.653421
//ang=409 slant=0.866227 vx,vy=0.755853,0.654741
//ang=410 slant=0.869287 vx,vy=0.75471,0.656059
//ang=411 slant=0.872356 vx,vy=0.753563,0.657375
//ang=412 slant=0.875434 vx,vy=0.752415,0.658689
//ang=413 slant=0.878521 vx,vy=0.751264,0.660002
//ang=414 slant=0.881619 vx,vy=0.750111,0.661312
//ang=415 slant=0.884725 vx,vy=0.748956,0.66262
//ang=416 slant=0.887842 vx,vy=0.747798,0.663926
//ang=417 slant=0.890967 vx,vy=0.746638,0.66523
//ang=418 slant=0.894103 vx,vy=0.745476,0.666532
//ang=419 slant=0.897249 vx,vy=0.744312,0.667833
//ang=420 slant=0.900404 vx,vy=0.743145,0.669131
//ang=421 slant=0.903569 vx,vy=0.741976,0.670427
//ang=422 slant=0.906745 vx,vy=0.740805,0.671721
//ang=423 slant=0.90993 vx,vy=0.739631,0.673013
//ang=424 slant=0.913125 vx,vy=0.738455,0.674302
//ang=425 slant=0.916331 vx,vy=0.737277,0.67559
//ang=426 slant=0.919547 vx,vy=0.736097,0.676876
//ang=427 slant=0.922773 vx,vy=0.734915,0.67816
//ang=428 slant=0.92601 vx,vy=0.73373,0.679441
//ang=429 slant=0.929257 vx,vy=0.732543,0.680721
//ang=430 slant=0.932515 vx,vy=0.731354,0.681998
//ang=431 slant=0.935783 vx,vy=0.730162,0.683274
//ang=432 slant=0.939063 vx,vy=0.728969,0.684547
//ang=433 slant=0.942352 vx,vy=0.727773,0.685818
//ang=434 slant=0.945653 vx,vy=0.726575,0.687088
//ang=435 slant=0.948965 vx,vy=0.725374,0.688355
//ang=436 slant=0.952287 vx,vy=0.724172,0.68962
//ang=437 slant=0.955621 vx,vy=0.722967,0.690882
//ang=438 slant=0.958966 vx,vy=0.72176,0.692143
//ang=439 slant=0.962322 vx,vy=0.720551,0.693402
//ang=440 slant=0.965689 vx,vy=0.71934,0.694658
//ang=441 slant=0.969067 vx,vy=0.718126,0.695913
//ang=442 slant=0.972458 vx,vy=0.716911,0.697165
//ang=443 slant=0.975859 vx,vy=0.715693,0.698415
//ang=444 slant=0.979272 vx,vy=0.714473,0.699663
//ang=445 slant=0.982697 vx,vy=0.71325,0.700909
//ang=446 slant=0.986134 vx,vy=0.712026,0.702153
//ang=447 slant=0.989582 vx,vy=0.710799,0.703395
//ang=448 slant=0.993043 vx,vy=0.709571,0.704634
//ang=449 slant=0.996515 vx,vy=0.70834,0.705872
//ang=450 slant=1 vx,vy=0.707107,0.707107
//ang=451 slant=1.0035 vx,vy=0.705872,0.70834
//ang=452 slant=1.00701 vx,vy=0.704634,0.709571
//ang=453 slant=1.01053 vx,vy=0.703395,0.710799
//ang=454 slant=1.01406 vx,vy=0.702153,0.712026
//ang=455 slant=1.01761 vx,vy=0.700909,0.71325
//ang=456 slant=1.02117 vx,vy=0.699663,0.714473
//ang=457 slant=1.02474 vx,vy=0.698415,0.715693
//ang=458 slant=1.02832 vx,vy=0.697165,0.716911
//ang=459 slant=1.03192 vx,vy=0.695913,0.718126
//ang=460 slant=1.03553 vx,vy=0.694658,0.71934
//ang=461 slant=1.03915 vx,vy=0.693402,0.720551
//ang=462 slant=1.04279 vx,vy=0.692143,0.72176
//ang=463 slant=1.04644 vx,vy=0.690882,0.722967
//ang=464 slant=1.0501 vx,vy=0.68962,0.724172
//ang=465 slant=1.05378 vx,vy=0.688355,0.725374
//ang=466 slant=1.05747 vx,vy=0.687088,0.726575
//ang=467 slant=1.06117 vx,vy=0.685818,0.727773
//ang=468 slant=1.06489 vx,vy=0.684547,0.728969
//ang=469 slant=1.06862 vx,vy=0.683274,0.730162
//ang=470 slant=1.07237 vx,vy=0.681998,0.731354
//ang=471 slant=1.07613 vx,vy=0.680721,0.732543
//ang=472 slant=1.0799 vx,vy=0.679441,0.73373
//ang=473 slant=1.08369 vx,vy=0.67816,0.734915
//ang=474 slant=1.08749 vx,vy=0.676876,0.736097
//ang=475 slant=1.09131 vx,vy=0.67559,0.737277
//ang=476 slant=1.09514 vx,vy=0.674302,0.738455
//ang=477 slant=1.09899 vx,vy=0.673013,0.739631
//ang=478 slant=1.10285 vx,vy=0.671721,0.740805
//ang=479 slant=1.10672 vx,vy=0.670427,0.741976
//ang=480 slant=1.11061 vx,vy=0.669131,0.743145
//ang=481 slant=1.11452 vx,vy=0.667833,0.744312
//ang=482 slant=1.11844 vx,vy=0.666532,0.745476
//ang=483 slant=1.12238 vx,vy=0.66523,0.746638
//ang=484 slant=1.12633 vx,vy=0.663926,0.747798
//ang=485 slant=1.13029 vx,vy=0.66262,0.748956
//ang=486 slant=1.13428 vx,vy=0.661312,0.750111
//ang=487 slant=1.13828 vx,vy=0.660002,0.751264
//ang=488 slant=1.14229 vx,vy=0.658689,0.752415
//ang=489 slant=1.14632 vx,vy=0.657375,0.753563
//ang=490 slant=1.15037 vx,vy=0.656059,0.75471
//ang=491 slant=1.15443 vx,vy=0.654741,0.755853
//ang=492 slant=1.15851 vx,vy=0.653421,0.756995
//ang=493 slant=1.16261 vx,vy=0.652098,0.758134
//ang=494 slant=1.16672 vx,vy=0.650774,0.759271
//ang=495 slant=1.17085 vx,vy=0.649448,0.760406
//ang=496 slant=1.175 vx,vy=0.64812,0.761538
//ang=497 slant=1.17916 vx,vy=0.64679,0.762668
//ang=498 slant=1.18334 vx,vy=0.645458,0.763796
//ang=499 slant=1.18754 vx,vy=0.644124,0.764921
//ang=500 slant=1.19175 vx,vy=0.642788,0.766044
//ang=501 slant=1.19599 vx,vy=0.64145,0.767165
//ang=502 slant=1.20024 vx,vy=0.64011,0.768284
//ang=503 slant=1.20451 vx,vy=0.638768,0.7694
//ang=504 slant=1.20879 vx,vy=0.637424,0.770513
//ang=505 slant=1.2131 vx,vy=0.636078,0.771625
//ang=506 slant=1.21742 vx,vy=0.634731,0.772734
//ang=507 slant=1.22176 vx,vy=0.633381,0.77384
//ang=508 slant=1.22612 vx,vy=0.632029,0.774944
//ang=509 slant=1.2305 vx,vy=0.630676,0.776046
//ang=510 slant=1.2349 vx,vy=0.62932,0.777146
//ang=511 slant=1.23931 vx,vy=0.627963,0.778243
//ang=512 slant=1.24375 vx,vy=0.626604,0.779338
//ang=513 slant=1.2482 vx,vy=0.625243,0.78043
//ang=514 slant=1.25268 vx,vy=0.62388,0.78152
//ang=515 slant=1.25717 vx,vy=0.622515,0.782608
//ang=516 slant=1.26169 vx,vy=0.621148,0.783693
//ang=517 slant=1.26622 vx,vy=0.619779,0.784776
//ang=518 slant=1.27077 vx,vy=0.618408,0.785857
//ang=519 slant=1.27535 vx,vy=0.617036,0.786935
//ang=520 slant=1.27994 vx,vy=0.615661,0.788011
//ang=521 slant=1.28456 vx,vy=0.614285,0.789084
//ang=522 slant=1.28919 vx,vy=0.612907,0.790155
//ang=523 slant=1.29385 vx,vy=0.611527,0.791224
//ang=524 slant=1.29853 vx,vy=0.610145,0.79229
//ang=525 slant=1.30323 vx,vy=0.608761,0.793353
//ang=526 slant=1.30795 vx,vy=0.607376,0.794415
//ang=527 slant=1.31269 vx,vy=0.605988,0.795473
//ang=528 slant=1.31745 vx,vy=0.604599,0.79653
//ang=529 slant=1.32224 vx,vy=0.603208,0.797584
//ang=530 slant=1.32704 vx,vy=0.601815,0.798636
//ang=531 slant=1.33187 vx,vy=0.60042,0.799685
//ang=532 slant=1.33673 vx,vy=0.599024,0.800731
//ang=533 slant=1.3416 vx,vy=0.597625,0.801776
//ang=534 slant=1.3465 vx,vy=0.596225,0.802817
//ang=535 slant=1.35142 vx,vy=0.594823,0.803857
//ang=536 slant=1.35637 vx,vy=0.593419,0.804894
//ang=537 slant=1.36134 vx,vy=0.592013,0.805928
//ang=538 slant=1.36633 vx,vy=0.590606,0.80696
//ang=539 slant=1.37134 vx,vy=0.589196,0.80799
//ang=540 slant=1.37638 vx,vy=0.587785,0.809017
//ang=541 slant=1.38145 vx,vy=0.586372,0.810042
//ang=542 slant=1.38653 vx,vy=0.584958,0.811064
//ang=543 slant=1.39165 vx,vy=0.583541,0.812084
//ang=544 slant=1.39679 vx,vy=0.582123,0.813101
//ang=545 slant=1.40195 vx,vy=0.580703,0.814116
//ang=546 slant=1.40714 vx,vy=0.579281,0.815128
//ang=547 slant=1.41235 vx,vy=0.577858,0.816138
//ang=548 slant=1.41759 vx,vy=0.576432,0.817145
//ang=549 slant=1.42286 vx,vy=0.575005,0.81815
//ang=550 slant=1.42815 vx,vy=0.573576,0.819152
//ang=551 slant=1.43347 vx,vy=0.572146,0.820152
//ang=552 slant=1.43881 vx,vy=0.570714,0.821149
//ang=553 slant=1.44418 vx,vy=0.56928,0.822144
//ang=554 slant=1.44958 vx,vy=0.567844,0.823136
//ang=555 slant=1.45501 vx,vy=0.566406,0.824126
//ang=556 slant=1.46046 vx,vy=0.564967,0.825113
//ang=557 slant=1.46595 vx,vy=0.563526,0.826098
//ang=558 slant=1.47146 vx,vy=0.562083,0.827081
//ang=559 slant=1.47699 vx,vy=0.560639,0.82806
//ang=560 slant=1.48256 vx,vy=0.559193,0.829038
//ang=561 slant=1.48816 vx,vy=0.557745,0.830012
//ang=562 slant=1.49378 vx,vy=0.556296,0.830984
//ang=563 slant=1.49944 vx,vy=0.554844,0.831954
//ang=564 slant=1.50512 vx,vy=0.553392,0.832921
//ang=565 slant=1.51084 vx,vy=0.551937,0.833886
//ang=566 slant=1.51658 vx,vy=0.550481,0.834848
//ang=567 slant=1.52235 vx,vy=0.549023,0.835807
//ang=568 slant=1.52816 vx,vy=0.547563,0.836764
//ang=569 slant=1.534 vx,vy=0.546102,0.837719
//ang=570 slant=1.53986 vx,vy=0.544639,0.838671
//ang=571 slant=1.54576 vx,vy=0.543174,0.83962
//ang=572 slant=1.5517 vx,vy=0.541708,0.840567
//ang=573 slant=1.55766 vx,vy=0.54024,0.841511
//ang=574 slant=1.56366 vx,vy=0.538771,0.842452
//ang=575 slant=1.56969 vx,vy=0.5373,0.843391
//ang=576 slant=1.57575 vx,vy=0.535827,0.844328
//ang=577 slant=1.58184 vx,vy=0.534352,0.845262
//ang=578 slant=1.58797 vx,vy=0.532876,0.846193
//ang=579 slant=1.59414 vx,vy=0.531399,0.847122
//ang=580 slant=1.60033 vx,vy=0.529919,0.848048
//ang=581 slant=1.60657 vx,vy=0.528438,0.848972
//ang=582 slant=1.61283 vx,vy=0.526956,0.849893
//ang=583 slant=1.61914 vx,vy=0.525472,0.850811
//ang=584 slant=1.62548 vx,vy=0.523986,0.851727
//ang=585 slant=1.63185 vx,vy=0.522499,0.85264
//ang=586 slant=1.63826 vx,vy=0.52101,0.853551
//ang=587 slant=1.64471 vx,vy=0.519519,0.854459
//ang=588 slant=1.6512 vx,vy=0.518027,0.855364
//ang=589 slant=1.65772 vx,vy=0.516533,0.856267
//ang=590 slant=1.66428 vx,vy=0.515038,0.857167
//ang=591 slant=1.67088 vx,vy=0.513541,0.858065
//ang=592 slant=1.67752 vx,vy=0.512043,0.85896
//ang=593 slant=1.68419 vx,vy=0.510543,0.859852
//ang=594 slant=1.69091 vx,vy=0.509041,0.860742
//ang=595 slant=1.69766 vx,vy=0.507538,0.861629
//ang=596 slant=1.70446 vx,vy=0.506034,0.862514
//ang=597 slant=1.71129 vx,vy=0.504528,0.863396
//ang=598 slant=1.71817 vx,vy=0.50302,0.864275
//ang=599 slant=1.72509 vx,vy=0.501511,0.865151
//ang=600 slant=1.73205 vx,vy=0.5,0.866025
//ang=601 slant=1.73905 vx,vy=0.498488,0.866897
//ang=602 slant=1.7461 vx,vy=0.496974,0.867765
//ang=603 slant=1.75319 vx,vy=0.495459,0.868632
//ang=604 slant=1.76032 vx,vy=0.493942,0.869495
//ang=605 slant=1.76749 vx,vy=0.492424,0.870356
//ang=606 slant=1.77471 vx,vy=0.490904,0.871214
//ang=607 slant=1.78198 vx,vy=0.489382,0.872069
//ang=608 slant=1.78929 vx,vy=0.48786,0.872922
//ang=609 slant=1.79665 vx,vy=0.486335,0.873772
//ang=610 slant=1.80405 vx,vy=0.48481,0.87462
//ang=611 slant=1.8115 vx,vy=0.483282,0.875465
//ang=612 slant=1.81899 vx,vy=0.481754,0.876307
//ang=613 slant=1.82654 vx,vy=0.480223,0.877146
//ang=614 slant=1.83413 vx,vy=0.478692,0.877983
//ang=615 slant=1.84177 vx,vy=0.477159,0.878817
//ang=616 slant=1.84946 vx,vy=0.475624,0.879649
//ang=617 slant=1.8572 vx,vy=0.474088,0.880477
//ang=618 slant=1.86499 vx,vy=0.472551,0.881303
//ang=619 slant=1.87283 vx,vy=0.471012,0.882127
//ang=620 slant=1.88073 vx,vy=0.469472,0.882948
//ang=621 slant=1.88867 vx,vy=0.46793,0.883766
//ang=622 slant=1.89667 vx,vy=0.466387,0.884581
//ang=623 slant=1.90472 vx,vy=0.464842,0.885394
//ang=624 slant=1.91282 vx,vy=0.463296,0.886204
//ang=625 slant=1.92098 vx,vy=0.461749,0.887011
//ang=626 slant=1.9292 vx,vy=0.4602,0.887815
//ang=627 slant=1.93746 vx,vy=0.45865,0.888617
//ang=628 slant=1.94579 vx,vy=0.457098,0.889416
//ang=629 slant=1.95417 vx,vy=0.455545,0.890213
//ang=630 slant=1.96261 vx,vy=0.45399,0.891007
//ang=631 slant=1.97111 vx,vy=0.452435,0.891798
//ang=632 slant=1.97966 vx,vy=0.450878,0.892586
//ang=633 slant=1.98828 vx,vy=0.449319,0.893371
//ang=634 slant=1.99695 vx,vy=0.447759,0.894154
//ang=635 slant=2.00569 vx,vy=0.446198,0.894934
//ang=636 slant=2.01449 vx,vy=0.444635,0.895712
//ang=637 slant=2.02335 vx,vy=0.443071,0.896486
//ang=638 slant=2.03227 vx,vy=0.441506,0.897258
//ang=639 slant=2.04125 vx,vy=0.439939,0.898028
//ang=640 slant=2.0503 vx,vy=0.438371,0.898794
//ang=641 slant=2.05942 vx,vy=0.436802,0.899558
//ang=642 slant=2.0686 vx,vy=0.435231,0.900319
//ang=643 slant=2.07785 vx,vy=0.433659,0.901077
//ang=644 slant=2.08716 vx,vy=0.432086,0.901833
//ang=645 slant=2.09654 vx,vy=0.430511,0.902585
//ang=646 slant=2.106 vx,vy=0.428935,0.903335
//ang=647 slant=2.11552 vx,vy=0.427358,0.904083
//ang=648 slant=2.12511 vx,vy=0.425779,0.904827
//ang=649 slant=2.13477 vx,vy=0.424199,0.905569
//ang=650 slant=2.14451 vx,vy=0.422618,0.906308
//ang=651 slant=2.15432 vx,vy=0.421036,0.907044
//ang=652 slant=2.1642 vx,vy=0.419452,0.907777
//ang=653 slant=2.17416 vx,vy=0.417867,0.908508
//ang=654 slant=2.18419 vx,vy=0.416281,0.909236
//ang=655 slant=2.1943 vx,vy=0.414693,0.909961
//ang=656 slant=2.20449 vx,vy=0.413104,0.910684
//ang=657 slant=2.21475 vx,vy=0.411514,0.911403
//ang=658 slant=2.2251 vx,vy=0.409923,0.91212
//ang=659 slant=2.23553 vx,vy=0.40833,0.912834
//ang=660 slant=2.24604 vx,vy=0.406737,0.913545
//ang=661 slant=2.25663 vx,vy=0.405142,0.914254
//ang=662 slant=2.2673 vx,vy=0.403545,0.91496
//ang=663 slant=2.27806 vx,vy=0.401948,0.915663
//ang=664 slant=2.28891 vx,vy=0.400349,0.916363
//ang=665 slant=2.29984 vx,vy=0.398749,0.91706
//ang=666 slant=2.31086 vx,vy=0.397148,0.917755
//ang=667 slant=2.32197 vx,vy=0.395546,0.918446
//ang=668 slant=2.33317 vx,vy=0.393942,0.919135
//ang=669 slant=2.34447 vx,vy=0.392337,0.919821
//ang=670 slant=2.35585 vx,vy=0.390731,0.920505
//ang=671 slant=2.36733 vx,vy=0.389124,0.921185
//ang=672 slant=2.37891 vx,vy=0.387516,0.921863
//ang=673 slant=2.39058 vx,vy=0.385906,0.922538
//ang=674 slant=2.40235 vx,vy=0.384295,0.92321
//ang=675 slant=2.41421 vx,vy=0.382683,0.92388
//ang=676 slant=2.42618 vx,vy=0.38107,0.924546
//ang=677 slant=2.43825 vx,vy=0.379456,0.92521
//ang=678 slant=2.45043 vx,vy=0.377841,0.925871
//ang=679 slant=2.4627 vx,vy=0.376224,0.926529
//ang=680 slant=2.47509 vx,vy=0.374607,0.927184
//ang=681 slant=2.48758 vx,vy=0.372988,0.927836
//ang=682 slant=2.50018 vx,vy=0.371368,0.928486
//ang=683 slant=2.51289 vx,vy=0.369747,0.929133
//ang=684 slant=2.52571 vx,vy=0.368125,0.929776
//ang=685 slant=2.53865 vx,vy=0.366501,0.930418
//ang=686 slant=2.5517 vx,vy=0.364877,0.931056
//ang=687 slant=2.56487 vx,vy=0.363251,0.931691
//ang=688 slant=2.57815 vx,vy=0.361625,0.932324
//ang=689 slant=2.59156 vx,vy=0.359997,0.932954
//ang=690 slant=2.60509 vx,vy=0.358368,0.93358
//ang=691 slant=2.61874 vx,vy=0.356738,0.934204
//ang=692 slant=2.63252 vx,vy=0.355107,0.934826
//ang=693 slant=2.64642 vx,vy=0.353475,0.935444
//ang=694 slant=2.66046 vx,vy=0.351842,0.93606
//ang=695 slant=2.67462 vx,vy=0.350207,0.936672
//ang=696 slant=2.68892 vx,vy=0.348572,0.937282
//ang=697 slant=2.70335 vx,vy=0.346936,0.937889
//ang=698 slant=2.71792 vx,vy=0.345298,0.938493
//ang=699 slant=2.73263 vx,vy=0.34366,0.939094
//ang=700 slant=2.74748 vx,vy=0.34202,0.939693
//ang=701 slant=2.76247 vx,vy=0.34038,0.940288
//ang=702 slant=2.77761 vx,vy=0.338738,0.940881
//ang=703 slant=2.79289 vx,vy=0.337095,0.941471
//ang=704 slant=2.80833 vx,vy=0.335452,0.942057
//ang=705 slant=2.82391 vx,vy=0.333807,0.942641
//ang=706 slant=2.83965 vx,vy=0.332161,0.943223
//ang=707 slant=2.85555 vx,vy=0.330514,0.943801
//ang=708 slant=2.87161 vx,vy=0.328867,0.944376
//ang=709 slant=2.88783 vx,vy=0.327218,0.944949
//ang=710 slant=2.90421 vx,vy=0.325568,0.945519
//ang=711 slant=2.92076 vx,vy=0.323917,0.946085
//ang=712 slant=2.93748 vx,vy=0.322266,0.946649
//ang=713 slant=2.95437 vx,vy=0.320613,0.94721
//ang=714 slant=2.97144 vx,vy=0.318959,0.947768
//ang=715 slant=2.98868 vx,vy=0.317305,0.948324
//ang=716 slant=3.00611 vx,vy=0.315649,0.948876
//ang=717 slant=3.02372 vx,vy=0.313992,0.949425
//ang=718 slant=3.04152 vx,vy=0.312335,0.949972
//ang=719 slant=3.0595 vx,vy=0.310676,0.950516
//ang=720 slant=3.07768 vx,vy=0.309017,0.951057
//ang=721 slant=3.09606 vx,vy=0.307357,0.951594
//ang=722 slant=3.11464 vx,vy=0.305695,0.952129
//ang=723 slant=3.13341 vx,vy=0.304033,0.952661
//ang=724 slant=3.1524 vx,vy=0.30237,0.953191
//ang=725 slant=3.17159 vx,vy=0.300706,0.953717
//ang=726 slant=3.191 vx,vy=0.299041,0.95424
//ang=727 slant=3.21063 vx,vy=0.297375,0.954761
//ang=728 slant=3.23048 vx,vy=0.295708,0.955278
//ang=729 slant=3.25055 vx,vy=0.29404,0.955793
//ang=730 slant=3.27085 vx,vy=0.292372,0.956305
//ang=731 slant=3.29139 vx,vy=0.290702,0.956814
//ang=732 slant=3.31216 vx,vy=0.289032,0.957319
//ang=733 slant=3.33317 vx,vy=0.287361,0.957822
//ang=734 slant=3.35443 vx,vy=0.285688,0.958323
//ang=735 slant=3.37594 vx,vy=0.284015,0.95882
//ang=736 slant=3.39771 vx,vy=0.282341,0.959314
//ang=737 slant=3.41973 vx,vy=0.280667,0.959805
//ang=738 slant=3.44202 vx,vy=0.278991,0.960294
//ang=739 slant=3.46458 vx,vy=0.277315,0.960779
//ang=740 slant=3.48741 vx,vy=0.275637,0.961262
//ang=741 slant=3.51053 vx,vy=0.273959,0.961741
//ang=742 slant=3.53393 vx,vy=0.27228,0.962218
//ang=743 slant=3.55761 vx,vy=0.2706,0.962692
//ang=744 slant=3.5816 vx,vy=0.26892,0.963163
//ang=745 slant=3.60588 vx,vy=0.267238,0.96363
//ang=746 slant=3.63048 vx,vy=0.265556,0.964095
//ang=747 slant=3.65538 vx,vy=0.263873,0.964557
//ang=748 slant=3.68061 vx,vy=0.262189,0.965016
//ang=749 slant=3.70616 vx,vy=0.260505,0.965473
//ang=750 slant=3.73205 vx,vy=0.258819,0.965926
//ang=751 slant=3.75828 vx,vy=0.257133,0.966376
//ang=752 slant=3.78485 vx,vy=0.255446,0.966823
//ang=753 slant=3.81177 vx,vy=0.253758,0.967268
//ang=754 slant=3.83906 vx,vy=0.252069,0.967709
//ang=755 slant=3.86671 vx,vy=0.25038,0.968148
//ang=756 slant=3.89474 vx,vy=0.24869,0.968583
//ang=757 slant=3.92316 vx,vy=0.246999,0.969016
//ang=758 slant=3.95196 vx,vy=0.245307,0.969445
//ang=759 slant=3.98117 vx,vy=0.243615,0.969872
//ang=760 slant=4.01078 vx,vy=0.241922,0.970296
//ang=761 slant=4.04081 vx,vy=0.240228,0.970716
//ang=762 slant=4.07127 vx,vy=0.238533,0.971134
//ang=763 slant=4.10216 vx,vy=0.236838,0.971549
//ang=764 slant=4.1335 vx,vy=0.235142,0.971961
//ang=765 slant=4.1653 vx,vy=0.233445,0.97237
//ang=766 slant=4.19756 vx,vy=0.231748,0.972776
//ang=767 slant=4.2303 vx,vy=0.23005,0.973179
//ang=768 slant=4.26352 vx,vy=0.228351,0.973579
//ang=769 slant=4.29724 vx,vy=0.226651,0.973976
//ang=770 slant=4.33148 vx,vy=0.224951,0.97437
//ang=771 slant=4.36623 vx,vy=0.22325,0.974761
//ang=772 slant=4.40152 vx,vy=0.221548,0.975149
//ang=773 slant=4.43735 vx,vy=0.219846,0.975535
//ang=774 slant=4.47374 vx,vy=0.218143,0.975917
//ang=775 slant=4.51071 vx,vy=0.21644,0.976296
//ang=776 slant=4.54826 vx,vy=0.214735,0.976672
//ang=777 slant=4.58641 vx,vy=0.21303,0.977046
//ang=778 slant=4.62518 vx,vy=0.211325,0.977416
//ang=779 slant=4.66458 vx,vy=0.209619,0.977783
//ang=780 slant=4.70463 vx,vy=0.207912,0.978148
//ang=781 slant=4.74534 vx,vy=0.206204,0.978509
//ang=782 slant=4.78673 vx,vy=0.204496,0.978867
//ang=783 slant=4.82882 vx,vy=0.202787,0.979223
//ang=784 slant=4.87162 vx,vy=0.201078,0.979575
//ang=785 slant=4.91516 vx,vy=0.199368,0.979925
//ang=786 slant=4.95945 vx,vy=0.197657,0.980271
//ang=787 slant=5.00451 vx,vy=0.195946,0.980615
//ang=788 slant=5.05037 vx,vy=0.194234,0.980955
//ang=789 slant=5.09704 vx,vy=0.192522,0.981293
//ang=790 slant=5.14455 vx,vy=0.190809,0.981627
//ang=791 slant=5.19293 vx,vy=0.189095,0.981959
//ang=792 slant=5.24218 vx,vy=0.187381,0.982287
//ang=793 slant=5.29235 vx,vy=0.185667,0.982613
//ang=794 slant=5.34345 vx,vy=0.183951,0.982935
//ang=795 slant=5.39552 vx,vy=0.182236,0.983255
//ang=796 slant=5.44857 vx,vy=0.180519,0.983571
//ang=797 slant=5.50264 vx,vy=0.178802,0.983885
//ang=798 slant=5.55777 vx,vy=0.177085,0.984196
//ang=799 slant=5.61397 vx,vy=0.175367,0.984503
//ang=800 slant=5.67128 vx,vy=0.173648,0.984808
//ang=801 slant=5.72974 vx,vy=0.171929,0.985109
//ang=802 slant=5.78938 vx,vy=0.170209,0.985408
//ang=803 slant=5.85024 vx,vy=0.168489,0.985703
//ang=804 slant=5.91236 vx,vy=0.166769,0.985996
//ang=805 slant=5.97576 vx,vy=0.165048,0.986286
//ang=806 slant=6.04051 vx,vy=0.163326,0.986572
//ang=807 slant=6.10664 vx,vy=0.161604,0.986856
//ang=808 slant=6.17419 vx,vy=0.159881,0.987136
//ang=809 slant=6.24321 vx,vy=0.158158,0.987414
//ang=810 slant=6.31375 vx,vy=0.156434,0.987688
//ang=811 slant=6.38587 vx,vy=0.15471,0.98796
//ang=812 slant=6.45961 vx,vy=0.152986,0.988228
//ang=813 slant=6.53503 vx,vy=0.151261,0.988494
//ang=814 slant=6.61219 vx,vy=0.149535,0.988756
//ang=815 slant=6.69116 vx,vy=0.147809,0.989016
//ang=816 slant=6.77199 vx,vy=0.146083,0.989272
//ang=817 slant=6.85475 vx,vy=0.144356,0.989526
//ang=818 slant=6.93952 vx,vy=0.142629,0.989776
//ang=819 slant=7.02637 vx,vy=0.140901,0.990024
//ang=820 slant=7.11537 vx,vy=0.139173,0.990268
//ang=821 slant=7.20661 vx,vy=0.137445,0.990509
//ang=822 slant=7.30018 vx,vy=0.135716,0.990748
//ang=823 slant=7.39616 vx,vy=0.133986,0.990983
//ang=824 slant=7.49465 vx,vy=0.132256,0.991216
//ang=825 slant=7.59575 vx,vy=0.130526,0.991445
//ang=826 slant=7.69957 vx,vy=0.128796,0.991671
//ang=827 slant=7.80622 vx,vy=0.127065,0.991894
//ang=828 slant=7.91582 vx,vy=0.125333,0.992115
//ang=829 slant=8.02848 vx,vy=0.123601,0.992332
//ang=830 slant=8.14435 vx,vy=0.121869,0.992546
//ang=831 slant=8.26355 vx,vy=0.120137,0.992757
//ang=832 slant=8.38625 vx,vy=0.118404,0.992966
//ang=833 slant=8.51259 vx,vy=0.116671,0.993171
//ang=834 slant=8.64275 vx,vy=0.114937,0.993373
//ang=835 slant=8.77689 vx,vy=0.113203,0.993572
//ang=836 slant=8.9152 vx,vy=0.111469,0.993768
//ang=837 slant=9.05789 vx,vy=0.109734,0.993961
//ang=838 slant=9.20516 vx,vy=0.107999,0.994151
//ang=839 slant=9.35724 vx,vy=0.106264,0.994338
//ang=840 slant=9.51436 vx,vy=0.104528,0.994522
//ang=841 slant=9.6768 vx,vy=0.102793,0.994703
//ang=842 slant=9.84482 vx,vy=0.101056,0.994881
//ang=843 slant=10.0187 vx,vy=0.0993197,0.995056
//ang=844 slant=10.1988 vx,vy=0.0975829,0.995227
//ang=845 slant=10.3854 vx,vy=0.0958458,0.995396
//ang=846 slant=10.5789 vx,vy=0.0941083,0.995562
//ang=847 slant=10.7797 vx,vy=0.0923706,0.995725
//ang=848 slant=10.9882 vx,vy=0.0906326,0.995884
//ang=849 slant=11.2048 vx,vy=0.0888943,0.996041
//ang=850 slant=11.4301 vx,vy=0.0871557,0.996195
//ang=851 slant=11.6645 vx,vy=0.0854169,0.996345
//ang=852 slant=11.9087 vx,vy=0.0836778,0.996493
//ang=853 slant=12.1632 vx,vy=0.0819385,0.996637
//ang=854 slant=12.4288 vx,vy=0.0801989,0.996779
//ang=855 slant=12.7062 vx,vy=0.0784591,0.996917
//ang=856 slant=12.9962 vx,vy=0.076719,0.997053
//ang=857 slant=13.2996 vx,vy=0.0749787,0.997185
//ang=858 slant=13.6174 vx,vy=0.0732382,0.997314
//ang=859 slant=13.9507 vx,vy=0.0714974,0.997441
//ang=860 slant=14.3007 vx,vy=0.0697565,0.997564
//ang=861 slant=14.6685 vx,vy=0.0680153,0.997684
//ang=862 slant=15.0557 vx,vy=0.0662739,0.997801
//ang=863 slant=15.4638 vx,vy=0.0645323,0.997916
//ang=864 slant=15.8945 vx,vy=0.0627905,0.998027
//ang=865 slant=16.3499 vx,vy=0.0610485,0.998135
//ang=866 slant=16.8319 vx,vy=0.0593064,0.99824
//ang=867 slant=17.3432 vx,vy=0.057564,0.998342
//ang=868 slant=17.8863 vx,vy=0.0558215,0.998441
//ang=869 slant=18.4645 vx,vy=0.0540788,0.998537
//ang=870 slant=19.0811 vx,vy=0.052336,0.99863
//ang=871 slant=19.7403 vx,vy=0.0505929,0.998719
//ang=872 slant=20.4465 vx,vy=0.0488498,0.998806
//ang=873 slant=21.2049 vx,vy=0.0471065,0.99889
//ang=874 slant=22.0217 vx,vy=0.045363,0.998971
//ang=875 slant=22.9038 vx,vy=0.0436194,0.999048
//ang=876 slant=23.8593 vx,vy=0.0418757,0.999123
//ang=877 slant=24.8978 vx,vy=0.0401318,0.999194
//ang=878 slant=26.0307 vx,vy=0.0383878,0.999263
//ang=879 slant=27.2715 vx,vy=0.0366437,0.999328
//ang=880 slant=28.6363 vx,vy=0.0348995,0.999391
//ang=881 slant=30.1446 vx,vy=0.0331552,0.99945
//ang=882 slant=31.8205 vx,vy=0.0314108,0.999507
//ang=883 slant=33.6935 vx,vy=0.0296662,0.99956
//ang=884 slant=35.8006 vx,vy=0.0279216,0.99961
//ang=885 slant=38.1885 vx,vy=0.0261769,0.999657
//ang=886 slant=40.9174 vx,vy=0.0244322,0.999701
//ang=887 slant=44.0661 vx,vy=0.0226873,0.999743
//ang=888 slant=47.7395 vx,vy=0.0209424,0.999781
//ang=889 slant=52.0807 vx,vy=0.0191974,0.999816
//ang=890 slant=57.29 vx,vy=0.0174524,0.999848
//ang=891 slant=63.6567 vx,vy=0.0157073,0.999877
//ang=892 slant=71.6151 vx,vy=0.0139622,0.999903
//ang=893 slant=81.847 vx,vy=0.012217,0.999925
//ang=894 slant=95.4895 vx,vy=0.0104718,0.999945
//ang=895 slant=114.589 vx,vy=0.00872654,0.999962
//ang=896 slant=143.237 vx,vy=0.00698126,0.999976
//ang=897 slant=190.984 vx,vy=0.00523596,0.999986
//ang=898 slant=286.478 vx,vy=0.00349065,0.999994
//ang=899 slant=572.957 vx,vy=0.00174533,0.999998

