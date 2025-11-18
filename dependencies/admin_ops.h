#include <stdio.h>

#include <time.h>
#include "customFunc.h"
// const float c_gst = 5.6;
// ------------TIME------------------------
// time_t now;
// time(&now);
// mytime = localtime(&now);

//----------------PIN---------------------PIN---------------------PIN---------------------PIN-------
typedef struct
{
    int pin;
} PIN;
int pintAuth(int spin)
{
    PIN p;
    FILE *pinfile = fopen("./data_files/PIN.dat", "rb");
    fread(&p, sizeof(PIN), 1, pinfile);
    int pin = p.pin;
    fclose(pinfile);
    if (pin == spin)
    {
        return 1;
    }
    else
    {
    }
    return 0;
}
void updatePin(int spin)
{
    PIN p = {spin};
    FILE *pinfile = fopen("./data_files/PIN.dat", "wb");
    fwrite(&p, sizeof(PIN), 1, pinfile);
    fclose(pinfile);
}

//-------------FOOD MENU-------------FOOD MENU-------------FOOD MENU-------------FOOD MENU-------------FOOD MENU---------------

typedef struct
{
    char id[5];
    char name[25];
    char timing[20];      // breakfast, lunch, dinner, anytime
    char category[15];    // appetizers, maincourse ,desserts, beverages
    char subcategory[15]; //
    int veg;              // [0]-> for non-veg, [1]-> for veg
    char locality[15];
    float price_in_rupee[3]; // {small, medium, large}
    char description[100];
    char newline;
} ITEM;

void set_item_id(ITEM *sitm)
{
    ITEM itm;
    FILE *mdfile = fopen("./data_files/menudata.dat", "rb");
    int found = 0;
    while (fread(&itm, sizeof(ITEM), 1, mdfile))
    {
        found = 1;
    }
    if (found == 0)
    {
        strcpy(sitm->id, "0001");
    }
    else
    {
        int num = string_to_int(itm.id);
        num++;
        int_to_item_id(num, sitm->id);
    }
    fclose(mdfile);
}
void add_item_to_menu(ITEM *d)
{
    FILE *menufile = fopen("./data_files/menudata.dat", "ab");
    fwrite(d, sizeof(ITEM), 1, menufile);
    fclose(menufile);
}

void remove_item_from_menu(char *itm_name_or_id)
{
    FILE *originalfile = fopen("./data_files/menudata.dat", "rb");
    FILE *tempfile = fopen("./data_files/tempdata.dat", "wb");
    ITEM itm;
    int found = 0;
    while (fread(&itm, sizeof(ITEM), 1, originalfile))
    {
        if (strcmp_ig_case(itm.name, itm_name_or_id) == 0 || strcmp_ig_case(itm.id, itm_name_or_id) == 0)
        {
            found = 1;
            continue;
        }
        fwrite(&itm, sizeof(ITEM), 1, tempfile);
    }
    remove("./data_files/menudata.dat");
    rename("./data_files/tempdata.dat", "./data_files/menudata.dat");
    if (found == 0)
    {
        printf("\n\t! Item Not Found !\n");
    }
    else
    {
        printf("\n\t! Item REMOVED !\n");
    }
    fclose(originalfile);
    fclose(tempfile);
}
int doesItemExistsinMenu(char *item_name_OR_id)
{
    FILE *menufile = fopen("./data_files/menudata.dat", "rb");
    ITEM d;
    int r = 0;
    while (fread(&d, sizeof(ITEM), 1, menufile))
    {
        if ((strcmp_ig_case(item_name_OR_id, d.name) == 0) || (strcmp_ig_case(item_name_OR_id, d.id) == 0))
        {
            fclose(menufile);
            return r;
        }
        r++;
    }
    fclose(menufile);
    return -1;
}
void print_item_details(ITEM *itm)
{
    printf("ID: %s\t\t", itm->id);
    printf("Name: %s\n", itm->name);
    printf("Timings: %s\t\t", itm->timing);
    printf("Category: %s\n", itm->category);
    printf("Subcategory: %s\t\t", itm->subcategory);
    printf("Veg / Non-veg: ");
    if (itm->veg == 1)
    {
        printf("Veg\n");
    }
    else
    {
        printf("Non-Veg\n");
    }

    printf("Locality: %s\n", itm->locality);
    printf("Prices: ");
    for (int i = 0; i < 3; i++)
    {
        if (itm->price_in_rupee[i] != 0)
        {
            printf("%f    ", itm->price_in_rupee[i]);
        }
    }

    printf("\nDescription: %s\n", itm->description);
}
int read_item_from_menu_by_id(char sid[5], ITEM *d)
{
    FILE *menufile = fopen("./data_files/menudata.dat", "rb");
    while (fread(d, sizeof(ITEM), 1, menufile))
    {
        if (strcmp(sid, d->id) == 0)
        {
            fclose(menufile);
            return 1;
        }
    }
    fclose(menufile);
    return 0;
}
int read_item_from_menu_by_name(char sname[20], ITEM *d)
{
    FILE *menufile = fopen("./data_files/menudata.dat", "rb");
    while (fread(d, sizeof(ITEM), 1, menufile))
    {
        if (strcmp_ig_case(sname, d->name) == 0)
        {
            fclose(menufile);
            return 1;
        }
    }
    fclose(menufile);
    return 0;
}

