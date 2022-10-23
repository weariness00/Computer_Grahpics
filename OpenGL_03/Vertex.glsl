#version 330 core

layout (location = 0) in vec3 vPos; //--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
layout (location = 1) in vec4 vPrismColor;

uniform mat4 modelTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����
out vec4 prismColor;

void main()
{
	gl_Position = modelTransform * vec4(vPos, 1.0); //--- ��ǥ���� modelTransform ��ȯ�� �����Ѵ�.
	if(vPrismColor.w == 1)
		prismColor = vPrismColor;
}
