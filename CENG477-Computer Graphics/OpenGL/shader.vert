#version 410

layout(location = 0) in vec3 position;

uniform mat4 MVP; 
uniform mat4 MV; 
uniform vec3 cameraPosition;
uniform float heightFactor;
uniform float moveFactor;
uniform int lightSourceMoveModifierX;
uniform int lightSourceMoveModifierY;
uniform int lightSourceMoveModifierZ;

uniform sampler2D heightMapTexture;
uniform sampler2D rgbTexture;
uniform int widthTexture;
uniform int heightTexture;

out vec2 textureCoordinate; 
out vec3 vertexNormal; 
out vec3 ToLightVector; 
out vec3 ToCameraVector; 


void main()
{
    int horizontalStep = int (250*(position.x/widthTexture));
    float alpha=2*3.14159265*horizontalStep/250;
    
    int verticalStep=int (125*(position.z/heightTexture));
    float beta= 3.14159265*verticalStep/125;


    float textureX = (alpha-3.1415926 + moveFactor)/(2*3.14159265);
    
    textureCoordinate = vec2(textureX,
                            beta/3.14159265); 

    vec3 heightMapColor = texture2D(heightMapTexture, textureCoordinate).xyz;

    float radiusMultiplier= heightFactor * heightMapColor.y*350.0 /255.0 + 350.0;

    vec3 myPos = vec3(radiusMultiplier * sin(beta)*cos(alpha),
                radiusMultiplier * sin(beta)*sin(alpha),
                radiusMultiplier * cos(beta));
  
    vertexNormal = normalize(vec3(sin(beta)*cos(alpha),sin(beta)*sin(alpha),cos(beta))) ;

    ToCameraVector = normalize(cameraPosition - myPos);

    ToLightVector = normalize(vec3(-lightSourceMoveModifierX - myPos.x ,
                                    lightSourceMoveModifierY + 1600 - myPos.y,
                                    lightSourceMoveModifierZ - myPos.z));
    
    gl_Position =  MVP * vec4(myPos,1);
}