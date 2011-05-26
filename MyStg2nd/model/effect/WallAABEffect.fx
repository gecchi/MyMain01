#include "GgafEffectConst.fxh" 

////////////////////////////////////////////////////////////////////////////////
// WallAABActor�p�V�F�[�_�[
// �y�T�v�z
// �O�ǃu���b�N�̕`����s���B
// ���_�o�b�t�@�ɁA�O�ǃu���b�N��񂪁A�Q�O���J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� �`��ŁA�ő�
// 20�I�u�W�F�N�g�܂ŕ`��B��������_���B
// author : Masatoshi Tsuge
// date:2010/10/20
////////////////////////////////////////////////////////////////////////////////
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam;
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ���C�g�̕���
float3 g_vecLightDirection;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j  
float4 g_colLightDiffuse;  
//View�ϊ��s��
float4x4 g_matView; 
//�ˉe�ϊ��s��  
float4x4 g_matProj;  

//���[���h�ϊ��s��
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
float4x4 g_matWorld016;
float4x4 g_matWorld017;
float4x4 g_matWorld018;
float4x4 g_matWorld019;
//float4x4 g_matWorld020;

//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDx9VS_WallAAB(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_object_index  : PSIZE , // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���j
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//���[���h�ϊ��s������蓖�Ă�
	int index = (int)prm_object_index; 
	float4x4 matWorld;
	if (index == 0) {
		matWorld = g_matWorld001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
	} else if (index == 14) {
		matWorld = g_matWorld015;
	} else if (index == 15) {
		matWorld = g_matWorld016;
	} else if (index == 16) {
		matWorld = g_matWorld017;
	} else if (index == 17) {
		matWorld = g_matWorld018;
//	} else if (index == 18) {
//		matWorld = g_matWorld019;
	} else {
		matWorld = g_matWorld019;
	} 
    //�`��ʔԍ���񂪁A���[���h�ϊ��s���matWorld._14 �ɖ��ߍ��܂�Ă���
	int draw_face = matWorld._14;
    matWorld._14 = 0; //���̍s��l�ɖ߂��Ă���

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

	//World*View*�ˉe�ϊ�
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);

	//UV�͂��̂܂�
	out_vs.uv = prm_uv;

    //���_�J���[�v�Z

	//�@���� World �ϊ����Đ��K��
    float3 normal = normalize(mul(prm_normal, matWorld)); 	
    normal.x+=0.5; //�l0.5�͕ǖʂɂ����������𓖂Ă邽��
                   //���C�g�x�N�g���� XYZ=0.819232,-0.573462,0
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(normal, float3(-0.819232,0.573462,0)), 0);      
	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g���� ���l�������J���[�쐬�B      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power));// * �}�e���A���F����colMaterialDiffuse;
	//���t�H�O
	//out_vs.color.a = colMaterialDiffuse.a;
    if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }
    //���@����O�̓�
	if ( out_vs.pos.z < g_distance_AlphaTarget) {
		out_vs.color.a = (out_vs.pos.z + 1.0)  / (g_distance_AlphaTarget*2);
	}
	//�}�X�^�[��
	out_vs.color.a *= g_alpha_master;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_WallAAB(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0
) : COLOR  {
    if (prm_color.a == 0) {
        return 0;
    }
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color;

    //Blinker���l��
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
	} 
	return out_color;
}


float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color * FLUSH_COLOR;
	return out_color;
}

technique WallAABTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_WallAAB();
		PixelShader  = compile PS_VERSION GgafDx9PS_WallAAB();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile VS_VERSION GgafDx9VS_WallAAB();
		PixelShader  = compile PS_VERSION GgafDx9PS_WallAAB();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_WallAAB();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
