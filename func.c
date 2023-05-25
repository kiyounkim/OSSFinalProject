#include <stdio.h>
#include <string.h>
typedef struct{
    char name[20];
    int price;
    char type;
    int quantity;
}Menu;

int selectMenu(){
    int menu;
    printf("\n*** 카페 음료 관리 ***\n");
    printf("1. 메뉴 조회\n");
    printf("2. 메뉴 추가\n");
    printf("3. 메뉴 수정\n");
    printf("4. 메뉴 삭제\n");
    printf("5. 메뉴 검색\n");
    printf("6. 가격대 검색\n");
    printf("7. 종류별 검색\n");
    printf("8. 재고 검색\n");
    printf("9. 저장\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}
void readProduct(Menu *menu){
    printf("Menu: %s Price: %d Type: %c Quantity: %d\n", menu->name, menu->price, menu->type, menu->quantity);
}
void showMenu(Menu *menu, int index){
    for(int i=0; i<index; i++){
        if(menu[i].price==-1) continue;
        printf("#%d ", i+1);
        readProduct(&menu[i]);
    }
}
int createProduct(Menu *menu){
    getchar();
    printf("메뉴 이름은? ");
    scanf("%[^\n]s", menu->name);
    while(1){
        printf("메뉴 가격은? ");
        scanf("%d", &menu->price);
        if(menu->price<=0) {
            printf("가격이 무료입니다. 맞습니까? (Y/N) ", menu->price);
            getchar();
            char answer;
            scanf("%c", &answer);
            if(answer=='Y') break;
        }
        else break;
    }
    getchar();
    if(strstr(menu->name, "아이스")!=NULL)
        menu->type = 'I';
    else if(strstr(menu->name,"핫")!=NULL)
        menu->type = 'H';
    else{
        printf("메뉴 종류는? (Hot=H / Ice=I / Both=B)");
        scanf("%c", &menu->type);
    }
    printf("메뉴 재고는? (제한 없음 = -1)");
    scanf("%d", &menu->quantity);

    return 1;
}

int selectDataNo(Menu *menu, int count){
    int no;
    showMenu(menu,count);
    printf("번호는 (취소:0)?");
    scanf("%d",&no);
    return no;
}
void updateMenu(Menu *menu){
    createProduct(menu);
}
void searchMenu(Menu *menu, int count){
    getchar();
    printf("검색할 메뉴 이름은? (부분만 입력 가능)");
    char search[20];
    scanf("%[^\n]s", search);
    for(int i=0; i<count; i++){
        if(strstr(menu[i].name, search)!=NULL&&menu[i].price!=-1){
            printf("#%d ", i+1);
            readProduct(&menu[i]);
        }
    }
}
void searchPrice(Menu *menu, int count){
    getchar();
    printf("검색할 가격대는? 두 숫자 입력 (최소, 최대) ");
    int searchMin, searchMax;
    scanf("%d %d", &searchMin, &searchMax);
    for(int i=0; i<count; i++){
        if(menu[i].price<=searchMax&&menu[i].price>=searchMin&&menu[i].price!=-1){
            printf("#%d ", i+1);
            readProduct(&menu[i]);
        }
    }
}
void typeSearch(Menu *menu, int count){
    getchar();
    printf("검색할 종류는? (Hot=H / Ice=I / Both=B)");
    char search;
    scanf("%c", &search);
    for(int i=0; i<count; i++){
        if(menu[i].type==search&&menu[i].price!=-1){
            printf("#%d ", i+1);
            readProduct(&menu[i]);
        }
    }
}
void quantitySearch(Menu *menu, int count){
    getchar();
    printf("재고가 부족한 메뉴만 검색하시겠습니까? (Y/N)");
    char search;
    scanf("%c", &search);
    if(search=='Y'){
        for(int i=0; i<count; i++){
            if(menu[i].quantity==0&&menu[i].price!=-1){
                printf("#%d ", i+1);
                readProduct(&menu[i]);
            }
        }
    }
    else{
        printf("재고의 최소값을 입력해주세요. ");
        int searchMin;
        scanf("%d", &searchMin);
        for(int i=0; i<count; i++){
            if(menu[i].quantity>=searchMin&&menu[i].price!=-1){
                printf("#%d ", i+1);
                readProduct(&menu[i]);
            }
        }
    }
}
void saveData(Menu *menu, int count){
    FILE *fp;
    fp = fopen("menu.txt", "wt");
    for(int i=0; i<count; i++){
        if(menu[i].price==-1) continue;
        fprintf(fp, "%s: %d %c %d\n", menu[i].name, menu[i].price, menu[i].type, menu[i].quantity);
    }
    fclose(fp);
    printf("저장됨!\n");
}
int loadData(Menu *menu){
    int count = 0;
    FILE *fp;
    fp = fopen("menu.txt", "rt");
    if(fp==NULL){
        printf("=> 파일 없음\n");
        return 0;
    }
    while(!feof(fp)){
        fscanf(fp, "%[^:]: %d %c %d\n", menu[count].name, &menu[count].price, &menu[count].type, &menu[count].quantity);
        count++;
    }
    fclose(fp);
    printf("=> 로딩 성공!\n");
    showMenu(menu, count);
    return count;
}