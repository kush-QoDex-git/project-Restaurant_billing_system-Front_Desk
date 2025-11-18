#include "admin_ops.h"
void PressEnter()
{
    char ent[2];
    printf("\n\t\tPress Enter if DONE:");
    fgets(ent, 2, stdin);
    fflush(stdin);
}
int displaymenu1();
void createBillmenu();
void adminmenu();
void welcome()
{
    int spin;
start:
    printf("\t\t\t\t __________________________________________________________________\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|\t\t\tWelcome to Front Desk!\t\t\t   |\n");
    printf("\t\t\t\t|\t\t   Please Enter the PIN to Log IN:\t\t   |\n");
    printf("\t\t\t\t|__________________________________________________________________|\n");
    printf("\n\t\t\t\t\t\t\t|-->");
    scanf("%d", &spin);
    if (pintAuth(spin))
    {
        displaymenu1();
    }
    else
    {
        goto start;
    }
}
int displaymenu1()
{
    int choice;
dm1:
    printf("\n");
    printf("\t\t\t\t __________________________________________________________________\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|           1. Create Bill                 2. ADMIN                |\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|                                          0. Exit                 |\n");
    printf("\t\t\t\t|__________________________________________________________________|\n");
    printf("\n\t\t\t\tChoose an option [Enter its corresponding number] :");
    scanf("%d", &choice);
    fflush(stdin);
    switch (choice)
    {
    case 0:
        return 0;
    case 1:
        createBillmenu();
        break;
    case 2:
        adminmenu();
        break;

    default:
        printf("\n\t\t\t\t! Please Enter the \"Number of give option only\" !\n");
        goto dm1;
    }
}
void print_bill(BILL *);
void createBillmenu()
{
    BILL bb;

    int num = 0;
    char repeat;

    printf("\nEnter Server/Waiter Name: ");
    fgets(bb.serverName, sizeof(bb.serverName), stdin);
    remove_fgets_newline(bb.serverName);
    fflush(stdin);

    printf("\nEnter Table Number: ");
    fgets(bb.table_num, sizeof(bb.table_num), stdin);
    remove_fgets_newline(bb.table_num);
    fflush(stdin);

    printf("\nEnter customer name: ");
    fgets(bb.customerName, sizeof(bb.customerName), stdin);
    remove_fgets_newline(bb.customerName);
    fflush(stdin);

    printf("\nEnter customer contact number: ");
    fgets(bb.customerContact, sizeof(bb.customerContact), stdin);
    remove_fgets_newline(bb.customerContact);
    fflush(stdin);

    while (1)
    {
        printf("\n\t\tEnter item no. %d: ", num + 1);
        fgets(bb.itemList[num], sizeof(bb.itemList[0]), stdin);
        remove_fgets_newline(bb.itemList[num]);
        fflush(stdin);
        if (doesItemExistsinMenu(bb.itemList[num]) < 0)
        {
            printf("\n\t\t\t! Item with that name does not exists in our menu !\n");
            continue;
        }

        printf("\n\t\t\tIts Size[nosize(0),small(1),medium(2),large(3)]: ");
        scanf("%d", &bb.size[num]);
        fflush(stdin);

        printf("\n\t\t\tIts Quantity: ");
        scanf("%d", &bb.quantities[num]);
        fflush(stdin);

        printf("\n\t\tAdd More [y/n]: ");
        scanf("%c", &repeat);
        fflush(stdin);
        num++;
        if (repeat != 'y' && repeat != 'Y')
        {
            break;
        }
    }
    printf("\n\t\tEnter Mode of Payment: ");
    fgets(bb.mop, sizeof(bb.mop), stdin);
    remove_fgets_newline(bb.mop);
    fflush(stdin);

    bb.itemListCount = num;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    bb.billtime = *local;
    bb.gst = 5.6;
    auto_set_invoice_num(&bb);
    add_to_billHistory(&bb);
    print_bill(&bb);
    PressEnter();
    displaymenu1();
}

