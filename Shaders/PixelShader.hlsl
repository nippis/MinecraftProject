cbuffer LightCBuf
{
	float3 lightPos;
  float3 camPos;
}

Texture2D shaderTexture;
SamplerState SampleType;

static const float3 matColor = { 0.1f, 0.7f, 0.15f };
static const float3 ambient = { 0.9f, 0.9f, 0.9f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 0.1f;
static const float attConst = 1.0f;
static const float attLin = 1.0f;
static const float attQuad = 1.0f;

float4 main(float3 worldPos : POSITION, float3 n : NORMAL, float4 position : SV_POSITION, float2 texCoord : TEXCOORD) : SV_TARGET
{
  const float3 vToL = lightPos - worldPos;
  const float distToL = length(vToL);
  const float3 dirToL = vToL / distToL;
  const float3 vToCam = camPos - worldPos;
  const float distToCam = length(vToCam);
  const float3 dirToCam = vToCam / distToCam;
  
  const float3 diffuse = diffuseColor * diffuseIntensity * dot(dirToL, n);
  
  const float3 specular = 0.1 * diffuseColor * max(pow(dot(reflect(dirToL, n), dirToCam), 2), 0);
  
  float2 xd;
  
  return shaderTexture.Sample(SampleType, worldPos.xy);
  
  if ( n.x  == 1.0 )
  {
    return shaderTexture.Sample(SampleType, worldPos.xy) * float4(diffuse + ambient, 1.0f);
  }
  else
  {
    return float4(0.4, 0.2, 0.1, 1.0) * float4(diffuse + ambient, 1.0f);
  }
}