int reader_count = 0;
semaphore rw_lock = 1, mutex = 1;

writer() : 
while (true)
{
    wait(rw_lock); /* writer requests to enter critical section */

    /* performs the write operation */

    signal(rw_lock); /* writer leaves the critical section */
}

reader() :
while (true)
{
    wait(mutex);    /* Reader wants to enter the critical section */
    reader_count++; /* The number of readers is increased by 1 */

    if (reader_count == 1)
    {
        wait(rw_lock);
    }
    /*  now we have atleast one reader in critical section and this ensures that
        no writer can enter if there is more than or equal to 1 in the critical section
        thus we give preference to readers here  */

    signal(mutex);
    /*  Other readers can enter while the current reader is still inside the critical section.
         Current reader performs reading here. */

    wait(mutex); /* a reader requests to leave */

    reader_count = reader_count - 1;

    if (reader_count == 0)
    {
        signal(rw_lock);
    }
    /* Now no reader is left in the critical section and only then the writers can enter */

    signal(mutex); /* reader leaves */
}
