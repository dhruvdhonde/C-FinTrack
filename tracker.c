#include <stdio.h>
Transaction *tx = &list->items[i];
if (tx->type == INCOME) total_income += tx->amount;
else total_expense += tx->amount;
}
double balance = total_income - total_expense;
printf("Total income : %.2f\n", total_income);
printf("Total expense: %.2f\n", total_expense);
printf("Balance : %.2f\n", balance);
}


// Simple filter by month (YYYY-MM)
static void monthly_summary(TxList *list) {
char buf[BUF]; printf("Enter month (YYYY-MM), empty = all: "); if (!fgets(buf, sizeof(buf), stdin)) return; trim(buf);
const char *prefix = (buf[0] == 0) ? NULL : buf;
double inc = 0.0, exp = 0.0;
for (size_t i = 0; i < list->count; ++i) {
Transaction *tx = &list->items[i];
if (prefix) {
if (strncmp(tx->date, prefix, 7) != 0) continue;
}
if (tx->type == INCOME) inc += tx->amount; else exp += tx->amount;
}
printf("For %s:\n", (prefix?prefix:"ALL"));
printf(" Income : %.2f\n", inc);
printf(" Expense: %.2f\n", exp);
printf(" Net : %.2f\n", inc - exp);
}


static void remove_transaction(TxList *list) {
char buf[BUF]; printf("Enter transaction id to remove: "); if (!fgets(buf, sizeof(buf), stdin)) return; int id = atoi(buf);
size_t i; for (i = 0; i < list->count; ++i) if (list->items[i].id == id) break;
if (i == list->count) { puts("Not found."); return; }
// shift left
for (size_t j = i+1; j < list->count; ++j) list->items[j-1] = list->items[j];
list->count--;
if (!save_transactions(list)) puts("Warning: failed to save to disk."); else puts("Transaction removed and saved.");
}


static void print_help(void) {
puts("Commands:");
puts(" 1 - List all transactions");
puts(" 2 - Add transaction");
puts(" 3 - Summary (totals)");
puts(" 4 - Monthly summary (enter YYYY-MM)");
puts(" 5 - Remove transaction by id");
puts(" 6 - Export to CSV (same file overwritten)");
puts(" 0 - Exit");
}


int main(void) {
TxList list; txlist_init(&list);
if (!load_transactions(&list)) { puts("Failed to load transactions file."); }
puts("Personal Finance Tracker - single-file C");
print_help();
char buf[BUF];
while (1) {
printf("\nEnter command (h for help): ");
if (!fgets(buf, sizeof(buf), stdin)) break; trim(buf);
if (buf[0] == 'h' || buf[0] == 'H') { print_help(); continue; }
int cmd = atoi(buf);
switch (cmd) {
case 0: puts("Exiting..."); txlist_free(&list); return 0;
case 1: list_all(&list); break;
case 2: add_transaction(&list); break;
case 3: summary(&list); break;
case 4: monthly_summary(&list); break;
case 5: remove_transaction(&list); break;
case 6: if (save_transactions(&list)) puts("Exported to " CSV_FILE); else puts("Export failed"); break;
default: puts("Unknown command. Enter 'h' for help."); break;
}
}
txlist_free(&list);
return 0;
}
