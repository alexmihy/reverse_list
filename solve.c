#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

/*
 * Определение структуры для задания списков
 * */
typedef struct List 
{
    int value;
    struct List *next;
} List;

/*
 * Данная функция печатает список в обратном порядке при помощи рекурсии.  
 * Не изменяет исходный список. Легкая реализация. 
 * Время выполения O(n), где n - длина списка
 * Требует O(n) дополнительной памяти на стеке, т.к. рекурсия не хвостовая.
 * Минус: на больших списках возможно переполнение стека. 
 * */
void reverse_print_recursive(const List *head) 
{
    if (head == NULL) 
        return;

    reverse_print_recursive(head->next);
    printf("%d\n", head->value);
}

/*
 * Данная функция печатает список в обратном порядке без помощи рекурсии. 
 * Не изменяет исходный список. По сути метод - развернутая рекурсия. 
 * Время выполнения O(n), требует O(n) дополнительной памяти
 * Минус: необходимость дополнительной памяти.
 * */
void reverse_print_wo_recursion(const List *head) 
{
    const List *cur;
    int i, p, len, *buf = NULL;

    for (len = 0, cur = head; cur != NULL; cur = cur->next, len++);

    p = 0;
    buf = (int*)malloc(len * sizeof(*buf));

    while (head != NULL) {
        buf[p++] = head->value;
        head = head->next;
    }

    for (i = p - 1; i >= 0; i--)
        printf("%d\n", buf[i]);

    free((void*)buf);
}

/*
 * Вспомогательная функция. Разворачивает однонаправленный список.
 * */
List* reverse_list(List *head) 
{
    List *prev = NULL, *next;

    while (head != NULL) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}

/*
 * Данная функция в ходе своей работы изменяет исходный список, после чего 
 * возвращает его в начальное состояние. 
 * При помощи функции reverse_list() разворачиваем список, печатаем, затем
 * разворачиваем обратно.
 * Не требует дополнительной памяти. Время выполнения O(n)
 * Минусы: изменяет список в ходе работы.
 * */
void reverse_print_with_changes(List *head)
{
    List *p;

    head = reverse_list(head);

    for (p = head; p != NULL; p = p->next)
        printf("%d\n", p->value);

    head = reverse_list(head);
}

int main(int argc, char **argv) 
{
    int val;
    FILE *f = fopen("in.txt", "r");
    List *head = NULL, *last = NULL, *cur;
    
    if (f == NULL) {
        printf("Error: fopen: (%s)\n", strerror(errno));
        return 1;
    }

    while (fscanf(f, "%d", &val) > 0) {
        List *cur = (List*)malloc(sizeof(*cur));
        cur->value = val;
        cur->next = NULL;

        if (head == NULL) {
            head = last =  cur;
        } else {
            last->next = cur;
            last = cur; 
        }
    }

    printf("LIST:\n");
    for (cur = head; cur != NULL; cur = cur->next)
        printf("%d\n", cur->value);

    printf("RECURSIVE REVERSED LIST:\n");
    reverse_print_recursive(head);
    printf("REVERSED LIST WITHOUT RECURSION:\n");
    reverse_print_wo_recursion(head);
    printf("REVERSED LIST WITH REVERSE OPERATION:\n");
    reverse_print_with_changes(head);

    return 0;
}