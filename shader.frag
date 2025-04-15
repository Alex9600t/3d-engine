uniform sampler2D textureMap;
uniform sampler2D normalMap;
uniform sampler2D diffuseMap;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 LightPos;
in mat3 TBN;


void main() {
    vec4 pixel = texture2D(textureMap, gl_TexCoord[0].xy);
    vec3 normal = texture2D(normalMap, gl_TexCoord[0].rgb);
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);

    vec3 LightDir = normalize(LightPos - gl_FragCoord);
    float diff = max(dot(normal, LightDir), 0.0);

    vec3 color = texture(diffuseMap, TexCoord).rgb;
    vec3 lighting = color * diff;

    gl_FragColor = gl_Color * pixel + vec4(lighting, 1.0);
    // gl_FragColor = gl_Color * pixel;

}