////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9BoardSetModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

//画面幅(px)
float g_view_width; 
//画面高さ(px)
float g_view_height; 

//テクスチャU座標増分
float g_offsetU001;
float g_offsetU002;
float g_offsetU003;
float g_offsetU004;
float g_offsetU005;
float g_offsetU006;
float g_offsetU007;
float g_offsetU008;
float g_offsetU009;
float g_offsetU010;
float g_offsetU011;
float g_offsetU012;
float g_offsetU013;
float g_offsetU014;
float g_offsetU015;
float g_offsetU016;
float g_offsetU017;
float g_offsetU018;
float g_offsetU019;
float g_offsetU020;
float g_offsetU021;
float g_offsetU022;
float g_offsetU023;
float g_offsetU024;

float g_offsetU025;
float g_offsetU026;
float g_offsetU027;
float g_offsetU028;
float g_offsetU029;
float g_offsetU030;
float g_offsetU031;
float g_offsetU032;
float g_offsetU033;
float g_offsetU034;
float g_offsetU035;
float g_offsetU036;
float g_offsetU037;
float g_offsetU038;
float g_offsetU039;
float g_offsetU040;
float g_offsetU041;
float g_offsetU042;
float g_offsetU043;
float g_offsetU044;
float g_offsetU045;
float g_offsetU046;
float g_offsetU047;
float g_offsetU048;
float g_offsetU049;
float g_offsetU050;
float g_offsetU051;
float g_offsetU052;
float g_offsetU053;
float g_offsetU054;
float g_offsetU055;
float g_offsetU056;
float g_offsetU057;
float g_offsetU058;
float g_offsetU059;
float g_offsetU060;
float g_offsetU061;
float g_offsetU062;
float g_offsetU063;
float g_offsetU064;
float g_offsetU065;
float g_offsetU066;
float g_offsetU067;
float g_offsetU068;
float g_offsetU069;
float g_offsetU070;
float g_offsetU071;
float g_offsetU072;
float g_offsetU073;
float g_offsetU074;
float g_offsetU075;
float g_offsetU076;
float g_offsetU077;
float g_offsetU078;
float g_offsetU079;
float g_offsetU080;
float g_offsetU081;
float g_offsetU082;
float g_offsetU083;
float g_offsetU084;
float g_offsetU085;
float g_offsetU086;
float g_offsetU087;
float g_offsetU088;
float g_offsetU089;
float g_offsetU090;
float g_offsetU091;
float g_offsetU092;
float g_offsetU093;
float g_offsetU094;
float g_offsetU095;
float g_offsetU096;
float g_offsetU097;
float g_offsetU098;
float g_offsetU099;
float g_offsetU100;
float g_offsetU101;
float g_offsetU102;
float g_offsetU103;
float g_offsetU104;
float g_offsetU105;
float g_offsetU106;
float g_offsetU107;
float g_offsetU108;
float g_offsetU109;
float g_offsetU110;
float g_offsetU111;
float g_offsetU112;
float g_offsetU113;
float g_offsetU114;
float g_offsetU115;
float g_offsetU116;
float g_offsetU117;
float g_offsetU118;
float g_offsetU119;
float g_offsetU120;
float g_offsetU121;
float g_offsetU122;
float g_offsetU123;
float g_offsetU124;
float g_offsetU125;
float g_offsetU126;
float g_offsetU127;
float g_offsetU128;
float g_offsetU129;
float g_offsetU130;
float g_offsetU131;
float g_offsetU132;
float g_offsetU133;
float g_offsetU134;
float g_offsetU135;
float g_offsetU136;
float g_offsetU137;
float g_offsetU138;
float g_offsetU139;
float g_offsetU140;
float g_offsetU141;
float g_offsetU142;
float g_offsetU143;
float g_offsetU144;
float g_offsetU145;
float g_offsetU146;
float g_offsetU147;
float g_offsetU148;
float g_offsetU149;
float g_offsetU150;
float g_offsetU151;
float g_offsetU152;
float g_offsetU153;
float g_offsetU154;
float g_offsetU155;
float g_offsetU156;
float g_offsetU157;
float g_offsetU158;
float g_offsetU159;
float g_offsetU160;
float g_offsetU161;
float g_offsetU162;
float g_offsetU163;
float g_offsetU164;
float g_offsetU165;
float g_offsetU166;
float g_offsetU167;
float g_offsetU168;
float g_offsetU169;
float g_offsetU170;
float g_offsetU171;
float g_offsetU172;
float g_offsetU173;
float g_offsetU174;
float g_offsetU175;
float g_offsetU176;
float g_offsetU177;
float g_offsetU178;
float g_offsetU179;
float g_offsetU180;
float g_offsetU181;
float g_offsetU182;
float g_offsetU183;
float g_offsetU184;
float g_offsetU185;
float g_offsetU186;
float g_offsetU187;
float g_offsetU188;
float g_offsetU189;
float g_offsetU190;
float g_offsetU191;
float g_offsetU192;
float g_offsetU193;
float g_offsetU194;
float g_offsetU195;
float g_offsetU196;
float g_offsetU197;
float g_offsetU198;
float g_offsetU199;
float g_offsetU200;
float g_offsetU201;
float g_offsetU202;
float g_offsetU203;
float g_offsetU204;
float g_offsetU205;
float g_offsetU206;
float g_offsetU207;
float g_offsetU208;
float g_offsetU209;
float g_offsetU210;
float g_offsetU211;
float g_offsetU212;
float g_offsetU213;
float g_offsetU214;
float g_offsetU215;
float g_offsetU216;
float g_offsetU217;
float g_offsetU218;
float g_offsetU219;
float g_offsetU220;
float g_offsetU221;
float g_offsetU222;
float g_offsetU223;
float g_offsetU224;
float g_offsetU225;
float g_offsetU226;
float g_offsetU227;
float g_offsetU228;
float g_offsetU229;
float g_offsetU230;
float g_offsetU231;
float g_offsetU232;
float g_offsetU233;
float g_offsetU234;
float g_offsetU235;
float g_offsetU236;
float g_offsetU237;
float g_offsetU238;
float g_offsetU239;
float g_offsetU240;
float g_offsetU241;
float g_offsetU242;
float g_offsetU243;
float g_offsetU244;
float g_offsetU245;
float g_offsetU246;
float g_offsetU247;
float g_offsetU248;
float g_offsetU249;
float g_offsetU250;
float g_offsetU251;
float g_offsetU252;
float g_offsetU253;
float g_offsetU254;
float g_offsetU255;
float g_offsetU256;
float g_offsetU257;
float g_offsetU258;
float g_offsetU259;
float g_offsetU260;
float g_offsetU261;
float g_offsetU262;
float g_offsetU263;
float g_offsetU264;
float g_offsetU265;
float g_offsetU266;
float g_offsetU267;
float g_offsetU268;
float g_offsetU269;
float g_offsetU270;
float g_offsetU271;
float g_offsetU272;
float g_offsetU273;
float g_offsetU274;
float g_offsetU275;
float g_offsetU276;
float g_offsetU277;
float g_offsetU278;
float g_offsetU279;
float g_offsetU280;
float g_offsetU281;
float g_offsetU282;
float g_offsetU283;
float g_offsetU284;
float g_offsetU285;
float g_offsetU286;
float g_offsetU287;
float g_offsetU288;
float g_offsetU289;
float g_offsetU290;
float g_offsetU291;
float g_offsetU292;
float g_offsetU293;
float g_offsetU294;
float g_offsetU295;
float g_offsetU296;
float g_offsetU297;
float g_offsetU298;
float g_offsetU299;
float g_offsetU300;
float g_offsetU301;
float g_offsetU302;
float g_offsetU303;
float g_offsetU304;
float g_offsetU305;
float g_offsetU306;
float g_offsetU307;
float g_offsetU308;
float g_offsetU309;
float g_offsetU310;
float g_offsetU311;
float g_offsetU312;
float g_offsetU313;
float g_offsetU314;
float g_offsetU315;
float g_offsetU316;
float g_offsetU317;
float g_offsetU318;
float g_offsetU319;
float g_offsetU320;
float g_offsetU321;
float g_offsetU322;
float g_offsetU323;
float g_offsetU324;
float g_offsetU325;
float g_offsetU326;
float g_offsetU327;
float g_offsetU328;
float g_offsetU329;
float g_offsetU330;
float g_offsetU331;
float g_offsetU332;
float g_offsetU333;
float g_offsetU334;
float g_offsetU335;
float g_offsetU336;
float g_offsetU337;
float g_offsetU338;
float g_offsetU339;
float g_offsetU340;
float g_offsetU341;
float g_offsetU342;
float g_offsetU343;
float g_offsetU344;
float g_offsetU345;
float g_offsetU346;
float g_offsetU347;
float g_offsetU348;
float g_offsetU349;
float g_offsetU350;
float g_offsetU351;
float g_offsetU352;
float g_offsetU353;
float g_offsetU354;
float g_offsetU355;
float g_offsetU356;
float g_offsetU357;
float g_offsetU358;
float g_offsetU359;
float g_offsetU360;
float g_offsetU361;
float g_offsetU362;
float g_offsetU363;
float g_offsetU364;
float g_offsetU365;
float g_offsetU366;
float g_offsetU367;
float g_offsetU368;
float g_offsetU369;
float g_offsetU370;
float g_offsetU371;
float g_offsetU372;
float g_offsetU373;
float g_offsetU374;
float g_offsetU375;
float g_offsetU376;
float g_offsetU377;
float g_offsetU378;
float g_offsetU379;
float g_offsetU380;
float g_offsetU381;
float g_offsetU382;
float g_offsetU383;
float g_offsetU384;
float g_offsetU385;
float g_offsetU386;
float g_offsetU387;
float g_offsetU388;
float g_offsetU389;
float g_offsetU390;
float g_offsetU391;
float g_offsetU392;
float g_offsetU393;
float g_offsetU394;
float g_offsetU395;
float g_offsetU396;
float g_offsetU397;
float g_offsetU398;
float g_offsetU399;
float g_offsetU400;
float g_offsetU401;
float g_offsetU402;
float g_offsetU403;
float g_offsetU404;
float g_offsetU405;
float g_offsetU406;
float g_offsetU407;
float g_offsetU408;
float g_offsetU409;




