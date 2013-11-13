#include "stdafx.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

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
//angRx rot_X rx Rx rx radRx ・・・ X軸回転に関連している変数名
//angRy rot_y ry Ry ry radRy ・・・ Y軸回転に関連している変数名
//angRz rot_z rx Rz rz radRz ・・・ Z軸回転に関連している変数名
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
//という場合は rotxy という変数にしています。
//つまり rotxy = angXY or angRz
//angXY -> angRz は角度0°の位置(方向ベクトル(x,y,z)=(1,0,0))、正の回転方向が一致するのでわかりやすいです。

//「めも」
//angXZ -> angRy の読み替えは正の回転方向が angXZ と angRy で逆になってしまいます。
//angZX -> angRy の場合は正の回転方向は一致しますが、角度0°の位置が(x,y,z)=(1,0,0) ではなくなってしまうため、キャラの軸回転には向きません
//
//そこで
//rot_XZ = angXZ or angRy_rev
//のように "rev" 「逆周りですよ」と書くようにした。角度0°の位置を優先した結果、こんなややこしいことになっている！



bool GgafDxUtil::_was_inited_flg = false;

//float GgafDxUtil::PARABORA[D360SANG+1];
float GgafDxUtil::COS[D360SANG+1];
float GgafDxUtil::SIN[D360SANG+1];
float GgafDxUtil::RAD[D360SANG+1];

float GgafDxUtil::ROOT_1_MINUS_XX[1000];


angle GgafDxUtil::SLANT2ANG[100000 + 1];

//こんなんいるのでは！
//angle GgafDxUtil::PROJANG_XY_ZX_YZ_TO_ROTANG_z[D90SANG+1][D90SANG+1];


angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_z[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_y_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_x_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_y[D90SANG+1][D90SANG+1];
double GgafDxUtil::SMOOTH_DV[3600+1];
angle GgafDxUtil::GOLDEN_ANG[1000];
uint32_t GgafDxUtil::BITNUM[33];
GgafDxSphereRadiusVectors GgafDxUtil::_srv = GgafDxSphereRadiusVectors();
GgafDxCamera* GgafDxUtil::_pCam = nullptr; //GgafDxUniverse::GgafDxUniverse() で設定される

void GgafDxUtil::init() {
    if (_was_inited_flg) {
        return;
    }

    for (s_ang ang = 0; ang < D360SANG+1; ang++) {
        double rad = (PI * 2.0 * ang) / D360SANG;

        COS[ang] = (float)(cos(rad));
        SIN[ang] = (float)(sin(rad));
        RAD[ang] = (float)rad;
        //PARABORA[ang] = (float)((double)((ang-(D360SANG/2))*(ang-(D360SANG/2))) /  (double)(-1.0*(D360SANG/2)*(D360SANG/2)) + 1.0);
        ////PARABORA[0] = 0 , PARABORA[D180SANG] = 1,  PARABORA[D360SANG-1] = 0 で y = -x^2  放物線の値をとる
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
        if (ZEROf_EQ(vx)) {
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
            //convVectorToRzRy((float)nvx,(float)nvy,(float)nvz,rz,ry,30);
            //単位ベクトルからRxRyを求める
            _srv.getFaceAngClosely(
                    (uint32_t)(nvx*1000000),
                    (uint32_t)(nvy*1000000),
                    (uint32_t)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );
            PROJANG_XY_XZ_TO_ROTANG_z[prj_ang_xy][prj_ang_xz] = rz*SANG_RATE;
            PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_ang_xy][prj_ang_xz] = ry_rev*SANG_RATE;
            //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_ang_xy][prj_ang_xz]<<")");

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
            //convVectorToRzRy((float)nvx,(float)nvy,(float)nvz,rz,ry,30);
            //単位ベクトルからRxRyを求める
            _srv.getFaceAngClosely(
                    (uint32_t)(nvx*1000000),
                    (uint32_t)(nvy*1000000),
                    (uint32_t)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );

            //(0,0,1.0)を0°としX軸の正の方を向いて時計回りを正の角(rx_rev)を考える
            //これは上で求めたrzと等しくなる。
            int rx_rev = rz;
            //(0,0,1.0)を0°としY軸の正の方を向いて反時計回りを正の角(ry)を考える
            //これは上で求めたry_revをD90ANGから引いた値である。
            PROJANG_ZY_ZX_TO_ROTANG_x_REV[prj_ang_zy][prj_ang_zx] = rx_rev*SANG_RATE;
            PROJANG_ZY_ZX_TO_ROTANG_y[prj_ang_zy][prj_ang_zx] = D90ANG - ry_rev*SANG_RATE;
            //_TRACE_("PROJANG_ZY_ZX_TO_ROTANG_y["<<prj_ang_zy<<"]["<<prj_ang_zx<<"] = D90ANG - "<<ry_rev<<"*SANG_RATE = "<<PROJANG_ZY_ZX_TO_ROTANG_y[prj_ang_zy][prj_ang_zx]);
            //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_ang_xy][prj_ang_xz]<<")");
        }
    }

    //ROOT_1_MINUS_XXの設定
    for (int i = 0; i < 1000; i++) {
        ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }

    for (int i = 0; i <= 3600; i++) {
        double t = double(i / 3600.0);
        //D = 1 - cos(2πt)
        SMOOTH_DV[i] = 1.0 - cos(2.0*PI*t);
    }

    //黄金角配列
    for (int n = 0; n < 1000; n++) {
        // θは黄金角
        // 1 : (1+√5) / 2 = 2π-θ : θ
        // 2π-θ = { (1+√5) / 2 } θ
        // (2π-θ) / θ = (1+√5) / 2
        // (2π/θ) - 1 = (1+√5) / 2
        // 2π/θ = 1 + {(1+√5) / 2}
        // 2π =  ( 1 + {(1+√5) / 2} ) θ
        // θ = 2π/ ( 1 + {(1+√5) / 2} )
        double n_theta = n * ( PI2 / ( 1.0 + ((1.0+sqrt(5.0))/2.0) ) );
        //標準化
        while (n_theta >= PI2) {
            n_theta -= PI2;
        }
        while (n_theta < 0) {
            n_theta += PI2;
        }
        GOLDEN_ANG[n] = (angle)(D360ANG*n_theta / PI2);
        //_TRACE_("GOLDEN_ANG["<<n<<"]="<<GOLDEN_ANG[n]);
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
    int angstart = GgafDxUtil::addAng(prm_angCenter, ((prm_nWay - 1) * prm_angClearance) / -2);

    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = GgafDxUtil::addAng(angstart, prm_angClearance * i);
    }
}

