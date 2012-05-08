#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;



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



bool GgafDxUtil::_was_inited_flg = false;

float GgafDxUtil::PARABORA[D360SANG+1];
float GgafDxUtil::COS[D360SANG+1];
float GgafDxUtil::SIN[D360SANG+1];
float GgafDxUtil::RAD[D360SANG+1];

float GgafDxUtil::ROOT_1_MINUS_XX[1000];


angle GgafDxUtil::SLANT2ANG[100000 + 1];

//こんなんいるのでは！
//angle GgafDxUtil::PROJANG_XY_ZX_YZ_TO_ROTANG_Z[D90SANG+1][D90SANG+1];


angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_Z[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_Y_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_X_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_Y[D90SANG+1][D90SANG+1];


UINT32 GgafDxUtil::BITNUM[33];
GgafDxSphereRadiusVectors GgafDxUtil::_srv = GgafDxSphereRadiusVectors();

void GgafDxUtil::init() {
    if (_was_inited_flg) {
        return;
    }

    for (s_ang ang = 0; ang < D360SANG+1; ang++) {
        double rad = (PI * 2.0 * ang) / D360SANG;


        COS[ang] = (float)(cos(rad));
        SIN[ang] = (float)(sin(rad));
        RAD[ang] = (float)rad;
        PARABORA[ang] = (float)((double)((ang-(D360SANG/2))*(ang-(D360SANG/2))) /  (double)(-1.0*(D360SANG/2)*(D360SANG/2)) + 1.0);
        //PARABORA[0] = 0 , PARABORA[D180SANG] = 1,  PARABORA[D360SANG-1] = 0 で y = -x^2  放物線の値をとる
    }

    COS[D0SANG]   =  1;
    COS[D90SANG]  =  0;
    COS[D180SANG] = -1;
    COS[D270SANG] =  0;
    COS[D360SANG] =  1;
    SIN[D0SANG]   =  0;
    SIN[D90SANG]  =  1;
    SIN[D180SANG] =  0;
    SIN[D270SANG] = -1;
    SIN[D360SANG] =  0;
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
        rad = (PI * 2.0 * ang) / 360000;
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
        SLANT2ANG[i] = (angle)( (45000-1) + (1.0*d)/(1.0*d_index_slant) );
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
    for (s_ang prj_ang_xy = 0; prj_ang_xy <= D90SANG; prj_ang_xy++) {
        prj_rad_xy = (PI * 2.0 * prj_ang_xy) / (1.0*D360SANG);
        vy = tan(prj_rad_xy);

        for (s_ang prj_ang_xz = 0; prj_ang_xz <= D90SANG; prj_ang_xz++) {
            prj_rad_xz = (PI * 2.0 * prj_ang_xz) / (1.0*D360SANG);
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
            PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz] = rz*SANG_RATE;
            PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz] = ry_rev*SANG_RATE;


           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }



    vz = 1.0;
    for (s_ang prj_ang_zy = 0; prj_ang_zy <= D90SANG; prj_ang_zy++) {
        prj_rad_zy = (PI * 2.0 * prj_ang_zy) / (1.0*D360SANG);
        vy = tan(prj_rad_zy);

        for (s_ang prj_ang_zx = 0; prj_ang_zx <= D90SANG; prj_ang_zx++) {
            prj_rad_zx = (PI * 2.0 * prj_ang_zx) / (1.0*D360SANG);
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
            //これは上で求めたry_revをD90ANGから引いた値である。
            PROJANG_ZY_ZX_TO_ROTANG_X_REV[prj_ang_zy][prj_ang_zx] = rx_rev*SANG_RATE;
            PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx] = D90ANG - ry_rev*SANG_RATE;
            //_TRACE_("PROJANG_ZY_ZX_TO_ROTANG_Y["<<prj_ang_zy<<"]["<<prj_ang_zx<<"] = D90ANG - "<<ry_rev<<"*SANG_RATE = "<<PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx]);

           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }

    //ROOT_1_MINUS_XXの設定
    for (int i = 0; i < 1000; i++) {
        ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }

    BITNUM[ 0] = 0;
    BITNUM[ 1] = (0x1);            //0b 00000000 00000000 00000000 00000001
    BITNUM[ 2] = (0x2);            //0b 00000000 00000000 00000000 00000010
    BITNUM[ 3] = (0x4);            //0b 00000000 00000000 00000000 00000100
    BITNUM[ 4] = (0x8);            //0b 00000000 00000000 00000000 00001000
    BITNUM[ 5] = (0x10);           //0b 00000000 00000000 00000000 00010000
    BITNUM[ 6] = (0x20);           //0b 00000000 00000000 00000000 00100000
    BITNUM[ 7] = (0x40);           //0b 00000000 00000000 00000000 01000000
    BITNUM[ 8] = (0x80);           //0b 00000000 00000000 00000000 10000000
    BITNUM[ 9] = (0x100);          //0b 00000000 00000000 00000001 00000000
    BITNUM[10] = (0x200);          //0b 00000000 00000000 00000010 00000000
    BITNUM[11] = (0x400);          //0b 00000000 00000000 00000100 00000000
    BITNUM[12] = (0x800);          //0b 00000000 00000000 00001000 00000000
    BITNUM[13] = (0x1000);         //0b 00000000 00000000 00010000 00000000
    BITNUM[14] = (0x2000);         //0b 00000000 00000000 00100000 00000000
    BITNUM[15] = (0x4000);         //0b 00000000 00000000 01000000 00000000
    BITNUM[16] = (0x8000);         //0b 00000000 00000000 10000000 00000000
    BITNUM[17] = (0x10000);        //0b 00000000 00000001 00000000 00000000
    BITNUM[18] = (0x20000);        //0b 00000000 00000010 00000000 00000000
    BITNUM[19] = (0x40000);        //0b 00000000 00000100 00000000 00000000
    BITNUM[20] = (0x80000);        //0b 00000000 00001000 00000000 00000000
    BITNUM[21] = (0x100000);       //0b 00000000 00010000 00000000 00000000
    BITNUM[22] = (0x200000);       //0b 00000000 00100000 00000000 00000000
    BITNUM[23] = (0x400000);       //0b 00000000 01000000 00000000 00000000
    BITNUM[24] = (0x800000);       //0b 00000000 10000000 00000000 00000000
    BITNUM[25] = (0x1000000);      //0b 00000001 00000000 00000000 00000000
    BITNUM[26] = (0x2000000);      //0b 00000010 00000000 00000000 00000000
    BITNUM[27] = (0x4000000);      //0b 00000100 00000000 00000000 00000000
    BITNUM[28] = (0x8000000);      //0b 00001000 00000000 00000000 00000000
    BITNUM[29] = (0x10000000);     //0b 00010000 00000000 00000000 00000000
    BITNUM[30] = (0x20000000);     //0b 00100000 00000000 00000000 00000000
    BITNUM[31] = (0x40000000);     //0b 01000000 00000000 00000000 00000000
    BITNUM[32] = (0x80000000);     //0b 10000000 00000000 00000000 00000000
}



