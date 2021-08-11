#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node* lchild;
	struct node* rchild;
} BTNode;
//�����ŷ�����������
void CreateBTNode(BTNode*& b, const char* str)
{
	BTNode* St[MaxSize], * p = NULL;
	int top = -1, k=0, j = 0;
	char ch;
	b = NULL;
	ch = str[j];
	while (ch != '\0')
	{
		switch (ch)
		{
		case '(':top++; St[top] = p; k = 1; break;
		case ')':top--; break;
		case ',':k = 2; break;
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch; p->lchild = p->rchild = NULL;
			if (b == NULL)
				b = p;
			else
			{
				switch (k)
				{
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}
//Ѱ�ҽ��
BTNode* FindNode(BTNode* b, ElemType x)
{
	BTNode* p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
		return b;
	else
	{
		p = FindNode(b->lchild, x);
		if (p != NULL)
			return p;
		else
			return FindNode(b->rchild, x);
	}
}
//�������
int Total(BTNode* b)
{
	if (b != NULL)
		return Total(b->lchild) + Total(b->rchild) + 1;
	else
		return 0;
}
//�������
bool InOrderTraverse(BTNode* b)
{
	if (b == NULL)
		return false;
	else
	{
		InOrderTraverse(b->lchild);
		printf("%c ", b->data);
		InOrderTraverse(b->rchild);
		return true;
	}
}
//��α���
void LevelTraverse(BTNode* b)
{
	BTNode* p;
	BTNode* Queue[MaxSize];
	int front, rear;
	front = rear = -1;
	rear++;
	Queue[rear] = b;
	while (front != rear)
	{
		front = (front + 1) % MaxSize;
		p = Queue[front];
		printf("%c ", p->data);
		if (p->lchild != NULL)
		{
			rear = (rear + 1) % MaxSize;
			Queue[rear] = p->lchild;
		}
		if (p->rchild != NULL)
		{
			rear = (rear + 1) % MaxSize;
			Queue[rear] = p->rchild;
		}
	}
}
//��������ĸ߶�
int BTNodeHeight(BTNode* b)
{
	int lchildh, rchildh;
	if (b == NULL) return(0);
	else
	{
		lchildh = BTNodeHeight(b->lchild);
		rchildh = BTNodeHeight(b->rchild);
		return (lchildh > rchildh) ?  (lchildh + 1) : (rchildh + 1);
	}
}
//�������������
void PrintBTNode(BTNode* root, int level)
{
	if (root != NULL){
		PrintBTNode(root->rchild, level + 1);

		if (level != 0)
		{
			for (int i = 0; i < 4 * (level - 1); i++) {
				printf("%s", " ");
			}
			printf("%s", "---");
		}
		printf("%c", root->data);
		printf("\n");
		PrintBTNode(root->lchild, level + 1);
	}
}


int main()
{
	BTNode* b;
	const char* str = "1(2,3(4(6,),5))";
	CreateBTNode(b, str);//����������
	printf("�������������:\n");
	PrintBTNode(b, 0);
	printf("���ҽ��3��%c\n", FindNode(b, '3')->data);
	printf("�������ĸ߶ȣ�%d\n", BTNodeHeight(b));
	printf("���ĸ���Ϊ:%d",Total(b));
	printf("\n");
	printf("�������:");
	InOrderTraverse(b); printf("\n");
	printf("��α���:");
	LevelTraverse(b); printf("\n");

}