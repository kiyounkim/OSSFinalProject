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
void searchMenu(Menu *menu, int count);
void searchPrice(Menu *menu, int count);
void typeSearch(Menu *menu, int count);
void quantitySearch(Menu *menu, int count);
void saveData(Menu *menu, int count);
int loadData(Menu *menu);
