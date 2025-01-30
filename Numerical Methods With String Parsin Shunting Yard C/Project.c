#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define PI 3.14159265
#define SIZE 150
double determinant(double **, double);
void cofactor(double **, double);
void transpose(double **, double **, double);
void free_matrix(double **, int);
/*
Kodda string parsing icin shunting yard algoritmasini kullandim ilk 400 satir onunla ilgili.
*/
struct STACK {
    char op;
    struct STACK *next;
};
struct RPN {
    double number;
    char op;
    struct RPN *next;
};

struct Token {
    double number;
    char op;
    int isOperator;
    struct Token *next;
};

void pushstack(struct STACK **topptr, char op) {
    struct STACK *newptr = (struct STACK *)malloc(sizeof(struct STACK));
    newptr->op = op;
    newptr->next = *topptr;
    *topptr = newptr;
}

char poptoken(struct STACK **topptr) {
    struct STACK *tempptr = *topptr;
    char op = (*topptr)->op;
    *topptr = (*topptr)->next;
    free(tempptr);
    return op;
}

void tokenekle(double number, char op, int isOperator, struct Token **root, struct Token **son) {
    struct Token *new_token = (struct Token *)malloc(sizeof(struct Token));
    new_token->number = number;
    new_token->op = op;
    new_token->isOperator = isOperator;

    if (*root == NULL) {
        *root = new_token;
    } else {
        (*son)->next = new_token;
    }
    *son = new_token;
    new_token->next = NULL;
}

struct Token *processString(char *str, double x) {
	int i,j;
	int length = strlen(str);
    for (i = 0; i < length; i++) {
        if (str[i] == 'x' && isdigit(str[i - 1])) {
            for (j = length; j > i - 1; j--) {
                str[j+1] = str[j];
            }
            str[length + 1] = '\0';
            str[i] = '*';    
            length++;
        }
    }

    struct Token *root = NULL;
    struct Token *son = NULL;
    int decimalPlace = 1;

    int index = 0;
    while (str[index] != '\0') {
        float number = 0;
        char op = ' ';
        int isOperator = 0;
        decimalPlace = 1;
        int decimalpoint = 0;

        if (isdigit(str[index]) || str[index] == '.' || str[index] == 'x'|| str[index] == 'e') {
            while (isdigit(str[index]) || str[index] == '.') {
                if (str[index] == '.') {
                	decimalpoint = 1;
                	index++;
                }
                if(decimalpoint){
                	number = number + (str[index] - '0') / (float)pow(10, decimalPlace);
                	decimalPlace++;
				}else{
					number = number* 10 + (str[index] - '0');	
				}
				index ++;
                
            }
            if (str[index] == 'x') {
                number = x;
                index++;
            }
            if (str[index] == 'e'){
            	number = 2.71828 ;
				index++;
			}

        } else if (str[index] == '*' || str[index] == '/' || str[index] == '+' || str[index] == '-' || str[index] == '(' || str[index] == ')' || str[index] == '^') {
            op = str[index];
            isOperator = 1;
            index++;
        } else if (str[index] == 's' && str[index+1] == 'i' && str[index+2] == 'n' ){
        	op = 'a';
        	isOperator = 1;
        	index = index + 3;
		}else if (str[index] == 'c' && str[index+1] == 'o' && str[index+2] == 's' ){
        	op = 'b';
        	isOperator = 1;
        	index = index + 3;
		}else if (str[index] == 't' && str[index+1] == 'a' && str[index+2] == 'n' ){
        	op = 't';
        	isOperator = 1;
        	index = index + 3;
		}else if (str[index] == 'c' && str[index+1] == 'o' && str[index+2] == 't' ){
        	op = 'c';
        	isOperator = 1;
        	index = index + 3;
		}else if (str[index] == 'a' && str[index+1] == 's' && str[index+2] == 'i' && str[index+3] == 'n' ){
        	op = 'k';
        	isOperator = 1;
        	index = index + 4;
		}else if (str[index] == 'a' && str[index+1] == 'c' && str[index+2] == 'o' && str[index+3] == 's' ){
        	op = 'm';
        	isOperator = 1;
        	index = index + 4;
		}else if (str[index] == 'a' && str[index+1] == 't' && str[index+2] == 'a' && str[index+3] == 'n' ){
        	op = 'l';
        	isOperator = 1;
        	index = index + 4;
		}else if (str[index] == 'a' && str[index+1] == 'c' && str[index+2] == 'o' && str[index+3] == 't' ){
        	op = 'n';
        	isOperator = 1;
        	index = index + 4;
		}else if (str[index] == 'l' && str[index+1] == 'o' && str[index+2] == 'g' && str[index+3] == '_'){
			op ='f';
			isOperator = 1;
			index = index+4;
			
		}

        tokenekle(number, op, isOperator, &root, &son);
    }

