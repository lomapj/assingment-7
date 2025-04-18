import threading
import time
import random

fork0 = threading.Lock()
fork1 = threading.Lock()

def philosopher(id):
    if id == 0:
        first_fork = fork0
        second_fork = fork1
        name = "Philosopher 0"
    else:
        first_fork = fork1
        second_fork = fork0
        name = "Philosopher 1"
    
    while True:
        think_time = random.uniform(1, 3)
        print(f"{name} is thinking for {think_time:.1f} seconds")
        time.sleep(think_time)
        
        print(f"{name} is hungry and wants to eat")
        
        print(f"{name} is trying to pick up first fork")
        first_fork.acquire()
        print(f"{name} picked up first fork")
        
        print(f"{name} is trying to pick up second fork")
        second_fork.acquire()
        print(f"{name} picked up second fork")
        
        eat_time = random.uniform(1, 3)
        print(f"{name} is eating for {eat_time:.1f} seconds")
        time.sleep(eat_time)
        
        second_fork.release()
        print(f"{name} put down second fork")
        first_fork.release()
        print(f"{name} put down first fork")

philosopher_threads = []
for i in range(2):
    thread = threading.Thread(target=philosopher, args=(i,))
    thread.daemon = True
    philosopher_threads.append(thread)
    thread.start()

try:
    time.sleep(20)
except KeyboardInterrupt:
    print("Simulation stopped by user")



