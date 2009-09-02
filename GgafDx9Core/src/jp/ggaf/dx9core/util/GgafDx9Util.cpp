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
            //PARABORA[0] = 0 , PARABORA[S_ANG180] = 1,  PARABORA[S_ANG360-1] = 0 で y = -x^2  放物線の値をとる
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

    }
}

angle GgafDx9Util::getAngle2D(int prm_vx, int prm_vy) {
    if (prm_vy == 0) {
        if (prm_vx > 0) {
            return 0;
        } else if (prm_vx < 0) {
            return ANGLE180;
        } else {
            //(0,0)のベクトル方向は無い
            //しかたないので 0
            return 0;
        }
    } else if (prm_vx == 0) {
        if (prm_vy > 0) {
            return ANGLE90;
        } else if (prm_vy < 0) {
            return ANGLE270;
        } else {
            //(0,0)のベクトル方向は無い
            //しかたないので 0
            return 0;
        }
    } else {

        //バイナリーサーチで直近を探す
        static s_ang left, right, middle;
        if (prm_vx > 0 && prm_vy > 0) { //第1象限
            left = 1;
            right = S_ANG90 - 1;
        } else if (prm_vx < 0 && prm_vy > 0) { //第2象限
            left = S_ANG90 + 1;
            right = S_ANG180 - 1;
        } else if (prm_vx < 0 && prm_vy < 0) { //第3象限
            left = S_ANG180 + 1;
            right = S_ANG270 - 1;
        } else if (prm_vx > 0 && prm_vy < 0) { //第4象限
            left = S_ANG270 + 1;
            right = S_ANG360 - 1;
        } else {
            //ぴったり重なっている場合
            return 0; //仕方ないので0
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

// 線分の当たり判定 (x11,y11)-(x12,y12) × (x21,y21)-(x22,y22)
bool GgafDx9Util::chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {

    //x座標によるチェック
    if (x11 >= x12) {
        if ((x11 < x21 && x11 < x22) || (x12 > x21 && x12 > x22)) {
            return false;
        }
    } else {
        if ((x12 < x21 && x12 < x22) || (x11 > x21 && x11 > x22)) {
            return false;
        }
    }
    //y座標によるチェック
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
    //vx,vy,vz を正規化する。
    //求める単位ベクトルを (X,Y,Z) とすると (X,Y,Z) = t(vx,vy,vz)
    //関係式   X=t*vx; Y=t*vy; Z=t*vz; ･･･ (1) を得る
    //単位球は X^2 + Y^2 + Z^2 = 1 ･･･(2)
    //(1)(2)を連立させて、t について解く。
    //t = 1 / sqrt(vx^2 + vy^2 + vz^2)
    t = 1 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    //求めた t を (1) に代入し (X,Y,Z) を求める。
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;

    //GgafDx9SphereRadiusVectors を使って単位ベクトルから回転角をもとめる
    //但し GgafDx9SphereRadiusVectors のベクトル精度は 10000を乗じた整数である。(LEN_UNIT*10)
    //さらに、引数のベクトル要素は全て正の値（1/8 の球分）だけなのです。よって、いろいろ場合わけする。

    static s_ang rZ, rY;
    _srv.getRotAngleClosely(
            (unsigned __int16) abs(out_nvx*10000),
            (unsigned __int16) abs(out_nvy*10000),
            (unsigned __int16) abs(out_nvz*10000),
            rZ,
            rY
    );

    //x > 0; y > 0; z > 0 の領域を第一象限とする
    //x < 0; y > 0; z > 0 の領域を第二象限とする
    //x < 0; y < 0; z > 0 の領域を第三象限とする
    //x > 0; y < 0; z > 0 の領域を第四象限とする
    //x > 0; y > 0; z < 0 の領域を第五象限とする
    //x < 0; y > 0; z < 0 の領域を第六象限とする
    //x < 0; y < 0; z < 0 の領域を第七象限とする
    //x > 0; y < 0; z < 0 の領域を第八象限とする
    //象限によって回転角を補正
    if (vx >= 0 && vy >= 0 && vz >= 0) { //第一象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //第二象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //第三象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //第四象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //第五象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //第六象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //第七象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //第八象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else {
        _TRACE_("おかしいですぜ");
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
    if (vx >= 0 && vy >= 0 && vz >= 0) { //第一象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //第二象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //第三象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //第四象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //第五象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //第六象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //第七象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //第八象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else {
        _TRACE_("おかしいですぜ");
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
    if (vx >= 0 && vy >= 0 && vz >= 0) { //第一象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //第二象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //第三象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //第四象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //第五象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //第六象限
        out_angRotZ = rZ * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //第七象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //第八象限
        out_angRotZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angRotY = rY * ANGLE_RATE;
    } else {
        _TRACE_("おかしいですぜ");
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
    //回転角によって象限を考慮し、getVectorCloselyのパラメータ角(< 900)を出す
    static int Xsign, Ysign, Zsign;
    static s_ang rZ, rY;

    if (0 <= prm_angRotZ && prm_angRotZ < ANGLE90) {
        rZ = (prm_angRotZ - ANGLE0) / ANGLE_RATE;
        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //第五象限
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //第六象限
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //第二象限
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //第一象限
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        }
    } else if (ANGLE90 <= prm_angRotZ && prm_angRotZ < ANGLE180) {
        rZ = (ANGLE180 - prm_angRotZ) / ANGLE_RATE;

        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //第二象限
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //第一象限
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //第五象限
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //第六象限
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        }

    } else if (ANGLE180 <= prm_angRotZ && prm_angRotZ < ANGLE270) {
        rZ = (prm_angRotZ - ANGLE180) / ANGLE_RATE;
        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //第三象限
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //第四象限
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //第八象限
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //第七象限
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        }
    } else if (ANGLE270 <= prm_angRotZ && prm_angRotZ < ANGLE360) {
        rZ = (ANGLE360 - prm_angRotZ) / ANGLE_RATE;
        if (0 <= prm_angRotY && prm_angRotY < ANGLE90) { //第八象限
            rY = prm_angRotY / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angRotY && prm_angRotY < ANGLE180) { //第七象限
            rY = (ANGLE180 - prm_angRotY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angRotY && prm_angRotY < ANGLE270) { //第三象限
            rY = (prm_angRotY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angRotY && prm_angRotY <= ANGLE360) { //第四象限
            rY = (ANGLE360 - prm_angRotY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        }
    } else {
        _TRACE_("getNormalizeVectorZY: なんかおかしいですぜ");
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

