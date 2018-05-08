#include "GgafEffectConst.fxh" 

////////////////////////////////////////////////////////////////////////////////
// CubeMapMassWallActor�p�V�F�[�_�[
// �y�T�v�z
// �O�ǃv���Y���̕`����s���B
// ���_�o�b�t�@�ɁA�O�ǃv���Y����񂪁A10���J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� �`��ŁA�ő�
// 10�I�u�W�F�N�g�܂ŕ`��B��������_���B
// author : Masatoshi Tsuge
// date:2011/01/10
////////////////////////////////////////////////////////////////////////////////
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_reflectance;
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_wall_dep;    //�ǃu���b�N�̒����iX���W�������j
float g_wall_height; //�ǃu���b�N�̍����iY���W�������j
float g_wall_width;  //�ǃu���b�N�̕��iZ���W������)

float g_ah_POS_PRISM_ZX;
float g_fh_POS_PRISM_ZX;
float g_ah_POS_PRISM_YZ;
float g_fh_POS_PRISM_YZ;
float g_ah_POS_PRISM_XY;
float g_fh_POS_PRISM_XY;


float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ���C�g�̕���
float3 g_vecLightFrom_World;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j  
float4 g_colLightDiffuse;  
//View�ϊ��s��
float4x4 g_matView; 
//�ˉe�ϊ��s��  
float4x4 g_matProj;  

#define POS_PRISM_xx_NN    1 
#define POS_PRISM_xx_NP    2 
#define POS_PRISM_xx_PN    4 
#define POS_PRISM_xx_PP    8 
#define POS_PRISM_XY_xx    16
#define POS_PRISM_YZ_xx    32
#define POS_PRISM_ZX_xx    64