    return root;
}




int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^') {
        return 3;
        
    }
	else {
        return 3;
    }
}

void processTokens(struct RPN **rpnRoot, struct STACK **stackTop,char input[SIZE],double x) {
	struct Token *root = processString(input, x);
    struct Token *current = root;
    while (current != NULL) {
        if (current->isOperator) {
            if (current->op == '(') {
                pushstack(stackTop, current->op);
            } else if (current->op == ')') {
                // Stack'te '(' karakteri gorenene kadar tum operatorleri RPN ifadesine ekle
                while (*stackTop != NULL && (*stackTop)->op != '(') {
                    struct RPN *new_rpn = (struct RPN *)malloc(sizeof(struct RPN));
                    new_rpn->op = poptoken(stackTop);
                    new_rpn->next = NULL;

                    if (*rpnRoot == NULL) {
                        *rpnRoot = new_rpn;
                    } else {
                        struct RPN *temp = *rpnRoot;
                        while (temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = new_rpn;
                    }
                }
                if (*stackTop != NULL && (*stackTop)->op == '(') {
                    poptoken(stackTop);
                } else {
                    
                    printf("Hata: Parantez eslesmesi bulunamadi.\n");
                    return; 
                }
            } else {
            	
            	if(current->op =='^'){
            		pushstack(stackTop, current->op);
				}else{
					
					
					while (*stackTop != NULL && precedence((*stackTop)->op) >= precedence(current->op) && (*stackTop)->op != '(') { 
                        struct RPN *new_rpn = (struct RPN *)malloc(sizeof(struct RPN));
                        new_rpn->op = poptoken(stackTop);
                        new_rpn->next = NULL;

                        if (*rpnRoot == NULL) {
                            *rpnRoot = new_rpn;
                        } else {
                            struct RPN *temp = *rpnRoot;
                            while (temp->next != NULL) {
                                temp = temp->next;
                            }
                            temp->next = new_rpn;
                            }
                    
                    
                        }				
				    pushstack(stackTop, current->op);		
				}
                
            }
        } else {
            struct RPN *new_rpn = (struct RPN *)malloc(sizeof(struct RPN));
            new_rpn->number = current->number;
            new_rpn->op = ' ';
            new_rpn->next = NULL;

            if (*rpnRoot == NULL) {
                *rpnRoot = new_rpn;
            } else {
                struct RPN *temp = *rpnRoot;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new_rpn;
            }
        }
        current = current->next;
    }

    while (*stackTop != NULL) {
        struct RPN *new_rpn = (struct RPN *)malloc(sizeof(struct RPN));
        new_rpn->op = poptoken(stackTop);
        new_rpn->next = NULL;

        if (*rpnRoot == NULL) {
            *rpnRoot = new_rpn;
        } else {
            struct RPN *temp = *rpnRoot;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_rpn;
        }
    }
}

double calculateRPN(struct RPN **root) {
    struct RPN *current = *root;
    struct RPN *temp1 = NULL;
    struct RPN *temp2 = NULL;
    struct RPN *eleman1 = NULL;
    struct RPN *eleman2 = NULL;
    struct RPN *eleman3 = NULL;
    struct RPN *onceki = NULL;

    double result = 0;

    while (current != NULL && current->next != NULL) {
    	if (current ->next->op == 'a' || current ->next->op == 'b' || current->next->op == 't' || current->next->op == 'c' || current->next->op == 'k' ||  current->next->op == 'l' || current->next->op == 'm' || current->next->op == 'n'){
    		eleman1 = current;
    		eleman2= current->next;
    		switch(eleman2->op){
    			case 'a':
    				result = sin(eleman1->number);
    				break;
    			case 'b':
    				result = cos(eleman1->number);
    				break;
    			case 't':
    				result = tan(eleman1->number);
    				break;
    			case 'c':
    				result = 1/tan(eleman1->number);
    				break;
    			case 'l':
    				result = atan(eleman1->number);
    				break;
    			case 'm':
    				result = acos(eleman1->number);
    				break;
    			case 'n':
    				result = atan(1/eleman1->number);
    				break;
    			case 'k':
    				result = asin(eleman1->number);
    				break;
    			}
    			
    		eleman2->number = result;
    		eleman2->op = ' ';
    		if(eleman1 == *root){
    			*root = eleman2;
			}else{
				onceki->next =  eleman2;
			}
			temp1 = eleman1;
			current = *root;
			free(temp1);	
    		
		}
        else if (current->next->next != NULL && (current->next->next->op == '+' || current->next->next->op == '-' || current->next->next->op == '*' || current->next->next->op == '/' || current->next->next->op == '^' || current ->next->next-> op == 'f' )) { 
            eleman1 = current;
            eleman2 = current->next;
            eleman3 = current->next->next;
            switch (eleman3->op){
            	case '+':
            		result = eleman1->number + eleman2->number;
            		break;
            	case '-':
            		result = eleman1->number - eleman2->number;
            		break;
            	case '*':
            		result = eleman1->number * eleman2->number;
            		break;
            	case '/':
            		result = eleman1->number / eleman2->number;
            		break;
            	case '^':
            		result = pow(eleman1->number,eleman2->number);
            		break;
            	case 'f':
            		result = (log(eleman2->number)/log(eleman1->number));                
            		
			}
            
            eleman3->number = result;
            eleman3->op = ' ';
            if (eleman1 == *root) {
            	*root = eleman3;
            }else {
            	onceki->next = eleman3;
				}
            temp1 = eleman1;	
            temp2 = eleman2;	
			current = *root;
            free(temp1);
            free(temp2);
            } 
            	
		    else {
		    	
            	onceki = current;
            	if(current->next != NULL){
            		current = current->next;
				}
            	
            }	

    }
    
    return result;
}
double determinant(double **a, double k) {
    double s = 1, det = 0, **b;
    int i, j, m, n, c;

    if (k == 1) {
        return (a[0][0]);
    } else {
        det = 0;
        
        b = (double **)malloc(k * sizeof(double *));
        for (i = 0; i < k; i++)
            b[i] = (double *)malloc(k * sizeof(double));

        for (c = 0; c < k; c++) {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++) {
                for (j = 0; j < k; j++) {
                    b[i][j] = 0;
                    if (i != 0 && j != c) {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }

        free_matrix(b, k);
    }

    return (det);
}
void cofactor(double **num, double f) {
    double **b, **fac;
    int p, q, m, n, i, j;

    b = (double **)malloc(f * sizeof(double *));
    for (i = 0; i < f; i++){
        b[i] = (double *)malloc(f * sizeof(double));
    }
    
    fac = (double **)malloc(f * sizeof(double *));

    for (i = 0; i < f; i++){
        fac[i] = (double *)malloc(f * sizeof(double));
    }

    for (q = 0; q < f; q++) {
        for (p = 0; p < f; p++) {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++) {
                for (j = 0; j < f; j++) {
                    if (i != q && j != p) {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);

    free_matrix(b, f);
    free_matrix(fac, f);
}
void transpose(double **num, double **fac, double r) {
    int i, j;
    double **b, **inverse, d;
    
    b = (double **)malloc(r * sizeof(double *));
    for (i = 0; i < r; i++){
        b[i] = (double *)malloc(r * sizeof(double));
    }

    inverse = (double **)malloc(r * sizeof(double *));
    for (i = 0; i < r; i++){
        inverse[i] = (double *)malloc(r * sizeof(double));
    }

    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, r);
    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            inverse[i][j] = b[i][j] / d;
        }
    }
    printf("\n\n\nMatrisin Tersi:: \n");

    for (i = 0; i < r; i++) {
        for (j = 0; j < r; j++) {
            printf("\t %lf", inverse[i][j]);
        }
        printf("\n");
    }
    free_matrix(b, r);
    free_matrix(inverse, r);
}

void free_matrix(double **matrix, int size) {
    int i;
    for (i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
    matrix = NULL;
}
double** allocate_matrix(int n) {
	int i;
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void diagonal_sort(double** matrix, double* b, int n) {
	int i,j;
    for (i = 0; i < n; i++) {
        int max_index = i;
        for (j = i + 1; j < n; j++) {
            if (fabs(matrix[j][i]) > fabs(matrix[max_index][i])) {
                max_index = j;
            }
        }
        if (max_index != i) {
            
            double* temp_row = matrix[i];
            matrix[i] = matrix[max_index];
            matrix[max_index] = temp_row;
            
            
            double temp_b = b[i];
            b[i] = b[max_index];
            b[max_index] = temp_b;
        }
    }
}

void gauss_seidel(double** matrix, double* b, double* x, int n, int max_iterations, double tolerance) {
    double* x_old = (double*)malloc(n * sizeof(double));
    double hata = 1;
    int i,j,iter;
    iter = 0;
    while(iter < max_iterations && fabs(hata )> tolerance){
        for (i = 0; i < n; i++) {
            x_old[i] = x[i];
        }
        
        for (i = 0; i < n; i++) {
            double sum = 0.0;
            for (j = 0; j < n; j++) {
                if (i != j) {
                    sum += matrix[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / matrix[i][i];
        }
        
        
        hata = 0;
        for (i = 0; i < n; i++) {
            hata += fabs(x[i] - x_old[i]);
        }
        
        printf("iterasyon %d:\n", iter + 1);
        for (i = 0; i < n; i++) {
            printf("x[%d] = %lf\n", i, x[i]);
        }
        printf("hata: %lf\n\n", hata); 
		iter++;	
	}
    free(x_old);
    x_old = NULL;
}
double merkeziturev(char *func,double x){
	struct RPN *rpnRoot = NULL;
	struct STACK *stackTop = NULL;
	double h = 0.0001,result1,result2,result;
	processTokens(&rpnRoot, &stackTop,func,x+h/2);
	result1= calculateRPN(&rpnRoot);
	processTokens(&rpnRoot, &stackTop,func,x-h/2);
	result2= calculateRPN(&rpnRoot);
	result = (result1-result2)/h;
	return result;
	
}
int main() {
    char input[SIZE];
    char func[SIZE],turev[SIZE];
    double **matrix,*sonuc,*b,*xmatris,**matris,*noktalar,*deger;
    double x,y,result,start,end,epsilon,result1,result2,hata,orta,ortadeger,kok,h,a,p,c,d,sum,orta2,tolerance;
    int i ,j,secim,maxiter,hataoran,sayac,elemansayisi,sutunno,secim2,n,k;
    struct Token *root = NULL;
    struct RPN *rpnRoot = NULL;
    struct Token *root2 = NULL;
    struct RPN *rpnRoot2 = NULL;
    struct STACK *stackTop = NULL;
    struct STACK *stackTop2 = NULL;
    do{
        printf("Lutfen yapmak istediginiz islemi secin:\n");
    	printf("-----------------------------------------\n");
    	printf("0.  Cikis\n");
        printf("1.  Bisection yontemi\n"); // 
        printf("2.  Regula-Falsi yontemi\n");
        printf("3.  Newton-Rapshon Yontemi\n");
        printf("4.  NxN'lik bir matrisin tersi \n");//
        printf("5.  Gauss Eleminasyon\n"); /// 
        printf("6.  Gauss Seidal yontemleri\n"); //az kaldi
        printf("7.  Sayisal Turev (merkezi, ileri ve geri farklar opsiyonlu)\n");//
        printf("8.  Simpson yontemi\n");//
        printf("9.  Trapez yontemi\n");//
        printf("10. Degisken donusumsuz Gregory Newton Enterpolasyonu\n");//
        printf("-----------------------------------------\n");	
    	printf("Seciminizi girin (0-10): ");
        scanf("%d", &secim);
        switch (secim){

    	    case 0:
    		    break;
    	    case 1:
    	    	sayac = 0;
    	    	system("cls");
    		    printf("Bisection Yontemini Sectiniz\n");
    		    printf("Fonksiyon:\n");
    		    scanf("%s",func);
    		    printf("start\n");
    		    scanf("%lf",&start);
    		    printf("end\n");
    		    scanf("%lf",&end);
    		    printf("epsilon\n");
    		    scanf("%lf",&epsilon);
    		    printf("max iteration\n");
    		    scanf("%d",&maxiter);
    		    processTokens(&rpnRoot, &stackTop,func,start);
    		    result1= calculateRPN(&rpnRoot);
    		    processTokens(&rpnRoot, &stackTop,func,end);
    		    result2 = calculateRPN(&rpnRoot);
    		    printf("f(start):%lf\n",result1);
    		    printf("f(end):%lf\n",result2);
    		    hata = (end-start)/pow(2,sayac); 
    		    sayac = 1;
    		    
    		    if(result1 * result2 <= 0){
    		    	while(sayac<maxiter && fabs(hata )>= epsilon){
    		    		hata = (end-start)/pow(2,sayac);
    		    	    printf("\n %d. iterasyon:\n",sayac);
    		    	    printf("Hata: %lf\n",hata);
    		    	    processTokens(&rpnRoot, &stackTop,func,start);
    		    	    result1= calculateRPN(&rpnRoot);
    		    	    processTokens(&rpnRoot, &stackTop,func,end);
    		    	    result2 = calculateRPN(&rpnRoot);
    		    	    orta = (start+end)/2;
    		    	    processTokens(&rpnRoot, &stackTop,func,orta);
    		    	    ortadeger = calculateRPN(&rpnRoot);
    		    		printf("start:%lf\n",start);
    		    		printf("end:%lf\n",end);
    		    		printf("orta:%lf\n",orta);
    		    	    printf("f(start):%lf\n",result1);
    		    	    printf("f(end):%lf\n",result2);    		    		
    		    		printf("f(orta): %lf\n ",ortadeger);
    		    	    
    		    	    if(ortadeger * result1 <= 0){
    		    	    	end = orta;/// 
    		    	    	}else{
    		    	    		start = orta;
    		    	    		}
    		    	    	sayac++;
    		    	    	kok = orta;
    		    	    }
    		    	    printf("Kok: %lf\n",kok);
    		    	
				}else{
					printf("Bu aralikta kok yok.\n");
				}
				
    		    break;
    		case 2:
    			sayac = 1;
    			system("cls");
    		    printf("Regula-falsi yontemini sectiniz\n");
    		    printf("Fonksiyonu Giriniz:\n");
    		    scanf("%s",func);
    		    printf("start\n");
    		    scanf("%lf",&start);
    		    printf("end\n");
    		    scanf("%lf",&end);
    		    printf("epsilon\n");
    		    scanf("%lf",&epsilon);
    		    printf("max iteration\n");
    		    scanf("%d",&maxiter);
    		    hata = (end-start)/pow(2,sayac);
    		    processTokens(&rpnRoot, &stackTop,func,start);
    		    result1= calculateRPN(&rpnRoot);
    		    processTokens(&rpnRoot, &stackTop,func,end);
    		    result2 = calculateRPN(&rpnRoot);
    		    printf("%lf\n",result1);
    		    printf("%lf\n",result2);
    		    
    		    if(result1*result2 <= 0){
    		    	
    		    	while(sayac<maxiter && fabs(hata)>= epsilon){
    		    		hata = (end-start)/pow(2,sayac);
    		    		printf("\n%d. iterasyon:\n",sayac);
    		    		printf("hata: %lf\n",hata);
    		    		processTokens(&rpnRoot, &stackTop,func,start);
    		    		result1= calculateRPN(&rpnRoot);
    		    		processTokens(&rpnRoot, &stackTop,func,end);
    		    		result2 = calculateRPN(&rpnRoot);
    		    		orta = (end*result1 - start*result2)/(result1-result2);
    		    		processTokens(&rpnRoot, &stackTop,func,orta);
    		    		ortadeger = calculateRPN(&rpnRoot);
    		    		printf("start:%lf\n",start);
    		    		printf("end:%lf\n",end);
    		    		printf("orta:%lf\n",orta);
    		    	    printf("f(start):%lf\n",result1);
    		    	    printf("f(end):%lf\n",result2);    		    		
    		    		printf("f(orta): %lf\n ",ortadeger);
    		    		kok = orta;
    		    		if(result1 * ortadeger < 0){
    		    			end = orta;
						}else if (result2 * ortadeger < 0){
							start = orta;
						}else if(result1 == 0){
							kok = start;
						}else if(result2 == 0){
							kok = end;
						}
						sayac++;		
					}
					printf("Kok: %lf\n",kok);
				}else{
					printf("Bu aralilkta Kok yok\n");
				}
			
    			break;
    		case 3:
    			system("cls");
    			printf("Newton-Rapshon yontemini sectiniz:\n");
    			printf("Fonksiyonu giriniz:\n");
    			scanf("%s",func);
    			printf("Baslangic degeri girmek icin 1 e,baslangic degeri girmeyip aralik girmek icin 2ye basiniz\n");
    			scanf("%d",&secim);
    			if(secim == 1){
    				printf("Baslangic degerini giriniz:\n");
    				scanf("%lf",&start);
				}else{
					printf("Araligin baslangic ve bitis degerlerini giriniz:\n");
					scanf("%lf",&start);
					scanf("%lf",&end);
				}
    			printf("Kabul edilebilir en yuksek hata:");
    			scanf("%lf",&epsilon);
    			printf("max iteration\n");
    			scanf("%d",&maxiter);
    			sayac = 1;
    			hata = 10;
    			while(sayac<maxiter && fabs(hata)>= epsilon){
    				processTokens(&rpnRoot, &stackTop,func,start);
    				result1= calculateRPN(&rpnRoot);
    				result2 = merkeziturev(func,start);
    				result = start - result1/result2;
    				hata = result-start;
    
    				start = result;
    				printf("\n%d. itersasyon:\n",sayac);
    				printf("f(x(i)): %lf\n",result1);
    				printf("f'(x(i)): %lf\n",result2);
    				printf("x(i+1):%lf\n",start);
    				printf("hata: %lf\n",hata);
    				sayac++;
				}
				printf("kok:%lf\n",start);
    			
    			break;
    		case 4:
    			system("cls");
    			printf("NxN'lik bir matrisin tersi Yontemini sectiniz\n");
    			printf("Matrisin Boyutunu giriniz\n");
    			scanf("%d", &k);
    			matris = allocate_matrix(k);
    			
				printf("Matris elemanlarini giriniz %dX%d Matrix(Once satirar dolduruluyor): \n", n, n);//once sat�r sutun
				for (i = 0; i < k; i++) {
					for (j = 0; j < k; j++) {
						printf("matris[%d][%d] : ", i,j);
						scanf("%lf", &matris[i][j]);
					}
			    }
			    d = determinant(matris, k);
			    if (d == 0){
			    	printf("Determinant 0 oldugu icin matrisin tersi alinamaz\n");	
				}else{
					cofactor(matris,k);
				}
				free_matrix(matris,k);
				break;
			case 5:
				system("cls");
				printf("Gauss Eliminasyon Yontemini sectiniz\n");
				printf("Matrisin boyutunu giriniz:\n");
				scanf("%d",&n);
				sonuc = (double *)malloc(n* sizeof(double));
				matrix = (double**)malloc(n*sizeof(double*));
				for(i=0;i<n;i++){
					matrix[i] = (double *)malloc((n+1)* sizeof(double));
				}
				printf("Matris elemanlarini giriniz %dX%d Matrix(Once satirlar dolduruluyor): \n", n,n);
				for (i = 0; i < n; i++) {
					for (j = 0; j < n+1; j++) {
						printf("\nmatris[%d][%d] : ", i,j);
						scanf("%lf", &matrix[i][j]);
					}
			    }
			    for(j=0; j<n; j++){
			    	for(i=0; i<n; i++){
			    		if(i>j){
			    			c=matrix[i][j]/matrix[j][j];
			    			for(k=0; k<n+1; k++){
			    				matrix[i][k]=matrix[i][k]-c*matrix[j][k];
			    			}
			    		}
					}
				}
				sonuc[n-1]=matrix[n-1][n]/matrix[n-1][n-1];
				sum = 0;
				for(i=n-2; i>=0; i--){
					sum=0;
					for(j=i; j<n; j++){
						sum=sum+matrix[i][j]*sonuc[j];
					}
					sonuc[i]=(matrix[i][n]-sum)/matrix[i][i];
				}
				
				printf("Sonuc: \n");
				for(i=0; i<n; i++){
					printf("\nx%d=%lf\t\n",i,sonuc[i]);
				}
				free(sonuc);
				sonuc = NULL;
				for (i = 0; i < n; i++) {
					free(matrix[i]);
				}
				free(matrix);
				matrix = NULL;
				break;
				
			case 6:
				system("cls");
				printf("Gauss-Seidal Metodunu sectiniz\n");
				printf("Matris Boyutunu Giriniz:\n ");
				scanf("%d", &n);
				printf("Max Iter:\n ");
				scanf("%d", &maxiter);
				printf("Kabul edilebilir hata toleransi:\n ");
				scanf("%lf", &tolerance);
				printf("Baslanic degerini giriniz:\n");
				scanf("%lf",&start);
				matrix = allocate_matrix(n);
				b = (double*)malloc(n * sizeof(double));
				xmatris = (double*)malloc(n * sizeof(double)); 
				printf("Matris Elamanlarini giriniz:\n");
				for (i = 0; i < n; i++) {
					for (j = 0; j < n; j++) {
						printf("Matris[%d][%d]:",i,j);
						scanf("%lf", &matrix[i][j]);
					}
				}
				printf("b yani sag tarafi giriniz:\n");
				for (i = 0; i < n; i++) {
					scanf("%lf", &b[i]);
					xmatris[i] = start;
			    }
			    diagonal_sort(matrix, b, n);
			    gauss_seidel(matrix, b, xmatris, n, maxiter, tolerance);
			    printf("Sonuc:\n");
			    
			    for (i = 0; i < n; i++) {
			    	printf("x[%d] = %lf\n", i, xmatris[i]);
			    }
			    free_matrix(matrix, n);
			    free(b);
			    free(xmatris);
			    b = NULL;
			    xmatris= NULL;
				break;
					
    		case 7:
    			system("cls");
    			printf("Sayisal Turev yontemini sectiniz:\n");
    			printf("fonksiyonu giriniz:\n");
    			scanf("%s",func);
    			printf("x:\n");
    			scanf("%lf",&x);
    			printf("h degerini giriniz:\n");
    			scanf("%lf",&h);
    			printf("Ileri fark ile turev icin 1\nGeri fark ile turev icin 2\nmerkezi fark ile turev icin 3 e basiniz\n ");
    			scanf("%d",&secim2);
    			switch(secim2){
    				case 1:
    					processTokens(&rpnRoot, &stackTop,func,x);
    					result1= calculateRPN(&rpnRoot);
    					processTokens(&rpnRoot, &stackTop,func,x+h);
    					result2= calculateRPN(&rpnRoot);
    					kok = (result2-result1)/h;
    					printf("turevin degeri: %lf\n",kok);
    					break;
    				case 2:
    					processTokens(&rpnRoot, &stackTop,func,x);
    					result1= calculateRPN(&rpnRoot);
    					processTokens(&rpnRoot, &stackTop,func,x-h);
    					result2= calculateRPN(&rpnRoot);
    					kok = (result1-result2)/h;
    					printf("turevin degeri: %lf\n",kok);
    	
    					
    					break;
    				case 3:
    					processTokens(&rpnRoot, &stackTop,func,x+h/2);
    					result1= calculateRPN(&rpnRoot);
    					processTokens(&rpnRoot, &stackTop,func,x-h/2);
    					result2= calculateRPN(&rpnRoot);
    					kok = (result1-result2)/h;
    					printf("turevin degeri: %lf\n",kok);
    					break;
    				default:
    					printf("Gecersiz secim\n");
    					break;
				}
				break;
			case 8:
				system("cls");
				printf("Simpson Integral Yontemini Sectiniz\n");
				printf("fonksiyonu giriniz:\n");
				scanf("%s",func);
				printf("Integralin sinirlarini giriniz bas ve son seklinde:\n");
				scanf("%lf",&start);
				scanf("%lf",&end);
				printf("Kac adim uygulamak istiyorsunuz");
				scanf("%d",&n);
				sum = 0;
				printf("Simpson 1/3 icin 1'i,simpson 3/8 icin 2 yi seciniz.\n");
				scanf("%d",&secim2);
				d = (end-start)/n;
				switch(secim2){
					
					case 1:
						if(n%2 != 0){
							printf("Simpson 1/3 metodu icin aralik sayisi cift olmalidir\n");
							
						}else{
							while(end != start){
								processTokens(&rpnRoot, &stackTop,func,start);
								result1= calculateRPN(&rpnRoot);//f(a)
								processTokens(&rpnRoot, &stackTop,func,start+d);
								result2 = calculateRPN(&rpnRoot);//f(b)
								processTokens(&rpnRoot, &stackTop,func,(start+start+d)/2);//f((a+b)/2)
								orta = calculateRPN(&rpnRoot);
								sum = sum+ (d*(result1+4*orta+result2))/6;
								start = start+d;// n = 2 olsun
							}
							printf("Sonuc: %lf\n",sum);
						}
						
						break;
					case 2:
						while(end != start){
							processTokens(&rpnRoot, &stackTop,func,start);
							result1= calculateRPN(&rpnRoot);//f(a)
							processTokens(&rpnRoot, &stackTop,func,start+d/3);
							orta =  calculateRPN(&rpnRoot);
							processTokens(&rpnRoot, &stackTop,func,start+d*2/3);
							orta2 =calculateRPN(&rpnRoot);
							processTokens(&rpnRoot, &stackTop,func,start+d);
							result2 = calculateRPN(&rpnRoot);//f(b)
							sum = sum+ d*(result1+3*orta+3*orta2+result2)/8;
							start = start+d;
							
						
						}
						printf("Sonuc: %lf\n",sum);
						break;
						
				}
				break;
			case 9:
				system("cls");
				printf("Trapez yontemini sectiniz\n");
				printf("Fonksiyonu Giriniz:\n");
				scanf("%s",func);
				printf("Integralin sinirlarini giriniz bas ve son seklinde:\n");
				scanf("%lf",&start);
				scanf("%lf",&end);
				printf("Kac adim uygulamak istiyorsunuz:\n");
				scanf("%d",&n);
				sum=0;
				d = (end-start)/n;
				while(start!=end){
					processTokens(&rpnRoot, &stackTop,func,start);
					result1= calculateRPN(&rpnRoot);
					processTokens(&rpnRoot, &stackTop,func,start+d);
					result2= calculateRPN(&rpnRoot);//f(a)
					sum = sum+(d*1/2*(result1+result2));
					start = start+d;
				}
				printf("Sonuc: %lf\n",sum);
				break;
				
    		case 10 :
    			system("cls");
    			printf("Degisken donusumsuz Gregory Newton Enterpolasyonu Yontemini Sectiniz\n");
    			printf("Eleman sayisi:\n");
    			scanf("%d",&elemansayisi);
    			noktalar = (double *)malloc(elemansayisi*sizeof(double));
    			deger = (double *)malloc(elemansayisi*sizeof(double));
				printf("Noktalari giriniz:\n");
				for(i=0;i<elemansayisi;i++){
					scanf("%lf",&noktalar[i]);
				}
				printf("Noktalara karsilik gelen degerleri giriniz:\n");
				for(i=0;i<elemansayisi;i++){
					scanf("%lf",&deger[i]);
				}
				printf("Hangi degeri bulmak istiyorusuz?");
				scanf("%lf",&x);
				h=noktalar[2]-noktalar[1];
				d = deger[0];
				a=1;
				p = (x - noktalar[0]) / h;
				double *fark = (double *)malloc(elemansayisi * sizeof(double));
				for (i = 0; i < elemansayisi; i++) {
					fark[i] = deger[i];
				}
				for (i = 1; i < elemansayisi; i++) {
					for (j = 0; j < elemansayisi - i; j++) {
						fark[j] = fark[j + 1] - fark[j];
					}
					a = a * (p - (i - 1)) / i;
					d = d + a * fark[0];
				}
				printf("Sonuc:%lf\n",d);
				free(deger);
				free(noktalar);
				free(fark);
				
				deger = NULL;
				noktalar = NULL;
    			break;
    			
	    }
	
	}while(secim != 0);
	
    return 0;
}

