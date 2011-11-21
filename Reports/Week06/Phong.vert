#version 150 

in  vec4 vPosition;
in  vec3 vNormal;
in  vec2 vTexCoord;

out vec4 color;
out vec3 fragNormal;
out vec3 fPosition;
out vec2 TexCoordinates;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;
void main()
{
	TexCoordinates = vTexCoord;
    // Transform vertex  position into eye coordinates
    vec3 pos = (ModelView * vPosition).xyz;
	fPosition = pos;
    vec3 L = normalize( LightPosition.xyz - pos );
    vec3 E = normalize( -pos );
    // Transform vertex normal into eye coordinates
    vec3 N = normalize( ModelView*vec4(vNormal, 0.0) ).xyz;
    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;

    gl_Position = Projection * ModelView * vPosition;
	
	fragNormal = N;
	
    color = ambient + diffuse;
    color.a = 1.0;
}
