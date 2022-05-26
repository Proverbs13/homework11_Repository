/* 필요한 헤더파일 추가 */
#include <stdio.h>
#include <stdlib.h>


/* 함수 리스트 */



//메인함수
int main()
{
	char command; //명령 입력받을 command
	int vertex;   //추가할 정점 입력받을 vertex
	int edge;     
	
	printf("[----- [이찬] [2019038029] -----]\n");
	do{
		printf("\n\n");
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
		switch(command) { //사용자의 입력에 따른 명령 실행
		case 'z': case 'Z':
			//그래프 선언함수 호출
			break;
		case 'q': case 'Q':
			//그래프 동적할당 해제 함수 호출
			break;
		case 'v': case 'V':
			printf("Add Vertex = ");
			scanf("%d", &vertex);
			//정점 추가함수 호출
			break;
		case 'e': case 'E':
			printf("Add Edge = ");
			scanf("%d", &edge);
			//정점 추가함수 호출
			break;
		case 'd': case 'D':
			//깊이 우선탐색함수 호출
			break;
		case 'b': case 'B':
			//너비 우선탐색함수 호출
			break;
		case 'p': case 'P':
			//그래프 출력함수 호출
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 0; //프로그램종료
}