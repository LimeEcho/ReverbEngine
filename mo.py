import psutil
import time
import subprocess
import matplotlib.pyplot as plt

def monitor_memory_usage(command):
    # 启动外部程序
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    pid = process.pid
    memory_usage_records = []
    timestamps = []

    start_time = time.time()

    try:
        while process.poll() is None:  # 检查进程是否仍在运行
            try:
                # 获取进程的内存使用情况
                proc = psutil.Process(pid)
                memory_info = proc.memory_info()
                memory_usage_records.append(memory_info.rss / (1024 * 1024))  # 记录 RSS（常驻内存集），单位 MB
                timestamps.append(time.time() - start_time)  # 记录时间戳
                print(f"Memory Usage: {memory_info.rss / (1024 * 1024):.2f} MB")
            except psutil.NoSuchProcess:
                break
            time.sleep(0.5)  # 每隔 1 秒采样一次

        # 等待子进程结束
        process.communicate()
    except KeyboardInterrupt:
        process.terminate()
        print("Monitoring interrupted.")

    print("\nProgram exited.")
    return timestamps, memory_usage_records

def plot_memory_usage(timestamps, memory_usage):
    plt.figure(figsize=(10, 6))
    plt.plot(timestamps, memory_usage, label="Memory Usage (MB)", color="blue", marker="o")
    plt.title("Memory Usage Over Time")
    plt.xlabel("Time (seconds)")
    plt.ylabel("Memory Usage (MB)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    # 替换为你想要启动的程序命令
    command = ["./build/reverb"]  # 示例
    timestamps, memory_usage = monitor_memory_usage(command)
    if timestamps and memory_usage:
        plot_memory_usage(timestamps, memory_usage)
