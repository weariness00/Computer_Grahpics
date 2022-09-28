#version 330 core
in vec2 vPos; //--- 메인 프로그램에서 입력 받음
in vec4 vColor; //--- 메인 프로그램에서 입력 받음
out vec4 passColor; //--- fragment shader로 전달
void main()
{
gl_Position = vec4 (vPos.x, vPos.y, 0, 1.0);
passColor = vColor;
}