void print_bill(BILL *pb)
{
    ITEM itm;
    char restaurantName[] = "THE TAJ HOTEL";
    char addressline1[] = "A22, BLOCK-5, City Complex";
    char addressline2[] = "Azad Nagar";
    char addressline3[] = "Mumbai";
    char receptionContact[] = "Ph No. 1001001012";
    char sizes[4][7] = {"", "regular", "medium", "large"};
    int s;
    // printf("\n|\t%s\t|\n|\t%s\t|\n|\t%s\t|\n|\t%s\t|\n|\tPH: %s\t|\n", restaurantName, addresslin1, addresslin2, addresslin3, receptionContact);
    printf("\n __________________________________________________________________________________________\n");
    printf("|");
    print_sufficient_spaces_in_ui(0, 90);
    printf("|\n");

    printf("|");
    print_sufficient_spaces_in_ui((strlen(restaurantName) / 2), 45);
    printf("%s", restaurantName);
    print_sufficient_spaces_in_ui((45 - (strlen(restaurantName) / 2) + (strlen(restaurantName))), 90);
    printf("|\n");

    printf("|");
    print_sufficient_spaces_in_ui((strlen(addressline1) / 2), 45);
    printf("%s", addressline1);
    print_sufficient_spaces_in_ui((45 - (strlen(addressline1) / 2) + (strlen(addressline1))), 90);
    printf("|\n");

    printf("|");
    print_sufficient_spaces_in_ui((strlen(addressline2) / 2), 45);
    printf("%s", addressline2);
    print_sufficient_spaces_in_ui((45 - (strlen(addressline2) / 2) + (strlen(addressline2))), 90);
    printf("|\n");

    printf("|");
    print_sufficient_spaces_in_ui((strlen(addressline3) / 2), 45);
    printf("%s", addressline3);
    print_sufficient_spaces_in_ui((45 - (strlen(addressline3) / 2) + (strlen(addressline3))), 90);
    printf("|\n");

    printf("|");
    print_sufficient_spaces_in_ui((strlen(receptionContact) / 2), 45);
    printf("%s", receptionContact);
    print_sufficient_spaces_in_ui((45 - (strlen(receptionContact) / 2) + (strlen(receptionContact))), 90);
    printf("|\n");

    printf("|------------------------------------------------------------------------------------------|\n");
    printf("|\t\tServer\t\tT.No.\t\t  Date\t\t  Time\t\t\t   |\n");
    printf("|\t\t %s\t\t %s\t\t%d/%d/%d\t  %d:%d\t\t\t   |\n", pb->serverName, pb->table_num, pb->billtime.tm_mday, pb->billtime.tm_mon, pb->billtime.tm_year + 1900, pb->billtime.tm_hour, pb->billtime.tm_min);
    printf("|------------------------------------------------------------------------------------------|\n");
    printf("|\t Items\t\t\t\tPrice\t\tQty\t\tTotal Rs.\t   |\n");
    for (int i = 0; i < pb->itemListCount; i++)
    {
        s = pb->size[i] - 1;
        s = (s < 0) ? 0 : s;
        read_item_from_menu_by_name(pb->itemList[i], &itm);
        printf("|\t%s %s", pb->itemList[i], sizes[pb->size[i]]);
        print_sufficient_spaces_in_ui((strlen(pb->itemList[i]) + strlen(sizes[pb->size[i]])), 31);
        printf("%.2f\t\t %d\t\t %.2f\n", itm.price_in_rupee[s], pb->quantities[i], (itm.price_in_rupee[s] * pb->quantities[i]));
    }
    printf("|------------------------------------------------------------------------------------------|\n");
    printf("|\tGross Total : \t\t\t\t\t\t%.2f\n", gross_total_calc(pb));
    printf("|\tgst( @%0.2f%% ) : \t\t\t\t\t%0.2f\n", pb->gst, ((pb->gst) / 100) * gross_total_calc(pb));

    printf("|------------------------------------------------------------------------------------------|\n");
    printf("|\tTotal Paymet:\t\t\t%0.2f\n", gross_total_calc(pb) + (gross_total_calc(pb) * (pb->gst / 100)));
    printf("|\tMode of Paymet:\t\t\t%s\n", pb->mop);
    printf("|__________________________________________________________________________________________|\n");
}
void add_item_to_menu_ui();
void show_bill_history_ui();
void revenue_ui();
void emp_served_guest_ui();
void updatePin_ui()
{
    int pin;
    printf("\n\t\t\tEnter New Pin [6 digits]--> ");
    scanf("%d", &pin);
    updatePin(pin);
    if (pintAuth(pin))
    {
        printf("\n\t\t\t\tPin Successfully updated");
    }
    else
    {

        printf("\n\t\t\t\tPin updated !Unsuccessfull. \n");
    }
}
void showItemsMenuContentPrint(ITEM itm)
{
    printf("\t|\t|\t|\t%s", itm.name);
    print_sufficient_spaces_in_ui(strlen(itm.name), 62);
    for (int i = 0; i < 3; i++)
    {
        if (itm.price_in_rupee[i] != 0)
        {
            printf("%.1f    ", itm.price_in_rupee[i]);
        }
    }

    printf("\n\t|\t|\t|\t( %s )", itm.description);
    print_sufficient_spaces_in_ui(strlen(itm.description), 92);
    printf("|\t|\t|\n");
    printf("\t|\t|\t|                                                                                                       |\t|\t|\n");
}
void print_locality_menu(char *locality, char *category)
{
    printf("\t|\t _______________________________________________________________________________________________________________________ \t|\n");
    printf("\t|\t|");
    print_sufficient_spaces_in_ui(0, 119);
    printf("|\t|\n");

    printf("\t|\t|");
    print_sufficient_spaces_in_ui((strlen(locality) / 2), 60);
    char lct[20] = "\0";
    strcpy(lct, locality);
    strUpper(lct);
    printf("%s", lct);
    print_sufficient_spaces_in_ui((60 - (strlen(locality) / 2) + strlen(locality)), 119);
    printf("|\t|\n");
    printf("\t|\t|\t \t\t\t\t\t\t          \t\t\t\t\t\t \t|\t|\n");
    printf("\t|\t|\t _______________________________________________________________________________________________________ \t|\t|\n");
    printf("\t|\t|\t|\t\t\t\t\t\t          \t\t\t\t\t\t|\t|\t|\n");
    printf("\t|\t|\t|\t\t\t\t\t\t    VEG   \t\t\t\t\t\t|\t|\t|\n");
    printf("\t|\t|\t|\t\t\t\t\t\t          \t\t\t\t\t\t|\t|\t|\n");
    ITEM itm;
    FILE *menufile = fopen("./data_files/menudata.dat", "rb");
    while (fread(&itm, sizeof(ITEM), 1, menufile))
    {
        if ((strcmp_ig_case(itm.category, category) == 0) && (strcmp_ig_case(itm.locality, locality) == 0) && (itm.veg = 1))
        {
            showItemsMenuContentPrint(itm);
        }
    }
    printf("\t|\t|\t|_______________________________________________________________________________________________________|\t|\t|\n");
    fclose(menufile);

    printf("\t|\t|\t                                                                                                         \t|\t|\n");
    printf("\t|\t|\t _______________________________________________________________________________________________________ \t|\t|\n");
    printf("\t|\t|\t|\t\t\t\t\t\t          \t\t\t\t\t\t|\t|\t|\n");
    printf("\t|\t|\t|\t\t\t\t\t\t  NON-VEG \t\t\t\t\t\t|\t|\t|\n");
    printf("\t|\t|\t|\t\t\t\t\t\t          \t\t\t\t\t\t|\t|\t|\n");
    menufile = fopen("./data_files/menudata.dat", "rb");
    while (fread(&itm, sizeof(ITEM), 1, menufile))
    {
        if ((strcmp_ig_case(itm.category, category) == 0) && (strcmp_ig_case(itm.locality, locality) == 0) && (itm.veg = 0))
        {
            showItemsMenuContentPrint(itm);
        }
    }
    printf("\t|\t|\t|_______________________________________________________________________________________________________|\t|\t|\n");
    fclose(menufile);
    printf("\t|\t|                                                                                                                       |\t|\n");
    printf("\t|\t|_______________________________________________________________________________________________________________________|\t|\n");
}
void showItemsMenu()
{
    printf("\n");
    printf("\t _______________________________________________________________________________________________________________________________________\n");
    printf("\t|                                                                                                                                       |\n");
    printf("\t|\t\t __________      __________       ________________       ___________        ______       ______       ______\t\t|\n");
    printf("\t|\t\t|          \\    /          |     |                |     |           \\      |      |     |      |     |      |\t\t|\n");
    printf("\t|\t\t|           \\  /           |     |      __________|     |            \\     |      |     |      |     |      |\t\t|\n");
    printf("\t|\t\t|            \\/            |     |     |                |             \\    |      |     |      |     |      |\t\t|\n");
    printf("\t|\t\t|      |\\          /|      |     |     |__________      |      |\\      \\   |      |     |      |     |      |\t\t|\n");
    printf("\t|\t\t|      | \\        / |      |     |                |     |      | \\      \\  |      |     |      |     |      |\t\t|\n");
    printf("\t|\t\t|      |  \\______/  |      |     |      __________|     |      |  \\      \\ |      |     |      |     |      |\t\t|\n");
    printf("\t|\t\t|      |            |      |     |     |                |      |   \\      \\|      |     |      |_____|      |\t\t|\n");
    printf("\t|\t\t|      |            |      |     |     |__________      |      |    \\             |     |                   |\t\t|\n");
    printf("\t|\t\t|      |            |      |     |                |     |      |     \\            |     |                   |\t\t|\n");
    printf("\t|\t\t|______|            |______|     |________________|     |______|      \\___________|     |___________________|\t\t|\n");
    printf("\t|                                                                                                                                       |\n");
    printf("\t|                                                                                                                                       |\n");
    printf("\t|                                                                                                                                       |\n");

    printf("\t|\t \t \t\t\t\t\t\tBREAKFAST \t\t\t\t\t \t\t \t|\n");

    print_locality_menu("", "breakfast");
    printf("\t|\t                                                                                                                         \t|\n");
    printf("\t|_______________________________________________________________________________________________________________________________________|\n");
    printf("\t|\t                                                                                                                         \t|\n");
    printf("\t|\t \t \t\t\t\t\t\tAPPETIZERS\t\t\t\t\t \t\t \t|\n");

    print_locality_menu("indian", "appetizer");
    printf("\t|\t                                                                                                                         \t|\n");
    print_locality_menu("italian", "appetizer");
    printf("\t|\t                                                                                                                         \t|\n");
    print_locality_menu("Chinese", "appetizer");
    printf("\t|\t                                                                                                                         \t|\n");
    printf("\t|_______________________________________________________________________________________________________________________________________|\n");
    printf("\t|\t                                                                                                                         \t|\n");
    printf("\t|\t \t \t\t\t\t\t\tMAINCOURES\t\t\t\t\t\t \t \t|\n");
    print_locality_menu("indian", "maincourse");
    printf("\t|\t                                                                                                                         \t|\n");
    print_locality_menu("italian", "maincourse");
    printf("\t|\t                                                                                                                         \t|\n");
    print_locality_menu("Chinese", "maincourse");
    printf("\t|                                                                                                                                       |\n");
    printf("\t|_______________________________________________________________________________________________________________________________________|\n");

    PressEnter();
}
void Edit_Menu_ui();
void edit_item_ui()
{
    ITEM itm;
    set_item_id(&itm);
    FILE *menufile = fopen("./data_files/menudata.dat", "rb+");
    char input_str[30];
    printf("Enter Item Name or ID: ");
    fgets(input_str, sizeof(input_str), stdin);
    remove_fgets_newline(input_str);
    fflush(stdin);
    int choice;
    int item_index = doesItemExistsinMenu(input_str);
    if (item_index < 0)
    {
        printf("\t\t! ITEM Does NOT EXIST !\n");
        edit_item_ui();
    }
    else
    {
        fseek(menufile, item_index * sizeof(ITEM), SEEK_SET);
        fread(&itm, sizeof(ITEM), 1, menufile);
        printf("\tCurrent details: \n");
        print_item_details(&itm);
        printf("\n");
        printf("\t\t\t\tWhat Do you want to Change: \n");
        printf("\t\t\t\t __________________________________________________________________\n");
        printf("\t\t\t\t|                                                                  |\n");
        printf("\t\t\t\t|         1. Name                       2. Category                |\n");
        printf("\t\t\t\t|         3. Subcategory                4. Timmings                |\n");
        printf("\t\t\t\t|         5. Veg / Non-Vag              6. Locality                |\n");
        printf("\t\t\t\t|         7. Prices                     8. Description             |\n");
        printf("\t\t\t\t|                                                                  |\n");
        printf("\t\t\t\t|                               9. ALL                             |\n");
        printf("\t\t\t\t|                                                                  |\n");
        printf("\t\t\t\t|                                         0. Back to Edit Menu     |\n");
        printf("\t\t\t\t|__________________________________________________________________|\n");
        printf("\n\t\t\t\tChoose an option [Enter its corresponding number] : ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice)
        {
        case 0:
            Edit_Menu_ui();
            break;
        case 1:
            printf("Enter NEW Item Name: ");
            fgets(itm.name, sizeof(itm.name), stdin);
            remove_fgets_newline(itm.name);
            fflush(stdin);
            break;
        case 2:
            printf("Enter NEW Item Category: ");
            fgets(itm.category, sizeof(itm.category), stdin);
            remove_fgets_newline(itm.category);
            fflush(stdin);
            break;
        case 3:
            printf("Enter Item SubCategory: ");
            fgets(itm.subcategory, sizeof(itm.subcategory), stdin);
            remove_fgets_newline(itm.subcategory);
            fflush(stdin);
            break;
        case 4:
            printf("Enter NEW Item Timming: ");
            fgets(itm.timing, sizeof(itm.timing), stdin);
            remove_fgets_newline(itm.timing);
            fflush(stdin);
            break;
        case 5:
            printf("Enter [1] -> for veg  OR [0] -> for non-veg : ");
            scanf("%d", &itm.veg);
            fflush(stdin);
            break;
        case 6:
            printf("Enter Item Locality: ");
            fgets(itm.locality, sizeof(itm.locality), stdin);
            remove_fgets_newline(itm.locality);
            fflush(stdin);
            break;
        case 7:
            printf("Enter Item Prices [small medium large]: ");
            scanf("%f %f %f", &itm.price_in_rupee[0], &itm.price_in_rupee[1], &itm.price_in_rupee[2]);
            fflush(stdin);
            break;
        case 8:
            printf("Enter Item Description: ");
            fgets(itm.description, sizeof(itm.description), stdin);
            remove_fgets_newline(itm.description);
            fflush(stdin);
            break;
        case 9:
            printf("Enter NEW Item Name: ");
            fgets(itm.name, sizeof(itm.name), stdin);
            remove_fgets_newline(itm.name);
            fflush(stdin);

            printf("Enter Item Timming: ");
            fgets(itm.timing, sizeof(itm.timing), stdin);
            remove_fgets_newline(itm.timing);
            fflush(stdin);

            printf("Enter Item Category: ");
            fgets(itm.category, sizeof(itm.category), stdin);
            remove_fgets_newline(itm.category);
            fflush(stdin);

            printf("Enter [1] -> for veg  OR [0] -> for non-veg : ");
            scanf("%d", &itm.veg);
            fflush(stdin);

            printf("Enter Item SubCategory: ");
            fgets(itm.subcategory, sizeof(itm.subcategory), stdin);
            remove_fgets_newline(itm.subcategory);
            fflush(stdin);

            printf("Enter Item Locality: ");
            fgets(itm.locality, sizeof(itm.locality), stdin);
            remove_fgets_newline(itm.locality);
            fflush(stdin);

            printf("Enter Item Prices [small medium large]: ");
            scanf("%f %f %f", &itm.price_in_rupee[0], &itm.price_in_rupee[1], &itm.price_in_rupee[2]);
            fflush(stdin);

            printf("Enter Item Description: ");
            fgets(itm.description, sizeof(itm.description), stdin);
            remove_fgets_newline(itm.description);
            fflush(stdin);

            break;
        default:
            Edit_Menu_ui();
            break;
        }

        itm.newline = '\n';
        fseek(menufile, item_index * sizeof(ITEM), SEEK_SET);
        fwrite(&itm, sizeof(ITEM), 1, menufile);

        PressEnter();
        printf("\n\t\tItem Changed.\n");
        Edit_Menu_ui();
    }
}
void remove_item_ui()
{
    char itm_name_or_id[30];
    printf("Enter Item name or id: ");
    fgets(itm_name_or_id, sizeof(itm_name_or_id), stdin);
    remove_fgets_newline(itm_name_or_id);
    fflush(stdin);
    remove_item_from_menu(itm_name_or_id);
}
void Edit_Menu_ui()
{
    printf("\n");
    int choice;
    printf("\t\t\t\t __________________________________________________________________\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|    1. Show Menu                    2. Add Item To Menu           |\n");
    printf("\t\t\t\t|    3. Update/Edit Item             4. Remove Item                |\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|                                         0. Back to Admin Menu    |\n");
    printf("\t\t\t\t|__________________________________________________________________|\n");
    printf("\n\t\t\t\tChoose an option [Enter its corresponding number] : ");
    scanf("%d", &choice);
    fflush(stdin);
    switch (choice)
    {
    case 0:
        adminmenu();
        break;
    case 1:
        showItemsMenu();
        Edit_Menu_ui();
        break;
    case 2:
        add_item_to_menu_ui();
        Edit_Menu_ui();
        break;
    case 3:
        edit_item_ui();
        Edit_Menu_ui();
        break;
    case 4:
        remove_item_ui();
        Edit_Menu_ui();
        break;
    default:
        printf("\n\t\t\t\t! Please Enter the \"Number of give option only\" !\n");
        Edit_Menu_ui();
        break;
    }
}
void adminmenu()
{
    int choice;

    printf("\n");
    printf("\t\t\t\t __________________________________________________________________\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|    1. Show Menu                    2. EDIT Menu                  |\n");
    printf("\t\t\t\t|    3. Show Bill History            4. Revenue                    |\n");
    printf("\t\t\t\t|    5. Employees Served Guests      6. Update PIN                 |\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|                                         0. Back to First Menu    |\n");
    printf("\t\t\t\t|__________________________________________________________________|\n");
    printf("\n\t\t\t\tChoose an option [Enter its corresponding number] : ");
    scanf("%d", &choice);
    fflush(stdin);
    switch (choice)
    {
    case 0:
        displaymenu1();
        break;
    case 1:
        showItemsMenu();
        adminmenu();
        break;
    case 2:
        Edit_Menu_ui();
        adminmenu();
        break;
    case 3:
        show_bill_history_ui();
        break;
    case 4:
        revenue_ui();
        break;
    case 5:
        emp_served_guest_ui();
        break;
    case 6:
        updatePin_ui();
        break;
    default:
        printf("\n\t\t\t\t! Please Enter the \"Number of give option only\" !\n");
        adminmenu();
    }
}
void add_item_to_menu_ui()
{
    ITEM itm;
    set_item_id(&itm);

    printf("Enter Item Name: ");
    fgets(itm.name, sizeof(itm.name), stdin);
    remove_fgets_newline(itm.name);
    fflush(stdin);
    if (doesItemExistsinMenu(itm.name) >= 0)
    {
        printf("\t\t! ITEM Already EXISTS !");
        Edit_Menu_ui();
    }
    else
    {

        printf("Enter Item Timming: ");
        fgets(itm.timing, sizeof(itm.timing), stdin);
        remove_fgets_newline(itm.timing);
        fflush(stdin);

        printf("Enter Item Category: ");
        fgets(itm.category, sizeof(itm.category), stdin);
        remove_fgets_newline(itm.category);
        fflush(stdin);

        printf("Enter [1] -> for veg  OR [0] -> for non-veg : ");
        scanf("%d", &itm.veg);
        fflush(stdin);

        printf("Enter Item SubCategory: ");
        fgets(itm.subcategory, sizeof(itm.subcategory), stdin);
        remove_fgets_newline(itm.subcategory);
        fflush(stdin);

        printf("Enter Item Locality: ");
        fgets(itm.locality, sizeof(itm.locality), stdin);
        remove_fgets_newline(itm.locality);
        fflush(stdin);

        printf("Enter Item Prices [small medium large]: ");
        scanf("%f %f %f", &itm.price_in_rupee[0], &itm.price_in_rupee[1], &itm.price_in_rupee[2]);
        fflush(stdin);

        printf("Enter Item Description: ");
        fgets(itm.description, sizeof(itm.description), stdin);
        remove_fgets_newline(itm.description);
        fflush(stdin);

        itm.newline = '\n';

        PressEnter();
        add_item_to_menu(&itm);
        printf("\n\t\tItem Added.\n");
        Edit_Menu_ui();
    }
}

void show_bill_history(int);
void show_bill_history_ui()
{
    int choice;

    printf("\n");
    printf("\t\t\t\t __________________________________________________________________\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|         1. Last Hour\'s                2. Past 5 Hours\'           |\n");
    printf("\t\t\t\t|         3. Past 24 Hours\'             4. Last week\'s             |\n");
    printf("\t\t\t\t|         5. Last Month                 6. Custom                  |\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|                                         0. Back to Admin Menu    |\n");
    printf("\t\t\t\t|__________________________________________________________________|\n");
    printf("\n\t\t\t\tChoose an option [Enter its corresponding number] :");
    scanf("%d", &choice);
    fflush(stdin);
    show_bill_history(choice);
}
void show_bill_history(int ch)
{
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int now_hour = local->tm_hour;
    FILE *billhis = open_this_years_billhis_file();
    BILL bb;
    int lmd;
    int limmon;
    switch (local->tm_mon)
    {
    case 1:
        lmd = 31;
        break;
    case 2:
        lmd = 31;
        break;
    case 3:
        lmd = 30;
        break;
    case 4:
        lmd = 31;
        break;
    case 5:
        lmd = 30;
        break;
    case 6:
        lmd = 31;
        break;
    case 7:
        lmd = 30;
        break;
    case 8:
        lmd = 31;
        break;
    case 9:
        lmd = 31;
        break;
    case 10:
        lmd = 30;
        break;
    case 11:
        lmd = 31;
        break;
    case 12:
        lmd = 30;
        break;

    default:
        break;
    }
    int limday;
    int custFromYear, custFromMonth, custFromDay, custToYear, custToMonth, custToDay;

    switch (ch)
    {
    case 0:
        adminmenu();
        break;
    case 1:
        printf("\n\t\tAll bills since around %d/%d/%d  %d:%d --", local->tm_mday, local->tm_mon, local->tm_year + 1900, local->tm_hour - 1, local->tm_min);
        while (fread(&bb, sizeof(BILL), 1, billhis))
        {
            if ((bb.billtime.tm_mon == (local->tm_mon)) && (bb.billtime.tm_mday == local->tm_mday) && (bb.billtime.tm_hour >= (local->tm_hour - 1)) && (bb.billtime.tm_min >= local->tm_min - 5))
            {
                print_bill(&bb);
                printf("\n");
            }
        }
        PressEnter();
        show_bill_history_ui();
        break;

    case 2:
        printf("\n\t\tAll bills since around %d/%d/%d  %d:%d --", local->tm_mday, local->tm_mon, local->tm_year + 1900, local->tm_hour - 5, local->tm_min);
        while (fread(&bb, sizeof(BILL), 1, billhis))
        {
            if ((bb.billtime.tm_mon == (local->tm_mon)) && (bb.billtime.tm_mday == local->tm_mday) && (bb.billtime.tm_hour >= (local->tm_hour - 5)) && (bb.billtime.tm_min >= local->tm_min - 5))
            {
                print_bill(&bb);
                printf("\n");
            }
        }
        PressEnter();
        show_bill_history_ui();
        break;

    case 3:

        limday = (local->tm_mday == 1) ? lmd : local->tm_mday - 1;
        limmon = (local->tm_mday == 1) ? local->tm_mon - 1 : local->tm_mon;
        printf("\n\t\tAll bills since around %d/%d/%d\t %d:%d --", limday, limmon, local->tm_year + 1900, local->tm_hour, local->tm_min);
        while (fread(&bb, sizeof(BILL), 1, billhis))
        {
            if (((bb.billtime.tm_mon == limmon) && (bb.billtime.tm_mday == limday)) || ((bb.billtime.tm_mon == local->tm_mon) && (bb.billtime.tm_mday == local->tm_mday)))
            {
                print_bill(&bb);
                printf("\n");
            }
        }
        PressEnter();
        show_bill_history_ui();
        break;
    case 4:
        limday = (local->tm_mday < 7) ? lmd : local->tm_mday;
        limmon = (local->tm_mday < 7) ? local->tm_mon - 1 : local->tm_mon;
        int dif = limday - 6;
        printf("\n\t\tAll bills since %d/%d/%d\t %d:%d --", dif, limmon, local->tm_year + 1900, local->tm_hour, local->tm_min);
        while (fread(&bb, sizeof(BILL), 1, billhis))
        {

            if (((bb.billtime.tm_mon >= limmon) && (bb.billtime.tm_mday >= dif)) || ((bb.billtime.tm_mon == local->tm_mon) && (bb.billtime.tm_mday <= local->tm_mday)))
            {
                print_bill(&bb);
                printf("\n");
            }
        }
        PressEnter();
        show_bill_history_ui();
        break;
    case 5:
        printf("\n\t\tAll bills since %d/%d/%d  %d:%d --", local->tm_mday, local->tm_mon - 1, local->tm_year + 1900, local->tm_hour - 5, local->tm_min);
        while (fread(&bb, sizeof(BILL), 1, billhis))
        {
            if (((bb.billtime.tm_mon == local->tm_mon - 1) && (bb.billtime.tm_mday >= local->tm_mday)) || ((bb.billtime.tm_mon == local->tm_mon) && (bb.billtime.tm_mday <= local->tm_mday)))
            {
                print_bill(&bb);
                printf("\n");
            }
        }
        PressEnter();
        show_bill_history_ui();
        break;
    case 6:
        printf("\n\t\t\t\t   From which date \n\t\t\t\tEnter in this format[dd mm yyyy]: ");
        scanf("%d %d %d", &custFromDay, &custFromMonth, &custFromYear);
        fflush(stdin);
        printf("\n\t\t\t\t   Till which date \n\t\t\t\tEnter in this format[dd mm yyyy]: ");
        scanf("%d %d %d", &custToDay, &custToMonth, &custToYear);
        fflush(stdin);
        FILE *custbillfile;
        for (int i = custFromYear; i <= custToYear; i++)
        {
            custbillfile = open_given_years_billhis_file(i);
            while (fread(&bb, sizeof(BILL), 1, custbillfile))
            {
                if (((bb.billtime.tm_mon > custFromMonth) && (bb.billtime.tm_mon < custToMonth)) || ((bb.billtime.tm_mon == custFromMonth) && (bb.billtime.tm_mday >= custFromDay)) || ((bb.billtime.tm_mon == custToMonth) && (bb.billtime.tm_mday <= custToDay)))
                {
                    print_bill(&bb);
                    printf("\n");
                }
            }
            fclose(custbillfile);
        }

        PressEnter();
        show_bill_history_ui();
    default:
        printf("\n\t\t\t\t! Please Enter the \"Number of give option only\" !\n");
        show_bill_history_ui();
        break;
    }
    fclose(billhis);
}
void revenue_ui()
{
    BILL bb;
    FILE *billhisfile = open_this_years_billhis_file();
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int lmd;
    switch (local->tm_mon)
    {
    case 1:
        lmd = 31;
        break;
    case 2:
        lmd = 31;
        break;
    case 3:
        lmd = 30;
        break;
    case 4:
        lmd = 31;
        break;
    case 5:
        lmd = 30;
        break;
    case 6:
        lmd = 31;
        break;
    case 7:
        lmd = 30;
        break;
    case 8:
        lmd = 31;
        break;
    case 9:
        lmd = 31;
        break;
    case 10:
        lmd = 30;
        break;
    case 11:
        lmd = 31;
        break;
    case 12:
        lmd = 30;
        break;

    default:
        break;
    }
    int choice;
    printf("\n");
    printf("\t\t\t\t __________________________________________________________________\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|    1. For Today                    2. For this week              |\n");
    printf("\t\t\t\t|    3. For this Month               4. For entire year            |\n");
    printf("\t\t\t\t|    5. Custom                                                     |\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|                                         0. Back to Admin Menu    |\n");
    printf("\t\t\t\t|__________________________________________________________________|\n");
    printf("\n\t\t\t\tChoose an option [Enter its corresponding number] : ");
    scanf("%d", &choice);
    fflush(stdin);
    float revenue = 0;
    int dif = (local->tm_mday < local->tm_wday) ? (local->tm_wday - local->tm_mday) : 0;
    int custFromYear, custFromMonth, custFromDay, custToYear, custToMonth, custToDay;
    switch (choice)
    {
    case 0:
        adminmenu();
        break;
    case 1:
        while (fread(&bb, sizeof(BILL), 1, billhisfile))
        {
            if (bb.billtime.tm_yday == local->tm_yday)
            {
                print_bill(&bb);
                revenue += gross_total_calc(&bb) + ((gross_total_calc(&bb)) * (bb.gst / 100));
            }
        }
        printf("\n\t\tToday's Revenue: %.2f\n", revenue);
        PressEnter();
        revenue_ui();
        break;
    case 2:

        while (fread(&bb, sizeof(BILL), 1, billhisfile))
        {
            if (local->tm_mday < local->tm_wday)
            {
                if (((bb.billtime.tm_mon == local->tm_mon - 1) && (bb.billtime.tm_wday > (lmd - dif))) || ((bb.billtime.tm_mon == local->tm_mon) && (bb.billtime.tm_mday <= local->tm_mday)))
                {
                    revenue += gross_total_calc(&bb) + ((gross_total_calc(&bb)) * (bb.gst / 100));
                }
            }
            else
            {
                if (bb.billtime.tm_mon == local->tm_mon && bb.billtime.tm_mday > (local->tm_mday - local->tm_wday))
                {
                    revenue += gross_total_calc(&bb) + ((gross_total_calc(&bb)) * (bb.gst / 100));
                }
            }
        }
        printf("\n\t\tThis Week's Revenue: %.2f\n", revenue);
        PressEnter();
        revenue_ui();
        break;
    case 3:
        while (fread(&bb, sizeof(BILL), 1, billhisfile))
        {
            if (bb.billtime.tm_mon == local->tm_mon)
            {
                revenue += gross_total_calc(&bb) + ((gross_total_calc(&bb)) * (bb.gst / 100));
            }
        }
        printf("\n\t\tThis Month's Revenue: %.2f\n", revenue);
        PressEnter();
        revenue_ui();
        break;
    case 4:
        while (fread(&bb, sizeof(BILL), 1, billhisfile))
        {
            revenue += gross_total_calc(&bb) + ((gross_total_calc(&bb)) * (bb.gst / 100));
        }
        printf("\n\t\tThis Year's Revenue: %.2f\n", revenue);
        PressEnter();
        revenue_ui();
        break;
    case 5:
        printf("\n\t\t\t\t   From which date \n\t\t\t\tEnter in this format[dd mm yyyy]: ");
        scanf("%d %d %d", &custFromDay, &custFromMonth, &custFromYear);
        fflush(stdin);
        printf("\n\t\t\t\t   Till which date \n\t\t\t\tEnter in this format[dd mm yyyy]: ");
        scanf("%d %d %d", &custToDay, &custToMonth, &custToYear);
        fflush(stdin);
        FILE *custbillfile;
        for (int i = custFromYear; i <= custToYear; i++)
        {
            custbillfile = open_given_years_billhis_file(i);
            while (fread(&bb, sizeof(BILL), 1, custbillfile))
            {
                if (((bb.billtime.tm_mon > custFromMonth) && (bb.billtime.tm_mon < custToMonth)) || ((bb.billtime.tm_mon == custFromMonth) && (bb.billtime.tm_mday >= custFromDay)) || ((bb.billtime.tm_mon == custToMonth) && (bb.billtime.tm_mday <= custToDay)))
                {
                    revenue += gross_total_calc(&bb) + ((gross_total_calc(&bb)) * (bb.gst / 100));
                }
            }
            fclose(custbillfile);
        }
        printf("\n\t\tTotal Revenue From %d:%d:%d  to %d:%d:%d   ---    Rs. %.2f\n", custFromDay, custFromMonth, custFromYear, custToDay, custToMonth, custToYear, revenue);
        PressEnter();
        revenue_ui();
        break;
    default:
        printf("\n\t\t\t\tChoose an option [Enter its corresponding number] :");
        revenue_ui();
        break;
    }

    fclose(billhisfile);
}

void emp_served_guest(int);
void emp_served_guest_ui()
{
    int choice;
    printf("\n");
    printf("\t\t\t\t __________________________________________________________________\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|    1. For One Employee             2. For One Customer           |\n");
    printf("\t\t\t\t|                                                                  |\n");
    printf("\t\t\t\t|                                         0. Back to Admin Menu    |\n");
    printf("\t\t\t\t|__________________________________________________________________|\n");
    printf("\n\t\t\t\tChoose an option [Enter its corresponding number] : ");
    scanf("%d", &choice);
    fflush(stdin);
    emp_served_guest(choice);
}

void emp_served_guest(int ch)
{
    FILE *billhisfile = open_this_years_billhis_file();
    BILL bb;
    char empname[20];
    char customername[20];
    int found = 0;
    switch (ch)
    {
    case 0:
        adminmenu();
        break;
    case 1:
        printf("Enter Employee's name: ");
        fgets(empname, sizeof(empname), stdin);
        remove_fgets_newline(empname);
        fflush(stdin);
        printf("\n\t\t\t\t ________________________________________\n");
        printf("\t\t\t\t\t|               %s              \n", empname);
        printf("\t\t\t\t\t|__________________________________________|\n");
        while (fread(&bb, sizeof(BILL), 1, billhisfile))
        {
            if (strcmp(empname, bb.serverName) == 0)
            {
                found++;
                printf("\t\t\t\t|     %d. %s\n", found, bb.customerName);
            }
        }
        if (found == 0)
        {
            printf("\n! No Match Found !\n");
        }
        else
        {

            printf("\n\t\t\t\t\t %d Customer served by %s\n", found, empname);
        }
        PressEnter();
        emp_served_guest_ui();
        break;
    case 2:
        printf("Enter Customer's name: ");
        fgets(customername, sizeof(customername), stdin);
        remove_fgets_newline(customername);
        fflush(stdin);
        printf("\n\t\t\t\t ________________________________________\n");
        printf("\t\t\t\t\t|               %s              \n", customername);
        printf("\t\t\t\t\t|__________________________________________|\n");
        found = 0;
        while (fread(&bb, sizeof(BILL), 1, billhisfile))
        {
            if (strcmp(customername, bb.customerName) == 0)
            {
                found++;
                printf("\t\t\t\t|     %d. %s\n", found, bb.serverName);
            }
        }
        if (found == 0)
        {
            printf("\n! No Match Found !\n");
        }
        else
        {

            printf("\n\t\t\t\t\t %d Employees served %s\n", found, customername);
        }
        PressEnter();
        emp_served_guest_ui();
        break;
    default:
        printf("\n\t\t\t\t! Please Enter the \"Number of give option only\" !\n");
        emp_served_guest_ui();
        break;
    }
    fclose(billhisfile);
}
