sem_init(&sem1, 0, 5); // Allow only 5 threads at once to be executed

void limited_area()
{
    sem_wait(&sem1);

    // Code to be executed

    sem_post(&sem1);
}