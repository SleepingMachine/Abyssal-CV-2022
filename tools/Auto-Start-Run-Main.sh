#!/bin/sh

#相机驱动加载
#echo 'abyssal' | sudo -S echo "USBDriver"
#v4l2-ctl -d /dev/video0 -c exposure_absolute=200

#sleep 1
cd /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug
renum=0
#自动输入密码，启动Baldr
sudo ./Abyssal_CV_2022
echo abyssal | sudo -S cpufreq-set -g performance
pwd
while true; do
#当Baldr不在运行时启动Baldr，重启三次就重新开机
	echo 'abyssal' | sudo -S echo "Abyssal"
        PID0=`pgrep Abyssal`
        if [ ! "$PID0" ]; then
            sudo ./Abyssal_CV_2022
	    echo "restart"
            renum=$(($renum+1))
            echo $renum
	fi
        if [ $renum -gt 3 ]
        then
	    echo "abyssal"
            shutdown -r now
        fi
	sleep 2
done
