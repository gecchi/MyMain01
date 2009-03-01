xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


Frame Box01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,-0.000000,0.000000,-0.000000,1.000000;;
 }

 Mesh {
  8;
  -1.000000;-1.000000;1.000000;,
  1.000000;-1.000000;1.000000;,
  -1.000000;1.000000;1.000000;,
  1.000000;1.000000;1.000000;,
  -1.000000;-1.000000;-1.000000;,
  1.000000;-1.000000;-1.000000;,
  -1.000000;1.000000;-1.000000;,
  1.000000;1.000000;-1.000000;;
  12;
  3;0,3,2;,
  3;3,0,1;,
  3;4,7,5;,
  3;7,4,6;,
  3;0,5,1;,
  3;5,0,4;,
  3;1,7,3;,
  3;7,1,5;,
  3;3,6,2;,
  3;6,3,7;,
  3;2,4,0;,
  3;4,2,6;;

  MeshNormals {
   6;
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;-1.000000;0.000000;,
   1.000000;0.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   -1.000000;0.000000;0.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;5,5,5;;
  }

  MeshTextureCoords {
   24;
   0.258544;0.500000;,
   0.258544;0.244957;,
   0.368668;0.658514;,
   0.368668;0.403471;,
   0.200508;0.719266;,
   0.200508;0.974309;,
   0.455559;0.719266;,
   0.455559;0.974309;,
   0.705015;0.822935;,
   0.705015;0.567892;,
   0.013587;0.500000;,
   0.013587;0.244957;,
   0.960066;0.822935;,
   0.960066;0.567892;,
   0.331008;0.027174;,
   0.586059;0.027174;,
   0.706912;0.160328;,
   0.961962;0.160328;,
   0.613626;0.658514;,
   0.613626;0.403471;,
   0.706912;0.405285;,
   0.961962;0.405285;,
   0.331008;0.272131;,
   0.586059;0.272131;;
  }

  MeshMaterialList {
   1;
   12;
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
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "testtex.png";
    }
   }
  }
 }
}