//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
sampler BumpMapTextureSampler : register(s2);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj   : POSITION;
	float2 uv              : TEXCOORD0;
	float4 color           : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   //���_�̖@���x�N�g��(���[���h���W�n)
    float3 vecEye_World    : TEXCOORD2;   //���_�̎���(���_->���_)�x�N�g��(���[���h���W�n)
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDxVS_CubeMapMassWall(
      float4 prm_posModel_Local   : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local  : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv               : TEXCOORD0 ,    // ���f���̒��_��UV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float2 prm_info             : TEXCOORD5
) {
	OUT_VS out_vs = (OUT_VS)0;

	int draw_face = (int)(prm_info.x);
    //UV�ɂ��ǂ̖ʂ̒��_�����f���A
    //�`��s�v�Ȗʂ̒��_�̏ꍇ�͉��Ƃ�����i�W�I���g���V�F�[�_�[�g�������G�j

    //draw_face�͕Ǖ����Ƀr�b�g�������Ă���
    //&b 00abcdef
    //
    //���}��BOX�̓W�J������Ԃ̐}
    //
    //                   ^y
    //              z��  | 
    //                 \ | 
    //                  c| 
    // ----���@��--- a b d f ---- -> x
    //                   |e
    //                   | \
    //                   |  \   
	//  u v
	// (0,0)      0.25                     ��u
	//       +------+------+------+------+
	//       |      |        Z+          |
	//       |      |       ��c          |
	//  0.25 +  X+  +--------------------+
	//       | ��f  |        Y-          |
	//       |      |       ��d          |
	//   0.5 +------+--------------------+
	//       |      |        Y+          |
	//       |      |       ��a          |
	//  0.75 +  X-  +--------------------+
	//       | ��b  |        Z-          |
	//       |      |       ��e          |
	//       +------+------+------+------+
	//    ��                                (1,1)
	//    v

    //                          00abcdef
  	if (draw_face >= 32) {  //&b00100000
        draw_face -= 32;
    } else {
        //���(��a)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x && 
            0.5  < prm_uv.y && prm_uv.y < 0.75 ) 
		{
            return out_vs;
        }
    }

    //                          00abcdef
  	if (draw_face >= 16) {  //&b00010000
        draw_face -= 16;
    } else {
        //����(��b)���`��s�v�̏ꍇ
        if (                   prm_uv.x < 0.25 &&
            0.5  < prm_uv.y                       ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
  	if (draw_face >= 8) {   //&b00001000
        draw_face -= 8;
    } else {
        //������(��c)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x && 
                               prm_uv.y < 0.25 ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
   	if (draw_face >= 4) {   //&b00000100
        draw_face -= 4;
    } else {
        //���(��d)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.25 < prm_uv.y && prm_uv.y < 0.5 ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
  	if (draw_face >= 2) {   //&b00000010
        draw_face -= 2;
    } else {
        //�E����(��e)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.75 < prm_uv.y                    ) 
		{
            return out_vs;
        } 
    }
    //                          00abcdef
  	if (draw_face >= 1) {   //&b00000001
       // draw_face -= 1;
    } else {
        //����������(��f)���`��s�v�̏ꍇ
        if (                    prm_uv.x < 0.25 &&
                                prm_uv.y < 0.5    ) 
		{
            return out_vs;
        }
    }

	int pos_info = (int)(prm_info.y);

	if (pos_info == 0) {
        //BOX
	} else if (pos_info >= POS_PRISM_ZX_xx) {   
        //BOX�̂P�ʂ𖳗������ăv���Y���^�ɕό`������
		//�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
		// ZX �� XZ���ʂƌ���
		pos_info -= POS_PRISM_ZX_xx;
		if (pos_info == POS_PRISM_xx_PP) {
			prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))       - ((prm_posModel_Local.x-g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		} else if (pos_info == POS_PRISM_xx_PN) {
			prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))) + ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		} else if (pos_info == POS_PRISM_xx_NP) { 
			prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))       + ((prm_posModel_Local.x-g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		} else { //if (pos_info == POS_PRISM_xx_NN) {
			prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))) - ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		}
	} else if (pos_info >= POS_PRISM_YZ_xx) {   
		//�{Z -Z �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
		pos_info -= POS_PRISM_YZ_xx;
		if (pos_info == POS_PRISM_xx_PP) {
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))       - ((prm_posModel_Local.z-g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		} else if (pos_info == POS_PRISM_xx_PN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))) + ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		} else if (pos_info == POS_PRISM_xx_NP) { 
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))       + ((prm_posModel_Local.z-g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		} else { //if (pos_info == POS_PRISM_xx_NN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))) - ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		}
	} else { //if (pos_info >= POS_PRISM_XY_xx) {   
		pos_info -= POS_PRISM_XY_xx;
		//�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
		if (pos_info == POS_PRISM_xx_PP) {
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))       - ((prm_posModel_Local.x-g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		} else if (pos_info == POS_PRISM_xx_PN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))       + ((prm_posModel_Local.x-g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		} else if (pos_info == POS_PRISM_xx_NP) { 
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))) + ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		} else { //if (pos_info == POS_PRISM_xx_NN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))) - ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		}
	}
	//����
	//(prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))   �E�E�E ��[���L���b�Ƃ܂Ƃ߂�v�Z
	//+ ((prm_posModel_Local.x-fh)*ah);                      �E�E�E ��[�𐅕��ɂ���v�Z

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
	//World*View*�ˉe�ϊ�
    const float4 posModel_World = mul(prm_posModel_Local, matWorld);        //World �ϊ�
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //View*�ˉe �ϊ�
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	//�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld)); 	
    out_vs.vecNormal_World.x+=0.5; //�l0.5�͕ǖʂɂ����������𓖂Ă邽��
                   //���C�g�x�N�g���� XYZ=0.819232,-0.573462,0 �Œ�B�Ƃ肠�����B
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(out_vs.vecNormal_World, float3(-0.819232,0.573462,0)), 0);      
// const float power = max(dot(out_vs.vecNormal_World, -g_vecLightFrom_World ), 0); //�{��

	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g���� ���l�������J���[�쐬�B      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power));// * �}�e���A���F����colMaterialDiffuse;
    //�u���_���J�������_�v�����x�N�g��
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);

	//���t�H�O
	//out_vs.color.a = colMaterialDiffuse.a;
//    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
//        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
//    }
    
    if (out_vs.posModel_Proj.z > out_vs.posModel_Proj.w) {
        out_vs.posModel_Proj.z = out_vs.posModel_Proj.w;
    }
    //���@����O�̓�
	if ( out_vs.posModel_Proj.z < g_distance_AlphaTarget) {
		out_vs.color.a = (out_vs.posModel_Proj.z + 1.0)  / (g_distance_AlphaTarget*2);
	}
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDxPS_CubeMapMassWall(
	float2 prm_uv              : TEXCOORD0,
    float4 prm_color           : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
    if (prm_color.a == 0) {
        discard;
    }

    const float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World));
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        const float3 vecHarf = normalize(prm_vecEye_World + float3(-0.819232,0.573462,0));
        //const float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));  //�{��
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 colOut = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinker���l��
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }

    colOut.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master;

	return colOut;
}


float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	const float4 colTex = tex2D( MyTextureSampler, prm_uv);        
	float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
	return colOut;
}

technique CubeMapMassWallTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMassWall();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMassWall();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMassWall();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMassWall();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMassWall();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
