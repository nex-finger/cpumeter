import psutil       #システムの使用率の監視
import serial       #シリアル通信
import serial.tools.list_ports

#シリアル通信の初期設定
class SerialSetup:
    def __init__(self):
        self.ports = list(serial.tools.list_ports.comports())        #シリアルポート一覧取得
    
    def GetSerialPort(self):
        for p in self.ports:
            if ("Silicon" in p.manufacturer) == True:
                print("open")
                return p.name
            #print("no python")
    
    def close(self):
        ser.close()        #通信終了

#シリアル通信で情報の転送
class SerialCommunication:
    def __init__(self, value):
        self.value = value
        self.byted_value = bytes([value])
    
    def WriteSerialData(self):
        ser.write(self.byted_value)      #データの送信
        #print(self.value)

#数値の正規化
class Normalizer:
    def __init__(self):
        self.min_value = 0
        self.max_value = 100
    
    def Normalize(self, value, sign):
        normalized_value = int((value - self.min_value) * 127 / (self.max_value - self.min_value))
        normalized_value = max(0, min(127, normalized_value))       # 値を0から127の範囲に制限
        if(sign == 1):
            normalized_value += 128
        return normalized_value

#cpuの使用率を取得
class SystemMonitor:
    def __init__(self):
        self.interval = 0.1     #x秒に一度使用率を取得する

    def monitor(self):
        cpu = psutil.cpu_percent(interval = self.interval, percpu = True)       #全てのコアの使用率を配列で取得
        cpu_ave = sum(cpu) / len(cpu)
        cpu_max = max(cpu)

        nave = Normalizer()
        data_ave = nave.Normalize(cpu_ave, 0)
        save = SerialCommunication(data_ave)
        save.WriteSerialData()

        nmax = Normalizer()
        data_max = nmax.Normalize(cpu_max, 1)
        smax = SerialCommunication(data_max)
        smax.WriteSerialData()

        print("\r"+"ave : "+str(round(cpu_ave, 1))+"  max : "+str(round(cpu_max, 1))+ "      ",end="")

if __name__ == "__main__":
    print("CPU monitor masuda")
    data_ave = 0
    data_max = 0
    
    s = SerialSetup()
    name = s.GetSerialPort()
    ser = serial.Serial(name, 9600, timeout = 0.1)        #通信開始

    while True:
        m = SystemMonitor()
        m.monitor()