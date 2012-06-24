xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 42;
 -3.70000;0.20000;2.83371;,
 -3.30000;0.20000;2.98958;,
 -3.30000;0.60000;-1.06319;,
 -3.70000;0.50000;-1.21907;,
 -4.40000;0.00000;0.33969;,
 -4.00000;0.10000;2.05433;,
 -4.10000;0.30000;-1.68670;,
 -4.60000;0.00000;-3.08958;,
 -2.90000;0.20000;2.83371;,
 -2.90000;0.50000;-1.21907;,
 -2.60000;0.10000;2.05433;,
 -2.20000;0.00000;0.33969;,
 -2.00000;0.00000;-3.08958;,
 -2.50000;0.30000;-1.68670;,
 -0.40000;0.20000;2.83371;,
 0.00000;0.20000;2.98958;,
 0.00000;0.60000;-1.06319;,
 -0.40000;0.50000;-1.21907;,
 -1.10000;0.00000;0.33969;,
 -0.70000;0.10000;2.05433;,
 -0.80000;0.30000;-1.68670;,
 -1.30000;0.00000;-3.08958;,
 0.40000;0.20000;2.83371;,
 0.40000;0.50000;-1.21907;,
 0.70000;0.10000;2.05433;,
 1.10000;0.00000;0.33969;,
 1.30000;0.00000;-3.08958;,
 0.80000;0.30000;-1.68670;,
 2.90000;0.20000;2.83371;,
 3.30000;0.20000;2.98958;,
 3.30000;0.60000;-1.06319;,
 2.90000;0.50000;-1.21907;,
 2.20000;0.00000;0.33969;,
 2.60000;0.10000;2.05433;,
 2.50000;0.30000;-1.68670;,
 2.00000;0.00000;-3.08958;,
 3.70000;0.20000;2.83371;,
 3.70000;0.50000;-1.21907;,
 4.00000;0.10000;2.05433;,
 4.40000;0.00000;0.33969;,
 4.60000;0.00000;-3.08958;,
 4.10000;0.30000;-1.68670;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,0,3,6;,
 4;1,8,9,2;,
 4;10,11,12,13;,
 4;8,10,13,9;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;19,14,17,20;,
 4;15,22,23,16;,
 4;24,25,26,27;,
 4;22,24,27,23;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;33,28,31,34;,
 4;29,36,37,30;,
 4;38,39,40,41;,
 4;36,38,41,37;;
 
 MeshMaterialList {
  3;
  18;
  2,
  0,
  1,
  2,
  0,
  1,
  2,
  0,
  1,
  2,
  0,
  1,
  2,
  0,
  1,
  2,
  0,
  1;;
  Material {
   0.301961;0.066667;0.035294;0.490000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.075490;0.016667;0.008824;;
  }
  Material {
   0.400000;0.090196;0.047059;0.770000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.100000;0.022549;0.011765;;
  }
  Material {
   0.501961;0.109804;0.058824;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.125490;0.027451;0.014706;;
  }
 }
 MeshNormals {
  7;
  0.000000;0.996274;0.086250;,
  -0.323430;0.943276;0.074991;,
  -0.506604;0.860441;0.054713;,
  -0.529934;0.846741;0.046902;,
  0.323430;0.943276;0.074991;,
  0.506604;0.860441;0.054713;,
  0.529934;0.846741;0.046902;;
  18;
  4;1,0,0,1;,
  4;3,2,2,3;,
  4;2,1,1,2;,
  4;0,4,4,0;,
  4;5,6,6,5;,
  4;4,5,5,4;,
  4;1,0,0,1;,
  4;3,2,2,3;,
  4;2,1,1,2;,
  4;0,4,4,0;,
  4;5,6,6,5;,
  4;4,5,5,4;,
  4;1,0,0,1;,
  4;3,2,2,3;,
  4;2,1,1,2;,
  4;0,4,4,0;,
  4;5,6,6,5;,
  4;4,5,5,4;;
 }
 MeshTextureCoords {
  42;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;;
 }
}