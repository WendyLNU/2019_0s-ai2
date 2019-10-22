#pragma once
#include <stdio.h>
#include <iostream>
#include <queue>
#include <math.h>
#include <stdlib.h>
using namespace std;

//�����Ƿ�����߶Խ��ߵĺ�
#define WALK_DIAGONAL

#ifdef WALK_DIAGONAL

#define NeighborNum 8       //�ھӸ���
static int offset[NeighborNum][2]={{1,0},{1,1},{1,-1},{-1,0},{-1,-1},{-1,1},{0,-1},{0,1}};//�ھӵ�����ѡ��

#else

#define NeighborNum 4   //�ھӸ���
static int offset[NeighborNum][2]={{1,0},{-1,0},{0,-1},{0,1}};//�ھӵ�����ѡ��

#endif

//�����ά����ĳ���
#define RowNumber 6
#define ColumnNumber 8

//���������پ�����������
#define ManhattanSacle 10 //10��

enum NodeType
{
    Node_Start = 0,     //��ʼ��
    Node_Barrier,       //�ϰ�������в���ͨ���ĵ㶼��Ϊ���ϰ���
    Node_Way,           //��ͨ�е�·
    Node_FindWay,       //����Ѱ·�󣬻ᾭ���ĵ�
    Node_End,           //�յ�
    Node_Null,          //δ����ĵ�
};

//�����ҵ���·���ķ��ű�ʾ
#define FindWay '*' //�����ҵ���·���ķ��ű�ʾ
#define HaveFindPlace 'o'//�ҹ��ĵط��ķ��ű�ʾ

//����һ���ڵ�����ݽṹ
struct myNode
{
    myNode()
    {
        m_ParentNode = NULL;
        m_Type = Node_Null;
        m_X = m_Y = 0;
        m_Gvalue = 0;
        m_Hvalue = 0;
        m_ParentNode = NULL;
        m_IsFind = false;
    }
    char m_cSymbol;     //�ýڵ�ķ���
    int m_Type;         //�ýڵ������
    int m_X;            //�ڵ��X����
    int m_Y;            //�ڵ��Y����
    float m_Gvalue;     //g(x)  Gֵ
    float m_Hvalue;     //h(x)  Hֵ
    myNode* m_ParentNode;   //�ýڵ�ָ��ĸ��ڵ�
    bool m_IsFind;      //�ýڵ��Ƿ��ҹ�

    //��Fֵ��= G + H�� ��С��������FֵС�����ȼ���
    friend bool operator<(myNode nNodeA,myNode nNodeB)
    {
        return (nNodeA.m_Gvalue+nNodeA.m_Hvalue > nNodeB.m_Gvalue+nNodeB.m_Hvalue);
    }

    //���ز����� ==
    friend bool operator==(myNode nNodeA,myNode nNodeB)
    {
        return (nNodeA.m_X == nNodeB.m_X &&  nNodeA.m_Y == nNodeB.m_Y);
    }
};

class A_Star
{
public:

    A_Star(const char pImportMap[RowNumber][ColumnNumber]);

    ~A_Star();

protected:

    //��ʼ����ͼ
    bool initMap(const char pImportMap[RowNumber][ColumnNumber]);

    //�����پ���Ϊ��|x1 - x2| + |y1 - y2|
    float manhattanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //��Ȩ�����پ��� better  �������Ϊʲô�����
    float jiaquan_manhattanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //ŷ�Ͼ���Ϊ�� sqrt((x1-x2)^2+(y1-y2)^2 )
    float euclideanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //�б�ѩ�����Ϊ��max(|x1 - x2| , |y1 - y2|)
    float chebyshevDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y);

    //��С�ȽϺ���
    int max(int a,int b)
    {
        return a>b?a:b;
    }


//����ӿ�
public:

    //�жϽڵ��Ƿ񳬹��߽�
    //return true �����߽磬false��δ����
    bool isOverBorder(int nX,int nY);

    //A*�����㷨
    void AstarAlgorithm();

    //�ҵ�·��·��
    bool findRoute();

    //��ӡ��·��
    void printRoute();


private:

    myNode  m_StarNode[RowNumber][ColumnNumber];    //�洢���нڵ���
    myNode  m_StarStart;        //��ʼ�ڵ�
    myNode  m_StartEnd;         //�յ�ڵ�
};
