/* �ʿ��� ������� �߰� */
#include <stdio.h>
#include <stdlib.h>


/* �Լ� ����Ʈ */



//�����Լ�
int main()
{
	char command; //��� �Է¹��� command
	int vertex;   //�߰��� ���� �Է¹��� vertex
	int edge;     
	
	printf("[----- [����] [2019038029] -----]\n");
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
		switch(command) { //������� �Է¿� ���� ��� ����
		case 'z': case 'Z':
			//�׷��� �����Լ� ȣ��
			break;
		case 'q': case 'Q':
			//�׷��� �����Ҵ� ���� �Լ� ȣ��
			break;
		case 'v': case 'V':
			printf("Add Vertex = ");
			scanf("%d", &vertex);
			//���� �߰��Լ� ȣ��
			break;
		case 'e': case 'E':
			printf("Add Edge = ");
			scanf("%d", &edge);
			//���� �߰��Լ� ȣ��
			break;
		case 'd': case 'D':
			//���� �켱Ž���Լ� ȣ��
			break;
		case 'b': case 'B':
			//�ʺ� �켱Ž���Լ� ȣ��
			break;
		case 'p': case 'P':
			//�׷��� ����Լ� ȣ��
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 0; //���α׷�����
}