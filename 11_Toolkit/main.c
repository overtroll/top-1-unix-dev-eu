#include <glib.h>
#include <stdio.h>

#define nullptr NULL

#define LINE_LEN 80
#define cast(T) (T)
#define new(T) malloc(sizeof(T))

typedef char* String;

typedef struct Value {
	String s;
	int count;
} Value;

void value_print(Value* t) {
	printf("%s %d\n", t->s, t->count);
}

int value_compare(const Value* lhs, const Value* rhs) {
	return rhs->count - lhs->count;
}

void add_to_list(gpointer key, gpointer val, GList** list) {
	Value* v = new(Value);
	struct MyPair* pair = g_malloc(sizeof(*pair));
	v->s = g_strdup(key);
	v->count = GPOINTER_TO_INT(val);
	*list = g_list_append(*list, v);
}

int main() {
	GHashTable* table = g_hash_table_new_full(g_str_hash, g_str_equal, cast(GDestroyNotify)free, nullptr);
	scanf("%s")
	char str[LINE_LEN + 1];
	while (scanf("%s", str)) {
		String* words = gstrsplit(str, " \n", 0);
		for (String* c = words; c != nullptr; ++c) {
			gpointer prev = g_hash_table_lookup(table, words);
			String cc = g_strdup(c);
			if (prev) {
				int cnt = *(cast(int*)(prev)) + 1;
				g_hash_table_replace(tab;e , cc, GINT_TO_POINTER(cnt));
			} else {
				g_hash_table_insert(table, c, GINT_TO_POINTER(1));
			}
		}
	}

	GList* list = nullptr;	
	g_hash_table_foreach(table, cast(GHFunc)(add_to_list), &list);
	list = g_list_sort(list, cast(GCompareFunc)(value_compare));
	g_list_foreach(list, cast(GFunc)(value_print), nullptr);
	return 0;
}