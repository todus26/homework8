/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { 							// node를 구조체로 선언
	int key;									// key값을 저장할 변수						
	struct node *left;							// 왼쪽 자식 노드를 가리키는 포인터
	struct node *right;							// 오른쪽 자식 노드를 가리키는 포인터
} Node;

int initializeBST(Node** h); 					// headNode에 메모리를 할당하는 함수 선언

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  			/* recursive inorder traversal */
void preorderTraversal(Node* ptr);    			/* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  			/* recursive postorder traversal */
int insert(Node* head, int key);  				/* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  		/* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  	/* search the node for the key */
Node* searchIterative(Node* head, int key); 	/* search the node for the key */
int freeBST(Node* head); 						/* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL; 							// Node에 대한 포인터 head 선언 
	Node* ptr = NULL;	/* temp */ 				// Node에 대한 포인터 변수 ptr 선언

	do{
		printf("----------[정새연] [2023041074]----------\n");

		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { 						// command에 따라서 다른 함수 호출
		case 'z': case 'Z':                 	// z를 입력하면 
			initializeBST(&head);				// initializeBST 함수(head의 주소를 매개변수로 갖는) 호출 후, 메모리 할당
			break;
		case 'q': case 'Q':						// q를 입력하면					
			freeBST(head);						// freeBST 함수 호출을 통해 head에 할당된 메모리 해제
			break;
		case 'n': case 'N':						// n을 입력하면		
			printf("Your Key = ");
			scanf("%d", &key);					// key 값을 입력받아서
			insert(head, key);				 	// insert 함수 호출을 통해 key 값을 가진 노드를 트리에 추가
			break;
		case 'd': case 'D': 					// d를 입력하면
			printf("Your Key = ");
			scanf("%d", &key);					// key 값을 입력받아서
			deleteLeafNode(head, key);      	// deleteLeafNode 함수 호출을 통해 key 값을 가지는 단말 노드 삭제
			break;
		case 'f': case 'F':          	   		// f를 입력하면
			printf("Your Key = ");
			scanf("%d", &key);					// key 값을 입력받아서
			ptr = searchIterative(head, key);	// searchIterative 함수 호출을 통해 반복적 탐색 결과를 ptr에 저장
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); 	// ptr이 NULL이 아니라면 해당 노드의 key와 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':												// s를 입력하면
			printf("Your Key = ");
			scanf("%d", &key);											// key 값을 입력받아서
			ptr = searchRecursive(head->left, key);						// searchRecursive 함수 호출을 통해 재귀적 탐색 결과를 ptr에 저장
			if(ptr != NULL)												// ptr이 NULL이 아니라면			
				printf("\n node [%d] found at %p\n", ptr->key, ptr);	// 결과 출력
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':									// i를 입력하면
			inorderTraversal(head->left);					// inorderTraversal 함수 호출 (중위 순회 함수)
			break;
		case 'p': case 'P':									// p를 입력하면							
			preorderTraversal(head->left);					// preorderTraversal 함수 호출 (전위 순회 함수)
			break;
		case 't': case 'T':									// t를 입력하면			
			postorderTraversal(head->left);					// postorderTraversal 함수 호출 (후위 순회 함수)			
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); 				// q가 입력될 때까지 반복

	return 1; 												// 프로그램 종료
}

int initializeBST(Node** h) {			// headNode에 메모리를 할당하는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)						// head가 NULL이 아니라면
		freeBST(*h);					// freeBST 함수 호출을 통해 head에 할당된 메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));	// h에 메모리 할당
	(*h)->left = NULL;	/* root */		// h의 left 생성
	(*h)->right = *h;					// h의 right에 포인터 h 저장
	(*h)->key = -9999;					// h의 key를 -9999로 초기화
	return 1;							// 함수 종료
}



void inorderTraversal(Node* ptr) 		// LVR식으로 출력
{
	if (ptr != NULL) 					// ptr이 NULL이 아니라면
	{
		inorderTraversal(ptr->left); 	// 순환 호출을 통해서 ptr이 가장 왼쪽 자식을 가리키게 하고
		printf("[%d]   ",ptr->key); 	// ptr의 key 값 출력
		inorderTraversal(ptr->right); 	// 오른쪽 자식으로 이동
	}
}

void preorderTraversal(Node* ptr) 		// VLR식으로 출력
{
	if (ptr != NULL) 					// ptr이 NULL이 아니라면
	{
		printf("[%d]   ", ptr->key); 	// ptr의 key 출력 (현재 트리에서 가장 위에 있는 노드의 key)
		preorderTraversal(ptr->left); 	// 순환 호출을 통해서 ptr이 왼쪽으로 가면서 왼쪽 자식들 프린트
		preorderTraversal(ptr->right);  // 오른쪽 자식들 프린트
	}
}

void postorderTraversal(Node* ptr) 		// LRV식으로 출력
{
	if (ptr != NULL) 					// ptr이 NULL이 아니라면
	{
		postorderTraversal(ptr->left); 	// 순환 호출을 통해서 ptr이 가장 왼쪽 자식을 가리키게 하고
		postorderTraversal(ptr->right);	// 오른쪽 자식으로 이동
		printf("[%d]   ", ptr->key); 	// ptr의 key 프린트
	}
}

