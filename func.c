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
    return no;
}
void updateMenu(Menu *menu){
    createProduct(menu);
}
void searchMenu(Menu *menu, int count){
    getchar();
    printf("�˻��� �޴� �̸���? (�κи� �Է� ����)");
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
    printf("�˻��� ���ݴ��? �� ���� �Է� (�ּ�, �ִ�) ");
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
    printf("�˻��� ������? (Hot=H / Ice=I / Both=B)");
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
    printf("��� ������ �޴��� �˻��Ͻðڽ��ϱ�? (Y/N)");
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
        printf("����� �ּҰ��� �Է����ּ���. ");
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
    printf("�����!\n");
}
int loadData(Menu *menu){
    int count = 0;
    FILE *fp;
    fp = fopen("menu.txt", "rt");
    if(fp==NULL){
        printf("=> ���� ����\n");
        return 0;
    }
    while(!feof(fp)){
        fscanf(fp, "%[^:]: %d %c %d\n", menu[count].name, &menu[count].price, &menu[count].type, &menu[count].quantity);
        count++;
    }
    fclose(fp);
    printf("=> �ε� ����!\n");
    showMenu(menu, count);
    return count;
}