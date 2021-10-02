# EDF
Embedded Development Framework
# Attention
The base template is based on stm32f407zet6,the develop board is explorer which is made by zhengdianyuanzi
and its result is send "hello world" every seconds
if you want to use this framework,the following step is:
### 1.download the repo
### 2.just open /project/keil/template.uvprojx
### 3.build and run
### 4.see what happen by watching the result on serial debug assistant
## 2021.9.25
#### Based on FreeRTOS template have been built,usage step is as same as bare board
#### Based on FreeRTOS padding template also have been built,usage step is as same as bare board
## 2021.10.2
#### Add dbs threadx application in demo direct.And fix the bug that Connecting to wifi in the wrong way
#### Esp8266 uart interrupt must be a little higher priority than freertos that it can control the maximum of priority 