//テクスチャV座標増分
float g_offsetV001;
float g_offsetV002;
float g_offsetV003;
float g_offsetV004;
float g_offsetV005;
float g_offsetV006;
float g_offsetV007;
float g_offsetV008;
float g_offsetV009;
float g_offsetV010;
float g_offsetV011;
float g_offsetV012;
float g_offsetV013;
float g_offsetV014;
float g_offsetV015;
float g_offsetV016;
float g_offsetV017;
float g_offsetV018;
float g_offsetV019;
float g_offsetV020;
float g_offsetV021;
float g_offsetV022;
float g_offsetV023;
float g_offsetV024;

//変換済みX座標(px)
float g_transformedX001;
float g_transformedX002;
float g_transformedX003;
float g_transformedX004;
float g_transformedX005;
float g_transformedX006;
float g_transformedX007;
float g_transformedX008;
float g_transformedX009;
float g_transformedX010;
float g_transformedX011;
float g_transformedX012;
float g_transformedX013;
float g_transformedX014;
float g_transformedX015;
float g_transformedX016;
float g_transformedX017;
float g_transformedX018;
float g_transformedX019;
float g_transformedX020;
float g_transformedX021;
float g_transformedX022;
float g_transformedX023;
float g_transformedX024;

//変換済みY座標(px)
float g_transformedY001;
float g_transformedY002;
float g_transformedY003;
float g_transformedY004;
float g_transformedY005;
float g_transformedY006;
float g_transformedY007;
float g_transformedY008;
float g_transformedY009;
float g_transformedY010;
float g_transformedY011;
float g_transformedY012;
float g_transformedY013;
float g_transformedY014;
float g_transformedY015;
float g_transformedY016;
float g_transformedY017;
float g_transformedY018;
float g_transformedY019;
float g_transformedY020;
float g_transformedY021;
float g_transformedY022;
float g_transformedY023;
float g_transformedY024;


