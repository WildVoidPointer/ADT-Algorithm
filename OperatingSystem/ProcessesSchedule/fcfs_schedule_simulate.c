#include <stdio.h>


typedef struct SimplePCB {
    int pid;
    double submit_time;
    double start_time;
    double wait_time;
    double finish_time;
    double run_time;
    struct SimplePCB* next_pcb;
} SimplePCB;


double SimplePCB_cycle_time(SimplePCB* pcb) {
    return pcb->finish_time - pcb->submit_time;
}


double SimplePCB_turnaround_time(SimplePCB* pcb) {
    return SimplePCB_cycle_time(pcb) / pcb->run_time;
}


void FCFS_work_execute(SimplePCB* pcb, double* time) {
    pcb->start_time = *time;

    if (*time >= pcb->submit_time) {
        pcb->wait_time = (*time) - pcb->submit_time;
    } else {
        *time = pcb->submit_time;
    }
    
    *time = *time + pcb->run_time;
    pcb->finish_time = *time;
}


int first_come_first_served_schedule(SimplePCB* tasks, double* time) {
    *time = tasks[0].submit_time;
    while (tasks != NULL) {
        FCFS_work_execute(tasks, time);
        tasks = tasks->next_pcb;
    }
}


void FCFS_simulate_result_print(SimplePCB* tasks) {
    SimplePCB* curr_task = tasks;

    while (curr_task != NULL) {
        printf(
            "pcb: {  " \
                "pid = %d  " \
                "submit_time = %.1lf  " \
                "run_time = %.1lf  "
                "start_time = %.1lf  " \
                "wait_time = %.1lf  " \
                "finish_time = %.1lf  " \
                "cycle_time = %.1lf  " \
                "turnaround_time = %.1lf  " \
            "}\n",
            curr_task->pid,
            curr_task->submit_time,
            curr_task->run_time,
            curr_task->start_time,
            curr_task->wait_time,
            curr_task->finish_time,
            SimplePCB_cycle_time(curr_task),
            SimplePCB_turnaround_time(curr_task)
        );
        curr_task = curr_task->next_pcb;
    }
}


int main() {
    SimplePCB pcb1 = {
        .pid = 1, .submit_time = 8, .run_time = 2, 
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    SimplePCB pcb2 = {
        .pid = 2, .submit_time = 8.4, .run_time = 1, 
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    SimplePCB pcb3 = {
        .pid = 3, .submit_time = 8.8, .run_time = 0.5, 
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    SimplePCB pcb4 = {
        .pid = 4, .submit_time = 9, .run_time = 0.2, 
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    pcb1.next_pcb = &pcb2;
    pcb2.next_pcb = &pcb3;
    pcb3.next_pcb = &pcb4;
    pcb4.next_pcb = NULL;

    double time;

    first_come_first_served_schedule(&pcb1, &time);
    FCFS_simulate_result_print(&pcb1);

    return 0;
}