void GgafDxUtil::getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle) {
    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = GgafDxUtil::addAng(prm_angStart, (angle)(1.0f * D360ANG / prm_nWay * i));
    }
}

void GgafDxUtil::convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz) {
    float vx,vy,vz;
    GgafDxUtil::convRzRyToVector(prm_Rz, prm_Ry , vx, vy, vz);
    GgafDxUtil::convVectorToRzRy(vx, vz, -1.0f*vy, out_Ry, out_Rz ); //-９０度X軸回転RzRy入れ替え
    out_Rz = D360ANG-out_Rz; //Y軸をZ軸考えるため、正負が変わる＝逆回転＝360から引く
}



//void GgafDxUtil::getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
//                                              int prm_nWay, angle prm_angClearance,
//                                              angle* out_paAngleRz, angle* out_paAngleRy) {
//    float vx,vy,vz;
//    convRzRyToVector(prm_angCenterRz, prm_angCenterRy, vx, vy, vz);
//    float vx2,vy2,vz2;
//    //X軸９０度回転
//    vx2 = vx;
//    vy2 = -vz;
//    vz2 = vy;
//
//    getWayAngle2D(prm_angCenterRz, prm_nWay, prm_angClearance, out_paAngleRz);
//
//}

//void GgafDxUtil::getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, coord prm_tx, coord prm_ty, coord prm_tz,
//                                          angle& out_angFaceZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    convVectorToRzRy(prm_tx, prm_ty, prm_tz, tRy, tRy);
//
//    angle angStart = addAng(tRy, ((prm_nWay - 1) * prm_angClearance) / -2);
//    for (int i = 0; i < prm_nWay; i++) {
//        out_paAngRotY[i] = addAng(angstart, prm_angClearance * i);
//    }
//}

