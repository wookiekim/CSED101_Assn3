#include <stdio.h>

void print_board(char gameboard[][4]);//���Ͽ��� ���忡 ���� ������ �о�� ����ϴ� �Լ��Դϴ�.
void get_code(int coded[][3], char gameboard[][4]);//�޾ƿ� ���� ���� ���� ������ ���Ͽ� encrypt�� ��Ű�� �Լ��Դϴ�.
int get_solution(int solution[],int coded[][3]);//Encrypt�� �ǿ��� ���� ��� �ĺ���̼��� ã�Ƴ��� �����ϴ� �Լ��Դϴ�.
void check_answer(int first, int second, int third, int solution[],int finished[],int *entry,int *score);//����ڿ��Լ� ���� �Է¹����� ���� �´��� Ȯ���ϴ� �Լ��Դϴ�.
void check_end(int *entry,int *score);//��밡���Լ� ���� �Է¹޾����� ���� �´��� Ȯ���ϴ� �Լ��Դϴ�.

int main(void)
{
	FILE *infile;//infile�̶�� ���� ��θ� �������ݴϴ�.
	int number,round, i, first, second=0, third=0;	
	int score=0,entry;
	char gameboard[9][4];//�����ǿ� ���� ������ �������� �迭�Դϴ�.
	int coded[9][3];//�����ǿ� ���� ������ �˱⽱���� encrypt�Ͽ� �����ϴ� �迭�Դϴ�.
	int solution[84];//������ ���� ��� ����� ���� �����ϴ� �迭�Դϴ�.
	int finished[84]={0};//�̹� ������ �Է¹��� �յ��� �����ϴ� �迭�Դϴ�.

	//�ʿ��� ������� �迭���� �����մϴ�.

	printf("���� ��� 1 2 3 �� ���� �Է����ֽð�, ���� ��� 0�� �Է����ּ���.\n");
	printf("��, ���� ������������ ����մϴ�. 1 2 3�� ������ ó�������� 3 1 2��\n�������� ó���մϴ�.\n");
	printf("���� ���� ��� +1��, ���� ���� ��� +3��, Ʋ�� ��� -1���Դϴ�.\n\n");
	//instruction�� ����մϴ�.
	infile=fopen("problem.txt","r");//problem.txt�� �б��������� �ҷ��ɴϴ�.

	if(infile==NULL){
		printf("cannot open input file\n");
		return 1;
	}// problem.txt.������ �����ÿ� ���α׷��� ������������ �����մϴ�.

	fscanf(infile,"%d",&round);//�� round�� Ƚ���� �о�ɴϴ�.

	for(number=1;number<=round;number++){//�� round��ŭ�� ������ �ϱ� ���� �ݺ����Դϴ�.

		printf("============================== %d Round / %d Round ==============================\n\n",number,round);
		printf("�������� : %d \n\n",score);

		for(i=0;i<9;i++){
			fscanf(infile,"%s",&gameboard[i]);//�ش� ���忡 ���� �ǿ� ���� ������ �о�ɴϴ�.
		}

		print_board(gameboard);//���带 ����մϴ�.

		get_code(coded,gameboard);//���忡 ������ encrypt�մϴ�.

		entry=get_solution(solution,coded);//encrypt�� ���忡�� ���ü� �ִ� ��� ���� ��츦 ã�Ƽ� solution�̶�� �迭�� �����մϴ�.

		while(entry>=0){
			printf("�� :");
			scanf("%d",&first);
			if(first==0){
				check_end(&entry,&score);//���� 0�� �Է¹����� �������� �մϴ�.
			}
			else{
				scanf("%d %d",&second, &third);
				check_answer(first,second,third,solution,finished,&entry,&score);//0���� ���ڸ� �Է¹��� ���, �� 3���� ���ڸ� �Է¹ް� �� ������ �����մϴ�.
			}
	
	}

		printf("���� ���� : %d \n\n",score);

	for(i=0;i<84;i++)
		finished[i]=0;//finished�迭�� �ִ� ��� ���� 0���� �ʱ�ȭ ���ݴϴ�.
	}

	printf("������ �����մϴ�.\n");
	printf("���� ���� : %d \n",score);

	fclose(infile);//infile,�� problem.txt���� ��ũ�� �����ϴ�.

	return 0;
}

