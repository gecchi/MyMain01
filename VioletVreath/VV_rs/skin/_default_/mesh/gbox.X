xof 0303txt 0032
template AnimTicksPerSecond {
 <9e415a43-7ba6-4a73-8743-b73d47e88476>
 DWORD AnimTicksPerSecond;
}

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

template Animation {
 <3d82ab4f-62da-11cf-ab39-0020af71e433>
 [...]
}

template AnimationSet {
 <3d82ab50-62da-11cf-ab39-0020af71e433>
 [Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]
}


AnimTicksPerSecond {
 4800;
}

Frame Box01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh {
  20;
  -20.10000;-5.100000;-5.100000;,
  20.10000;5.100000;-5.100000;,
  20.10000;-5.100000;-5.100000;,
  -20.10000;5.100000;-5.100000;,
  -20.10000;-5.100000;5.100000;,
  20.10000;5.100000;5.100000;,
  -20.10000;5.100000;5.100000;,
  20.10000;-5.100000;5.100000;,
  -20.10000;-5.100000;-5.100000;,
  20.10000;-5.100000;5.100000;,
  -20.10000;-5.100000;5.100000;,
  20.10000;-5.100000;-5.100000;,
  20.10000;-5.100000;5.100000;,
  20.10000;5.100000;-5.100000;,
  20.10000;5.100000;-5.100000;,
  -20.10000;5.100000;5.100000;,
  20.10000;5.100000;5.100000;,
  -20.10000;5.100000;-5.100000;,
  -20.10000;5.100000;-5.100000;,
  -20.10000;-5.100000;5.100000;;
  12;
  3;0,1,2;,
  3;1,0,3;,
  3;4,5,6;,
  3;5,4,7;,
  3;8,9,10;,
  3;9,8,11;,
  3;2,5,12;,
  3;5,2,13;,
  3;14,15,16;,
  3;15,14,17;,
  3;18,19,6;,
  3;19,18,0;;

  MeshNormals {
   18;
   0.000000;0.000000;-1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   1.000000;0.000000;-0.000000;,
   1.000000;-0.000000;0.000000;,
   1.000000;0.000000;0.000000;,
   1.000000;0.000000;-0.000000;,
   0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   0.000000;1.000000;-0.000000;,
   -1.000000;-0.000000;-0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;-0.000000;-0.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,4,3;,
   3;4,2,5;,
   3;6,8,7;,
   3;8,6,9;,
   3;10,12,11;,
   3;12,10,13;,
   3;14,16,15;,
   3;16,14,17;;
  }

  MeshTextureCoords {
   20;
   1.000000;1.000000;,
   0.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;,
   0.000000;0.000000;,
   1.000000;1.000000;,
   0.000000;1.000000;,
   1.000000;0.000000;;
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
   }
  }
 }
}

AnimationSet default {
 
}