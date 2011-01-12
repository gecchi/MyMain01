#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;



//角度の種類の変数名の命名。忘れないようメモ(2009/10/21)
//
//変数名と種類
//
//基本的に度数法（0°～360°）を使用している。
//ang または angle と変数名にある場合、ラジアンではなくて度数法での角度数値が入る。
//（ラジアンの場合はradと書くようにしている）
//但し精度が場合によってまちまちである。
//キャラがもつ angle値は 0 ～ 360,000 で 値の上では度数法の1000倍の精度を持つ。一応これが基本。
//s_ang は計算用、テーブルインデックス用に精度を落とすため、angle値を100で割って  0 ～ 3600 にした単位系。
//
//次に軸回転と平面の中心角の表現区別について
//＜軸回転の角度の変数名表現＞
//軸回転は rot または r で書くようにする。 angRx とか、とにかく "R" か "r" が変数名に入ってる
//＜例＞
//angRx rotX rX Rx rX radRx ・・・ X軸回転に関連している変数名
//angRy rotY rY Ry rY radRy ・・・ Y軸回転に関連している変数名
//angRz rotZ rX Rz rZ radRz ・・・ Z軸回転に関連している変数名
//これらもその時々により精度が変わっているかもしれない。
//また左手系(X軸は右へ行くと正、Y軸は上に行くと正、Z軸は奥へ行くと正）を前提としているため、
//これらの軸回転angle値の正の値とは通常は、軸を向いて反時計回りの方向を表す。
//X軸回転値 ・・・ X軸の正の方向を向いて左回りが正の回転角度
//Y軸回転値 ・・・ Y軸の正の方向を向いて左回りが正の回転角度
//Z軸回転値 ・・・ Z軸の正の方向を向いて左回りが正の回転角度
//
//＜平面の中心角、または直線の成す角度の変数名表現＞
//ある平面系に対しての中心角はどの平面かを書くようにする。
//
//angXY ・・・XY平面での中心角の値。正の角度とは X軸の正の方向を右、Y軸の正の方向を上にした２次元平面で、３時の方向 (x,y)=(1,0)を角度0°とし、原点を中心に反時計回り
//angXZ ・・・XZ平面での中心角の値。正の角度とは X軸の正の方向を右、Z軸の正の方向を上にした２次元平面で、３時の方向 (x,z)=(1,0)を角度0°とし、原点を中心に反時計回り
//angZX ・・・ZX平面での中心角の値。正の角度とは Z軸の正の方向を右、X軸の正の方向を上にした２次元平面で、３時の方向 (z,x)=(1,0)を角度0°とし、原点を中心に反時計回り
//ここで注意は、
//angXY → Z軸回転値
//angZX → Y軸回転値
//と読み替えれるが、angXZはY軸回転値の正負が逆になること、どのように「平面と見る」か姿勢が違うため。
//
//＜平面の中心角、または直線の成す角度を、軸回転とみなして計算する場合の変数名表現＞
//angXY は ３次元空間の Z=0 のXY平面上に限り、angRz とみなすことが出来ます。
//このようにして計算を行っている箇所があり、
//「平面の中心角、または直線の成す角度 として値を求めたけども、軸回転として読み替えた、或いは、使いたかった」
//という場合は rotXY という変数にしています。
//つまり rotXY = angXY or angRz
//angXY -> angRz は角度0°の位置(方向ベクトル(x,y,z)=(1,0,0))、正の回転方向が一致するのでわかりやすいです。

//「めも」
//angXZ -> angRy の読み替えは正の回転方向が angXZ と angRy で逆になってしまいます。
//angZX -> angRy の場合は正の回転方向は一致しますが、角度0°の位置が(x,y,z)=(1,0,0) ではなくなってしまうため、キャラの軸回転には向きません
//
//そこで
//rotXZ = angXZ or angRy_rev
//のように "rev" 「逆周りですよ」と書くようにした。角度0°の位置を優先した結果、こんなややこしいことになっている！



bool GgafDx9Util::_was_inited_flg = false;

float GgafDx9Util::PARABORA[S_ANG360+1];
float GgafDx9Util::COS[S_ANG360+1];
float GgafDx9Util::SIN[S_ANG360+1];
float GgafDx9Util::RAD[S_ANG360+1];

float GgafDx9Util::ROOT_1_MINUS_XX[1000];


angle GgafDx9Util::SLANT2ANG[100000 + 1];

//こんなんいるのでは！
//angle GgafDx9Util::PROJANG_XY_ZX_YZ_TO_ROTANG_Z[S_ANG90+1][S_ANG90+1];


angle GgafDx9Util::PROJANG_XY_XZ_TO_ROTANG_Z[S_ANG90+1][S_ANG90+1];
angle GgafDx9Util::PROJANG_XY_XZ_TO_ROTANG_Y_REV[S_ANG90+1][S_ANG90+1];
angle GgafDx9Util::PROJANG_ZY_ZX_TO_ROTANG_X_REV[S_ANG90+1][S_ANG90+1];
angle GgafDx9Util::PROJANG_ZY_ZX_TO_ROTANG_Y[S_ANG90+1][S_ANG90+1];

