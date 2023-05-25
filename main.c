#include <stdio.h>
#include "func.h"

int main(void)
{
    Menu menu[100];
    int count, index = 0;
    count = loadData(menu);
    index = count;
    int menuNum,no;
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
                no=selectDataNo(menu, count);
                if(no==0){
                    printf("=>취소됨!");
                    continue;
                }
                updateMenu(&menu[no-1]);
                printf("=> 수정됨!\n");
            break;
            case 4:
                no=selectDataNo(menu, count);
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
                searchMenu(menu, count);
            break;
            case 6:
                searchPrice(menu, count);
            break;
            case 7:
                typeSearch(menu, count);
            break;
            case 8:
                quantitySearch(menu, count);
            break;
            case 9:
                saveData(menu, index);
            break;
        }
    }
    return 0;
}
