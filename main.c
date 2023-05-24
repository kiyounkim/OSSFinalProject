#include <stdio.h>
#include <string.h>

typedef struct{
    char name[20];
    int price;
    char type;
    int quantity;
}Menu;

int selectMenu();
void showMenu(Menu *menu, int index);
int createProduct(Menu *menu);
int selectDataNo(Menu *menu, int count);
void updateMenu(Menu *menu);
int main(void)
{
    Menu menu[100];
    int count = 0, index = 0;
    int menuNum;
    while(1){
        menuNum=selectMenu();
        if(menuNum==0) break;
        switch(menuNum){
            case 1:
                showMenu(menu, index);
            break;
            case 2:
                count+=createProduct(&menu[index++]);
                printf("=> 추가됨!\n");
            break;
            case 3:
                int no=selectDataNo(menu, count);
                if(no==0){
                    printf("=>취소됨!");
                    continue;
                }
                updateMenu(&menu[no-1]);
                printf("=> 수정됨!\n");
            break;
            case 4:
                int no=selectDataNo(menu, count);
                if(no==0){
                    printf("=>취소됨!");
                    continue;
                }
                int deleteok;
                printf("정말로 삭제하시겠습니까?(삭제:1)");
                scanf("%d",&deleteok);
                if(deleteok == 1){
                    menu[no-1].price=-1;
                }
                printf("=> 삭제됨!\n");
            break;
            case 5:
                printf("메뉴 검색\n");
            break;
            case 6:
                printf("가격대 검색\n");
            break;
            case 7:
                printf("종류별 검색\n");
            break;
            case 8:
                printf("재고 검색\n");
            break;
            case 9:
                printf("저장\n");
            break;
        }
    }
    return 0;
}
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
    getchar();
    return no;
}
void updateMenu(Menu *menu){
    createProduct(menu);
}