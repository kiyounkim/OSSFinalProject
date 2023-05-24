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
                printf("=> �߰���!\n");
            break;
            case 3:
                int no=selectDataNo(menu, count);
                if(no==0){
                    printf("=>��ҵ�!");
                    continue;
                }
                updateMenu(&menu[no-1]);
                printf("=> ������!\n");
            break;
            case 4:
                int no=selectDataNo(menu, count);
                if(no==0){
                    printf("=>��ҵ�!");
                    continue;
                }
                int deleteok;
                printf("������ �����Ͻðڽ��ϱ�?(����:1)");
                scanf("%d",&deleteok);
                if(deleteok == 1){
                    menu[no-1].price=-1;
                }
                printf("=> ������!\n");
            break;
            case 5:
                printf("�޴� �˻�\n");
            break;
            case 6:
                printf("���ݴ� �˻�\n");
            break;
            case 7:
                printf("������ �˻�\n");
            break;
            case 8:
                printf("��� �˻�\n");
            break;
            case 9:
                printf("����\n");
            break;
        }
    }
    return 0;
}
int selectMenu(){
    int menu;
    printf("\n*** ī�� ���� ���� ***\n");
    printf("1. �޴� ��ȸ\n");
    printf("2. �޴� �߰�\n");
    printf("3. �޴� ����\n");
    printf("4. �޴� ����\n");
    printf("5. �޴� �˻�\n");
    printf("6. ���ݴ� �˻�\n");
    printf("7. ������ �˻�\n");
    printf("8. ��� �˻�\n");
    printf("9. ����\n");
    printf("0. ����\n\n");
    printf("=> ���ϴ� �޴���? ");
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
    printf("�޴� �̸���? ");
    scanf("%[^\n]s", menu->name);
    while(1){
        printf("�޴� ������? ");
        scanf("%d", &menu->price);
        if(menu->price<=0) {
            printf("������ �����Դϴ�. �½��ϱ�? (Y/N) ", menu->price);
            getchar();
            char answer;
            scanf("%c", &answer);
            if(answer=='Y') break;
        }
        else break;
    }
    getchar();
    if(strstr(menu->name, "���̽�")!=NULL)
        menu->type = 'I';
    else if(strstr(menu->name,"��")!=NULL)
        menu->type = 'H';
    else{
        printf("�޴� ������? (Hot=H / Ice=I / Both=B)");
        scanf("%c", &menu->type);
    }
    printf("�޴� ����? (���� ���� = -1)");
    scanf("%d", &menu->quantity);

    return 1;
}

int selectDataNo(Menu *menu, int count){
    int no;
    showMenu(menu,count);
    printf("��ȣ�� (���:0)?");
    scanf("%d",&no);
    getchar();
    return no;
}
void updateMenu(Menu *menu){
    createProduct(menu);
}