GgafDx9SphereRadiusVectors GgafDx9Util::_srv = GgafDx9SphereRadiusVectors();

void GgafDx9Util::init() {
    if (_was_inited_flg) {
        return;
    }

    for (s_ang ang = 0; ang < S_ANG360+1; ang++) {
        double rad = (PI * 2.0f * ang) / S_ANG360;


        COS[ang] = (float)(cos(rad));
        SIN[ang] = (float)(sin(rad));
        RAD[ang] = (float)rad;
        PARABORA[ang] = (float)((double)((ang-(S_ANG360/2))*(ang-(S_ANG360/2))) /  (double)(-1.0*(S_ANG360/2)*(S_ANG360/2)) + 1.0);
        //PARABORA[0] = 0 , PARABORA[S_ANG180] = 1,  PARABORA[S_ANG360-1] = 0 で y = -x^2  放物線の値をとる
    }

    COS[S_ANG0]   =  1;
    COS[S_ANG90]  =  0;
    COS[S_ANG180] = -1;
    COS[S_ANG270] =  0;
    COS[S_ANG360] =  1;
    SIN[S_ANG0]   =  0;
    SIN[S_ANG90]  =  1;
    SIN[S_ANG180] =  0;
    SIN[S_ANG270] = -1;
    SIN[S_ANG360] =  0;
    //<SLANT2ANG>
    double rad;
    double vx,vy,vz;
    float slant;
    int index_slant;
    int index_slant_prev = -1;
    int d_index_slant = 0;
    //傾き 0.0 ～ 1.0 の 角度を求め配列に収める。収める角度は100倍の整数。
    //要素番号は、傾き*10000

    //ang=0  slant=0 vx,vy=1,0
    //ang=1  slant=0.000174533   vx,vy=1,0.000174533
    //ang=2  slant=0.000349066   vx,vy=1,0.000349066
    //ang=3  slant=0.000523599   vx,vy=1,0.000523599
    //ang=4  slant=0.000698132   vx,vy=1,0.000698132
    //ang=5  slant=0.000872665   vx,vy=1,0.000872665

    // SLANT2ANG[0]      = 0
    // SLANT2ANG[1(.7)]～ = 1000～
    // SLANT2ANG[3(.4)]～ = 2000～
    // SLANT2ANG[5(.2)]  = 3000～
    // SLANT2ANG[6(.9)]  = 4000～
    // SLANT2ANG[8(.7)]  = 5000～ といった具合になるように調整

    //ang=4493   slant=0.99756   vx,vy=0.70797,0.706242
    //ang=4494   slant=0.997908  vx,vy=0.707847,0.706366
    //ang=4495   slant=0.998256  vx,vy=0.707724,0.706489
    //ang=4496   slant=0.998605  vx,vy=0.7076,0.706613
    //ang=4497   slant=0.998953  vx,vy=0.707477,0.706736
    //ang=4498   slant=0.999302  vx,vy=0.707354,0.70686
    //ang=4499   slant=0.999651  vx,vy=0.70723,0.706983
    //ang=4500   slant=1 vx,vy=0.707107,0.707107         <--このあたりまで求める
    //ang=4501   slant=1.00035   vx,vy=0.706983,0.70723
    //ang=4502   slant=1.0007    vx,vy=0.70686,0.707354

    //2010/03/09 SLANT2ANGの精度10倍にアップ
    //現在は要素番号は、傾き*100000
    for (int ang = 0; ang <= 45000; ang++) {
        rad = (PI * 2.0f * ang) / 360000;
        vx = cos(rad);
        vy = sin(rad);
        if (vx == 0) {
            slant = 0.0f;
        } else {
            slant = (float)(vy / vx);
        }
        index_slant = (int)(slant * 100000);
        d_index_slant = index_slant - index_slant_prev;
        for (int i = index_slant_prev+1, d = 1; i <= index_slant; i++, d++) {
            if (i > 100000) {
                _TRACE_("＜警告＞想定範囲以上の傾き配列INDEXを設定。メモリが破壊されます。SLANT2ANG["<<i<<"]<="<<(ang*10));
            }
            //等分する（ここがアバウトのもと）
            SLANT2ANG[i] = (angle)( ((ang-1) + (1.0*d)/(1.0*d_index_slant))*1.0);
        }
        index_slant_prev = index_slant;
    }
    d_index_slant = 100000 - index_slant_prev;
    for (int i = index_slant_prev+1, d = 1; i <= 100000; i++, d++) {
        if (i > 100000) {
            _TRACE_("＜警告＞想定範囲以上の傾き配列INDEXを設定。メモリが破壊されます。SLANT2ANG["<<i<<"]<="<<(450000));
        }
        SLANT2ANG[i] = (angle)( (450000-1) + (1.0*d)/(1.0*d_index_slant) );
    }

    //<PROJ_ANG2ROT_ANG> （2009/10/20 経緯・・・速くするためなら何でもやってみよう）
    //ある方向ベクトルから、XY平面、ZY平面に投影した時にできる軸との角（それぞれXY射影角、ZY射影角と呼ぶこととする）と、
    //その方向ベクトルの単位ベクトルが指す単位球の緯度と経度（Z軸回転角、Y軸回転角）を紐つけることを目的とする。
    //つまり、XY射影角、ZY射影角 → Z軸回転角、Y軸回転角 の読み替えを高速に行いたい
    //XY射影角90度分 * ZY射影角90度分 を配列要素、値をZ軸回転角、Y軸回転角を値とする配列を構築。

    double nvx,nvy,nvz;
    double prj_rad_xy,prj_rad_xz, prj_rad_zy, prj_rad_zx;
    s_ang rz, ry_rev;

    vx = 1.0;
    for (s_ang prj_ang_xy = 0; prj_ang_xy <= S_ANG90; prj_ang_xy++) {
        prj_rad_xy = (PI * 2.0 * prj_ang_xy) / (1.0*S_ANG360);
        vy = tan(prj_rad_xy);

        for (s_ang prj_ang_xz = 0; prj_ang_xz <= S_ANG90; prj_ang_xz++) {
            prj_rad_xz = (PI * 2.0 * prj_ang_xz) / (1.0*S_ANG360);
            vz = tan(prj_rad_xz);

            //方向ベクトルを作成
            //vx,vy,vz を正規化する。
            //求める単位ベクトルを (X,Y,Z) とすると (X,Y,Z) = t(vx,vy,vz)
            //関係式   X=t*vx; Y=t*vy; Z=t*vz; ・・・ (1) を得る
            //単位球は X^2 + Y^2 + Z^2 = 1 ・・・(2)
            //(1)(2)を連立させて、t について解く。
            //t = 1 / sqrt(vx^2 + vy^2 + vz^2)
            double t = 1 / sqrt(vx * vx + vy * vy + vz * vz);
            //求めた t を (1) に代入し (X,Y,Z) を求める。
            nvx = t * vx;
            nvy = t * vy;
            nvz = t * vz;
            //getRzRyAng((float)nvx,(float)nvy,(float)nvz,rZ,rY,30);
//
//            //単位ベクトルからRxRyを求める
            _srv.getFaceAngClosely(
                    (UINT32)(nvx*1000000),
                    (UINT32)(nvy*1000000),
                    (UINT32)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );
            PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz] = rz*ANGLE_RATE;
            PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz] = ry_rev*ANGLE_RATE;


           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }



    vz = 1.0;
    for (s_ang prj_ang_zy = 0; prj_ang_zy <= S_ANG90; prj_ang_zy++) {
        prj_rad_zy = (PI * 2.0 * prj_ang_zy) / (1.0*S_ANG360);
        vy = tan(prj_rad_zy);

        for (s_ang prj_ang_zx = 0; prj_ang_zx <= S_ANG90; prj_ang_zx++) {
            prj_rad_zx = (PI * 2.0 * prj_ang_zx) / (1.0*S_ANG360);
            //方向ベクトルを作成
            vx = tan(prj_rad_zx);

            double t = 1 / sqrt(vx * vx + vy * vy + vz * vz);
            nvx = t * vx;
            nvy = t * vy;
            nvz = t * vz;
            //getRzRyAng((float)nvx,(float)nvy,(float)nvz,rZ,rY,30);
//
//            //単位ベクトルからRxRyを求める
            _srv.getFaceAngClosely(
                    (UINT32)(nvx*1000000),
                    (UINT32)(nvy*1000000),
                    (UINT32)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );

            //(0,0,1.0)を0°としX軸の正の方を向いて時計回りを正の角(rx_rev)を考える
            //これは上で求めたrzと等しくなる。
            int rx_rev = rz;
            //(0,0,1.0)を0°としY軸の正の方を向いて反時計回りを正の角(ry)を考える
            //これは上で求めたry_revをANGLE90から引いた値である。
            PROJANG_ZY_ZX_TO_ROTANG_X_REV[prj_ang_zy][prj_ang_zx] = rx_rev*ANGLE_RATE;
            PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx] = ANGLE90 - ry_rev*ANGLE_RATE;
            //_TRACE_("PROJANG_ZY_ZX_TO_ROTANG_Y["<<prj_ang_zy<<"]["<<prj_ang_zx<<"] = ANGLE90 - "<<ry_rev<<"*ANGLE_RATE = "<<PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx]);

           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }

    //ROOT_1_MINUS_XXの設定
    for (int i = 0; i < 1000; i++) {
        ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }
}



