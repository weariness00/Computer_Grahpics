#version 330 core
in vec2 vPos; //--- ���� ���α׷����� �Է� ����
in vec4 vColor; //--- ���� ���α׷����� �Է� ����
out vec4 passColor; //--- fragment shader�� ����
void main()
{
gl_Position = vec4 (vPos.x, vPos.y, 0, 1.0);
passColor = vColor;
}
