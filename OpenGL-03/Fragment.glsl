#version 330 core

uniform vec4 vColor;
in vec4 prismColor;

out vec4 FragColor; //--- ������ ���۷� ���
void main()
{
	FragColor = prismColor;
	if(vColor.w > 0)
		FragColor = vColor;
}