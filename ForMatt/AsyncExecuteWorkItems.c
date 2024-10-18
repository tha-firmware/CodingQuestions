#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define INDEX_SIZE  100

typedef struct WORK_ITEM {
    int index;
} WORK_ITEM;

WORK_ITEM *queue[INDEX_SIZE] = {0};
int qIndex = 0;

HANDLE qSem;
HANDLE hThreadExecutionWork[INDEX_SIZE];
int threadCount = 0;

void InitializeWorkItem(WORK_ITEM* pItem, int Index);
DWORD WINAPI ExecuteWorkItem(LPVOID lPtr);
DWORD WINAPI CheckQueueIndexThread(LPVOID lPtr);
HANDLE Init(void);
int CleanUpThreads(HANDLE *hThread);

/*
Name: InitializeWorkItem

Description: 
Used to populate the Work Item structure and placing it in the 
queue for it to be dequeed by execution thread.
*/
void InitializeWorkItem (WORK_ITEM* pItem, int Index) {
    if (pItem != NULL) {
        pItem->index = Index;

        WaitForSingleObject(qSem, INFINITE);
        queue[qIndex++] = pItem;
        ReleaseSemaphore(qSem, 1, NULL);
    }
}

/*
Name: ExecuteWorkItem

Description: 
As the name suggest, this execute the work item by
printing it. It execute in it's own thread and it 
free the memory that was allocated in heap.

Return: 1 - invalid pointer, 
        0 - valid pointer.
*/
DWORD WINAPI ExecuteWorkItem(LPVOID pItem) {
    DWORD ret = 1;

    if (pItem != NULL) {
        printf("index: %i\n", ((WORK_ITEM *)pItem)->index);

        free(pItem); //Free up heap memory after use

        ret = 0;
    }
    return ret; 
}

/*
Name: CheckQueueIndexThread

Description: 
This is thread that checks if the queue has an entry. 
if it has it will dequeue and pass the worker item to 
a seperate thread to be lated execute in that thread.

Return: 1 - thread failed to create thread, 
        0 - finished creating all possible threads.
*/
DWORD WINAPI CheckQueueIndexThread(LPVOID lPtr) {
    DWORD ret = 0;
    void *pItem = NULL;

    while (threadCount < INDEX_SIZE) {
        if (qIndex) {
            WaitForSingleObject(qSem, INFINITE);
            pItem = (void *)queue[--qIndex];
            ReleaseSemaphore(qSem, 1, NULL);

            hThreadExecutionWork[threadCount] = CreateThread(
                                                NULL, //default security
                                                0, //default stack size
                                                ExecuteWorkItem, //LPTHREAD_START_ROUTINE
                                                pItem, //argument to threadFunc
                                                0, //creation flags
                                                0
                                                );
            // if thread failed to create.
            if (hThreadExecutionWork[threadCount++] == NULL) {
                free(pItem);
                threadCount--;
                ret = 1;
                break;
            }
        }
    }
    return ret;
}

/*
Name: Init

Description: 
Create semaphores for synchronization of the queue and
create thread that will check the queue for execution. 

Return: NULL - thread failed to create semaphore or thread. 
        Thread handler - successfully created semaphore and thread.
*/
HANDLE Init(void) {
    HANDLE hThread = NULL;

    qSem = CreateSemaphore( 
        NULL,           // default security attributes
        1,  // initial count
        1,  // maximum count
        NULL);

    if (qSem != NULL) {
        hThread = CreateThread(
                NULL, //default security
                0, //default stack size
                CheckQueueIndexThread, //LPTHREAD_START_ROUTINE
                NULL, //argument to threadFunc
                0, //creation flags
                0
                );
    }
    return hThread;
}

/*
Name: CleanUpThreads

Description: 
Close all created thread.

Return: 0 - All threads have been closed.  
        1 - Some, if not all threads failed to close.
*/
int CleanUpThreads(HANDLE *hThread) {
    int ret = 0; 

    if (CloseHandle(*hThread) == 0) {
        printf("first thread failed to close\n");
        ret = 1;
    }

    for (int i = 0; i < threadCount; i++) {
        if (CloseHandle(hThreadExecutionWork[i]) == 0) {
            printf("ExecuteWorkItems thread %i failed to close\n", i);
            ret = 1;
        }
    }

    return ret;
}

int main(void) {
    int ret = 1;
    HANDLE hThread = NULL;

    hThread = Init();

    if (hThread == NULL) return 1;

    for (int i = 0; i < INDEX_SIZE; ++i) {
        /*Had to dynamically create the Items in heap since compiler 
          would only keep latest copy for locatly created variable*/
        WORK_ITEM *Item = (WORK_ITEM *)malloc(sizeof(WORK_ITEM));

        InitializeWorkItem(Item, i);
    }

    // We wait for all threads to finish its task before we clean them up and exit. 
    WaitForSingleObject(hThread, INFINITE);
    WaitForMultipleObjects(threadCount, hThreadExecutionWork, TRUE, INFINITE);

    ret = CleanUpThreads(&hThread);

    system("pause");
    return ret;
}