int insert(Node* head, int key)					// key 값을 가진 노드를 트리에 추가
{
	Node* node = (Node*)malloc(sizeof(Node));	// 새로운 노드 생성
	Node* temp;									// 임시 노드 		
	node->key = key;							// key 자리에 입력받은 key 값 저장
	node->left = NULL;							// 왼쪽 자식 노드를 NULL로 초기화
	node->right = NULL;							// 오른쪽 자식 노드를 NULL로 초기화			
	
	if (head->left == NULL) {					// 비어있는 트리라면
		head->left = node;						// head의 left에 node 저장	
		return 0;								// 종료
	}

	else 										// 트리가 비어있지 않다면
	{
		temp = head->left; 						// temp는 트리의 첫 번째 원소 가리킴
		while (temp->left!=NULL || temp->right != NULL )	// temp의 left나 right가 NULL이 아니라면
		{
			if (temp->key >= key) 				// temp가 가리키는 곳의 key가 key보다 크거나 같다면
			{
				if (temp->left == NULL)			// temp의 left가 NULL이라면
					break;						// 반복문 탈출
				temp = temp->left;				// temp의 left로 이동
			}
			else
			{
				if (temp->right == NULL)		// temp의 right가 NULL이라면
					break;						// 반복문 탈출	
				temp = temp->right;				// temp의 right로 이동
			}
		}

		if (temp->key >= key) 	// temp의 key가 key보다 크거나 같다면 temp의 left가 node
		{
			temp->left = node;
		}
		else 					// 아니라면 temp의 right가 node
		{
			temp->right = node;
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)		// key 값을 가지는 단말 노드 삭제
{
	Node* temp,* pre;						// temp와 pre 노드 선언
	if (head->left == NULL) 				// 트리가 이미 비어있다면 
		printf("tree is empty\n");
	else //아니라면
	{
		pre = head;							// pre는 head를 가리킴
		temp = head->left; 					// temp는 트리의 첫 번째 노드를 가리킴
		while (temp!=NULL)					// temp가 NULL이 아니라면
		{
			if (temp->key == key) 			// temp의 key가 찾는 key와 같고
			{
				if (temp->left == NULL && temp->right == NULL)//temp가 leaf 노드이고
				{
					if (pre->left == temp) 	// pre의 left child가 temp 라면 
						pre->left = NULL; 	// pre의 left를 NULL로 만듦
					else 					// pre의 right child 가 temp 라면 
						pre->right = NULL;	// pre의 right를 NULL로 만듦
						free(temp); 		// 삭제
						return 0; 			// 종료
				}
				else 						// leaf 노드가 아니라면
				{
					printf("the node [%d] is not a leaf\n", temp->key);
					return 0;
				}
			}
			else if (temp->key >= key) 		// temp의 key가 찾는 key보다 크거나 같다면 
			{
				pre = temp;					// pre는 temp를 가리킴
				temp = temp->left;			// temp는 왼쪽 자식을 가리킴
			}
			else							// 아니라면 
			{
				pre = temp;					// pre는 temp를 가리킴
				temp = temp->right;			// temp는 오른쪽 자식을 가리킴
			}
		}

		// 반복문을 나왔으므로 key는 트리에 없다
		printf("node [%d] is not in tree\n",key);
	}
	return 0;
}

Node* searchRecursive(Node* ptr, int key)			// 재귀적 탐색
{
	if(ptr == NULL)									// ptr이 NULL이라면
		return NULL;
	if (ptr->key == key)							// ptr의 key가 찾는 key와 같다면
		return ptr;
	else if (ptr->key > key)						// ptr의 key가 찾는 key보다 크다면
		return searchRecursive(ptr->left, key);		
	else											// 아니라면
		return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)			// 반복적 탐색
{
	Node* temp = head->left;						// temp는 트리의 첫 번째 노드를 가리킴
	while (temp != NULL)							// temp가 NULL이 아니라면
	{
		if (temp->key == key)						// temp의 key와 찾는 key가 같다면 temp가 가리키는 주소 리턴
			return temp;
		else if (temp->key > key)					// temp의 key가 찾는 key보다 크다면 temp의 left로 이동	
			temp = temp->left;
		else										// 아니라면 temp의 right로 이동
			temp = temp->right;
	}
	//반복문을 나왔다는 것은 key가 트리에 없다는 것이다
	return NULL;
}

int freeBST(Node* head) 							// inorder처럼 recursive 하게 동작
{
    if (head == NULL) return 1;						// head가 NULL이라면 종료

    Node* temp = head->left;						// temp는 트리의 첫 번째 노드를 가리킴

    if (temp != NULL) {								// temp가 NULL이 아니라면				
        freeBST(temp->left);						// 왼쪽 자식 노드로 이동	
        freeBST(temp->right);						// 오른쪽 자식 노드로 이동
        free(temp);									// temp에 할당된 메모리 해제
    }

    free(head);										// head에 할당된 메모리 해제
    return 1;
}