//深度Z (0 ～ +1)
float g_depthZ001;
float g_depthZ002;
float g_depthZ003;
float g_depthZ004;
float g_depthZ005;
float g_depthZ006;
float g_depthZ007;
float g_depthZ008;
float g_depthZ009;
float g_depthZ010;
float g_depthZ011;
float g_depthZ012;
float g_depthZ013;
float g_depthZ014;
float g_depthZ015;
float g_depthZ016;
float g_depthZ017;
float g_depthZ018;
float g_depthZ019;
float g_depthZ020;
float g_depthZ021;
float g_depthZ022;
float g_depthZ023;
float g_depthZ024;

//α
float g_alpha001;
float g_alpha002;
float g_alpha003;
float g_alpha004;
float g_alpha005;
float g_alpha006;
float g_alpha007;
float g_alpha008;
float g_alpha009;
float g_alpha010;
float g_alpha011;
float g_alpha012;
float g_alpha013;
float g_alpha014;
float g_alpha015;
float g_alpha016;
float g_alpha017;
float g_alpha018;
float g_alpha019;
float g_alpha020;
float g_alpha021;
float g_alpha022;
float g_alpha023;
float g_alpha024;


//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 col    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDx9BoardSetModel標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultBoardSet(
      float4 prm_pos    : POSITION,     // モデルの頂点
	  float  prm_index  : PSIZE ,    // モデル番号
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;
	float offsetU; //テクスチャU座標増分
	float offsetV; //テクスチャV座標増分
	float transformedX; //変換済みX座標(px)
	float transformedY; //変換済みY座標(px)
	float depthZ; //深度Z (0 ～ +1)
	float alpha; //α

	if (index == 0) {
		transformedX = g_transformedX001;
		transformedY = g_transformedY001;
		depthZ = g_depthZ001;
		offsetU  = g_offsetU001;
		offsetV  = g_offsetV001;
		alpha   = g_alpha001;
	} else if (index == 1) {
		transformedX = g_transformedX002;
		transformedY = g_transformedY002;
		depthZ = g_depthZ002;
		offsetU  = g_offsetU002;
		offsetV  = g_offsetV002;
		alpha   = g_alpha002;
	} else if (index == 2) {
		transformedX = g_transformedX003;
		transformedY = g_transformedY003;
		depthZ = g_depthZ003;
		offsetU  = g_offsetU003;
		offsetV  = g_offsetV003;
		alpha   = g_alpha003;
	} else if (index == 3) {
		transformedX = g_transformedX004;
		transformedY = g_transformedY004;
		depthZ = g_depthZ004;
		offsetU  = g_offsetU004;
		offsetV  = g_offsetV004;
		alpha   = g_alpha004;
	} else if (index == 4) {
		transformedX = g_transformedX005;
		transformedY = g_transformedY005;
		depthZ = g_depthZ005;
		offsetU  = g_offsetU005;
		offsetV  = g_offsetV005;
		alpha   = g_alpha005;
	} else if (index == 5) {
		transformedX = g_transformedX006;
		transformedY = g_transformedY006;
		depthZ = g_depthZ006;
		offsetU  = g_offsetU006;
		offsetV  = g_offsetV006;
		alpha   = g_alpha006;
	} else if (index == 6) {	
		transformedX = g_transformedX007;
		transformedY = g_transformedY007;
		depthZ = g_depthZ007;
		offsetU  = g_offsetU007;
		offsetV  = g_offsetV007;
		alpha   = g_alpha007;
	} else if (index == 7) {	
		transformedX = g_transformedX008;
		transformedY = g_transformedY008;
		depthZ = g_depthZ008;
		offsetU  = g_offsetU008;
		offsetV  = g_offsetV008;
		alpha   = g_alpha008;
	} else if (index == 8) {	
		transformedX = g_transformedX009;
		transformedY = g_transformedY009;
		depthZ = g_depthZ009;
		offsetU  = g_offsetU009;
		offsetV  = g_offsetV009;
		alpha   = g_alpha009;
	} else if (index == 9) {	
		transformedX = g_transformedX010;
		transformedY = g_transformedY010;
		depthZ = g_depthZ010;
		offsetU  = g_offsetU010;
		offsetV  = g_offsetV010;
		alpha   = g_alpha010;
	} else if (index == 10) {	
		transformedX = g_transformedX011;
		transformedY = g_transformedY011;
		depthZ = g_depthZ011;
		offsetU  = g_offsetU011;
		offsetV  = g_offsetV011;
		alpha   = g_alpha011;
	} else if (index == 11) {	
		transformedX = g_transformedX012;
		transformedY = g_transformedY012;
		depthZ = g_depthZ012;
		offsetU  = g_offsetU012;
		offsetV  = g_offsetV012;
		alpha   = g_alpha012;
	} else if (index == 12) {	
		transformedX = g_transformedX013;
		transformedY = g_transformedY013;
		depthZ = g_depthZ013;
		offsetU  = g_offsetU013;
		offsetV  = g_offsetV013;
		alpha   = g_alpha013;
	} else if (index == 13) {	
		transformedX = g_transformedX014;
		transformedY = g_transformedY014;
		depthZ = g_depthZ014;
		offsetU  = g_offsetU014;
		offsetV  = g_offsetV014;
		alpha   = g_alpha014;
	} else if (index == 14) {	
		transformedX = g_transformedX015;
		transformedY = g_transformedY015;
		depthZ = g_depthZ015;
		offsetU  = g_offsetU015;
		offsetV  = g_offsetV015;
		alpha   = g_alpha015;
	} else if (index == 15) {	
		transformedX = g_transformedX016;
		transformedY = g_transformedY016;
		depthZ = g_depthZ016;
		offsetU  = g_offsetU016;
		offsetV  = g_offsetV016;
		alpha   = g_alpha016;
	} else if (index == 16) {	
		transformedX = g_transformedX017;
		transformedY = g_transformedY017;
		depthZ = g_depthZ017;
		offsetU  = g_offsetU017;
		offsetV  = g_offsetV017;
		alpha   = g_alpha017;
	} else if (index == 17) {	
		transformedX = g_transformedX018;
		transformedY = g_transformedY018;
		depthZ = g_depthZ018;
		offsetU  = g_offsetU018;
		offsetV  = g_offsetV018;
		alpha   = g_alpha018;
	} else if (index == 18) {	
		transformedX = g_transformedX019;
		transformedY = g_transformedY019;
		depthZ = g_depthZ019;
		offsetU  = g_offsetU019;
		offsetV  = g_offsetV019;
		alpha   = g_alpha019;
	} else if (index == 19) {	
		transformedX = g_transformedX020;
		transformedY = g_transformedY020;
		depthZ = g_depthZ020;
		offsetU  = g_offsetU020;
		offsetV  = g_offsetV020;
		alpha   = g_alpha020;
	} else if (index == 20) {	
		transformedX = g_transformedX021;
		transformedY = g_transformedY021;
		depthZ = g_depthZ021;
		offsetU  = g_offsetU021;
		offsetV  = g_offsetV021;
		alpha   = g_alpha021;
	} else if (index == 21) {	
		transformedX = g_transformedX022;
		transformedY = g_transformedY022;
		depthZ = g_depthZ022;
		offsetU  = g_offsetU022;
		offsetV  = g_offsetV022;
		alpha   = g_alpha022;
	} else if (index == 22) {	
		transformedX = g_transformedX023;
		transformedY = g_transformedY023;
		depthZ = g_depthZ023;
		offsetU  = g_offsetU023;
		offsetV  = g_offsetV023;
		alpha   = g_alpha023;
	} else {	
		transformedX = g_transformedX024;
		transformedY = g_transformedY024;
		depthZ = g_depthZ024;
		offsetU  = g_offsetU024;
		offsetV  = g_offsetV024;
		alpha   = g_alpha024;
	}
                                 a
	//X座標Y座標をを -1 ～ +1 に押し込める。
	out_vs.pos.x = - 1 + ((2*prm_pos.x + 2*transformedX - 1) / g_view_width);
	out_vs.pos.y =   1 - ((2*prm_pos.y + 2*transformedY - 1) / g_view_height);
