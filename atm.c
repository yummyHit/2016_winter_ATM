#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Menu(); // 초기메뉴화면 출력 함수
void NewAccount(); // 새 계좌 만들기 함수
void Deposit(); // 입금 함수
void Withdraw(); // 출금 함수
void Show(); // 생성된 전체 계좌 출력 함수
double random_prime1();
double random_prime2();
double relative_prime(double a);
double make_k(double e, double pi);
double exponetial_function(double a, double b);
void make_key(double *key);
void check_password();

typedef struct {// 계좌정보를 담고있는 Account 구조체
   int accNum; // 계좌번호
   char accName[20]; // 이름
   int accMoney; // 잔액
} Account;

Account accArr[100]; // Account 구조체를 크기 100인 배열로 선언
int accNum; // 계좌 넘버

int main(){
   int i, click; // 메뉴 선택 변수
   for(i = 0; i < 100; i++) {
      accArr[i].accNum = 0;
      *accArr[i].accName = NULL;
      accArr[i].accMoney = 0;
   }
   while(1) {
      Menu();
      printf("선택: ");
      scanf("%d", &click);
      switch (click) { // switch문으로 각 메뉴의 경우 일 때로 넘어감
      case 1:
         NewAccount(); break; // 계좌 생성
      case 2:
         check_password(); break; // 입금 및 출금
      case 3:
         Show(); break; // 전체 출력
      case 4:
         return 0; // 종료
      default:
         printf("잘못된 선택입니다.\n");
      }
   } // while문 무한루프 생성
}

void Menu() {// 메뉴
   printf("-------Menu -------\n");
   printf("1. 계좌 개설\n");
   printf("2. 입금 및 출금\n");
   printf("3. 계좌정보 전체 출력\n");
   printf("4. 프로그램 종료\n");
}

void NewAccount() {// 새 계좌 생성
   FILE *fp;
   char *tmp = (char*)malloc(sizeof(char));
   printf("<계좌 개설>\n");
   printf("계좌 번호: ");
   scanf("%d", &accArr[accNum].accNum);
   fflush(stdin);
   printf("이 름: ");
   scanf("%s", accArr[accNum].accName);
   printf("입금액: ");
   scanf("%d", &accArr[accNum].accMoney);
	fflush(stdin);
   sprintf(tmp, "%d%s.txt", accArr[accNum].accNum, accArr[accNum].accName);
   fclose(fopen(tmp, "w"));
   accNum++; // 계좌 넘버 카운트 ++
}

void Deposit() {// 입금
   int money;
   int id, i;
   printf("<입 금>\n");
   printf("계좌 번호: ");
   scanf("%d", &id);
   printf("입금액: ");
   scanf("%d", &money);
   for (i = 0; i < accNum; i++) {// 계좌 넘버의 수 만큼 for문 반복
      if (accArr[i].accNum == id) {// 입력한 id와 등록된 계좌의 accNum이랑 같으면
         accArr[i].accMoney += money; // 입금액을 해당 구조체의 accMoney에 더해준다
         printf("입금완료\n");
         return; // return으로 Deposit() 함수 탈출
      }
   }
   printf("유효하지 않은 계좌 입니다.\n");
}

void Withdraw() {// 출금
   int money;
   int id, i;
   printf("<출 금>\n");
   printf("계좌 번호: ");
   scanf("%d", &id);
   printf("출금액: ");
   scanf("%d", &money);
   for (i = 0; i < accNum; i++) {// 계좌 넘버의 수 만큼 for문 반복
      if (accArr[i].accNum == id) {// 입력한 id와 등록된 계좌의 accNum이랑 같으면
         if (accArr[i].accMoney < money) {// 출금하고싶은 액수보다 잔액이 적을 경우
            printf("잔액부족\n");
            return;
         }
         accArr[i].accMoney -= money; // 잔액에서 출금액을 빼준다
         printf("출금완료\n");
         return; // return으로 Deposit() 함수 탈출
      }
   }
   printf("유효하지 않은 계좌 입니다.\n");
}

void Show() {// 전체 계좌 출력
   int i = 0;
   for (i = 0; i < accNum; i++) {// 계좌 넘버의 수 만큼 for문 반복
      printf("계좌 번호: %d\n", accArr[i].accNum);
      printf("이 름: %s\n" , accArr[i].accName);
      printf("잔 액: %d\n" , accArr[i].accMoney);
   }
}

double random_prime1() {
   int i;
   double prime1;
   srand((unsigned int)time(NULL));
   while (1) {
      prime1 = (rand() % 9) + 2;
      printf("random_prime1 = %.0f\n", prime1);
      for (i = 2; i < (prime1 / 2) + 1; i++) if (fmod(prime1, i) == 0) {
         i = 1;
         break;
      }
      if(i == 1) continue;
      else break;
   }
   return prime1;
}

