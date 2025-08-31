#include <stdio.h>


enum ProcessStateEnum {
    READY = 1,
    FINISHED = 0
};


typedef struct SimplePCB {
    int pid;
    enum ProcessStateEnum state;
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


SimplePCB* SJF_shortest_job_search(SimplePCB* tasks, double* time) {
    SimplePCB* shortest_job = NULL;

    while (tasks != NULL) {
        if (tasks->state == READY && tasks->submit_time <= (*time)) {
            if (shortest_job == NULL) {
                shortest_job = tasks;
            }
            if (shortest_job->run_time > tasks->run_time) {
                shortest_job = tasks;
            }
        }
        tasks = tasks->next_pcb;
    }
    return shortest_job;
}


void SJF_work_execute(SimplePCB* pcb, double* time) {
    pcb->start_time = *time;
    
    if (*time > pcb->submit_time) {
        pcb->wait_time = (*time) - pcb->submit_time;
    } else {
        *time = pcb->submit_time;
    }

    *time = *time + pcb->run_time;
    pcb->finish_time = *time;
    pcb->state = FINISHED;
}


void short_job_first_schedule(SimplePCB* tasks, double* time) {
    *time = tasks[0].submit_time;
    SimplePCB* curr_task = NULL;
    do {
        curr_task = SJF_shortest_job_search(tasks, time);
        if (curr_task !=  NULL) {
            SJF_work_execute(curr_task, time);
        }
    } while (curr_task != NULL);
}


void SJF_simulate_result_print(SimplePCB* tasks, int max_pid) {
    SimplePCB* curr_task = tasks;
    for (int curr_pid = 1; curr_pid <= max_pid; curr_pid++) {
        curr_task = tasks;

        while (curr_task != NULL && curr_task->pid != curr_pid) {
            curr_task = curr_task->next_pcb;
        };

        if (curr_task != NULL) {
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
        }
    }
}


int main() {
    SimplePCB pcb1 = {
        .pid = 1, .submit_time = 8, .run_time = 2, .state = READY,
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    SimplePCB pcb2 = {
        .pid = 2, .submit_time = 8.4, .run_time = 1, .state = READY,
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    SimplePCB pcb3 = {
        .pid = 3, .submit_time = 8.8, .run_time = 0.5, .state = READY,
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    SimplePCB pcb4 = {
        .pid = 4, .submit_time = 9, .run_time = 0.2, .state = READY,
        .start_time = 0, .wait_time = 0, .finish_time = 0
    };

    pcb1.next_pcb = &pcb2;
    pcb2.next_pcb = &pcb3;
    pcb3.next_pcb = &pcb4;
    pcb4.next_pcb = NULL;

    double time = 0;

    short_job_first_schedule(&pcb1, &time);
    SJF_simulate_result_print(&pcb1, 4);

    return 0;
}
