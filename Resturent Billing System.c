# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <conio.h>
# include <time.h>

# define get_value_from_user(kindly, variable_name, is_flush_needed) \
	printf("%s: ", kindly); \
	if( __builtin_types_compatible_p(typeof(* variable_name), char) ) { \
	  scanf("%c", variable_name); \
	}else if( __builtin_types_compatible_p(typeof(* variable_name), int) ) { \
	  scanf("%d", variable_name); \
	}else if( __builtin_types_compatible_p(typeof(* variable_name), float) ){ \
	  scanf("%f", variable_name); \
	}else{ \
	  if(is_flush_needed == 1) getchar(); \
	  gets((char *) variable_name); \
	}

typedef struct food_item{
	char food_name[31];
	int quantity;
	float price_per_unit;
} food_item;

typedef struct food_items{
	food_item * food_item;
	struct food_items * next_food_item;
} food_items;

typedef struct invoice{
	char customer_name[31];
	char sold_time[31];
	food_items * list_of_food;
	float grand_total;
} invoice;

typedef struct invoices{
	invoice * single_invoice;
	struct invoices * next_invoice;
} invoices;



food_item * init_food_item();
food_items * init_food_items();
food_item * insertion_food_item(
	char food_name[31],
	int quantity,
	float price_per_unit
);
food_items * insertion_food_items(
	food_items * the_main_list,
	food_item * new_item_info
);
void display(
	food_items * the_main_list
);
float grandTotal(
	food_items * the_main_list
);
void header(char header_text[]);
void you_may_continue(char continue_text[]);
void showing_info(char info_text[]);
invoices * generete_invoice(invoices * the_main_list);

char * CurrentTime();


invoice * init_invoice(){
	invoice * blank = (invoice *) malloc(sizeof(invoice));
	return blank;
}

invoices * init_invoices(){
	invoices * blank = (invoices *) malloc(sizeof(invoices));
	blank -> next_invoice = NULL;
	return blank;
}

invoice * insertion_invoice(
	char customer_name[31],
	food_items * list_of_food,
	float grand_total
){
	invoice * an_item = init_invoice();
	strcpy(an_item -> customer_name, customer_name);
	strcpy(an_item -> sold_time, CurrentTime());
	an_item -> list_of_food = list_of_food;
	an_item -> grand_total = grand_total;

	return an_item;
}

invoices * insertion_invoices(
	invoices * the_main_list,
	invoice * new_item_info
){
	invoices * new_item = init_invoices();
	new_item -> single_invoice = new_item_info;

	invoices * temp = init_invoices();
	temp = the_main_list;

	if(temp == NULL){
		the_main_list = new_item;
	}else{
		for(;temp -> next_invoice != NULL; temp = temp -> next_invoice){}
		temp -> next_invoice = new_item;
	}

	return the_main_list;
}

void show_single_invoice(
	invoice * single_invoice_info
){
	invoice * temp = init_invoice();
	temp = single_invoice_info;

    printf(
        "name: %s\n"
        "date: %s\n",
        temp -> customer_name,
        temp -> sold_time
	);
	display(temp -> list_of_food);

	printf("GrandTotal: %.2f\n", grandTotal((temp -> list_of_food)));

}

invoices * show_all_invoices(
	invoices * the_main_list
){
    header("show all invoices");
	invoices * temp = init_invoices();
	temp = the_main_list;

	if(temp == NULL){
	}else{
		for(;temp != NULL; temp = temp -> next_invoice){
			show_single_invoice(temp -> single_invoice);
			printf("\n=-=-=-=-=-=-=-=-=-=-=-=\n");
		}
	}

	return the_main_list;
}

char * CurrentTime(){
	time_t time_function = time(NULL);
    struct tm *time_pointer = localtime(&time_function);

    char temp[51];
    strftime(temp, sizeof(temp), "%c", time_pointer);

    char * current_time = (char *) malloc(sizeof(char));
    strcpy(current_time, temp);

    return (char *) current_time;
}

food_item * init_food_item(){
	food_item * blank = (food_item *) malloc(sizeof(food_item));
	return blank;
}

