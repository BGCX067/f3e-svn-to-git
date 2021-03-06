
Texture2D texture0;
SamplerState linearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Border;
    AddressV = Border;
};

matrix World;
matrix View;
matrix Projection;

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	
	output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );    
    output.Pos = mul( output.Pos, Projection );
	output.Tex = input.Tex;
	
    return output;  
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{
    return float4( 1.0f, 0.0f , 0.0f, 1.0f );
}


//--------------------------------------------------------------------------------------
technique10 Render
{
    pass P0
    {       
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
