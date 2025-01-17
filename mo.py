import psutil
import time
import subprocess
import matplotlib.pyplot as plt

def monitor_memory_usage(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    pid = process.pid
    memory_usage_records = []
    timestamps = []

    start_time = time.time()

    try:
        while process.poll() is None:
            try:
                proc = psutil.Process(pid)
                memory_info = proc.memory_info()
                memory_usage_records.append(memory_info.rss / (1024 * 1024))
                timestamps.append(time.time() - start_time)
                print(f"Memory Usage: {memory_info.rss / (1024 * 1024):.2f} MB")
            except psutil.NoSuchProcess:
                break
            time.sleep(0.5) 
        process.communicate()
    except KeyboardInterrupt:
        process.terminate()
        print("Stop now")
    print("\nProgram Exit.")
    return timestamps, memory_usage_records
def plot_memory_usage(timestamps, memory_usage):
    plt.figure(figsize=(10, 6))
    plt.plot(timestamps, memory_usage, label="Memory Usage (MB)", color="red", marker="o")
    plt.title("Memory Usage")
    plt.xlabel("Time (s)")
    plt.ylabel("Memory Usage (MB)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()
if __name__ == "__main__":
    command = ["./build/reverb"]
    timestamps, memory_usage = monitor_memory_usage(command)
    if timestamps and memory_usage:
        plot_memory_usage(timestamps, memory_usage)