void print_board(char gameboard[][4])//�ݺ����� ����Ͽ�, ���ϴ� �������� ���� ����ϴ� �Լ��Դϴ�.
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
	for(i=0;i<9;i++){//encryption�� ��� �ǽ��� ���� ���ֱ� ���� �ݺ����Դϴ�.
		switch(gameboard[i][0]){//��� ������ �ִ��Ŀ� ���� 0,1 �Ǵ� 2�� ��ü���� ���⽱�� ���ݴϴ�.
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

		switch(gameboard[i][1]){//��� ����� �ִ��Ŀ� ���� 0,1 �Ǵ� 2�� ��ü���� ���⽱�� ���ݴϴ�.
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

		switch(gameboard[i][2]){//��� ���� �ִ��Ŀ� ���� 0,1 �Ǵ� 2�� ��ü���� ���⽱�� ���ݴϴ�.
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
	/*�� ���� ������ ���� 0,1 �Ǵ� 2�� ���ڸ� �����Ͽ��ݴϴ�. �̶� ���� �� ���Ұ� ��� �ٸ��ų� ���ٸ� 0+0+0=0,1+1+1=3,2+2+2=6,0+1+2=3���� ��� %3�� ���� 0�� ������ �˴ϴ�.
	�� ������ �̿��Ͽ� ���� �����Ͽ�, solution�迭�� �����մϴ�.*/
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
		if(solution[i]==guess){//���� �Է¹��� ���� ������ �����س��� �迭�� �ִٸ�
			*score+=1;
			printf("���� �½��ϴ�. +1�� (���� : %d��)\n",*score);

			for(j=0;j<84;j++){
				if(finished[j]==0){//���� ���� ������ �� �� ������ �ٸ� �迭�� �����صӴϴ�. ������ �����س��� �迭������ �����մϴ�,
					finished[j]=guess;
					break;//���� �̹� ã�ұ⿡ �ݺ������� �����ϴ�,
				}
			}
			
			for(j=i;j<*entry;j++){
				solution[j]=solution[j+1];//������ �ִ� �� ���� �տ� �ִ� ������ �� ��ܿɴϴ�.

			}
			*entry-=1;//���� ������ ������ �ϳ� ���Դϴ�.
			break;
		}
	}
	
	if(i==*entry+1){//���� for���� �� ���Ҵµ� ������ ���ٸ�, �̹� ���� ������ �ƴ��� Ȯ���մϴ�.
		for(j=0;j<84;j++){
			if(guess==finished[j]){
				*score-=1;
				printf("�̹� ���� ���Դϴ�. -1�� (���� : %d��)\n",*score);
				break;//���� �̹� ���� ���̶�� ���� �ڵ���� �����մϴ�.
			}
		}
	}
		
	if(j==84){//���� �̹� ���� ���䵵 �ƴ϶�� �Ʒ��� �ڵ带 �����մϴ�.
		*score-=1;
		printf("���� �ƴմϴ�. -1�� (���� : %d��)\n",*score);
	}
}

void check_end(int *entry, int *score)
{
	if(*entry==0)//entry�� �����ִ� ���� ������ �����ϴ� �����Դϴ�. ���� ���� �������� �ʴٸ�, �� �����Դϴ�. ���� �����ִٸ� �� �����Դϴ�.
	{
		*score+=3;
		printf("�ῡ �����߽��ϴ�. +3�� (���� : %d��)\n",*score);
		*entry-=1;//entry�� 0���� -1�̵Ǿ�, main�Լ��� �ִ� �ݺ����� �������� �� �ְԵ˴ϴ� (�ش� ���� ����)
}
	else{
		*score-=1;
		printf("�ῡ �����߽��ϴ�. -1�� (���� : %d��)\n",*score);
	}
}