#version 150 

uniform vec4 LightPosition;
uniform float Shininess;
uniform vec4 DiffuseProduct, SpecularProduct;
in vec3 fPosition; // fragment position in view space
in vec4 color;     // colour computed in the vertex shader (diffuse and ambient)
in vec3 fragNormal;
in vec2 TexCoordinates;
out vec4 fColor;
uniform sampler2D LennaTexture;

void main() 
{
    vec3 normal = normalize( fragNormal );
	vec3 Lm = normalize(LightPosition.xyz - fPosition.xyz);
	vec3 Rm = 2 *( dot(Lm, normal) * normal ) - Lm;
	vec3 specular = SpecularProduct.rgb * max( pow( dot(Rm, normalize(-fPosition) ), Shininess ), 0.0);
    fColor = color + vec4(specular, 1.0); // use this line for phong shading
    //fColor = texture2D(LennaTexture, TexCoordinates) + vec4(specular, 1.0); // use this line for texturing
} 

