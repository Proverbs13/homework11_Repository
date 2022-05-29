/* 필요한 헤더파일 추가 */
#include <stdio.h>
#include <stdlib.h>
#define MAXVER 10 //정점 최대 개수 10개 


//인접리스트에서 사용할 노드 구조체
typedef struct Node {
	int vertex; // 그래프 노드가 가질 값
	struct Node* link; // 정점에 연결된 다른 정점을 리스트로 연결해둘 자기참조 구조체 포인터
}node; //별칭 node

//그래프 형태를 나타낼때 사용할 구조체
typedef struct Graph {
	int N; // 그래프 현재 정점개수 
	node* headlist[MAXVER];
	// 노드구조체를 가리킬 (연결되있음을 표시할) 헤드 포인터 배열
	// 배열의 인덱스(0~9)를 표기상 정점으로 사용해 
	// 이와 연결된 정점들이 연결리스트로 헤드포인터 배열에서 연결된다    
	
}Graph; //별칭 Graph

int visit[MAXVER]; //정점 방문여부를 확인 할 int형 배열 visit

int PV = 0;   //현재 추가될 정점 출력용 전역변수




/* 함수 리스트 */
int Initialize_Graph(Graph** g); // 그래프 초기화 함수
int Insert_Vertex(Graph* g);    // 그래프 정점 생성 함수 ( 정점은 0~9까지 순서대로 생성)
int Insert_Edge(Graph* g, int u, int v); // 그래프 간선 생성 함수
int vertex_locate(Graph* g, int u, int v); //간선 생성시 내부 연결리스트 정점 위치 설정 함수
int Print_Graph(Graph* g); //그래프 정보 출력 함수
void Free_Graph(Graph* g); //그래프 동적 메모리 해제 함수
int DFS(Graph* g, int v);   //깊이우선탐색 함수