//-----------BILL---------------------BILL----------------------BILL--------------------------------BILL---------------------

typedef struct
{
    char invoice_no[12];
    char serverName[20];
    char customerName[20];
    char customerContact[11];
    struct tm billtime;
    char table_num[4];
    char itemList[20][20];
    int itemListCount;
    int quantities[20];
    int size[20]; // 0->no size, 1->small, 2->medium, 3->large
    char mop[10]; // card, UPI, cash
    float gst;

} BILL;
FILE *open_this_years_billhis_file()
{
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int now_hour = local->tm_hour;
    char fyname[5];
    int_to_str((local->tm_year + 1900), fyname);
    char fname[50] = "./data_files/billHistories/billHistory";
    strcat(fname, fyname);
    strcat(fname, ".dat");
    FILE *billhis = fopen(fname, "rb");
    return billhis;
}

FILE *open_given_years_billhis_file(int year)
{
    char fyname[5];
    int_to_str((year), fyname);
    char fname[50] = "./data_files/billHistories/billHistory";
    strcat(fname, fyname);
    strcat(fname, ".dat");
    FILE *billhis = fopen(fname, "rb");
    return billhis;
}
void auto_set_invoice_num(BILL *bb)
{
    char invn[12];
    if ((bb->billtime.tm_mon % 10) == 0)
    {
        invn[0] = '1';
    }
    else
    {
        invn[0] = ((char)((bb->billtime.tm_mon % 10) + 48));
    }

    invn[1] = ((char)((bb->billtime.tm_sec % 10) + 48));
    for (int i = 2; i < 7; i++)
    {
        invn[i] = bb->customerContact[i];
    }

    // str_slice_cat(invn, bb->customerContact, 2, 5);
    // str_slice_cat(invn, bb->table_num, 1, 1)
    invn[7] = bb->table_num[1];
    invn[8] = ((char)((bb->billtime.tm_hour % 10) + 48));
    invn[9] = ((char)((bb->billtime.tm_mday % 10) + 48));
    invn[10] = ((char)(bb->billtime.tm_wday + 48));
    invn[11] = '\0';
    strcpy(bb->invoice_no, invn);
}
void add_to_billHistory(BILL *sbill)
{
    char fyname[5];
    int_to_str((sbill->billtime.tm_year + 1900), fyname);
    char fname[50] = "./data_files/billHistories/billHistory";
    strcat(fname, fyname);
    strcat(fname, ".dat");
    FILE *billfile = fopen(fname, "ab");
    fwrite(sbill, sizeof(BILL), 1, billfile);
    fclose(billfile);
}

float gross_total_calc(BILL *bb)
{
    float tot = 0;
    ITEM itm;
    int s;
    for (int i = 0; i < bb->itemListCount; i++)
    {
        s = bb->size[i] - 1;
        s = (s < 0) ? 0 : s;
        read_item_from_menu_by_name(bb->itemList[i], &itm);
        tot += (itm.price_in_rupee[s] * bb->quantities[i]);
    }
    return tot;
}
void retrieve_from_billHistory(BILL *sbill)
{
    FILE *billfile = fopen("./data_files/billHistory", "rb");
    fread(sbill, sizeof(BILL), 1, billfile);
    fclose(billfile);
}
int search_bill_by_customerName(char *custName, BILL *bb)
{
    FILE *billfile = fopen("./data_files/billHistory", "rb");
    while (fread(bb, sizeof(BILL), 1, billfile))
    {
        if (strcmp_ig_case(custName, bb->customerName) == 0)
        {
            fclose(billfile);
            return 1;
        }
    }
    fclose(billfile);
    return 0;
}
int search_bill_by_serverName(char *servername, BILL *bb)
{
    FILE *billfile = fopen("./data_files/billHistory", "rb");
    while (fread(bb, sizeof(BILL), 1, billfile))
    {
        if (strcmp_ig_case(servername, bb->serverName) == 0)
        {
            fclose(billfile);
            return 1;
        }
    }
    fclose(billfile);
    return 0;
}
