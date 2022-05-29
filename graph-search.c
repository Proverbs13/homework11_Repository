/* �ʿ��� ������� �߰� */
#include <stdio.h>
#include <stdlib.h>
#define MAXVER 10 //���� �ִ� ���� 10�� 

//��������Ʈ���� ����� ��� ����ü
typedef struct Node {
	int vertex; // �׷��� ��尡 ���� ��
	struct Node* link; // ������ ����� �ٸ� ������ ����Ʈ�� �����ص� �ڱ����� ����ü ������
}node; //��Ī node

//�׷��� ���¸� ��Ÿ���� ����� ����ü
typedef struct Graph {
	int N; // �׷��� ���� �������� 
	node* headlist[MAXVER];
	// ��屸��ü�� ����ų (����������� ǥ����) ��� ������ �迭
	// �迭�� �ε���(0~9)�� ǥ��� �������� ����� 
	// �̿� ����� �������� ���Ḯ��Ʈ�� ��������� �迭���� ����ȴ�    

}Graph; //��Ī Graph

int visit[MAXVER]; //���� �湮���θ� Ȯ�� �� int�� �迭 visit
int PV = 0;   //���� �߰��� ���� ��¿� ��������

//bfs������ ���� ť ��� homework 5 ����
#define MAX_QUEUE_SIZE 15 //ť �ִ� ����
typedef struct {
	int queue[MAX_QUEUE_SIZE]; // ����ü �� int�� queue �迭 ����
	int front, rear;
}QueueType;  //QueueType �ڷ��� ����ü ����

int enQueue(QueueType* cQ, int item); //ť�� ���Ҹ� �����ϴ� �Լ�
int deQueue(QueueType* cQ);//ť�� ���Ҹ� �����ϴ� �Լ� 

/* �Լ� ����Ʈ */
int Initialize_Graph(Graph** g); // �׷��� �ʱ�ȭ �Լ�
int Insert_Vertex(Graph* g);    // �׷��� ���� ���� �Լ� ( ������ 0~9���� ������� ����)
int Insert_Edge(Graph* g, int u, int v); // �׷��� ���� ���� �Լ�
int vertex_locate(Graph* g, int u, int v); //���� ������ ���� ���Ḯ��Ʈ ���� ��ġ ���� �Լ�
int Print_Graph(Graph* g); //�׷��� ���� ��� �Լ�
void Free_Graph(Graph* g); //�׷��� ���� �޸� ���� �Լ�
int DFS(Graph* g, int v);   //���̿켱Ž�� �Լ�
int BFS(Graph* g, int v);   //�ʺ�켱Ž�� �Լ�


