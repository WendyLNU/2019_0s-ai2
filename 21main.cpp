#include "1.h"

int main()
{
    //�Զ���һ����ͼ ��RowNumber * ColumnNumber����С
    //'s':��ʼ���ַ�
    //'e':�յ��ַ�
    //'x':�ϰ����ַ�
    //'.':��ͨ����
    char chMapDraw[RowNumber][ColumnNumber] =
    {
        { '.','.','.','x','x','x','.','.'},
        { '.','.','.','.','.','x','x','.'},
        { '.','x','.','x','.','x','.','e'},
        { '.','x','.','x','.','x','.','.'},
        { 's','x','.','.','.','x','.','x'},
        { '.','x','.','.','.','.','.','.'},
    };

    //��ʼ����ͼ
    A_Star Astar(chMapDraw);

    //A*�㷨
    Astar.AstarAlgorithm();

    //�ҵ�·��
    if (Astar.findRoute())
    {
        Astar.printRoute();//��ӡ·��
    }

    getchar();
}
