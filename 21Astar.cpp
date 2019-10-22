#include "1.h"

A_Star::A_Star(const char pImportMap[RowNumber][ColumnNumber])
{
    if (!initMap(pImportMap))
    {
        exit(0);
    }
}

A_Star::~A_Star()
{

}

bool A_Star::initMap( const char pImportMap[RowNumber][ColumnNumber] )
{
    bool isHaveStart,isHaveEnd;
    isHaveStart = isHaveEnd = false;//����Ƿ��������յ�

    for(int i=0;i<RowNumber;i++)
    {
        for(int j=0;j<ColumnNumber;j++)
        {
            m_StarNode[i][j].m_cSymbol = pImportMap[i][j];
            m_StarNode[i][j].m_X=i;
            m_StarNode[i][j].m_Y=j;
            if(m_StarNode[i][j].m_cSymbol=='s')
            {
                m_StarNode[i][j].m_Type = Node_Start;
                m_StarNode[i][j].m_Gvalue=0;
                m_StarNode[i][j].m_IsFind=true;
                isHaveStart = true;
                m_StarStart=m_StarNode[i][j];
            }
            else if(m_StarNode[i][j].m_cSymbol=='e')
            {
                m_StarNode[i][j].m_Type = Node_End;
                m_StartEnd=m_StarNode[i][j];
                isHaveEnd = true;
            }
            else if(m_StarNode[i][j].m_cSymbol=='x')
            {
                m_StarNode[i][j].m_Type = Node_Barrier;
            }
            else
            {
                m_StarNode[i][j].m_Type = Node_Way;
            }
        }
    }
    if (!isHaveStart)
    {
        cout<<"Where will We Start"<<endl;
    }
    else if(!isHaveEnd)
    {
        cout<<"Where will We Go ?"<<endl;
    }
    return (isHaveStart&&isHaveEnd);
}

bool A_Star::isOverBorder(int nX,int nY)
{
    if (nX < 0 || nX >= RowNumber || nY < 0 || nY >= ColumnNumber)
    {
        return true;
    }
    return false;
}


//�����پ���Ϊ��|x1 - x2| + |y1 - y2|
float A_Star::manhattanDis(int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y)
{
    float hVal;
    hVal=(float)abs(nDisStart_x-nDisEnd_x)+abs(nDisStart_y-nDisEnd_y);
    hVal*=ManhattanSacle;
    return hVal;
}

//��Ȩ������ better
float A_Star::jiaquan_manhattanDis( int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y )
{
    float hVal,dx,dy;
    dx=(float)abs(nDisStart_x-nDisEnd_x);
    dy=(float)abs(nDisStart_y-nDisEnd_y);
    if(dx>dy)
        hVal=10*dx+6*dy;
    else
        hVal=6*dx+10*dy;
    return hVal;
}

//ŷ�Ͼ���Ϊ�� sqrt((x1-x2)^2+(y1-y2)^2 )
float A_Star::euclideanDis( int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y )
{
    float hVal;
    hVal=(float)sqrt(pow((nDisStart_x-nDisEnd_x),2)+pow((nDisStart_y-nDisEnd_y),2));
    return hVal;
}

//�б�ѩ�����Ϊ��max(|x1 - x2| , |y1 - y2|)
float A_Star::chebyshevDis( int nDisStart_x,int nDisStart_y,int nDisEnd_x,int nDisEnd_y )
{
    float hVal;
    hVal=(float)max(abs(nDisStart_x-nDisEnd_x),abs(nDisStart_y-nDisEnd_y));
    return hVal;
}