angle GgafDxUtil::addAng(angle prm_angNow, angle prm_angOffset) {
    angle angAdd = prm_angNow + prm_angOffset;
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

void GgafDxUtil::rotxy(int prm_x, int prm_y, angle prm_ang, int& out_x, int& out_y) {
    out_x = (int)(floor((prm_x * GgafDxUtil::COS[prm_ang/SANG_RATE]) - (prm_y * GgafDxUtil::SIN[prm_ang/SANG_RATE])));
    out_y = (int)(floor((prm_x * GgafDxUtil::SIN[prm_ang/SANG_RATE]) + (prm_y * GgafDxUtil::COS[prm_ang/SANG_RATE])));
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

coord GgafDxUtil::getDistance(coord x1, coord y1, coord x2, coord y2) {
    return (coord)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}
//int GgafDxUtil::getDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
//    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))) + (((double)(z2 - z1)) * ((double)(z2 - z1))));
//}


void GgafDxUtil::convVectorToRzRy(coord vx,
                                  coord vy,
                                  coord vz,
                                  angle& out_angRz,
                                  angle& out_angRy ) {
    if (vz == 0) {
        out_angRz = GgafDxUtil::getAngle2D(vx, vy);
        out_angRy = 0;
        return;
    }

    //何れかの要素が0の場合、getAngle2Dの結果が大きくずれてしまう。
    //とりあえず１を設定して近似させておこう。
    //TODO:0 が来ても大丈夫にする。
    vx = (vx == 0 ? 1 : vx);
    vy = (vy == 0 ? 1 : vy);
    vz = (vz == 0 ? 1 : vz);

    angle prj_rXY = GgafDxUtil::getAngle2D(ABS(vx), ABS(vy)); //Rz
    angle prj_rXZ = GgafDxUtil::getAngle2D(ABS(vx), ABS(vz));
    angle prj_rZY = GgafDxUtil::getAngle2D(ABS(vz), ABS(vy)); //Rz
    angle prj_rZX = GgafDxUtil::getAngle2D(ABS(vz), ABS(vx));

    angle rot_z, rot_y_rev;
    if (0 <= prj_rXZ && prj_rXZ <= D45ANG) {
        rot_z = GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_z[(int)(prj_rXY*0.01)][(int)(prj_rXZ*0.01)];
        rot_y_rev = GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_y_REV[(int)(prj_rXY*0.01)][(int)(prj_rXZ*0.01)];
    } else if (D45ANG <= prj_rXZ && prj_rXZ <= D90ANG) {
        rot_z = GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_x_REV[(int)(prj_rZY*0.01)][(int)(prj_rZX*0.01)];
        rot_y_rev = D90ANG - GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_y[(int)(prj_rZY*0.01)][(int)(prj_rZX*0.01)];
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng 範囲が破綻してます。prj_rXZ="<<prj_rXZ<<" 引数:"<<vx<<","<<vy<<","<<vz);
    }
#if MY_DEBUG
    if (0 <= prj_rXY && prj_rXY < D45ANG) {
        //OK
    } else if (D45ANG <= prj_rXY && prj_rXY <= D90ANG) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng 範囲が破綻してます。prj_rXY="<<prj_rXY<<" 引数:"<<vx<<","<<vy<<","<<vz);
    }
#endif
    //象限によって回転角を補正
    if (vx >= 0 && vy >= 0 && vz >= 0) { //第一象限
        out_angRz = rot_z;
        out_angRy = (D360ANG - rot_y_rev);
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //第二象限
        out_angRz = rot_z;
        out_angRy = (D180ANG + rot_y_rev);
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //第三象限
        out_angRz = (D360ANG - rot_z);
        out_angRy = (D180ANG + rot_y_rev);
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //第四象限
        out_angRz = (D360ANG - rot_z);
        out_angRy = (D360ANG - rot_y_rev);
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //第五象限
        out_angRz = rot_z;
        out_angRy = rot_y_rev;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //第六象限
        out_angRz = rot_z;
        out_angRy = (D180ANG - rot_y_rev);
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //第七象限
        out_angRz = (D360ANG - rot_z);
        out_angRy = (D180ANG - rot_y_rev);
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //第八象限
        out_angRz = (D360ANG - rot_z);
        out_angRy = rot_y_rev;
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng ありえません。vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }

#if MY_DEBUG
    if (D360ANG < out_angRz || 0 > out_angRz || D360ANG < out_angRy || 0 > out_angRy) {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng 範囲外です要調査。\n out_angRz,out_angRy="<<out_angRz<<","<<out_angRy<<" vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }
#endif
//    out_angRz = simplifyAng(out_angRz);
//    out_angRy = simplifyAng(out_angRy);
}


void GgafDxUtil::convVectorToRzRy(coord vx,
                                  coord vy,
                                  coord vz,
                                  float& out_nvx,
                                  float& out_nvy,
                                  float& out_nvz,
                                  angle& out_angRz,
                                  angle& out_angRy) {

    GgafDxUtil::convVectorToRzRy(vx, vy, vz,
                                 out_angRz, out_angRy );

    GgafDxUtil::convRzRyToVector(out_angRz, out_angRy,
                                 out_nvx, out_nvy, out_nvz);

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
    double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;
}

void GgafDxUtil::getNormalizeVector(dxcoord x,
                                    dxcoord y,
                                    dxcoord z,
                                    float& out_nvx,
                                    float& out_nvy,
                                    float& out_nvz) {
    double t = 1.0 / sqrt(x * x + y * y + z * z);
    out_nvx = t * x;
    out_nvy = t * y;
    out_nvz = t * z;
}


void GgafDxUtil::convRzRyToVector(angle prm_angRz,
                                  angle prm_angRy,
                                  float& out_nvx,
                                  float& out_nvy,
                                  float& out_nvz) {
    //void GgafDxSphereRadiusVectors::getVectorClosely(int out_angFaceY, int prm_angZ, uint16_t& out_x, uint16_t& out_y, uint16_t& out_z) {
    //回転角によって象限を考慮し、getVectorCloselyのパラメータ角(< 900)を出す
    int xsign, ysign, zsign;
    s_ang rz, ry_rev;

    if (0 <= prm_angRz && prm_angRz < D90ANG) {
        rz = (prm_angRz - D0ANG) * (1.0 / SANG_RATE);
        if (0 <= prm_angRy && prm_angRy < D90ANG) { //第五象限
            ry_rev = prm_angRy * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = -1;
        } else if (D90ANG <= prm_angRy && prm_angRy < D180ANG) { //第六象限
            ry_rev = (D180ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = -1;
        } else if (D180ANG <= prm_angRy && prm_angRy < D270ANG) { //第二象限
            ry_rev = (prm_angRy - D180ANG) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = 1;
        } else if (D270ANG <= prm_angRy && prm_angRy <= D360ANG) { //第一象限
            ry_rev = (D360ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(1) prm_angRz="<<prm_angRz<<" prm_angRy="<<prm_angRy);
        }
    } else if (D90ANG <= prm_angRz && prm_angRz < D180ANG) {
        rz = (D180ANG - prm_angRz) * (1.0 / SANG_RATE);

        if (0 <= prm_angRy && prm_angRy < D90ANG) { //第二象限
            ry_rev = prm_angRy * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = 1;
        } else if (D90ANG <= prm_angRy && prm_angRy < D180ANG) { //第一象限
            ry_rev = (D180ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = 1;
        } else if (D180ANG <= prm_angRy && prm_angRy < D270ANG) { //第五象限
            ry_rev = (prm_angRy - D180ANG) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = -1;
        } else if (D270ANG <= prm_angRy && prm_angRy <= D360ANG) { //第六象限
            ry_rev = (D360ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(2) prm_angRz="<<prm_angRz<<" prm_angRy="<<prm_angRy);
        }

    } else if (D180ANG <= prm_angRz && prm_angRz < D270ANG) {
        rz = (prm_angRz - D180ANG) * (1.0 / SANG_RATE);
        if (0 <= prm_angRy && prm_angRy < D90ANG) { //第三象限
            ry_rev = prm_angRy * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = 1;
        } else if (D90ANG <= prm_angRy && prm_angRy < D180ANG) { //第四象限
            ry_rev = (D180ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = 1;
        } else if (D180ANG <= prm_angRy && prm_angRy < D270ANG) { //第八象限
            ry_rev = (prm_angRy - D180ANG) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = -1;
        } else if (D270ANG <= prm_angRy && prm_angRy <= D360ANG) { //第七象限
            ry_rev = (D360ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(3) prm_angRz="<<prm_angRz<<" prm_angRy="<<prm_angRy);
        }
    } else if (D270ANG <= prm_angRz && prm_angRz <= D360ANG) {
        rz = (D360ANG - prm_angRz) * (1.0 / SANG_RATE);
        if (0 <= prm_angRy && prm_angRy < D90ANG) { //第八象限
            ry_rev = prm_angRy * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = -1;
        } else if (D90ANG <= prm_angRy && prm_angRy < D180ANG) { //第七象限
            ry_rev = (D180ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = -1;
        } else if (D180ANG <= prm_angRy && prm_angRy < D270ANG) { //第三象限
            ry_rev = (prm_angRy - D180ANG) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = 1;
        } else if (D270ANG <= prm_angRy && prm_angRy <= D360ANG) { //第四象限
            ry_rev = (D360ANG - prm_angRy) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(4) prm_angRz="<<prm_angRz<<" prm_angRy="<<prm_angRy);
        }
    } else {
        throwGgafCriticalException("getNormalizeVectorZY: なんかおかしいですぜ(5) prm_angRz="<<prm_angRz<<" prm_angRy="<<prm_angRy);
    }
    uint32_t vx, vy, vz;
    GgafDxUtil::_srv.getVectorClosely(ry_rev, rz, vx, vy, vz);
    out_nvx = xsign * (int)vx * (1.0 / 1000000.0);
    out_nvy = ysign * (int)vy * (1.0 / 1000000.0);
    out_nvz = zsign * (int)vz * (1.0 / 1000000.0);
}




void GgafDxUtil::setWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    // | sx*cosRz*cosRy                           , sx*sinRz       , sx*cosRz*-sinRy                           , 0|
    // | (sy* cosRx*-sinRz*cosRy + sy*sinRx*sinRy), sy*cosRx*cosRz , (sy* cosRx*-sinRz*-sinRy + sy*sinRx*cosRy), 0|
    // | (sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy), sz*-sinRx*cosRz, (sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx * cosRz *cosRy;
    out_matWorld._12 = sx * sinRz;
    out_matWorld._13 = sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (sy * cosRx * -sinRz *  cosRy) + (sy * sinRx * sinRy);
    out_matWorld._22 =  sy * cosRx *  cosRz;
    out_matWorld._23 = (sy * cosRx * -sinRz * -sinRy) + (sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (sz * -sinRx * -sinRz *  cosRy) + (sz * cosRx * sinRy);
    out_matWorld._32 =  sz * -sinRx *  cosRz;
    out_matWorld._33 = (sz * -sinRx * -sinRz * -sinRy) + (sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
    /*
     //前のやり方
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDxUtil::RAD_UNITLEN[s_rx]/LEN_UNIT);
     D3DXMatrixRotationX(&matrixRotY, GgafDxUtil::RAD_UNITLEN[s_ry]/LEN_UNIT);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDxUtil::RAD_UNITLEN[s_rz]/LEN_UNIT);
     D3DXMatrixTranslation(&matrixTrans, _x/LEN_UNIT, _y/LEN_UNIT, _z/LEN_UNIT);
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
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);

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
    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);

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

void GgafDxUtil::setWorldMatrix_RxRzRy(angle prm_rx, angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Z軸回転 × Y軸回転 の変換行列を作成
    //※XYZの順でないことに注意
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    float sinRx = ANG_SIN(prm_rx);
    float cosRx = ANG_COS(prm_rx);
    float sinRy = ANG_SIN(prm_ry);
    float cosRy = ANG_COS(prm_ry);
    float sinRz = ANG_SIN(prm_rz);
    float cosRz = ANG_COS(prm_rz);

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
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx*cosRz*cosRy;
    out_matWorld._12 = sx*sinRz;
    out_matWorld._13 = sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*-sinRz*cosRy;
    out_matWorld._22 = sy*cosRz;
    out_matWorld._23 = sy*-sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = sz*cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDxUtil::mulWorldMatrix_RzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //    |  cosRz*cosRy*sx  sinRz*sy   cosRz*-sinRy*sz   0 |
    //    | -sinRz*cosRy*sx  cosRz*sy  -sinRz*-sinRy*sz   0 |
    //    |  sinRy*sx        0          cosRy*sz          0 |
    //    |  dx              dy         dz                1 |
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRz*cosRy*sx;
    out_matWorld._12 = sinRz*sy;
    out_matWorld._13 = cosRz*-sinRy*sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy*sx;
    out_matWorld._22 = cosRz*sy;
    out_matWorld._23 = -sinRz*-sinRy*sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy*sx;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy*sz;
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
    // |                         cosRz*cosRy*sx,          sinRz*sy,                         cosRz*-sinRy*sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*sx,    cosRx*cosRz*sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*sx,   -sinRx*cosRz*sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRz * cosRy * sx;
    out_matWorld._12 = sinRz * sy;
    out_matWorld._13 = cosRz * -sinRy * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((cosRx * -sinRz * cosRy) + (sinRx * sinRy)) * sx;
    out_matWorld._22 = cosRx * cosRz * sy;
    out_matWorld._23 = ((cosRx * -sinRz * -sinRy) + (sinRx * cosRy)) * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((-sinRx * -sinRz * cosRy) + (cosRx * sinRy)) * sx;
    out_matWorld._32 = -sinRx * cosRz * sy;
    out_matWorld._33 = ((-sinRx * -sinRz * -sinRy) + (cosRx * cosRy)) * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_RxRyRzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //単位行列 × X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動　の変換行列を作成
    //    |                           cosRy*cosRz*sx,                        cosRy*sinRz*sy  ,      -sinRy*sz,  0 |
    //    | ((sinRx*sinRy*cosRz +  cosRx*-sinRz)*sx), ((sinRx*sinRy*sinRz +  cosRx*cosRz)*sy), sinRx*cosRy*sz,  0 |
    //    | ((cosRx*sinRy*cosRz + -sinRx*-sinRz)*sx), ((cosRx*sinRy*sinRz + -sinRx*cosRz)*sy), cosRx*cosRy*sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRy*cosRz*sx;
    out_matWorld._12 = cosRy*sinRz*sy;
    out_matWorld._13 = -sinRy*sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((sinRx*sinRy*cosRz) + (cosRx*-sinRz))*sx;
    out_matWorld._22 = ((sinRx*sinRy*sinRz) + (cosRx*cosRz))*sy;
    out_matWorld._23 = sinRx*cosRy*sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((cosRx*sinRy*cosRz) + (-sinRx*-sinRz))*sx;
    out_matWorld._32 = ((cosRx*sinRy*sinRz) + (-sinRx* cosRz))*sy;
    out_matWorld._33 = cosRx*cosRy*sz;
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
    //|         cosRz*sx,                          sinRz*cosRy*sy ,                          sinRz*sinRy*sz, 0 |
    //|  cosRx*-sinRz*sx, (( cosRx*cosRz*cosRy + sinRx*-sinRy)*sy), (( cosRx*cosRz*sinRy + sinRx*cosRy)*sz), 0 |
    //| -sinRx*-sinRz*sx, ((-sinRx*cosRz*cosRy + cosRx*-sinRy)*sy), ((-sinRx*cosRz*sinRy + cosRx*cosRy)*sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRz * sx;
    out_matWorld._12 = sinRz * cosRy * sy;
    out_matWorld._13 = sinRz * sinRy * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = cosRx * -sinRz * sx;
    out_matWorld._22 = (( cosRx * cosRz * cosRy) + (sinRx * -sinRy)) * sy;
    out_matWorld._23 = (( cosRx * cosRz * sinRy) + (sinRx *  cosRy)) * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = -sinRx * -sinRz * sx;
    out_matWorld._32 = ((-sinRx * cosRz * cosRy) + (cosRx * -sinRy)) * sy;
    out_matWorld._33 = ((-sinRx * cosRz * sinRy) + (cosRx *  cosRy)) * sz;
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
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
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
    // |sx*cosZ , sx*sinZ , 0    , 0  |
    // |sy*-sinZ, sy*cosZ , 0    , 0  |
    // |0       , 0       , sz   , 0  |
    // |dx      , dy      , dz   , 1  |
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx * cosRz;
    out_matWorld._12 = sx * sinRz;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy * -sinRz;
    out_matWorld._22 = sy * cosRz;
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_ScMvRxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);
    dxcoord dx = prm_pActor->_fX;
    dxcoord dy = prm_pActor->_fY;
    dxcoord dz = prm_pActor->_fZ;

    out_matWorld._11 = sx*cosRz*cosRy;
    out_matWorld._12 = sx*sinRz;
    out_matWorld._13 = sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*cosRx*-sinRz*cosRy + sy*sinRx*sinRy;
    out_matWorld._22 = sy*cosRx*cosRz;
    out_matWorld._23 = sy*cosRx*-sinRz*-sinRy + sy*sinRx*cosRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy;
    out_matWorld._32 = sz*-sinRx*cosRz;
    out_matWorld._33 = sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy;
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
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = _pCam->_matView._11 * sx;
    out_matWorld._12 = _pCam->_matView._21 * sy;
    out_matWorld._13 = _pCam->_matView._31 * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = _pCam->_matView._12 * sx;
    out_matWorld._22 = _pCam->_matView._22 * sy;
    out_matWorld._23 = _pCam->_matView._32 * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = _pCam->_matView._13 * sx;
    out_matWorld._32 = _pCam->_matView._23 * sy;
    out_matWorld._33 = _pCam->_matView._33 * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_BxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {

    out_matWorld._11 = _pCam->_matView._11;
    out_matWorld._12 = _pCam->_matView._21;
    out_matWorld._13 = _pCam->_matView._31;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = _pCam->_matView._12;
    out_matWorld._22 = _pCam->_matView._22;
    out_matWorld._23 = _pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = _pCam->_matView._13;
    out_matWorld._32 = _pCam->_matView._23;
    out_matWorld._33 = _pCam->_matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDxUtil::setWorldMatrix_ScRzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {

    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx*cosRz*_pCam->_matView._11 + sx*sinRz*_pCam->_matView._12;
    out_matWorld._12 = sx*cosRz*_pCam->_matView._21 + sx*sinRz*_pCam->_matView._22;
    out_matWorld._13 = sx*cosRz*_pCam->_matView._31 + sx*sinRz*_pCam->_matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*-sinRz*_pCam->_matView._11 + sy*cosRz*_pCam->_matView._12;
    out_matWorld._22 = sy*-sinRz*_pCam->_matView._21 + sy*cosRz*_pCam->_matView._22;
    out_matWorld._23 = sy*-sinRz*_pCam->_matView._31 + sy*cosRz*_pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*_pCam->_matView._13;
    out_matWorld._32 = sz*_pCam->_matView._32;
    out_matWorld._33 = sz*_pCam->_matView._33;
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
    // | sx*cosRz*cosRy                           , sx*sinRz       , sx*cosRz*-sinRy                           , 0|
    // | (sy* cosRx*-sinRz*cosRy + sy*sinRx*sinRy), sy*cosRx*cosRz , (sy* cosRx*-sinRz*-sinRy + sy*sinRx*cosRy), 0|
    // | (sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy), sz*-sinRx*cosRz, (sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    D3DXMATRIX matScRxRzRyMv;
    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    matScRxRzRyMv._11 = sx * cosRz *cosRy;
    matScRxRzRyMv._12 = sx * sinRz;
    matScRxRzRyMv._13 = sx * cosRz * -sinRy;
    matScRxRzRyMv._14 = 0.0f;

    matScRxRzRyMv._21 = (sy * cosRx * -sinRz *  cosRy) + (sy * sinRx * sinRy);
    matScRxRzRyMv._22 = sy * cosRx *  cosRz;
    matScRxRzRyMv._23 = (sy * cosRx * -sinRz * -sinRy) + (sy * sinRx * cosRy);
    matScRxRzRyMv._24 = 0.0f;

    matScRxRzRyMv._31 = (sz * -sinRx * -sinRz *  cosRy) + (sz * cosRx * sinRy);
    matScRxRzRyMv._32 = sz * -sinRx *  cosRz;
    matScRxRzRyMv._33 = (sz * -sinRx * -sinRz * -sinRy) + (sz * cosRx * cosRy);
    matScRxRzRyMv._34 = 0.0f;

    matScRxRzRyMv._41 = prm_pActor->_fX;
    matScRxRzRyMv._42 = prm_pActor->_fY;
    matScRxRzRyMv._43 = prm_pActor->_fZ;
    matScRxRzRyMv._44 = 1.0f;

    D3DXMatrixMultiply(&inout_matWorld, &inout_matWorld, &matScRxRzRyMv);
}



void GgafDxUtil::setWorldMatrix_RzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    D3DXMATRIX& matView = _pCam->_matView;
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);

    out_matWorld._11 = cosRz*matView._11 + sinRz*matView._12;
    out_matWorld._12 = cosRz*matView._21 + sinRz*matView._22;
    out_matWorld._13 = cosRz*matView._31 + sinRz*matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*matView._11 + cosRz*matView._12;
    out_matWorld._22 = -sinRz*matView._21 + cosRz*matView._22;
    out_matWorld._23 = -sinRz*matView._31 + cosRz*matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = matView._13;
    out_matWorld._32 = matView._32;
    out_matWorld._33 = matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
void GgafDxUtil::setWorldMatrix_ScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._11 = SC_R(prm_pActor->_sx);
    out_matWorld._12 = 0.0f;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = 0.0f;
    out_matWorld._22 = SC_R(prm_pActor->_sy);
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = SC_R(prm_pActor->_sz);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

