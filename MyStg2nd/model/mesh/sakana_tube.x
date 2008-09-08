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
 100;
 1.00000;1.00000;1.00000;,
 1.00000;1.00000;0.50000;,
 1.26516;0.55492;0.50000;,
 1.26516;0.55492;1.00000;,
 1.00000;1.00000;0.00000;,
 1.26516;0.55492;0.00000;,
 1.00000;1.00000;-0.50000;,
 1.26516;0.55492;-0.50000;,
 1.00000;1.00000;-1.00000;,
 1.26516;0.55492;-1.00000;,
 1.35355;-0.00000;0.50000;,
 1.35355;-0.00000;1.00000;,
 1.35355;-0.00000;0.00000;,
 1.35355;0.00000;-0.50000;,
 1.35355;0.00000;-1.00000;,
 1.26516;-0.55492;0.50000;,
 1.26516;-0.55492;1.00000;,
 1.26516;-0.55492;0.00000;,
 1.26516;-0.55492;-0.50000;,
 1.26516;-0.55492;-1.00000;,
 1.00000;-1.00000;0.50000;,
 1.00000;-1.00000;1.00000;,
 1.00000;-1.00000;-0.00000;,
 1.00000;-1.00000;-0.50000;,
 1.00000;-1.00000;-1.00000;,
 -1.00000;1.00000;-1.00000;,
 -1.00000;1.00000;-0.50000;,
 -1.26516;0.55492;-0.50000;,
 -1.26516;0.55492;-1.00000;,
 -1.00000;1.00000;0.00000;,
 -1.26516;0.55492;0.00000;,
 -1.00000;1.00000;0.50000;,
 -1.26516;0.55492;0.50000;,
 -1.00000;1.00000;1.00000;,
 -1.26516;0.55492;1.00000;,
 -1.35355;0.00000;-0.50000;,
 -1.35355;0.00000;-1.00000;,
 -1.35355;0.00000;0.00000;,
 -1.35355;0.00000;0.50000;,
 -1.35355;0.00000;1.00000;,
 -1.26516;-0.55492;-0.50000;,
 -1.26516;-0.55492;-1.00000;,
 -1.26516;-0.55492;0.00000;,
 -1.26516;-0.55492;0.50000;,
 -1.26516;-0.55492;1.00000;,
 -1.00000;-1.00000;-0.50000;,
 -1.00000;-1.00000;-1.00000;,
 -1.00000;-1.00000;0.00000;,
 -1.00000;-1.00000;0.50000;,
 -1.00000;-1.00000;1.00000;,
 -1.00000;1.00000;-1.00000;,
 -0.55492;1.26516;-1.00000;,
 -0.55492;1.26516;-0.50000;,
 -1.00000;1.00000;-0.50000;,
 0.00000;1.35355;-1.00000;,
 0.00000;1.35355;-0.50000;,
 0.55492;1.26516;-1.00000;,
 0.55492;1.26516;-0.50000;,
 1.00000;1.00000;-1.00000;,
 1.00000;1.00000;-0.50000;,
 -0.55492;1.26516;0.00000;,
 -1.00000;1.00000;0.00000;,
 0.00000;1.35355;0.00000;,
 0.55492;1.26516;0.00000;,
 1.00000;1.00000;0.00000;,
 -0.55492;1.26516;0.50000;,
 -1.00000;1.00000;0.50000;,
 0.00000;1.35355;0.50000;,
 0.55492;1.26516;0.50000;,
 1.00000;1.00000;0.50000;,
 -0.55492;1.26516;1.00000;,
 -1.00000;1.00000;1.00000;,
 0.00000;1.35355;1.00000;,
 0.55492;1.26516;1.00000;,
 1.00000;1.00000;1.00000;,
 -1.00000;-1.00000;1.00000;,
 -0.55492;-1.26516;1.00000;,
 -0.55492;-1.26516;0.50000;,
 -1.00000;-1.00000;0.50000;,
 -0.00000;-1.35355;1.00000;,
 -0.00000;-1.35355;0.50000;,
 0.55492;-1.26516;1.00000;,
 0.55492;-1.26516;0.50000;,
 1.00000;-1.00000;1.00000;,
 1.00000;-1.00000;0.50000;,
 -0.55492;-1.26516;0.00000;,
 -1.00000;-1.00000;0.00000;,
 0.00000;-1.35355;0.00000;,
 0.55492;-1.26516;-0.00000;,
 1.00000;-1.00000;-0.00000;,
 -0.55492;-1.26516;-0.50000;,
 -1.00000;-1.00000;-0.50000;,
 0.00000;-1.35355;-0.50000;,
 0.55492;-1.26516;-0.50000;,
 1.00000;-1.00000;-0.50000;,
 -0.55492;-1.26516;-1.00000;,
 -1.00000;-1.00000;-1.00000;,
 0.00000;-1.35355;-1.00000;,
 0.55492;-1.26516;-1.00000;,
 1.00000;-1.00000;-1.00000;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;,
 4;11,10,15,16;,
 4;10,12,17,15;,
 4;12,13,18,17;,
 4;13,14,19,18;,
 4;16,15,20,21;,
 4;15,17,22,20;,
 4;17,18,23,22;,
 4;18,19,24,23;,
 4;25,26,27,28;,
 4;26,29,30,27;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;28,27,35,36;,
 4;27,30,37,35;,
 4;30,32,38,37;,
 4;32,34,39,38;,
 4;36,35,40,41;,
 4;35,37,42,40;,
 4;37,38,43,42;,
 4;38,39,44,43;,
 4;41,40,45,46;,
 4;40,42,47,45;,
 4;42,43,48,47;,
 4;43,44,49,48;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;53,52,60,61;,
 4;52,55,62,60;,
 4;55,57,63,62;,
 4;57,59,64,63;,
 4;61,60,65,66;,
 4;60,62,67,65;,
 4;62,63,68,67;,
 4;63,64,69,68;,
 4;66,65,70,71;,
 4;65,67,72,70;,
 4;67,68,73,72;,
 4;68,69,74,73;,
 4;75,76,77,78;,
 4;76,79,80,77;,
 4;79,81,82,80;,
 4;81,83,84,82;,
 4;78,77,85,86;,
 4;77,80,87,85;,
 4;80,82,88,87;,
 4;82,84,89,88;,
 4;86,85,90,91;,
 4;85,87,92,90;,
 4;87,88,93,92;,
 4;88,89,94,93;,
 4;91,90,95,96;,
 4;90,92,97,95;,
 4;92,93,98,97;,
 4;93,94,99,98;;
 
 MeshMaterialList {
  2;
  64;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "sakana1.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "sakana2.png";
   }
  }
 }
 MeshNormals {
  19;
  -0.707107;-0.707106;0.000000;,
  -0.940184;-0.340668;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.940184;0.340668;0.000000;,
  -0.940184;0.340668;0.000000;,
  -0.707106;0.707107;0.000000;,
  0.707106;-0.707107;-0.000000;,
  0.940184;-0.340668;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.940184;0.340668;0.000000;,
  0.940184;0.340668;0.000000;,
  0.707107;0.707106;0.000000;,
  0.340668;-0.940184;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.340668;-0.940184;0.000000;,
  0.340668;0.940184;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.340668;0.940184;0.000000;;
  64;
  4;0,0,1,1;,
  4;0,0,1,1;,
  4;0,0,1,1;,
  4;0,0,1,1;,
  4;1,1,3,2;,
  4;1,1,3,3;,
  4;1,1,3,3;,
  4;1,1,2,3;,
  4;2,3,5,4;,
  4;3,3,5,5;,
  4;3,3,5,5;,
  4;3,2,4,5;,
  4;4,5,6,6;,
  4;5,5,6,6;,
  4;5,5,6,6;,
  4;5,4,6,6;,
  4;7,7,8,8;,
  4;7,7,8,8;,
  4;7,7,8,8;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;8,8,9,9;,
  4;8,8,9,9;,
  4;8,8,9,9;,
  4;9,9,11,10;,
  4;9,9,11,11;,
  4;9,9,11,11;,
  4;9,9,10,11;,
  4;10,11,12,12;,
  4;11,11,12,12;,
  4;11,11,12,12;,
  4;11,10,12,12;,
  4;7,13,13,7;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,0,0,15;,
  4;7,13,13,7;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,0,0,15;,
  4;7,13,13,7;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,0,0,15;,
  4;7,13,13,7;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,0,0,15;,
  4;12,16,16,12;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,6,6,18;,
  4;12,16,16,12;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,6,6,18;,
  4;12,16,16,12;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,6,6,18;,
  4;12,16,16,12;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,6,6,18;;
 }
 MeshTextureCoords {
  100;
  1.000000;0.000000;
  1.000000;0.250000;
  0.750000;0.250000;
  0.750000;0.000000;
  1.000000;0.500000;
  0.750000;0.500000;
  1.000000;0.750000;
  0.750000;0.750000;
  1.000000;1.000000;
  0.750000;1.000000;
  0.500000;0.250000;
  0.500000;0.000000;
  0.500000;0.500000;
  0.500000;0.750000;
  0.500000;1.000000;
  0.250000;0.250000;
  0.250000;0.000000;
  0.250000;0.500000;
  0.250000;0.750000;
  0.250000;1.000000;
  0.000000;0.250000;
  0.000000;0.000000;
  0.000000;0.500000;
  0.000000;0.750000;
  0.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.250000;1.000000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.000000;0.250000;
  0.250000;0.250000;
  0.000000;0.000000;
  0.250000;0.000000;
  0.500000;0.750000;
  0.500000;1.000000;
  0.500000;0.500000;
  0.500000;0.250000;
  0.500000;0.000000;
  0.750000;0.750000;
  0.750000;1.000000;
  0.750000;0.500000;
  0.750000;0.250000;
  0.750000;0.000000;
  1.000000;0.750000;
  1.000000;1.000000;
  1.000000;0.500000;
  1.000000;0.250000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.750000;1.000000;
  0.750000;0.750000;
  1.000000;0.750000;
  0.500000;1.000000;
  0.500000;0.750000;
  0.250000;1.000000;
  0.250000;0.750000;
  0.000000;1.000000;
  0.000000;0.750000;
  0.750000;0.500000;
  1.000000;0.500000;
  0.500000;0.500000;
  0.250000;0.500000;
  0.000000;0.500000;
  0.750000;0.250000;
  1.000000;0.250000;
  0.500000;0.250000;
  0.250000;0.250000;
  0.000000;0.250000;
  0.750000;0.000000;
  1.000000;0.000000;
  0.500000;0.000000;
  0.250000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.250000;0.000000;
  0.250000;0.250000;
  0.000000;0.250000;
  0.500000;0.000000;
  0.500000;0.250000;
  0.750000;0.000000;
  0.750000;0.250000;
  1.000000;0.000000;
  1.000000;0.250000;
  0.250000;0.500000;
  0.000000;0.500000;
  0.500000;0.500000;
  0.750000;0.500000;
  1.000000;0.500000;
  0.250000;0.750000;
  0.000000;0.750000;
  0.500000;0.750000;
  0.750000;0.750000;
  1.000000;0.750000;
  0.250000;1.000000;
  0.000000;1.000000;
  0.500000;1.000000;
  0.750000;1.000000;
  1.000000;1.000000;;
 }
}
