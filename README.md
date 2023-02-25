# Readers-Writers Problem's Solution

*This is a solution for the Readers-Writers problem using semaphores. We assume readers' preference in the solution.*

Three variables are used in the pseudocode: mutex, rw_lock, reader_count 

We define a variable **reader_count** which gives the number of processes performing read in the critical section currently,
```
int reader_count; 
```
Semaphore **mutex** is used to ensure mutual exclusion when **reader_count** is updated i.e. when any reader enters or exit from the critical section. 

Semaphore **rw_lock** is used by both readers and writers to ensure that writers dont enter thier critical section when a reader is already in thier critical section and vice versa. */
```
semaphore mutex, rw_lock; 
```
Functions for semaphore : 

* **wait()** : decrements the semaphore value. 

* **signal()** : increments the semaphore value. 

### Writer process:
 

* Writer requests the entry to critical section.
* If allowed i.e. wait() return true, it enters and performs the write operation. If not allowed, it keeps waiting.
* It exits the critical section.

```
reader():
while(true){
    wait(rw_lock);  /* writer requests to enter critical section */
    
    /* performs the write operation */
    
    signal(rw_lock);  /* writer leaves the critical section */
} 
```

### Reader process: 
 
* Reader requests the entry to critical section.
* If allowed: 
    - It increments the count of number of readers inside the critical section. If this reader is the first reader entering, it locks the **rw_lock** semaphore to restrict the entry of writers if any reader is inside.
    - It then, signals **mutex** as any other reader is allowed to enter while others are already reading.
    - After performing reading, it exits the critical section. When exiting, it checks if no more reader is inside, it signals the semaphore “**rw_lock**” as now, writer can enter the critical section.
* If not allowed, it keeps on waiting.
```
writer():

while(true){
   wait(mutex);  /* Reader wants to enter the critical section */
   reader_count++;  /* The number of readers is increased by 1 */          
   
   if (reader_count==1) {    
		wait(rw_lock);    
   }    
   /*  now we have atleast one reader in critical section and this ensures that
       no writer can enter if there is more than or equal to 1 in the critical section 
       thus we give preference to readers here  */           

   signal(mutex); 
   /*  Other readers can enter while the current reader is still inside the critical section.          
      	Current reader performs reading here. */

   wait(mutex);   /* a reader requests to leave */

   reader_count = reader_count - 1;

   if (reader_count == 0) {
        signal(rw_lock);
	}  
   /* Now no reader is left in the critical section and only then the writers can enter */
   
   signal(mutex); /* reader leaves */ 
}
```

Thus, the semaphore **rw_lock** is used to give preference to readers by ensuring that no writer enters when a reader is reading.