void GgafDx9Util::getWayAngle2D(int prm_vx_Center,
                                int prm_vy_Center,
                                int prm_nWay,
                                angle prm_angClearance,
                                angle* out_paAngle) {
    return getWayAngle2D(getAngle2D(prm_vx_Center, prm_vy_Center), prm_nWay, prm_angClearance, out_paAngle);
}

void GgafDx9Util::getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle) {
    int angstart = addAng(prm_angCenter, ((prm_nWay - 1) * prm_angClearance) / -2);

    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(angstart, prm_angClearance * i);
    }
}

void GgafDx9Util::getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle) {
    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(prm_angStart, (angle)(1.0f * ANGLE360 / prm_nWay * i));
    }
}

void GgafDx9Util::convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz) {
    float vx,vy,vz;
    getNormalizeVectorZY(prm_Rz, prm_Ry , vx, vy, vz);
    getRzRyAng(vx, vz, -1.0f*vy, out_Ry, out_Rz ); //-９０度X軸回転RzRy入れ替え
    out_Rz = ANGLE360-out_Rz; //Y軸をZ軸考えるため、正負が変わる＝逆回転＝360から引く
}



//void GgafDx9Util::getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
//                                              int prm_nWay, angle prm_angClearance,
//                                              angle* out_paAngleRz, angle* out_paAngleRy) {
//    float vx,vy,vz;
//    getNormalizeVectorZY(prm_angCenterRz, prm_angCenterRy, vx, vy, vz);
//    float vx2,vy2,vz2;
//    //X軸９０度回転
//    vx2 = vx;
//    vy2 = -vz;
//    vz2 = vy;
//
//    getWayAngle2D(prm_angCenterRz, prm_nWay, prm_angClearance, out_paAngleRz);
//
//}

