#include<stdio.h>
#include<stdlib.h>

#define TIME 100 //ֻ����100��
#define MAXSIZE 100
int n=1;
int result[9]={1,2,3,8,0,4,7,6,5};//0�ǿո�
typedef struct Node{
    int num[9];
    char expension;//��¼�Ƿ������չ��Y���ԣ�N������
    char banOperate;/*��ʾ����ִ�еĲ�����L���������ƣ�
R���������ƣ�U���������ƣ�D���������ƣ�
C������������ƶ�*/
    int father;//���ڵ���±�
}Node;
Node store[MAXSIZE];//����������״̬�洢��������

int same(int temp)//�ж��Ƿ�ﵽ��Ŀ��״̬
{
    for(int j=0;j<9;j++)

        if(store[temp].num[j]!=result[j])
            return 0;
        return 1;

}

void printResult()//����������
{
    for(int j=1;j<=n;j++)
    {
        printf("��%d��������:\n",j);
        printf("\t%d\t%d\t%d\n",
        store[j].num[0],store[j].num[1],store[j].num[2]);
        printf("\t%d\t%d\t%d\n",
        store[j].num[3],store[j].num[4],store[j].num[5]);
        printf("\t%d\t%d\t%d\n",
        store[j].num[6],store[j].num[7],store[j].num[8]);
        printf("\n\n");
    }
}

int left(int temp)//���ո�����
{
    int o;
    for(int j=0;j<9;j++)//�жϿո�λ��
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==0||o==3||o==6)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o-1];//�ƶ����״̬
    store[n].num[o-1]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='L';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

int right(int temp)//���ո�����
{
    int o;
    for(int j=0;j<9;j++)//�жϿո�λ��
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==2||o==5||o==8)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o+1];//�ƶ����״̬
    store[n].num[o+1]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='R';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

int up(int temp)//���ո�����
{
    int o;
    for(int j=0;j<9;j++)//�жϿո�λ��
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==0||o==1||o==2)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o-3];//�ƶ����״̬
    store[n].num[o-3]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='U';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

int down(int temp)//���ո�����
{
    int o;
    for(int j=0;j<9;j++)//�жϿո�λ��
    {
        if(store[temp].num[j]==0)
            o=j;
        break;
    }
    if(o==6||o==7||o==8)
        return 0;
    for(int k=0;k<9;k++)
        store[n].num[k]=store[temp].num[k];
    int tempNum=store[n].num[o+3];//�ƶ����״̬
    store[n].num[o+3]=0;
    store[n].num[o]=tempNum;
    store[temp].expension='N';
    store[n].banOperate='D';
    store[n].expension='Y';
    store[n].father=temp;

    if(same(n))
    {

        printResult();
        exit(1);
    }
    n++;
    return 1;
}

void init()
{
    Node start;
    printf("�������ʼ״̬���ÿո�ֿ���0����ո�:\n");//�����ʼ״̬
    for(int i=0;i<9;i++)
        scanf("%d",&start.num[i]);
    for(int k=0;k<9;k++)
        if(start.num[k]==0)
            break;
    start.banOperate='C';
    start.expension='Y';
    start.father=-1;
    store[0]=start;
}//����ʼ״̬����store[0]

int main()
{
    init();
    if(same(0))
    {
        printf("û�б�Ҫ��������");
        exit(1);
    }


    for(int i=0;i<TIME;i++)
    {
        if(store[i].expension=='Y')
        {
            if(store[i].banOperate=='L')
            {
                up(i);
                right(i);
                down(i);
            }
             if(store[i].banOperate=='R')
            {
                left(i);
                up(i);
                down(i);
            }
             if(store[i].banOperate=='U')
            {
                left(i);
                right(i);
                down(i);
            }
             if(store[i].banOperate=='D')
            {
                left(i);
                up(i);
                right(i);
            }
             if(store[i].banOperate=='C')
            {
                left(i);
                up(i);
                right(i);
                down(i);
            }
        }
        if(n>=TIME)
        {
            n--;
            printResult();
            printf("��������Χ��û�н��");
            exit(1);
        }
    }
    return 0;
}













