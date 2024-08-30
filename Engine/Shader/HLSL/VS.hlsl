#include "IL.hlsli"

cbuffer Transform : register(B0) { matrix Former; }
cbuffer Transform : register(B1) { matrix Latter; }

Pixel VS(const Vertex Input)
{
    Pixel Output =
    {
        Input.Position,
        Input.TexCoord
    };
    
	Output.Position = mul(Former, Output.Position);
	Output.Position = mul(Latter, Output.Position);

    return Output;
}