void A_Star::AstarAlgorithm()
{
    priority_queue<myNode> openQueue;//open��

    openQueue.push(m_StarStart);//����ʼ��ѹ��open��
    myNode currNode,*neighborNode;
    int nNeighborX,nNeighborY;  //�ھӵ�x��y����, �ھ������ѡ�����Gֵƫ��
    float offsetG;
    while(!openQueue.empty())//oepn��Ϊ��һֱѭ��
    {
        currNode = openQueue.top();//ÿ����Ԫ�ز��붼���������myNode �����˲�������� < ��ÿ�ζ���ͷ��Ԫ�ص�Fֵ��С

        if (currNode == m_StartEnd)//��ǰ�ڵ�Ϊ�յ㣬�˳�
        {
            break;
        }
        openQueue.pop();//������
    //  printRoute();
        for (int i=0;i<NeighborNum;++i)//�����ýڵ���ھ�
        {
            //��������ƫ�����ҵ��ھ�
            nNeighborX = currNode.m_X + offset[i][0];
            nNeighborY = currNode.m_Y + offset[i][1];
            //�ھӽڵ㳬���߽磬�ϰ�����ҹ��˶�����
            if (isOverBorder(nNeighborX,nNeighborY))
            {
                continue;
            }
            neighborNode = &m_StarNode[nNeighborX][nNeighborY];//�ҵ��ھӽڵ����Ϣ
            if (neighborNode->m_IsFind || neighborNode->m_Type == Node_Barrier)
            {
                continue;
            }

            //���� �����滻��ͬ���㷨��ѡ�����õ�h(x)
            neighborNode->m_Hvalue = jiaquan_manhattanDis(nNeighborX,nNeighborY,m_StartEnd.m_X,m_StartEnd.m_Y);

            offsetG = 1.0f;//���ǶԽ��ߵ��ھӣ�Ĭ�� 1 �����룬�൱��һ������
            if (offset[i][0]!=0 && offset[i][1]!=0)//˵���ǶԶԽ����ϵ��ھ�
            {
                offsetG = 1.4f;//ȡ����ֵ,���ڼ���,1.4������
            }

            //��ûѹ��open�� ����
            //������ھ�֮ǰ��Gֵ(Gֵ������ѡ���׽ڵ�ǰ����õ���)С�ڴ��¼����Gֵ(�Ե�ǰ��Ϊ���ڵ�����)
            //���ھӽڵ�ĸ��ڵ�Ҫ�����ģ�ָ��ǰ�ڵ���Ϊ���ڵ�, ��Ϊ�����ֵ��С�����۸���
            if(neighborNode->m_Gvalue == 0 || neighborNode->m_Gvalue>currNode.m_Gvalue+offsetG)
            {
                neighborNode->m_ParentNode = &m_StarNode[currNode.m_X][currNode.m_Y];
                neighborNode->m_Gvalue = currNode.m_Gvalue+offsetG;
            }

            neighborNode->m_IsFind = true;//�����ҹ���

            openQueue.push(*neighborNode);
        }
    }
}

bool A_Star::findRoute()
{
    myNode* pNode = m_StarNode[m_StartEnd.m_X][m_StartEnd.m_Y].m_ParentNode;//���ڵ㣬���յ�
    if (pNode == NULL)
    {
        cout<<"�ӵ���������û��·�����Ե����յ�"<<endl;
        return false;
    }
    //�����յ㣬һ����������
    while (pNode)
    {
        if (pNode->m_ParentNode)
        {
            pNode->m_Type = Node_FindWay;
        }
        pNode = pNode->m_ParentNode;
    }
    return true;
}

void A_Star::printRoute()
{
    int nFindNum = 0;//ͳ�Ʊ����Ľڵ���
    for(int i=0;i<RowNumber;i++)
    {
        for(int j=0;j<ColumnNumber;j++)
        {
            if (m_StarNode[i][j].m_IsFind)//ͳ�Ʊ����Ľڵ���
            {
                nFindNum++;
            }
            if(m_StarNode[i][j].m_Type==Node_FindWay)//�ҵ���·
                cout<<FindWay;//<<"F:"<<m_StarNode[i][j].m_Gvalue+m_StarNode[i][j].m_Hvalue;
            else if(m_StarNode[i][j].m_IsFind)//�ҹ��ĵط�
            {
                if (m_StarNode[i][j].m_Type == Node_Way)
                {
                    cout<<HaveFindPlace;//<<"F:"<<m_StarNode[i][j].m_Gvalue+m_StarNode[i][j].m_Hvalue;
                }
                else
                {
                    cout<<m_StarNode[i][j].m_cSymbol;
                }
            }
            else
                cout<<m_StarNode[i][j].m_cSymbol;
        }
        cout<<endl;
    }
    cout<<"������ "<<nFindNum<<" ���ڵ㣬�����ҵ���·"<<endl;
}
