# Readers-Writers Problem's Solution
Three variables are used: mutex, wrt, readcnt to implement solution 
 
int reader_count;  /* reader_count tells the number of processes performing read in the critical section */
semaphore mutex, rw_lock; /* semaphore mutex is used to ensure mutual exclusion when reader_count is updated i.e. when any reader enters or exit from the critical section. Semaphore rw_lock is used by both readers and writers to ensure that writers dont enter thier critical section when a reader is already in thier critical section and vice versa. */