void GgafDxUtil::getWayAngle2D(int prm_vx_Center,
                               int prm_vy_Center,
                               int prm_nWay,
                               angle prm_angClearance,
                               angle* out_paAngle) {
    return getWayAngle2D(getAngle2D(prm_vx_Center, prm_vy_Center), prm_nWay, prm_angClearance, out_paAngle);
}

void GgafDxUtil::getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle) {
    int angstart = addAng(prm_angCenter, ((prm_nWay - 1) * prm_angClearance) / -2);

    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(angstart, prm_angClearance * i);
    }
}

void GgafDxUtil::getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle) {
    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(prm_angStart, (angle)(1.0f * D360ANG / prm_nWay * i));
    }
}

void GgafDxUtil::convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz) {
    float vx,vy,vz;
    getNormalizeVectorZY(prm_Rz, prm_Ry , vx, vy, vz);
    getRzRyAng(vx, vz, -1.0f*vy, out_Ry, out_Rz ); //-９０度X軸回転RzRy入れ替え
    out_Rz = D360ANG-out_Rz; //Y軸をZ軸考えるため、正負が変わる＝逆回転＝360から引く
}



//void GgafDxUtil::getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
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

//void GgafDxUtil::getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, coord prm_tX, coord prm_tY, coord prm_tZ,
//                                          angle& out_angFaceZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    getRzRyAng(prm_tX, prm_tY, prm_tZ, tRy, tRy);
//
//    angle angStart = addAng(tRy, ((prm_nWay - 1) * prm_angClearance) / -2);
//    for (int i = 0; i < prm_nWay; i++) {
//        out_paAngRotY[i] = addAng(angstart, prm_angClearance * i);
//    }
//}

