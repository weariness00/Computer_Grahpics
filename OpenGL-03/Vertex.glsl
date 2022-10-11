#version 330 core

layout (location = 0) in vec3 vPos; //--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
uniform mat4 modelTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����

void main()
{
gl_Position = modelTransform * vec4(vPos, 1.0); //--- ��ǥ���� modelTransform ��ȯ�� �����Ѵ�.
}