//�����Լ�
int main()
{
	char command;   //��� �Է¹��� command
	int u, v;        //������ ������ ���� �Է¹��� u,v     
	Graph* graph = NULL;       //�׷��� ����ü ������ G
	int DFSstart= 0; //dfs ������ ����
	int BFSstart= 0; //bfs ������ ����

	printf("[----- [����] [2019038029] -----]\n");
	do {
		printf("\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph    = z                                        \n");
		printf(" Insert Vertex       = v        Insert Edge           = e       \n");
		printf(" Depth First Search  = d        Breath First Search   = b       \n");
		printf(" Print Graph         = p        Quit = q              = q       \n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);
		switch (command) { //������� �Է¿� ���� ��� ����
		case 'z': case 'Z':
			Initialize_Graph(&graph);
			break;
		case 'q': case 'Q':
			Free_Graph(graph);
			break;
		case 'v': case 'V':
			Insert_Vertex(graph);
			break;
		case 'e': case 'E':
			printf("Add Edge =  (ex: 3 4) ) "); 
			scanf("%d %d", &u, &v);
			Insert_Edge(graph, u, v);
			break;
		case 'd': case 'D':
			printf("start vertex =  ");
			scanf("%d", &DFSstart);
			printf("\n DFS => ");
			DFS(graph, DFSstart);
			for (int i = 0; i < MAXVER; i++) {
				visit[i] = 0;  //���� �湮���� 0���� �ʱ�ȭ
			}
			break;
		case 'b': case 'B':
			printf("start vertex =  ");
			scanf("%d", &BFSstart);
			printf("\n BFS => ");
			BFS(graph, BFSstart);
			break;
		case 'p': case 'P':
			Print_Graph(graph);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 0; //���α׷�����
}

// �׷��� �ʱ�ȭ �Լ�
int Initialize_Graph(Graph** g) { //graph��ü�� �ּҰ� �޾ƿ�, �Լ����� *g=graph

	if ((*g) != NULL) { //�׷����� ������� ������
		Free_Graph(*g); //���� �޸� ����
	}

	(*g) = (Graph*)malloc(sizeof(Graph)); //graph �� ����Ű�� ������ �׷�������ü ũ�⸸ŭ �����Ҵ�
	(*g)->N = 0; //�׷��� ���� ���� 0
	for (int i = 0; i < MAXVER; i++) {  //�׷��� ��������͹迭�� �� �ε��� (����) �鿡 ���� ������ NULL�� �ʱ�ȭ��
		(*g)->headlist[i] = NULL;
	}
	for (int i = 0; i < MAXVER; i++) {
		visit[i] = 0;  //���� �湮���� 0���� �ʱ�ȭ
	}
	PV = 0; //���� �߰��� ����ǥ��� PV�� 0���� ����
	return 0;
}

// �׷��� ���� ���� �Լ� ( ������ 0~9���� ������� ����)
int Insert_Vertex(Graph* g) {
	//����ó��
	if (g == NULL) {  // �׷����� ������� ��
		printf("\nInitialize_Graph first.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	if ((g->N) + 1 > MAXVER) {//�׷��� �ִ� ���� �������� �� ���� �߰��Ϸ��� �Ҷ�
		printf("\nAlready the maximum number of vertices.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	printf("Add Vertex %d \n", PV);
	g->N++; //�׷��� ���� ���� ���� ex: ó�� �ѹ� �߰��� �߰��� ����= 0 , N = 1
	PV++;   //�߰��� ���� ��¿� ���� ����
	return 0; //�Լ�����
}

// �׷��� ���� ���� �Լ�  
int Insert_Edge(Graph* g, int u, int v) {
	//����ó��
	if (g == NULL) { // �׷����� ������� ��
		printf("\nInitialize_Graph first.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	if (u<0 || u>MAXVER || v<0 || v>MAXVER) { // ������ �Է��ؾ��� ������ ��� ��
		printf("\nyour vertex is not in proper range.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	//���� �ϳ��� �׷����� ���� ������ �Է����� ��
	if (u >= g->N || v >= g->N) {  // ex: ������ 3���� �߰������� ���������� 4 �̹Ƿ� >= ���
		printf("\nyour vertex is not in the graph.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	//self loop(self edge) ����
	if (u == v) {  // u= v�� ���� ��
		printf("\n not allowed self loop.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	//�̹� �����ϴ� ������ �Է� ���� ��
	node* check = g->headlist[u]; //Ȯ�ο� ��� ������ check
	while (check != NULL) {// check �� NULL�� ������ �ݺ�
		if (check->vertex == v) {//��������͹迭�� �ε��� u�϶� v�� �����������ٸ�
			printf("%d - %d Edge already exist.\n", u, v); //�ȳ��޼��� ��� 
			return 0;  //�Լ�����
		}
		check = check->link; //check �̵�
	}
	/* �Ʒ��� ���Ḯ��Ʈ �߰��κп��� �̹� u->v, v->u ���Ḯ��Ʈ�� �Ѵ� ���������Ƿ�
		u-v,v-u���� ���������� Ȯ�������� �� �� �ϳ��� üũ�ص� Ȯ�� ���� �ϴ� */

	//������ �׷����̹Ƿ� ������ ��� ������ ��� ��
	//u - v ����
	vertex_locate(g, u, v); //��屸��ü�迭�� �ε��� u������ �� v�� ���� �߰�
	//v - u  ����
	vertex_locate(g, v, u); //�μ��� �ݴ�� ���� ȣ����

	return 0;//�Լ�����
}

//���� ������ ���� ���Ḯ��Ʈ ���� ��ġ ���� �Լ� (��屸��ü�迭�� �ε��� u������ �� v�� ���� �߰�)
int vertex_locate(Graph* g, int u, int v) {
	//DFS, BFS Ž���� ���� Edge�� ���� ��� Vertex�� ��ȣ�� ���� ������ Ž���ϱ����ؼ� ���ʿ�
	//���� �߰��� ��ȣ�� ���� ������ ū ���� ������ ���� ���Ḯ��Ʈ ���� (homework6-singly-linked-list����)

	node* gn = (node*)malloc(sizeof(node)); // ������ ���� ��� ������ �����Ҵ�
	gn->vertex = v; //������ ��� �� = �߰��� ���� v
	gn->link = NULL; //��ũ�� �ӽ÷� NULL����

	//���Ḯ��Ʈ ��� ù �����϶�
	if (g->headlist[u] == NULL) {
		g->headlist[u] = gn; //��尡 ��带 ����Ű���ϰ�
		return 0;      //�Լ�����
	}

	node* searchN = g->headlist[u];  //�˻��� ����Ʈ ����ü ������
	node* lastN = g->headlist[u];    //�˻��ϸ�searchN �Ѿ�� ���� ��带 �����س��� ����ü ������

	while (searchN != NULL) {
		if (v <= searchN->vertex) {    // �ִ°��� �����ִ� ����Ʈ ������ ���� �� ������
			if (g->headlist[u] == searchN) { // ����Ʈ ù ��尪���� �ִ°��� ������ g->headlist[u] = gn�� �Ǿ��� ��
				g->headlist[u] = gn;      //����� ��,
				gn->link = searchN; //ã�� ��� ������ gn ����
			}
			else { //��������ġ�� �ƴ����� ���� ����Ʈ ������ �����ٴ� ���� ���
				gn->link = searchN; //ã�Ƴ� ���� �� ū ��� ��,
				lastN->link = gn;   //������ִ� ������� �ڷ� gn ����
			}
			return 0;// �Լ�����
		}
		lastN = searchN; //�������� �Ѿ���� searchN�� ������ lastN�� ����
		searchN = searchN->link;	//searchN�� �������� �Ѿ
	}
	//�߰��� ����� ������ �����ִ� ��� ������ �������� Ŭ �� �������� �־���
	lastN->link = gn; //��������Ʈ�� ������ ������ gn���� ����
}

//�׷��� ���� ��� �Լ�
int Print_Graph(Graph* g) {
	if (g == NULL) { // �׷����� ������� ��
		printf("Initialize_Graph first.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	node* p = NULL; //����� ���� ��������� ���� �̵��� ��� ������
	for (int i = 0; i < g->N; i++) {
		p = g->headlist[i]; // i�� �ε���(����) �� ����� �������� ���� ����� ���� �ʱ�ȭ
		printf("\n adjlist of vertex %d", i);
		while (p != NULL) { //p ��ü�� NULL�� �� ������ 
			printf(" -> %d", p->vertex); //����� ����� ���� ���� ���
			p = p->link; //p �̵�z
		}
	}
	return 0; //�Լ�����
}

//�׷��� ���� �޸� ���� �Լ�
void Free_Graph(Graph* g) {
	if (g == NULL) { // �׷����� ������� ��
		printf("Initialize_Graph first.\n"); //�ȳ��޼��� ��� 
		return;  //�Լ�����
	}
	node* dp = NULL; //���Ḯ��Ʈ�� �̵��� ���
	node* prev = NULL; //������ ���
	for (int i = 0; i < MAXVER; i++) { //i�� ������Ű�� ��������� �迭 �� ��ҿ� ����� ������ �����޸� ������
		prev = NULL; //�迭 ���� ��ҷ� ������ NULL �ʱ�ȭ
		dp = g->headlist[i]; // i�� �ε���(����)��  ����� ���������� �޸� ������ ���� dp�� ���� 
		while (dp != NULL) { //dp ��ü�� NULL�� �� ������ 
			prev = dp; //�̵� �� ����
			dp = dp->link; //dp �������� �̵�
			free(prev); // prev ��ġ ��� ���� �޸� ����
		}
	}
	free(g); //������ graph �� ����Ű�� ���� ���� �޸� ����
	return; //�Լ�����
}

//���̿켱Ž�� �Լ� = ���� ��� ���� ���� �ذ��� �ȵż� ��ͽ����� ����
int DFS(Graph* g, int v) { //v�� Ž���� ������ ����
	if (g == NULL) { // �׷����� ������� ��
		printf("Initialize_Graph first.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	if (v<0 || v>MAXVER) { // ������ �Է��ؾ��� ������ ��� ��
		printf("\nyour vertex is not in proper range.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	//���� �ϳ��� �׷����� ���� ������ �Է����� ��
	if (v >= g->N) {  // ex: ������ 3���� �߰������� ���������� 4 �̹Ƿ� >= ���
		printf("\nyour vertex is not in the graph.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	node* p = NULL;    // �̵��ϸ� Ž���� ��� ����ü������ p
	printf("%d  ", v);  // ���� ��� ���� ���
	visit[v] = 1;      // ���� v �� �湮���� 1�� üũ
	p = g->headlist[v];// p��忡 v�� �������� ��� (����� ����Ʈ ù ����) �޾ƿ�

	while (p != NULL) {// �޾ƿ� p�� NULL�϶����� �ݺ�
		if (0 == visit[p->vertex]) //���� ��ġ p����� ������ �湮���ΰ� 0 = �湮���� �ʾ��� ��
			DFS(g, p->vertex); // �� ��ġ���� DFS �ٽ� ȣ�� - ���
		p = p->link; //p�� ��������Ʈ �������� �̵�
	}
}

//�ʺ�켱Ž�� �Լ� => ť����Ͽ� ����
int BFS(Graph* g, int v) {
	if (g == NULL) { // �׷����� ������� ��
		printf("Initialize_Graph first.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	if (v<0 || v>MAXVER) { // ������ �Է��ؾ��� ������ ��� ��
		printf("\nyour vertex is not in proper range.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	//���� �ϳ��� �׷����� ���� ������ �Է����� ��
	if (v >= g->N) {  // ex: ������ 3���� �߰������� ���������� 4 �̹Ƿ� >= ���
		printf("\nyour vertex is not in the graph.\n"); //�ȳ��޼��� ��� 
		return 0;  //�Լ�����
	}
	QueueType q;// ����ü ť ����
	node* p = NULL; // �̵��ϸ� Ž���� ��� ����ü������ p
	q.front= 0; // 
	q.rear = 0; // ť �ʱ�ȭ

	printf("%d  ", v); // ���� ��� ���� ���
	enQueue(&q, v);	  // ���� ��� ���� ť�� �־���
	visit[v] = 1;             // ���� v �� �湮���� 1�� üũ
	//ť�� ������� ���� ���� �ݺ�
	while (q.front != q.rear) {
		v = deQueue(&q);  // ť���� ������ ��� �̾ƿ�
		p = g->headlist[v];  // p��忡 v�� �������� ��� (����� ����Ʈ ù ����) �޾ƿ�
		
		while (p != NULL) {// �޾ƿ� p�� NULL�϶����� �ݺ�
			//��� p�� ������ �湮���� ���� �����̶��
			if (0 == visit[p->vertex]) { 
				printf("%d  ", p->vertex); // ���� ���p ���� ���
				enQueue(&q, p->vertex);	  // ���� ���p ���� ť�� �־���
				visit[p->vertex] = 1;             // �湮���� 1�� üũ
			}
			p = p->link; //p�� ��������Ʈ �������� �̵�
		}
	}
	for (int i = 0; i < MAXVER; i++) {
		visit[i] = 0;  //���� �湮���� 0���� �ʱ�ȭ
	}
	return 0; // �Լ�����
}

//ť�� ���Ҹ� �����ϴ� �Լ�
int enQueue(QueueType* cQ, int item) {
	if (((cQ->rear) + 1) % MAX_QUEUE_SIZE == cQ->front) { //ť�� ����á�ٸ�
		return 0; //�Լ�����
	}
	cQ->rear = ((cQ->rear) + 1) % MAX_QUEUE_SIZE; //modulo ������ �̿��� ť�� rear 1ĭ �̵���Ŵ
	cQ->queue[cQ->rear] = item; //ť�� ������ �������� �� �̵��� rear �κп� �Էµ� �� �ʱ�ȭ
	return 0;//�Լ�����
}

//ť�� ���Ҹ� �����ϴ� �Լ� 
int  deQueue(QueueType* cQ) {
	if (cQ->front == cQ->rear) //ť�� ����ִٸ�
		return 0;//�Լ�����
	cQ->front = ((cQ->front) + 1) % MAX_QUEUE_SIZE; //ť�� ������� �ʴٸ� front 1ĭ ����(�̵�)
	return cQ->queue[cQ->front]; // front �� ��ȯ�ϸ� �Լ�����
}


// dfs �������� ���� �����߻����� �ڵ� �ڷḸ ����
//visit[v] = 1; //���� v �� �湮���� 1�� üũ
	//push(v); //���� v ���ÿ� Ǫ��
	//printf("DFS-> %d", v); // DFS Ž�� ���� ������ �Բ� ���
	////������ ������� ������ �ݺ� 
	//while (top != -1) {
	//	p = g->headlist[v]; //p��� ������ v�� �������� ��� (����� ���� ���Ḯ��Ʈ ù ����) �޾ƿ�
	//	//���� p��� ������ ���������� �����ϴ� ���� = ���Ḯ��Ʈ �̵��ϸ� p �� NULL�� �ɶ� ���� �ݺ�
	//	while (p != NULL) {
	//		if (0 == visit[p->vertex]) {//���� ��ġ p����� ������ �湮���ΰ� 0 = �湮���� �ʾ��� ��
	//			visit[p->vertex] = 1; //p��� ���� �湮���� 1�� üũ
	//			push(p->vertex); //p��� ���� ���ÿ� Ǫ��
	//			printf(" - %d", p->vertex); // p��� ���� ���
	//			//���� �켱Ž���� �°� �� ����� �̵�
	//			p = g->headlist[p->vertex]; //���� p ����� ������ ���� �������� �̵�
	//		}
	//		else { //������ �湮 ���� ��
	//			p = p->link; //���Ḯ��Ʈ �������� p �̵�
	//		}
	//	}// ���������� ���� �� �ݺ��� Ż��
	//	v = pop(); //�־��� ���� ��� pop �ؼ� v�� ���� -> �ٽ� �ݺ��Ǹ鼭 ���� v�� ������� p�� ����
	//}

//���� ���Լ�
//int pop() {
//	if (top == -1) {
//		printf("stack is empty.\n");
//		return 0;
//	}
//	return stack[top--];
//}
////���� Ǫ���Լ�
//int push(int key) {
//	if (top + 1 == MAXSTACK) {
//		printf("stack is full.\n");
//		return 0;
//	}
//	stack[++top] = key;
//	return 0;
//}