angle GgafDxUtil::addAng(angle prm_angNow, angle prm_angOffset) {
    static angle angAdd;
    angAdd = prm_angNow + prm_angOffset;
    while (angAdd >= D360ANG) {
        angAdd -= D360ANG;
    }
    while (angAdd < 0) {
        angAdd += D360ANG;
    }
    return angAdd;
}

angle GgafDxUtil::getAngDiff(angle angFrom, angle angTo, int prm_way) {
    if (prm_way == TURN_CLOSE_TO) {
        if (0 <= angFrom && angFrom < D180ANG) {
            if (0 <= angTo && angTo < angFrom) {
                return -1 * (angFrom - angTo);
            } else if (angTo == angFrom) {
                //重なってる場合
                return 0;
            } else if (angFrom < angTo && angTo < angFrom + D180ANG) {
                return angTo - angFrom;
            } else if (angTo == angFrom + D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。(正確には -D180ANG or D180ANG)
                return D180ANG;
            } else if (angFrom + D180ANG < angTo && angTo <= D360ANG) {
                return -1 * (angFrom + (D360ANG - angTo));
            } else {
                //おかしい
                _TRACE_("GgafDxUtil::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
                throwGgafCriticalException("GgafDxUtil::getDiffAngle アングル値が範囲外です(1)。\n"<<
                                           "angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
            }
        } else if (D180ANG <= angFrom && angFrom <= D360ANG) {
            if (0 <= angTo && angTo < angFrom - D180ANG) {
                return D360ANG - angFrom + angTo;
            } else if (angTo == angFrom - D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。(正確には -D180ANG or D180ANG)
                return D180ANG;
            } else if (angFrom - D180ANG < angTo && angTo < angFrom) {
                return -1 * (angFrom - angTo);
            } else if (angFrom == angTo) {
                //重なってる場合
                return 0;
            } else if (angFrom < angTo && angTo <= D360ANG) {
                return angTo - angFrom;
            } else {
                //おかしい
                _TRACE_("GgafDxUtil::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
                throwGgafCriticalException("GgafDxUtil::getDiffAngle アングル値が範囲外です(2)。\n"<<
                                           "angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) {
        if (angFrom <= angTo) {
            return angTo - angFrom;
        } else {
            return (D360ANG - angFrom) + angTo;
        }
    } else if (prm_way == TURN_CLOCKWISE) {
        if (angFrom >= angTo) {
            return -(angFrom - angTo);
        } else {
            return -(angFrom + (D360ANG - angTo));
        }
    } else {
        _TRACE_("GgafDxUtil::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
        throwGgafCriticalException("GgafDxUtil::getDiffAngle  prm_way = TURN_CLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE 以外が指定されています。");
    }

    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
    throwGgafCriticalException("GgafDxUtil::getDiffAngle  何故かしら角の距離が求めれません。(1) \n"<<
                               "angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
}

void GgafDxUtil::rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y) {
    out_X = (int)(floor((prm_X * GgafDxUtil::COS[prm_ang/SANG_RATE]) - (prm_Y * GgafDxUtil::SIN[prm_ang/SANG_RATE])));
    out_Y = (int)(floor((prm_X * GgafDxUtil::SIN[prm_ang/SANG_RATE]) + (prm_Y * GgafDxUtil::COS[prm_ang/SANG_RATE])));
}

// 線分の当たり判定 (x11,y11)-(x12,y12) × (x21,y21)-(x22,y22)
bool GgafDxUtil::chk2DLineCrossing(coord x11, coord y11, coord x12, coord y12, coord x21, coord y21, coord x22, coord y22) {

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

int GgafDxUtil::getDistance(int x1, int y1, int x2, int y2) {
    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}
//int GgafDxUtil::getDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
//    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))) + (((double)(z2 - z1)) * ((double)(z2 - z1))));
//}


void GgafDxUtil::getRzRyAng(coord vx,
                            coord vy,
                            coord vz,
                            angle& out_angRZ,
                            angle& out_angRY ) {

    if (vz == 0) {
        out_angRZ = getAngle2D(vx, vy);
        out_angRY = 0;
        return;
    }



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

    angle rotZ, rotY_rev;
    if (0 <= prj_rXZ && prj_rXZ <= D45ANG) {
        rotZ = PROJANG_XY_XZ_TO_ROTANG_Z[(int)(prj_rXY/100)][(int)(prj_rXZ/100)];
        rotY_rev = PROJANG_XY_XZ_TO_ROTANG_Y_REV[(int)(prj_rXY/100)][(int)(prj_rXZ/100)];
    } else if (D45ANG <= prj_rXZ && prj_rXZ <= D90ANG) {
        rotZ = PROJANG_ZY_ZX_TO_ROTANG_X_REV[(int)(prj_rZY/100)][(int)(prj_rZX/100)];
        rotY_rev = D90ANG - PROJANG_ZY_ZX_TO_ROTANG_Y[(int)(prj_rZY/100)][(int)(prj_rZX/100)];
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng 範囲が破錠してます。prj_rXZ="<<prj_rXZ);
    }
#if MY_DEBUG
    if (0 <= prj_rXY && prj_rXY < D45ANG) {
        //OK
    } else if (D45ANG <= prj_rXY && prj_rXY <= D90ANG) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng 範囲が破錠してます。prj_rXY="<<prj_rXY<<" 引数:"<<vx<<","<<vy<<","<<vz);
    }
#endif
    //象限によって回転角を補正
    if (vx >= 0 && vy >= 0 && vz >= 0) { //第一象限
        out_angRZ = rotZ;
        out_angRY = (D360ANG - rotY_rev);
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //第二象限
        out_angRZ = rotZ;
        out_angRY = (D180ANG + rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //第三象限
        out_angRZ = (D360ANG - rotZ);
        out_angRY = (D180ANG + rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //第四象限
        out_angRZ = (D360ANG - rotZ);
        out_angRY = (D360ANG - rotY_rev);
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //第五象限
        out_angRZ = rotZ;
        out_angRY = rotY_rev;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //第六象限
        out_angRZ = rotZ;
        out_angRY = (D180ANG - rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //第七象限
        out_angRZ = (D360ANG - rotZ);
        out_angRY = (D180ANG - rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //第八象限
        out_angRZ = (D360ANG - rotZ);
        out_angRY = rotY_rev;
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng ありえません。vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }

#if MY_DEBUG
    if (D360ANG < out_angRZ || 0 > out_angRZ || D360ANG < out_angRY || 0 > out_angRY) {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng 範囲外です要調査。\n out_angRZ,out_angRY="<<out_angRZ<<","<<out_angRY<<" vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }
#endif
//    out_angRZ = simplifyAng(out_angRZ);
//    out_angRY = simplifyAng(out_angRY);
}


void GgafDxUtil::getRzRyAng(coord vx,
                            coord vy,
                            coord vz,
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



void GgafDxUtil::getNormalizeVector(coord x,
                                    coord y,
                                    coord z,
                                    float& out_nvx,
                                    float& out_nvy,
                                    float& out_nvz) {
    dxcoord vx = C_DX(x);
    dxcoord vy = C_DX(y);
    dxcoord vz = C_DX(z);
    double t = 1.0 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;
}



void GgafDxUtil::getNormalizeVectorZY(angle prm_angFaceZ,
                                      angle prm_angFaceY,
                                      float& out_nvx,
                                      float& out_nvy,
                                      float& out_nvz) {
    //void GgafDxSphereRadiusVectors::getVectorClosely(int out_angFaceY, int prm_angFaceZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z) {
    //回転角によって象限を考慮し、getVectorCloselyのパラメータ角(< 900)を出す
    int Xsign, Ysign, Zsign;
    s_ang rZ, rY_rev;

    if (0 <= prm_angFaceZ && prm_angFaceZ < D90ANG) {
        rZ = (prm_angFaceZ - D0ANG) / SANG_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //第五象限
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //第六象限
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //第二象限
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //第一象限
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(1) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }
    } else if (D90ANG <= prm_angFaceZ && prm_angFaceZ < D180ANG) {
        rZ = (D180ANG - prm_angFaceZ) / SANG_RATE;

        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //第二象限
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //第一象限
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //第五象限
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //第六象限
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(2) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }

    } else if (D180ANG <= prm_angFaceZ && prm_angFaceZ < D270ANG) {
        rZ = (prm_angFaceZ - D180ANG) / SANG_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //第三象限
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //第四象限
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //第八象限
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //第七象限
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(3) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }
    } else if (D270ANG <= prm_angFaceZ && prm_angFaceZ <= D360ANG) {
        rZ = (D360ANG - prm_angFaceZ) / SANG_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //第八象限
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //第七象限
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //第三象限
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //第四象限
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(4) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }
    } else {
        throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(5) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
    }
    UINT32 vx, vy, vz;
    _srv.getVectorClosely(rY_rev, rZ, vx, vy, vz);
    out_nvx = Xsign * (int)vx / 1000000.0;
    out_nvy = Ysign * (int)vy / 1000000.0;
    out_nvz = Zsign * (int)vz / 1000000.0;
}




void GgafDxUtil::setWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = Sx * cosRz *cosRy;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = Sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    out_matWorld._22 =  Sy * cosRx *  cosRz;
    out_matWorld._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    out_matWorld._32 =  Sz * -sinRx *  cosRz;
    out_matWorld._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
    /*
     //前のやり方
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDxUtil::RAD_UNITLEN[s_RX]/LEN_UNIT);
     D3DXMatrixRotationX(&matrixRotY, GgafDxUtil::RAD_UNITLEN[s_RY]/LEN_UNIT);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDxUtil::RAD_UNITLEN[s_RZ]/LEN_UNIT);
     D3DXMatrixTranslation(&matrixTrans, _X/LEN_UNIT, _Y/LEN_UNIT, _Z/LEN_UNIT);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}

void GgafDxUtil::setWorldMatrix_RzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × Z軸回転 × Y軸回転 の変換行列を作成
    //※XYZの順でないことに注意
    // |  cosRz*cosRy, sinRz,  cosRz*-sinRy,   0  |
    // | -sinRz*cosRy, cosRz, -sinRz*-sinRy,   0  |
    // |        sinRy,     0,         cosRy,   0  |
    // |            0,     0,             0,   1  |
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

    out_matWorld._11 = cosRz*cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy;
    out_matWorld._22 = cosRz;
    out_matWorld._23 = -sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = 0.0f;
    out_matWorld._42 = 0.0f;
    out_matWorld._43 = 0.0f;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_RzRy(angle prm_Rz, angle prm_Ry, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × Z軸回転 × Y軸回転 の変換行列を作成
    //※XYZの順でないことに注意
    // |  cosRz*cosRy, sinRz,  cosRz*-sinRy,   0  |
    // | -sinRz*cosRy, cosRz, -sinRz*-sinRy,   0  |
    // |        sinRy,     0,         cosRy,   0  |
    // |            0,     0,             0,   1  |
    float sinRy = ANG_SIN(prm_Ry);
    float cosRy = ANG_COS(prm_Ry);
    float sinRz = ANG_SIN(prm_Rz);
    float cosRz = ANG_COS(prm_Rz);

    out_matWorld._11 = cosRz*cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy;
    out_matWorld._22 = cosRz;
    out_matWorld._23 = -sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = 0.0f;
    out_matWorld._42 = 0.0f;
    out_matWorld._43 = 0.0f;
    out_matWorld._44 = 1.0f;
}

void GgafDxUtil::setWorldMatrix_RxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × Y軸回転 の変換行列を作成
    //※XYZの順でないことに注意
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

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

void GgafDxUtil::setWorldMatrix_RxRzRy(angle prm_RX, angle prm_RZ, angle prm_RY, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × Y軸回転 の変換行列を作成
    //※XYZの順でないことに注意
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    float sinRx = ANG_SIN(prm_RX);
    float cosRx = ANG_COS(prm_RX);
    float sinRy = ANG_SIN(prm_RY);
    float cosRy = ANG_COS(prm_RY);
    float sinRz = ANG_SIN(prm_RZ);
    float cosRz = ANG_COS(prm_RZ);

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


void GgafDxUtil::setWorldMatrix_ScRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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



void GgafDxUtil::mulWorldMatrix_RzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //    |  cosRz*cosRy*Sx  sinRz*Sy   cosRz*-sinRy*Sz   0 |
    //    | -sinRz*cosRy*Sx  cosRz*Sy  -sinRz*-sinRy*Sz   0 |
    //    |  sinRy*Sx        0          cosRy*Sz          0 |
    //    |  dx              dy         dz                1 |
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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

void GgafDxUtil::setWorldMatrix_RxRzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × Y軸回転 × 拡大縮小 × 平行移動　の変換行列を作成
    //※XYZの順でないことに注意
    // |                         cosRz*cosRy*Sx,          sinRz*Sy,                         cosRz*-sinRy*Sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*Sx,    cosRx*cosRz*Sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*Sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*Sx,   -sinRx*cosRz*Sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*Sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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


void GgafDxUtil::setWorldMatrix_RxRyRzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動　の変換行列を作成
    //    |                           cosRy*cosRz*Sx,                        cosRy*sinRz*Sy  ,      -sinRy*Sz,  0 |
    //    | ((sinRx*sinRy*cosRz +  cosRx*-sinRz)*Sx), ((sinRx*sinRy*sinRz +  cosRx*cosRz)*Sy), sinRx*cosRy*Sz,  0 |
    //    | ((cosRx*sinRy*cosRz + -sinRx*-sinRz)*Sx), ((cosRx*sinRy*sinRz + -sinRx*cosRz)*Sy), cosRx*cosRy*Sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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



void GgafDxUtil::setWorldMatrix_RxRzRxScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × X軸回転 × 拡大縮小 × 平行移動　の変換行列を作成.
    //※Y軸回転がありません。RYは２回目のX軸回転となる
    //|         cosRz*Sx,                          sinRz*cosRy*Sy ,                          sinRz*sinRy*Sz, 0 |
    //|  cosRx*-sinRz*Sx, (( cosRx*cosRz*cosRy + sinRx*-sinRy)*Sy), (( cosRx*cosRz*sinRy + sinRx*cosRy)*Sz), 0 |
    //| -sinRx*-sinRz*Sx, ((-sinRx*cosRz*cosRy + cosRx*-sinRy)*Sy), ((-sinRx*cosRz*sinRy + cosRx*cosRy)*Sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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


void GgafDxUtil::setWorldMatrix_RzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × Z軸回転 × 平行移動　の変換行列を作成
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy   , dz , 1  |
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    out_matWorld._11 = cosRz;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz;
    out_matWorld._22 = cosRz;
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



void GgafDxUtil::setWorldMatrix_ScRzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × 拡大縮小 × Z軸回転 × 平行移動　の変換行列を作成
    // |Sx*cosZ , Sx*sinZ , 0    , 0  |
    // |Sy*-sinZ, Sy*cosZ , 0    , 0  |
    // |0       , 0       , Sz   , 0  |
    // |dx      , dy      , dz   , 1  |
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = Sx * cosRz;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy * -sinRz;
    out_matWorld._22 = Sy * cosRz;
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


void GgafDxUtil::setWorldMatrix_ScMvRxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);
    dxcoord dx = prm_pActor->_fX;
    dxcoord dy = prm_pActor->_fY;
    dxcoord dz = prm_pActor->_fZ;

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




void GgafDxUtil::updateWorldMatrix_Mv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}







void GgafDxUtil::setWorldMatrix_BxyzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDxCamera* pCam = P_CAM;

    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = pCam->_matView._11 * Sx;
    out_matWorld._12 = pCam->_matView._21 * Sy;
    out_matWorld._13 = pCam->_matView._31 * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = pCam->_matView._12 * Sx;
    out_matWorld._22 = pCam->_matView._22 * Sy;
    out_matWorld._23 = pCam->_matView._32 * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_matView._13 * Sx;
    out_matWorld._32 = pCam->_matView._23 * Sy;
    out_matWorld._33 = pCam->_matView._33 * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}






void GgafDxUtil::setWorldMatrix_ScRzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDxCamera* pCam = P_CAM;

    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = Sx*cosRz*pCam->_matView._11 + Sx*sinRz*pCam->_matView._12;
    out_matWorld._12 = Sx*cosRz*pCam->_matView._21 + Sx*sinRz*pCam->_matView._22;
    out_matWorld._13 = Sx*cosRz*pCam->_matView._31 + Sx*sinRz*pCam->_matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*-sinRz*pCam->_matView._11 + Sy*cosRz*pCam->_matView._12;
    out_matWorld._22 = Sy*-sinRz*pCam->_matView._21 + Sy*cosRz*pCam->_matView._22;
    out_matWorld._23 = Sy*-sinRz*pCam->_matView._31 + Sy*cosRz*pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*pCam->_matView._13;
    out_matWorld._32 = Sz*pCam->_matView._32;
    out_matWorld._33 = Sz*pCam->_matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::mulWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    D3DXMATRIX matScRxRzRyMv;
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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
}


void GgafDxUtil::setWorldMatrix_RxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    // | cosRz*cosRy                        , sinRz       , cosRz*-sinRy                        , 0 |
    // | (cosRx*-sinRz*cosRy + sinRx*sinRy) , cosRx*cosRz , (cosRx*-sinRz*-sinRy + sinRx*cosRy) , 0 |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy), -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy), 0 |
    // | dx                                 , dy          , dz                                  , 1 |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

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

void GgafDxUtil::setWorldMatrix_RzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDxCamera* pCam = P_CAM;
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

    out_matWorld._11 = cosRz*pCam->_matView._11 + sinRz*pCam->_matView._12;
    out_matWorld._12 = cosRz*pCam->_matView._21 + sinRz*pCam->_matView._22;
    out_matWorld._13 = cosRz*pCam->_matView._31 + sinRz*pCam->_matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*pCam->_matView._11 + cosRz*pCam->_matView._12;
    out_matWorld._22 = -sinRz*pCam->_matView._21 + cosRz*pCam->_matView._22;
    out_matWorld._23 = -sinRz*pCam->_matView._31 + cosRz*pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_matView._13;
    out_matWorld._32 = pCam->_matView._32;
    out_matWorld._33 = pCam->_matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
void GgafDxUtil::setWorldMatrix_ScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._11 = SC_R(prm_pActor->_SX);
    out_matWorld._12 = 0.0f;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = 0.0f;
    out_matWorld._22 = SC_R(prm_pActor->_SY);
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = SC_R(prm_pActor->_SZ);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
//UINT32 GgafDxUtil::max3(UINT32 a, UINT32 b, UINT32 c) {
//  if (a > b) {
//      if (a > c) {
//          return a;
//      } else {
//          return c;
//      }
//  } else {
//      if (b > c) {
//          return b;
//      } else {
//          return c;
//      }
//  }
//}

