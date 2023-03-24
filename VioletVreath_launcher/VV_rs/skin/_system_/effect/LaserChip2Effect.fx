#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ���[�U�[�`�b�v�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////
/*
���[�U�[�`�b�v�͎��̂悤�ȃ��b�V���ł��邱�Ƃ��O��

 Mesh {
  8;
  0.000100;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000100;0.000000;-1.000000;,
  0.000100;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000100;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;;
  4;
  3;0,1,2;,
  3;3,4,5;,
  3;2,1,6;,
  3;5,4,7;;

  MeshNormals {
   2;
   0.000000;-1.000000;0.000000;,
   0.000000;0.000000;-1.000000;;
   4;
   3;0,0,0;,
   3;1,1,1;,
   3;0,0,0;,
   3;1,1,1;;
  }

  MeshTextureCoords {
   8;
   0.532110;0.000000;,
   0.500000;0.000000;,
   0.533110;0.999000;,
   0.532110;0.000000;,
   0.500000;0.000000;,
   0.533110;0.999000;,
   0.501000;0.999000;,
   0.501000;0.999000;;
  }

  MeshMaterialList {
   1;
   4;
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "MyOptionWateringLaserChip2001.png";
    }
   }
  }
*/
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_specular;
float g_specular_power;
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_vecLightFrom_World; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float2 uv            : TEXCOORD0;
    float4 color         : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���[�U�[�`�b�v���_�V�F�[�_�[
OUT_VS VS_LaserChip2(
      float4 prm_posModel_Local   : POSITION,   // ���f���̒��_
      float3 prm_vecNormal_Local  : NORMAL,
      float2 prm_uv               : TEXCOORD0,  // ���f���̒��_��UV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float4 prm_infront_world0   : TEXCOORD5,
      float4 prm_infront_world1   : TEXCOORD6,
      float4 prm_infront_world2   : TEXCOORD7,
      float4 prm_infront_world3   : TEXCOORD8,
      float4 prm_info             : TEXCOORD9   //x:�`�b�v���, y:������, z:�Η͗�, w:�O���`�b�v�Η͗�

) {
    OUT_VS out_vs = (OUT_VS)0;

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
    float offset_u = matWorld._14; //���[���h�ϊ��s���._14 u,v���W�� u �I�t�Z�b�g
    float offset_v = matWorld._24;  //���[���h�ϊ��s���._14 u,v���W�� u �I�t�Z�b�g
    //���̍s��l�ɖ߂��Ă���
    matWorld._14 = 0.0f;
    matWorld._24 = 0.0f;

    float4x4 matWorld_infront = {prm_infront_world0, prm_infront_world1, prm_infront_world2, prm_infront_world3};
    int kind_t = (int)(prm_info.x);
    float force_alpha = prm_info.y;
    float power;
    float4 posModel_infront_World;
    float4 posModel_own_World;
    float4 posModel_World;

    //���[�U�[�`�b�v��� �ɂ��āB
    //
    //      -==========<>            ���[�U�[��
    //
    //      -= === === === <>        ����Ȃӂ��ɕ��f����Ă��܂��B
    //
    //    | -=|===|===|===|<> |     ���}�̓��[�U�[���I�u�W�F�N�g�ŋ�؂�������̐}
    //
    //    <--><--><--><--><-->^
    //    ^   ^   ^   ^   ^   |
    //    |   |   |   |   |   |
    //    |   |   |   |   |    `----- 5:��[�`�b�v(��\���ŁA���Ԑ擪�`�b�v��\�����邽�߂����ɑ���)
    //    |   |   |   |    `----- 4:���Ԑ擪�`�b�v(�\�����������̐擪)
    //    |   |   |    `----- 3:���ԃ`�b�v
    //    |   |    `----- 3:���ԃ`�b�v
    //    |    `----- 3:���ԃ`�b�v
    //     `----- 1:�����`�b�v
    //
    //�擪�Ɛ�[�Ƃ������t�ŋ�ʂ��Ă��܂��B
    if (prm_posModel_Local.x > 0.0) {

        if (kind_t == 5) {  //4�ł͂Ȃ���
            prm_posModel_Local.x = 0;
            prm_posModel_Local.y = 0;
            prm_posModel_Local.z = 0;
        }
        // ��O���̃`�b�v���W�ւ�������
        posModel_own_World = mul( prm_posModel_Local, matWorld );
        posModel_infront_World = mul( prm_posModel_Local, matWorld_infront );  //��O���̃`�b�v��World�ϊ�
        posModel_World = lerp( posModel_own_World, posModel_infront_World, prm_posModel_Local.x );  //prm_posModel_Local.x �� 0.0 �` 1.0 �Ƃ���
        power = lerp(prm_info.z, prm_info.w, prm_posModel_Local.x ); //z ���g�̉Η͗� w �O���`�b�v�Η͗�
    } else { // prm_posModel_Local.x <= 0.0
        //���_�v�Z
        prm_posModel_Local.x = 0;
        posModel_World = mul( prm_posModel_Local, matWorld );  // World�ϊ�
        power = prm_info.z; //�Η͗�
    }
    out_vs.posModel_Proj = mul(mul(posModel_World, g_matView), g_matProj);  // View�ϊ��E�ˉe�ϊ�

    //UV�ݒ�
    if (kind_t == 3) {
        //���ԃ`�b�v
        out_vs.uv = prm_uv;
    } else if (kind_t == 2) {
        //�����`�b�v�i�悪�ۂ��j
        if (prm_uv.x < 0.51f) {
            out_vs.uv.x = 0.0f;
        } else if (prm_uv.x > 0.51f) {
            out_vs.uv.x = 1.0f;
        } else {
            out_vs.uv.x = prm_uv.x;
        }
        out_vs.uv.y = prm_uv.y;
    } else if (kind_t == 1) {
        //�����`�b�v
        out_vs.uv.x = prm_uv.x < 0.51f ? 0.0f : prm_uv.x;
        out_vs.uv.y = prm_uv.y;
    } else if (kind_t == 4) {
        //���Ԑ擪�`�b�v
        out_vs.uv.x = prm_uv.x > 0.51f ? 1.0f : prm_uv.x;
        out_vs.uv.y = prm_uv.y;
    } else {
        //��[�`�b�v
        //�����`�悵�����Ȃ�
        out_vs.uv.x = 0;
        out_vs.uv.y = 1;
    }
    //���t�H�O
    const float c = (1.25-(((out_vs.posModel_Proj.z)/g_zf)*2));
    out_vs.color = (c < 0.2  ? 0.2 : c) ;
    if (force_alpha > out_vs.color.a) {
        out_vs.color.a = force_alpha*g_alpha_master;
    } else {
        out_vs.color.a = out_vs.color.a*g_alpha_master;
    }
    out_vs.color.rgb *= power;  //power���傫���قǔ����P��
//    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
//        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
//    }

//	if (out_vs.posModel_Proj.z > g_zf*0.75) { //�ŉ��� 3/4 ��艜�̏ꍇ���X�ɓ�����
//    	out_vs.color.a *= (-1.0/(g_zf*0.25)*out_vs.posModel_Proj.z + 4.0);
//	}

    //�ȈՃt�H�O
//	out_vs.color.a = 1.0/((g_zf*0.9)*0.5))*out_vs.posModel_Proj.z - 1.0; // 1/2 ��艜�̏ꍇ���X�ɓ�����
    //out_vs.color.a = 1.0/(g_zf - (g_zf*0.75))*out_vs.posModel_Proj.z - 3.0;  // 3/4 ��艜�̏ꍇ���X�ɓ�����
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }

//�ˉe�ϊ��Ƃ�
//�E�ʂ�X��+1.0�A���ʂ�X��-1.0
//��ʂ�Y��+1.0�A���ʂ�Y��-1.0
//�O�ʁi��O�̖ʁj��Z��0.0�A�w�ʁi���̖ʁj��Z��+1.0
//g_zf:���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn
//    _zn = 0.1f;
//    _zf = -_cameraZ_org*(_dep+1.0);
//�� w =  _zf ������
//
    return out_vs;
}

float4 PS_LaserChip2(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    return tex2D( MyTextureSampler, prm_uv) * prm_color;
}

technique LaserChip2Technique
{
     pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true; //!!
        SrcBlend  = SrcAlpha;
        DestBlend = One;
        BlendOp = Max;
        SrcBlendAlpha = One;
        DestBlendAlpha = Zero;
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_LaserChip2();
        PixelShader  = compile PS_VERSION PS_LaserChip2();
    }
}