//메인함수
int main()
{
	char command;   //명령 입력받을 command
	int u, v;        //간선을 연결할 정점 입력받을 u,v     
	Graph* graph = NULL;       //그래프 구조체 포인터 G
	int DFSstart; //dfs 시작할 정점
	int BFSstart; //bfs 시작할 정점

	printf("[----- [이찬] [2019038029] -----]\n");
	do {
		printf("\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph    = z                                       \n");
		printf(" Insert Vertex       = v        Insert Edge           = e \n");
		printf(" Depth First Search  = d        Breath First Search   = b \n");
		printf(" Print Graph         = p        Quit = q              = q \n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);
		switch (command) { //사용자의 입력에 따른 명령 실행
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
				visit[i] = 0;  //정점 방문여부 0으로 초기화
			}
			break;
		case 'b': case 'B':
			//너비 우선탐색함수 호출
			break;
		case 'p': case 'P':
			Print_Graph(graph);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 0; //프로그램종료
}

// 그래프 초기화 함수
int Initialize_Graph(Graph** g) { //graph자체의 주소값 받아옴, 함수에서 *g=graph

	if ((*g) != NULL) { //그래프가 비어있지 않으면
		Free_Graph(*g); //먼저 메모리 해제
	}

	(*g) = (Graph*)malloc(sizeof(Graph)); //graph 가 가리키는 공간에 그래프구조체 크기만큼 동적할당
	(*g)->N = 0; //그래프 정점 개수 0
	for (int i = 0; i < MAXVER; i++) {  //그래프 헤드포인터배열의 각 인덱스 (정점) 들에 대한 포인터 NULL로 초기화함
		(*g)->headlist[i] = NULL;
	}
	for (int i = 0; i < MAXVER; i++) {
		visit[i] = 0;  //정점 방문여부 0으로 초기화
	}

	PV = 0; //현재 추가될 정점표기용 PV을 0으로 설정
	return 0;
}

// 그래프 정점 생성 함수 ( 정점은 0~9까지 순서대로 생성)
int Insert_Vertex(Graph* g) {
	//예외처리
	if (g == NULL) {  // 그래프가 비어있을 때
		printf("\nInitialize_Graph first.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	if ((g->N) + 1 > MAXVER) {//그래프 최대 정점 개수보다 더 많이 추가하려고 할때
		printf("\nAlready the maximum number of vertices.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	printf("Add Vertex %d \n", PV);
	g->N++; //그래프 정점 개수 증가 ex: 처음 한번 추가시 추가된 정점= 0 , N = 1
	PV++;   //추가될 정점 출력용 변수 증가
	return 0; //함수종료
}

// 그래프 간선 생성 함수  
int Insert_Edge(Graph* g, int u, int v) {
	//예외처리
	if (g == NULL) { // 그래프가 비어있을 때
		printf("\nInitialize_Graph first.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	if (u<0 || u>MAXVER || v<0 || v>MAXVER) { // 정점이 입력해야할 범위를 벗어날 때
		printf("\nyour vertex is not in proper range.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	//둘중 하나라도 그래프에 없는 정점을 입력했을 때
	if (u >= g->N || v >= g->N) {  // ex: 정점이 3까지 추가됬으면 정점개수는 4 이므로 >= 사용
		printf("\nyour vertex is not in the graph.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	//self loop(self edge) 제외
	if (u == v) {  // u= v가 같을 때
		printf("\n not allowed self loop.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	//이미 존재하는 정점을 입력 했을 때
	node* check = g->headlist[u]; //확인용 노드 포인터 check
	while (check != NULL) {// check 가 NULL일 때까지 반복
		if (check->vertex == v) {//헤드포인터배열의 인덱스 u일때 v인 정점을가진다면
			printf("%d - %d Edge already exist.\n", u, v); //안내메세지 출력 
			return 0;  //함수종료
		}
		check = check->link; //check 이동
	}
	/* 아래의 연결리스트 추가부분에서 이미 u->v, v->u 연결리스트를 둘다 만들어버리므로
		u-v,v-u간선 존재유무의 확인절차는 둘 중 하나만 체크해도 확인 가능 하다 */

		//무방향 그래프이므로 양쪽을 모두 연결해 줘야 함
		//u - v 연결
	vertex_locate(g, u, v); //헤드구조체배열의 인덱스 u정점에 값 v인 정점 추가
	//v - u  연결
	vertex_locate(g, v, u); //인수를 반대로 돌려 호출함

	return 0;//함수종료
}

//간선 생성시 내부 연결리스트 정점 위치 설정 함수 (헤드구조체배열의 인덱스 u정점에 값 v인 정점 추가)
int vertex_locate(Graph* g, int u, int v) {
	//DFS, BFS 탐색시 여러 Edge가 있을 경우 Vertex의 번호가 작은 순으로 탐색하기위해서 애초에
	//간선 추가시 번호가 작은 정점이 큰정점 앞으로 들어가게 연결리스트 구현 (homework6-singly-linked-list참조)

	node* gn = (node*)malloc(sizeof(node)); // 연결할 정점 노드 포인터 동적할당
	gn->vertex = v; //생성한 노드 값 = 추가한 정점 v
	gn->link = NULL; //링크는 임시로 NULL설정

	//연결리스트 노드 첫 생성일때
	if (g->headlist[u] == NULL) {
		g->headlist[u] = gn; //헤드가 노드를 가리키게하고
		return 0;      //함수종료
	}

	node* searchN = g->headlist[u];  //검색용 리스트 구조체 포인터
	node* lastN = g->headlist[u];    //검색하며searchN 넘어갈때 이전 노드를 저장해놓을 구조체 포인터

	while (searchN != NULL) {
		if (v <= searchN->vertex) {    // 넣는값이 원래있던 리스트 값보다 작을 때 노드삽입
			if (g->headlist[u] == searchN) { // 리스트 첫 노드값보다 넣는값이 작을때 g->headlist[u] = gn이 되야할 때
				g->headlist[u] = gn;      //헤드노드 뒤,
				gn->link = searchN; //찾은 노드 앞으로 gn 연결
			}
			else { //헤드다음위치는 아니지만 원래 리스트 노드들의 값보다는 작을 경우
				gn->link = searchN; //찾아낸 값이 더 큰 노드 앞,
				lastN->link = gn;   //저장되있던 이전노드 뒤로 gn 연결
			}
			return 0;// 함수종료
		}
		lastN = searchN; //다음으로 넘어가기전 searchN의 연결경로 lastN에 저장
		searchN = searchN->link;	//searchN은 다음으로 넘어감
	}
	//추가할 노드의 정점이 원래있던 모든 노드들의 정점보다 클 때 마지막에 넣어줌
	lastN->link = gn; //원래리스트의 마지막 연결을 gn으로 해줌
}



//그래프 정보 출력 함수
int Print_Graph(Graph* g) {
	if (g == NULL) { // 그래프가 비어있을 때
		printf("Initialize_Graph first.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	node* p = NULL; //연결된 정점 정보출력을 위한 이동용 노드 포인터
	for (int i = 0; i < g->N; i++) {
		p = g->headlist[i]; // i번 인덱스(정점) 과 연결된 정점들의 정보 출력을 위해 초기화
		printf("\n adjlist of vertex %d", i);
		while (p != NULL) { //p 자체가 NULL이 될 때까지 
			printf(" -> %d", p->vertex); //노드의 연결된 정점 정보 출력
			p = p->link; //p 이동z
		}
	}
	return 0; //함수종료
}

//그래프 동적 메모리 해제 함수
void Free_Graph(Graph* g) {
	if (g == NULL) { // 그래프가 비어있을 때
		printf("Initialize_Graph first.\n"); //안내메세지 출력 
		return;  //함수종료
	}
	node* dp = NULL; //연결리스트를 이동할 노드
	node* prev = NULL; //삭제용 노드
	for (int i = 0; i < MAXVER; i++) { //i를 증가시키며 헤드포인터 배열 각 요소에 연결된 노드들의 동적메모리 해제함
		prev = NULL; //배열 다음 요소로 가기전 NULL 초기화
		dp = g->headlist[i]; // i번 인덱스(정점)를  연결된 정점노드들의 메모리 해제를 위해 dp에 대입 
		while (dp != NULL) { //dp 자체가 NULL이 될 때까지 
			prev = dp; //이동 전 저장
			dp = dp->link; //dp 다음으로 이동
			free(prev); // prev 위치 노드 동적 메모리 해제
		}
	}
	free(g); //메인의 graph 가 가리키는 공간 동적 메모리 해제
	return; //함수종료
}


//깊이우선탐색 함수 = 스택 사용 구현 오류발생 해결 실패로 재귀식으로 구현
int DFS(Graph* g, int v) { //v는 탐색을 시작할 정점
	if (g == NULL) { // 그래프가 비어있을 때
		printf("Initialize_Graph first.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	if (v<0 || v>MAXVER) { // 정점이 입력해야할 범위를 벗어날 때
		printf("\nyour vertex is not in proper range.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}
	//둘중 하나라도 그래프에 없는 정점을 입력했을 때
	if (v >= g->N) {  // ex: 정점이 3까지 추가됬으면 정점개수는 4 이므로 >= 사용
		printf("\nyour vertex is not in the graph.\n"); //안내메세지 출력 
		return 0;  //함수종료
	}

	node* p = NULL;    // 이동하며 탐색할 노드 구조체포인터 p
	visit[v] = 1;      // 정점 v 의 방문여부 1로 체크
	printf("%d  ", v);  // 현재 노드 정점 출력
	p = g->headlist[v];// p노드 정점에 v의 인접정점 노드 (연결된 리스트 첫 정점) 받아옴
	
	while(p!=NULL){// 받아온 p가 NULL일때까지 반복
		if (0 == visit[p->vertex]) //현재 위치 p노드의 정점의 방문여부가 0 = 방문하지 않았을 때
			DFS(g, p->vertex); // 그 위치에서 DFS 다시 호출
		p = p->link; //p는 인접리스트 다음으로 이동
	}

	
}




// dfs 스택으로 구현 오류발생으로 코드 자료만 저장

//visit[v] = 1; //정점 v 의 방문여부 1로 체크
	//push(v); //정점 v 스택에 푸시
	//printf("DFS-> %d", v); // DFS 탐색 시작 정점과 함께 출력
	////스택이 비어있을 때까지 반복 
	//while (top != -1) {
	//	p = g->headlist[v]; //p노드 정점에 v의 인접정점 노드 (연결된 정점 연결리스트 첫 정점) 받아옴
	//	//현재 p노드 정점의 인접정점이 존재하는 동안 = 연결리스트 이동하며 p 가 NULL이 될때 까지 반복
	//	while (p != NULL) {
	//		if (0 == visit[p->vertex]) {//현재 위치 p노드의 정점의 방문여부가 0 = 방문하지 않았을 때
	//			visit[p->vertex] = 1; //p노드 정점 방문여부 1로 체크
	//			push(p->vertex); //p노드 정점 스택에 푸시
	//			printf(" - %d", p->vertex); // p노드 정점 출력
	//			//깊이 우선탐색에 맞게 더 깊숙히 이동
	//			p = g->headlist[p->vertex]; //현재 p 노드의 정점의 인접 정점으로 이동
	//		}
	//		else { //정점을 방문 했을 때
	//			p = p->link; //연결리스트 다음노드로 p 이동
	//		}
	//	}// 인접정점이 없을 때 반복문 탈출
	//	v = pop(); //넣어준 스택 요소 pop 해서 v에 대입 -> 다시 반복되면서 정점 v의 인접노드 p에 연결
	//}

//스택 팝함수
//int pop() {
//	if (top == -1) {
//		printf("stack is empty.\n");
//		return 0;
//	}
//	return stack[top--];
//}
////스택 푸시함수
//int push(int key) {
//	if (top + 1 == MAXSTACK) {
//		printf("stack is full.\n");
//		return 0;
//	}
//	stack[++top] = key;
//	return 0;
//}