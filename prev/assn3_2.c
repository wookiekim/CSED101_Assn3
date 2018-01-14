#include <stdio.h>

void print_board(char gameboard[][4]);//파일에서 보드에 대한 정보를 읽어와 출력하는 함수입니다.
void get_code(int coded[][3], char gameboard[][4]);//받아온 판을 쉬운 결합 판정을 위하여 encrypt를 시키는 함수입니다.
int get_solution(int solution[],int coded[][3]);//Encrypt된 판에서 합의 모든 컴비네이션을 찾아내어 저장하는 함수입니다.
void check_answer(int first, int second, int third, int solution[],int finished[],int *entry,int *score);//사용자에게서 합을 입력받을때 합이 맞는지 확인하는 함수입니다.
void check_end(int *entry,int *score);//사용가에게서 결을 입력받았을때 결이 맞는지 확인하는 함수입니다.

int main(void)
{
	FILE *infile;//infile이라는 파일 경로를 선언해줍니다.
	int number,round, i, first, second=0, third=0;	
	int score=0,entry;
	char gameboard[9][4];//게임판에 대한 정보를 저장해줄 배열입니다.
	int coded[9][3];//게임판에 대한 정보를 알기쉽도록 encrypt하여 저장하는 배열입니다.
	int solution[84];//가능한 합의 모든 경우의 수를 저장하는 배열입니다.
	int finished[84]={0};//이미 합으로 입력받은 합들을 저장하는 배열입니다.

	//필요한 변수들과 배열들을 선언합니다.

	printf("합일 경우 1 2 3 과 같이 입력해주시고, 결일 경우 0을 입력해주세요.\n");
	printf("단, 합은 오름차순으로 써야합니다. 1 2 3은 답으로 처리하지만 3 1 2는\n오답으로 처리합니다.\n");
	printf("합이 맞을 경우 +1점, 결이 맞을 경우 +3점, 틀릴 경우 -1점입니다.\n\n");
	//instruction을 출력합니다.
	infile=fopen("problem.txt","r");//problem.txt를 읽기형식으로 불러옵니다.

	if(infile==NULL){
		printf("cannot open input file\n");
		return 1;
	}// problem.txt.파일이 없을시에 프로그램을 비정상적으로 종료합니다.

	fscanf(infile,"%d",&round);//총 round의 횟수를 읽어옵니다.

	for(number=1;number<=round;number++){//총 round만큼의 게임을 하기 위한 반복문입니다.

		printf("============================== %d Round / %d Round ==============================\n\n",number,round);
		printf("현재점수 : %d \n\n",score);

		for(i=0;i<9;i++){
			fscanf(infile,"%s",&gameboard[i]);//해당 라운드에 사용될 판에 대한 정보를 읽어옵니다.
		}

		print_board(gameboard);//보드를 출력합니다.

		get_code(coded,gameboard);//보드에 정보를 encrypt합니다.

		entry=get_solution(solution,coded);//encrypt되 보드에서 나올수 있는 모든 합의 경우를 찾아서 solution이라는 배열에 저장합니다.

		while(entry>=0){
			printf("합 :");
			scanf("%d",&first);
			if(first==0){
				check_end(&entry,&score);//만일 0을 입력받으면 결판정을 합니다.
			}
			else{
				scanf("%d %d",&second, &third);
				check_answer(first,second,third,solution,finished,&entry,&score);//0외의 숫자를 입력받을 경우, 총 3개의 숫자를 입력받고 합 판정을 진행합니다.
			}
	
	}

		printf("현재 점수 : %d \n\n",score);

	for(i=0;i<84;i++)
		finished[i]=0;//finished배열에 있는 모든 값을 0으로 초기화 해줍니다.
	}

	printf("게임을 종료합니다.\n");
	printf("최종 점수 : %d \n",score);

	fclose(infile);//infile,즉 problem.txt와의 링크를 끊습니다.

	return 0;
}

void print_board(char gameboard[][4])//반복문을 사용하여, 원하는 형식으로 판을 출력하는 함수입니다.
{
	int i,j;
		printf("+---+---+---+\n");

		for(j=0;j<9;j+=3){

		printf("|");
		for(i=j;i<j+3;i++){
		printf("%c%c%c|",gameboard[i][0],gameboard[i][0],gameboard[i][0]);			
	}
		printf("\n|");

		for(i=j;i<j+3;i++){
		printf("%c%c%c|",gameboard[i][1],gameboard[i][2],gameboard[i][1]+2);
		}

		printf("\n|");

		for(i=j;i<j+3;i++){
		printf("%c%c%c|",gameboard[i][0],gameboard[i][0],gameboard[i][0]);		
	}
		
		printf("\n+---+---+---+\n");

		}
}

