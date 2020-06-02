import time
import RPi.GPIO as GPIO

DATA_PORT = 18
count = 0

tpr = 0
hum = 0

GPIO.setmode(GPIO.BCM)
while True:

    errflag = False
    datatmp = 0
    cntlist = []

    #s = input("want to start a sampling?[y/n]\n")
    #if s != "y":
        #break
    
    time.sleep(1)               # 上电启动1s延时
    GPIO.setup(DATA_PORT, GPIO.OUT)
    GPIO.output(DATA_PORT, GPIO.LOW) # 主机拉低总线，发开始信号
    time.sleep(0.025)           # 拉低18ms以上
    GPIO.setup(DATA_PORT, GPIO.IN)   # 总线由上拉电阻拉高，等丛机信号
    while GPIO.input(DATA_PORT) != GPIO.LOW:    # 等从机响应低电平
        count += 1
        if count > 600:
            print("ERROR: SLAVE NO RESPONSE")
            errflag = True
            break
    else:
        count = 0
    if errflag:
        continue
    while GPIO.input(DATA_PORT) != GPIO.HIGH:     # 等从机拉高电平
        count += 1
        if count > 100:
            print("ERROR: SLAVE RESPONSE TIMEOUT")
            errflag = True
            break
    else:
        count = 0  
    if errflag:
        continue  
    while GPIO.input(DATA_PORT) != GPIO.LOW:   # 等从机拉低，开始传送数据
        count += 1
        if count > 100:
            print("ERROR: DATA RECEIVE BEGIN TIMEOUT")
            errflag = True
            break
    else:
        count = 0    
    if errflag:
        continue 

    # 40bit数据接收   
    for j in range(40):
        while GPIO.input(DATA_PORT) != GPIO.HIGH:    # 等从机拉高传数据
            pass
        while GPIO.input(DATA_PORT) != GPIO.LOW:     # 等低电平开始下一数据位
            count += 1
        if count < 18:
            datatmp |= 0 << (39 - j)
        else:
            datatmp |= 1 << (39 - j)
        cntlist.append(count)
        count = 0

    # 校验
    # print(cntlist)
    read = [(datatmp >> (8*(4-i))) & 0XFF for i in range(5)]
    #print(read)
    checksum = sum(read[:4]) & 0XFF
    if checksum == read[4]:
        tpr = read[2]
        hum = read[0]
        print("Humidity: %d, Temperature: %d" % (hum, tpr))
    else:
        print("ERROR: CHECKSUM NOT MATCH")      
        # 输出采集到的数据，便于调试
        print('''FETCH DATA:\n
            humidity = {0[0]}\n
            humidity_frac = {0[1]}\n
            temperature = {0[2]}\n
            temperature_frac = {0[3]}\n
            checksum = {0[4]}\n
            Expected checksum = {1}'''.format(read, checksum))       