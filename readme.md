# タコメーターを使用してCPU使用率を表示させる
    Status: finished!  
    LastUpdate: 2023/07/12  

<img src="https://img.shields.io/badge/licence-masuda-green"> <img src="https://img.shields.io/badge/university-CIT-green"> <img src="https://img.shields.io/badge/undergraduate-Computer%20Science-green">  
<img src="https://img.shields.io/badge/Arduino-blue"> <img src="https://img.shields.io/badge/Tachometer-blue">   
<img src="https://img.shields.io/badge/c-yellow"> <img src="https://img.shields.io/badge/Python-yellow"> <img src="https://img.shields.io/badge/WiredLogic-yellow">  

## 概要
エンジンの回転数を表示させる計器，タコメーターにcpuの使用率を表示させると画面の面積をとらないし針の角度で直感的に視認できるしかっこいいしいいんじゃねと思い制作しました．  

  
### 動作環境
windowsパソコン（linuxやmacはUSBの接続方法が少し違うのでそのままでは動きません）  
2コア以上のIntelもしくはAMD社のCPU（マイナーなプロセッサだと使用率を読み取る機能がついていない場合があります）  
    
### 必要なもの
- Arduino(12Vの電源を使うのでUnoがいいかと思います)
- タコメータ(最大回転数が10000rpmだと直感的に 10000rpm=100% とわかりいいかと思います)
- 12V直流電源(秋月で800円で売ってるし隣のケーブルやさんで500円で売ってます)
- それなりのLED，それなりのユニバーサル基板，それなりのはんだ，はんだごて，ワイヤ，木板などなど