void get_code(int coded[][3], char gameboard[][4])
{
	int i;
	for(i=0;i<9;i++){//encryption을 모든 피스를 위해 해주기 위한 반복문입니다.
		switch(gameboard[i][0]){//어떠한 배경색이 있느냐에 따라서 0,1 또는 2로 대체시켜 보기쉽게 해줍니다.
		case '.':
			coded[i][0]=0;
			break;
		case '#':
			coded[i][0]=1;
			break;
		case '%':
			coded[i][0]=2;
			break;
		}

		switch(gameboard[i][1]){//어떠한 모양이 있느냐에 따라서 0,1 또는 2로 대체시켜 보기쉽게 해줍니다.
		case '<':
			coded[i][1]=0;
			break;
		case '{':
			coded[i][1]=1;
			break;
		case '[':
			coded[i][1]=2;
			break;
		}

		switch(gameboard[i][2]){//어떠한 색이 있느냐에 따라서 0,1 또는 2로 대체시켜 보기쉽게 해줍니다.
		case 'A':
			coded[i][2]=0;
			break;
		case 'B':
			coded[i][2]=1;
			break;
		case 'C':
			coded[i][2]=2;
			break;
		}
	}
}

int get_solution(int solution[],int coded[][3])
{
	/*각 모양과 배경색과 색에 0,1 또는 2의 숫자를 배정하여줍니다. 이때 만일 한 원소가 모두 다르거나 같다면 0+0+0=0,1+1+1=3,2+2+2=6,0+1+2=3으로 모두 %3의 값이 0이 나오게 됩니다.
	이 성질을 이용하여 합을 판정하여, solution배열에 저장합니다.*/
	int i,j,k,entry=0;

	for(i=0;i<9;i++){
		for(j=i+1;j<9;j++){
			for(k=j+1;k<9;k++){
			if((coded[i][0]+coded[j][0]+coded[k][0])%3==0 && (coded[i][1]+coded[j][1]+coded[k][1])%3==0 && (coded[i][2]+coded[j][2]+coded[k][2])%3==0){

				solution[entry]=(100*(i+1))+(10*(j+1))+k+1;
				entry++;
			}
			}
		}
	}

	return entry;
	
}

void check_answer(int first, int second, int third, int solution[],int finished[],int *entry,int *score)
{
	int guess,i,j;

	guess=(100*first)+(10*second)+third;

	for(i=0;i<*entry+1;i++){
		if(solution[i]==guess){//만일 입력받은 합이 정답을 저장해놓은 배열에 있다면
			*score+=1;
			printf("합이 맞습니다. +1점 (현재 : %d점)\n",*score);

			for(j=0;j<84;j++){
				if(finished[j]==0){//같은 합을 여러번 할 수 없도록 다른 배열에 저장해둡니다. 정답을 저장해놓은 배열에서는 삭제합니다,
					finished[j]=guess;
					break;//답을 이미 찾았기에 반복문에서 나갑니다,
				}
			}
			
			for(j=i;j<*entry;j++){
				solution[j]=solution[j+1];//정답이 있던 곳 부터 앞에 있던 값들을 다 당겨옵니다.

			}
			*entry-=1;//남은 정답의 개수를 하나 줄입니다.
			break;
		}
	}
	
	if(i==*entry+1){//만일 for문을 다 돌았는데 정답이 없다면, 이미 나온 정답은 아닌지 확인합니다.
		for(j=0;j<84;j++){
			if(guess==finished[j]){
				*score-=1;
				printf("이미 나온 합입니다. -1점 (현재 : %d점)\n",*score);
				break;//만일 이미 나온 합이라면 위의 코드들을 실행합니다.
			}
		}
	}
		
	if(j==84){//만일 이미 나온 정답도 아니라면 아래의 코드를 실행합니다.
		*score-=1;
		printf("합이 아닙니다. -1점 (현재 : %d점)\n",*score);
	}
}

void check_end(int *entry, int *score)
{
	if(*entry==0)//entry는 남아있는 답의 개수를 저장하는 변수입니다. 만일 답이 남아있지 않다면, 결 성공입니다. 담이 남아있다면 결 실패입니다.
	{
		*score+=3;
		printf("결에 성공했습니다. +3점 (현재 : %d점)\n",*score);
		*entry-=1;//entry가 0에서 -1이되어, main함수에 있는 반복문을 빠져나갈 수 있게됩니다 (해당 라운드 종료)
}
	else{
		*score-=1;
		printf("결에 실패했습니다. -1점 (현재 : %d점)\n",*score);
	}
}