food_items * init_food_items(){
	food_items * blank = (food_items *) malloc(sizeof(food_items));
	blank -> next_food_item = NULL;
	return blank;
}

food_item * insertion_food_item(
	char food_name[31],
	int quantity,
	float price_per_unit
){
	food_item * an_item = init_food_item();
	strcpy(an_item -> food_name, food_name);
	an_item -> quantity =  quantity;
	an_item -> price_per_unit =  price_per_unit;

	return an_item;
}

food_items * insertion_food_items(
	food_items * the_main_list,
	food_item * new_item_info
){
	food_items * new_item = init_food_items();
	new_item -> food_item = new_item_info;

	food_items * temp = init_food_items();
	temp = the_main_list;

	if(temp == NULL){
		the_main_list = new_item;
	}else{
		for(;temp -> next_food_item != NULL; temp = temp -> next_food_item){}
		temp -> next_food_item = new_item;
	}

	return the_main_list;
}

void display(
	food_items * the_main_list
){
	food_items * temp = init_food_items();
	printf(
		"\n"
		"------------------\n\n"
	);
	for(temp = the_main_list; temp != NULL; temp = temp -> next_food_item){
		printf(
			"foodname\t: %s\n"
			"food quantity\t: %d\n"
			"unit price\t: %.2f\n"
			"total price\t: %.2f\n",
			temp -> food_item -> food_name,
			temp -> food_item -> quantity,
			temp -> food_item -> price_per_unit,
			temp -> food_item -> quantity * temp -> food_item -> price_per_unit
		);
		printf(
			"\n"
			"------------------\n\n"
		);
	}
}

float grandTotal(
	food_items * the_main_list
){
	float grand_total = 0;
	food_items * temp = init_food_items();
	for(temp = the_main_list; temp != NULL; temp = temp -> next_food_item){
		grand_total += temp -> food_item -> quantity * temp -> food_item -> price_per_unit;
	}
	return grand_total;
}

void header(char header_text[]){
	system("cls");
	printf(
		"\n"
		"---------------------\n"
		" %s\n"
		"---------------------\n\n",
		header_text
	);
}

void you_may_continue(char continue_text[]){
	printf("\n%s", continue_text);
	getch();
	system("cls");
}


void showing_info(char info_text[]){
	printf("!! %s\n", info_text);
}

invoices * generete_invoice(invoices * the_main_list){
    header("generate invoice");
    char customer_name[31];
    int items;

    get_value_from_user("customer name ", &customer_name, 1);
    get_value_from_user("items ", &items, 0);
    printf("\n");

    food_items * food_items_for_invoice = NULL;
    for(int pompom = 1; pompom <= items; pompom++){
        char food_name[31];
        int quantity;
        float price_per_unit;
        get_value_from_user("food name ", &food_name, 1);
        get_value_from_user("quantity ", &quantity, 0);
        get_value_from_user("price ", &price_per_unit, 0);
        food_items_for_invoice = insertion_food_items(
            food_items_for_invoice,
            insertion_food_item(
                food_name,
                quantity,
                price_per_unit
            )
        );
        printf("\n");
    }

    invoice * just_created_invoice = insertion_invoice(
        customer_name,
        food_items_for_invoice,
        grandTotal(food_items_for_invoice)
    );
    header("just created invoice");
    show_single_invoice(just_created_invoice);

    the_main_list = insertion_invoices(
        the_main_list,
        just_created_invoice
    );

    return the_main_list;
}

invoices * dashboard(invoices * the_main_list){
	header("dashboard");
	printf(
		"\t1. Generate Invoice\n"
		"\t2. Show All Invoice\n"
		"\t3. exit\n"
	);
	int option;
	get_value_from_user("option ", &option, 0);

	printf("\n");

    if(option == 1){
        the_main_list = generete_invoice(the_main_list);
    }else if(option == 2){
        show_all_invoices(the_main_list);
    }else{
        header("Thank you");
        showing_info("exiting from the project with respect 100%... 100% nigga certified");
        exit(0);
    }

    you_may_continue("continue..");

    dashboard(the_main_list);

    return the_main_list;
}

int main(){

    invoices * the_main_list = NULL;
	dashboard(the_main_list);


	return 0;
}