//void GgafDx9Util::getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, int prm_tX, int prm_tY, int prm_tZ,
//                                          angle& out_angFaceZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    getRzRyAng(prm_tX, prm_tY, prm_tZ, tRy, tRy);
//
//    angle angStart = addAng(tRy, ((prm_nWay - 1) * prm_angClearance) / -2);
//    for (int i = 0; i < prm_nWay; i++) {
//        out_paAngRotY[i] = addAng(angstart, prm_angClearance * i);
//    }
//}

angle GgafDx9Util::addAng(angle prm_angNow, angle prm_angOffset) {
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

angle GgafDx9Util::getAngDiff(angle angFrom, angle angTo, int prm_way) {
    if (prm_way == TURN_CLOSE_TO) {
        if (0 <= angFrom && angFrom < ANGLE180) {
            if (0 <= angTo && angTo < angFrom) {
                return -1 * (angFrom - angTo);
            } else if (angTo == angFrom) {
                //重なってる場合
                return 0;
            } else if (angFrom < angTo && angTo < angFrom + ANGLE180) {
                return angTo - angFrom;
            } else if (angTo == angFrom + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。(正確には -ANGLE180 or ANGLE180)
                return ANGLE180;
            } else if (angFrom + ANGLE180 < angTo && angTo <= ANGLE360) {
                return -1 * (angFrom + (ANGLE360 - angTo));
            } else {
                //おかしい
                _TRACE_("GgafDx9Util::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
                throwGgafCriticalException("GgafDx9Util::getDiffAngle アングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= angFrom && angFrom <= ANGLE360) {
            if (0 <= angTo && angTo < angFrom - ANGLE180) {
                return ANGLE360 - angFrom + angTo;
            } else if (angTo == angFrom - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。(正確には -ANGLE180 or ANGLE180)
                return ANGLE180;
            } else if (angFrom - ANGLE180 < angTo && angTo < angFrom) {
                return -1 * (angFrom - angTo);
            } else if (angFrom == angTo) {
                //重なってる場合
                return 0;
            } else if (angFrom < angTo && angTo <= ANGLE360) {
                return angTo - angFrom;
            } else {
                //おかしい
                _TRACE_("GgafDx9Util::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
                throwGgafCriticalException("GgafDx9Util::getDiffAngle アングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) {
        if (angFrom <= angTo) {
            return angTo - angFrom;
        } else {
            return (ANGLE360 - angFrom) + angTo;
        }
    } else if (prm_way == TURN_CLOCKWISE) {
        if (angFrom >= angTo) {
            return -(angFrom - angTo);
        } else {
            return -(angFrom + (ANGLE360 - angTo));
        }
    } else {
        _TRACE_("GgafDx9Util::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
        throwGgafCriticalException("GgafDx9Util::getDiffAngle  prm_way = TURN_CLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE 以外が指定されています。");
    }

    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
    throwGgafCriticalException("GgafDx9Util::getDiffAngle  何故かしら角の距離が求めれません。(1)");
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
    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}

void GgafDx9Util::getRzRyAng(int vx,
                             int vy,
                             int vz,
                             angle& out_angFaceZ,
                             angle& out_angFaceY ) {
    //何れかの要素が0の場合、getAngle2Dの結果が大きくずれてしまう。
    //とりあえず１を設定して近似させておこう。
    //TODO:0 が来ても大丈夫にする。
    vx = (vx == 0 ? 1 : vx);
    vy = (vy == 0 ? 1 : vy);
    vz = (vz == 0 ? 1 : vz);

    angle prj_rXY = getAngle2D(abs(vx), abs(vy)); //Rz
    angle prj_rXZ = getAngle2D(abs(vx), abs(vz));
    angle prj_rZY = getAngle2D(abs(vz), abs(vy)); //Rz
    angle prj_rZX = getAngle2D(abs(vz), abs(vx));

    angle rotZ, rotY_rev, rotY;
    if (0 <= prj_rXZ && prj_rXZ <= ANGLE45) {
        rotZ = PROJANG_XY_XZ_TO_ROTANG_Z[(int)(prj_rXY/100.0)][(int)(prj_rXZ/100.0)];
        rotY_rev = PROJANG_XY_XZ_TO_ROTANG_Y_REV[(int)(prj_rXY/100.0)][(int)(prj_rXZ/100.0)];
    } else if (ANGLE45 <= prj_rXZ && prj_rXZ <= ANGLE90) {
        rotZ = PROJANG_ZY_ZX_TO_ROTANG_X_REV[(int)(prj_rZY/100.0)][(int)(prj_rZX/100.0)];
        rotY = PROJANG_ZY_ZX_TO_ROTANG_Y[(int)(prj_rZY/100.0)][(int)(prj_rZX/100.0)];
        rotY_rev = ANGLE90 - rotY;
    } else {
        throwGgafCriticalException("GgafDx9Util::getRzRyAng 範囲が破錠してます。prj_rXZ="<<prj_rXZ);
    }

    if (0 <= prj_rXY && prj_rXY < ANGLE45) {
        //OK
    } else if (ANGLE45 <= prj_rXY && prj_rXY <= ANGLE90) {
        //OK
    } else {
        throwGgafCriticalException("GgafDx9Util::getRzRyAng 範囲が破錠してます。prj_rXY="<<prj_rXY<<" 引数:"<<vx<<","<<vy<<","<<vz);
    }
    //象限によって回転角を補正
    if (vx >= 0 && vy >= 0 && vz >= 0) { //第一象限
        out_angFaceZ = rotZ;
        out_angFaceY = (ANGLE360 - rotY_rev);
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //第二象限
        out_angFaceZ = rotZ;
        out_angFaceY = (ANGLE180 + rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //第三象限
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = (ANGLE180 + rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //第四象限
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = (ANGLE360 - rotY_rev);
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //第五象限
        out_angFaceZ = rotZ;
        out_angFaceY = rotY_rev;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //第六象限
        out_angFaceZ = rotZ;
        out_angFaceY = (ANGLE180 - rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //第七象限
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = (ANGLE180 - rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //第八象限
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = rotY_rev;
    } else {
        throwGgafCriticalException("GgafDx9Util::getRzRyAng ありえません。vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }
    out_angFaceZ = simplifyAng(out_angFaceZ);
    out_angFaceY = simplifyAng(out_angFaceY);
}


void GgafDx9Util::getRzRyAng(int vx,
                          int vy,
                          int vz,
                          float& out_nvx,
                          float& out_nvy,
                          float& out_nvz,
                          angle& out_angFaceZ,
                          angle& out_angFaceY) {

    getRzRyAng(vx,
               vy,
               vz,
               out_angFaceZ,
               out_angFaceY );

    getNormalizeVectorZY(out_angFaceZ,
                         out_angFaceY,
                         out_nvx,
                         out_nvy,
                         out_nvz);

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


void GgafDx9Util::getNormalizeVectorZY(angle prm_angFaceZ,
                                       angle prm_angFaceY,
                                       float& out_nvx,
                                       float& out_nvy,
                                       float& out_nvz) {
    //void GgafDx9SphereRadiusVectors::getVectorClosely(int out_angFaceY, int prm_angFaceZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z) {
    //回転角によって象限を考慮し、getVectorCloselyのパラメータ角(< 900)を出す
    int Xsign, Ysign, Zsign;
    s_ang rZ, rY_rev;

    if (0 <= prm_angFaceZ && prm_angFaceZ < ANGLE90) {
        rZ = (prm_angFaceZ - ANGLE0) / ANGLE_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //第五象限
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //第六象限
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //第二象限
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //第一象限
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        }
    } else if (ANGLE90 <= prm_angFaceZ && prm_angFaceZ < ANGLE180) {
        rZ = (ANGLE180 - prm_angFaceZ) / ANGLE_RATE;

        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //第二象限
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //第一象限
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //第五象限
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //第六象限
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        }

    } else if (ANGLE180 <= prm_angFaceZ && prm_angFaceZ < ANGLE270) {
        rZ = (prm_angFaceZ - ANGLE180) / ANGLE_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //第三象限
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //第四象限
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //第八象限
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //第七象限
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        }
    } else if (ANGLE270 <= prm_angFaceZ && prm_angFaceZ <= ANGLE360) {
        rZ = (ANGLE360 - prm_angFaceZ) / ANGLE_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //第八象限
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //第七象限
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //第三象限
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //第四象限
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        }
    } else {
        _TRACE_("getNormalizeVectorZY: なんかおかしいですぜ prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
    }
    UINT32 vx, vy, vz;
    //  _TRACE_("prm_angFaceZ="<<prm_angFaceZ<<"/prm_angFaceY="<<prm_angFaceY<<" rY="<<rY<<"/rZ="<<rZ<<")");
    //  _TRACE_("("<<Xsign<<","<<Ysign<<","<<Zsign<<")");
    _srv.getVectorClosely(rY_rev, rZ, vx, vy, vz);
    out_nvx = Xsign * (int)vx / 1000000.0f;
    out_nvy = Ysign * (int)vy / 1000000.0f;
    out_nvz = Zsign * (int)vz / 1000000.0f;
}




void GgafDx9Util::setWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx * cosRz *cosRy;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = Sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    out_matWorld._22 = Sy * cosRx *  cosRz;
    out_matWorld._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    out_matWorld._32 = Sz * -sinRx *  cosRz;
    out_matWorld._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
    /*
     //前のやり方
     float fRateScale = LEN_UNIT;
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
     D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
     D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}

void GgafDx9Util::setWorldMatrix_RxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × Y軸回転 の変換行列を作成
    //※XYZの順でないことに注意
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    out_matWorld._11 = cosRz * cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (cosRx * -sinRz * cosRy) + (sinRx * sinRy);
    out_matWorld._22 = cosRx * cosRz;
    out_matWorld._23 = (cosRx * -sinRz * -sinRy) + (sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (-sinRx * -sinRz * cosRy) + (cosRx * sinRy);
    out_matWorld._32 = -sinRx * cosRz;
    out_matWorld._33 = (-sinRx * -sinRz * -sinRy) + (cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = 0.0f;
    out_matWorld._42 = 0.0f;
    out_matWorld._43 = 0.0f;
    out_matWorld._44 = 1.0f;
}




void GgafDx9Util::setWorldMatrix_ScRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];

    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx*cosRz*cosRy;
    out_matWorld._12 = Sx*sinRz;
    out_matWorld._13 = Sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*-sinRz*cosRy;
    out_matWorld._22 = Sy*cosRz;
    out_matWorld._23 = Sy*-sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = Sz*cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9Util::mulWorldMatrix_RzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //    |  cosRz*cosRy*Sx  sinRz*Sy   cosRz*-sinRy*Sz   0 |
    //    | -sinRz*cosRy*Sx  cosRz*Sy  -sinRz*-sinRy*Sz   0 |
    //    |  sinRy*Sx        0          cosRy*Sz          0 |
    //    |  dx              dy         dz                1 |
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRz*cosRy*Sx;
    out_matWorld._12 = sinRz*Sy;
    out_matWorld._13 = cosRz*-sinRy*Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy*Sx;
    out_matWorld._22 = cosRz*Sy;
    out_matWorld._23 = -sinRz*-sinRy*Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy*Sx;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy*Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDx9Util::setWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × Y軸回転 × 拡大縮小 × 平行移動　の変換行列を作成
    //※XYZの順でないことに注意
    // |                         cosRz*cosRy*Sx,          sinRz*Sy,                         cosRz*-sinRy*Sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*Sx,    cosRx*cosRz*Sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*Sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*Sx,   -sinRx*cosRz*Sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*Sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRz * cosRy * Sx;
    out_matWorld._12 = sinRz * Sy;
    out_matWorld._13 = cosRz * -sinRy * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((cosRx * -sinRz * cosRy) + (sinRx * sinRy)) * Sx;
    out_matWorld._22 = cosRx * cosRz * Sy;
    out_matWorld._23 = ((cosRx * -sinRz * -sinRy) + (sinRx * cosRy)) * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((-sinRx * -sinRz * cosRy) + (cosRx * sinRy)) * Sx;
    out_matWorld._32 = -sinRx * cosRz * Sy;
    out_matWorld._33 = ((-sinRx * -sinRz * -sinRy) + (cosRx * cosRy)) * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::setWorldMatrix_RxRyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動　の変換行列を作成
    //    |                           cosRy*cosRz*Sx,                        cosRy*sinRz*Sy  ,      -sinRy*Sz,  0 |
    //    | ((sinRx*sinRy*cosRz +  cosRx*-sinRz)*Sx), ((sinRx*sinRy*sinRz +  cosRx*cosRz)*Sy), sinRx*cosRy*Sz,  0 |
    //    | ((cosRx*sinRy*cosRz + -sinRx*-sinRz)*Sx), ((cosRx*sinRy*sinRz + -sinRx*cosRz)*Sy), cosRx*cosRy*Sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    static float fRateScale = 1.0f * LEN_UNIT;

    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRy*cosRz*Sx;
    out_matWorld._12 = cosRy*sinRz*Sy;
    out_matWorld._13 = -sinRy*Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((sinRx*sinRy*cosRz) + (cosRx*-sinRz))*Sx;
    out_matWorld._22 = ((sinRx*sinRy*sinRz) + (cosRx*cosRz))*Sy;
    out_matWorld._23 = sinRx*cosRy*Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((cosRx*sinRy*cosRz) + (-sinRx*-sinRz))*Sx;
    out_matWorld._32 = ((cosRx*sinRy*sinRz) + (-sinRx* cosRz))*Sy;
    out_matWorld._33 = cosRx*cosRy*Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9Util::setWorldMatrix_RxRzRxScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × X軸回転 × 拡大縮小 × 平行移動　の変換行列を作成.
    //※Y軸回転がありません。RYは２回目のX軸回転となる
    //|         cosRz*Sx,                          sinRz*cosRy*Sy ,                          sinRz*sinRy*Sz, 0 |
    //|  cosRx*-sinRz*Sx, (( cosRx*cosRz*cosRy + sinRx*-sinRy)*Sy), (( cosRx*cosRz*sinRy + sinRx*cosRy)*Sz), 0 |
    //| -sinRx*-sinRz*Sx, ((-sinRx*cosRz*cosRy + cosRx*-sinRy)*Sy), ((-sinRx*cosRz*sinRy + cosRx*cosRy)*Sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRz * Sx;
    out_matWorld._12 = sinRz * cosRy * Sy;
    out_matWorld._13 = sinRz * sinRy * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = cosRx * -sinRz * Sx;
    out_matWorld._22 = (( cosRx * cosRz * cosRy) + (sinRx * -sinRy)) * Sy;
    out_matWorld._23 = (( cosRx * cosRz * sinRy) + (sinRx *  cosRy)) * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = -sinRx * -sinRz * Sx;
    out_matWorld._32 = ((-sinRx * cosRz * cosRy) + (cosRx * -sinRy)) * Sy;
    out_matWorld._33 = ((-sinRx * cosRz * sinRy) + (cosRx *  cosRy)) * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::setWorldMatrix_RzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × Z軸回転 × 平行移動　の変換行列を作成
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy   , dz , 1  |
    s_ang s_RZ = prm_pActor->_RZ / ANGLE_RATE;

    out_matWorld._11 = GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (float)(-1.0f * GgafDx9Util::SIN[s_RZ]);
    out_matWorld._22 = GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = 1.0f;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9Util::setWorldMatrix_ScRzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × 拡大縮小 × Z軸回転 × 平行移動　の変換行列を作成
    // |Sx*cosZ , Sx*sinZ , 0    , 0  |
    // |Sy*-sinZ, Sy*cosZ , 0    , 0  |
    // |0       , 0       , Sz   , 0  |
    // |dx      , dy      , dz   , 1  |
    static float fRateScale = 1.0f * LEN_UNIT;

    s_ang s_RZ = prm_pActor->_RZ / ANGLE_RATE;
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx * GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = Sx * GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy * -1.0f * GgafDx9Util::SIN[s_RZ];
    out_matWorld._22 = Sy * GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::setWorldMatrix_ScMvRxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;

    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;
    float dx = prm_pActor->_fX;
    float dy = prm_pActor->_fY;
    float dz = prm_pActor->_fZ;

    out_matWorld._11 = Sx*cosRz*cosRy;
    out_matWorld._12 = Sx*sinRz;
    out_matWorld._13 = Sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*cosRx*-sinRz*cosRy + Sy*sinRx*sinRy;
    out_matWorld._22 = Sy*cosRx*cosRz;
    out_matWorld._23 = Sy*cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy;
    out_matWorld._32 = Sz*-sinRx*cosRz;
    out_matWorld._33 = Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*cosRy + ((dy*sinRx + dz*cosRx))*sinRy;
    out_matWorld._42 = (dx*sinRz + (dy*cosRx + dz*-sinRx)*cosRz);
    out_matWorld._43 = (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*-sinRy + ((dy*sinRx + dz*cosRx))*cosRy;
    out_matWorld._44 = 1.0f;

}




void GgafDx9Util::updateWorldMatrix_Mv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}







void GgafDx9Util::setWorldMatrix_BxyzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;
    GgafDx9Camera* pCam = P_CAM;

    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = pCam->_vMatrixView._11 * Sx;
    out_matWorld._12 = pCam->_vMatrixView._21 * Sy;
    out_matWorld._13 = pCam->_vMatrixView._31 * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = pCam->_vMatrixView._12 * Sx;
    out_matWorld._22 = pCam->_vMatrixView._22 * Sy;
    out_matWorld._23 = pCam->_vMatrixView._32 * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_vMatrixView._13 * Sx;
    out_matWorld._32 = pCam->_vMatrixView._23 * Sy;
    out_matWorld._33 = pCam->_vMatrixView._33 * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}






void GgafDx9Util::setWorldMatrix_ScRzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;
    GgafDx9Camera* pCam = P_CAM;

    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx*cosRz*pCam->_vMatrixView._11 + Sx*sinRz*pCam->_vMatrixView._12;
    out_matWorld._12 = Sx*cosRz*pCam->_vMatrixView._21 + Sx*sinRz*pCam->_vMatrixView._22;
    out_matWorld._13 = Sx*cosRz*pCam->_vMatrixView._31 + Sx*sinRz*pCam->_vMatrixView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*-sinRz*pCam->_vMatrixView._11 + Sy*cosRz*pCam->_vMatrixView._12;
    out_matWorld._22 = Sy*-sinRz*pCam->_vMatrixView._21 + Sy*cosRz*pCam->_vMatrixView._22;
    out_matWorld._23 = Sy*-sinRz*pCam->_vMatrixView._31 + Sy*cosRz*pCam->_vMatrixView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*pCam->_vMatrixView._13;
    out_matWorld._32 = Sz*pCam->_vMatrixView._32;
    out_matWorld._33 = Sz*pCam->_vMatrixView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::mulWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    static float fRateScale = 1.0f * LEN_UNIT;
    D3DXMATRIX matScRxRzRyMv;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    matScRxRzRyMv._11 = Sx * cosRz *cosRy;
    matScRxRzRyMv._12 = Sx * sinRz;
    matScRxRzRyMv._13 = Sx * cosRz * -sinRy;
    matScRxRzRyMv._14 = 0.0f;

    matScRxRzRyMv._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    matScRxRzRyMv._22 = Sy * cosRx *  cosRz;
    matScRxRzRyMv._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    matScRxRzRyMv._24 = 0.0f;

    matScRxRzRyMv._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    matScRxRzRyMv._32 = Sz * -sinRx *  cosRz;
    matScRxRzRyMv._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    matScRxRzRyMv._34 = 0.0f;

    matScRxRzRyMv._41 = prm_pActor->_fX;
    matScRxRzRyMv._42 = prm_pActor->_fY;
    matScRxRzRyMv._43 = prm_pActor->_fZ;
    matScRxRzRyMv._44 = 1.0f;

    D3DXMatrixMultiply(&inout_matWorld, &inout_matWorld, &matScRxRzRyMv);
    /*
     //前のやり方
     float fRateScale = LEN_UNIT;
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
     D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
     D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}


void GgafDx9Util::setWorldMatrix_RxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    // | cosRz*cosRy                        , sinRz       , cosRz*-sinRy                        , 0 |
    // | (cosRx*-sinRz*cosRy + sinRx*sinRy) , cosRx*cosRz , (cosRx*-sinRz*-sinRy + sinRx*cosRy) , 0 |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy), -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy), 0 |
    // | dx                                 , dy          , dz                                  , 1 |
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    out_matWorld._11 = cosRz*cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (cosRx*-sinRz*cosRy + sinRx*sinRy);
    out_matWorld._22 = cosRx*cosRz;
    out_matWorld._23 = (cosRx*-sinRz*-sinRy + sinRx*cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (-sinRx*-sinRz*cosRy + cosRx*sinRy);
    out_matWorld._32 = -sinRx*cosRz;
    out_matWorld._33 = (-sinRx*-sinRz*-sinRy + cosRx*cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDx9Util::setWorldMatrix_RzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDx9Camera* pCam = P_CAM;
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    out_matWorld._11 = cosRz*pCam->_vMatrixView._11 + sinRz*pCam->_vMatrixView._12;
    out_matWorld._12 = cosRz*pCam->_vMatrixView._21 + sinRz*pCam->_vMatrixView._22;
    out_matWorld._13 = cosRz*pCam->_vMatrixView._31 + sinRz*pCam->_vMatrixView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*pCam->_vMatrixView._11 + cosRz*pCam->_vMatrixView._12;
    out_matWorld._22 = -sinRz*pCam->_vMatrixView._21 + cosRz*pCam->_vMatrixView._22;
    out_matWorld._23 = -sinRz*pCam->_vMatrixView._31 + cosRz*pCam->_vMatrixView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_vMatrixView._13;
    out_matWorld._32 = pCam->_vMatrixView._32;
    out_matWorld._33 = pCam->_vMatrixView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
void GgafDx9Util::setWorldMatrix_ScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;

    out_matWorld._11 = prm_pActor->_SX / fRateScale;
    out_matWorld._12 = 0.0f;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = 0.0f;
    out_matWorld._22 = prm_pActor->_SY / fRateScale;
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = prm_pActor->_SZ / fRateScale;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
//UINT32 GgafDx9Util::max3(UINT32 a, UINT32 b, UINT32 c) {
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

