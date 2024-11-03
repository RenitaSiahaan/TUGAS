#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Stack {
    struct Node *top;
    int count;
};

struct Stack* createStack() {
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

int isEmpty(struct Stack *stack) {
    return (stack->top == NULL);
}

int push(struct Stack *stack, int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return 0;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
    return 1;
}

int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    struct Node *temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->count--;
    return data;
}

int peek(struct Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->top->data;
}

int size(struct Stack *stack) {
    return stack->count;
}

void clear(struct Stack *stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

void freeStack(struct Stack *stack) {
    clear(stack);
    free(stack);
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("4. Size\n");
    printf("5. Clear\n");
    printf("6. Keluar\n");
}

int main() {
    struct Stack *stack = createStack();
    int choice, value;

    while (1) {
        displayMenu();
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nilai untuk ditambahkan ke stack: ");
                scanf("%d", &value);
                if (push(stack, value)) {
                    printf("%d berhasil ditambahkan ke stack\n", value);
                } else {
                    printf("Gagal menambahkan %d ke stack\n", value);
                }
                break;

            case 2:
                value = pop(stack);
                if (value != -1) {
                    printf("%d berhasil dihapus dari stack\n", value);
                } else {
                    printf("Stack kosong, tidak dapat menghapus\n");
                }
                break;

            case 3:
                value = peek(stack);
                if (value != -1) {
                    printf("Elemen teratas adalah %d\n", value);
                } else {
                    printf("Stack kosong\n");
                }
                break;

            case 4:
                printf("Ukuran stack adalah %d\n", size(stack));
                break;

            case 5:
                clear(stack);
                printf("Stack telah dibersihkan\n");
                break;

            case 6:
                freeStack(stack);
                printf("Keluar dari program\n");
                return 0;

            default:
                printf("Pilihan tidak valid, silakan coba lagi\n");
        }
    }

    return 0;
}
