#version 330 core
in vec4 passColor; //--- vertex shader���� �Է� ����
out vec4 FragColor; //--- ������ ���۷� ���
void main()
{
FragColor = passColor;
}