//out_vs.pos.x = - 1 + 2 * ((prm_pos.x + g_transformedX- 0.5) / g_view_width);
//out_vs.pos.y =   1 - 2 * ((prm_pos.y + g_transformedY- 0.5) / g_view_height);
//out_vs.pos.x = (2 * prm_pos.x  / g_view_width ) - 1 + (2 * g_transformedX / g_view_width);
//out_vs.pos.y = (2 * -prm_pos.y / g_view_height) + 1 - (2 * g_transformedY / g_view_height);
	out_vs.pos.z = depthZ;
	out_vs.pos.w = 1.0;
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.col  = alpha;
	return out_vs;
}


//GgafDx9BoardSetModel標準ピクセルシェーダー
float4 GgafDx9PS_DefaultBoardSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 out_color = tex2D( MyTextureSampler, prm_uv);                
	//α考慮
	out_color.a = out_color.a * prm_col.a; 
	return out_color;
}



//＜テクニック：DefaultBoardSetTechnique＞
//【機能】
//GgafDx9BoardSetModel用標準シェーダー
//【概要】
//D3DFVF_XYZRHW で描画したような仕様で２Ｄ表示します。
//画面左上隅が(0,0)で画面右下隅が（画面幅(px), 画面高さ(px))となる座標系で
//プリミティブ（板ポリ）の基点は左上隅になります。
//--- VS ---
//・頂点を -1 ～ +1へ押し込み(＝正射影変換)、Y座標反転
//--- PS ---
//・オブジェクトのテクスチャ
//・半透明α
//
//【設定グローバル】
// float g_hAlpha			:	α値
// float g_transformedX		: 	変換済みX座標(px)
// float g_transformedY		:	変換済みY座標(px)
// float g_depthZ			:	深度Z (0 ～ +1)
// float g_view_width		:	画面幅(px)
// float g_view_height		:	画面高さ(px)
// float g_offsetU			:	テクスチャU座標増分
// float g_offsetV			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
technique DefaultBoardSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoardSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultBoardSet();
	}
}


