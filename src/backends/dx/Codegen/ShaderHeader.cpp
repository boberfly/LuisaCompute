#pragma vengine_package vengine_directx
#include <vstl/Common.h>
namespace toolhub::directx {
vstd::string_view GetHLSLHeader() {
    return R"(
#define INFINITY_f 3.40282347e+37
SamplerState samplers[16] : register(s0);

float4x4 _inverse(float4x4 m) {
	float n11 = m[0][0], n12 = m[1][0], n13 = m[2][0], n14 = m[3][0];
	float n21 = m[0][1], n22 = m[1][1], n23 = m[2][1], n24 = m[3][1];
	float n31 = m[0][2], n32 = m[1][2], n33 = m[2][2], n34 = m[3][2];
	float n41 = m[0][3], n42 = m[1][3], n43 = m[2][3], n44 = m[3][3];
	float t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
	float t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
	float t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
	float t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;
	float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;
	float idet = 1.0f / det;
	float4x4 ret;
	ret[0][0] = t11 * idet;
	ret[0][1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * idet;
	ret[0][2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * idet;
	ret[0][3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * idet;

	ret[1][0] = t12 * idet;
	ret[1][1] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * idet;
	ret[1][2] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * idet;
	ret[1][3] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * idet;

	ret[2][0] = t13 * idet;
	ret[2][1] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * idet;
	ret[2][2] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * idet;
	ret[2][3] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * idet;

	ret[3][0] = t14 * idet;
	ret[3][1] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * idet;
	ret[3][2] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * idet;
	ret[3][3] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * idet;

	return ret;
}

float3x3 _inverse(float3x3 m) {
	float3 c = float3(m[0][0], m[1][0], m[2][0]);
	float3 c2 = float3(m[0][1], m[1][1], m[2][1]);
	float3 c3 = float3(m[0][2], m[1][2], m[2][2]);
	float3 lhs = float3(c2.x, c3.x, c.x);
	float3 flt = float3(c2.y, c3.y, c.y);
	float3 rhs = float3(c2.z, c3.z, c.z);
	float3 flt2 = flt * rhs.yzx - flt.yzx * rhs;
	float3 c4 = lhs.yzx * rhs - lhs * rhs.yzx;
	float3 c5 = lhs * flt.yzx - lhs.yzx * flt;
	float rhs2 = 1.0 / dot(lhs.zxy * flt2, 1);
	return float3x3(flt2, c4, c5) * rhs2;
}
/*
////vec(["float"])
Z _acosh(Z v){return log(v + sqrt(v * v - 1));}
////vec(["float"])
Z _asinh(Z v){return log(v + sqrt(v * v + 1));}
////vec(["float"])
Z _atanh(Z v){return 0.5 * log((1 + v) / (1 - v));}
////vec(["float"])
Z _exp10(Z v){return pow(10, v);};
////vec(["float","int"])
Z _copysign(Z x, Z y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
////vec(["float"])
Z _length_sqr(Z x){ return dot(x,x);}
////vec(["float"])
Z _distance_sqr(Z x, Z y){ return _length_sqr(x - y);}
////vec(["float","uint","int"])
Z _min3(Z x, Z y, Z z){return min(x, min(y,z));}
*/
float _acosh(float v) { return log(v + sqrt(v * v - 1)); }
float2 _acosh(float2 v) { return log(v + sqrt(v * v - 1)); }
float3 _acosh(float3 v) { return log(v + sqrt(v * v - 1)); }
float4 _acosh(float4 v) { return log(v + sqrt(v * v - 1)); }
float _asinh(float v) { return log(v + sqrt(v * v + 1)); }
float2 _asinh(float2 v) { return log(v + sqrt(v * v + 1)); }
float3 _asinh(float3 v) { return log(v + sqrt(v * v + 1)); }
float4 _asinh(float4 v) { return log(v + sqrt(v * v + 1)); }
float _atanh(float v) { return 0.5 * log((1 + v) / (1 - v)); }
float2 _atanh(float2 v) { return 0.5 * log((1 + v) / (1 - v)); }
float3 _atanh(float3 v) { return 0.5 * log((1 + v) / (1 - v)); }
float4 _atanh(float4 v) { return 0.5 * log((1 + v) / (1 - v)); }
float _exp10(float v) { return pow(10, v); };
float2 _exp10(float2 v) { return pow(10, v); };
float3 _exp10(float3 v) { return pow(10, v); };
float4 _exp10(float4 v) { return pow(10, v); };
/*
float _copysign(float x, float y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
float2 _copysign(float2 x, float2 y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
float3 _copysign(float3 x, float3 y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
float4 _copysign(float4 x, float4 y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
int _copysign(int x, int y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
int2 _copysign(int2 x, int2 y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
int3 _copysign(int3 x, int3 y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
int4 _copysign(int4 x, int4 y) { (abs(sign(x) - sign(y)) > 1) ? (-x): (x); }
*/
float _length_sqr(float x) { return dot(x, x); }
float2 _length_sqr(float2 x) { return dot(x, x); }
float3 _length_sqr(float3 x) { return dot(x, x); }
float4 _length_sqr(float4 x) { return dot(x, x); }
float _distance_sqr(float x, float y) { return _length_sqr(x - y); }
float2 _distance_sqr(float2 x, float2 y) { return _length_sqr(x - y); }
float3 _distance_sqr(float3 x, float3 y) { return _length_sqr(x - y); }
float4 _distance_sqr(float4 x, float4 y) { return _length_sqr(x - y); }
float4 to_tex(float4 v) { return v; }
float4 to_tex(float2 v) { return float4(v, 1, 1); }
float4 to_tex(float3 v) { return float4(v, 1); }
uint4 to_tex(uint4 v) { return v; }
uint4 to_tex(uint2 v) { return uint4(v, 1, 1); }
uint4 to_tex(uint3 v) { return uint4(v, 1); }
int4 to_tex(int4 v) { return v; }
int4 to_tex(int2 v) { return int4(v, 1, 1); }
int4 to_tex(int3 v) { return int4(v, 1); }
bool _isnan(float x) {
	return (asuint(x) & 0x7FFFFFFF) > 0x7F800000;
}
bool2 _isnan(float2 x) {
	return (asuint(x) & 0x7FFFFFFF) > 0x7F800000;
}
bool3 _isnan(float3 x) {
	return (asuint(x) & 0x7FFFFFFF) > 0x7F800000;
}
bool4 _isnan(float4 x) {
	return (asuint(x) & 0x7FFFFFFF) > 0x7F800000;
}
bool _isinf(float x) {
	return (asuint(x) & 0x7FFFFFFF) == 0x7F800000;
}
bool2 _isinf(float2 x) {
	return (asuint(x) & 0x7FFFFFFF) == 0x7F800000;
}
bool3 _isinf(float3 x) {
	return (asuint(x) & 0x7FFFFFFF) == 0x7F800000;
}
bool4 _isinf(float4 x) {
	return (asuint(x) & 0x7FFFFFFF) == 0x7F800000;
}
#define select(a,b,c) (c ? b : a)
float4 FMul(float4 vec, float4x3 mat){
	return float4(mul(vec, mat).xyz,0);
}
bool4 GetBool(uint b){
	return bool4(
	b & 1,
	b & 256,
	b & 65536,
	b & 16777216
	);
}
uint SetBool(bool4 b){
	return (b.x ? 1 : 0) | (b.y ? 256 : 0) | (b.z ? 65536 : 0) | (b.w ? 16777216 : 0);
}

#define bfread(bf,idx) (bf[(idx)])
#define bfwrite(bf,idx,value) (bf[(idx)]=(value))
struct BdlsStruct{
	uint buffer;
	uint tex2D;
	uint tex3D;
	uint tex2DSize;
	uint tex3DSizeXY;
	uint tex3DSizeZSamp;
};
#define Smptx(tex, uv) (tex[uv])
#define Writetx(tex, uv, value) (tex[uv] = value)
#define BINDLESS_ARRAY StructuredBuffer<BdlsStruct>
Texture2D<float4> _BindlessTex[]:register(t0,space1);
Texture3D<float4> _BindlessTex3D[]:register(t0,space1);

uint2 Tex2DSize(uint tex2DSize){
	uint2 result;
	result.x = (tex2DSize & 65536);
	tex2DSize >>= 16;
	result.y = tex2DSize;
	return result;
}

uint3 Tex3DSize(
uint tex3DSizeXY,
uint tex3DSizeZSamp
){
	uint3 result;
	result.x = (tex3DSizeXY & 65536);
	tex3DSizeXY >>= 16;
	result.y = tex3DSizeXY;
	result.z = (tex3DSizeZSamp >> 16);
	return result;
}
uint2 Sampler2D3D(uint tex3DSizeZSamp){
	uint samplers = tex3DSizeZSamp & 65536;
	uint2 result;
	result.x = samplers & 255;
	result.y = (samplers >> 8);
	return result;
}

float4 SampleTex2D(BINDLESS_ARRAY arr, uint index, float2 uv, float level){
	BdlsStruct s = arr[index];
	SamplerState samp = samplers[Sampler2D3D(s.tex3DSizeZSamp).x];
	return _BindlessTex[s.tex2D].SampleLevel(samp, uv, level);
}
float4 SampleTex3D(BINDLESS_ARRAY arr, uint index, float3 uv, float level){
	BdlsStruct s = arr[index];
	SamplerState samp = samplers[Sampler2D3D(s.tex3DSizeZSamp).y];
	return _BindlessTex3D[s.tex3D].SampleLevel(samp, uv, level);
}
float4 SampleTex2D(BINDLESS_ARRAY arr, uint index, float2 uv){
	return SampleTex2D(arr, index, uv);
}
float4 SampleTex3D(BINDLESS_ARRAY arr, uint index, float3 uv){
	return SampleTex3D(arr, index, uv);
}
float4 ReadTex2D(BINDLESS_ARRAY arr,  uint index, uint2 coord, uint level){
	BdlsStruct s = arr[index]; 
	return _BindlessTex[s.tex2D].Load(uint3(coord, level));
}
float4 ReadTex3D(BINDLESS_ARRAY arr,  uint index, uint3 coord, uint level){
	BdlsStruct s = arr[index]; 
	return _BindlessTex3D[s.tex3D].Load(uint4(coord, level));
}
float4 ReadTex2D(BINDLESS_ARRAY arr,  uint index, uint2 coord){
	return ReadTex2D(arr, index, 0);
}
float4 ReadTex3D(BINDLESS_ARRAY arr, uint index,  uint3 coord){
	return ReadTex3D(arr, index, 0);
}
uint2 Tex2DSize(BINDLESS_ARRAY arr, uint index){
	BdlsStruct s = arr[index]; 
	return Tex2DSize(s.tex2DSize);
}
uint3 Tex3DSize(BINDLESS_ARRAY arr, uint index){
	BdlsStruct s = arr[index]; 
	return Tex3DSize(s.tex3DSizeXY, s.tex3DSizeZSamp);
}
uint2 Tex2DSize(BINDLESS_ARRAY arr, uint index, uint level){
	return max(Tex2DSize(arr, index) >> level, 1u);
}
uint3 Tex3DSize(BINDLESS_ARRAY arr, uint index, uint level){
	return max(Tex3DSize(arr, index) >> level, 1u);
}
#define READ_BUFFER(arr, index, bf) (bf[arr[index].buffer])
)"sv;
}
vstd::string_view GetRayTracingHeader() {
    return R"(
[shader("miss")]
void miss_hit(inout RayPayload payload)
{
	payload.v0 = 4294967295;
}
RayPayload TraceClosest(RaytracingAccelerationStructure accel, LCRayDesc rayDesc){
	RayDesc ray;
	ray.Origin = float3(rayDesc.v0.v[0], rayDesc.v0.v[1], rayDesc.v0.v[2]);
	ray.Direction = float3(rayDesc.v2.v[0], rayDesc.v2.v[1], rayDesc.v2.v[2]);
	ray.TMin = rayDesc.v1;
	ray.TMax = rayDesc.v3;
	RayPayload payload;
	TraceRay(
	accel,
	RAY_FLAG_FORCE_OPAQUE,
	~0, 0, 1, 0, ray, payload);
	return payload;
}
bool TraceAny(RaytracingAccelerationStructure accel, LCRayDesc rayDesc){
	RayDesc ray;
	ray.Origin = float3(rayDesc.v0.v[0], rayDesc.v0.v[1], rayDesc.v0.v[2]);
	ray.Direction = float3(rayDesc.v2.v[0], rayDesc.v2.v[1], rayDesc.v2.v[2]);
	ray.TMin = rayDesc.v1;
	ray.TMax = rayDesc.v3;
	RayPayload payload;
	payload.v0 = 0;
	TraceRay(
	accel,
	(RAY_FLAG_SKIP_CLOSEST_HIT_SHADER | RAY_FLAG_FORCE_OPAQUE),
	~0, 0, 1, 0, ray, payload);
	return (payload.v0 != 4294967295);
}
)"sv;
}
vstd::string_view GetClosestHitHeader() {
    return R"(
[shader("closesthit")]
void closest_hit(inout RayPayload payload, in BuiltInTriangleIntersectionAttributes attr)
{
payload.v0 = InstanceIndex();
payload.v1 = PrimitiveIndex();
payload.v2 = attr.barycentrics;
}
)"sv;
}
}// namespace toolhub::directx