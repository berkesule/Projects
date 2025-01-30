#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int boardsize, boardwidth, i, j,k,d,l,m,n,score;

int main() {
	int boardsize, boardwidth, i, j,choice,koordinat= 1,yerkor=1,kayip,deger;
	int parca[4][3][3],piece1,piece2,a,dondur,d,kontrol = 1;
	int yeniparca[3][3];
	int yerlestirme;
	int maxscore = 0;
	score = 0;
	
	
    while (1) {
    	score = 0;
    	
    
        printf("==============\n");
        printf("  TETRIS OYUNU  \n");
        printf("==============\n");
        printf("En yuksek skor :%d\n",maxscore);
        printf("1. Oyuna basla\n");
        printf("2. Oyundan cik\n");
        printf("Seciminizi yapin: ");
        
        

        
        scanf("%d", &choice);

        if (choice == 1) {
            
        	
            printf("Tahta boyutlarini giriniz\n: ");
            scanf("%d", &boardsize);
            scanf("%d", &boardwidth);

            int board[boardsize + 2][boardwidth + 2];
            for (i = 0; i < boardsize + 2; i++) {
                for (j = 0; j < boardwidth + 2; j++) {
                    if (i == 0 || i == boardsize + 1 || j == 0 || j == boardwidth + 1) {
                        board[i][j] = '*';
                    } else {
                        board[i][j] = ' ';
                    }
                }
            }
            for (i = 0; i < boardsize + 2; i++) {
                for (j = 0; j < boardwidth + 2; j++) {
                    printf("%c", board[i][j]);
                }
                printf("\n");
            }
            yerkor = 1;
            koordinat = 1;
            /// koordinat alma ve konrtol kýsmý//
            while(yerkor != 0){ /// while da and kullan diðerleri için
                srand(time(0));
                a = rand() % 6 +1;
                int parca1[4][3][3] = {
                	{///1
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{' ','*',' '}
						
					},
					{////2
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{' ','*',' '}
						
					},
					{///3
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{' ','*',' '}
						
					},
					{
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{' ','*',' '}
						
					}
				};
                int parca2[4][3][3] = {
                	{///1
                		{' ',' ',' '},
                		{' ','*',' '},
                		{' ','*',' '}
						
					},
					{////2
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{' ','*','*'}
						
					},
					{///3
                		{' ',' ',' '},
                		{' ','*',' '},
                		{' ','*',' '}
						
					},
					{
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{'*','*',' '}
						
					}
				};
                int parca3[4][3][3] = {
                	{///1
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{'*','*','*'}
						
					},
					{////2
                		{' ','*',' '},
                		{' ','*',' '},
                		{' ','*',' '}
						
					},
					{///3
                		{' ',' ',' '},
                		{' ',' ',' '},
                		{'*','*','*'}
						
					},
					{
                		{' ','*',' '},
                		{' ','*',' '},
                		{' ','*',' '}
						
					}
				};
                int parca4[4][3][3] = {
                	{///1
                		{' ',' ',' '},
                		{'*',' ',' '},
                		{'*','*','*'}
						
					},
					{////2
                		{' ','*','*'},
                		{' ','*',' '},
                		{' ','*',' '}
						
					},
					{///3
                		{' ',' ',' '},
                		{'*','*','*'},
                		{' ',' ','*'}
						
					},
					{
                		{' ','*',' '},
                		{' ','*',' '},
                		{'*','*',' '}
						
					}
				};
                int parca5[4][3][3] = {
                	{///1
                		{' ',' ',' '},
                		{'*','*',' '},
                		{'*','*',' '}
						
					},
					{////2
                		{' ',' ',' '},
                		{'*','*',' '},
                		{'*','*',' '}
						
					},
					{///3
                		{' ',' ',' '},
                		{'*','*','*'},
                		{'*','*','*'}
						
					},
					{
                		{' ',' ',' '},
                		{'*','*',' '},
                		{'*','*',' '}
						
					}
				};
                int parca6[4][3][3] = {
                	{///1
                		{' ',' ',' '},
                		{' ','*','*'},
                		{'*','*',' '}
						
					},
					{////2
                		{' ','*',' '},
                		{' ','*','*'},
                		{' ',' ','*'}
						
					},
					{///3
                		{' ',' ',' '},
                		{' ','*','*'},
                		{'*','*',' '}
						
					},
					{
                		{' ','*',' '},
                		{'*','*',' '},
                		{'*',' ',' '}
						
					}
				};
                                                      
				switch(a){
					case 1:
						for(k=0;k<4;k++){
							for(i = 0;i<3;i++){
								for(j =0;j<3;j++){
									parca[k][i][j] = parca1[k][i][j];
								}
							}
						}

						break;
					case 2:
						for(k=0;k<4;k++){
							for(i = 0;i<3;i++){
								for(j =0;j<3;j++){
									parca[k][i][j] = parca2[k][i][j];
								}
							}
						}

						
						break;
					case 3:
						for(k=0;k<4;k++){
							for(i = 0;i<3;i++){
								for(j =0;j<3;j++){
									parca[k][i][j] = parca3[k][i][j];
								}
							}
						}

						break;
					case 4:
						for(k=0;k<4;k++){
							for(i = 0;i<3;i++){
								for(j =0;j<3;j++){
									parca[k][i][j] = parca4[k][i][j];
								}
							}
						}
	
						
						break;

					case 5:
						for(k=0;k<4;k++){
							for(i = 0;i<3;i++){
								for(j =0;j<3;j++){
									parca[k][i][j] = parca5[k][i][j];
								}
							}
						}

						
						break;
					case 6:
						for(k=0;k<4;k++){
							for(i = 0;i<3;i++){
								for(j =0;j<3;j++){
									parca[k][i][j] = parca6[k][i][j];
								}
							}
						}

						
						break;
					
				}
				///döndürme iþlemleri;
				d = 0;
				deger = 0;
				while(d !=4){
					
				    printf("parca:\n");
				    for(i =0;i<3;i++){
					    for(j=0;j<3;j++){
						    printf("%c",parca[d][i][j]);
						
					    }
					    printf("\n");

				     }
				    printf("parcayi dondurmek icin 0,1,2,3 karakterlerini kullanabirlisiniz.dondurme islemini bitirmek icin 4 e basýnýz\n");
				    scanf("%d",&d);
				    
				    if(d != 4){
					    deger = d;
				    }			
				}
				
				for (i=0;i<3;i++){
					for(j=0;j<3;j++){
						yeniparca[i][j] = parca[deger][i][j];
					}
				}
			
				///koordinat kýsmý
				printf("tetrominonun sol ucunun  koordinati:");
            	scanf("%d",&yerkor);	
				koordinat = yerkor;			
            	if(koordinat > boardwidth){
            		koordinat = boardwidth;
				}
				if(yeniparca[0][0] == ' ' && yeniparca[1][0] == ' ' && yeniparca[2][0] == ' '){
					koordinat--;
				}
				///3 sutunlu sekillerin son sutunda otelenmesi icin
				if(yeniparca[0][0] == '*' || yeniparca[1][0] == '*' || yeniparca[2][0]== '*'){
					
					if(yeniparca[0][1] == '*' || yeniparca[1][1] == '*' || yeniparca[2][1] == '*'){
						if(yeniparca[0][2] == '*' || yeniparca[1][2] == '*' || yeniparca[2][2] == '*'){
							if(koordinat == boardwidth){
								koordinat = koordinat -2;
								}
							if(koordinat == boardwidth -1){
								koordinat= koordinat - 1;
							}
						}					
					}
				}
				if(yeniparca[0][1] == '*' || yeniparca[1][1] == '*' || yeniparca[2][1] == '*'){
					if(yeniparca[0][2] != '*' && yeniparca[1][2] != '*' && yeniparca[2][2] != '*'){
						if(koordinat == boardwidth){
							koordinat = koordinat -1;
						}
					}
				}
            	////yerlesirme kýsmý
            	
            	kontrol = 0;
            	////yerleþtirme komtrolunu yaz
            	for(a=3;a<=boardsize;a++){
            		for(i=2;i>-1;i--){
            			for(j=2;j>-1;j--){
            				if(board[a-2+i][koordinat+j] == '*' && yeniparca[i][j] == '*'){//bu saðlanýyorsa býrakmalý ve a nýn bir kucuk deðerini yazdýrmalý
            				kontrol = 1;
            				break;
            					
							}
						}
					}
					if(kontrol ==1){
						break;
					}					
				}
            	for(i=2;i>-1;i--){
            		for(j=2;j>-1;j--){
            			if(yeniparca[i][j] == '*'){
            				board[a-3+i][koordinat+j] = '*';
            				
						}
					}
				}
				score++;
				printf("\tscore %d \n",score);
				n = 1;
				l =1;
				m=1;
/////yerlestirmeden sonraki kontrol satýr kontrolu ve oyun sonu kontrolu
  				for(i=1;i<boardwidth+1;i++){
					if(board[a-1][i] ==' '){
						l = 0;
					}
				}
				for(i=1;i<boardwidth+1;i++){
					if(board[a-2][i] ==' '){
						n = 0;
					}
				}
				for(i=1;i<boardwidth+1;i++){
					if(board[a-3][i] ==' '){
						m = 0;
					}
				}
				//dolu satýrtarý kýrma:
				if(a>2){
					if(m == 1){
					for(i=1;i<boardwidth+1;i++){
						board[a-3][i] = ' ';
						
					}
					for(i=a-4;i>0;i--){
						for(j=1;j<boardwidth+1;j++){
							board[i+1][j] = board[i][j];
						}
					}
					score = score +5;
				}
				if(n == 1){
					for(i=1;i<boardwidth+1;i++){
						board[a-2][i] = ' ';
					}
					for(i=a-3;i>0;i--){
						for(j=1;j<boardwidth+1;j++){
							board[i+1][j] = board[i][j];
						}
					}
					score =score +5;
				}
				if(l == 1){
					for(i=1;i<boardwidth+1;i++){
						board[a-1][i] = ' ';
					}
					for(i=a-2;i>0;i--){
						for(j=1;j<boardwidth+1;j++){
							board[i+1][j] = board[i][j];
						}
					}
					score = score+5;				
				}				
				}
				///en üste parça yerleþtirip yerleþtirmediðinin kontrolu ve oyun sonu
				kayip = 0;
				for(i=1;i<boardwidth+1;i++){
					if(board[1][i] == '*'){
						kayip = 1;
					}
				}
				if(kayip ==1){
					printf("\tGAME OVER\n");
					score = score -5;
					printf("\tskorunuz:%d\n",score);
					if(score > maxscore){
						maxscore = score;
					}
					printf("\tEn yüksek skor:%d:\n",maxscore);
					printf("Tekrar oynamak icin 0'a basiniz'");
					
					scanf("%d",&yerkor);
				}				
				for(i = 0;i<boardsize +2;i++){
					for(j=0;j<boardwidth+2;j++){
						printf("%c",board[i][j]);
					}
					printf("\n");
				}
			}
                    
        } else if (choice == 2) {
            return 0;
        } else {
            printf("Gecersiz secim!\n");
        }
    }
    
}