double random_prime2() {
   int i;
   double prime2;
   srand((unsigned int)time(NULL));
   while (1) {
      prime2 = (rand() % 8) + 2;
      printf("random_prime2 = %.0f\n", prime2);
      for (i = 2; i < (prime2 / 2) + 1; i++) if (fmod(prime2, i) == 0) {
         i = 1;
         break;
      }
      if(i == 1) continue;
      else break;
   }
   return prime2;
}

double relative_prime(double a) {
   double e, i;
   int sub, count = 0;
   srand((unsigned int)time(NULL));
   if (a > 100000) sub = 100000;
   else sub = a;
   while (1) {
	if((count++) > 50) break;
      e = (rand() % (sub - 1)) + 2;
      printf("relative_prime = %.0f\n", e);
      for (i = e; i > 1; i--) if (fmod(a, i) == 0 && fmod(e, i) == 0) {
         i = -1;
         break;
      }
      if(i == -1) continue;
      else break;
   }
   return e;
}

double make_k(double e, double pi) {
   double k, result;
   for (k = 2; k > 1; k++) {
      result = fmod((pi*k + 1), e);
      if (result == 0) break;
   }
   return (double)k;
}

double exponetial_function(double a, double b) {
   int i;
   double result = 1;
   for (i = 0; i < b; i++) result *= a;
   return result;
}

void make_key(double *key) {
   double pi;
   while(1) if((pi = (random_prime1() - 1) * (random_prime2() - 1)) > 2) break;
   printf("pi = %.0f\n", pi);
   *key = random_prime1() * random_prime2();
   printf("*key = %.0f\n", *key);
   *(key + 1) = relative_prime(pi);
   printf("*(key + 1) = %.0f\n", *(key+1));
   *(key + 2) = ((pi * make_k(*(key + 1), pi)) + 1) / *(key + 1);
   printf("*(key + 2) = %.0f\n", *(key+2));
   return;
}

void check_password() {
   double key[3] = {0,};
   int button, password = 0, input;
   double secret_number, decoding_number;
   FILE *fp;
   char fname[20];
   srand((unsigned int)time(NULL));
   make_key(key);

   while (1) {
      printf("1. 일회성 비밀번호 생성\n");
      printf("2. 로그인 후 입금하기\n");
      printf("3. 로그인 후 출금하기\n");
      scanf("%d", &button);
      switch (button) {
      case 1:
         fflush(stdin);
         printf("본인확인을 위해 계좌번호와 이름을 입력해주세요(띄어쓰기 없이) : ");
         scanf("%s", fname);
         if((fp = fopen(fname, "r+")) != NULL) {
            printf("공개키와 비밀키를 생성합니다.\n\n");   
            fprintf(fp, "비밀키 : (%.0f, %.0f)\n", key[0],key[2]);
            printf("공개키 : (%.0f,%.0f)\n\n", key[0], key[1]);
            printf("암호화된 번호를 받겠습니까?(yes = 1) : ");
            scanf("%d", &button);
            fflush(stdin);
            switch (button) {
            case 1:
               password = (rand() % 4) + 2;
               secret_number = fmod(exponetial_function((double)password, key[1]), key[0]);
               printf("암호문을 푸시겠습니까?(yes = 1) : ");
               scanf("%d", &button);
               fflush(stdin);
               switch (button) {
               case 1:
                  decoding_number = fmod(exponetial_function(secret_number, key[2]), key[0]);
                  fprintf(fp, "비밀번호 : %.0f\n", decoding_number);
                  break;
               default:
                  printf("No를 입력하셨습니다.\n\n");
                  break;
               }
               break;
            default:
               printf("다시 시도해 주세요.\n");
               break;
            }
         }
         else printf("본인확인이 실패하셨습니다.\n\n");
         break;

      case 2:
         if(password == 0) {
            printf("OTP 생성기를 먼저 실행해 주세요.\n");
            break;
         }
         printf("비밀번호를 입력해주세요.\n");
         scanf("%d", &input);
         if (input == password) Deposit();
         else printf("로그인에 실패하셨습니다.\n다시 시도해 주세요.\n");
	fclose(fopen(fname, "w"));
         return;
      case 3:
         if(password == 0) {
            printf("OTP 생성기를 먼저 실행해 주세요.\n");
            break;
         }
         printf("비밀번호를 입력해주세요.\n");
         scanf("%d", &input);
         if (input == password) Withdraw();
         else printf("로그인에 실패하셨습니다.\n다시 시도해 주세요.\n");
	fclose(fopen(fname, "w"));
         return;
      default:
         printf("잘못 입력하셨습니다.\n다시 시도해 주세요.\n");
         break;
      }
	if(password != 0) fclose(fp);
   }
}
