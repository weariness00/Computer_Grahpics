#version 330 core
uniform vec4 vColor;
out vec4 FragColor; //--- 프레임 버퍼로 출력
void main()
{
FragColor = vColor;
}