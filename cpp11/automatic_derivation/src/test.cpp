#include <iostream>
#include <vector>

int main() {
    // �ñ������ڱ��������Ƶ������������ͣ�����ͨ��=�ұߵ������Ƶ�������������
    auto a = 10;  // 10��int�ͣ������Զ��Ƶ���a��int
    std::cout << a << std::endl;

    // �����auto�����Ƶ��������ͣ���decltype�������Ƶ����ʽ���ͣ�����ֻ���ڱ������������ʽ�����ͣ����ʽʵ�ʲ����������
    const int &i = 1;
    int x = 2;
    decltype(i) b = 2;  // b��const int&
}